#include <cmath>
#include <cstdarg>
#ifndef GTFM_H
#define GTFM_H
#include "../../qbLinAlg/qbVector.h"
#include "../../qbLinAlg/qbMatrix.h"
#include "ray.h"

namespace RT {
	// DEfinr direction flag value
	constexpr bool FWDTFORM = true;
	constexpr bool BCKTFORM = false;

	class Gtform
	{
		public:
			Gtform();
			~Gtform();
			Gtform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);
			// function to set translation and scal component 
			void SetTransform(const qbVector<double> &translation,
					const qbVector<double> &rotation,
					const qbVector<double> &scal);
			//function to return transform matrices
			qbMatrix2<double> GetForwardd();
			qbMatrix2<double> GetBackward();
			//function to apply the transform
			RT::Ray Apply(const RT::Ray &inputRay, bool dirFlag);
			qbVector<double> Apply(const qbVector<double> &inputVector, bool dirFlag);
			//overload operators
			friend Gtform operator*(const RT::Gtform &lhs, const RT::Gtform &rhs);
			// overload assigment operator
			Gtform operator= (const Gtform &rhs);
			// function to print transform matrix to STDOUT
			void PrintMatrix(bool dirFlag);
			//function to allow printing of vectors.
			static void PrintVector(const qbVector<double> &vector);

		private:
			void Print(const qbMatrix2<double> &matrix);

		private:
			qbMatrix2<double> m_fwdtfm{4,4};
			qbMatrix2<double> m_bcktfm{4,4};
	};
}
#endif
