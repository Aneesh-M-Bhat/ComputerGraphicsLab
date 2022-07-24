#include <GL/glut.h>
#include <stdio.h>
int x1, y1, x2, y2;

void drawPoint(int x, int y)
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void bresenhamLineDraw()
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float m = dy / dx;
    if (m < 1)
    {
        int decisionParameter = 2 * dy - dx;
        int x = x1;
        int y = y1;
        if (dx < 0)
        {
            x = x2;
            y = y2;
            x2 = x1;
        }
        drawPoint(x, y);
        while (x < x2)
        {
            if (decisionParameter >= 0)
            {
                x++;
                y++;
                decisionParameter += 2 * dy - 2 * dx;
            }
            else
            {
                x++;
                decisionParameter += 2 * dy;
            }
            drawPoint(x, y);
        }
    }
    else
    {
        int decisionParameter = 2 * dx - dy;
        int x = x1;
        int y = y1;
        if (dy < 0)
        {
            x = x2;
            y = y2;
            y2 = y1;
        }
        drawPoint(x, y);
        while (y < y2)
        {
            if (decisionParameter >= 0)
            {
                x++;
                y++;
                decisionParameter += 2 * dx - 2 * dy;
            }
            else
            {
                y++;
                decisionParameter += 2 * dx;
            }
            drawPoint(x, y);
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    bresenhamLineDraw();
    glFlush();
}

void init()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(220, 200);
    glutCreateWindow("Bresenham's Line Drawing");
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glutDisplayFunc(display);
    glutMainLoop();
}

int main(int argc, char **argv)
{
    printf("Enter Start Points (x1,y1)\n");
    scanf("%d %d", &x1, &y1);
    printf("Enter End Points (x2,y2)\n");
    scanf("%d %d", &x2, &y2);

    glutInit(&argc, argv);
    init();
}