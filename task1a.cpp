#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

// Function to draw a pixel at (x, y)
void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Function to implement Bresenham's Line Algorithm
void bresenhamLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    bool steep = dy > dx;

    if (steep)
    {
        swap(x1, y1);
        swap(x2, y2);
        swap(dx, dy);
        swap(sx, sy);
    }

    int err = 2 * dy - dx;
    int x = x1;
    int y = y1;

    // Draw the line by iterating over the x-axis
    for (int i = 0; i <= dx; i++)
    {
        if (steep)
            drawPixel(y, x);
        else
            drawPixel(x, y);

        x += sx;
        if (err > 0)
        {
            y += sy;
            err -= 2 * dx;
        }
        err += 2 * dy;
    }
}

// Display function to clear screen and draw the line
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0); // Black color for the line
    bresenhamLine(100, 100, 400, 300); // Hardcoded example coordinates
    glFlush();
}

// Function to initialize OpenGL settings
void initializeOpenGL(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Bresenham Line Drawing (All Cases)");
    gluOrtho2D(0, 700, 0, 700); // Set the coordinate system
    glClearColor(1, 1, 1, 1);    // Set white background
}

// Main function to handle user input
int main(int argc, char** argv)
{
    int x1, y1, x2, y2;
    cout << "Enter x1 y1 x2 y2: ";
    cin >> x1 >> y1 >> x2 >> y2;

    // Check if the coordinates are within the OpenGL window bounds
    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || x1 > 700 || y1 > 700 || x2 > 700 || y2 > 700) {
        cout << "Error: Coordinates should be between 0 and 700." << endl;
        return -1; // Exit if out of bounds
    }

    initializeOpenGL(argc, argv);  // Initialize OpenGL settings
    glutDisplayFunc(display);      // Register the display function
    glutMainLoop();                // Start the GLUT main loop
    return 0;
}
