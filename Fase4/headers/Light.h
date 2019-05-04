#ifndef _LIGHT_H_
#define _LIGHT_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <string>

using namespace std; 
class Light{
	private:
		float x, y, z;
		std::string type;

	public:
		Light();
		Light(float x, float y, float z, std::string type);

		void renderLight(void);
		float getX() {
			return x;
		}
		float getY() {
			return y;
		}
		float getZ() {
			return z;
		}
		std::string getType() {
			return type;
		}


};
#endif