#include <GL/glut.h>
#include <iostream>
using namespace std;

// Clipping window boundaries
float xmin, ymin, xmax, ymax;

// Line endpoints (max 20 lines)
float x0[20], y0[20], x1[20], y1[20];
int n; // Number of lines

// Liang–Barsky line clipping algorithm
bool liangBarsky(float x0, float y0, float x1, float y1,
                 float xmin, float ymin, float xmax, float ymax,
                 float &cx0, float &cy0, float &cx1, float &cy1)
{
    float dx = x1 - x0;
    float dy = y1 - y0;

    float p[4] = {-dx, dx, -dy, dy};
    float q[4] = {x0 - xmin, xmax - x0, y0 - ymin, ymax - y0};

    float u1 = 0.0f, u2 = 1.0f;

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0) {
            if (q[i] < 0) return false; // Line parallel and outside
        } else {
            float r = q[i] / p[i];
            if (p[i] < 0) u1 = max(u1, r);
            else u2 = min(u2, r);
        }
    }

    if (u1 > u2) return false; // Line outside

    cx0 = x0 + u1 * dx;
    cy0 = y0 + u1 * dy;
    cx1 = x0 + u2 * dx;
    cy1 = y0 + u2 * dy;

    return true;
}

// Draw rectangle (clipping window)
void drawRectangle(float xmin, float ymin, float xmax, float ymax) {
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window in white
    glColor3f(1, 1, 1);
    drawRectangle(xmin, ymin, xmax, ymax);

    for (int i = 0; i < n; i++) {
        // Draw original line in red
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
            glVertex2f(x0[i], y0[i]);
            glVertex2f(x1[i], y1[i]);
        glEnd();

        // Clip the line
        float cx0, cy0, cx1, cy1;
        if (liangBarsky(x0[i], y0[i], x1[i], y1[i], xmin, ymin, xmax, ymax, cx0, cy0, cx1, cy1)) {
            // Draw clipped line in green
            glColor3f(0, 1, 0);
            glBegin(GL_LINES);
                glVertex2f(cx0, cy0);
                glVertex2f(cx1, cy1);
            glEnd();
        }
    }

    glFlush();
}

// OpenGL initialization
void init() {
    glClearColor(0, 0, 0, 1); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500); // Coordinate system
}

int main(int argc, char **argv) {
    cout << "Enter clipping window (xmin ymin xmax ymax): ";
    cin >> xmin >> ymin >> xmax >> ymax;

    cout << "Enter number of lines: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter line " << i + 1 << " (x0 y0 x1 y1): ";
        cin >> x0[i] >> y0[i] >> x1[i] >> y1[i];
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Liang-Barsky Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
