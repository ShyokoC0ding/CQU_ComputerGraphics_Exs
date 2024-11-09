//
// Created by 84151 on 2024/10/2.
//
#include<GL/glaux.h>
#include<iostream>

/*---------Prototype---------*/
void init();
void drawAxis(float minX, float maxX, float minY, float maxY, int numLines);



void drawAxis(float minX, float maxX, float minY, float maxY, int numLines){

    /*
            parameter : ......
            return : ......
            This function is to .....
    */

    glBegin(GL_LINES);
    for (int i = 0; i <= numLines; ++i) {
        float y = minY + (maxY - minY) * i / numLines;
        glVertex2f(minX, y);
        glVertex2f(maxX, y);
    }

    // 绘制平行于Y轴的网格线
    for (int i = 0; i <= numLines; ++i) {
        float x = minX + (maxX - minX) * i / numLines;
        glVertex2f(x, minY);
        glVertex2f(x, maxY);
    }

    glEnd();

}

void init(){
    // 设置背景色 参数依次为 Red,Green,Blue,alpha(透明度)
    glClearColor(1.0,1.0,1.0,1.0);
    // 设置当前矩阵模式为投影矩阵
    glMatrixMode(GL_PROJECTION);
    // 将当前矩阵重置为单位矩阵
    glLoadIdentity();
    /* 定义一个正交投影矩阵，并将其加载到当前选定的矩阵。正交投影不会改变物体在屏幕上的相对大小,
     * 同时也设置了横纵坐标范围
    */
    gluOrtho2D(-300,300,-250,250);
}