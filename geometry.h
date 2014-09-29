#ifndef GEOMETRY_H_
#define GEOMETRY_H_

class Point
{
private:
    int x, y;

public:
    Point();
    Point(int, int);
    Point(const Point&);
    ~Point();

    int getX();
    int getY();

    void move(int, int);
};

class Rectangle
{
private:
    Point origin;
    int width, height;

public:
    Rectangle();
    Rectangle(int, int, int, int);
    Rectangle(const Rectangle&);
    ~Rectangle();

    int getX();
    int getY();
    int getWidth();
    int getHeight();

    void move(int, int);
    void resize(int, int);
    void moveResize(int, int, int, int);
};

#endif /* GEOMETRY_H_ */
