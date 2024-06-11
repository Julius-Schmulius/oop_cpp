#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <utility>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <map>
#include <sstream> 
#include <limits>

//declarations for later use in gameLoop
std::string getName();
void gameLoop(std::vector<std::vector<char>>& spielfeld, const std::string& colors, int& score, std::vector<std::vector<int>>& visited);

void printColoredAsciiArt(const std::string& asciiArt) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // map each symbol to a color
    std::map<char, int> colorMap = {
        {'/', 12}, {'_', 12}, {'-', 12}, {'`', 12}, {' ', 5}, {'|', 12}, {'\\', 12}, {'\'', 12},
        {',', 12}, {'(', 12}, {')', 12}
    };

    std::istringstream iss(asciiArt);
    std::string line;
    while (std::getline(iss, line)) {
        for (char c : line) {
            if (colorMap.count(c) > 0) {
                SetConsoleTextAttribute(hConsole, colorMap[c]);
            } else {
                SetConsoleTextAttribute(hConsole, 15);  // default color for every other characters
            }
            std::cout << c;
        }
        std::cout << '\n';
    }

    SetConsoleTextAttribute(hConsole, 15);  // Reset color
}

//*** NORMAL GAME ***
void fillBoard(std::vector<std::vector<char>>& spielfeld, const std::string& colors) {
    std::srand(std::time(0)); 
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            int random_color_index = std::rand() % colors.length(); // random index from colors
            spielfeld[i][j] = colors[random_color_index]; // assign random color to cell
        }
    }
}

//***ONLY RED***
// void fillBoard(std::vector<std::vector<char>>& spielfeld, const std::string& colors) {
//     for(int i = 0; i < 9; i++) {
//         for(int j = 0; j < 9; j++) {
//             spielfeld[i][j] = 'R'; // assign only RED color to cell
//         }
//     }
// }

//***RANDOM COLORED COLUMNS***
// void fillBoard(std::vector<std::vector<char>>& spielfeld, const std::string& colors) {
//     for(int j = 0; j < 9; j++) {
//         char color = colors[j % colors.size()]; // select color for each column
//         for(int i = 0; i < 9; i++) {
//             spielfeld[i][j] = color;
//         }
//     }
// }

//***RANDOM COLORED ROWS***
// void fillBoard(std::vector<std::vector<char>>& spielfeld, const std::string& colors) {
//     for(int i = 0; i < 9; i++) {
//         char color = colors[i % colors.size()]; // select color for each row
//         for(int j = 0; j < 9; j++) {
//             spielfeld[i][j] = color;
//         }
//     }
// }

bool initializegame(std::vector<std::vector<char>>& spielfeld, const std::string& colors){

    fillBoard(spielfeld, colors);
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

// void resetBoard(std::vector<std::vector<int>>& spielfeld, const std::vector<char>& colors) {
//     for (auto& row : spielfeld) {
//         for (int& cell : row) {
//             //TODO
//         }
//     }
// }

// bool cleargame() {
//     for(auto& row : std::vector<std::vector<char>> spielfeld) { //TODO: fix
//         row.clear();
//     }
//     std::vector<std::vector<char>> spielfeld.clear();
    
//     if(spielfeld.empty()) {
//         return true;
//     } else {
//         return false;
//     }
// }

std::pair<int, int> getMove(std::vector<std::vector<char>>& spielfeld) {
    std::string input;
    std::cin >> input;
    
    if(input == "exit") {
        std::cout << "Exiting..." << std::endl;
        exit(0);
    }

    if(input.length() > 2) {
        input = input.substr(0, 2); // only look at first 2 characters
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore leftover newline
    }
    
    //check for: length < 2, [0] is a letter, [1] is a number 
    if(input.length() < 2 || !std::isalpha(input[0]) || !std::isdigit(input[1])) {
            std::cout << "\033[1;31m" << "Invalid input. Syntax is (letter)(number) e.g. a1, I9, ..." << "\033[0m" << std::endl;
            //td::cout << "Invalid input. Syntax is (letter)(number) e.g. a1, I9, ..." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore leftover newline
            std::cout << "Enter your move: ";
            return getMove(spielfeld);
    }

    int column = std::tolower(input[0]) - 'a'; // letter -> column index
    int row = input[1] - '1'; // number -> row index

    if(row < 0 || row >= spielfeld.size() || column < 0 || column >= spielfeld[0].size()) {
        std::cout << "\033[1;31m" << "Invalid move. Not inside field boundaries." << "\033[0m" << std::endl;
            //std::cout << "Invalid move. Not inside field boundaries." << std::endl;
            std::cout << "Enter your move: ";
            return getMove(spielfeld);
    }

    return std::make_pair(row, column);
}

//find color clusters with depth first search
void dfs(int row, int column, int color, std::vector<std::vector<int>>& visited, std::vector<std::vector<char>>& spielfeld) {
    // check if the cell is out of bounds or has already been visited
    if(row < 0 || row >= spielfeld.size() || column < 0 || column >= spielfeld[0].size() || visited[row][column]) {
        return; 
    }

    if(spielfeld[row][column] != color) { 
        return;
    }

    visited[row][column] = 1; // mark as visited

    dfs(row - 1, column, color, visited, spielfeld); // check upper cell
    dfs(row + 1, column, color, visited, spielfeld); // down
    dfs(row, column - 1, color, visited, spielfeld); // left
    dfs(row, column + 1, color, visited, spielfeld); // right
}

void resetVisited(std::vector<std::vector<int>>& visited) {
    for (auto& row : visited) {
        std::fill(row.begin(), row.end(), 0);
    }
}

std::vector<std::vector<int>> findGroup(std::pair<int, int> move, std::vector<std::vector<char>>& spielfeld, std::vector<std::vector<int>>& visited) {
    int startRow = move.first;
    int startColumn = move.second;
    int color = spielfeld[startRow][startColumn]; //color of selected cell
    //std::vector<std::vector<int>> visited(spielfeld.size(), std::vector<int>(spielfeld[0].size(), 0)); 
    //initialize zero matrix, visited cells will be marked with 1 
    resetVisited(visited);
    dfs(startRow, startColumn, color, visited, spielfeld); //start depth first search
    return visited; //return visited cells
}

int countVisited(std::vector<std::vector<int>>& visited, std::vector<std::vector<char>>& spielfeld) { //const ?
    int count = 0;
    for (int i = 0; i < visited.size(); ++i) {
        for (int j = 0; j < visited[i].size(); ++j) {
            if (visited[i][j] == 1 && spielfeld[i][j] != 0) {
                ++count;
            }
        }
    }
    //std::cout << count << std::endl; //DEBBUGING
    return count;
}

void gamestep(std::vector<std::vector<char>>& spielfeld, std::vector<std::vector<int>>& visited) {
    int visitedCount = countVisited(visited, spielfeld);
    if (visitedCount > 1) {
        for (int i = 0; i < spielfeld.size(); ++i) {
            for (int j = 0; j < spielfeld[0].size(); ++j) {
                if (visited[i][j] == 1) {
                    spielfeld[i][j] = 0;
                }
            }
        }
    }

    // apply gravity
    for (int j = 0; j < spielfeld[0].size(); ++j) {     
        int emptyRow = spielfeld.size() - 1;
        for (int i = spielfeld.size() - 1; i >= 0; --i) {
            if (spielfeld[i][j] != 0) {
                std::swap(spielfeld[i][j], spielfeld[emptyRow][j]); // swap current cell with the first empty cell from the bottom in the current column
                emptyRow--;  // move index of the first empty cell up to the next row
            }
        }
    }

    // shove columns together to the right
    int emptyCol = spielfeld[0].size() - 1;     //variable that stores the index of the first empty column
    for (int j = spielfeld[0].size() - 1; j >= 0; --j) {
        bool isEmpty = true; //assumes column is empty
        for (int i = 0; i < spielfeld.size(); ++i) {
            if (spielfeld[i][j] != 0) {
                isEmpty = false;
                break; // if current cell not empty then skips rest of cells in column
            }
        }
        if (!isEmpty) { 
            for (int i = 0; i < spielfeld.size(); ++i) {
                std::swap(spielfeld[i][j], spielfeld[i][emptyCol]); // swap each cell in the current column with the corresponding cell in first empty column
            }
            emptyCol--; // move index of the first empty column to the left, because the current is not longer empty
        }
    }
}

// void printBoard(const std::vector<std::vector<char>>& spielfeld) {
//     // column headers
//     std::cout << "  ";
//     for (int i = 0; i < spielfeld[0].size(); ++i) {
//         std::cout << static_cast<char>('a' + i) << " ";
//     }
//     std::cout << "\n";

//     // rows with headers
//     for (int i = 0; i < spielfeld.size(); ++i) {
//         std::cout << i + 1 << " ";
//         for (int j = 0; j < spielfeld[i].size(); ++j) {
//             std::cout << spielfeld[i][j] << " ";
//         }
//         std::cout << "\n";
//     }
// }

void printBoard(const std::vector<std::vector<char>>& spielfeld) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "\033[1m" << "===================" << "\033[0m" << std::endl;
    //std::cout << "===================" << std::endl;
    // column headers
    std::cout << "  ";
    for (int i = 0; i < spielfeld[0].size(); ++i) {
        std::cout << static_cast<char>('a' + i) << " "; // static cast to revert back to char
    }
    std::cout << "\n";

    // rows with headers
    for (int i = 0; i < spielfeld.size(); ++i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < spielfeld[i].size(); ++j) {
            switch (spielfeld[i][j]) {
                case 'B':
                    SetConsoleTextAttribute(hConsole, 1);
                    std::cout << "# ";
                    break;
                case 'R':
                    SetConsoleTextAttribute(hConsole, 4);
                    std::cout << "# ";
                    break;
                case 'G':
                    SetConsoleTextAttribute(hConsole, 2);
                    std::cout << "# ";
                    break;
                case 'Y':
                    SetConsoleTextAttribute(hConsole, 14);
                    std::cout << "# ";
                    break;
                case 'P':
                    SetConsoleTextAttribute(hConsole, 5);
                    std::cout << "# ";
                    break;
                default:
                    SetConsoleTextAttribute(hConsole, 15);
                    std::cout << "  ";
                    break;
            }
        }
        SetConsoleTextAttribute(hConsole, 15);
        std::cout << "\n";
    }
}

int scoreUpdate(std::vector<std::vector<int>>& visited, std::vector<std::vector<char>>& spielfeld, int& score) {
    int n = 0;
    int visitedCount = countVisited(visited, spielfeld);
    if (visitedCount > 1) { 
        for (int i = 0; i < visited.size(); ++i) {
            for (int j = 0; j < visited[0].size(); ++j) {
                if (visited[i][j] == 1 & spielfeld[i][j] != 0) { // check if cell is visited and not empty 
                    ++n;
                }
            }
        }
        int subscore = n*(n-1);
        score += subscore;
    }
    return score;
}

bool gameover(std::vector<std::vector<char>>& spielfeld) {
    for (int i = 0; i < spielfeld.size(); ++i) {
        for (int j = 0; j < spielfeld[i].size(); ++j) {
            if (spielfeld[i][j] != 0) {
                if ((j + 1 < spielfeld[i].size() && spielfeld[i][j] == spielfeld[i][j + 1]) ||
                    (i + 1 < spielfeld.size() && spielfeld[i][j] == spielfeld[i + 1][j]) ||
                    (i - 1 >= 0 && spielfeld[i][j] == spielfeld[i - 1][j]) ||
                    (j - 1 >= 0 && spielfeld[i][j] == spielfeld[i][j - 1])) {
                    return false;
                }
            }
        }
    }
    return true;
}

void createScoresFile() {
    std::ofstream file("scores.txt", std::ios::app);
    if (!file) {
        std::cerr << "Failed to create scores.txt" << std::endl;
        return;
    }
    file.close();
}

void saveScore(int score, std::string name) {
    std::ofstream file("scores.txt", std::ios::app);
    if (file.is_open()) {
        file << name << ": " << score << std::endl;
        file.close();
    }
}

void loadScores() {
    std::cout << "\033[1m" << "Leaderboard: " << "\033[0m";
    std::ifstream file("scores.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
}

void newGame(int& score, const std::string& colors, std::vector<std::vector<char>>& spielfeld, std::vector<std::vector<int>>& visited) {
    std::cout << "Do you want to start a new game? (y/n)" << std::endl;
    std::string answer;
    std::getline(std::cin, answer);
    char firstChar = answer[0];
    if (firstChar == 'y' || firstChar == 'Y') {
        std::cout << "Starting new game..." << std::endl;   
        fillBoard(spielfeld, colors);
        score = 0;
        // std::string name = getName();
        gameLoop(spielfeld, colors, score, visited);
    } else if (firstChar == 'n' || firstChar == 'N') {
        std::cout << "Exiting..." << std::endl;
        exit(0);
    } else {
        std::cout << "\033[1;31m" << "Invalid input. Retry Input." << "\033[0m" << std::endl;
        //std::cout << "Invalid input. Retry Input." << std::endl;
        newGame(score, colors, spielfeld, visited);
    }
}
void gameLoop(std::vector<std::vector<char>>& spielfeld, const std::string& colors, int& score, std::vector<std::vector<int>>& visited) {
    while (true) {
        
        printBoard(spielfeld);
        std::cout << "\033[1m" << "Score: " << score << "\033[0m" << std::endl;
        //std::cout << "Score: " << score << std::endl;
        std::cout << "\033[1m" << "===================" << "\033[0m" << std::endl;
        //std::cout << "===================" << std::endl;
        std::cout << "Enter your move: ";
        std::pair<int, int> move = getMove(spielfeld);
        std::vector<std::vector<int>> group = findGroup(move, spielfeld, visited);
        std::vector<std::vector<char>> spielfeldCopy = spielfeld;
        gamestep(spielfeld, group); 
        scoreUpdate(visited, spielfeldCopy, score);
        
        bool isGameOver = gameover (spielfeld);
        if (isGameOver) {
            std::cout << "\033[1m" << "Game over!" << "\033[0m" << std::endl;
            //std::cout << "Game over!" << std::endl;
            std::string name = getName();
            saveScore(score, name);
            loadScores();
            newGame(score, colors, spielfeld, visited);
            break;
        }
    }
}

std::string getName() {
    std::cout << "Enter your player name: " << std::endl;
    std::string name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline
    std::getline(std::cin, name);
    if (name.empty()) {
        std::cout << "No name entered. Using default name 'Player'" << std::endl;
        name = "Player";
    }
    return name;
}

int main () {
    std::string asciiArt = R"(
     _____                       _____                      
    / ____|                     / ____|                     
   | (___   __ _ _ __ ___   ___| |  __  __ _ _ __ ___   ___ 
    \___ \ / _` | '_ ` _ \ / _ \ | |_ |/ _` | '_ ` _ \ / _ \
    ____) | (_| | | | | | |  __/ |__| | (_| | | | | | |  __/
    _____/ \__,_|_| |_| |_|\___|\_____|\__,_|_| |_| |_|\___|
    )";
    printColoredAsciiArt(asciiArt);
        
    int score = 0;
    createScoresFile();
    std::cout << "\033[1m" << "Welcome to SameGame!" << "\033[0m" << std::endl;
    std::cout << "Now 100 % bug free." << std::endl;
    std::vector<std::vector<char>> spielfeld(9,std::vector<char>(9));
    std::string colors = "RGBYP"; // Red, Green, Blue, Yellow, Purple
    std::vector<std::vector<int>> visited(spielfeld.size(), std::vector<int>(spielfeld[0].size(), 0)); 
    fillBoard(spielfeld, colors);
    gameLoop(spielfeld, colors, score, visited);

    return 0;
}