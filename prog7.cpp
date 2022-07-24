#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

struct point
{
    GLfloat x, y, z;
};
point v[4] = {{0, 0, 1}, {0, 1, 0}, {-1, -0.5, 0}, {1, -0.5, 0}};
int n;

void drawTriangle(point a, point b, point c)
{
    glBegin(GL_POLYGON);
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);
    glVertex3f(c.x, c.y, c.z);
    glEnd();
}

point midPoint(point a, point b)
{
    point mid;
    mid.x = (a.x + b.x) / 2;
    mid.y = (a.y + b.y) / 2;
    mid.z = (a.z + b.z) / 2;
    return mid;
}

void divideTriangle(point a, point b, point c, int n)
{
    if (n > 0)
    {
        point v1, v2, v3;
        int j;
        v1 = midPoint(a, b);
        v3 = midPoint(b, c);
        v2 = midPoint(a, c);
        divideTriangle(a, v1, v2, n - 1);
        glFlush();
        divideTriangle(c, v2, v3, n - 1);
        glFlush();
        divideTriangle(b, v3, v1, n - 1);
        glFlush();
    }
    else
        (drawTriangle(a, b, c));
}

void drawPartTetrahedron(int r, int g, int b, int i, int j, int k)
{
    glColor3f(r, g, b);
    divideTriangle(v[i], v[j], v[k], n);
}

void tetrahedron()
{
    drawPartTetrahedron(1, 0, 0, 0, 1, 2);
    drawPartTetrahedron(0, 1, 0, 3, 2, 1);
    drawPartTetrahedron(0, 0, 1, 0, 3, 1);
    drawPartTetrahedron(0, 0, 0, 0, 2, 3);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    tetrahedron();
    glFlush();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2, 2, -2 * (GLfloat)h / (GLfloat)w, 2 * (GLfloat)h / (GLfloat)w, -10, 10);
    else
        glOrtho(-2 * (GLfloat)w / (GLfloat)h, 2 * (GLfloat)w / (GLfloat)h, -2, 2, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    printf("No of Recursive steps/Division: ");
    scanf("%d", &n);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow(" 3D Sierpinski gasket");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1, 1, 1, 0);
    glutMainLoop();
    return 0;
}