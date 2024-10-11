//
// Created by 84151 on 2024/10/2.
//

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include"GL/glut.h"
#include<GL/glaux.h>
#include "circle.h"

void DDA(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
void Bresenham(GLint x1, GLint y1, GLint x2, GLint y2);


//数值微分法
void DDA(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    float dx,dy;
    float step;
    dx = x2-x1; dy = y2-y1;

    if(fabs(dx)>fabs(dy))
        step=fabs(dx);
    else
        step=fabs(dy);

    float stepX = dx/step;
    float stepY = dy/step;

    glBegin(GL_POINTS);

    for(int i=0;i<(int)(fabs(dx));i++){
        glVertex2f(x1,int(y1+0.5));
        x1+=stepX;
        y1+=stepY;
    }

    glEnd();
}

//Bresenham算法 有问题
void Bresenham(GLint x1, GLint y1, GLint x2, GLint y2) {

    int dx, dy, p, length, temp;
    dx = x2-x1; dy = y2-y1;

    p = 2*dy-dx;


    if ( fabs(dx) < fabs(dy) )
    {
        length = fabs(dy);
        glBegin(GL_POINTS);
        glVertex2f(x1,y1);
        for(int i=0;i<length;i++){
            y1+=1;
            if(p>0){
                x1+=1;
                glVertex2f(x1,y1);
                p+=2*dx-2*dy;
            }
            else{
                glVertex2f(x1,y1);
                p+=2*dx;
            }
        }
        glEnd();
    }
    else
    {
        length = fabs(dx);
        glBegin(GL_POINTS);
        glVertex2f(x1,y1);
        for(int i =0; i<length;i++){
            x1+=1;
            if(p>0) {
                y1+=1;
                glVertex2f(x1,y1);
                p+=2*dy-2*dx;
            }
            else
            {
                glVertex2f(x1,y1);
                p+=2*dy;
            }
        }
        glEnd();
    }

//    glBegin(GL_POINTS);
//    glVertex2f(x1,y1);
//    for(int i =0; i< (int)(length);i++){
//        x1+=1;
//        if(p>0) {
//            y1 += 1;
//            glVertex2f(x1, y1);
//            p+=2*dy-2*dx;
//        }
//        else
//        {
//
//            glVertex2f(x1, y1);
//            p+=2*dy;
//        }
//    }
//    glEnd();

}

//void myDisplay(){
//    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(0.87,0.56,0.4);
//    glPointSize(3);
//    Bresenham(2,3,200,50);
//    glFlush();
//}

//void init(){
//    glClearColor(1.0,1.0,1.0,1.0);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0,600,0,500);
//}


//int main(int argc, char* argv[])
//{
//    glutInit(&argc,argv);
//    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
//    glutInitWindowPosition(300,100);
//    glutInitWindowSize(600,500);
//    glutCreateWindow("TEST DDA");
//
//    init();
//    glutDisplayFunc(myDisplay);
//    glutMainLoop();
//    return 0;
//}

