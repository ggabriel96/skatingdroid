#include <stdio.h>
#include <GL/glut.h>
#include "skating.h"

GLuint display_list_head;

void identity(GLenum model) {
  glMatrixMode(model);
  glLoadIdentity();
}

void reshape(GLsizei w, GLsizei h) {
	// Avoid division by 0
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

  identity(GL_PROJECTION);
	gluPerspective(45.0 /* angle of view */, (double) w / h /* aspect ratio */ , 1.0 /* near */, 100.0 /* far */);

  identity(GL_MODELVIEW);
}

void idle(void) {
	glutPostRedisplay();
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

  glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void display(void) {
	identity(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gluLookAt(0.0, 30.0, 2.5 /* position*/,
            0.0, 0.0, 0.0 /* look at */,
            0.0, 1.0, 0.0 /* up vector */);

  glPushMatrix();
  glColor3d(0.5, 1.0, 1.0);
  glTranslated(-15.0, 0.0, 0.0);
  glutSolidSphere(5.0, OBJ_SLICES, OBJ_STACKS);
  glPopMatrix();

  glPushMatrix();
  glColor3d(1.0, 1.0, 0.5);
  glCallList(display_list_head);
  glPopMatrix();

  glPushMatrix();
  glColor3d(1.0, 0.5, 1.0);
  glTranslated(15, 0.0, 0.0);
  glutSolidSphere(5.0, OBJ_SLICES, OBJ_STACKS);
  glPopMatrix();

  glutSwapBuffers();
}

// void quadric_err(GLenum errcode) {
//   const GLubyte *estring = gluErrorString(errcode);
//   fprintf(stderr, "Quadric error: %s\n", estring);
//   exit(errcode);
// }

// http://www.glprogramming.com/red/chapter11.html#name2
int init_droid(void) {
  GLUquadricObj *qobj = NULL;
  display_list_head = glGenLists(1);
  qobj = gluNewQuadric();
  if (qobj == NULL) {
    fprintf(stderr, "Failed to initialize droid_body\n");
    return -1;
  }
  // GLU_ERROR is the only legal value for which
  // For GLU_ERROR, fn is called with one parameter, which is the error code.
  // gluErrorString() can be used to convert the error code into an ASCII string.
  // gluQuadricCallback(droid_body, GLU_ERROR, quadric_err);
  // drawStyle controls the rendering style.
  // Legal values for drawStyle are GLU_POINT, GLU_LINE, GLU_SILHOUETTE, and GLU_FILL.
  gluQuadricDrawStyle(qobj, GLU_FILL);
  // orientation is either GLU_OUTSIDE (the default) or GLU_INSIDE,
  // which controls the direction in which normals are pointing.
  gluQuadricOrientation(qobj, GLU_OUTSIDE); // default
  // GLU_NONE means that no normals are generated and is intended for use without lighting.
  // GLU_FLAT generates one normal for each facet, which is often best for lighting with flat shading.
  // GLU_SMOOTH generates one normal for every vertex of the quadric, which is usually best for lighting with smooth shading.
  gluQuadricNormals(qobj, GLU_SMOOTH);
  // For the quadrics object qobj, textureCoords is either GL_FALSE (the default) or GL_TRUE.
  // If the value of textureCoords is GL_TRUE, then texture coordinates are generated for the quadrics object.
  // The manner in which the texture coordinates are generated varies, depending upon the type of quadrics object rendered.
  gluQuadricTexture (qobj, GL_FALSE);
  // https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
  glNewList(display_list_head, GL_COMPILE);
  // Draws a cylinder oriented along the z axis, with the base of the cylinder at z = 0 and the top at z = height.
  // Like a sphere, the cylinder is subdivided around the z axis into a number of slices and along the z axis into
  // a number of stacks. baseRadius is the radius of the cylinder at z = 0. topRadius is the radius of the cylinder
  // at z = height. If topRadius is set to zero, then a cone is generated.
  // void gluCylinder (GLUquadricObj *qobj, GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);
  gluCylinder(qobj, 5.0, 5.0, 5.0, OBJ_SLICES, OBJ_STACKS);
  glEndList();
  return 0;
}
