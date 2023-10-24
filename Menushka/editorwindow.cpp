#include "editorwindow.h"
#include "ui_editorwindow.h"

EditorWindow::EditorWindow(QWidget *parent, QString path) :
    QMainWindow(parent),
    ui(new Ui::EditorWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("EditorWindow - " + path);
    QAction * saveAction = new QAction("Save");
    ui->menubar->addAction(saveAction);

    connect(saveAction, &QAction::triggered, this, &EditorWindow::saveFile);


    fileName = path;

    fileIO.open(fileName.toStdString(), ios::out | ios::in);
    qDebug() << "File "<< path <<" status: " << fileIO.is_open();
    ui->textEdit->setText(readFileFromString());
    fileIO.close();


}

EditorWindow::~EditorWindow()
{
    delete ui;
}
void EditorWindow::saveFile() {
    fileIO.open(fileName.toStdString(), ios::out | ios::in | ios::trunc);
    fileIO << ui->textEdit->toPlainText().toStdString();
    fileIO.close();
    qDebug() << "File saved";
}

void EditorWindow::closeEvent(QCloseEvent *event) {
    saveFile();
}

void EditorWindow::collectStat() {


}
QString EditorWindow::readFileFromString() {
    ostringstream ss;
    ss << fileIO.rdbuf();
    return QString::fromStdString(ss.str());
}
