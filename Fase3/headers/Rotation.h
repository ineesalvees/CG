#ifndef _Rotation_H_
#define _Rotation_H_

class Rotation : public Transformation {
	private:
		float time, axisX, axisY, axisZ;

	public:
		Rotation();
		Rotation(float time, float axisX, float axisY, float axisZ);

		float getTime(){
			return time;
		}

		float getAxisX(){
			return axisX;
		}

		float getAxisY(){
			return axisY;
		}

		float getAxisZ(){
			return axisZ;
		}
};
#endif
