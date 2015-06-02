#include "figure.h"

void Figure::moveTo(const QPoint& to)
{
    upp_left = to;
}

void Figure::resize(const QPoint &lr)
{
    size = lr - upp_left;
}

bool Figure::inside(QPoint& p)
{
    return (p.x() - upp_left.x())*(p.x() - upp_left.x() - size.x()) <= 0 &&
           (p.y() - upp_left.y())*(p.y() - upp_left.y() - size.y()) <= 0;
}

QDomElement pointToElement(const QPoint& p, const QString& name, QDomDocument& doc)
{
    QDomElement elem = doc.createElement(name);
    QDomAttr attrx = doc.createAttribute("x");
    attrx.setValue(QString::number(p.x()));
    QDomAttr attry = doc.createAttribute("y");
    attry.setValue(QString::number(p.y()));
    elem.setAttributeNode(attrx);
    elem.setAttributeNode(attry);
    return elem;
}

void Figure::fill(QDomDocument& doc, QDomElement &elem)
{
    QDomElement ulElem = pointToElement(upp_left, "upper_left", doc);
    elem.appendChild(ulElem);
    QDomElement sizeElem = pointToElement(size, "size", doc);
    elem.appendChild(sizeElem);
    QDomAttr attrred = doc.createAttribute("red");
    attrred.setValue(QString::number(color.red()));
    elem.setAttributeNode(attrred);
    QDomAttr attrgreen = doc.createAttribute("green");
    attrgreen.setValue(QString::number(color.green()));
    elem.setAttributeNode(attrgreen);
    QDomAttr attrblue = doc.createAttribute("blue");
    attrblue.setValue(QString::number(color.blue()));
    elem.setAttributeNode(attrblue);
}

QPoint pointFromElement(QDomElement& elem)
{
    QString strx = elem.attribute("x");
    QString stry = elem.attribute("y");
    int x = strx.toInt();
    int y = stry.toInt();
    return QPoint(x, y);
}

Figure* Figure::createFigure(QDomElement &elem)
{
    QDomElement ulElem = elem.firstChildElement("upper_left");
    QPoint ul = pointFromElement(ulElem);
    QDomElement urElem = elem.firstChildElement("upper_right");
    QPoint ur = pointFromElement(urElem);
    QDomElement szElem = elem.firstChildElement("size");
    QPoint sz = pointFromElement(szElem);
    int red = elem.attribute("red").toInt();
    int green = elem.attribute("green").toInt();
    int blue = elem.attribute("blue").toInt();
    QColor c = QColor(red, green, blue);
    if (elem.tagName()=="square")
    {
        return new Square(ul, sz, c);
    }
    else if (elem.tagName()=="circle")
    {
        return new Circle(ul, sz, c);
    }
    else if (elem.tagName()=="triangle")
    {
        return new Triangle(ul, sz, c);
    }
    else if (elem.tagName()=="sometriangle")
    {
        return new SomeTriangle(ul, ur, sz, c);
    }
    else
    {
        return 0;
    }
}

void Square::paint(QPainter &painter)
{
    painter.setPen(QPen(color));
    painter.drawRect(QRect(upp_left, upp_left + size));
}

void Circle::paint(QPainter &painter)
{
    painter.setPen(QPen(color));
    QPoint radius = size / 2;
    painter.drawEllipse(upp_left + radius, radius.x(), radius.y());
}

void Triangle::paint(QPainter &painter)
{
    painter.setPen(QPen(color));
    painter.drawLine(upp_left.x(), upp_left.y(), upp_left.x() + size.x(), upp_left.y());
    painter.drawLine(upp_left.x(), upp_left.y(), upp_left.x(), upp_left.y() + size.y());
    painter.drawLine(upp_left.x() + size.x(), upp_left.y(), upp_left.x(), upp_left.y() + size.y());
}

void SomeTriangle::paint(QPainter &painter)
{
    painter.setPen(QPen(color));
    painter.drawLine(upp_left.x(), upp_left.y(), upp_right.x(), upp_right.y());
    painter.drawLine(upp_left.x(), upp_left.y(), size.x() + upp_left.x(),  size.y() + upp_left.y());
    painter.drawLine(size.x() + upp_left.x(),  size.y() + upp_left.y(), upp_right.x(), upp_right.y());
}

/*void SomeTriangle::resize(const QPoint& lr)
{
    upp_right.setX(lr.x());
    upp_right.setY(lr.y());
}*/

void SomeTriangle::fill(QDomDocument& doc, QDomElement &elem)
{
    QDomElement ulElem = pointToElement(upp_left, "upper_left", doc);
    elem.appendChild(ulElem);
    QDomElement ulElem2 = pointToElement(upp_right, "upper_right", doc);
    elem.appendChild(ulElem2);
    QDomElement sizeElem = pointToElement(size, "size", doc);
    elem.appendChild(sizeElem);
    QDomAttr attrred = doc.createAttribute("red");
    attrred.setValue(QString::number(color.red()));
    elem.setAttributeNode(attrred);
    QDomAttr attrgreen = doc.createAttribute("green");
    attrgreen.setValue(QString::number(color.green()));
    elem.setAttributeNode(attrgreen);
    QDomAttr attrblue = doc.createAttribute("blue");
    attrblue.setValue(QString::number(color.blue()));
    elem.setAttributeNode(attrblue);
}

QDomElement Square::toDomElement(QDomDocument &doc)
{
    QDomElement elem = doc.createElement("square");
    fill(doc, elem);
    return elem;
}

QDomElement Circle::toDomElement(QDomDocument &doc)
{
    QDomElement elem = doc.createElement("circle");
    fill(doc, elem);
    return elem;
}

QDomElement Triangle::toDomElement(QDomDocument &doc)
{
    QDomElement elem = doc.createElement("triangle");
    fill(doc, elem);
    return elem;
}

QDomElement SomeTriangle::toDomElement(QDomDocument &doc)
{
    QDomElement elem = doc.createElement("sometriangle");
    SomeTriangle::fill(doc, elem);
    return elem;
}
