#ifndef FLAT_H
#define FLAT_H
#include "TextureBase.hpp"
namespace RT {

	namespace Texture {

		class Flat :  public TextureBase
		{
			public:
				Flat();
				~Flat();
				// FUntion to return color at given point at the (u,v) coordinate sytem
				//  color is return as 4 dims verctor (RGBA)
				virtual qbVector<double> GetColor(qbVector<double> &u_v_cords) override;
				void SetColor(const qbVector<double> &inputColor);
			private:
				qbVector<double> m_color {4};

		};
	}
}
#endif

