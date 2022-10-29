#include "GraphAlgorithms.h"

namespace s21 {

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph, int start_vertex) {
    std::vector<int> result = std::vector<int>();
    if (graph.GetMatrix().get_cols() == 0) {
        result.push_back(EMPTY_GRAPH_ERROR);
    }
    S21Matrix &matrix = graph.GetMatrix();
    if (start_vertex > matrix.get_cols() || start_vertex <= 0) {
        result.push_back(WRONG_VERTEX_NUMBER);
        return result;
    }

    std::unordered_set<int> visited = std::unordered_set<int>();
    Stack stack = Stack::init();
    stack.push(start_vertex);

    while (!stack.empty()) {
        int current_vertex = stack.pop();
        result.push_back(current_vertex);
        visited.insert(current_vertex);

        //        debug_print_vector(result);
        //        debug_print_stack(stack);
        //        debug_print_set(visited);

        for (int i = 0; i < matrix.get_cols(); i++) {
            if (matrix(current_vertex - 1, i) && visited.find(i + 1) == visited.end()) {
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

void GraphAlgorithms::debug_print_set(std::unordered_set<int> set) {
    printf("Visited: ");
    for (auto it = set.begin(); it != set.end(); it++) {
        printf("%d ", *it);
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

    // вывод пути
    // std::vector<int> temp;
    // for (int i = vertex2 - 1; i != -1; i = parent[i]) temp.push_back(i + 1);
    // std::reverse(temp.begin(), temp.end());
    // for (int i = 0; i < temp.size(); ++i) std::cout << temp[i] << " ";
    // std::cout << std::endl;
    return pos[vertex2 - 1];
}

S21Matrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
    S21Matrix return_matrix(graph.GetMatrix());
    for (int i = 0; i < return_matrix.get_rows(); ++i) {
        for (int j = 0; j < return_matrix.get_cols(); ++j) {
            if (return_matrix(i, j) == 0)
                return_matrix(i, j) = big_number_;
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
            if (return_matrix(i, j) == big_number_)
                return_matrix(i, j) = 0;
        }
    }
    return return_matrix;
}

}  // namespace s21

// int main() {
//     s21::Graph graph;
//     graph.GetMatrixFromFile("/Users/pilafber/Projects/2/src/DotFiles/graph");
//     s21::GraphAlgorithms graph_algs;
//     s21::S21Matrix return_matrix = graph_algs.GetShortestPathsBetweenAllVertices(graph);
//     for (int i = 0; i < return_matrix.get_rows(); ++i) {
//         for (int j = 0; j < return_matrix.get_cols(); ++j) {
//             std::cout << return_matrix(i, j) << " ";
//         }
//         std::cout << std::endl;
//     }
//     return 0;
// }