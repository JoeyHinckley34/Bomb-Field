//------------------------
//Game I created using c++
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

//funciton which creates a board
vector<vector<int> > createboard(int size,int level){
    srand((int)time(0));
    vector<vector<int> > board;
    int num1;
    int num2;
    for(int x = 0; x < size; x++ ){
        vector<int> temp;
        for(int y = 0; y < size; y++ ){
            if(level == 1){
                num1 = rand()%3;
                num2 = rand()%3;
                if(num1 < num2) {
                    temp.push_back(num1);
                }else{
                    temp.push_back(num2);
                }
            }else if(level == 2){
                num1 = rand()%4;
                temp.push_back(num1);
            }else{
                num1 = rand()%4;
                num2 = rand()%4;
                if(num1 < num2) {
                    temp.push_back(num1);
                }else{
                    temp.push_back(num2);
                }
            }
        }
        board.push_back(temp);
    }
    return board;
}

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

void printboard(vector<vector<int> > board, vector<vector<bool> > moves,vector<pair<int,int> > r, vector<pair<int,int> > c,int level){
    cout << "LEVEL: " << level << endl;
    cout << setw(4) << "-" << "----------------------------------------" << endl;
    cout << setw(4) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << endl;
    for(int x = 0; x < board.size(); x++ ){
        for(int y = 0; y < board.size(); y++ ){
            if(moves[x][y]){
                if(board[x][y] > 1){
                    cout << setw(7) << "|   " << BOLDCYAN << board[x][y] << WHITE;
                }else{
                    cout << setw(7) << "|   " << BOLDBLUE << board[x][y] << WHITE;
                }
            }else{
                cout << setw(7) << "|   "  << BOLDYELLOW << "?" << WHITE;
            }
        }
        cout << setw(4) << "|" << setw(4) << GREEN << (5-x) << WHITE <<"  P: " << r[x].first;
        if( (r[x].first-9) > 0){
            cout << setw(5) << "B: " << r[x].second << "\n";
        }else{
            cout << setw(6) << "B: " << r[x].second << "\n";
        }
        cout << setw(4) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << endl;
        cout << setw(4) << "-" << "----------------------------------------" << endl;
        if(x != 4){
            cout << setw(4) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << setw(8) << "|" << endl;
        }
    }
    cout << GREEN << setw(8) << 1 << setw(8) << 2 << setw(8) << 3 << setw(8) << 4 << setw(8) << 5 << WHITE << endl;
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
}

void printanswer(vector<vector<int> > board, vector<pair<int,int> > r, vector<pair<int,int> > c, bool win){
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
        if(x != 4){
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
    
    if(win){
        cout<< "NICE" <<endl;
    }else{
        cout << "Better Luck Next Time" << endl;
    }
    
}

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

void startup(){
    cout << "Welcome to Bombfield" << endl;
    cout << "The Goal of this game is to uncover all the tiles with points greater than 1.\nBe careful not to hit any bombs!\nEach row and column have two values.\nOne for the number of points and one for the number of bombs\n\nHint!\nYou dont have to worry about flipping ALL the tiles, just the tiles greater than 1\nGood Luck:)\n" << endl;
    
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
    cout << "Please enter a row and column number in this format: 4,3\nThis would be the third row and fourth column" << endl;
    cout << "\nReady to Start?(type your name)" <<endl;
}

//loads the database file
vector<pair<string,int> > loadleaderboard(const std::string &filename) {
    // open the file for reading
    std::ifstream istr (filename.c_str());
    if (!istr) {
        std::cerr << "ERROR: could not open " << filename << " for reading" << std::endl;
    }
    //rids the top line and assgins them to variables
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

bool updateleaderboard(const std::string &filename, string name, int level, vector<pair<string,int> > &leaderboard) {
    bool found = false;
    bool pr = false;
    
    for(int x = 0; x < leaderboard.size(); x++){
        if(leaderboard[x].first == name){
            found = true;
            if(leaderboard[x].second < level){
                leaderboard[x].second = level;
                pr = true;
            }
        }
    }
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

bool sortByVal(const pair<string, int> &a,const pair<string, int> &b){
    return (a.second > b.second);
}


int main(int argc, char** argv){
    cout << RESET;
    system("clear");
    if(argc != 2){
        std::cerr << "Proper usage is " << argv[0] << "[leaderboard file]" << std::endl;
        return -1;
    }
    startup();

    
    vector<pair<string,int> > leaderboard = loadleaderboard(argv[1]);
    
    //vector to hold board
    vector<vector<int> > board = createboard(5,1);
    //vector to hold which tile user has flipped
    vector<vector<bool> > moves = createturns(5);
    //vector to hold the points and bombs in a row
    vector<pair<int,int> > rows = getrows(board);
    //vector to hold the points and bombs in a col
    vector<pair<int,int> > cols = getcols(board);
    
    string name;
    cin >> name;
    int level = 1;
    system("clear");
    printboard(board, moves, rows,cols,level);
    string input;
    while(true){
        cin >> input;
        system("clear");
        if(input == "q"){
            break;
        }
        if(input.size() != 3){
            cout << "Please enter a valid position for example: 2,3" << endl;
        }else{
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
            printanswer(board, rows,cols,false);
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
            printboard(board, moves, rows,cols,level);
        } else if( boardwin(board,moves) == true){
            printanswer(board, rows,cols,true);
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
            printboard(board, moves, rows,cols,level);
        }else{
            printboard(board, moves, rows,cols,level);
        }
    }
    cout << RESET;
    return 0;
}
