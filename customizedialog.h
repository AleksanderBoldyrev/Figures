#ifndef CUSTOMIZEDIALOG_H
#define CUSTOMIZEDIALOG_H

#include <QtWidgets>

namespace Ui {
class CustomizeDialog;
}

class CustomizeDialog : public QDialog
{
    Q_OBJECT

    QColor background;
    bool needBlink;
    
public:
    explicit CustomizeDialog(QColor bk, bool nb, QWidget *parent = 0);
    ~CustomizeDialog();

    QColor getBackground() { return background; }
    bool isBlinkNeeded() { return needBlink; }
    
private slots:
    void on_checkBox_toggled(bool checked);

    void on_backgroundButton_clicked();

private:
    Ui::CustomizeDialog *ui;
};

#endif // CUSTOMIZEDIALOG_H
