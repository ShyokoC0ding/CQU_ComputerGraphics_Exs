//
// Created by 84151 on 2024/11/8.
//

#include "lineClip.h"
#include "Paint.h"
#include"GL/glut.h"
#include"GLFW/glfw3.h"
#include"line.h"


inline GLint myround(const GLfloat a){
    return (GLint)(a+0.5);
}

// 根据区域码判断裁剪点是否位于裁剪矩形内
// 返回值设置成bool 更合适
inline GLint inside(GLint code)
{
    return (GLint)(!code);
}

// 判断2个区域码是否位于裁剪矩形外
inline GLint reject(GLint code1, GLint code2)
{
    return code1 & code2;
}

// 判断2个区域码是否位于裁剪矩形内
inline GLint accept(GLint code1, GLint code2)
{
    return (GLint)!(code1 | code2);
}

// 计算裁剪点pt的区域码
// winMin, winMax包含裁剪区域信息
GLubyte encode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax)
{
    GLubyte code = 0x00;

    if (pt.x < winMin.x)
        code = code | winLeftBitCode;
    if (pt.x > winMax.x)
        code = code | winRightBitCode;
    if (pt.y < winMin.y)
        code = code | winBottomBitCode;
    if (pt.y > winMax.y)
        code = code | winTopBitCode;

    return code;
}

void swapPts(wcPt2D* p1, wcPt2D* p2)
{
    wcPt2D tmp;

    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void swapCode(GLubyte* c1, GLubyte* c2)
{
    GLubyte tmp;

    tmp = *c1;
    *c1 = *c2;
    *c2 = tmp;
}

void lineClipCohSuth(wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2)
{
    GLubyte code1, code2;
    GLboolean done = false, plotLine = false;
    GLfloat m = 0.0;

    while (!done) {
        // 为线段2端点建立区域码
        code1 = encode(p1, winMin, winMax);
        code2 = encode(p2, winMin, winMax);

        if (accept(code1, code2)) { // 线段在矩形内
            done = true;
            plotLine = true;
        }
        else if (reject(code1, code2)) { // 线段在矩形外
            done = true;
        }
        else { // 线段与矩形相交或在矩形外, 需进一步测试
            /* Label the endpoint outside the display window as p1. */
            if (inside(code1)) { // 确保在边界外的点是p1, 那么在边界内的是p2
                swapPts(&p1, &p2);
                swapCode(&code1, &code2);
            }

            /* Use slope m to find line-clipEdge intersection. */
            if (p2.x != p1.x) {
                m = (p2.y - p1.y) / (p2.x - p1.x); // 斜率
            }

            // 按左->右->下->上的顺序, 测试边界是否裁剪后线段相交
            if (code1 & winLeftBitCode) { // 与左边界相交, 更新p1到左边界
                // 与左边界相交, 则斜率存在
                p1.y += (winMin.x - p1.x) * m; // y - y0 = (x - x0)m
                p1.x = winMin.x;
            }
            else if (code1 & winRightBitCode) { // 与右边界相交, 更新p1到右边界
                // 与右边界相交, 则斜率存在
                p1.y += (winMax.x - p1.x) * m; // y - y0 = (x - x0)m
                p1.x = winMax.x;
            }
            else if (code1 & winBottomBitCode) { // 与下边界相交, 更新p1到下边界
                /* Need to update p1.x for nonvertical lines only */
                if (p2.x != p1.x) {
                    p1.x += (winMin.y - p1.y) / m; // x - x0 = (y - y0)/m
                }
                p1.y = winMin.y;
            }
            else if (code1 & winTopBitCode) { // 与上边界相交, 更新p1到下边界
                if (p2.x != p1.x) {
                    p1.x += (winMax.y - p1.y) / m; // x - x0 = (y-y0)/m
                }
                p1.y = winMax.y;
            }
        }
    }

    // 绘制裁剪后的线段p1p2
    if (plotLine) {
        glBegin(GL_LINES);
        glColor3f(1.0,0,0);
        glVertex2i(myround(p1.x), myround(p1.y));
        glVertex2i(myround(p2.x), myround(p2.y));
        glEnd();
        glColor3f(0.87,0.56,0.4); // 设置颜色
        DDA(winMin.x,winMin.y,winMin.x,winMax.y);
        DDA(winMax.x,winMax.y,winMin.x,winMax.y);
        DDA(winMax.x,winMax.y,winMax.x,winMin.y);
        DDA(winMin.x,winMin.y,winMax.x,winMin.y);
//        glEnd();
    }
}