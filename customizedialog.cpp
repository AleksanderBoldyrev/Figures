#include "customizedialog.h"
#include "ui_customizedialog.h"

CustomizeDialog::CustomizeDialog(QColor bk, bool nb, QWidget *parent) :
    QDialog(parent), background(bk), needBlink(nb),
    ui(new Ui::CustomizeDialog)
{
    ui->setupUi(this);
    ui->labelColor->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window, background);
    ui->labelColor->setPalette(palette);
    ui->checkBox->setChecked(needBlink);
}

CustomizeDialog::~CustomizeDialog()
{
    delete ui;
}

void CustomizeDialog::on_checkBox_toggled(bool checked)
{
    needBlink = checked;
}

void CustomizeDialog::on_backgroundButton_clicked()
{
    QColorDialog * dialog = new QColorDialog(this);
    background = dialog->getColor();
    QPalette palette;
    palette.setColor(QPalette::Window, background);
    ui->labelColor->setPalette(palette);
}
