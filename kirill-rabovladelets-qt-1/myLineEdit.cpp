#include "mylineedit.h"
#include <QPainter>

MyLineEdit::MyLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
}

void MyLineEdit::setBackgroundImage(const QString& imagePath)
{
    QPixmap pixmap(imagePath);
    QPalette p = palette();
    p.setBrush(QPalette::Base, pixmap);
    setPalette(p);
}
