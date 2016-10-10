#include <stdio.h>
#include <GL/glut.h>

void identity(GLenum model) {
  glMatrixMode(model);
  glLoadIdentity();
}

void resizeWindow(GLsizei w, GLsizei h) {
	// Avoid division by 0
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

  identity(GL_PROJECTION);
	gluPerspective(45.0 /* angle of view */, (double) w / h /* aspect ratio */ , 1.0 /* near */, 100.0 /* far */);

  identity(GL_MODELVIEW);
}

void idle() {
	glutPostRedisplay();
}

void init(void) {
  identity(GL_MODELVIEW);

  // The position is transformed by the modelview matrix when glLight is called (just as if
  // it were a point), and it is stored in eye coordinates. If the w component of the position
  // is 0, the light is treated as a directional source. Diffuse and specular lighting calculations
  // take the light's direction, but not its actual position, into account, and attenuation is
  // disabled. Otherwise, diffuse and specular lighting calculations are based on the actual
  // location of the light in eye coordinates, and attenuation is enabled.
  const GLfloat light0_position[] = {25.0, 25.0, 25.0, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  const GLfloat light0_ambient[] = {0.0, 0.0, 0.0, 1.0};
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  const GLfloat light0_color[] = {1.0, 1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_color);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0_color);
  const GLfloat light_ambient_global[] = {0.2, 0.2, 0.2, 1.0}; // default is 0.2, 0.2, 0.2, 1.0
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_global);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // Enable GL_COLOR_MATERIAL and set glColorMaterial to GL_AMBIENT_AND_DIFFUSE.
  // This means that glMaterial will control the polygon's specular and emission
  // colours and the ambient and diffuse will both be set using glColor.
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  const GLfloat material_specular[] = {1.0, 1.0, 1.0, 1.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
  const GLfloat material_shininess[] = {128.0}; // 0 to 128. The higher, the "thinner" the "little white glow"
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);

  glShadeModel(GL_SMOOTH); // GL_SMOOTH is the default

  glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void draw(void) {
	identity(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gluLookAt(0.0, 25.0, 25.0 /* position*/,
            0.0, 0.0, 0.0 /* look at */,
            0.0, 1.0, 0.0 /* up vector */);

  glPushMatrix();
  glColor3d(0.5, 1.0, 1.0);
  glTranslated(-15.0, 0.0, 0.0);
  glutSolidSphere(5.0, 64, 64);
  glPopMatrix();

  glPushMatrix();
  glColor3d(1.0, 0.5, 1.0);
  glTranslated(15, 0.0, 0.0);
  glutSolidSphere(5.0, 64, 64);
  glPopMatrix();

  glPushMatrix();
  glColor3d(1.0, 1.0, 0.5);
  glRotated(90.0, 0.0, 1.0, 0.0);
  glutSolidTeapot(5.0);
  glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Skating Droid");
	glutIdleFunc(idle);
	glutDisplayFunc(draw);
	glutReshapeFunc(resizeWindow);
	init();
	glutMainLoop();
  return 0;
}
