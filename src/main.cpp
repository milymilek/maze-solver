#include <iostream>
#include <string>

#include <QApplication>
#include <QPicture>
#include <QLabel>
#include "display/mainwindow.h"

using namespace std;

void paintSolveStep(QPainter* painter) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::black, 12));
    painter->fillRect(0, 0, 20, 20, Qt::red);
    painter->end(); // Don't forget this line!
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QStringList arguments = QApplication::arguments();

    string size_str = arguments[1].toStdString();
    int size = stoi(size_str);

    MainWindow mainWindow(size, 400);
    mainWindow.show();
//
//    QPicture pi;
//    QPainter painter(&pi);
//    paintSolveStep(&painter);
//
//    QLabel l;
//    l.setPicture(pi);
//    l.show();

    return app.exec();
}
