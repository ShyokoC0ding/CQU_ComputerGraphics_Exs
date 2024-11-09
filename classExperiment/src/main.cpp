//
// Created by 84151 on 2024/10/11.
//
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include"GL/glut.h"
#include<GL/glaux.h>
#include "Paint.h"
#include "circle.h"
#include "line.h"
#include "polygonScan.h"
#include "lineClip.h"

using namespace std;

void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);  // 清除颜色缓冲区
    glColor3f(0.87,0.56,0.4); // 设置颜色
    glPointSize(3); // 设置点大小

    /*-----画坐标轴-------*/
    drawAxis(-300,300,-250,250,10);

    /*-----Line DDA-------uncomment下列内容并点击运行------------*/
//    DDA(-10,10,-100,200);
//    DDA(10,-10,100,-200);
//    DDA(-10,10,-100,50);
//    DDA(10,-10,100,-50);
//    DDA(10,10,100,200);
//    DDA(-10,-10,-100,-200);
//    DDA(10,10,100,50);
//    DDA(-10,-10,-100,-50);
//    DDA(-150,0,-20,0);
//    DDA(150,0,20,0);
//    DDA(0,-150,0,-20);
//    DDA(0,150,0,20);



    /*-----Line Bresenham-------uncomment下列内容并点击运行------------*/
//    Bresenham(-10,10,-100,200);
//    Bresenham(10,-10,100,-200);
//    Bresenham(-10,10,-100,50);
//    Bresenham(10,-10,100,-50);
//    Bresenham(10,10,100,200);
//    Bresenham(-10,-10,-100,-200);
//    Bresenham(10,10,100,50);
//    Bresenham(-10,-10,-100,-50);
//    Bresenham(-150,0,-20,0);
//    Bresenham(150,0,20,0);
//    Bresenham(0,-150,0,-20);
//    Bresenham(0,150,0,20);


    /*-----Line centerPoint-------uncomment下列内容并点击运行------------*/
//    centerPoint(-10,10,-100,200);
//    centerPoint(10,-10,100,-200);
//    centerPoint(-10,10,-100,50);
//    centerPoint(10,-10,100,-50);
//    centerPoint(10,10,100,200);
//    centerPoint(-10,-10,-100,-200);
//    centerPoint(10,10,100,50);
//    centerPoint(-10,-10,-100,-50);
//    centerPoint(-150,0,-20,0);
//    centerPoint(150,0,20,0);
//    centerPoint(0,-150,0,-20);
//    centerPoint(0,150,0,20);

    /*-----circle centerPoint-------uncomment下列内容并点击运行------------*/
//    circle_centerPoint(100);


    /*-----ellipse centerPoint-------uncomment下列内容并点击运行------------*/
//    ellipse_centerPoint(250,175);


    /*-----扫描线填充多边形-------uncomment下列内容并点击运行------------*/
    //polygonScan();

    /*-----直线段裁剪-------uncomment下列内容并点击运行------------*/
//    wcPt2D p1,p2,winMin,winMax;
//    p1.x=-200; p1.y=-180;
//    p2.x=100; p2.y=110;
//    winMin.x=-100; winMin.y=-100;
//    winMax.x=100; winMax.y=100;
//    lineClipCohSuth(winMin,winMax,p1,p2);

    glFlush(); // 适用于较旧的OpenGL版本，保证之前的命令被立即执行

}

int main(int argc, char* argv[])
{
    // 初始化GLUT库，其参数是从程序main函数传递来的，用于处理命令行参数
    glutInit(&argc,argv);

    /* 设置显示模式，此处设置为：
     *  GLUT_RGB 使用RGB颜色模式
     *  GLUT_SINGLE 使用单缓冲窗口
     * */
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);

    // 设置OpenGL窗口在屏幕上的初始位置
    glutInitWindowPosition(300,100);
    // 设置窗口大小
    glutInitWindowSize(600,500);
    // 创建窗口
    glutCreateWindow("TEST");

    init();
    glutDisplayFunc(myDisplay);
    // 启动GLUT的事件处理循环，会持续运行，等待并处理窗口事件
    glutMainLoop();
    return 0;
}



