#include "TSMAntAlgorithmSolver.h"

namespace s21 {

    TSMAntAlgorithmSolver::TSMAntAlgorithmSolver(S21Matrix &matrix) : AbstractTSM(matrix) {
        this->matrix_ = matrix;
        count_of_nodes_ = matrix.get_rows();
        FillEmptyElements();
    }

    TSMAntAlgorithmSolver::pair TSMAntAlgorithmSolver::GetAnswer() {
        return shortest_path_;
    }

    void TSMAntAlgorithmSolver::PerformAntAlgorithm() {
        shortest_path_ = {{}, -1.0};
        pheromones_ = pheromones_delta_ = event_ = S21Matrix(count_of_nodes_, count_of_nodes_);
        for (int i = 0; i < matrix_.get_rows(); i++) {
            for (int j = 0; j < matrix_.get_cols(); j++) {
                if (matrix_(i, j) != 0.0) {
                    pheromones_(i, j) = 0.2;
                }
            }
        }
        for (size_t iteration = 0; iteration < 1; iteration++) {
            if (iteration > 0) {
                ApplyDeltaToPheromones();
            }
            pair cur_path = AntColonyAlgorithm();
            if (iteration >= 0 && shortest_path_.second == -1.0 || cur_path.second < shortest_path_.second) {
                shortest_path_ = cur_path;
            }
        }
        for (int i = 0; i < shortest_path_.first.size(); i++) {
            shortest_path_.first[i]++;
        }
    }

    void TSMAntAlgorithmSolver::ApplyDeltaToPheromones() {
        const double vape = 0.5;
        for (int i = 0; i < matrix_.get_rows(); i++) {
            for (int j = 0; j < matrix_.get_cols(); j++) {
                if (matrix_(i, j) != 0.0) {
                    pheromones_(i, j) = vape * pheromones_(i, j) + pheromones_delta_(i, j);
                }
            }
        }
    }
//#include <iostream>
    TSMAntAlgorithmSolver::pair TSMAntAlgorithmSolver::AntColonyAlgorithm() {
        const int ants = 200;
        for (int i = 0; i < ants; i++) {
            std::vector<int> ants_path(ants), visited;
            std::set<int> available_nodes;
            for (int i = 0; i < count_of_nodes_; i++)
                available_nodes.insert(i);
            int current_pos = 0;
            while (true) {
                visited.push_back(current_pos);
                for (auto iter : visited) {
                    printf("%d ", iter);
//                    std::cout << iter << "\n";
                }
                printf("\n");
                available_nodes.erase(current_pos);
                if (available_nodes.size() == 0)
                    break;
                event_.FillWithDigit(0.0);
                for (int j = 1; j < count_of_nodes_ && available_nodes.size() > 1; j++) {
                    if (matrix_(current_pos, j) != 0.0) {
                        event_(current_pos, j) = GetEventPossibility(current_pos, j, available_nodes);
                    }
                }
                int old_pos = current_pos;
                current_pos = GetNextNode(current_pos, available_nodes);
                ants_path[i] += matrix_(old_pos, current_pos);
            }
            IncreaseDelta(ants_path[i], visited);
        }
        return GetFullPath();
    }

    double TSMAntAlgorithmSolver::GetEventPossibility(int rows, int cols, std::set<int> &nodes) {
        double denominator = 0.0;
        for (auto iterator : nodes) {
            if (matrix_(rows, iterator) != 0.0) {
                denominator += pheromones_(rows, iterator) * (1.0 / matrix_(rows, iterator));
            }
        }
        double nominator = pheromones_(rows, cols) * (1.0 / matrix_(rows, cols));
        return (nominator / denominator);
    }

    int TSMAntAlgorithmSolver::GetNextNode(int cur_pos, std::set<int> &nodes) {
        if (nodes.size() == 1) {
            return *(nodes.begin());
        }
        std::vector<double> event_vec;
        double sum = 0.0;
        for (int j = 0; j < matrix_.get_rows(); j++) {
            if (matrix_(cur_pos, j) != 0.0 && nodes.find(j) != nodes.end()) {
                sum += event_(cur_pos, j);
                event_vec.push_back(sum);
            } else {
                event_vec.push_back(0.0);
            }
        }
        int ind = -1;
        double random_value = (double)rand() / (RAND_MAX);
        for (int j = 0; j < event_vec.size(); j++) {
            if (event_vec[j] != 0.0 && (event_vec[j] > random_value &&
                (ind == -1 || random_value > LastPositiveEvent(event_vec, j)))) {
                ind = j;
            }
        }
        return ind;
    }

    double TSMAntAlgorithmSolver::LastPositiveEvent(std::vector<double> &event_vec, int j) {
        j--;
        while (j >= 0 && event_vec[j] == 0.0) {
            j--;
        }
        return event_vec[j];
    }

    void TSMAntAlgorithmSolver::IncreaseDelta(int path_of_cur, std::vector<int> &visited) {
        int last_ind = visited[0];
        const double Q = 10.0;
        for (int i = 1; i < visited.size(); i++) {
            pheromones_delta_(last_ind, visited[i]) += Q / path_of_cur;
            last_ind = visited[i];
        }
    }

    TSMAntAlgorithmSolver::pair TSMAntAlgorithmSolver::GetFullPath() {
        double cur_path = 0;

        std::vector<int> visited = { 0 };
        S21Matrix available(pheromones_);
        int cur_pos = 0;
        while (visited.size() < matrix_.get_cols()) {
            int max = -1;
            for (int i = 0; i < matrix_.get_cols(); i++) {
                if (available(cur_pos, i) > 0.0 &&
                    (max == -1 || available(cur_pos, i) > available(cur_pos, max) ||
                     available(i, cur_pos) > available(cur_pos, max))) {
                    max = i;
                }
            }
            cur_path += matrix_(cur_pos, max);
            available(cur_pos, max) = 0.0;
            cur_pos = max;
            visited.push_back(max);
        }

        // Reversed path from last visited node to home
        pair reversed = GetShortestPath(visited.back() + 1, 1);
        for (int i = reversed.first.size() - 2; i >= 0; i--) {
            visited.push_back(reversed.first[i]);
        }
        cur_path += reversed.second;
        return std::make_pair(visited, cur_path);
    }

    TSMAntAlgorithmSolver::pair TSMAntAlgorithmSolver::GetShortestPath(int vertex1, int vertex2) {
        int size = matrix_.get_rows();
        std::vector<int> pos(size), node(size), parent(size);
        int big_number = std::numeric_limits<int>::max();
        for (int i = 0; i < size; ++i) {
            pos[i] = big_number;
            node[i] = 0;
            parent[i] = -1;
        }

        int min = 0, index_min = 0;
        pos[vertex1 - 1] = 0;
        for (int i = 0; i < size; ++i) {
            min = big_number;
            for (int j = 0; j < size; ++j) {
                if (!node[j] && pos[j] < min) {
                    min = pos[j];
                    index_min = j;
                }
            }
            node[index_min] = 1;
            for (int j = 0; j < size; ++j) {
                if (!node[j] && matrix_(index_min, j) && pos[index_min] != big_number &&
                    pos[index_min] + matrix_(index_min, j) < pos[j]) {
                    pos[j] = pos[index_min] + matrix_(index_min, j);
                    parent[j] = index_min;
                }
            }
        }

        std::vector<int> temp;
        for (int i = vertex2 - 1; i != -1; i = parent[i]) {
            temp.push_back(i);
        }
        return std::make_pair(temp, pos[vertex2 - 1]);
    }
}
