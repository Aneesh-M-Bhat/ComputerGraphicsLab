#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#define PI 3.1416

struct point
{
    GLfloat x, y;
};

float theta = 0;
point controlPts[4];
int numControlPts = 4, numBezierPts = 20, n = numControlPts - 1;
int *ncrValues = new int[numControlPts];

int factorial(int n)
{
    if (n <= 1)
        return (1);
    else
        n = n * factorial(n - 1);
    return n;
}

void computenCr()
{
    for (int r = 0; r <= n; r++)
        ncrValues[r] = factorial(n) / (factorial(n - r) * factorial(r));
}

void computeBezierPoints(float t, point *bezierPt)
{
    float bernsteinPolynomial;
    bezierPt->x = 0;
    bezierPt->y = 0;
    for (int i = 0; i < numControlPts; i++)
    {
        bernsteinPolynomial = ncrValues[i] * pow(t, i) * pow(1 - t, n - i);
        bezierPt->x += bernsteinPolynomial * controlPts[i].x;
        bezierPt->y += bernsteinPolynomial * controlPts[i].y;
    }
}

void bezier()
{
    point bezierPt;
    float t;
    computenCr();
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= numBezierPts; i++)
    {
        t = float(i) / float(numBezierPts);
        computeBezierPoints(t, &bezierPt);
        glVertex2f(bezierPt.x, bezierPt.y);
    }
    glEnd();
}

void update()
{
    float temp = 25 * sin(theta * PI / 180.0);
    controlPts[1].x += temp;
    controlPts[1].y += temp;
    controlPts[2].x -= temp;
    controlPts[2].y -= temp;
    controlPts[3].x -= temp;
    controlPts[3].y += temp;
    theta += 0.2;
}

void drawFlagBlock(float r, float g, float b)
{
    glColor3f(r, g, b);
    for (int i = 0; i < 50; i++)
    {
        glTranslatef(0, -0.8, 0);
        bezier();
    }
}

void drawPole()
{
    glLineWidth(5);
    glColor3f(0.7, 0.5, 0.3);
    glBegin(GL_LINES);
    glVertex2f(100, 400);
    glVertex2f(100, 40);
    glEnd();
}

void drawFlag()
{
    glPushMatrix();
    glPointSize(5);
    drawFlagBlock(1, 0.4, 0.2);
    drawFlagBlock(1, 1, 1);
    drawFlagBlock(0, 1, 0);
    glPopMatrix();
}

void initControlPts()
{
    controlPts[0] = {100, 400};
    controlPts[1] = {150, 450};
    controlPts[2] = {250, 350};
    controlPts[3] = {300, 400};
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    initControlPts();
    update();
    drawFlag();
    drawPole();
    glutPostRedisplay();
    glutSwapBuffers();
}

void init()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bezier Curve");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    init();
}