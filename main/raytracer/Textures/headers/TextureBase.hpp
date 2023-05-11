#ifndef TEXTURE_BASE
#define TEXTURE_BASE
#include <memory>
#include "../../../qbLinAlg/qbMatrix.h"
#include "../../../qbLinAlg/qbVector.h"
#include "../../Objects/headers/objectbase.hpp"
#include "../../includes/ray.h"

namespace RT
{
    namespace Texture
    {
        class TextureBase
        {
        public:
            TextureBase();
            virtual ~TextureBase();

            // FUntion to return color at given point at the (u,v) coordinate sytem
            //  color is return as 4 dims verctor (RGBA)
            virtual qbVector<double> GetColor(qbVector<double> &u_v_cords);

            // Funtion to set transform
            void SetTransform(const qbVector<double> &translation,
                              const double &rotation, const qbVector<double> &scal);

            // Funtikon ti blend RGBA to RGB
            //  becuase we use only RGB colors in the codebase
            static qbVector<double> BlendColors(const std::vector<qbVector<double>> &ColorList);

            // funtion to Apply local transform to the given vector.
            qbVector<double> AppyTransform(const qbVector<double> &inputVecor);

        private:
            qbMatrix2<double> m_transformMatrex
            {
                3, 3, std::vector<double>
                {
                    1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 1.0
                }
            };
        };
    }
}

#endif