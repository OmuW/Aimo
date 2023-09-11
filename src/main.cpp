#include <iostream>
#include "Board.h"

int main() {
    Board b;
    b.pprint();
    std::string fen =  "2r5/3pk3/8/2P5/8/2K5/8/8 w - - 5 4";
    Board b2(fen);
    b2.pprint();

    return 0;
}
