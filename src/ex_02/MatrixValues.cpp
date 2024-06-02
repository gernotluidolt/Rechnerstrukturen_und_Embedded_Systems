#include "MatrixValues.h"

MatrixValues::MatrixValues() {
    for (int i = 0; i < 8; i++) {
        List[i] = 0;
    }
}

int MatrixValues::getVal(int i) {
    return List[i];
}

void MatrixValues::newVal(int x) {
    // move all values to the left and add the new value to the end
    for (int i = 0; i < 7; i++) {
        List[i] = List[i + 1];
    }
    List[7] = x;
}