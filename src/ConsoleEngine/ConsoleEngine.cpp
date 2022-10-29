#include "ConsoleEngine.h"

namespace s21 {

ConsoleEngine::ConsoleEngine() {
    graph_ = Graph();
    graph_algorithms = GraphAlgorithms();
}

void ConsoleEngine::start() {
    int answer = -1;
    read_path_ = "/Users/violette/Desktop/GraphAlgorithmsCpp/src/DotFiles/example.dot";
    write_path_ = "/Users/violette/Desktop/GraphAlgorithmsCpp/src/DotFiles/test.dot";
    cout << menu_options_;

    while (true) {

        std::string input;
        cin >> input;
        if (input.size() == 1 && input.at(0) >= '0' && input.at(0) <= '7') {
          answer = stoi(input);
        }

        if (answer == 1) {
            cout << "Enter path to file: ";
            cin >> read_path_;
            graph_.GetMatrixFromFile(read_path_);
        } else if (answer == 2) {
            PrintResult(graph_algorithms.DepthFirstSearch(graph_,
                    RequestNmbFromUser("Enter start vertex: ")));
        } else if (answer == 3) {
            PrintResult(graph_algorithms.BreadthFirstSearch(graph_,
                    RequestNmbFromUser("Enter start vertex: ")));
        } else if (answer == 4) {
            cout << "Not implemented\n";
        } else if (answer == 5) {
            cout << "Not implemented\n";
        } else if (answer == 6) {
            cout << "Not implemented\n";
        } else if (answer == 7) {
            cout << "Not implemented\n";
        } else if (answer == 0) {
            break;
        } else {
            cout << "Invalid menu option\n";
        }
        answer = -1;
    }
}

int ConsoleEngine::RequestNmbFromUser(std::string message) {
    std::string input;
    cout << message;
    cin >> input;
    int nmb;
    try {
        nmb = std::stoi(input);
    } catch (std::invalid_argument exp) {
        nmb = 0;
    }
    return nmb;
}

void ConsoleEngine::PrintResult(std::vector<int> result) {
    if (result.at(0) == WRONG_VERTEX_NUMBER) {
        cout << "Invalid start vertex number.";
    } else if (result.at(0) == EMPTY_GRAPH_ERROR) {
        cout << "You should load graph from file first(Menu option 1)";
    } else {
        cout << "Result: ";
        for (long unsigned i = 0; i < result.size(); i++) {
            cout << result.at(i) << " ";
        }
    }
    cout << std::endl;
}


} // namespace s21
