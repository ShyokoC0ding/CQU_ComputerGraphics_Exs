//
// Created by 84151 on 2024/10/2.
//

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include"GL/glut.h"
#include<GL/glaux.h>
#include "circle.h"
#include<iostream>
using std::cout;
using std::endl;


void DDA(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
void Bresenham(GLint x1, GLint y1, GLint x2, GLint y2);
void centerPoint(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);


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
    if(fabs(dx)==0) {
        for (int i = 0; i < (int) (fabs(dy)); i++) {
            glVertex2f(x1, int(y1 + 0.5));
            x1 += stepX;
            y1 += stepY;
        }
    }

    glEnd();
}

//Bresenham算法
void Bresenham(GLint x1, GLint y1, GLint x2, GLint y2) {
    glBegin(GL_POINTS);
    int dx, dy, p, length, temp,step;
//    if(fabs(dx)>fabs(dy))
//        step=fabs(dx);
//    else
//        step=fabs(dy);
//    float stepX = dx/step;
//    float stepY = dy/step;
    dx = x2 - x1;
    dy = y2 - y1;




    if (fabs(dx) == 0) {
        float stepY = (y2-y1)/fabs(dy);
        for (int i = 0; i < (int) (fabs(dy)); i++) {
            glVertex2f(x1, int(y1 + 0.5));
            y1 += stepY;
        }
    }   // 垂直线

    if (fabs(dy) == 0) {
        float stepX = (x2-x1)/fabs(dx);
        for (int i = 0; i < (int) (fabs(dx)); i++) {
            glVertex2f(x1, int(y1 + 0.5));
            x1 += stepX;
        }
    }   // 水平线


    if ( fabs(dx) < fabs(dy))
    {
        if(y1<y2) {
            if(x1<x2) {
                p = 2 * dx - dy;
                length = fabs(dy);
                glVertex2f(x1, y1);
                for (int i = 0; i < length; i++) {
                    y1 += 1;
                    if (p > 0) {
                        x1 += 1;
                        glVertex2f(x1, y1);
                        p += 2 * dx - 2 * dy;
                    } else {
                        glVertex2f(x1, y1);
                        p += 2 * dx;
                    }
                }
            }        //  1b
            else if(x1>x2){
                p = -2 * dx - dy;
                length = fabs(dy);
                glVertex2f(x1, y1);
                for (int i = 0; i < length; i++) {
                    y1 += 1;
                    if (p > 0) {
                        x1 -= 1;
                        glVertex2f(x1, y1);
                        p += -2 * dx - 2 * dy;
                    } else {
                        glVertex2f(x1, y1);
                        p += -2 * dx;
                    }
                }
            }    //  2b
        }
        else if(y1>y2){
            if(x1>x2) {
                p = -2 * dx + dy;
                length = fabs(dy);
                glVertex2f(x2, y2);
                for (int i = 0; i < length; i++) {
                    y2 += 1;
                    if (p > 0) {
                        x2 += 1;
                        glVertex2f(x2, y2);
                        p += -2 * dx + 2 * dy;
                    } else {
                        glVertex2f(x2, y2);
                        p += -2 * dx;
                    }
                }
            }        //  3b
            else if(x1<x2){
                p = 2 * dx + dy;
                length = fabs(dy);
                glVertex2f(x2, y2);
                for (int i = 0; i < length; i++) {
                    y2 += 1;
                    if (p > 0) {
                        x2 -= 1;
                        glVertex2f(x2, y2);
                        p += 2 * dx + 2 * dy;
                    } else {
                        glVertex2f(x2, y2);
                        p += 2 * dx;
                    }
                }
            }    //  4b
        }
    }
    else if(fabs(dx) > fabs(dy) && fabs(dy) != 0)
    {
        if(x1<x2) {
            if(y1<y2) {
                p = 2 * dy - dx;
                length = fabs(dx);
                glVertex2f(x1, y1);
                for (int i = 0; i < length; i++) {
                    x1 += 1;
                    //x1+=stepX;
                    if (p > 0) {
                        y1 += 1;
                        //y1+=stepY;
                        glVertex2f(x1, y1);
                        p += 2 * dy - 2 * dx;
                    } else {
                        glVertex2f(x1, y1);
                        p += 2 * dy;
                    }
                }
            }       //   1a
            else if(y1>y2){
                p = -2 * dy - dx;
                length = fabs(dx);
                glVertex2f(x1, y1);
                for (int i = 0; i < length; i++) {
                    x1 += 1;
                    //x1+=stepX;
                    if (p > 0) {
                        y1 -= 1;
                        //y1+=stepY;
                        glVertex2f(x1, y1);
                        p += -2 * dy - 2 * dx;
                    } else {
                        glVertex2f(x1, y1);
                        p += -2 * dy;
                    }
                }
            }   //   4a
        }
        else if(x1>x2){
            if(y1<y2) {
                p = 2 * dy + dx;
                length = fabs(dx);
                glVertex2f(x1, y1);
                for (int i = 0; i < length; i++) {
                    x1 -= 1;
                    if (p > 0) {
                        y1 += 1;
                        glVertex2f(x1, y1);
                        p += 2 * dy + 2 * dx;
                    } else {
                        glVertex2f(x1, y1);
                        p += 2 * dy;
                    }
                }
            }       //   2a
            else if(y1>y2){
                p = -2 * dy + dx;
                length = fabs(dx);
                glVertex2f(x1, y1);
                for (int i = 0; i < length; i++) {
                    x1 -= 1;
                    if (p > 0) {
                        y1 -= 1;
                        glVertex2f(x1, y1);
                        p += -2 * dy + 2 * dx;
                    } else {
                        glVertex2f(x1, y1);
                        p += -2 * dy;
                    }
                }
            }   //   3a
        }
    }

    glEnd();
}

//中点法
void centerPoint(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){
    float dx,dy;
    float y_hori; // choose horizontal point
    float y_up;   // choose upper point
    dx=x2-x1;
    dy=y2-y1;

    glBegin(GL_POINTS);

    glVertex2f(x1,y1);

    if (fabs(dx) == 0) {
        float stepY = (y2-y1)/fabs(dy);
        for (int i = 0; i < (int) (fabs(dy)); i++) {
            glVertex2f(x1, int(y1 + 0.5));
            y1 += stepY;
        }
    }   // 垂直线

    if (fabs(dy) == 0) {
        float stepX = (x2-x1)/fabs(dx);
        for (int i = 0; i < (int) (fabs(dx)); i++) {
            glVertex2f(x1, int(y1 + 0.5));
            x1 += stepX;
        }
    }   // 水平线

    /*----1a----*/
    if( fabs(dx)>fabs(dy) && x1<x2 && y1<y2 && dy!=0){
        float k = dy/dx;
        float intersec = y1+k*1.0;
        for(int i =0; i<fabs(dx);i++) {
            x1+=1;
            if (intersec > (y1 + 0.5)) { y1+=1; intersec=y1; glVertex2f(x1,y1); }
            if (intersec < (y1 + 0.5)) { intersec+=k; glVertex2f(x1,y1); }
        }
    }
    /*----1b----*/
    else if( fabs(dx)<fabs(dy) && x1<x2 && y1<y2 && dx!=0){
        float k = dx/dy;
        float intersec = x1+k*1.0;
        for(int i =0; i<fabs(dy);i++) {
            y1+=1;
            if (intersec > (x1 + 0.5)) { x1+=1; intersec=x1; glVertex2f(x1,y1); }
            if (intersec < (x1 + 0.5)) { intersec+=k; glVertex2f(x1,y1); }
        }
    }
    /*----2b----*/
    else if( fabs(dx)<fabs(dy) && x1>x2 && y1<y2 && dx!=0){
        float k = -dx/dy;
        float intersec = x1-k*1.0;
        for(int i =0; i<fabs(dy);i++) {
            y1+=1;
            if (intersec > (x1 + 0.5)) { x1-=1; intersec=x1; glVertex2f(x1,y1); }
            if (intersec < (x1 + 0.5)) { intersec+=k; glVertex2f(x1,y1); }
        }
    }
    /*----2a----*/
    else if( fabs(dx)>fabs(dy) && x1>x2 && y1<y2 && dy!=0){
        float k = -dy/dx;
        float intersec = y1+k*1.0;
        for(int i =0; i<fabs(dx);i++) {
            x1-=1;
            if (intersec > (y1 + 0.5)) { y1+=1; intersec=y1; glVertex2f(x1,y1); }
            if (intersec < (y1 + 0.5)) { intersec+=k; glVertex2f(x1,y1); }
        }
    }
    /*----3a----*/
    else if( fabs(dx)>fabs(dy) && x1>x2 && y1>y2 && dy!=0){
        float k = dy/dx;
        float intersec = y1-k*1.0;
        for(int i =0; i<fabs(dx);i++) {
            x1-=1;
            if (intersec > (y1 + 0.5)) { y1-=1; intersec=y1; glVertex2f(x1,y1); }
            if (intersec < (y1 + 0.5)) { intersec+=k; glVertex2f(x1,y1); }
        }
    }
    /*----3b----*/
    else if( fabs(dx)<fabs(dy) && x1>x2 && y1>y2 && dx!=0){
        float k = dx/dy;
        float intersec = x1-k*1.0;
        for(int i =0; i<fabs(dy);i++) {
            y1-=1;
            if (intersec > (x1 + 0.5)) { x1-=1; intersec=x1; glVertex2f(x1,y1); }
            if (intersec < (x1 + 0.5)) { intersec+=k; glVertex2f(x1,y1); }
        }
    }
    /*----4b----*/
    else if( fabs(dx)<fabs(dy) && x1<x2 && y1>y2 && dx!=0){
        float k = -dx/dy;
        float intersec = x1+k*1.0;
        for(int i =0; i<fabs(dy);i++) {
            y1-=1;
            if (intersec > (x1 + 0.5)) { x1+=1; intersec=x1; glVertex2f(x1,y1); }
            if (intersec < (x1 + 0.5)) { intersec+=k; glVertex2f(x1,y1); }
        }
    }
    /*----4a----*/
    else if( fabs(dx)>fabs(dy) && x1<x2 && y1>y2 && dx!=0){
        float k = -dy/dx;
        float intersec = y1+k*1.0;
        for(int i =0; i<fabs(dx);i++) {
            x1+=1;
            if (intersec > (y1 + 0.5)) { y1-=1; intersec=y1; glVertex2f(x1,y1); }
            if (intersec < (y1 + 0.5)) { intersec+=k; glVertex2f(x1,y1); }
        }
    }

    glEnd();
}


