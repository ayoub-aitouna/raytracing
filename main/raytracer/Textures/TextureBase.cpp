#include "headers/TextureBase.hpp"

RT::Texture::TextureBase::TextureBase()
{
}
RT::Texture::TextureBase::~TextureBase()
{
}

// FUntion to return color at given point at the (u,v) coordinate sytem
//  color is return as 4 dims verctor (RGBA)
qbVector<double> RT::Texture::TextureBase::GetColor(qbVector<double> &u_v_cords)
{
    // setUp the output Vector
    qbVector<double> output{4};
    return (output);
}

// Funtion to set transform
void RT::Texture::TextureBase::SetTransform(const qbVector<double> &translation,
                                            const double &rotation, const qbVector<double> &scal)
{
    qbMatrix2<double> rotationMt = {3, 3,
                                    std::vector<double>{
                                        cos(rotation), -sin(rotation), 0.0,
                                        sin(rotation), cos(rotation), 0.0,
                                        0.0, 0.0, 1.0}};

    qbMatrix2<double> ScalMt = {3, 3,
                                std::vector<double>{
                                    scal.GetElement(0), 0.0, 0.0,
                                    0.0, scal.GetElement(1), 0.0,
                                    0.0, 0.0, 1.0}};
    qbMatrix2<double> translationMt = {3, 3,
                                       std::vector<double>{
                                           1.0, 0.0, translation.GetElement(0),
                                           0.0, 1.0, translation.GetElement(1),
                                           0.0, 0.0, 1.0}};

    m_transformMatrex = translationMt * rotationMt * ScalMt;
}

// Funtikon ti blend RGBA to RGB
//  becuase we use only RGB colors in the codebase
qbVector<double> RT::Texture::TextureBase::BlendColors(const std::vector<qbVector<double>> &ColorList)
{
    // setUp the output Vector
    qbVector<double> output{3};
    return (output);
}

// funtion to Apply local transform to the given vector.
qbVector<double> RT::Texture::TextureBase::AppyTransform(const qbVector<double> &inputVecor)
{
    // the input vector expacted to be {2}
    // we Copy it to a {3} Vector
    qbVector<double> new_input = qbVector<double>{
        std::vector<double>{inputVecor.GetElement(0), inputVecor.GetElement(1), 0}};

    qbVector<double> result = m_transformMatrex * new_input;

    qbVector<double> output = qbVector<double>{
        std::vector<double>{result.GetElement(0), result.GetElement(1)}};
    return output;
}