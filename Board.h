#ifndef BOARD_H
#define BOARD_H

typedef char[5][5] Mosaic;

class Board
{
public:
    Board();

private:
    Mosaic mosaic;
}

#endif //BOARD_H