#include <math.h>

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480
#define WINDOW_POS_X 0
#define WINDOW_POS_Y 0
#define WINDOW_TITLE "Skating Droid"
#define TARGET_FPS 30.0
#define DEF_CAM_X 0.0
#define DEF_CAM_Y 0.0
#define DEF_CAM_Z 100.0
#define PERSPECTIVE_AOV 45.0
#define PERSPECTIVE_NEAR 0.1
#define PERSPECTIVE_FAR 200.0
#define OBJ_SLICES 64
#define OBJ_STACKS 64
#define DROID_LEFT -1
#define DROID_RIGHT 1
#define DROID_HEIGHT 10.0
#define DROID_SKATING_BODY_COUNT 2
#define SKATE_LEFT -1
#define SKATE_RIGHT 1
#define SKATE_FRONT 1
#define SKATE_BACK -1
#define SKATE_SIZE DROID_HEIGHT
#define SKATE_WHEEL_PARTS 6

const double PAN_STEP = 1.0;
const double ONE_STEP =  M_PI / 260.0;
const double SIN_ONE_STEP = sin(ONE_STEP);
const double COS_ONE_STEP = cos(ONE_STEP);

const GLubyte color_droid[] = {164, 199, 57};
const GLubyte color_droid_eyes[] = {255, 255, 255};
const GLubyte color_skate[] = {102, 51, 0};
const GLubyte color_skate_axis[] = {129, 133, 140};
const GLubyte color_skate_wheel[] = {40, 43, 42};
const GLubyte color_skate_spoiler[] = {205, 33, 42};
const GLubyte color_ground[] = {155, 50, 50};

const double DROID_RADIUS = DROID_HEIGHT / 2.0;
const double DROID_RATIO = DROID_RADIUS / 6.25;
const double DROID_ANT_LENGTH = DROID_HEIGHT / 4.5;
const double DROID_ANT_RADIUS = DROID_RADIUS / 20.0;
const double DROID_EYE_RADIUS = DROID_RADIUS / 10.0;
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
const double SKATE_WHEEL_SCALE_X = SKATE_SIZE / 24.0;
const double SKATE_WHEEL_SCALE_Y = SKATE_SIZE / 8.0;
const double SKATE_WHEEL_SCALE_Z = SKATE_SIZE / 14.0;
const double SKATE_SPOIL_RADIUS_IN = SKATE_SIZE / 3.0;
const double SKATE_SPOIL_RADIUS_OUT = 1.5 * SKATE_SPOIL_RADIUS_IN;
const double SKATE_SPOIL_ANGLE = 45.0;
const double SKATE_WHEEL_OFFSET = 180.0 / SKATE_WHEEL_PARTS;

const double DROID_SKATING_VERT_SPEED = 0.04;
const double DROID_SKATING_FWD_SPEED = 0.547;
const double DROID_SKATING_BWD_SPEED = 0.4;
const double DROID_SKATING_MOVEMENT_SPEED = 0.75;
const double DROID_SKATING_DELTA = (SKATE_RADIUS * SKATE_SCALE_Y) + (SKATE_AXIS_RADIUS) + (2 * SKATE_WHEEL_RADIUS * SKATE_WHEEL_SCALE_Y);

const double SKATE_WHEEL_SPEED = 4.0;

const double GROUND_RADIUS = 10.0 * DROID_RADIUS;

void idle(int);
void display(void);
void reshape(GLsizei, GLsizei);
void keyboard(unsigned char, int, int);
void init_gl(void);
int init_defquad(void);
