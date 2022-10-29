#include "GraphAlgorithms.h"

namespace s21 {

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
    S21Matrix matrix = graph.GetMatrix();
    const int length = matrix.get_cols(), ants = length;
    if (length < 2) {
        return TsmResult({}, Status::OUT_OF_RANGE);
    }
    const double Q = GetQConst(matrix);
    pheromones_ = pheromones_delta_ = S21Matrix(length, length);
    pheromones_.FillWithDigit(0.2);  // default concentration of pheromones
    for (int i = 0; i < ants; i++) {
        event_ = S21Matrix(length, length);
        std::set<int> available_nodes, visited;
        for (int i = 0; i < length; i++)
            available_nodes.insert(i);
        int current_pos = 0;
        if (i != 0) {
            ApplyDeltaToPheromones(matrix);
        }
        while (available_nodes.size() > 0) {
            for (int j = 0; j < length; j++) {
                if (matrix(current_pos, j) != 0) {
                    pheromones_delta_(current_pos, j) += Q / matrix(current_pos, j);
                    event_(current_pos, j) = GetEventPossibility(matrix, current_pos, j, available_nodes);
                    std::cout << event_(current_pos, j) << "\n";
                }
            }
            std::cout << "\n";
            available_nodes.erase(current_pos);
            visited.insert(current_pos);
            current_pos = GetNextNode(matrix, current_pos, visited);
        }
        std::cout << "End of one iteration\n\n";
    }
//    for (int i = 0; i < matrix.get_rows(); i++) {
//        for (int j = 0; j < matrix.get_cols(); j++) {
//            std::cout << pheromones_(i, j) << ' ';
//        }
//        std::cout << "\n";
//    }
}

double GraphAlgorithms::GetQConst(S21Matrix &matrix) {
    double min = -1.0;
    for (int i = 0; i < matrix.get_rows(); i++) {
        for (int j = 0; j < matrix.get_cols(); j++) {
            if (matrix(i, j) != 0.0 && (min > matrix(i, j) || min == -1.0)) {
                min = static_cast<double>(matrix(i, j));
            }
        }
    }
    return (min * 4.0 / 10.0);
}

void GraphAlgorithms::ApplyDeltaToPheromones(S21Matrix &matrix) {
    const double vape = 0.5;
    double delta_sum = 0.0;
    for (int i = 0; i < matrix.get_rows(); i++) {
        for (int j = 0; j < matrix.get_cols(); j++) {
            if (matrix(i, j) != 0) {
                delta_sum += pheromones_delta_(i, j);
            }
        }
    }
    for (int i = 0; i < matrix.get_rows(); i++) {
        for (int j = 0; j < matrix.get_cols(); j++) {
            if (matrix(i, j) != 0) {
                pheromones_(i, j) = vape * pheromones_(i, j) + delta_sum;
            }
        }
    }
}

int GraphAlgorithms::GetNextNode(S21Matrix &matrix, int cur_pos, std::set<int> visited) {
    double random_value = ((double)rand() / (RAND_MAX)) + 1;
    int ind = -1;
    for (int j = 1; j < matrix.get_cols(); j++) {
        if (matrix(cur_pos, j) != 0 &&
            (ind == -1 || (abs(event_(cur_pos, j) - random_value) < abs(event_(cur_pos, ind) - random_value))) &&
            visited.find(j) == visited.end()) {
            ind = j;
        }
    }
    return ind;
}

/**
 * @brief Gets an event possibility of moving to the position by rows and cols in matrix
 */
double GraphAlgorithms::GetEventPossibility(S21Matrix &matrix, int rows, int cols, std::set<int> nodes) {
    double denominator = 0.0;
    if (nodes.size() == 1) {
        return (1.0);
    }
    for (auto iterator : nodes) {
        if (matrix(rows, iterator) != 0 && iterator != rows) {
            denominator += pheromones_(rows, iterator) * matrix(rows, iterator);
        }
    }
    double nominator = pheromones_(rows, cols) * matrix(rows, cols);
    return (nominator / denominator);
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