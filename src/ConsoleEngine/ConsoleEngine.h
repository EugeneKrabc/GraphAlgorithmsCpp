#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_CONSOLEENGINE_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_CONSOLEENGINE_H

#include <iostream>

#include "../DotFormatHandler/DotFormatHandler.h"
#include "../Graph/Graph.h"
#include "../GraphAlgorithms/GraphAlgorithms.h"

namespace s21 {

    using std::cout;
    using std::cin;

    class ConsoleEngine {
    public:
        void start();

    private:
        DotFormatHandler dot_format_handler_;
        std::string read_path_, write_path_;
        S21Matrix matrix_;

        std::string menu_options_ = ("Menu options:\n"
                                     "\t 1. Load graph from a file.\n"
                                     "\t 2. Perform a breadth traversal of the graph.\n"
                                     "\t 3. Perform a depth traversal of the graph.\n"
                                     "\t 4. Search the shortest path between any two vertices of the graph.\n"
                                     "\t 5. Search shortest paths between all pairs of vertices of the graph.\n"
                                     "\t 6. Search the minimal spanning tree in the graph.\n"
                                     "\t 7. Solve salesman problem.\n"
                                     "\t 0. Close the application.\n");
    };

}

#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_CONSOLEENGINE_H