#include "GraphAlgorithms.h"

namespace s21 {

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
    S21Matrix matrix = graph.GetMatrix();
    const int length = matrix.get_cols(), ants = 200;
    std::vector<int> ants_path(ants);
    if (length < 2) {
        return TsmResult({}, Status::OUT_OF_RANGE);
    }
//    const double Q = GetQConst(matrix);
    const double Q = 10.0;
    pheromones_ = pheromones_delta_ = event_ = S21Matrix(length, length);
    for (int i = 0; i < matrix.get_rows(); i++) {
        for (int j = 0; j < matrix.get_cols(); j++) {
            if (matrix(i, j) != 0.0) {
                pheromones_(i, j) = 0.2;
            }
        }
    }
    for (size_t iteration = 0; iteration < 1; iteration++) {
        if (iteration > 0) {
            ApplyDeltaToPheromones(matrix);
        }
        for (int i = 0; i < ants; i++) {
            std::set<int> available_nodes;
            std::vector<int> visited;
            for (int i = 0; i < length; i++)
                available_nodes.insert(i);
            int current_pos = 0;
            while (true) {
                event_.FillWithDigit(0.0);
                visited.push_back(current_pos);
                available_nodes.erase(current_pos);
                if (available_nodes.size() == 0)
                    break;
                for (int j = 1; j < length && available_nodes.size() > 1; j++) {
                    if (matrix(current_pos, j) != 0.0) {
                        event_(current_pos, j) = GetEventPossibility(matrix, current_pos, j, available_nodes);
                    }
                }
                int old_pos = current_pos;
                current_pos = GetNextNode(matrix, current_pos, available_nodes);
                ants_path[i] += matrix(old_pos, current_pos);
            }
            IncreaseDelta(matrix, ants_path[i], Q, visited);
//            for (auto iter : visited) {
//                std::cout << iter << "\n";
//            }
//            std::cout << "\n";
        }
    }
//    for (int )
    for (int i = 0; i < matrix.get_rows(); i++) {
        for (int j = 0; j < matrix.get_cols(); j++) {
            printf("%.4f\t", pheromones_delta_(i, j));
        }
        std::cout << "\n";
    }
}

void GraphAlgorithms::IncreaseDelta(S21Matrix &matrix, int path_of_cur, const double Q, std::vector<int> &visited) {
    int last_ind = visited[0];
    for (int i = 1; i < visited.size(); i++) {
        pheromones_delta_(last_ind, visited[i]) += Q / path_of_cur;
        last_ind = visited[i];
    }
}

void GraphAlgorithms::ApplyDeltaToPheromones(S21Matrix &matrix) {
    const double vape = 0.5;
    for (int i = 0; i < matrix.get_rows(); i++) {
        for (int j = 0; j < matrix.get_cols(); j++) {
            if (matrix(i, j) != 0.0) {
                pheromones_(i, j) = vape * pheromones_(i, j) + pheromones_delta_(i, j);
            }
        }
    }
}

/**
 * @brief Gets an event possibility of moving to the position by rows and cols in matrix
 */
double GraphAlgorithms::GetEventPossibility(S21Matrix &matrix, int rows, int cols, std::set<int> &nodes) {
    double denominator = 0.0;
    for (auto iterator : nodes) {
        if (matrix(rows, iterator) != 0.0) {
            denominator += pheromones_(rows, iterator) * (1.0 / matrix(rows, iterator));
        }
    }
    double nominator = pheromones_(rows, cols) * (1.0 / matrix(rows, cols));
    return (nominator / denominator);
}

    double GraphAlgorithms::LastPositiveEvent(std::vector<double> &event_vec, int j) {
        j--;
        while (j >= 0 && event_vec[j] == 0.0) {
            j--;
        }
        return event_vec[j];
    }

    int GraphAlgorithms::GetNextNode(S21Matrix &matrix, int cur_pos, std::set<int> &nodes) {
        if (nodes.size() == 1) {
            return *(nodes.begin());
        }
        std::vector<double> event_vec;
        double sum = 0.0;
        for (int j = 0; j < matrix.get_rows(); j++) {
            if (matrix(cur_pos, j) != 0.0 && nodes.find(j) != nodes.end()) {
                sum += event_(cur_pos, j);
                event_vec.push_back(sum);
            } else {
                event_vec.push_back(0.0);
            }
        }
        int ind = -1;
        double random_value = ((double)rand() / (RAND_MAX));
        for (int j = 0; j < event_vec.size(); j++) {
            if (event_vec[j] != 0.0 && (event_vec[j] > random_value &&
                                        (ind == -1 || random_value > LastPositiveEvent(event_vec, j)))) {
                ind = j;
            }
        }
        return ind;
    }

    double GraphAlgorithms::GetQConst(S21Matrix &matrix) {
        double min = -1.0;
        for (int i = 0; i < matrix.get_rows(); i++) {
            for (int j = 0; j < matrix.get_cols(); j++) {
                if (matrix(i, j) != 0.0 && (min > matrix(i, j) || min == -1.0)) {
                    min = matrix(i, j);
                }
            }
        }
        return (min * 4.0 / 10.0);
    }

// Might be useful if we're going to do the bonus part
//
//#include <algorithm>
//TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
//    S21Matrix matrix = graph.GetMatrix();
//    std::vector<int> vertex, min_path;
//    for (int i = 1; i < matrix.get_cols(); ++i) {
//        vertex.push_back(i);
//    }
//    int min_weight = std::numeric_limits<int>::max();
//    while (std::next_permutation(vertex.begin(), vertex.end())) {
//        int cur_weight = 0;
//        std::vector<int> cur_path;
//        int k = 0;
//        for (size_t i = 0; i < vertex.size(); i++) {
//            cur_weight += matrix(k, vertex[i]);
//            cur_path.push_back(k);
//            k = vertex[i];
//        }
//        cur_weight += matrix(k, 0);
//        cur_path.push_back(k);
//        if (min_weight > cur_weight) {
//            min_weight = cur_weight;
//            min_path = cur_path;
//        }
//    }
//    min_path.push_back(0);
//    return TsmResult(min_path, min_weight);
//}


std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph, int start_vertex) {
    std::vector<int> result = std::vector<int>();
    if (graph.GetMatrix().get_cols() == 0) {
        result.push_back(Status::EMPTY_GRAPH_ERROR);
        return result;
    }
    S21Matrix& matrix = graph.GetMatrix();
    if (start_vertex > matrix.get_cols() || start_vertex <= 0) {
        result.push_back(Status::WRONG_VERTEX_NUMBER);
        return result;
    }

    std::vector<bool> visited = std::vector<bool>(matrix.get_cols() + 1, false);
    Stack stack = Stack::init();
    stack.push(start_vertex);

    while (!stack.empty()) {
        int current_vertex = stack.pop();
        if (!visited[current_vertex]) {
            result.push_back(current_vertex);
            visited[current_vertex] = true;
        }
        visited[current_vertex] = true;
        for (int i = matrix.get_cols() - 1; i >= 0; i--) {
            if (matrix(current_vertex - 1, i) && !visited[i + 1]) {
                stack.push(i + 1);
            }
        }
    }

    return result;
}

void GraphAlgorithms::debug_print_vector(std::vector<int> vector) {
    printf("Result vector: ");
    for (long unsigned i = 0; i < vector.size(); i++) {
        printf("%d ", vector.at(i));
    }
    printf("\n");
}

void GraphAlgorithms::debug_print_stack(Stack stack) {
    printf("Stack: ");
    while (!stack.empty()) {
        printf("%d ", stack.pop());
    }
    printf("\n");
}


}  // namespace s21