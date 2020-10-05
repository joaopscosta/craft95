#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL\glut.h>
#include "headers\func.h"
#include "headers\globals.h"

inline void reposition(){
    glLoadIdentity();
    glTranslatef(0, 0, cameraZoom); // DISTANCE
    glRotatef(cameraX, 1, 0, 0); // rotate x axis
    glRotatef(cameraY, 0, 1, 0); // rotate y axis
    //glRotatef(cameraZ, 0, 0, 1); // rotate z axis
}

void getCustomColor(){
    GLfloat r, g, b;
    unsigned int color;
    int c;
    printf("Enter RGB color.\n#");
    scanf("%x", &color);
    r = (color>>16 & 0xFF)/255.0; g = (color>>8 & 0xFF)/255.0; b = (color & 0xFF)/255.0;
    currentColor[0] = r; currentColor[1] = g; currentColor[2] = b;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    reposition();
    drawGrid();
    alignToGrid();
    drawCubes(cubeListHead);
    reposition();
    alignToGrid();

    // DRAW CURSOR
    drawCursor();

    glutSwapBuffers();
}

void init(){
    // lighting stuff
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 8.0, 0.0, 16.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 1);
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2, 2, -1.5, 1.5, 1, 40);
    glMatrixMode(GL_MODELVIEW);
    reposition();

    cubeListHead  = NULL;
}

inline void drawCursor(){
    glTranslatef(cursorX, cursorY, cursorZ);
    glColor3fv(currentColor);
    glutSolidCube(0.50);
}

inline void drawGrid(){
    GLfloat i;
    glColor3fv(whiteColor);
    glBegin(GL_LINES);
    for(i = -8.5; i <= 8.5; i += 0.5){
        glVertex3f(i, cursorY, 8.5); glVertex3f(i, cursorY, -8.5);
        glVertex3f(8.5, cursorY, i), glVertex3f(-8.5, cursorY, i);
    }
    glEnd();
}

void addCube(GLfloat *color){
    if(cubeListHead != NULL) {
        Cube* tempCube = (Cube*) malloc(sizeof(Cube));
        tempCube->x = cursorX; tempCube->y = cursorY; tempCube->z = cursorZ;
        memcpy(tempCube->color, currentColor, 3*sizeof(GLfloat));
        cubeListHead->prev = tempCube;
        tempCube->next = cubeListHead;
        tempCube->prev = NULL;
        cubeListHead = tempCube;
    } else {
        cubeListHead = (Cube*) malloc(sizeof(Cube));
        memcpy(cubeListHead->color, currentColor, 3*sizeof(GLfloat));
        cubeListHead->x = cursorX; cubeListHead->y = cursorY; cubeListHead->z = cursorZ;
        cubeListHead->prev = NULL; cubeListHead->next = NULL;
    }
}

void drawCubes(Cube* cubeHead){
    while(cubeHead != NULL){
        reposition(); alignToGrid();
        glTranslatef(cubeHead->x, cubeHead->y, cubeHead->z);
        glColor3fv(cubeHead->color);
        glutSolidCube(0.5);
        cubeHead = cubeHead->next;
    }
}

void removeCube(Cube* cubeHead){
    while(cubeHead != NULL){
        if(cubeHead->x == cursorX && cubeHead->y == cursorY && cubeHead->z == cursorZ){
            if(cubeHead->prev == NULL){
                if(cubeHead->next == NULL){
                    free(cubeHead); cubeListHead = NULL;
                    return;
                } else {
                    cubeListHead = cubeHead->next;
                    cubeListHead->prev = NULL;
                    free(cubeHead);
                    return;
                }
            } else { 
                if(cubeHead->next == NULL){
                    cubeHead->prev->next = NULL;
                    free(cubeHead);
                    return;
                } else { 
                    cubeHead->prev->next = cubeHead->next;
                    cubeHead->next->prev = cubeHead->prev;
                    free(cubeHead);
                    return;
                }
            }
            return;
        } else {
            cubeHead = cubeHead->next;
        }
    }
}

inline void alignToGrid(){
    glTranslatef(0.25, 0.25, 0.25);
}

void keyboardHandler(unsigned char key, int x, int y){
    switch(key){
        // movement
        case 'e': cursorY+=0.5; break;
        case 'q': cursorY-=0.5; break;
        case 'd': cursorZ+=0.5; break;
        case 'a': cursorZ-=0.5; break;
        case 'w': cursorX+=0.5; break;
        case 's': cursorX-=0.5; break;

        // placement
        case ' ': addCube(currentColor);    break;
        case 'x': removeCube(cubeListHead); break;

        // colors
        case '1': currentColor = redColor;     break;
        case '2': currentColor = greenColor;   break;
        case '3': currentColor = blueColor;    break;
        case '4': currentColor = whiteColor;   break;
        case '5': currentColor = magentaColor; break;
        case '6': currentColor = cyanColor;    break;
        case '7': currentColor = yellowColor;  break;
        case '8': currentColor = blackColor;   break;
    }
    glutPostRedisplay();
}

void specialKeyHandler(int key, int x, int y){
    switch(key){
        // camera movement xy
        case GLUT_KEY_UP:    cameraX++; break;
        case GLUT_KEY_DOWN:  cameraX--; break;
        case GLUT_KEY_LEFT:  cameraY++; break;
        case GLUT_KEY_RIGHT: cameraY--; break;

        // zoom
        case GLUT_KEY_PAGE_UP:   cameraZoom+=0.5; break;
        case GLUT_KEY_PAGE_DOWN: cameraZoom-=0.5; break;

        // custom color
        case GLUT_KEY_F1: getCustomColor(); break;

        // save/load
        case GLUT_KEY_F2: saveWorld(cubeListHead); break;
        case GLUT_KEY_F3: loadWorld(); break;
    }
    glutPostRedisplay();
}

void saveWorld(Cube* cubeHead){
    char fileName[255], fileName_s[255];
    FILE *fp;
    fprintf(stderr, "Enter a name for the savefile: ");
    fgets(fileName_s, 254, stdin);
    sscanf(fileName_s, "%s", fileName);
    if((fp = fopen(fileName, "wb"))){
        while(cubeHead != NULL){
            fwrite(cubeHead, 1, sizeof(Cube), fp);
            cubeHead = cubeHead->next;
        }
        fclose(fp);
        fprintf(stderr, "File %s created.\n", fileName);
    } else {
        fprintf(stderr, "Error creating file %s\n", fileName);
    }
}

void loadWorld(){
    char fileName[255], fileName_s[255];
    Cube* tempCube = (Cube*) malloc(sizeof(Cube));
    FILE *fp;
    fprintf(stderr, "Enter filename to load: ");
    fgets(fileName_s, 254, stdin);
    sscanf(fileName_s, "%s", fileName);
    if((fp = fopen(fileName, "rb"))){
        fprintf(stderr, "Loading file %s...\n", fileName);
        if(cubeListHead != NULL){
            free(cubeListHead);
            cubeListHead = NULL;
        }
        while(!feof(fp)){
            fread(tempCube, 1, sizeof(Cube), fp);
            cursorX = tempCube->x; cursorY = tempCube->y; cursorZ = tempCube->z;
            currentColor = tempCube->color;
            addCube(tempCube->color);
        }
        free(tempCube);
        fprintf(stderr, "Done.\n");
        fclose(fp);
        glutPostRedisplay();
        
    } else {
        fprintf(stderr, "Error opening file %s.\n", fileName);
    }
}
