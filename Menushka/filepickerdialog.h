#ifndef FILEPICKERDIALOG_H
#define FILEPICKERDIALOG_H

#include <QDialog>
namespace Ui {
class FilePickerDialog;
}

class FilePickerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilePickerDialog(QWidget *parent = nullptr, QString fileName = "");
    ~FilePickerDialog();

private:
    Ui::FilePickerDialog *ui;
signals:
    void fileSelected(QString fileName);
public slots:
    void fileAccepted();
};

#endif // FILEPICKERDIALOG_H
