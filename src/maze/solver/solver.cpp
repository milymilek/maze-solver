#include <vector>
#include <string>
#include <algorithm>
#include <QWidget>
#include <QCoreApplication>
#include <QEventLoop>
#include <QTimer>
#include <iostream>

using namespace std;

class MazeSolver {
private:
    int **maze;
    int size;
    int n_vertices;
    QEventLoop loop;

public:
    MazeSolver(int **maze, int size) : maze(maze), size(size) {
        this->n_vertices = this->size * this->size;
    }

    void DFS(int **maze, int* visited, int v, std::vector<int>* stack, std::vector<int>* path) {
        stack->push_back(v);
        visited[v] = 1;

        if (v == this->n_vertices-1) {
            path->insert(path->end(),
                         std::make_move_iterator(stack->rbegin()),
                         std::make_move_iterator(stack->rend()));
            return;
        }

        for (int n=0; n<this->n_vertices; n++) {
//            cout << "Maze[" << v << "]: ";
//            for (int z=0;z<16;z++) {
//                std::cout << maze[v][z] << " ";
//            }
//            std::cout << std::endl;
//            cout << "Visited: ";
//            for (int z=0;z<16;z++) {
//                std::cout << visited[z] << " ";
//            }
//            std::cout << std::endl;
            if (maze[v][n] && !visited[n]) {
                DFS(maze, visited, n, stack, path);
            }
        }
        stack->pop_back();
    }

    void DFS_visualize(int **maze, int* visited, int v, std::vector<int>* stack,
                       std::vector<int>* path, int** colors, std::function<void()> updt) {
        stack->push_back(v);
        visited[v] = 1;
        colors[v / size][v % size] = 3;
        //cout << "i: " << v / size << " j: " << v % size << endl;
//        widget->shouldPaint = true;
        //QThread::msleep(2000);

        if (v == this->n_vertices-1) {
            path->insert(path->end(),
                         std::make_move_iterator(stack->rbegin()),
                         std::make_move_iterator(stack->rend()));
            //cout << "path: ";
            for (const auto& element : *path) {
                //std::cout << element << " " << endl;
                colors[element / size][element % size] = 4;

//                for (int i=0; i<size; i++) {
//                    for (int j = 0; j < size; j++) {
//                        cout << colors[i][j] << " ";
//                    }
//                    cout << endl;
//                }

                //updt();

                QTimer::singleShot(50, &loop, SLOT(quit()));
                loop.exec();
                //QCoreApplication::processEvents(QEventLoop::AllEvents);
            }
            std::cout << std::endl;
            return;
        }

        for (int n=0; n<this->n_vertices; n++) {
            if (maze[v][n] && !visited[n]) {
                DFS_visualize(maze, visited, n, stack, path, colors, updt);
            }
        }
        stack->pop_back();
    }

    void Dijkstra(int **maze, int v, std::vector<int>* path) {
        ;
    }

    void solve(int alg, int** colors, std::function<void()> updt) {
        std::vector<int> path;
        std::vector<int> stack;

        int* visited = new int[this->n_vertices];
        for (int i=0; i<this->n_vertices; i++) {
            visited[i] = 0;
        }

        switch (alg) {
            case 1:
                DFS_visualize(maze, visited, 0, &stack, &path, colors, updt);
                break;
            case 2:
                Dijkstra(maze, 0, &path);
                break;
            default:
                std::cout << "Invalid algorithm chosen..." << std::endl;
                break;
        }
    }
};
