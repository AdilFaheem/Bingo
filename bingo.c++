#include "util.h"
#include <vector>
#include <set>

using namespace std;

struct player{
    string name;
    vector<set<int>> board;
};

void generateCard(player &p){
    // Copy your code from the previous exercise
    set<int> used;
    set<int> temp;
    int min = 1;
    int max = 15;
    int index = 0;
    
    for(int i = 0; i < 5; i++){
        while(temp.size() < 5){
            int random = randInt(min, max);
            if(used.find(random) == used.end()){
                temp.insert(random);
                used.insert(random);
                min += 15;
                max += 15;
            }else{
                random = randInt(min, max);
            }
        }
        min = 1;
        max = 15;
        p.board.push_back(temp);
        temp.clear();
    }
    
}

void printBlankCard(player &p){
    // Copy your code from the previous exercise
    cout << "\t\t" << p.name << endl;
    cout << "----------------------------------" << endl;
    for(int i = 0; i < 5; i++){
        for(auto itr : p.board[i]){
            cout << itr << "\t";
        }
        cout << endl;
    }
}

void printMarkedCard(set<int> &numbers, player &p){
    // Copy your code from the previous exercise
    cout << "\t\t" << p.name << endl;
    cout << "----------------------------------" << endl;
    for(int i = 0; i < 5; i++){
        for(auto itr : p.board[i]){
            if(numbers.find(itr) != numbers.end()){
                cout << "X" << "\t";
            }else{
                cout << itr << "\t";
            }
        }
        cout << endl;
    }
}

void playTurn(set<int> &numbers, vector<player> &players, int &turn) {
    int num;
    while(true){
        num = randInt(1,75);
        if(numbers.insert(num).second) break;
    }
    cout << "Round: " << turn << endl;
	cout << "You pulled " << num << endl;
	for (player p : players) {
		printMarkedCard(numbers, p);
		cout << endl;
	}
	turn++;
}


/* This function will take the set of
 * numbers and a player's card and
 * return true if their card has bingo. Otherwise
 * return false.
 * A card has bingo if all the numbers in a row,
 * column, or one of the diagonals have been
 * called.
 */
vector<vector<int> > turnVector(player &p){
    vector<vector<int> > temp = {{}, {}, {}, {}, {}};
    
    for(int i = 0; i < 5; i++){
        auto itr = p.board[i].begin();
        temp[0].push_back(*itr++);
        temp[1].push_back(*itr++);
        temp[2].push_back(*itr++);
        temp[3].push_back(*itr++);
        temp[4].push_back(*itr);
        //cout << temp[0][i] << " " << temp[1][i] << " " << temp[2][i] << " " << temp[3][i] << " " << temp[4][i] << endl;
    }
    return temp;
}

bool checkRow(set<int> numbers, player &p){
    int count = 0;
    for(int i = 0; i < 5; i++){
        for(auto itr : numbers){
            if(p.board[i].find(itr) != p.board[i].end()){
                count++;
                if(count == 5){
                    return true;
                }
            }
        }
        count = 0;
    }
    return false;
}

bool checkCol(set<int> numbers, player &p){
    int count = 0;
    vector<vector<int> > temp = turnVector(p);
    
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(numbers.find(temp[i][j]) != numbers.end()){
                count++;
                if(count == 5){
                    return true;
                }
            }
        }
        count = 0;
    }
    return false;
}

bool checkDiag(set<int> numbers, player &p){
    int count = 0;
    vector<vector<int> > temp = turnVector(p);
    
    for(int i = 0; i < 5; i++){
        if(numbers.find(temp[i][i]) != numbers.end()){
            count++;
            if(count == 5){
                return true;
            }
        }
    }
    count = 0;
    for(int i = p.board[0].size(); i < 0; i--){
        if(numbers.find(temp[i][i]) != numbers.end()){
            count++;
            if(count == 5){
                return true;
            }
        }
    }
    return false;
}

bool checkWinner(set<int> numbers, player &p){
	return checkRow(numbers, p) || checkCol(numbers, p) || checkDiag(numbers, p);
}

int main(){

    // Start with your previous code
    // Add the option to auto-play until
    // a winner is found, then print that
    // winner.
    
    player abel;
    abel.name = "Abel";
    generateCard(abel);
    
    player adil;
    adil.name = "Adil";
    generateCard(adil);
    
    player winner;
    vector<player> players;
    set<int> numbers;
    int turn = 1;
    
    players.push_back(abel);
    players.push_back(adil);
    
    while(true){
        cout << "Would you like to:" << endl;
        cout << "1) Play one turn" << endl;
        cout << "2) Print player's cards" << endl;
        cout << "3) Add a player" << endl;
        cout << "4) Auto play to win" << endl;
        cout << "5) Reset with same players" << endl;
        cout << "6) Exit" << endl;
        
        int input = readInt(1, 6, "> ", "Enter a valid input.\n> ");
        
        if(input == 1){
            playTurn(numbers, players, turn);
            for(player p : players){
                if(checkWinner(numbers, p)){
                    cout << "\t" << p.name << " wins!" << endl;
                    goto gameEnd;
                }
            }
        }else if(input == 2){
            for(player p : players){
                printMarkedCard(numbers, p);
            }
        }else if(input == 3){
            player p;
            p.name = readLine("Enter the player's name: ");
            generateCard(p);
            printBlankCard(p);
            players.push_back(p);
        }else if(input == 4){
            while(true){
                playTurn(numbers, players, turn);
                for(player p : players){
                    if(checkWinner(numbers, p)){
                        cout << "\t" << p.name << " wins!" << endl;
                        goto gameEnd;
                    }
                }
            }
        }else if(input == 5){
            for(player p : players){
                p.board.clear();
                generateCard(p);
                printBlankCard(p);
            }
            numbers.clear();
        }else if(input == 6){
            break;
        }
        
        gameEnd:
        cout << "";
    }
    

    return 0;
}
