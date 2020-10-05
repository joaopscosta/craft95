#ifndef FUNC_H
#define FUNC_H

       void display();
       void init();
inline void reposition();
inline void drawGrid();
inline void drawCursor();
inline void alignToGrid();
       void getCustomColor();
       void addCube(GLfloat*); // xyz
       void removeCube(struct cube*);
       void drawCubes(struct cube*);
       void keyboardHandler(unsigned char, int, int); // key x y
       void specialKeyHandler(int, int, int); // key x y
       void saveWorld(struct cube*);
       void loadWorld();

#endif /* FUNC_H */
