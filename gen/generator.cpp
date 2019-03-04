#ifdef __GENERATOR__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string.h>
#include <stdlib.h>

#include "../Plane.cpp"
#include "../Box.cpp"
#include "../Cone.cpp"
#include "../Sphere.cpp"

using namespace std;

int main (int argc, char *argv[]) {
	cout << argv[1] << "\n";

	if (argc > 2) {
		if (strcmp(argv[1],"Sphere") == 0) {
			cout << "Drawing Sphere!\n";

			float radius = atof(argv[2]);
			int slices = atoi(argv[3]);
			int stacks = atoi(argv[4]);

			Sphere *s = new Sphere(radius,slices,stacks);
			s->save(argv[5]);
		}
		if (strcmp(argv[1],"Box") == 0) {
			cout << "Drawing Box!\n";

			float x = atof(argv[2]);
			float y = atof(argv[3]);
			float z = atof(argv[4]);
			int slices = atoi(argv[5]);

			Box *b = new Box(x,y,z,slices);
			b->save(argv[6]);
			
		}
		if (strcmp(argv[1],"Plane") == 0) {
			cout << "Drawing Plane!\n";

			float size = atof(argv[2]);
			float height = atof(argv[3]);

			Plane *p = new Plane(size,height);
			p->save(argv[4]);
		}
		if (strcmp(argv[1],"Cone") == 0) {
			cout << "Drawing Cone!\n";

			float radius = atof(argv[2]);
			float height = atof(argv[3]);
			int slices = atoi(argv[4]);
			int stacks = atoi(argv[5]);
			
			Cone *c = new Cone (radius,height,slices,stacks);
			c->save(argv[6]);
		}
	} else {
		cout << "Argumentos insuficientes!\n";
	}


}