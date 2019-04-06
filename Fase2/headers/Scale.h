#ifndef _Scale_H_
#define _Scale_H_


class Scale{
	private:
		float x, y, z;

	public:
		Scale();
		Scale(float x, float y, float z);

		float getX(){
			return this->x;
		}

		float getY(){
			return this->y;
		}

		float getZ(){
			return this->z;
		}

		void setX(float x){
			this->x = x;
		}

		void setY(float y){
			this->y = y;
		}

		void setZ(float z){
			this->z = z;
		}
};
#endif