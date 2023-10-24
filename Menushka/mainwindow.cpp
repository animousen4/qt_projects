#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include "mainwindowbloc.h"
#include <QWidget>
#include "editorwindow.h"
#include <QWidgetAction>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MainWindow - [no file open]");
    curFileName = "";
    fileButton = new QAction("File");

    ui->menubar->addAction(fileButton);
    /////

    QWidgetAction* comboAction = new QWidgetAction(this);

    QTextEdit* edit = new QTextEdit();


    // Set the QComboBox as the default widget for the QWidgetAction
    comboAction->setDefaultWidget(edit);

    // Add the QWidgetAction to the QMenuBar
    QMenu* editMenu = this->ui->menubar->addMenu("Edit");
    editMenu->setDisabled(true);
    editMenu->addAction(comboAction);


    ////////
    editButton->setDisabled(true);

    //MainWindowBloc * mwBloc = new MainWindowBloc(this);
    connect(fileButton, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(editButton, SIGNAL(triggered()), this, SLOT(editFile()));



}
void MainWindow::openFile() {
    qDebug() << "openfile";
    FilePickerDialog * filePickerDialog = new FilePickerDialog(this, curFileName);
    connect(filePickerDialog, &FilePickerDialog::fileSelected, this, &MainWindow::fileRecieved);
    filePickerDialog->show();
}

void MainWindow::editFile() {
    qDebug() << "editfile";
    EditorWindow * editorWindow = new EditorWindow(this, curFileName);
    editorWindow->show();

}

void MainWindow::fileRecieved(QString fileName) {
    qDebug() << "selected file: " << fileName;
    curFileName = fileName;
    this->setWindowTitle("MainWindow - " + curFileName);
    editButton->setDisabled(false);

}
MainWindow::~MainWindow()
{
    delete ui;
}




