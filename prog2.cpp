#include <GL/glut.h>
#include <stdio.h>
int x, y;
int whereToRotate = 0;
float rotateAngle = 0;
float tX = 0, tY = 0;

void drawPoint(float x1, float y1)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(x1, y1);
    glEnd();
}

void drawTriangle(int x, int y)
{
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 400, y + 300);
    glVertex2f(x + 300, y + 0);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1, 1, 1);
    drawPoint(0, 0);
    if (whereToRotate == 1)
    {
        tX = 0;
        tY = 0;
        rotateAngle += 0.1;
    }
    if (whereToRotate == 2)
    {
        tX = x;
        tY = y;
        rotateAngle += 0.1;
        glColor3f(0, 0, 1);
        drawPoint(x, y);
    }
    glTranslatef(tX, tY, 0);
    glRotatef(rotateAngle, 0, 0, 1);
    glTranslatef(-tX, -tY, 0);
    drawTriangle(tX, tY);
    glutPostRedisplay();
    glutSwapBuffers();
}

void rotateMenu(int option)
{
    if (option == 1)
        whereToRotate = 1;
    if (option == 2)
        whereToRotate = 2;
    if (option == 3)
        whereToRotate = 3;
}

void createMenu()
{
    glutCreateMenu(rotateMenu);
    glutAddMenuEntry("Rotate around ORIGIN", 1);
    glutAddMenuEntry("Rotate around FIXED POINT", 2);
    glutAddMenuEntry("Stop Rotation", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Rotate Triangle");
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-800, 800, -800, 800);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    createMenu();
    glutMainLoop();
}

int main(int argc, char **argv)
{
    printf("Enter Fixed Points (x,y) for Rotation: \n");
    scanf("%d %d", &x, &y);

    glutInit(&argc, argv);
    init();
}