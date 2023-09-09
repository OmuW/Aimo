#include <iostream>
#include "Bitboard.h"

int main() {
    Bitboard b;
    b.setSquare(0);   // a8
    b.setSquare(63);  // h1

    b.pprint();

    return 0;
}
