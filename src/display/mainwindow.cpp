#include "mainwindow.h"
#include "mazewidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QPainter>

#include <iostream>

void MainWindow::setGridSize(int size) {
    this->gridSize = size;
}

int MainWindow::getGridSize() {
    return this->gridSize;
}


MainWindow::MainWindow(int gridSize, int frameSize, QWidget *parent) :
    gridSize(gridSize), frameSize(frameSize), QMainWindow(parent) {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    this->createLayout();
}

MazeWidget* MainWindow::createMazeWidget() {
    MazeWidget* mazeWidget = new MazeWidget(this->gridSize, this->frameSize, centralWidget);

    mazeWidget->setGridSize(this->gridSize);
    mazeWidget->setFixedSize(this->frameSize, this->frameSize);
    mazeWidget->setStyleSheet("background-color: black; border: 2px solid white;");

    return mazeWidget;
}


void MainWindow::createLayout() {
    QGridLayout *gridLayout = new QGridLayout(centralWidget);

    mazeWidget = this->createMazeWidget();

    QLabel *sizeLabel = new QLabel("Size:", centralWidget);
    sizeLineEdit = new QLineEdit(centralWidget);

    solveButton = new QPushButton("Solve", centralWidget);

    int alg_choice = 1;

    connect(solveButton, &QPushButton::clicked, [alg_choice, this]() {
        handleSolveClick(alg_choice);
    });


    gridLayout->addWidget(mazeWidget, 0, 0, 1, 2);
    gridLayout->addWidget(sizeLabel, 1, 0);
    gridLayout->addWidget(sizeLineEdit, 1, 1);
    gridLayout->addWidget(solveButton, 2, 0, 1, 2);
}

