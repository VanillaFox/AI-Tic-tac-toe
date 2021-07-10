#include <iostream>
#include <vector>


class Map{
    std::vector<std::vector<std::string>> table;
    std::vector<std::string>::iterator iter;
    int stringNumber, colomnNumber;
    int startString = 1, startColomn = 1;
    int intervalBetweenStrings = 4, intervalBetweenColomns = 1;
    std::string curSymbol, cursor = "@";

    public:
    Map();
    void Move(char a);
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
};