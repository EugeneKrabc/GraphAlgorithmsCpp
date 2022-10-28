#include "GraphAlgorithms.h"


namespace s21 {

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph, int start_vertex) {
    std::vector<int> result = std::vector<int>();
    if (graph.GetMatrix().get_cols() == 0) {
        result.push_back(EMPTY_GRAPH_ERROR);
    }
    S21Matrix& matrix = graph.GetMatrix();
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


}  // namespace s21