#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_POS_X 0
#define WINDOW_POS_Y 0
#define WINDOW_TITLE "Skating Droid"
#define CENTER_X 0.0
#define CENTER_Y 0.0
#define CENTER_Z 0.0
#define OBJ_SLICES 64
#define OBJ_STACKS 64
#define DROID_LEFT -1
#define DROID_RIGHT 1
#define DROID_HEIGHT 10.0

const double DROID_RADIUS = (DROID_HEIGHT / 2.0);
const double DROID_RATIO = DROID_RADIUS / 6.25;
const double DROID_ANT_LENGTH = (DROID_HEIGHT / 3.0);
const double DROID_ANT_RADIUS = (DROID_RADIUS / 20.0);
const double DROID_ARM_LENGTH = (DROID_HEIGHT / 2.0);
const double DROID_ARM_RADIUS = (DROID_RADIUS / 4.0);
const double DROID_LEG_LENGTH = (DROID_HEIGHT / 2.5);
const double DROID_LEG_RADIUS = DROID_ARM_RADIUS;
const GLubyte color_droid[] = {164, 199, 57};
const double PAN_STEP = 1.0;
const double ONE_STEP = 2 * M_PI / 180;
const double SIN_ONE_STEP = sin(ONE_STEP);
const double COS_ONE_STEP = cos(ONE_STEP);

void idle(void);
void display(void);
void reshape(GLsizei, GLsizei);
void keyboard(unsigned char, int, int);
void init_gl(void);
int init_defquad(void);
