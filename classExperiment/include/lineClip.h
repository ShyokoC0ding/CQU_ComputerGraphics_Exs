//
// Created by 84151 on 2024/11/8.
//

#ifndef OPENGL_LINECLIP_H
#define OPENGL_LINECLIP_H
#include"GL/glut.h"
#include"GLFW/glfw3.h"

class wcPt2D {
public:
    GLfloat x, y;
};

const GLint winLeftBitCode   = 0x1;
const GLint winRightBitCode  = 0x2;
const GLint winBottomBitCode = 0x4;
const GLint winTopBitCode    = 0x8;

inline GLint inside(GLint code);
inline GLint myround(const GLfloat a);
inline GLint reject(GLint code1, GLint code2);
inline GLint accept(GLint code1, GLint code2);
GLubyte encode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax);
void swapPts(wcPt2D* p1, wcPt2D* p2);
void swapCode(GLubyte* c1, GLubyte* c2);
void lineClipCohSuth(wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2);


#endif //OPENGL_LINECLIP_H
