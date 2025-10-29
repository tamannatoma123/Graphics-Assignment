#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int x1, y1, x2, y2;
int thickness;

void myInit() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_thick_pixel(int cx, int cy, int w) {
    int r = w / 2;
    for (int dx = -r; dx <= r; dx++) {
        for (int dy = -r; dy <= r; dy++) {
            draw_pixel(cx + dx, cy + dy);
        }
    }
}
void draw_line_thick(int x1, int y1, int x2, int y2, int w) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x2 >= x1) ? 1 : -1;
    int sy = (y2 >= y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        draw_thick_pixel(x1, y1, w);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    draw_line_thick(x1, y1, x2, y2, thickness);
    glFlush();
}

int main(int argc, char **argv) {
    printf("Enter x1 y1 x2 y2 thickness: ");
    if (scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &thickness) != 5) {
        printf("Invalid input.\n");
        return 0;
    }
    if (thickness < 1) thickness = 1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Line Drawing (Thick Line)");

    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}
