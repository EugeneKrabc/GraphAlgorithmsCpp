#pragma once
#include "../DataStructures/Matrix/Matrix.h"
#include <vector>

namespace s21 {
    struct TsmResult {
        std::vector<int> vertices;
        double distance;

        TsmResult(std::vector<int> path, double distance) {
            this->distance = distance;
            vertices = path;
        }
    };

    class AbstractTSM {
    public:
        AbstractTSM(S21Matrix &matrix) : matrix_(matrix) {
            FillEmptyElements();
        }
        virtual TsmResult GetAnswer() = 0;
        virtual ~AbstractTSM() {}

    protected:
        S21Matrix matrix_;

        void FillEmptyElements() {
            double max = matrix_(0, 0);
            for (int i = 0; i < matrix_.get_rows(); i++) {
                for (int j = 0; j < matrix_.get_cols(); j++) {
                    max = std::max(max, matrix_(i, j));
                }
            }
            for (int i = 0; i < matrix_.get_rows(); i++) {
                for (int j = 0; j < matrix_.get_cols(); j++) {
                    if (i != j && matrix_(i, j) == 0.0) {
                        matrix_(i, j) = max;
                        max += 5.0;
                    }
                }
            }
        }
    };
}
