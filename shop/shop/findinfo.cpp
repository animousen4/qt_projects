#include "findinfo.h"
#include "ui_findinfo.h"

FindInfo::FindInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindInfo)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, [this](){
        close();
    });
}

FindInfo::~FindInfo()
{
    delete ui;
}

void FindInfo::showInfo(s2 a, s2 b) {
    if (a.section == "" && a.cnt == -1) {
        ui->infoBrowser->append("not found in the first set");
    }
    else {
        QString dop = "in the first set: section name is " + a.section;
        if (a.cnt != -2) dop += ", amount of product is " + QString::number(a.cnt);
        ui->infoBrowser->append(dop);
    }

    if (b.section == "" && b.cnt == -1) {
        ui->infoBrowser->append("not found in the second set");
    }
    else {
        QString dop = "in the second set: section name is " + b.section;
        if (b.cnt != -2) dop += ", amount of product is " + QString::number(b.cnt);
        ui->infoBrowser->append(dop);
    }
}
