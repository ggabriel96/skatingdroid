#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_POS_X 0
#define WINDOW_POS_Y 0
#define WINDOW_TITLE "Skating Droid"
#define DEF_CAM_X 0.0
#define DEF_CAM_Y 0.0
#define DEF_CAM_Z 35.0
#define OBJ_SLICES 64
#define OBJ_STACKS 64
#define DROID_LEFT -1
#define DROID_RIGHT 1
#define DROID_HEIGHT 10.0
#define SKATE_FRONT 1
#define SKATE_BACK -1
#define SKATE_SIZE DROID_HEIGHT

const double PAN_STEP = 1.0;
const double ONE_STEP = 2 * M_PI / 180;
const double SIN_ONE_STEP = sin(ONE_STEP);
const double COS_ONE_STEP = cos(ONE_STEP);

const GLubyte color_droid[] = {164, 199, 57};
const GLubyte color_skate[] = {102, 51, 0};
const GLubyte color_skate_axis[] = {129, 133, 140};
const GLubyte color_skate_wheel[] = {40, 43, 42};

const double DROID_RADIUS = DROID_HEIGHT / 2.0;
const double DROID_RATIO = DROID_RADIUS / 6.25;
const double DROID_ANT_LENGTH = DROID_HEIGHT / 3.0;
const double DROID_ANT_RADIUS = DROID_RADIUS / 20.0;
const double DROID_ARM_LENGTH = DROID_HEIGHT / 2.0;
const double DROID_ARM_RADIUS = DROID_RADIUS / 4.0;
const double DROID_LEG_LENGTH = DROID_HEIGHT / 2.5;
const double DROID_LEG_RADIUS = DROID_ARM_RADIUS;

const double SKATE_RADIUS = SKATE_SIZE / 1.5;
const double SKATE_SCALE_X = SKATE_SIZE / 13.0;
const double SKATE_SCALE_Y = SKATE_SIZE / 100.0;
const double SKATE_SCALE_Z = SKATE_SIZE / 6.5;
const double SKATE_AXIS_RADIUS = SKATE_SIZE / 30.0;
const double SKATE_AXIS_LENGTH = SKATE_RADIUS;
const double SKATE_WHEEL_RADIUS = SKATE_SIZE / 20.0;
const double SKATE_WHEEL_SCALE_X = SKATE_SIZE / 14.0;
const double SKATE_WHEEL_SCALE_Y = SKATE_SIZE / 8.0;
const double SKATE_WHEEL_SCALE_Z = SKATE_SIZE / 8.0;

void idle(void);
void display(void);
void reshape(GLsizei, GLsizei);
void keyboard(unsigned char, int, int);
void init_gl(void);
int init_defquad(void);
