#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

// Function to plot a pixel at (x, y)
void drawPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Function to generate a circle using Bresenham's circle algorithm
void generateCircle(int cx, int cy, int radius) {
    int x = 0;
    int y = radius;
    int decision = 1 - radius;

    while (x <= y) {
        drawPoint(cx + x, cy + y);
        drawPoint(cx - x, cy + y);
        drawPoint(cx + x, cy - y);
        drawPoint(cx - x, cy - y);
        drawPoint(cx + y, cy + x);
        drawPoint(cx - y, cy + x);
        drawPoint(cx + y, cy - x);
        drawPoint(cx - y, cy - x);

        if (decision < 0) {
            decision += 2 * x + 3;
        } else {
            decision += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

// Function to create concentric circles with gradient effect
void drawGradientCircles(int centerX, int centerY, int numCircles) {
    int startRadius = 20; // Starting radius of the first circle

    // Define new gradient colors (pink, purple, sky blue)
    float endRed = 0.53f, endGreen = 0.81f, endBlue = 0.98f;  // Sky Blue
    float middleRed = 0.58f, middleGreen = 0.0f, middleBlue = 0.83f; // Purple
    float startRed = 1.0f, startGreen = 0.75f, startBlue = 0.8f; // Pink

    // Loop through all circles, creating each with different radius and thickness
    for (int i = 0; i < numCircles; i++) {
        int radius = startRadius + i * 20; // Increase radius for each circle
        int thickness = 2 + i / 2; // Vary thickness slightly

        // Calculate the interpolation factor for color transition
        float factor = float(i) / (numCircles - 1);

        // Calculate the color at this step
        float r, g, b;
        if (factor < 0.5f) {
            float t = factor / 0.5f;
            r = startRed + t * (middleRed - startRed);
            g = startGreen + t * (middleGreen - startGreen);
            b = startBlue + t * (middleBlue - startBlue);
        } else {
            float t = (factor - 0.5f) / 0.5f;
            r = middleRed + t * (endRed - middleRed);
            g = middleGreen + t * (endGreen - middleGreen);
            b = middleBlue + t * (endBlue - middleBlue);
        }

        // Set the color for the current circle
        glColor3f(r, g, b);

        // Draw the circle with the current radius and thickness
        for (int t = 0; t < thickness; t++) {
            generateCircle(centerX, centerY, radius + t);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
    drawGradientCircles(250, 250, 4); // Draw 4 concentric circles with gradient
    glFlush();
}

int main(int argc, char** argv) {
    // Initialize GLUT and set up the display mode
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Gradient Concentric Circles");

    // Set up orthogonal 2D projection
    gluOrtho2D(0, 500, 0, 500);

    // Set the background color to white
    glClearColor(1, 1, 1, 1);

    // Register the display function
    glutDisplayFunc(display);

    // Start the GLUT main loop
    glutMainLoop();

    return 0;
}
