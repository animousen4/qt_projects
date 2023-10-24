#include "dialogfile.h"
#include "ui_dialogfile.h"

DialogFile::DialogFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFile)
{
    ui->setupUi(this);

    fileNameEdit = ui->lineEdit;
    nameEnteredBtn = ui->nameEnteredBtn;
}

DialogFile::~DialogFile()
{
    delete ui;
}


