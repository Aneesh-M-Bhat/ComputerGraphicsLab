#include <GL/glut.h>

struct point
{
    GLfloat x, y, z;
};

void drawTeapot(point t)
{
    glPushMatrix();
    glTranslatef(t.x, t.y, t.z);
    glutSolidTeapot(0.1);
    glPopMatrix();
}

void drawCube(point t, point s)
{
    glPushMatrix();
    glTranslatef(t.x, t.y, t.z);
    glScalef(s.x, s.y, s.z);
    glutSolidCube(1);
    glPopMatrix();
}

void drawTableTop(point t)
{
    point s = {0.6, 0.02, 0.5};
    drawCube(t, s);
}

void drawTableLeg(point t)
{
    point s = {0.02, 0.3, 0.02};
    drawCube(t, s);
}

void drawWall(point t)
{
    point s = {1, 1, 0.02};
    drawCube(t, s);
}

void setLightSource()
{
    GLfloat mat_ambient[] = {1, 1, 1, 1};
    GLfloat mat_diffuse[] = {0.5, 0.5, 0.5, 1};
    GLfloat mat_specular[] = {1, 1, 1, 1};
    GLfloat mat_shininess[] = {50.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    GLfloat light_position[] = {2, 6, 3, 1};
    GLfloat light_intensity[] = {0.7, 0.7, 0.7, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_intensity);
}

void display()
{
    GLfloat teapotP = -0.07, tabletopP = -0.15, tablelegP = 0.2, wallP = 0.5;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(-2, 2, 5, 0, 0, 0, 0, 1, 0);
    setLightSource();
    drawTeapot({0, teapotP, 0});
    drawTableTop({0, tabletopP, 0});
    drawTableLeg({tablelegP, -0.3, tablelegP});
    drawTableLeg({-tablelegP, -0.3, tablelegP});
    drawTableLeg({-tablelegP, -0.3, -tablelegP});
    drawTableLeg({tablelegP, -0.3, -tablelegP});
    drawWall({0, 0, -wallP});
    glRotatef(90, 1, 0, 0);
    drawWall({0, 0, wallP});
    glRotatef(90, 0, 1, 0);
    drawWall({0, 0, wallP});
    glFlush();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 10);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    // glutInitWindowPosition(0, 0);
    glutCreateWindow("Teapot on a table");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}