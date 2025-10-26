#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;

struct Line {
    float x1, y1, x2, y2;
};

// Clipping window boundaries
float xmin = 100, ymin = 100, xmax = 400, ymax = 300;
vector<Line> lines;

// Function to draw a line
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// Function to draw the clipping rectangle
void drawRect() {
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
}

// Liang-Barsky Line Clipping algorithm helper function
bool clipTest(float p, float q, float &u1, float &u2) {
    float r;
    if (p == 0 && q < 0) return false;
    if (p != 0) {
        r = q / p;
        if (p < 0) {
            if (r > u2) return false;
            else if (r > u1) u1 = r;
        } else if (p > 0) {
            if (r < u1) return false;
            else if (r < u2) u2 = r;
        }
    }
    return true;
}

// Liang-Barsky Clipping function
void liangBarsky(Line l) {
    float dx = l.x2 - l.x1, dy = l.y2 - l.y1;
    float u1 = 0.0, u2 = 1.0;

    // Perform clipping tests for the left, right, bottom, and top edges
    if (clipTest(-dx, l.x1 - xmin, u1, u2) &&
        clipTest(dx, xmax - l.x1, u1, u2) &&
        clipTest(-dy, l.y1 - ymin, u1, u2) &&
        clipTest(dy, ymax - l.y1, u1, u2)) {

        // Calculate the new clipped coordinates
        float nx1 = l.x1 + u1 * dx;
        float ny1 = l.y1 + u1 * dy;
        float nx2 = l.x1 + u2 * dx;
        float ny2 = l.y1 + u2 * dy;

        // Draw the clipped portion in red
        glColor3f(1, 0, 0);
        drawLine(nx1, ny1, nx2, ny2);
    }
}

// Display function to show the result
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the clipping rectangle
    glColor3f(0, 0, 0);  // Black for rectangle
    drawRect();

    // Draw the original lines in blue
    glColor3f(0, 0, 1);  // Blue for original lines
    for (auto l : lines) {
        drawLine(l.x1, l.y1, l.x2, l.y2);
    }

    // Clip the lines using Liang-Barsky and display clipped portions in red
    for (auto l : lines) {
        liangBarsky(l);
    }

    glFlush();
}

int main(int argc, char** argv) {
    int n;
    cout << "=== Liang-Barsky Line Clipping ===\n";
    cout << "Clipping rectangle: xmin=" << xmin << ", ymin=" << ymin
         << ", xmax=" << xmax << ", ymax=" << ymax << "\n\n";

    cout << "Instructions for line input:\n";
    cout << "1. Fully Inside: Enter both endpoints inside rectangle (e.g., 150 150 350 250)\n";
    cout << "2. Fully Outside: Enter both endpoints completely outside and not intersecting (e.g., 10 10 50 50)\n";
    cout << "3. Partially Intersecting: Enter one endpoint inside and one outside or crossing (e.g., 50 150 450 250)\n\n";

    cout << "Enter number of lines: ";
    cin >> n;

    lines.resize(n);
    for (int i = 0; i < n; i++) {
        cout << "Line " << i + 1 << " - Enter x1 y1 x2 y2: ";
        cin >> lines[i].x1 >> lines[i].y1 >> lines[i].x2 >> lines[i].y2;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 400);
    glutCreateWindow("Liang-Barsky Line Clipping");
    gluOrtho2D(0, 500, 0, 400);
    glClearColor(1, 1, 1, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
