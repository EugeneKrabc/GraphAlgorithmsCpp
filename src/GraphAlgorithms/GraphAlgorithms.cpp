#include "GraphAlgorithms.h"

namespace s21 {

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
    S21Matrix matrix = graph.GetMatrix();
    const int length = matrix.get_cols();
    TsmResult shortest_path({}, -1);
    if (length < 2) {
        return TsmResult({}, Status::OUT_OF_RANGE);
    }
    pheromones_ = pheromones_delta_ = event_ = S21Matrix(length, length);
    for (int i = 0; i < matrix.get_rows(); i++) {
        for (int j = 0; j < matrix.get_cols(); j++) {
            if (matrix(i, j) != 0.0) {
                pheromones_(i, j) = 0.2;
            }
        }
    }
    for (size_t iteration = 0; iteration < 60; iteration++) {
        if (iteration > 0) {
            ApplyDeltaToPheromones(matrix);
        }
        TsmResult cur_path = AntColonyAlgorithm(matrix, length);
        if (shortest_path.distance == -1.0 || cur_path.distance < shortest_path.distance) {
            shortest_path = cur_path;
        }
    }
    return shortest_path;
}

TsmResult GraphAlgorithms::AntColonyAlgorithm(S21Matrix &matrix, const int length) {
    const int ants = 200;
    for (int i = 0; i < ants; i++) {
        std::vector<int> ants_path(ants), visited;
        std::set<int> available_nodes;
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
        IncreaseDelta(matrix, ants_path[i], visited);
    }
    TsmResult cur_path = GetFullPath(matrix);
    return GetFullPath(matrix);
}

    std::vector<int> GraphAlgorithms::GetStackWithShortestPathBetweenVertices(S21Matrix &matrix, int vertex1, int vertex2, int *length) {
        int size = matrix.get_rows();
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
                if (!node[j] && matrix(index_min, j) && pos[index_min] != big_number &&
                    pos[index_min] + matrix(index_min, j) < pos[j]) {
                    pos[j] = pos[index_min] + matrix(index_min, j);
                    parent[j] = index_min;
                }
            }
        }

        std::vector<int> temp;
        for (int i = vertex2 - 1; i != -1; i = parent[i]) {
            temp.push_back(i);
        }
        *length = pos[vertex2 - 1];
        return temp;
    }

TsmResult GraphAlgorithms::GetFullPath(S21Matrix &matrix) {
    double cur_path = 0;

    std::vector<int> visited = { 0 };
    S21Matrix available(pheromones_);
    int cur_pos = 0;
    while (visited.size() < matrix.get_cols()) {
        int max = -1;
        for (int i = 0; i < matrix.get_cols(); i++) {
            if (available(cur_pos, i) > 0.0 &&
                (max == -1 || available(cur_pos, i) > available(cur_pos, max) ||
                    available(i, cur_pos) > available(cur_pos, max))) {
                max = i;
            }
        }
        cur_path += matrix(cur_pos, max);
        available(cur_pos, max) = 0.0;
        cur_pos = max;
        visited.push_back(max);
    }

    int last_path;
    // Reversed path from last visited node to home
    auto reversed = GetStackWithShortestPathBetweenVertices(matrix, visited.back() + 1, 1, &last_path);
    for (int i = reversed.size() - 2; i >= 0; i--) {
        visited.push_back(reversed[i]);
    }
    cur_path += last_path;
    return {visited, cur_path};
}

void GraphAlgorithms::IncreaseDelta(S21Matrix &matrix, int path_of_cur, std::vector<int> &visited) {
    int last_ind = visited[0];
    const double Q = 10.0;
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
        double random_value = (double)rand() / (RAND_MAX);
        for (int j = 0; j < event_vec.size(); j++) {
            if (event_vec[j] != 0.0 && (event_vec[j] > random_value &&
                (ind == -1 || random_value > LastPositiveEvent(event_vec, j)))) {
                ind = j;
            }
        }
        return ind;
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
    return SearchAlgo(graph, start_vertex, SearchType::DepthFirstSearch);
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph, int start_vertex) {
    return SearchAlgo(graph, start_vertex, SearchType::BreadthFirstSearch);
}

std::vector<int> GraphAlgorithms::SearchAlgo(Graph &graph, int start_vertex,
                                             SearchType search_type) {
    std::vector<int> result = std::vector<int>();
    if (graph.GetMatrix().get_cols() == 0) {
        result.push_back(Status::EMPTY_GRAPH_ERROR);
        return result;
    }
    S21Matrix &matrix = graph.GetMatrix();
    if (start_vertex > matrix.get_cols() || start_vertex <= 0) {
        result.push_back(Status::WRONG_VERTEX_NUMBER);
        return result;
    }

    if (search_type == SearchType::BreadthFirstSearch) {
        list = Queue::init();
    } else {
        list = Stack::init();
    }
    list->push(start_vertex);
    std::vector<bool> visited = std::vector<bool>(matrix.get_cols() + 1, false);

    while (!list->empty()) {
        int current_vertex = list->pop();
        if (!visited[current_vertex]) {
            result.push_back(current_vertex);
            visited[current_vertex] = true;
        }

        for (int i = matrix.get_cols() - 1; i >= 0; i--) {
            if (matrix(current_vertex - 1, i) && !visited[i + 1]) {
                list->push(i + 1);
            }
        }
    }
    delete list;
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

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {
    int size = graph.GetMatrix().get_rows();
    if (size < 2 || vertex1 < 1 || vertex1 < 1 || vertex1 > size || vertex2 > size) return 0;
    std::vector<int> pos, node, parent;
    pos.resize(size);
    node.resize(size);
    parent.resize(size);
    for (int i = 0; i < size; ++i) {
        pos[i] = big_number_;
        node[i] = 0;
        parent[i] = -1;
    }

    int min = 0, index_min = 0;
    pos[vertex1 - 1] = 0;
    for (int i = 0; i < size; ++i) {
        min = big_number_;
        for (int j = 0; j < size; ++j) {
            if (!node[j] && pos[j] < min) {
                min = pos[j];
                index_min = j;
            }
        }
        node[index_min] = 1;
        for (int j = 0; j < size; ++j) {
            if (!node[j] && graph.GetMatrix()(index_min, j) && pos[index_min] != big_number_ &&
                pos[index_min] + graph.GetMatrix()(index_min, j) < pos[j]) {
                pos[j] = pos[index_min] + graph.GetMatrix()(index_min, j);
                parent[j] = index_min;
            }
        }
    }

    return pos[vertex2 - 1];
}

S21Matrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
    if (graph.GetMatrix().get_rows() < 2) return S21Matrix();
    S21Matrix return_matrix(graph.GetMatrix());
    for (int i = 0; i < return_matrix.get_rows(); ++i) {
        for (int j = 0; j < return_matrix.get_cols(); ++j) {
            if (return_matrix(i, j) == 0) return_matrix(i, j) = big_number_;
        }
    }
    for (int k = 0; k < return_matrix.get_rows(); ++k) {
        for (int i = 0; i < return_matrix.get_rows(); ++i) {
            for (int j = 0; j < return_matrix.get_cols(); ++j) {
                return_matrix(i, j) =
                    std::min(return_matrix(i, j), return_matrix(i, k) + return_matrix(k, j));
            }
        }
    }
    for (int i = 0; i < return_matrix.get_rows(); ++i) {
        for (int j = 0; j < return_matrix.get_cols(); ++j) {
            if (return_matrix(i, j) == big_number_) return_matrix(i, j) = 0;
        }
    }
    return return_matrix;
}

S21Matrix GraphAlgorithms::GetLeastSpanningTree(Graph &graph) {
    int size = graph.GetMatrix().get_rows();
    S21Matrix return_matrix(size, size), tmp_matrix(graph.GetMatrix());
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tmp_matrix(i, j) == 0) tmp_matrix(i, j) = big_number_;
            return_matrix(i, j) = 0;
        }
    }
    std::vector<bool> visited;
    visited.resize(size);
    for (int i = 0; i < size; ++i) {
        visited[i] = false;
    }
    visited[0] = true;
    for (int h = 1; h < size; ++h) {
        int min_weight = big_number_;
        std::pair<int, int> adding_edge;
        for (int i = 0; i < size; ++i) {
            if (visited[i]) {
                for (int j = 0; j < size; ++j) {
                    if (!visited[j] && !return_matrix(i, j) && tmp_matrix(i, j) < min_weight) {
                        min_weight = tmp_matrix(i, j);
                        adding_edge.first = i;
                        adding_edge.second = j;
                    }
                }
            }
        }
        visited[adding_edge.second] = true;
        return_matrix(adding_edge.first, adding_edge.second) = min_weight;
        return_matrix(adding_edge.second, adding_edge.first) = min_weight;
    }
    return return_matrix;
}

TsmResult GraphAlgorithms::SolveTSMBranchAndBoundMethod(Graph &graph) {
    branch_and_bound_solver = new TSMBranchAndBoundSolver(graph.GetMatrix().get_cols());
    TsmResult result;
    branch_and_bound_solver->TSP(graph.GetMatrix());
    result.distance = branch_and_bound_solver->GetLengthResult();
    result.vertices = branch_and_bound_solver->GetFinalPath();
    delete branch_and_bound_solver;
    return result;
}



}  // namespace s21