#include <cmath>
#include "shapes.h"

// Calculate the area of a square
double squareArea(double side) {
    return side * side;
}

// Calculate the perimeter of a square
double squarePerimeter(double side) {
    return 4 * side;
}

// Calculate the area of a rectangle
double rectangleArea(double length, double width) {
    return length * width;
}

// Calculate the perimeter of a rectangle
double rectanglePerimeter(double length, double width) {
    return 2 * (length + width);
}

// Calculate the surface area of a cube
double cubeSurfaceArea(double side) {
    return 6 * side * side;
}

// Calculate the volume of a cube
double cubeVolume(double side) {
    return side * side * side;
}

// Calculate the surface area of a rectangular prism
double rectangularPrismSurfaceArea(double length, double width, double height) {
    return 2 * (length * width + length * height + width * height);
}

// Calculate the volume of a rectangular prism
double rectangularPrismVolume(double length, double width, double height) {
    return length * width * height;
}

// Calculate the area of a trapezoid
double trapezoidArea(double base1, double base2, double height) {
    return (base1 + base2) * height / 2;
}

// Calculate the perimeter of a trapezoid
double trapezoidPerimeter(double base1, double base2, double side1, double side2) {
    return base1 + base2 + side1 + side2;
}

// Calculate the area of a circle
double circleArea(double radius) {
    return M_PI * radius * radius;
}

// Calculate the circumference of a circle
double circleCircumference(double radius) {
    return 2 * M_PI * radius;
}

// Calculate the surface area of a sphere
double sphereSurfaceArea(double radius) {
    return 4 * M_PI * radius * radius;
}

// Calculate the volume of a sphere
double sphereVolume(double radius) {
    return (4 / 3) * M_PI * radius * radius * radius;
}

// Calculate the surface area of a pyramid
double pyramidSurfaceArea(double baseLength, double baseWidth, double slantHeight) {
    double baseArea = baseLength * baseWidth;
    double triangleArea = (baseLength * slantHeight) / 2;
    return baseArea + 4 * triangleArea;
}

// Calculate the volume of a pyramid
double pyramidVolume(double baseLength, double baseWidth, double height) {
    return (baseLength * baseWidth * height) / 3;
}
