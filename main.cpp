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
	// glutIdleFunc(idle);
	glutDisplayFunc(display);
  glutTimerFunc(1000.0 / TARGET_FPS, idle, 0);
	glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
	init_gl();
  status = init_defquad();
	if (status == 0)
    glutMainLoop();
  else fprintf(stderr, "Failed to initialize defquad\n");
  return status;
}
