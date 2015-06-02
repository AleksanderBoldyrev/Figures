#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtCore>
#include "figure.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QList<Figure*> figures;
    Figure* current;
    Figure* toRemove;
    FigureType type;
    QTimer* timer;
    bool blink, needBlink;
    QColor color, background;
    QString fileName;

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void closeEvent(QCloseEvent * event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSquare_activated();

    void on_actionCircle_activated();

    void on_actionTriangle_activated();

    void on_actionSomeTriangle_activated();

    void onTimeout();

    void on_actionChooseColor_triggered();

    void on_actionSquare_triggered(bool checked);

    void on_actionCircle_triggered(bool checked);

    void on_actionTriangle_triggered(bool checked);

    void on_actionSomeTriangle_triggered(bool checked);

    void on_actionRemove_triggered();

    void onPopupHidden();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_actionCustomize_triggered();

    void on_actionExit_triggered();

    void on_pushButton_pressed();



private:
    Ui::MainWindow *ui;

    bool isPressed1, isPressed2;
    int xx, yy, xx1, yy1;


    void leftButtonPressEvent(QMouseEvent * event);
    void rightButtonPressEvent(QMouseEvent * event);
};

#endif // MAINWINDOW_H
