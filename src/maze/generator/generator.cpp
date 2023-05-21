#include <iostream>
#include <random>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <algorithm>

using namespace std;

class MazeGenerator {
private:
    int size;
    int n_vertices;
    int** adjMatrix;

    int** init_matrix(int n_vertices) {
        int** matrix = new int*[n_vertices];

        for (int i = 0; i < n_vertices; i++) {
            matrix[i] = new int[n_vertices];
        }

        for (int i=0; i<n_vertices; i++) {
            for (int j=0; j<n_vertices; j++) {
                matrix[i][j] = 0;
            }
        }
        return matrix;
    }

public:
    MazeGenerator(int size) : size(size) {
        this->n_vertices = this->size * this->size;
        this->adjMatrix = this->init_matrix(this->n_vertices);
        srand(0);
    }


    int getSize() {
        return this->size;
    }

    int** getAdj() {
        return this->adjMatrix;
    }

    int getAdj(int n, int m) {
        return this->adjMatrix[n][m];
    }

    static bool isEdge(int n, int v, int size) {
        //cout << "n: " << n << " v: " << v << " size: " << size << " 1st: " << ((!v%size) && (v-1)==n) << " 2nd: " << ((!((v+1)%size)) && (v+1)==n) << endl;
        return (n < 0 || n >= size*size || (!(v%size) && (v-1)==n) || (!((v+1)%size) && (v+1)==n));
    }

    std::vector<int> getNeighbors(int v) {
        int size = this->size;

        std::vector<int> neighbors = {v-1, v+1, v-size, v+size};

        neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(), [v, size](int n) {
            return MazeGenerator::isEdge(n, v, size);
        }), neighbors.end());

        random_device rd;
        //mt19937 generator(rd());
        mt19937 generator(42);
        shuffle(neighbors.begin(), neighbors.end(), generator);

        return neighbors;
    }

    void DFS(int* visited, int v) {
        visited[v] = 1;
        //cout << "V: " << v << endl;
        std::vector<int> neighbors = this->getNeighbors(v);

//        cout << "Neighbors(v): ";
//        for (const auto& element : neighbors) {
//            std::cout << element << " ";
//        }
//        std::cout << std::endl;

        for (const auto& n : neighbors) {
            if (!visited[n]) {
                this->adjMatrix[v][n] = 1;
                this->adjMatrix[n][v] = 1;
                DFS(visited, n);
            }
        }

    }

    void generate() {
        int* visited = new int[this->n_vertices];
        for (int i=0; i<this->n_vertices; i++) {
            visited[i] = 0;
        }

        int v = rand() % this->n_vertices;
        //int v = 0;

        DFS(visited, v);



//        this->adjMatrix[0][1] = 1;
//        this->adjMatrix[1][4] = 1;
//        this->adjMatrix[4][5] = 1;
//        this->adjMatrix[5][8] = 1;
//
//        this->adjMatrix[1][0] = 1;
//        this->adjMatrix[4][1] = 1;
//        this->adjMatrix[5][4] = 1;
//        this->adjMatrix[8][5] = 1;
    }

    void print_adj() {
        for (int i=0; i<this->n_vertices; i++) {
            for (int j=0; j<this->n_vertices; j++) {
                std::cout << adjMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};
