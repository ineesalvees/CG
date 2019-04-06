#ifndef _Color_H_
#define _Color_H_


class Color{
	private:
		float r, b, g;

	public:
		Color();
		Color(float r, float b, float g);

		float getR(){
			return this->r;
		}

		float getB(){
			return this->b;
		}

		float getG(){
			return this->g;
		}

		void setR(float r){
			this->r = r;
		}

		void setB(float b){
			this->b = b;
		}

		void setG(float g){
			this->g = g;
		}
};
#endif