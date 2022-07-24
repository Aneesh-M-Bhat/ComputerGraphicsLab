// Scan-Line algorithm for filling a polygon
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

float x1 = 200, y1 = 200, x2 = 100, y2 = 300, x3 = 200, y3 = 400, x4 = 300, y4 = 300;

void swap(float *a,float *b){
    float temp = *a;
    *a = *b;
    *b = temp;
}

void edgeDetect(float x1, float y1, float x2, float y2, int *leftEdge, int *rightEdge)
{
    float slope, x, temp;
    if ((y2 - y1) < 0) // decide where to start
    {
        swap(&y1,&y2);
        swap(&x1,&x2);
    }
    if ((y2 - y1) != 0)
        slope = (x2 - x1) / (y2 - y1);
    else
        slope = x2 - x1;
    x = x1;
    for (int i = y1; i <= y2; i++)
    {
        if (x < leftEdge[i])
            leftEdge[i] = x;
        if (x > rightEdge[i])
            rightEdge[i] = x;
        x = x + slope;
    }
}

void drawPoint(int x, int y)
{
    glColor3f(1, 1, 0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void scanfill()
{
    int leftEdge[500], rightEdge[500];
    int i, y;
    for (i = 0; i <= 500; i++)
    {
        leftEdge[i] = 500;
        rightEdge[i] = 0;
    }
    edgeDetect(x1, y1, x2, y2, leftEdge, rightEdge);
    edgeDetect(x2, y2, x3, y3, leftEdge, rightEdge);
    edgeDetect(x3, y3, x4, y4, leftEdge, rightEdge);
    edgeDetect(x4, y4, x1, y1, leftEdge, rightEdge);
    for (y = 0; y <= 500; y++)
    {
        if (leftEdge[y] <= rightEdge[y])
        {
            for (i = leftEdge[y]; i <= rightEdge[y]; i++)
            {
                drawPoint(i, y);
                glFlush();
            }
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
    scanfill();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 499, 0, 499);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    // glutInitWindowPosition(0, 0);
    glutCreateWindow("Filling a Polygon using Scan-line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}