#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
public:
    MyLineEdit(QWidget *parent = nullptr);
    void setBackgroundImage(const QString& imagePath);
};

#endif // MYLINEEDIT_H
