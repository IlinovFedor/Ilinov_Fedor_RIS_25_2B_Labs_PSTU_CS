#include "Graph.h"

#include <random>

// Один раз объяви генератор (можно как член класса или static внутри функции)
static std::mt19937 rng(std::random_device{}());

Graph::Graph(const Graph &other) {
    set_matrix(other.matrix);
}

Graph::~Graph() {
    clear_matrix();
}

void Graph::clear_matrix() {
    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix[i].size(); j++)
            if (matrix[i][j] != nullptr)
                delete matrix[i][j];

    matrix.clear();
}

Graph &Graph::operator=(const Graph &other) {
    if (this == &other)
        return *this;

    set_matrix(other.matrix);

    return *this;
}

const std::vector<std::vector<int *> > &Graph::get_matrix() {
    return matrix;
}

void Graph::set_matrix(const std::vector<std::vector<int *> > &new_matrix) {
    clear_matrix();

    matrix.resize(new_matrix.size());
    for (int i = 0; i < new_matrix.size(); i++)
        for (int j = 0; j < new_matrix[i].size(); j++)
            if (new_matrix[i][j] == nullptr)
                matrix[i].push_back(nullptr);
            else
                matrix[i].push_back(new int(*new_matrix[i][j]));
}

bool Graph::is_visual_tree() {
    int n = matrix.size();
    if (n == 0) return false;

    // Считаем рёбра как неориентированные пары
    int edgeCount = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (matrix[i][j] != nullptr || matrix[j][i] != nullptr)
                edgeCount++;

    // Условие E = V - 1
    if (edgeCount != n - 1) return false;

    // Проверяем связность через BFS по неориентированному графу
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    q.push(0);
    visited[0] = true;
    int visitedCount = 1;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int next = 0; next < n; next++) {
            if (!visited[next] &&
                (matrix[cur][next] != nullptr || matrix[next][cur] != nullptr)) {
                visited[next] = true;
                visitedCount++;
                q.push(next);
            }
        }
    }

    return visitedCount == n;
}

void Graph::generateRandom(int n, int maxWeight, double edgeProbability) {
    // Очищаем матрицу
    for (auto &row: matrix)
        for (auto *p: row)
            delete p;

    matrix.assign(n, std::vector<int *>(n, nullptr));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            std::bernoulli_distribution edge_dist(edgeProbability);
            if (edge_dist(rng)) {
                std::uniform_int_distribution<int> weight_dist(1, maxWeight);
                matrix[i][j] = new int(weight_dist(rng));
            }
        }
    }
}

void Graph::generateTree(int n, int maxWeight) {
    for (auto &row: matrix)
        for (auto *p: row)
            delete p;

    matrix.assign(n, std::vector<int *>(n, nullptr));

    // Перемешиваем порядок вершин
    std::vector<int> perm(n);
    for (int i = 0; i < n; i++) perm[i] = i;
    for (int i = n - 1; i > 0; i--) {
        std::uniform_int_distribution<int> idx_dist(0, i);
        int j = idx_dist(rng);
        std::swap(perm[i], perm[j]);
    }

    // Для каждой вершины (кроме первой) подключаем к случайному
    // уже добавленному узлу — гарантирует связность и отсутствие циклов
    for (int i = 1; i < n; i++) {
        int parent = perm[std::rand() % i];
        int child = perm[i];
        std::uniform_int_distribution<int> weight_dist(1, maxWeight);
        matrix[parent][child] = new int(weight_dist(rng));
    }
}

int Graph::size() {
    return matrix.size();
}

bool Graph::has_edge(int i, int j) {
    return matrix[i][j];
}

int *Graph::get_weight(int i, int j) {
    return matrix[i][j];
}
