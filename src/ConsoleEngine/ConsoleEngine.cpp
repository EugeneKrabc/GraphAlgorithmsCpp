#include "ConsoleEngine.h"

namespace s21 {

ConsoleEngine::ConsoleEngine() {
    graph_ = Graph();
    graph_algorithms_ = GraphAlgorithms();
}

void ConsoleEngine::start() {
    read_path_ = "/Users/violette/Desktop/GraphAlgorithmsCpp/src/DotFiles/TSP.dot";
    write_path_ = "/Users/violette/Desktop/GraphAlgorithmsCpp/src/DotFiles/test.dot";
    cout << menu_options_;

    while (true) {
        int answer = -1;
        std::string input;
        cin >> input;
        cout << std::endl;
        if (input.size() == 1 && input.at(0) >= '0' && input.at(0) <= '7') {
          answer = stoi(input);
        }

        if (answer == 1) {
//            cout << "Enter path to file: ";
//            cin >> read_path_;
            graph_.GetMatrixFromFile(read_path_);
        } else if (answer == 2) {
            PrintDFS(graph_algorithms_.DepthFirstSearch(graph_,
                    RequestNmbFromUser("Enter start vertex: ")));
        } else if (answer == 3) {
            cout << "Not implemented\n";
        } else if (answer == 4) {
            cout << "Not implemented\n";
        } else if (answer == 5) {
            cout << "Not implemented\n";
        } else if (answer == 6) {
            cout << "Not implemented\n";
        } else if (answer == 7) {
            PrintTSM(graph_algorithms_.SolveTravelingSalesmanProblem(graph_));
        } else if (answer == 0) {
            break;
        } else {
            cout << "Invalid menu option\n";
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
    if (result.distance == Status::OUT_OF_RANGE) {
        cout << "Count of vertices must be more than 1\n";
    } else {
        cout << "THe shortest path weights is " << result.distance << std::endl;
        cout << "Order of vertices: ";
        for (auto iterator: result.vertices)
            cout << iterator << ' ';
        cout << std::endl;
    }
}

void ConsoleEngine::PrintDFS(std::vector<int> result) {
    if (result.at(0) == Status::WRONG_VERTEX_NUMBER) {
        cout << "Invalid start vertex number.";
    } else if (result.at(0) == Status::EMPTY_GRAPH_ERROR) {
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
