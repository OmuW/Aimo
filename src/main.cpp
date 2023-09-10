#include <iostream>
#include "Board.h"

int main() {
    Board b;
    b.pprint();
    std::string fen =  "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";   Board b2(fen);
    b2.pprint();

    return 0;
}
