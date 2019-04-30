#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <string>

using namespace std; 
class Light{
	private:
		float x, y, z;
		std::string type;

	public:
		Light();
		Light(float x, float y, float z, std::string type);

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