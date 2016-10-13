#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include "skating.h"

GLUquadricObj *defquad = NULL;
double cam_x_angle = 0.0, cam_y_angle = 0.0;
double cam_x = 1.0, cam_y = 1.0, cam_z = 40.0;

void identity(GLenum model) {
  glMatrixMode(model);
  glLoadIdentity();
}

void drawEllipse(double radx, double rady, int slices) {
  int d;
  double rad = 2 * M_PI / slices, x, y;
	glBegin(GL_POLYGON);
	for (d = 0; d <= slices; d++) {
		x = radx * sin(d * rad);
		y = rady * cos(d * rad);
    // glNormal3d(x, y, 0.0);
		glVertex3d(x, y, 0.0);
	}
	glEnd();
}

void draw_droid_antenna(int dir) {
  double delta_y = (DROID_HEIGHT / 2.0) + DROID_RADIUS + DROID_ANT_LENGTH - DROID_RATIO;
  glPushMatrix();

  glRotated(15.0, 0.0, 0.0, dir == DROID_LEFT ? 1.0 : -1.0);

  // antenna
  glPushMatrix();
  glTranslated(0.0, delta_y, 0.0);
  glRotated(90.0, 1.0, 0.0, 0.0);
  gluCylinder(defquad, DROID_ANT_RADIUS, DROID_ANT_RADIUS, DROID_ANT_LENGTH, OBJ_SLICES, OBJ_STACKS);
  glPopMatrix();
  // point
  glPushMatrix();
  glTranslated(0.0, delta_y, 0.0);
  gluSphere(defquad, DROID_ANT_RADIUS, OBJ_SLICES, OBJ_STACKS);
  glPopMatrix();

  glPopMatrix();
}

void draw_droid_antennae(void) {
  draw_droid_antenna(DROID_LEFT);
  draw_droid_antenna(DROID_RIGHT);
}

void draw_droid_head(void) {
  glPushMatrix();
  glTranslated(0.0, DROID_HEIGHT / 2.0, 0.0);
  gluSphere(defquad, DROID_RADIUS, OBJ_SLICES, OBJ_STACKS);
  glPopMatrix();
}

void draw_droid_body(void) {
  glPushMatrix();
  glTranslated(0.0, DROID_HEIGHT / 2.0, 0.0);
  glRotated(90.0, 1.0, 0.0, 0.0);
  // Draws a cylinder oriented along the z axis, with the base of the cylinder at z = 0 and the top at z = height.
  // Like a sphere, the cylinder is subdivided around the z axis into a number of slices and along the z axis into
  // a number of stacks. baseRadius is the radius of the cylinder at z = 0. topRadius is the radius of the cylinder
  // at z = height. If topRadius is set to zero, then a cone is generated.
  // void gluCylinder (GLUquadricObj *qobj, GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);
  gluCylinder(defquad, DROID_RADIUS, DROID_RADIUS, DROID_HEIGHT, OBJ_SLICES, OBJ_STACKS);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.0, - DROID_HEIGHT / 2.0, 0.0);
  glRotated(90.0, 1.0, 0.0, 0.0);
  gluDisk(defquad, 0.0, DROID_RADIUS, OBJ_STACKS, OBJ_STACKS);
  glPopMatrix();
}

void draw_droid_arm(int dir) {
  glPushMatrix();

  glTranslated(dir == DROID_LEFT ? - DROID_RADIUS - (1.2 * DROID_ARM_RADIUS) : DROID_RADIUS + (1.2 * DROID_ARM_RADIUS), 0.0, 0.0);

  // shoulder
  glPushMatrix();
  glTranslated(0.0, DROID_ARM_LENGTH - DROID_ARM_RADIUS, 0.0);
  gluSphere(defquad, DROID_ARM_RADIUS, OBJ_SLICES, OBJ_STACKS);
  glPopMatrix();
  // arm
  glPushMatrix();
  glTranslated(0.0, DROID_ARM_LENGTH - DROID_ARM_RADIUS, 0.0);
  glRotated(90.0, 1.0, 0.0, 0.0);
  gluCylinder(defquad, DROID_ARM_RADIUS, DROID_ARM_RADIUS, DROID_ARM_LENGTH, OBJ_SLICES, OBJ_STACKS);
  glPopMatrix();
  // hand
  glPushMatrix();
  glTranslated(0.0, - DROID_ARM_RADIUS, 0.0);
  gluSphere(defquad, DROID_ARM_RADIUS, OBJ_SLICES, OBJ_STACKS);
  glPopMatrix();

  glPopMatrix();
}

void draw_droid_arms(void) {
  draw_droid_arm(DROID_LEFT);
  draw_droid_arm(DROID_RIGHT);
}

void draw_droid_leg(int dir) {
  glPushMatrix();

  glTranslated(dir == DROID_LEFT ? - DROID_RADIUS / 2.0 : DROID_RADIUS / 2.0, 0.0, 0.0);

  // leg
  glPushMatrix();
  glTranslated(0.0, - DROID_HEIGHT / 2.0, 0.0);
  glRotated(90.0, 1.0, 0.0, 0.0);
  gluCylinder(defquad, DROID_LEG_RADIUS, DROID_LEG_RADIUS, DROID_LEG_LENGTH, OBJ_SLICES, OBJ_STACKS);
  glPopMatrix();
  // foot
  glPushMatrix();
  glTranslated(0.0, (- DROID_HEIGHT / 2.0) - DROID_LEG_LENGTH, 0.0);
  gluSphere(defquad, DROID_LEG_RADIUS, OBJ_SLICES, OBJ_STACKS);
  glPopMatrix();

  glPopMatrix();
}

void draw_droid_legs(void) {
  draw_droid_leg(DROID_LEFT);
  draw_droid_leg(DROID_RIGHT);
}

void draw_droid(void) {
  draw_droid_antennae();
  draw_droid_head();
  draw_droid_body();
  draw_droid_arms();
  draw_droid_legs();
}


void idle(void) {
	glutPostRedisplay();
}

void display(void) {
	identity(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gluLookAt(cam_x, cam_y, cam_z /* position*/,
            CENTER_X, CENTER_Y, CENTER_Z /* look at */,
            0.0, 1.0, 0.0 /* up vector */);

  glPushMatrix();
  glColor3ubv(color_droid);
  draw_droid();
  glPopMatrix();

  glPushMatrix();
  glColor3d(1.0, 1.0, 1.0);
  glTranslated(15.0, 0.0, 0.0);
  drawEllipse(5.0, 10.0, 64);
  glPopMatrix();

  glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
	// Avoid division by 0
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

  identity(GL_PROJECTION);
	gluPerspective(45.0 /* angle of view */, (double) w / h /* aspect ratio */ , 1.0 /* near */, 100.0 /* far */);

  identity(GL_MODELVIEW);
}

// https://open.gl/transformations
void special(int key, int x, int y) {
  double camx = cam_x;
  double camy = cam_y;
  double camz = cam_z;
  switch (key) {
    case GLUT_KEY_LEFT:
      cam_x = camx * COS_ONE_STEP - camz * SIN_ONE_STEP;
      cam_z = camx * SIN_ONE_STEP + camz * COS_ONE_STEP;
      break;
    case GLUT_KEY_RIGHT:
      cam_x = camx * COS_ONE_STEP + camz * SIN_ONE_STEP;
      cam_z = -camx * SIN_ONE_STEP + camz * COS_ONE_STEP;
      break;
    case GLUT_KEY_UP:
      cam_y = camy * COS_ONE_STEP + camz * SIN_ONE_STEP;
      cam_z = -camy * SIN_ONE_STEP + camz * COS_ONE_STEP;
      break;
    case GLUT_KEY_DOWN:
      cam_y = camy * COS_ONE_STEP - camz * SIN_ONE_STEP;
      cam_z = camy * SIN_ONE_STEP + camz * COS_ONE_STEP;
      break;
  }
}

void init_gl(void) {
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

  glEnable(GL_NORMALIZE);

  glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

// void quadric_err(GLenum errcode) {
//   const GLubyte *estring = gluErrorString(errcode);
//   fprintf(stderr, "Quadric error: %s\n", estring);
//   exit(errcode);
// }

// http://www.glprogramming.com/red/chapter11.html#name2
int init_defquad(void) {
  defquad = gluNewQuadric();
  if (defquad == NULL) return -1;
  // GLU_ERROR is the only legal value for which
  // For GLU_ERROR, fn is called with one parameter, which is the error code.
  // gluErrorString() can be used to convert the error code into an ASCII string.
  // gluQuadricCallback(defquad, GLU_ERROR, quadric_err);

  // drawStyle controls the rendering style.
  // Legal values for drawStyle are GLU_POINT, GLU_LINE, GLU_SILHOUETTE, and GLU_FILL.
  gluQuadricDrawStyle(defquad, GLU_FILL);

  // orientation is either GLU_OUTSIDE (the default) or GLU_INSIDE,
  // which controls the direction in which normals are pointing.
  gluQuadricOrientation(defquad, GLU_OUTSIDE); // default

  // GLU_NONE means that no normals are generated and is intended for use without lighting.
  // GLU_FLAT generates one normal for each facet, which is often best for lighting with flat shading.
  // GLU_SMOOTH generates one normal for every vertex of the quadric, which is usually best for lighting with smooth shading.
  gluQuadricNormals(defquad, GLU_SMOOTH);

  // For the quadrics object qobj, textureCoords is either GL_FALSE (the default) or GL_TRUE.
  // If the value of textureCoords is GL_TRUE, then texture coordinates are generated for the quadrics object.
  // The manner in which the texture coordinates are generated varies, depending upon the type of quadrics object rendered.
  gluQuadricTexture (defquad, GL_FALSE);
  return 0;
}
