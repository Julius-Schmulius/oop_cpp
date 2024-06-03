#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <utility>
#include <cctype>

bool initializegame(){
    vector<vector<char> > spielfeld(9,vector<char>(9));
    std::vector<std::vector<char> > spielfeld(9,std::vector<char>(9));
    std::string colors = "RGBYP"; // Red, Green, Blue, Yellow, Purple

    std::srand(std::time(0));

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            int random_color_index = std::rand() % colors.size(); // random index from colors
            spielfeld[i][j] = colors[random_color_index]; // assign random color to cell
        }
    }
    
    // check if all cells are assigned a color
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(spielfeld[i][j] == '\0') { // check for unassigned
                return false;
            }
        }
    }
    return true;
}

bool cleargame() {
    for(auto& row : spielfeld) {
        row.clear();
    }
    spielfeld.clear();
    
    if(spielfeld.empty()) {
        return true;
    } else {
        return false;
    }
}

std::pair<int, int> getMove() {
    std::string input;
    std::cin >> input;
    
    if(input.length() > 2) {
        input = input.substr(0, 2); // Ignore characters after the first two
    }
    
    //check for: length < 2, [0] is a letter, [1] is a number 
    if(input.length() < 2 || !std::isalpha(input[0]) || !std::isdigit(input[1])) {
            std::cout << "Invalid input. Syntax is (letter)(number) e.g. a1, J9, ..." << std::endl;
            return getMove();
    }

    int column = std::tolower(input[0]) - 'a'; // letter -> column index
    int row = input[1] - '1'; // number -> row index

    if(row < 0 || row >= spielfeld.size() || column < 0 || column >= spielfeld[0].size()) {
            std::cout << "Invalid move. Not inside field boundaries." << std::endl;
            return getMove();
    }

    return std::make_pair(row, column);
}

//find color clusters with depth first search
void dfs(int row, int column, int color, std::vector<std::vector<int>>& visited) {
    // check if the cell is out of bounds or has already been visited
    if(row < 0 || row >= spielfeld.size() || column < 0 || column >= spielfeld[0].size() || visited[row][column]) {
        return;
    }

    if(spielfeld[row][column] != color) { 
        return;
    }

    visited[row][column] = 1; // mark as visited

    dfs(row - 1, column, color, visited); // check upper cell
    dfs(row + 1, column, color, visited); // down
    dfs(row, column - 1, color, visited); // left
    dfs(row, column + 1, color, visited); // right
}

std::vector<std::vector<int>> findGroup(int startRow, int startColumn) {
    int color = spielfeld[startRow][startColumn]; //color of selected cell
    std::vector<std::vector<int>> visited(spielfeld.size(), std::vector<int>(spielfeld[0].size(), 0)); 
    //initialize zero matrix, visited cells will be marked with 1 
    dfs(startRow, startColumn, color, visited); //start depth first search
    return visited; //return visited cells
}

int main () {
    bool isInitialized = initializegame();
    if(isInitialized) {
        std::cout << "Game initialized successfully" << std::endl;
    } else {
        std::cout << "Game initialization failed" << std::endl;
    }

    //TODO: Implement game logic and sequence in a loop
    // search
    // remove if more than one cell U,D,L,R has same color (recursive / efficient)
    // cells should fall down / fill up empty cells / whole column empty -> move them together
    // print game and points
    // check if game is over (no more moves possible)
    // ask for new game or exit

    bool isCleared = cleargame();
    if(isCleared) {
        std::cout << "Game cleared successfully" << std::endl;
    } else {
        std::cout << "Game clearing failed" << std::endl;
        //cleargame();
    }

    return 0;
}