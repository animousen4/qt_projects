#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QWidgetAction>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include <QLabel>
#include "statcollectordialog.h"
#include "windowlinknames.h"
#include "helpwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidgetAction* comboAction = new QWidgetAction(this);
    textEdit = new QTextEdit();
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    textEdit->setLineWrapMode(QTextEdit::NoWrap);
    textEdit->setFixedHeight(200);
    comboAction->setDefaultWidget(textEdit);

    QWidgetAction* comboAction2 = new QWidgetAction(this);
    fileNameEdit = new QTextEdit();
    fileNameEdit->setMaximumHeight(30);
    //connect(fileNameEdit, &QTextEdit::textChanged, this, &MainWindow::onFileNameChanged);

    comboAction2->setDefaultWidget(fileNameEdit);

    QWidgetAction* comboAction3 = new QWidgetAction(this);
    QPushButton * calculateButton = new QPushButton();
    calculateButton->setText("Calculate");
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculate);
    comboAction3->setDefaultWidget(calculateButton);

    QWidgetAction* comboAction4 = new QWidgetAction(this);
    QLabel * writeLabel = new QLabel("Write a filename");
    comboAction4->setDefaultWidget(writeLabel);
    // Add the QWidgetAction to the QMenuBar

    QWidgetAction* comboAction5 = new QWidgetAction(this);

    QLabel * hyperTratata = new QLabel;
    hyperTratata->setFixedWidth(300);
    hyperTratata->setWordWrap(true);
    hyperTratata->setText(WindowLinkNames::text());
    hyperTratata->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(hyperTratata, &QLabel::linkActivated, this, &MainWindow::onLabelHelp);

    comboAction5->setDefaultWidget(hyperTratata);




    QMenu* fileMenu = this->ui->menubar->addMenu("File");
    fileMenu->addAction(comboAction4);
    fileMenu->addAction(comboAction2);
    fileMenu->addAction(comboAction3);

    editMenu = this->ui->menubar->addMenu("Edit");
    editMenu->setDisabled(true);
    editMenu->addAction(comboAction);

    QMenu* helpMenu = this->ui->menubar->addMenu("Help");
    helpMenu->addAction(comboAction5);

    //fileNameEdit->setText("f.txt");
    //calculateButton->click();



}
void MainWindow::calculate(){
    QString tFileName = this->fileNameEdit->toPlainText();
    if (tFileName.isEmpty()) {

        qDebug() << "FILENAME IS EMPTY!";
        editMenu->setDisabled(true);
    } else {
        QFile file(this->fileName);

        this->fileName = tFileName;
        editMenu->setDisabled(false);
        textEdit->setText(load());

        curDialog = new StatCollectorDialog(this, textEdit);
        curDialog->show();
        qDebug() << "FILENAME CHANGED: " << this->fileName;
    }
}


void MainWindow::onLabelHelp(const QString & link){
    qDebug() << "Opening '" + link + "' link";
    HelpWindow * hw = new HelpWindow(this, link);
    hw->show();

}


QString MainWindow::readFileFromString() {
    ostringstream ss;
    ss << fileIO.rdbuf();
    return QString::fromStdString(ss.str());
}


void MainWindow::closeEvent(QCloseEvent *event) {
    save();
}
void MainWindow::save(){
    fileIO.open(fileName.toStdString(), ios::out | ios::in | ios::trunc);
    fileIO << textEdit->toPlainText().toStdString();
    fileIO.close();
}

QString MainWindow::load(){
    fileIO.open(fileName.toStdString(), ios::out | ios::in);
    QString str = readFileFromString();
    fileIO.close();
    return str;
}

MainWindow::~MainWindow()
{
    delete ui;
}

