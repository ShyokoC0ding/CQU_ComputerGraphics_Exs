// Created by 84151 on 2024/9/29.

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include"GL/glut.h"
#include<GL/glaux.h>
#include<iostream>
#include "line.h"

void circle_symmetryPaint(int x, int y);
void ellipse_symmetryPaint(int x, int y);
void circle_centerPoint(int r);
void ellipse_centerPoint(int a, int b);

/*
 * 绘图过程：
 * glBegin(GL_POINTS)
 * ...
 * glVertex2f(x_input,y_input)
 * ...
 * glEnd
 *
 * */

/*
 * glBegin(Glenum mode);
 * 参数mode制定了图元类型，即 决定了OpenGL如何解释顶点数据来绘制图形，常用的图元类型：
 * GL_POINTS 把每个顶点作为一个点来画，N个点就是 画N个点
 * GL_LINES 把每两个顶点作为一条独立的线段来画，N个点就是 画N/2条线段
 * */

void circle_symmetryPaint(int x, int y){
    /*
     * 利用圆的八对称性，画八个点
     * */
    glVertex2i(x,y);glVertex2i(y,x);
    glVertex2i(-x,y);glVertex2i(y,-x);
    glVertex2i(x,-y);glVertex2i(-y,x);
    glVertex2i(-x,-y);glVertex2i(-y,-x);
}


void ellipse_symmetryPaint(int x, int y){
    /*
     * 利用椭圆的对称性，画四个点，分别在四个象限
     * */
    glVertex2i(x,y);glVertex2i(-x,y);
    glVertex2i(x,-y);glVertex2i(-x,-y);
}


void circle_centerPoint(int r){
    /*
     * 圆对称性极好，画点只需考虑x>0,y>0,x<y的情况,
     * 然后用对称性画出整圆
     * */
    GLint x,y,d;
    x = 0; y = r;
    d = 1-r;
    glBegin(GL_POINTS);
    circle_symmetryPaint(x,y);
    while(x<=y) {
        circle_symmetryPaint(x,y);
        if (d < 0) { d+=2*x+3;}
        else { d+=2*(x-y)+5; y--; }
        x++;
    }
    glEnd();
}


void ellipse_centerPoint(int a, int b) {

    /*
     * 由于椭圆的对称性，只需画出第一象限部分，即可补足全部椭圆
     * 变量说明：
     *    x,y: 绘制点，初始为椭圆的(0,b)
     *    a2,b2: 代表a的平方，b的平方
     *        根据数学推导，当椭圆上一点的斜率小于-1时, 每一步递增的变量应该从x更换为y,
     *        前后两个阶段需要不同的d作为判别标准
     *    d1: 斜率大于-1的判别式
     *    d2: 斜率小于-1的判别式
     */
    GLint x, y, a2, b2;
    GLfloat d1, d2;
    x = 0;
    y = b;
    a2 = a * a;
    b2 = b * b;
    d1 = b2 + a2 * (-b + 0.25); // 设置d1初值
    glBegin(GL_POINTS);
    ellipse_symmetryPaint(x, y);
    while (b2 * x <= a2 * y) {
        ellipse_symmetryPaint(x, y);
        if (d1 < 0) { d1 += b2*(2*x+3); }
        else {  d1 += b2*(2*x+3)+a2*(-2*y+2);
            y--;
        }
        x++;
    }
    /* while(b2*x<=a2*y) */
    d2 = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2; // 设置d2初值
    while (y>=0) {
        ellipse_symmetryPaint(x,y);
        if (d2 > 0) { d2 += a2*(-2*y+3);  }
        else { d2 += b2*(2*x+2)+a2*(-2*y+3);
            x++; }
        y--;
    }
    glEnd();
}




