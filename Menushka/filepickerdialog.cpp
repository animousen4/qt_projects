#include "filepickerdialog.h"
#include "ui_filepickerdialog.h"
#include "mainwindow.h"
#include <QDialogButtonBox>
#include <QSignalMapper>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
FilePickerDialog::FilePickerDialog(QWidget *parent, QString fileName) :
    QDialog(parent),
    ui(new Ui::FilePickerDialog)
{

    ui->setupUi(this);

    ui->fileNameTextEdit->setText(fileName);

    connect(ui->controlButtons, &QDialogButtonBox::accepted, this, &FilePickerDialog::fileAccepted);
    connect(ui->controlButtons, &QDialogButtonBox::rejected, this, &FilePickerDialog::close);

}
void FilePickerDialog::fileAccepted(){
    QString fileName = ui->fileNameTextEdit->toPlainText();
    emit fileSelected(fileName);
    close();
}

FilePickerDialog::~FilePickerDialog()
{
    delete ui;
}
