#include <iostream>
#include <fstream>
#include <array>

//to do: input validation on the file -- if you can open it and it has the right number of values
//randomization of the file? (need to include all source files in directory)

const int GRID_SIZE = 9;
std::array<std::array<int, GRID_SIZE>, GRID_SIZE> solution;

std::array<std::array<int, GRID_SIZE>, GRID_SIZE> initializeGrid(std::string file_name) {
    std::string line, puz, raw_solution;
    std::ifstream file(file_name);

    int puz_num = 4;

    for(int i = 0;i<(1+puz_num);i++) {
        std::getline(file,line);
    }

    const int comma_pos = 81;
    puz = line.substr(0, comma_pos);
    raw_solution = line.substr(comma_pos + 1);

    file.close();
    
    std::array<std::array<int, GRID_SIZE>, GRID_SIZE> grid = {0};
    for (unsigned int i = 0;i<GRID_SIZE;i++) {
        for (unsigned int j = 0;j<GRID_SIZE;j++) {
            grid[i][j] = puz[(i*9)+j]-48;
            solution[i][j] = raw_solution[(i*9)+j]-48;
        }
    }

    return grid;
}

void print(std::array<std::array<int, GRID_SIZE>, GRID_SIZE> grid){
    std::cout<<"-------------------------------------"<<std::endl;
    for (int i = 0; i<GRID_SIZE;i++){
        for (int j = 0; j<GRID_SIZE;j++){
            if (j==0){
                std::cout<<'|';
            }
            if (grid[i][j] == 0) {
                std::cout << "   |";
            } else {
            std::cout << ' ' <<grid[i][j]<<" |";
            }
        }
        if ((i+1)%3 == 0 && i !=8) {
            std::cout<<std::endl<<"|-----------|-----------|-----------|";
        }
        std::cout<<std::endl;
    }
    std::cout<<"-------------------------------------";
}

int main() {
    std::array<std::array<int, GRID_SIZE>, GRID_SIZE> grid = initializeGrid("DATA.csv");
    print(grid);
    return 0;
}