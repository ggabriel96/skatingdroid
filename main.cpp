#include <stdio.h>
#include <GL/glut.h>
#include "skating.h"

int main(int argc, char *argv[]) {
  int status = 0;
  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	glutCreateWindow(WINDOW_TITLE);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init_gl();
  status = init_droid();
	if (status == 0)
    glutMainLoop();
  return status;
}
