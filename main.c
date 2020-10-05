#include <stdlib.h>
#include <GL\glut.h>
#include "headers\func.h"

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Craft '95");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(specialKeyHandler);
    init();
    glutMainLoop();
    return (0);
}
