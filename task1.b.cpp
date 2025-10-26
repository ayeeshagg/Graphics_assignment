#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int x1_, y1_, x2_, y2_, width_;

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Function to draw a thick pixel using 8-way symmetry (this is where thickness is applied)
void drawThickPixel(int x, int y, int w)
{
    int r = w / 2;  // Radius of the "thickness" around the pixel
    for (int i = -r; i <= r; i++)
    {
        for (int j = -r; j <= r; j++)
        {
            drawPixel(x + i, y + j);  // Draw a pixel at (x + i, y + j)
        }
    }
}

void thickLine(int x1, int y1, int x2, int y2, int w)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        drawThickPixel(x1, y1, w);  // Call drawThickPixel to draw a thicker pixel
        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
    glColor3f(0, 0, 0);  // Set line color to black (RGB)
    thickLine(x1_, y1_, x2_, y2_, width_); // Call the thick line function
    glFlush();
}

int main(int argc, char** argv)
{
    // Prompt for coordinates and thickness
    cout << "Enter x1 y1 x2 y2: ";
    cin >> x1_ >> y1_ >> x2_ >> y2_;

    // Prompt for thickness (only allow values 3, 6, or 9)
    cout << "Enter line thickness (choose from 3, 6, 9): ";
    cin >> width_;

    // Validate that the thickness is one of the allowed values
    if (width_ != 3 && width_ != 6 && width_ != 9)
    {
        cout << "Invalid thickness value. Please choose 3, 6, or 9." << endl;
        return -1; // Exit if the input is not valid
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Thick Line (Bresenham 8-way symmetry)");

    // Set the background color to light gray (0.8, 0.8, 0.8)
    glClearColor(0.8, 0.8, 0.8, 1);

    gluOrtho2D(0, 800, 0, 600); // Set up the 2D orthogonal projection
    glutDisplayFunc(display); // Register the display function
    glutMainLoop(); // Start the GLUT main loop

    return 0;
}
