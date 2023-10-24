#include "helpwindow.h"
#include "ui_helpwindow.h"

#include <QDesktopServices>

helpwindow::helpwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpwindow)
{
    ui->setupUi(this);

    ui->ssfile->setText("<a href=\"file.html\">Примеры выполнения и ввода.</a>");
    ui->ssfile->setTextFormat(Qt::RichText);
    ui->ssfile->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->ssfile->setOpenExternalLinks(true);

    ui->ssedit->setText("<a href=\"edit.html\">Примеры выполнения и ввода.</a>");
    ui->ssedit->setTextFormat(Qt::RichText);
    ui->ssedit->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->ssedit->setOpenExternalLinks(true);
}

helpwindow::~helpwindow()
{
    delete ui;
}
