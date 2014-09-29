#include "geometry.h"

Point::Point() :
        x (0),
        y (0)
{ }

Point::Point(int x, int y) :
        x (x),
        y (y)
{ }

Point::Point(const Point& cpy) :
        x (cpy.x),
        y (cpy.y)
{ }

Point::~Point()
{ }

int
Point::getX()
{
    return x;
}

int
Point::getY()
{
    return y;
}

void
Point::move(int x, int y)
{
    this->x = x;
    this->y = y;
}

Rectangle::Rectangle() :
        origin(0, 0),
        width(0),
        height(0)
{ }

Rectangle::Rectangle(int x, int y, int width, int height) :
        origin (x, y),
        width (width),
        height (height)
{ }

Rectangle::Rectangle(const Rectangle& cpy) :
        origin (cpy.origin),
        width (cpy.width),
        height (cpy.height)
{ }

Rectangle::~Rectangle()
{ }

int
Rectangle::getX()
{
    return origin.getX();
}

int
Rectangle::getY()
{
    return origin.getY();
}

int
Rectangle::getWidth()
{
    return width;
}

int
Rectangle::getHeight()
{
    return height;
}

void
Rectangle::move(int x, int y)
{
    origin.move(x, y);
}

void
Rectangle::resize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void
Rectangle::moveResize(int x, int y, int width, int height)
{
    move(x, y);
    resize(width, height);
}
