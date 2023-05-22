#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mazewidget.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(int gridSize, int frameSize, QWidget *parent = nullptr);
    int getGridSize();
    void setGridSize(int size);

public slots:
    void handleSolveClick(int alg) {
        MazeWidget* widget = this->mazeWidget;

        this->mazeWidget->mazeSolver->solve(
                alg,
                this->mazeWidget->cells,
                [widget]() {widget->startDelay();}
        );
    }

private:
    int gridSize;
    int frameSize;
    int cellUnit;

    QWidget *centralWidget;
    QLineEdit *sizeLineEdit;
    QPushButton *solveButton;
    MazeWidget *mazeWidget;

    void createLayout();
    MazeWidget* createMazeWidget();
};

#endif // MAINWINDOW_H