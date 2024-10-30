#include <iostream>
#include <fstream>

const int GRID_SIZE = 9;

//currently unutilized helper functions
bool grids_are_same(int grid[GRID_SIZE][GRID_SIZE], int solution[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i){
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] != solution[i][j]){
                return false;
            }
        }
    }
    return true;
}

void print_grid(int grid[GRID_SIZE][GRID_SIZE]){

    //formatting for printing the grid
    std::cout<<"+-----------------------------------+"<<std::endl;
    for (int i = 0; i<GRID_SIZE;i++){
        for (int j = 0; j<GRID_SIZE;j++){
            if (j==0){
                std::cout<<'|';
            }
            // 0's in the data indicate blanks
            if (grid[i][j] == 0) {
                std::cout << "   |";
            } else {
            std::cout << ' ' <<grid[i][j]<<" |";
            }
        }
        if ((i+1)%3 == 0 && i !=8) {
            std::cout<<std::endl<<"|-----------+-----------+-----------|";
        }
        std::cout<<std::endl;
    }
    std::cout<<"+-----------------------------------+" << std::endl;
}

void print_solution(int solution[GRID_SIZE][GRID_SIZE]){

    //formatting for printing the grid
    std::cout<<"+-----------------------------------+"<<std::endl;
    for (int i = 0; i<GRID_SIZE;i++){
        for (int j = 0; j<GRID_SIZE;j++){
            if (j==0){
                std::cout<<'|';
            }
            // 0's in the data indicate blanks
            if (solution[i][j] == 0) {
                std::cout << "   |";
            } else {
            std::cout << ' ' <<solution[i][j]<<" |";
            }
        }
        if ((i+1)%3 == 0 && i !=8) {
            std::cout<<std::endl<<"|-----------+-----------+-----------|";
        }
        std::cout<<std::endl;
    }
    std::cout<<"+-----------------------------------+" << std::endl;
}

//necessary functions
void initializeGrid(std::string file_name, int puz_num, int grid[GRID_SIZE][GRID_SIZE], int solution[GRID_SIZE][GRID_SIZE]) {
    std::string line, puz, raw_solution;

    //open the file
    std::ifstream file(file_name);

    //go through the file until you get to the correct puzzle
    for(int i = 0; i < 1+puz_num; i++) {
        std::getline(file,line);
    }
    //split the line into puzzle and solution data
    const int comma_pos = 81;

    puz = line.substr(0, comma_pos);
    raw_solution = line.substr(comma_pos + 1);

    file.close();
    
    //create the arrays for the grid (puzzle) and solution from the data
    for (unsigned int i = 0; i < GRID_SIZE; ++i) {
        for (unsigned int j = 0; j < GRID_SIZE; ++j) {
            //substracting 48 from both of these because they are ASCII indexes instead of ints themselves,
            //so im simply taking away 48 because 0 has an ASCII value of 48
            grid[i][j] = puz[(i*9)+j]-48; 
            solution[i][j] = raw_solution[(i*9)+j]-48;
        }
    }

}

bool is_valid(int grid[GRID_SIZE][GRID_SIZE], int row_index, int col_index, int try_digit) {

        //comparing row
        for (int i = 0; i < GRID_SIZE; ++i) {
            //skip the digit we are checking, and check return false if the digit is in the row
            if (grid[row_index][i] == try_digit && i != col_index){
                return false;
            }
        }

        //comparing col
        for (int i = 0; i < GRID_SIZE; ++i) {
            //skip the digit we are checking, and check return false if the digit is in the column
            if (grid[i][col_index] == try_digit && i != row_index){
                return false;
            }
        }
    
        //comparing against box 
        int box_starting_row = row_index/3 * 3;
        int box_starting_col = col_index/3 * 3;

        for (int i = 0; i  < 3; ++i){
            for (int j = 0; j < 3; ++j) {
                //if it is not in the position we are checking AND it is the same as the digit we are trying, it is not valid. 
                if ((i != row_index || j !=col_index) && grid[i + box_starting_row][j + box_starting_col] == try_digit){
                    return false;
                }
            }
        }

        return true;

}

bool backtracking(int grid[GRID_SIZE][GRID_SIZE], int row, int col) {
    // if we get to the end of a row, go to the next one
    if (col >= GRID_SIZE) {
        ++row;
        col = 0;
    }    
    // if we go too far, we know we solved the puzzle. return true. 
    if (row >= GRID_SIZE) {
            return true;
    }

    //skip filled positions
    if (grid[row][col] != 0) {
        return backtracking(grid, row, col+1);
    }  

    //try each digit
    for (int i = 1; i <= GRID_SIZE; ++i) {
        //if you get a correct digit
        if (is_valid(grid, row, col, i)) {
            //set the digit in place (probably temporarily)
            grid[row][col] = i;

            //if the chosen digit results in a solved puzzle, return true. 
            if (backtracking(grid, row, col + 1)){
                return true;
            }  
            //otherwise, reset the digit back to 0 and keep trying to find the correct digit (the backtracking part)
            grid[row][col] = 0; 
        }
    }
    //if we get to the end and can't do anything, the puzzle cant be filled
    return false;
}


int main() {
    int solution[GRID_SIZE][GRID_SIZE];
    int grid[GRID_SIZE][GRID_SIZE];

    bool all_solved = true;
    clock_t start, end;
    double time_in_secs;
    int puz_num;

    std::cout << "How many puzzles would you like to attempt to solve?" << std::endl;
    std::cin >> puz_num;
    
    start = clock(); 

    for (int i = 1; i <= puz_num; ++i){
        initializeGrid("DATA.csv", i, grid, solution);
        backtracking(grid, 0,0);

        if (!backtracking) {
            std::cout << "Puzzle number " << i << " was not able to be solved." << std::endl;
            all_solved = false;
        }

        //can check if the puzzle is the same as the hard-coded solution using the code below
        //unless the puzzle is poorly built, backtracking will almost always lead to this solution 

        /*if (!grids_are_same(grid,solution)) {
            std::cout << "Puzzle number " << i << " was not able to be solved." << std::endl;
            all_solved = false;
        }*/
    }
    end = clock();

    if (all_solved) {
        std::cout << "All puzzles have successfully been solved." << std::endl;
    }

    //simply reading the start time and end time, then subtracting them
    time_in_secs = ((double) (end - start)) / CLOCKS_PER_SEC; //dividing by CLOCKS_PER_SEC to get time in seconds
    std::cout << "Time taken: " << time_in_secs << " seconds" << std::endl;

    return 0;
}