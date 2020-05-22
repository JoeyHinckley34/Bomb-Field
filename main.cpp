//------------------------
//Game I created using c++
//Rules are explained if you just run the file
//Made using the terminal window
//Only tested on Mac
//Usage is [executable file] [text file for leaderboard]
//type this in command line to use
//      g++ main.cpp -o test.out -Wall
//      ./test.out leaderboard.txt
//Let me know what you think!
//------------------------





#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <map>

//coloring the test in the terminal window
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using namespace std;

//funciton which creates a board each level
vector<vector<int> > createboard(int size,int level){
    srand((int)time(0));
    //board is stored as a vector of vectors of type int
    vector<vector<int> > board;
    //variables used to determine what the value of each cell should be
    int num1;
    int num2;
    //Nested Loops to populate the board
    for(int x = 0; x < size; x++ ){
        //vector which will hold the values of each row
        vector<int> temp;
        //Loop to populate each row
        for(int y = 0; y < size; y++ ){
            //My challenge in making this game is making each level feel different yet random everytime
            //For level 1 I only wanted a few twos and no threes
            //This level should be easy as most of the rows and columns add up to 5 so they dont have to be touched
            if(level == 1){
                //Assigns either a 0,1,2 to each variable
                num1 = rand()%3;
                num2 = rand()%3;
                //Populates the board with the lowest number
                if(num1 < num2) {
                    temp.push_back(num1);
                }else{
                    temp.push_back(num2);
                }
            //For level 2 I introduce 3s to the game
            //This makes the user have to flip over much more tiles but there are much less bombs
            }else if(level == 2){
                num1 = rand()%4;
                temp.push_back(num1);
            //From level 3 on the difficulty remains the same
            //There are much more bombs than level 2 but still 3s
            }else{
                //Assigns either a 0,1,2,4 to each variable
                num1 = rand()%4;
                num2 = rand()%4;
                //Populates the board with the lowest number
                if(num1 < num2) {
                    temp.push_back(num1);
                }else{
                    temp.push_back(num2);
                }
            }
        }
        //adds the row to the board
        board.push_back(temp);
    }
    //returns to board
    return board;
}

//Function which creates the same size vector as the board but with boolean values to keep track of where the user has gone
//Since I use this function at the start of every new board I set all the values to false
vector<vector<bool> > createturns(int size){
    vector<vector<bool> > moves;
    for(int x = 0; x < size; x++ ){
        vector<bool> temp;
        for(int y = 0; y < size; y++ ){
            temp.push_back(false);
        }
        moves.push_back(temp);
    }
    return moves;
}

//Function which prints out the board
//Takes in the board, where the player has gone, the value of points and bombs in each row and column, and the current level
void printboard(vector<vector<int> > board, vector<vector<bool> > moves, vector<pair<int,int> > r, vector<pair<int,int> > c,int level, int size){
    cout << "LEVEL: " << level << endl;
    cout << setw(4) << "-" << "----------------------------------------" << endl;
    cout << setw(4) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << endl;
    //loops through the board
    for(int x = 0; x < board.size(); x++ ){
        for(int y = 0; y < board.size(); y++ ){
            //If a player has gone in the spot it prints out the value at that spot
            if(moves[x][y]){
                //If a player needed to flip the tile it is printed in Cyan otherwise Blue
                if(board[x][y] > 1){
                    cout << setw(7) << "|   " << BOLDCYAN << board[x][y] << WHITE;
                }else{
                    cout << setw(7) << "|   " << BOLDBLUE << board[x][y] << WHITE;
                }
            //Otherwise prints a ?
            }else{
                cout << setw(7) << "|   "  << BOLDYELLOW << "?" << WHITE;
            }
        }
        //prints the points for the row
        cout << setw(4) << "|" << setw(4) <<  " " << GREEN << (5-x) << WHITE <<"  P: " << r[x].first;
        //prints the  bombs for the row
        if( (r[x].first-9) > 0){
            cout << setw(5) << "B: " << r[x].second << "\n";
        }else{
            cout << setw(6) << "B: " << r[x].second << "\n";
        }
        cout << setw(4) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << endl;
        cout << setw(4) << "-" << "----------------------------------------" << endl;
        if(x != (size - 1)){
            cout << setw(4) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << endl;
        }
    }
    cout << GREEN << setw(8) << 1 << setw(8) << 2 << setw(8) << 3 << setw(8) << 4 << setw(8) << 5 << WHITE << endl;
    cout << setw(8) << "P: " << c[0].first;
    //Prints the points for each column
    for(int x = 1; x < board.size(); x++ ){
        if( (c[x-1].first-9) > 0){
           cout << setw(6) << "P: " << c[x].first;
        }else{
            cout << setw(7) << "P: " << c[x].first;
        }
    }
    cout << "\n";
    cout << setw(8) << "B: " << c[0].second;
    //Prints the bombs for each column
    for(int x = 1; x < board.size(); x++ ){
        if( (c[x-1].second-9) > 0){
           cout << setw(7) << "B: " << c[x].second;
        }else{
            cout << setw(7) << "B: " << c[x].second;
        }
    }
    cout << "\n";
}

//Function which prints out if the player has won the game
void printanswer(vector<vector<int> > board, vector<pair<int,int> > r, vector<pair<int,int> > c, bool win, int size){
    //Very Similar to last function
    cout << setw(4) << "-" << "----------------------------------------" << endl;
    cout << setw(4) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << endl;
    for(int x = 0; x < board.size(); x++ ){
        for(int y = 0; y < board.size(); y++ ){
            if(board[x][y] == 0){
                cout << setw(7) << "|   " << RED << "B" << WHITE;
            }else{
                if(board[x][y] > 1){
                    cout << setw(7) << "|   " << CYAN << board[x][y] << WHITE;
                }else{
                    cout << setw(7) << "|   " << BLUE << board[x][y] << WHITE;
                }
            }
        }
        cout << setw(4) << "|" << setw(4) << "P: " << r[x].first;
        if( (r[x].first-9) > 0){
            cout << setw(5) << "B: " << r[x].second << "\n";
        }else{
            cout << setw(6) << "B: " << r[x].second << "\n";
        }
        cout << setw(4) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << endl;
        cout << setw(4) << "-" << "----------------------------------------" << endl;
        if(x != (size-1)){
            cout << setw(4) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << endl;
        }
    }
    cout << setw(8) << "P: " << c[0].first;
    for(int x = 1; x < board.size(); x++ ){
        if( (c[x-1].first-9) > 0){
           cout << setw(6) << "P: " << c[x].first;
        }else{
            cout << setw(7) << "P: " << c[x].first;
        }
    }
    cout << "\n";
    cout << setw(8) << "B: " << c[0].second;
    for(int x = 1; x < board.size(); x++ ){
        if( (c[x-1].second-9) > 0){
           cout << setw(7) << "B: " << c[x].second;
        }else{
            cout << setw(7) << "B: " << c[x].second;
        }
    }
    cout << "\n";
    //Congradulates the user if they have won the game
    if(win){
        cout<< "NICE" <<endl;
    }else{
        cout << "Better Luck Next Time" << endl;
    }
}

//Function which gets the points and the bombs of a row
vector<pair<int,int> > getrows(vector<vector<int> > b){
     vector<pair<int,int> > rows;
     int points;
     int bombs;
     for(int x = 0; x < b.size(); x++ ){
         pair<int,int> r;
         points = 0;
         bombs = 0;
         for(int y = 0; y < b[x].size(); y++ ){
             points += b[x][y];
             if ( b[x][y] == 0 ){
                 bombs++;
             }
         }
         r.first = points;
         r.second = bombs;
         rows.push_back(r);
     }
     return rows;
}

//Function which gets the points and the bombs of a column
 vector<pair<int,int> > getcols(vector<vector<int> > b){
     vector<pair<int,int> > rows;
     int points;
     int bombs;
     for(int x = 0; x < b.size(); x++ ){
         pair<int,int> r;
         points = 0;
         bombs = 0;
         for(int y = 0; y < b[x].size(); y++ ){
             points += b[y][x];
             if ( b[y][x] == 0 ){
                 bombs++;
             }
         }
         r.first = points;
         r.second = bombs;
         rows.push_back(r);
     }
     return rows;
}

//returns whether or not the user has lost
bool boardlose(vector<vector<int> > board, vector<vector<bool> > moves){
    for(int x = 0; x < board.size(); x++ ){
        for(int y = 0; y < board.size(); y++ ){
            if(moves[x][y] && board[x][y] == 0){
                return true;
            }
        }
    }
    return false;
}

//returns whether or not the user has won
bool boardwin(vector<vector<int> > board, vector<vector<bool> > moves){
    for(int x = 0; x < board.size(); x++ ){
        for(int y = 0; y < board.size(); y++ ){
            if(!moves[x][y] && (board[x][y] == 2 || board[x][y] == 3 ) ){
                return false;
            }
        }
    }
    return true;
}

//Function which is used at the start of the game
void startup(){
    cout << "Welcome to Bombfield" << endl;
    cout << "The Goal of this game is to uncover all the tiles with points greater than 1.\nBe careful not to hit any bombs!\nEach row and column have two values.\nOne for the number of points and one for the number of bombs\n\nHint!\nIf a row or column adds up to 5 dont touch it\nGood Luck:)\n" << endl;
    //Prints out example board
    cout << setw(4) << "-" << "----------------------------------------" << endl;
    cout << setw(4) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << endl;
    for(int x = 0; x < 5; x++ ){
        for(int y = 0; y < 5; y++ ){
            if(x == 2&& y == 3){
                cout << setw(7) << "|   " << BOLDGREEN << "X" << WHITE;
            }else{
                cout << setw(4) << "|" << setw(4) << "?";
            }
        }
        cout << setw(4) << "|" <<endl;
        cout << setw(4) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << endl;
        cout << setw(4) << "-" << "----------------------------------------" << endl;
        if(x!=4){
            cout << setw(4) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << endl;
        }
    }
    cout << "Please enter a row and column number in this format: 4,3" << endl;
    cout << "\nReady to Start?(type your name)" <<endl;
}

//loads the database file returning a vector of pairs with the name and level
vector<pair<string,int> > loadleaderboard(const std::string &filename) {
    // open the file for reading
    std::ifstream istr (filename.c_str());
    if (!istr) {
        std::cerr << "ERROR: could not open " << filename << " for reading" << std::endl;
    }
    vector<pair<string,int> > leaderboard;
    pair<string,int> player;
    string name;
    int level;
    while (istr >> name){
        istr >> level;
        player.first = name;
        player.second = level;
        leaderboard.push_back(player);
    }
    return leaderboard;
}

//updates the leader board file and returns true if the user sets a  new personal record
bool updateleaderboard(const std::string &filename, string name, int level, vector<pair<string,int> > &leaderboard) {
    bool found = false;
    bool pr = false;
    //Finds the player
    for(int x = 0; x < leaderboard.size(); x++){
        if(leaderboard[x].first == name){
            found = true;
            if(leaderboard[x].second < level){
                leaderboard[x].second = level;
                pr = true;
            }
        }
    }
    //adds player if not already there
    if(!found){
        pair<string,int> player;
        player.first = name;
        player.second = level;
        leaderboard.push_back(player);
    }
    ofstream myfile;
    myfile.open(filename, std::ofstream::out | std::ofstream::trunc);
    for(int x = 0; x < leaderboard.size(); x++){
       myfile << leaderboard[x].first << " " << leaderboard[x].second  << "\n";
    }
    myfile.close();
    return pr;
}

//Sort Function for leaderboard
bool sortByVal(const pair<string, int> &a,const pair<string, int> &b){
    return (a.second > b.second);
}


int main(int argc, char** argv){
    //Resets colors and the sytem
    cout << RESET;
    system("clear");
    //Error message if improper usage
    if(argc != 2){
        std::cerr << "Proper usage is " << argv[0] << " [leaderboard file]" << std::endl;
        return -1;
    }
    
    startup();
    //loads leader board
    vector<pair<string,int> > leaderboard = loadleaderboard(argv[1]);
    
    //vector to hold board
    vector<vector<int> > board = createboard(5,1);
    //vector to hold which tile user has flipped
    vector<vector<bool> > moves = createturns(5);
    //vector to hold the points and bombs in a row
    vector<pair<int,int> > rows = getrows(board);
    //vector to hold the points and bombs in a col
    vector<pair<int,int> > cols = getcols(board);
    //gets player name
    string name;
    cin >> name;
    //sets level to 1
    int level = 1;
    //clears screen
    system("clear");
    //prints the board
    printboard(board, moves, rows,cols,level,5);
    //variable to hold the input
    string input;
    //game loop continues until user types in the letter q
    while(input != "q"){
        cin >> input;
        //clears screen
        system("clear");
        if(input.size() != 3){
            cout << "Please enter a valid position for example: 2,3" << endl;
        }else{
            //gets the position from the user
            pair<int,int> pos;
            int col = (int)(input[0])-48;
            int row = (int)(input[2])-48;
            pos.first = row;
            pos.second = col;
            if(pos.first > 5 || pos.second > 5){
                cout << "Please enter a value within the bounds of the grid" << endl;
            }else{
                if(pos.first == 1){
                     moves[4][pos.second-1] = true;
                }else if(pos.first == 2){
                     moves[3][pos.second-1] = true;
                }else if(pos.first == 3){
                     moves[2][pos.second-1] = true;
                }else if(pos.first == 4){
                     moves[1][pos.second-1] = true;
                }else if(pos.first == 5){
                     moves[0][pos.second-1] = true;
                }
  
            }
        }
        if(boardlose(board,moves) == true ){
            printanswer(board, rows,cols,false,5);
            bool pr = updateleaderboard(argv[1],name,level,leaderboard);
            level = 1;
            sort(leaderboard.begin(), leaderboard.end(), sortByVal);
            if(pr){
                cout << "NEW RECORD!!!" << endl;
                cout << "Leaderboard:" << endl;
                for(int x = 0; x < leaderboard.size(); x++){
                   cout << leaderboard[x].first << " " << leaderboard[x].second  << "\n";
                }
            }
            system( "read -n 1 -s -p \"Press any key to continue...\"" );
            system("clear");
            for(int x  = 0; x < board.size(); x++ ){
                board[x].clear();
                moves[x].clear();
            }
            board = createboard(5,level);
            moves = createturns(5);
            rows.clear();
            cols.clear();
            rows = getrows(board);
            cols = getcols(board);
            printboard(board, moves, rows,cols,level,5);
        } else if( boardwin(board,moves) == true){
            printanswer(board, rows,cols,true,5);
            level += 1;
            system( "read -n 1 -s -p \"Press any key to continue...\n\"" );
            system("clear");
            for(int x  = 0; x< board.size(); x++ ){
                board[x].clear();
                moves[x].clear();
            }
            board = createboard(5,level);
            moves = createturns(5);
            rows.clear();
            cols.clear();
            rows = getrows(board);
            cols = getcols(board);
            printboard(board, moves, rows,cols,level,5);
        }else{
            printboard(board, moves, rows,cols,level,5);
        }
    }
    cout << RESET;
    return 0;
}
