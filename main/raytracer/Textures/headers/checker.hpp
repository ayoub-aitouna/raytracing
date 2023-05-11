#ifndef CHECKER_H
#define CHECKER_H

#include "TextureBase.hpp"

namespace RT
{

	namespace Texture
	{
		class Checker : public TextureBase
		{
		public:
			Checker();
			virtual ~Checker() override;

			virtual qbVector<double> GetColor(qbVector<double> &u_v_cords) override;

			void SetColor(const qbVector<double> &color1, qbVector<double> color2);

		private:
			qbVector<double> color1;
			qbVector<double> color2;
		};
	}
}
#endif
