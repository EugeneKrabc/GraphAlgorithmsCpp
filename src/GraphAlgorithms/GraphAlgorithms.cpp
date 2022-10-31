#include "GraphAlgorithms.h"


namespace s21 {

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph, int start_vertex) {
    return SearchAlgo(graph, start_vertex, SearchType::DepthFirstSearch);
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph, int start_vertex) {
    return SearchAlgo(graph, start_vertex, SearchType::BreadthFirstSearch);
}

std::vector<int> GraphAlgorithms::SearchAlgo(Graph &graph, int start_vertex, SearchType search_type) {
    std::vector<int> result = std::vector<int>();
    if (graph.GetMatrix().get_cols() == 0) {
        result.push_back(EMPTY_GRAPH_ERROR);
        return result;
    }
    S21Matrix& matrix = graph.GetMatrix();
    if (start_vertex > matrix.get_cols() || start_vertex <= 0) {
        result.push_back(WRONG_VERTEX_NUMBER);
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
    std::vector<int> pos, node, parent;
    int size = graph.GetMatrix().get_rows();
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