#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdio.h>

const int WIDTH = 800;
const int HEIGHT = 600;

int numCircles = 10;
int baseRadius = 30;
int radiusStep = 20;
int baseThickness = 1;
float colorStart[3] = {1.0, 0.0, 0.0};
float colorEnd[3] = {0.0, 0.0, 1.0};

void plotPoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
    glEnd();
}

void drawCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 1 - r;
    plotPoints(xc, yc, x, y);

    while (x < y) {
        x++;
        if (d < 0)
            d += 2 * x + 1;
        else {
            y--;
            d += 2 * (x - y) + 1;
        }
        plotPoints(xc, yc, x, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int xc = WIDTH / 2;
    int yc = HEIGHT / 2;

    for (int i = 0; i < numCircles; i++) {
        int radius = baseRadius + i * radiusStep;
        int thickness = baseThickness + i;

        float t = (float)i / (numCircles - 1);
        float r = colorStart[0] * (1 - t) + colorEnd[0] * t;
        float g = colorStart[1] * (1 - t) + colorEnd[1] * t;
        float b = colorStart[2] * (1 - t) + colorEnd[2] * t;

        glColor3f(r, g, b);
        glPointSize(thickness);

        drawCircle(xc, yc, radius);
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Concentric Circles with Color Gradient");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
