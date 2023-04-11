#include "includes/gtfm.hpp"
#include <cmath>
#include <iomanip>
#include <ios>
#include <iterator>
#include <stdexcept>
#include <vector>

RT::Gtform::Gtform()
{
	// *Set forward and backward transforms to identity matrices
	m_fwdtfm.SetToIdentity();
	m_bcktfm.SetToIdentity();
}

RT::Gtform::~Gtform()
{
}

//construct from a pair of matrices
RT::Gtform::Gtform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck)
{
	//verify that the inputs are 4x4
	if((fwd.GetNumRows() != 4 || fwd.GetNumCols() != 4) || 
			(bck.GetNumRows() != 4 || bck.GetNumCols() != 4))
	{
		throw std::invalid_argument("Connot construct Gtform, inputs are not all 4x4");
	}
	m_fwdtfm = fwd;
	m_bcktfm = bck;
}

// function to set the transform
void RT::Gtform::SetTransform(const qbVector<double> &translation, const qbVector<double> &rotation, const qbVector<double> &scal)
{
	// define a matrix for each component of the transform
	qbMatrix2<double>	translation_matrix {4,4};
	qbMatrix2<double>	rotationMatriX {4, 4};
	qbMatrix2<double>	rotationMatriY {4, 4};
	qbMatrix2<double>	rotationMatriZ {4, 4};
	qbMatrix2<double>	scalMatrix {4, 4};
	// set to identity
	// [1,0,0,0]
	// [0,1,0,0]
	// [0,0,1,0]
	// [0,0,0,1]
	translation_matrix.SetToIdentity();
	rotationMatriX.SetToIdentity();
	rotationMatriY.SetToIdentity();
	rotationMatriZ.SetToIdentity();
	scalMatrix.SetToIdentity();
	// populate these with probpriate values
	// first translation matri
	translation_matrix.SetElement(0, 3, translation.GetElement(0));
	translation_matrix.SetElement(1, 3, translation.GetElement(1));
	translation_matrix.SetElement(2, 3, translation.GetElement(2));

	rotationMatriZ.SetElement(0, 0, std::cos(rotation.GetElement(2)));
	rotationMatriZ.SetElement(0, 1, -std::sin(rotation.GetElement(2)));
	rotationMatriZ.SetElement(1, 0, std::sin(rotation.GetElement(2)));
	rotationMatriZ.SetElement(1, 1, std::cos(rotation.GetElement(2)));

	rotationMatriY.SetElement(0, 0, std::cos(rotation.GetElement(1)));
	rotationMatriY.SetElement(0, 2, std::sin(rotation.GetElement(1)));
	rotationMatriY.SetElement(2, 0, -std::sin(rotation.GetElement(1)));
	rotationMatriY.SetElement(2, 2, std::cos(rotation.GetElement(1)));

	rotationMatriX.SetElement(1, 1, std::cos(rotation.GetElement(0)));
	rotationMatriX.SetElement(1, 2, -std::sin(rotation.GetElement(0)));
	rotationMatriX.SetElement(2, 1, std::sin(rotation.GetElement(0)));
	rotationMatriX.SetElement(2, 2, std::cos(rotation.GetElement(0)));
	//And the scal matrex
	scalMatrix.SetElement(0, 0, scal.GetElement(0));
	scalMatrix.SetElement(1, 1, scal.GetElement(1));
	scalMatrix.SetElement(2, 2, scal.GetElement(2));
	// combine to give the  final transform matrix
	m_fwdtfm = translation_matrix * scalMatrix * rotationMatriX * rotationMatriY * rotationMatriZ;
	// compute the backward transform
	m_bcktfm = m_fwdtfm;
	m_bcktfm.Inverse();
}

// Function to return transform matrices
qbMatrix2<double> RT::Gtform::GetForwardd()
{
	return m_fwdtfm;
}

qbMatrix2<double> RT::Gtform::GetBackward()
{
	return m_bcktfm;
}

// apply  the transform
RT::Ray RT::Gtform::Apply(const RT::Ray &inputRay, bool dirFlag)
{
	// create output object
	RT::Ray output;

	output.m_point1 = this->Apply(inputRay.m_point1, dirFlag);
	output.m_point2 = this->Apply(inputRay.m_point2, dirFlag);
	output.m_lab = output.m_point2 - output.m_point1;
	return output;
}

qbVector<double> RT::Gtform::Apply(const qbVector<double> &inputVector, bool dirFlag)
{
	std::vector<double> tempData = { inputVector.GetElement(0),
		inputVector.GetElement(1),
		inputVector.GetElement(2),
		1.0 };

	qbVector<double> tempVector {tempData};
	qbVector<double> resultVector;

	if(dirFlag)
	{
		// Apply the Fowrdard transform
		resultVector = m_fwdtfm * tempVector;
	}
	else
	{
		// Apply the backward transform
		resultVector = m_bcktfm * tempVector;
	}
	// Reform the output as a 4-elemt vector
	qbVector<double> result = { std::vector<double>{resultVector.GetElement(0),
		resultVector.GetElement(1),
		resultVector.GetElement(2)}};
	return (result);
}

// Overload operators
namespace RT {
	RT::Gtform operator*(const RT::Gtform &lhs, const Gtform &rhs)
	{
		// Form the product of the two forward transforms.
		qbMatrix2<double> fwdResult = lhs.m_fwdtfm * rhs.m_fwdtfm;
		// Compute the backward transform as the Inverse of the forward transform
		qbMatrix2<double> bckResult = fwdResult;
		bckResult.Inverse();
		// Form the final result
		RT::Gtform finalResult (fwdResult, bckResult);
		return  finalResult;
	}
}

// Overload th assigment operator
RT::Gtform RT::Gtform::operator=(const Gtform &rhs)
{
	// Make sure that we're not assigning to ourself 
	if(this == &rhs)
		return *this;
	this->m_fwdtfm = rhs.m_fwdtfm;
	this->m_bcktfm = rhs.m_bcktfm;
	return *this;
}

// function to print thr transform matrix to STDOUT
void RT::Gtform::PrintMatrix(bool dirFlag) 
{
	if(dirFlag == FWDTFORM)
		Print(m_fwdtfm);
	else 
		Print(m_bcktfm);
}

void RT::Gtform::Print(const qbMatrix2<double> &matrix)
{
	int nRows = matrix.GetNumRows();
	int nCols = matrix.GetNumCols();
	int r = 0; int c = 0;
	while (r < nRows) {
		c = 0;
		while (r < nRows)
			std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(r, c++);
		std::cout << std::endl;
		r++;
	}
}

void RT::Gtform::PrintVector(const qbVector<double> &vector)
{
	int nRows = vector.GetNumDims();
	int i = 0;
	while (i < nRows)
		std::cout << std::fixed << std::setprecision(3) << vector.GetElement(i++);
}

