#ifndef PRETTYBLOC_H
#define PRETTYBLOC_H

#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <mcl.h>
#include <TableModels.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
template<class T>
class PrettyBloc : public QWidget
{
public:
    PrettyBloc(QWidget *parent) : QWidget(parent) {
        QHBoxLayout * mainLayout = new QHBoxLayout();
        QVBoxLayout * panelLayout = new QVBoxLayout();

        QHBoxLayout * searchLayout = new QHBoxLayout();
        s1 = new T();
        s2 = new T();
        m = new T();

        loadButton = new QPushButton("Load");
        sortButton = new QPushButton("Sort");
        mergeButton = new QPushButton("Merge");
        toFileButton = new QPushButton("To file");
        searchButton = new QPushButton("Search");


        fileEdit1 = new QLineEdit("file1.txt");
        fileEdit2 = new QLineEdit("file2.txt");
        searchLineEdit = new QLineEdit();


        panelLayout->addWidget(fileEdit1);
        panelLayout->addWidget(fileEdit2);

        panelLayout->addWidget(loadButton);
        panelLayout->addWidget(mergeButton);
        panelLayout->addWidget(sortButton);
        panelLayout->addWidget(toFileButton);


        searchLayout->addWidget(searchButton);
        searchLayout->addWidget(searchLineEdit);

        panelLayout->addLayout(searchLayout);

        mainLayout->addLayout(panelLayout);

        table1 = new QTableView();
        table2 = new QTableView();
        mergeTable = new QTableView();

        mainLayout->addWidget(table1);
        mainLayout->addWidget(table2);
        mainLayout->addWidget(mergeTable);

        this->setLayout(mainLayout);

        connect(loadButton, &QPushButton::clicked, this, [this](){
            QFile file(fileEdit1->text());
            s1->fromText(file);

            QFile file2(fileEdit2->text());
            s2->fromText(file2);

            update();

        });

        connect(sortButton, &QPushButton::clicked, this, [this](){
            s1->Sort();
            s2->Sort();
            m->Sort();

            update();

        });

        connect(mergeButton, &QPushButton::clicked, this, [this](){
            m->merge(s1, s2);
            update();
        });

        connect(toFileButton, &QPushButton::clicked, this, [this](){
            QFile outputFile("output.txt");
            m->toText(outputFile);
        });

        connect(searchButton, &QPushButton::clicked, this, [this](){
            QString data = m->findData(searchLineEdit->text());

            QMessageBox * messageBox = new QMessageBox(this);
            messageBox->setText(data);
            messageBox->show();
        });
    }

    ABS_COMP * s1;
    ABS_COMP * s2;
    ABS_COMP * m;

    QPushButton * loadButton;
    QPushButton * sortButton;
    QPushButton * mergeButton;
    QPushButton * toFileButton;
    QPushButton * searchButton;
    QLineEdit * searchLineEdit;

    QLineEdit * fileEdit1;
    QLineEdit * fileEdit2;

    QTableView * table1;
    QTableView * table2;
    QTableView * mergeTable;

    void update(QAbstractTableModel * t1, QAbstractTableModel * t2, QAbstractTableModel * m);
    void update() {
        QAbstractTableModel * model1 = new PrettyTableModel(this, s1->getItems());
        table1->setModel(model1);

        QAbstractTableModel * model2 = new PrettyTableModel(this, s2->getItems());
        table2->setModel(model2);

        QAbstractTableModel * model3 = new PrettyTableModel(this, m->getItems());
        mergeTable->setModel(model3);
    }
    void setupWidget();
    //virtual void update();
signals:

};


#endif // PRETTYBLOC_H
