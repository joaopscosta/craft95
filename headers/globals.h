#ifndef GLOBALS_H
#define GLOBALS_H

GLfloat cursorX = 0;
GLfloat cursorY = 0;
GLfloat cursorZ = 0;

GLfloat cameraX    = 45;
GLfloat cameraY    = 90;
//GLfloat cameraZ    = 0;
GLfloat cameraZoom = -3;

GLfloat redColor[3]      = {1, 0, 0};
GLfloat greenColor[3]    = {0, 1, 0};
GLfloat blueColor[3]     = {0, 0, 1};
GLfloat whiteColor[3]    = {1, 1, 1};
GLfloat magentaColor[3]  = {1, 0, 1};
GLfloat cyanColor[3]     = {0, 1, 1};
GLfloat yellowColor[3]   = {1, 1, 0};
GLfloat blackColor[3]    = {0, 0, 0};

GLfloat *currentColor = redColor;

struct cube {
    GLfloat x, y, z;
    GLfloat color[3];
    struct cube* next;
    struct cube* prev;
};

typedef struct cube Cube;

Cube* cubeListHead;

#endif /* GLOBALS_H */
