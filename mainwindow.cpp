#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customizedialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    current = toRemove = 0;
    type = FT_NONE;
    blink = false;
    needBlink = true;
    background = this->palette().background().color();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(onTimeout()));
    isPressed1 = false;
    isPressed2 = false;
    QResource::registerResource("icon.qrc");
}

MainWindow::~MainWindow()
{
    QListIterator<Figure*> it(figures);
    while (it.hasNext())
    {
        Figure* fig = it.next();
        delete fig;
    }
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    QListIterator<Figure*> it(figures);
    while (it.hasNext())
    {
        Figure* fig = it.next();
        if (fig != toRemove || !blink)
            fig->paint(painter);
    }
    if (current && (!needBlink || !blink))
    {
        painter.setPen(QPen(Qt::red));
        current->paint(painter);
    }
    painter.end();
}

void MainWindow::leftButtonPressEvent(QMouseEvent * ev)
{
    toRemove = 0;
    timer->stop();
    if (type==FT_NONE)
        return;
    else if (type==FT_SQUARE)
    {
        current = new Square(ev->pos(), QPoint(0, 0), color);
    }
    else if (type==FT_TRIANGLE)
    {
        current = new Triangle(ev->pos(), QPoint(0, 0), color);
    }
    else if (type==FT_SOMETRIANGLE)
    {
        if (isPressed1 == false)
        {
            isPressed1 = true;
            xx = ev->pos().x();
            yy = ev->pos().y();
        }
        /*else if (isPressed2 == false)
        {
            isPressed2 = true;
            xx1 = ev->pos().x();
            yy1 = ev->pos().y();
        }*/
        else
        {
            isPressed1 = false;
            //isPressed2 = false;
            current = new SomeTriangle(ev->pos(), QPoint(xx, yy),  color);
        }
    }
    else
    {
        current = new Circle(ev->pos(), QPoint(0, 0), color);
    }
    timer->start(100);
}

void MainWindow::rightButtonPressEvent(QMouseEvent * ev)
{
    toRemove = 0;
    timer->stop();
    QPoint pos = ev->pos();
    QListIterator<Figure*> it(figures);
    while (it.hasNext())
    {
        Figure* fig = it.next();
        if (fig->inside(pos))
        {
            toRemove = fig;
            timer->start(100);
            QMenu* popup = new QMenu(this);
            connect(popup, SIGNAL(aboutToHide()), SLOT(popupHidden()));
            popup->addAction(ui->actionRemove);
            popup->exec(ev->globalPos());
            return;
        }
    }
    toRemove = 0;
}



void MainWindow::mousePressEvent(QMouseEvent * ev)
{
    if (ev->button() == Qt::LeftButton)
        leftButtonPressEvent(ev);
    else if (ev->button() == Qt::RightButton)
        rightButtonPressEvent(ev);
}

void MainWindow::mouseMoveEvent(QMouseEvent * ev)
{
    if (current != 0)
    {
        current->resize(ev->pos());
        repaint();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent * ev)
{
    if (ev->button() != Qt::LeftButton)
        return;
    if (current != 0)
    {
        current->resize(ev->pos());
        figures.append(current);
        current = 0;
        timer->stop();
        repaint();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() != Qt::Key_Escape)
        return;
    current = 0;
    type = FT_NONE;
    ui->actionCircle->setChecked(false);
    ui->actionSquare->setChecked(false);
    ui->actionTriangle->setChecked(false);
    ui->actionSomeTriangle->setChecked(false);
    repaint();
}

void MainWindow::onTimeout()
{
    blink = !blink;
    repaint();
}

void MainWindow::on_actionSquare_activated()
{
//    type = FT_SQUARE;
//    current = 0;
//    repaint();
}

void MainWindow::on_actionCircle_activated()
{
//    type = FT_CIRCLE;
//    current = 0;
//    repaint();
}

void MainWindow::on_actionTriangle_activated()
{
//    type = FT_TRIANGLE;
//    current = 0;
//    repaint();
}

void MainWindow::on_actionSomeTriangle_activated()
{
//    type = FT_TRIANGLE;
//    current = 0;
//    repaint();
}

void MainWindow::on_actionChooseColor_triggered()
{
    QColor chosen = QColorDialog::getColor(color, this);
    color = chosen.isValid() ? chosen : color;
}

void MainWindow::on_actionSquare_triggered(bool checked)
{
    type = checked ? FT_SQUARE : FT_NONE;
    ui->actionCircle->setChecked(false);
    ui->actionTriangle->setChecked(false);
    ui->actionSomeTriangle->setChecked(false);
    current = 0;
    repaint();
}

void MainWindow::on_actionCircle_triggered(bool checked)
{
    type = checked ? FT_CIRCLE : FT_NONE;
    ui->actionSquare->setChecked(false);
    ui->actionTriangle->setChecked(false);
    ui->actionSomeTriangle->setChecked(false);
    current = 0;
    repaint();
}

void MainWindow::on_actionTriangle_triggered(bool checked)
{
    type = checked ? FT_TRIANGLE : FT_NONE;
    ui->actionSquare->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionSomeTriangle->setChecked(false);
    current = 0;
    repaint();
}

void MainWindow::on_actionSomeTriangle_triggered(bool checked)
{
    type = checked ? FT_SOMETRIANGLE : FT_NONE;
    ui->actionSquare->setChecked(false);
    ui->actionCircle->setChecked(false);
    ui->actionTriangle->setChecked(false);
    current = 0;
    repaint();
}

void MainWindow::on_actionRemove_triggered()
{
    if (!toRemove)
        return;
    figures.removeOne(toRemove);
    delete toRemove;
    toRemove = 0;
    timer->stop();
    repaint();
}

void MainWindow::onPopupHidden()
{
    toRemove = 0;
    timer->stop();
    repaint();
}

void MainWindow::on_actionSave_triggered()
{
    fileName = QFileDialog::getSaveFileName(this, "Сохранить");
    this->setWindowTitle(fileName);
    // сохранение
    QDomDocument doc("figures");
    QDomElement root = doc.createElement("figures");
    doc.appendChild(root);
    QListIterator<Figure*> it(figures);
    while (it.hasNext())
    {
        Figure* fig = it.next();
        root.appendChild(fig->toDomElement(doc));
    }
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream(&file) << doc.toString();
        file.close();
    }
}

void MainWindow::on_actionLoad_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, "Загрузить");
    this->setWindowTitle(fileName);
    // загрузка
    QDomDocument doc;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        if (doc.setContent(&file))
        {
            figures.clear();
            QDomElement elem = doc.documentElement();
            QDomNode node = elem.firstChild();
            while (!node.isNull())
            {
                if (node.isElement())
                {
                    QDomElement figElem = node.toElement();
                    Figure* readFig = Figure::createFigure(figElem);
                    if (readFig)
                        figures.append(readFig);
                }
                node = node.nextSibling();
            }
            repaint();
        }
    }
}

void MainWindow::on_actionCustomize_triggered()
{
    CustomizeDialog * dialog = new CustomizeDialog(background,
                                                   needBlink, this);
    if (dialog->exec()==QDialog::Accepted)
    {
        needBlink = dialog->isBlinkNeeded();
        background = dialog->getBackground();
        QPalette palette;
        palette.setColor(QPalette::Window, background);
        this->setPalette(palette);
        repaint();
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (QMessageBox::question(this, "Подтвердить",
                              "Действительно выйти?",
                              QMessageBox::Yes,
                              QMessageBox::No)==QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::on_pushButton_pressed()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Test", "Quit?",
                                   QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
    qDebug() << "Yes was clicked";
    QApplication::quit();
    } else {
      qDebug() << "Yes was *not* clicked";
    }
    current = 0;
    repaint();
}
