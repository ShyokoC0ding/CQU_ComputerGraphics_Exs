//
// Created by 84151 on 2024/10/2.
//

#ifndef OPENGL_PAINT_H
#define OPENGL_PAINT_H

void init();
void drawAxis(float minX, float maxX, float minY, float maxY, int numLines);

struct polygon{

};

struct Edge{
public:
    int ymax;
    float dx;
    float x;
    Edge* next;
};

class Point{
public:
    float x;
    float y;
    Point(float x,float y) {
        this->x = x;
        this->y = y;
    }
};


#endif //OPENGL_PAINT_H
