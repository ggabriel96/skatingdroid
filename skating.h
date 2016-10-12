#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_POS_X 0
#define WINDOW_POS_Y 0
#define WINDOW_TITLE "Skating Droid"
#define OBJ_SLICES 64
#define OBJ_STACKS 64

typedef struct Color {
  double red, green, blue;
  Color(): red(0.0), green(0.0), blue(0.0) {}
  Color(double _red, double _green, double _blue): red(_red), green(_green), blue(_blue) {}
} color_t;

void identity(GLenum);
void reshape(GLsizei, GLsizei);
void idle(void);
void init_gl(void);
void display(void);
int init_droid(void);
