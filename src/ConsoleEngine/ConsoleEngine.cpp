#include "ConsoleEngine.h"

namespace s21 {

ConsoleEngine::ConsoleEngine() {
    graph_ = Graph();
    graph_algorithms_ = GraphAlgorithms();
}

void ConsoleEngine::start() {
    cout << menu_options_;

    while (true) {
        int answer = -1;
        std::string input;
        cin >> input;
        cout << std::endl;
        if (input.size() == 1 && input.at(0) >= '0' && input.at(0) <= '9') {
            answer = stoi(input);
        }

        switch (answer) {
            int start_vertex, end_vertex;
            case LOAD_GRAPH_FROM_FILE:  // 1
                cout << "Enter path to file: ";
                cin >> read_path_;
                graph_.GetMatrixFromFile(read_path_);
                break;
            case PERFORM_DFS:  // 2
                if (!graph_.IsEmpty()) start_vertex = RequestNmbFromUser("Enter start vertex: ");
                PrintResultVector(graph_algorithms_.DepthFirstSearch(graph_, start_vertex));
                break;
            case PERFORM_BFS:  // 3
                if (!graph_.IsEmpty()) start_vertex = RequestNmbFromUser("Enter start vertex: ");
                PrintResultVector(graph_algorithms_.BreadthFirstSearch(graph_, start_vertex));
                break;
            case FIND_SHORTEST_PATH_BETWEEN_TWO_V:  // 4
                if (!graph_.IsEmpty()) {
                    start_vertex = RequestNmbFromUser("Enter start vertex: ");
                    end_vertex = RequestNmbFromUser("Enter end vertex: ");
                }
                PrintResultInt(
                    graph_algorithms_.GetShortestPathBetweenVertices(graph_, start_vertex, end_vertex));
                break;
            case FIND_SHORTEST_PATH_BETWEEN_ALL_V:  // 5
                PrintResultMatrix(graph_algorithms_.GetShortestPathsBetweenAllVertices(graph_));
                break;
            case FIND_MINIMAL_SPANNING_TREE:  // 6
                PrintResultMatrix(graph_algorithms_.GetLeastSpanningTree(graph_));
                break;
            case SOLVE_TSM_ANT_METHOD:  // 7
                PrintTSM(graph_algorithms_.SolveTravelingSalesmanProblem(graph_));
                break;
            case DO_RESEARCH_ON_TSM_ALGORITHMS:
                cout << "Not implemented" << std::endl;
                break;
            case WRITE_GRAPH_TO_FILE:
                cout << "Not implemented" << std::endl;
                break;
            case EXIT:
                return;
            default:
                cout << "Invalid menu option" << std::endl;
        }
    }
}

int ConsoleEngine::RequestNmbFromUser(std::string message) {
    std::string input;
    cout << message;
    cin >> input;
    int nmb;
    try {
        nmb = std::stoi(input);
    } catch (std::invalid_argument &exp) {
        nmb = 0;
    }
    return nmb;
}

void ConsoleEngine::PrintTSM(TsmResult result) {
    if (result.distance == Status::EMPTY_GRAPH_ERROR) {
        cout << "You should load graph from file first (Menu option 1)";
    } else {
        cout << "The shortest path weights is " << result.distance << std::endl;
        cout << "Order of vertices: ";
        for (auto iterator : result.vertices) cout << iterator << ' ';
    }
    cout << std::endl;
}

void ConsoleEngine::PrintResultVector(std::vector<int> result) {
    if (result.at(0) == Status::WRONG_VERTEX_NUMBER) {
        cout << "Invalid start vertex number.";
    } else if (result.at(0) == Status::EMPTY_GRAPH_ERROR) {
        cout << "You should load graph from file first (Menu option 1)";
    } else {
        cout << "Result: ";
        for (long unsigned i = 0; i < result.size(); i++) {
            cout << result.at(i) << " ";
        }
    }
    cout << std::endl;
}

void ConsoleEngine::PrintResultMatrix(s21::S21Matrix result) {
    if (result.get_rows() == 0) {
        cout << "You should load graph from file first (Menu option 1)";
    } else {
        cout << "Result: " << std::endl;
        for (int i = 0; i < result.get_rows(); ++i) {
            for (int j = 0; j < result.get_cols(); ++j) {
                cout << result(i, j) << " ";
            }
            cout << std::endl;
        }
    }
    cout << std::endl;
}

void ConsoleEngine::PrintResultInt(int result) {
    if (result == Status::WRONG_VERTEX_NUMBER) {
        cout << "You should enter the correct vertices numbers";
    } else if (result == Status::EMPTY_GRAPH_ERROR) {
        cout << "You should load graph from file first (Menu option 1)";
    } else {
        cout << "Result: " << result << std::endl;
    }
    cout << std::endl;
}

}  // namespace s21
