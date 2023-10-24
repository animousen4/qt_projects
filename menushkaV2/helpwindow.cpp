#include "helpwindow.h"
#include "./ui_helpwindow.h"
#include "windowlinknames.h"
HelpWindow::HelpWindow(QWidget *parent,  QString link) :
    QDialog(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
    CommonHelper &helper = WindowLinkNames::helpMap.find(link).value();
    ui->topicLabel->setText(helper.topic);
    this->setWindowTitle(helper.topic);

    ui->contentLabel->setText(helper.description);


}

HelpWindow::~HelpWindow()
{
    delete ui;
}
