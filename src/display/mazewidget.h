#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include "../maze/generator/generator.cpp"
#include "../maze/solver/solver.cpp"

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <QEventLoop>
#include <QCoreApplication>

#include <iostream>
#include <QTime>

using namespace std;

class MazeWidget : public QWidget {
public:
    void startDelay() {
        // Start the timer with the specified delay time
        timer->start(delayTime);
    }

    MazeSolver* mazeSolver;
    int** cells;
    QRect** rects;

    MazeWidget(int gridSize, int frameSize, QWidget *parent = nullptr) :
        gridSize(gridSize), frameSize(frameSize), QWidget(parent) {

        timer = new QTimer(this);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(50);

        this->cellUnit = frameSize / gridSize;

        this->mazeGenerator = new MazeGenerator(gridSize);
        this->mazeGenerator->generate();
        //this->mazeGenerator->print_adj();

        this->mazeSolver = new MazeSolver(this->mazeGenerator->getAdj(), gridSize);

        //create grid for cells
        this->cells = new int*[gridSize];
        for (int i = 0; i < gridSize; i++) {
            this->cells[i] = new int[gridSize];
        }

        for (int i=0; i<gridSize; i++) {
            for (int j=0; j<gridSize; j++) {
                this->cells[i][j] = 0;
            }
        }
        this->cells[0][0] = 1;
        this->cells[gridSize-1][gridSize-1] = 2;


        this->rects = new QRect*[gridSize];
        for (int i = 0; i < gridSize; i++) {
            this->rects[i] = new QRect[gridSize];
        }

        for (int i=0; i<gridSize; i++) {
            for (int j=0; j<gridSize; j++) {
                this->rects[i][j] = QRect(j*this->cellUnit+1, i*this->cellUnit+1, this->cellUnit-2, this->cellUnit-2);
            }
        }
    }

    void setGridSize(int size) { this->gridSize = size; };
    int getGridSize() { return this->gridSize; };

    void delay()
    {
        QTime dieTime= QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            cout << "waiting..." << endl;
        }
    }

public slots:
    void updateDelayed() {
        //QTimer::singleShot(1000, this, )
        //QTimer::singleShot(delayTime, this, &MazeWidget::update);
        //cout << "invoked update... " << endl;
        update();
        //delay();
        //timer->stop();
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QWidget::paintEvent(event);
        QPainter painter(this);

        painter.setPen(QPen(Qt::white, 0));
        painter.setBrush(QBrush(Qt::black));

        for (int i=0; i<gridSize; i++) {
            for (int j=0; j<gridSize; j++) {
                painter.setBrush(mapColor(cells[i][j]));
                painter.drawRect(this->rects[i][j]);
            }
        }

        painter.setPen(QPen(Qt::black, 4));
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

    QTimer* timer;
    int delayTime;

    MazeGenerator* mazeGenerator;

    QColor mapColor(int i) {
        switch (i) {
            case 0:
                return Qt::black;
            case 1:
                return QColor(20, 120, 20);
            case 2:
                return QColor(120, 20, 20);
            case 3:
                return Qt::blue;
            case 4:
                return Qt::red;
        }
    }
};
#endif //MAZEWIDGET_H
