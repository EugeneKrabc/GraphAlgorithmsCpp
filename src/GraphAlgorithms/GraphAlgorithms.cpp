#include "GraphAlgorithms.h"


namespace s21 {

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph, int start_vertex) {
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

    std::vector<bool> visited = std::vector<bool>(matrix.get_cols() + 1, false);
    Stack stack = Stack::init();
    stack.push(start_vertex);

    while (!stack.empty()) {
        int current_vertex = stack.pop();
        if (!visited[current_vertex]) {
            result.push_back(current_vertex);
            visited[current_vertex] = true;
        }

        for (int i = matrix.get_cols() - 1; i >= 0; i--) {
            if (matrix(current_vertex - 1, i) && !visited[i + 1]) {
                stack.push(i + 1);
            }
        }
    }

    return result;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph, int start_vertex) {
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

    std::vector<bool> visited = std::vector<bool>(matrix.get_cols() + 1, false);
    Queue queue = Queue::init();
    queue.push(start_vertex);

    while (!queue.empty()) {
        int current_vertex = queue.pop();
        if (!visited[current_vertex]) {
            result.push_back(current_vertex);
            visited[current_vertex] = true;
        }

        for (int i = matrix.get_cols() - 1; i >= 0; i--) {
            if (matrix(current_vertex - 1, i) && !visited[i + 1]) {
                queue.push(i + 1);
            }
        }
    }

    return result;
}

//std::vector<int> GraphAlgorithms::SearchAlgo(Graph &graph, int start_vertex, SearchType search_type) {
//    std::vector<int> result = std::vector<int>();
//    if (graph.GetMatrix().get_cols() == 0) {
//        result.push_back(EMPTY_GRAPH_ERROR);
//        return result;
//    }
//    S21Matrix& matrix = graph.GetMatrix();
//    if (start_vertex > matrix.get_cols() || start_vertex <= 0) {
//        result.push_back(WRONG_VERTEX_NUMBER);
//        return result;
//    }
//
//    std::vector<bool> visited = std::vector<bool>(matrix.get_cols() + 1, false);
//    Queue list = Queue::init();
//
//
//    list.push(start_vertex);
//
//    while (!list.empty()) {
//        int current_vertex = list.pop();
//        if (!visited[current_vertex]) {
//            result.push_back(current_vertex);
//            visited[current_vertex] = true;
//        }
//
//        for (int i = matrix.get_cols() - 1; i >= 0; i--) {
//            if (matrix(current_vertex - 1, i) && !visited[i + 1]) {
//                list.push(i + 1);
//            }
//        }
//    }
//
//    return result;
//}

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