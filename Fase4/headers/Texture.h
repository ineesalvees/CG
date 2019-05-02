#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>

using namespace std; 
class Texture{
	private:
		float r,g,b;

		std::string texture;

	public:
		Texture();
		Texture(float r, float g, float b, std::string texture);

		float getR() {
			return r;
		}
		float getG() {
			return g;
		}
		float getB() {
			return b;
		}
		std::string getTexture() {
			return texture;
		}

};
#endif
