#include <iostream>
#include <string>

#include <QApplication>
#include "display/mainwindow.h"

using namespace std;



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QStringList arguments = QApplication::arguments();

    string size_str = arguments[1].toStdString();
    int size = stoi(size_str);

    MainWindow mainWindow(size, 400);
    mainWindow.show();

    return app.exec();
}
