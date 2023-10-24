#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include<sstream>
using namespace std;


QString readFileFromString() {
    fstream fileIO;
    fileIO.open("input.txt", ios::in);
    ostringstream ss;
    ss << fileIO.rdbuf();
    fileIO.close();
    return QString::fromStdString(ss.str());
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int ff;

    cout << "Reading from file...";
    cout << "";
    //cin >> ff;

    return a.exec();
}
