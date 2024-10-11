////
//// Created by 84151 on 2024/10/11.
////
//
//#include<stdio.h>
//#include<stdlib.h>
//#include <math.h>
//#include"GL/glut.h"
//#include<GL/glaux.h>
//#include "circle.h"
//#include "line.h"
//#include "Paint.h"
//
//void myDisplay(){
//    glClear(GL_COLOR_BUFFER_BIT);  // 清除颜色缓冲区
//    glColor3f(0.87,0.56,0.4); // 设置颜色
//    glPointSize(3); // 设置点大小
//    ellipse_centerPoint(250,175);
//    //Bresenham(10,20,100,200);
//    drawAxis(-300,300,-250,250,10);
//    /*   此行调用绘图算法   */
//    glFlush(); // 适用于较旧的OpenGL版本，保证之前的命令被立即执行
//
//}
//
//#include <GL/glut.h>
//
//void isplay(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
//    glFlush();
//}
//
//
//int main(int argc, char* argv[])
//{
//    // 初始化GLUT库，其参数是从程序main函数传递来的，用于处理命令行参数
//    glutInit(&argc,argv);
//
//    /* 设置显示模式，此处设置为：
//     *  GLUT_RGB 使用RGB颜色模式
//     *  GLUT_SINGLE 使用单缓冲窗口
//     * */
//    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
//
//    // 设置OpenGL窗口在屏幕上的初始位置
//    glutInitWindowPosition(300,100);
//    // 设置窗口大小
//    glutInitWindowSize(600,500);
//    // 创建窗口
//    glutCreateWindow("TEST");
//
//    init();
//    glutDisplayFunc(myDisplay);
//    // 启动GLUT的事件处理循环，会持续运行，等待并处理窗口事件
//    glutMainLoop();
//    return 0;
//}
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<GL/glut.h>
#include<GL/glaux.h>

const int n = 1000;
//修改const int n的值，观察当n=3,4,5,8,10,15,20,30,50等不同数值时输出的变化情况
const GLfloat R = 0.5f;
const GLfloat Pi = 3.1415926536;

void myDisplay(void)
{
    //画一个五角星
    GLfloat a = 1 / (2 - 2 * cos(72 * Pi / 180));
    GLfloat bx = a * cos(18 * Pi / 180);
    GLfloat by = a * sin(18 * Pi / 180);
    GLfloat cy = -a * cos(18 * Pi / 180);
    GLfloat
            PointA[2] = { 0, a },
            PointB[2] = { bx, by },
            PointC[2] = { 0.5, cy },
            PointD[2] = { -0.5, cy },
            PointE[2] = { -bx, by };

    glClear(GL_COLOR_BUFFER_BIT);
    // 按照A->C->E->B->D->A的顺序，可以一笔将五角星画出
    glBegin(GL_LINE_LOOP);
    glVertex2fv(PointA);
    glVertex2fv(PointC);
    glVertex2fv(PointE);
    glVertex2fv(PointB);
    glVertex2fv(PointD);
    glEnd();
    glFlush();
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    int cx = glutGet(GLUT_SCREEN_WIDTH);
    int cy = glutGet(GLUT_SCREEN_HEIGHT);//为了使窗口居中
    glutInitWindowPosition((cx - 400) / 2, (cy - 400) / 2);
    glutInitWindowSize(400, 400);
    glutCreateWindow("第二讲——画一个五角星");
    glutDisplayFunc(&myDisplay);
    glutMainLoop();
    return 0;
}


