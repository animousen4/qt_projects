#ifndef DIALOGFILE_H
#define DIALOGFILE_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class DialogFile;
}

class DialogFile : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFile(QWidget *parent = nullptr);
    ~DialogFile();

    QLineEdit* fileNameEdit;
    QPushButton* nameEnteredBtn;

private:
    Ui::DialogFile *ui;
};

#endif // DIALOGFILE_H
