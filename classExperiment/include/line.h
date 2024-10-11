//
// Created by 84151 on 2024/10/2.
//

#ifndef OPENGL_LINE_H
#define OPENGL_LINE_H
#include <math.h>
#include"GL/glut.h"
#include<GL/glaux.h>

void DDA(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
void Bresenham(GLint x1, GLint y1, GLint x2, GLint y2);

#endif //OPENGL_LINE_H
