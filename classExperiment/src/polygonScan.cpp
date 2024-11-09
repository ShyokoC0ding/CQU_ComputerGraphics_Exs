//
// Created by 84151 on 2024/11/8.
//

#include "polygonScan.h"
#include "Paint.h"
#include <vector>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
using namespace std;


/* 多边形的顶点集  */
vector<Point> vertices = { Point(20, 50), Point(20, 100), Point(90, 60),
                           Point(160, 110), Point(160, 40), Point(120, 20),
                           Point(70, 20)
};

void polygonScan()
{
    //计算最高点的y坐标
    int maxY = 0;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].y > maxY)
        {
            maxY = vertices[i].y;
        }
    }
    //初始化边表ET和活动边表AET
    Edge *ET[500];
    for (int i = 0; i < maxY; i++)
    {
        ET[i] = new Edge();
        ET[i]->next = nullptr;
    }
    Edge* AET = new Edge();
    AET->next = nullptr;

    //清空显示窗口并设置画点颜色为红色
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);

    //建立边表ET
    for (int i = 0; i < vertices.size(); i++)
    {
        //取出当前点1前后相邻的共4个点，点1与点2的连线作为本次循环处理的边，另外两个点点0和点3用于计算奇点
        int x0 = vertices[(i - 1 + vertices.size()) % vertices.size()].x;
        int x1 = vertices[i].x;
        int x2 = vertices[(i + 1) % vertices.size()].x;
        int x3 = vertices[(i + 2) % vertices.size()].x;
        int y0 = vertices[(i - 1 + vertices.size()) % vertices.size()].y;
        int y1 = vertices[i].y;
        int y2 = vertices[(i + 1) % vertices.size()].y;
        int y3 = vertices[(i + 2) % vertices.size()].y;
        //水平线直接舍弃
        if (y1 == y2)
            continue;
        //分别计算下端点y坐标、上端点y坐标、下端点x坐标和斜率倒数
        int ymin = y1 > y2 ? y2 : y1;
        int ymax = y1 > y2 ? y1 : y2;
        float x = y1 > y2 ? x2 : x1;
        float dx = (x1 - x2) * 1.0f / (y1 - y2);
        //奇点特殊处理，若点2->1->0的y坐标单调递减则y1为奇点，若点1->2->3的y坐标单调递减则y2为奇点
        if (((y1 < y2) && (y1 > y0)) || ((y2 < y1) && (y2 > y3)))
        {
            ymin++;
            x += dx;
        }
        //创建新边，插入边表ET
        Edge *p = new Edge();
        p->ymax = ymax;
        p->x = x;
        p->dx = dx;
        p->next = ET[ymin]->next;
        ET[ymin]->next = p;
    }

    //扫描线从下往上扫描，y坐标每次加1
    for (int i = 0; i < maxY; i++)
    {
        //取出ET中当前扫描行的所有边并按x的递增顺序（若x相等则按dx的递增顺序）插入AET
        while (ET[i]->next)
        {
            //取出ET中当前扫描行表头位置的边
            Edge *pInsert = ET[i]->next;
            Edge *p = AET;
            //在AET中搜索合适的插入位置
            while (p->next)
            {
                if (pInsert->x > p->next->x)
                {
                    p = p->next;
                    continue;
                }
                if (pInsert->x == p->next->x && pInsert->dx > p->next->dx)
                {
                    p = p->next;
                    continue;
                }
                //找到位置
                break;
            }
            //将pInsert从ET中删除，并插入AET的当前位置
            ET[i]->next = pInsert->next;
            pInsert->next = p->next;
            p->next = pInsert;
        }

        //AET中的边两两配对并填色
        Edge *p = AET;
        while (p->next && p->next->next)
        {
            for (int x = p->next->x; x < p->next->next->x; x++)
            {
                glVertex2i(x, i);
            }
            p = p->next->next;
        }

        //删除AET中满足y=ymax的边
        p = AET;
        while (p->next)
        {
            if (p->next->ymax == i)
            {
                Edge *pDelete = p->next;
                p->next = pDelete->next;
                pDelete->next = nullptr;
                delete pDelete;
            }
            else
            {
                p = p->next;
            }
        }

        //更新AET中边的x值，进入下一循环
        p = AET;
        while (p->next)
        {
            p->next->x += p->next->dx;
            p = p->next;
        }
    }
    glEnd();
    glFlush();

    // 释放边表和活动边表占用的内存
    for (int i = 0; i < maxY; i++)
    {
        Edge* ptr = ET[i];
        if (ptr != nullptr)
        {
            delete ptr;
            ptr = nullptr;
        }
    }
    Edge* p = AET;
    while (p)
    {
        Edge* tmp = p->next;
        delete p;
        p = tmp;
    }
}