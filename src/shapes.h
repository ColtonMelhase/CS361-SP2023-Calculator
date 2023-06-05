#ifndef SHAPES_H
#define SHAPES_H

// Square
double squareArea(double side);
double squarePerimeter(double side);

// Rectangle
double rectangleArea(double length, double width);
double rectanglePerimeter(double length, double width);

// Cube
double cubeSurfaceArea(double side);
double cubeVolume(double side);

// Rectangular Prism
double rectangularPrismSurfaceArea(double length, double width, double height);
double rectangularPrismVolume(double length, double width, double height);

// Trapezoid
double trapezoidArea(double base1, double base2, double height);
double trapezoidPerimeter(double base1, double base2, double side1, double side2);

// Circle
double circleArea(double radius);
double circleCircumference(double radius);

// Sphere
double sphereSurfaceArea(double radius);
double sphereVolume(double radius);

// Pyramid
double pyramidSurfaceArea(double baseLength, double baseWidth, double slantHeight);
double pyramidVolume(double baseLength, double baseWidth, double height);

#endif
