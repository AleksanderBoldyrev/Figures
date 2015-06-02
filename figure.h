#ifndef FIGURE_H
#define FIGURE_H

#include <QtWidgets>
#include <QtXml>

class Figure
{
protected:
    QPoint upp_left, size, upp_right;
    QColor color;
public:
    Figure(const QPoint& ul, const QPoint& s, const QColor& c):
        upp_left(ul), size(s),color(c) {}
    virtual ~Figure() {}
    void moveTo(const QPoint& to);
    void resize(const QPoint& lr);
    void checkSize();

    virtual bool inside(QPoint& p);
    virtual void paint(QPainter& painter) = 0;

    void fill(QDomDocument& doc, QDomElement& elem);
    static Figure* createFigure(QDomElement& elem);
    virtual QDomElement toDomElement(QDomDocument& doc) = 0;
};

class Square: public Figure
{
public:
    Square(const QPoint& ul, const QPoint& s, const QColor& c): Figure(ul, s, c) {}

    virtual void paint(QPainter& painter);
    virtual QDomElement toDomElement(QDomDocument& doc);
};

class Circle: public Figure
{
public:
    Circle(const QPoint& ul, const QPoint& s, const QColor& c): Figure(ul, s, c) {}

    virtual void paint(QPainter& painter);
    virtual QDomElement toDomElement(QDomDocument& doc);
};

class SomeTriangle: public Figure
{
public:
    SetSize(QPoint& q);

    //SomeTriangle(const QPoint& ul, const QPoint& s, const QPoint& r, const QColor& c): Figure(ul, s, r, c) {}
    SomeTriangle(const QPoint& ul, const QPoint& s, const QColor& c): Figure(ul, s, c) {

        upp_right.setX(s.x());
        upp_right.setY(s.y());
    }

    //virtual void resize(const QPoint& lr);
    virtual void paint(QPainter& painter);
    virtual QDomElement toDomElement(QDomDocument& doc);
};

class Triangle: public Figure
{
public:
    Triangle(const QPoint& ul, const QPoint& s, const QColor& c): Figure(ul, s, c) {}

    virtual void paint(QPainter& painter);
    virtual QDomElement toDomElement(QDomDocument& doc);
};

enum FigureType
{
    FT_NONE,
    FT_SQUARE,
    FT_CIRCLE,
    FT_TRIANGLE,
    FT_SOMETRIANGLE
};

#endif // FIGURE_H
