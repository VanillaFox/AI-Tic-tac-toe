#include <iostream>
#include <string>
#include <vector>
//отрисовка карты
// Х и О
//смена хода

class Game{
    bool game;
    int player;
    char X = 'X', O = 'O';
    std::vector<std::vector<std::string>> table{{"       |       |       \n"},
        {"   ", "1", "   |   ", "2", "   |   ", "3", "   \n"},
        {"       |       |       \n"},
        {"-----------------------\n"},
        {"       |       |       \n"},
        {"   ", "4", "   |   ", "5", "   |   ", "6", "   \n"},
        {"       |       |       \n"},
        {"-----------------------\n"},
        {"       |       |       \n"},
        {"   ", "7", "   |   ", "8", "   |   ", "9", "   \n"},
        {"       |       |       \n"}
        };
    
    void PrintTable(){
        for(int i = 0; i < table.size(); i++){
            for(std::vector<std::string>::iterator it = table[i].begin(); it != table[i].end(); it++){
                std::cout << (*it);
            }
        }
        std::cout << "Hello" << std::endl;
    }

    public:
    Game(){
        PrintTable();
    }
    
};