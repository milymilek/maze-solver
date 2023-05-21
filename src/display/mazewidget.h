#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include "../maze/generator/generator.cpp"
#include "../maze/solver/solver.cpp"

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

#include <iostream>
using namespace std;

class MazeWidget : public QWidget {
public:
    MazeSolver* mazeSolver;

    MazeWidget(int gridSize, int frameSize, QWidget *parent = nullptr) :
        gridSize(gridSize), frameSize(frameSize), QWidget(parent) {

        this->cellUnit = frameSize / gridSize;

        this->mazeGenerator = new MazeGenerator(gridSize);
        this->mazeGenerator->generate();
        this->mazeGenerator->print_adj();

        this->mazeSolver = new MazeSolver(this->mazeGenerator->getAdj(), gridSize);
        cout << "GRID SIZE: " << this->mazeGenerator->getSize() << endl;
        //this->mazeSolver->solve(1);
    }

    void setGridSize(int size) { this->gridSize = size; };
    int getGridSize() { return this->gridSize; };

protected:
    void paintEvent(QPaintEvent *event) override {
        QWidget::paintEvent(event);

        QPainter painter(this);

        // Set the pen properties for drawing the lines
        QPen pen(Qt::white);
        pen.setWidth(2);
        painter.setPen(pen);

        // Draw horizontal lines
        int y = this->cellUnit;
        for (int i = 0; i < this->gridSize; ++i) {
            painter.drawLine(0, y, width(), y);
            y += this->cellUnit;
        }

        // Draw vertical lines
        int x = this->cellUnit;
        for (int i = 0; i < this->gridSize; ++i) {
            painter.drawLine(x, 0, x, height());
            x += this->cellUnit;
        }

        // Fill start and end of maze
        painter.fillRect(2, 2, this->cellUnit-4, this->cellUnit-4, QColor(20, 120, 20));
        painter.fillRect((this->gridSize-1) * this->cellUnit + 2, (this->gridSize-1) * this->cellUnit + 2,
                         this->cellUnit - 4, this->cellUnit - 4, QColor(120, 20, 20));


        QPen pen2(Qt::black);
        pen2.setWidth(2);
        painter.setPen(pen2);


        int n_vertices = this->gridSize * this->gridSize;
        int n1, m1, n2, m2, n_max, m_max;

        for (int i=0; i<n_vertices; i++) {
            for (int j=0; j<n_vertices; j++) {
                if (i != j && (this->mazeGenerator->getAdj(i, j))) {
                    n1 = i / this->gridSize;
                    m1 = i % this->gridSize;
                    n2 = j / this->gridSize;
                    m2 = j % this->gridSize;
                    //cout << "i: " << i << " j: " << j << " n1m1: (" << n1 << ", " << m1 << ") n2m2: (" << n2 << ", " << m2 << ")\n";
                    if (abs(n1-n2)){
//                        cout << n1 * this->cellUnit << " " << m1 * this->cellUnit << " " <<
//                                (n1+1) * this->cellUnit << " " << m1 * this->cellUnit << endl;
                        n_max = max(n1, n2);
                        painter.drawLine(m1 * this->cellUnit, n_max * this->cellUnit,
                                         (m1+1) * this->cellUnit, n_max * this->cellUnit);
                    }
                    else if (abs(m1-m2)) {
//                        cout << m2 * this->cellUnit << " " << n1 * this->cellUnit << " " <<
//                             m2 * this->cellUnit << " " << (n1+1) * this->cellUnit << endl;
                        m_max = max(m1, m2);
                        painter.drawLine(m_max * this->cellUnit, n1 * this->cellUnit,
                                         m_max * this->cellUnit, (n1+1) * this->cellUnit);
                    }
                }
            }
        }
    }

private:
    int gridSize;
    int frameSize;
    int cellUnit;

    MazeGenerator* mazeGenerator;
};
#endif //MAZEWIDGET_H
