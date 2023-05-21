#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mazewidget.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(int gridSize, int frameSize, QWidget *parent = nullptr);
    int getGridSize();
    void setGridSize(int size);

public slots:
    void handleSolveClick(int alg) {
        this->mazeWidget->mazeSolver->solve(alg);
    }

private:
    int gridSize;
    int frameSize;

    QWidget *centralWidget;
    QLineEdit *sizeLineEdit;
    QPushButton *solveButton;
    MazeWidget *mazeWidget;

    void createLayout();
    MazeWidget* createMazeWidget();
};

#endif // MAINWINDOW_H