#include<iostream>
#include<cstdlib>
#include<vector>
#include<ctime>

using namespace std;

void board(int r, int c){
    int i, j;

    for(i = 1; i < c+1; i++) cout << "\t"<< i;
    cout << endl;
    cout << endl;
    for(i = 1; i < r+1; i ++){
        cout << i << "\t";
        for(j = 1; j < c+1; j++){
            cout << "RC" << "\t";
        }
        cout<<endl;
    }
}

void place_mines(vector<vector <int> >&t, int r, int c, int m){
    int col, row;
    for(int i = 0; i < m; i++){
        col = rand()%(c-2)+1;
        row = rand()%(r-2)+1;
        if(t[row][col] < 9){
            t[row][col] = 9;
            t[row-1][col-1]++;
            t[row-1][col]++;
            t[row][col-1]++;
            t[row+1][col+1]++;
            t[row+1][col]++;
            t[row][col+1]++;
            t[row-1][col+1]++;
            t[row+1][col-1]++;
        }
        else i--;
    }
}

void check_if_zero(vector<vector <int> >& t,vector<vector <int> >& if_revealed,int r, int c, int row, int col){
    if(row < r-1 && row > 0 && col < c-1 && col > 0) {
            if_revealed[row][col] = 1;
            if (t[row - 1][col - 1] == 0 && if_revealed[row - 1][col - 1] == 0) check_if_zero(t, if_revealed, r, c, row - 1, col - 1);
            else if_revealed[row - 1][col - 1] = 1;
            if (t[row - 1][col] == 0 && if_revealed[row - 1][col] == 0)  check_if_zero(t, if_revealed, r, c, row - 1, col);
            else if_revealed[row - 1][col] = 1;
            if (t[row][col - 1] == 0 && if_revealed[row][col - 1] == 0) check_if_zero(t, if_revealed, r, c, row, col - 1);
            else if_revealed[row][col - 1] = 1;
            if (t[row + 1][col + 1] == 0 && if_revealed[row + 1][col + 1] == 0) check_if_zero(t, if_revealed, r, c, row + 1, col + 1);
            else if_revealed[row + 1][col + 1] = 1;
            if (t[row + 1][col] == 0 && if_revealed[row + 1][col] == 0) check_if_zero(t, if_revealed, r, c, row + 1, col);
            else if_revealed[row + 1][col] = 1;
            if (t[row][col + 1]  == 0 && if_revealed[row][col + 1]  == 0) check_if_zero(t, if_revealed, r, c, row, col + 1);
            else if_revealed[row][col + 1] = 1;
            if (t[row - 1][col + 1]  == 0 && if_revealed[row - 1][col + 1]  == 0) check_if_zero(t, if_revealed, r, c, row - 1, col + 1);
            else if_revealed[row - 1][col + 1] = 1;
            if (t[row + 1][col - 1]  == 0 && if_revealed[row + 1][col - 1] == 0) check_if_zero(t, if_revealed, r, c, row + 1, col - 1);
            else if_revealed[row + 1][col - 1] = 1;
    }
}
void start(vector<vector <int> >& t, int r, int c, int m){
    int row, col, i, j;

    vector<vector<int>> if_revealed( (r) , vector<int> ((c), 0));

    while(true){
        cout << "Choose row to reveal: " << endl;
        cin >> row;
        if(std::cin.fail()){
            cout << "It is not a numer, choose again." << endl;
            cin.clear();
            cin.ignore(1000, '\n' );
            continue;
        }
        if(row > r-1 || row < 1){
            cout << "Out of range, choose again." << endl;
            cin.clear();
            cin.ignore(1000, '\n' );
            continue;
        }
        cin.clear();
        cin.ignore(1000, '\n' );
        cout << "Choose column to reveal: " << endl;
        cin >> col;
        if(std::cin.fail()){
            cout << "It is not a numer, choose again." << endl;
            cin.clear();
            cin.ignore(1000, '\n' );
            continue;
        }
        if(col > c-2 || col < 1){
            cout << "Out of range, choose again." << endl;
            cin.clear();
            cin.ignore(1000, '\n' );
            continue;
        }
        cin.clear();
        cin.ignore(1000, '\n' );
        if(t[row][col] >= 9) {
            cout << "Game over" << endl;
            for (i = 1; i < c - 1; i++) cout << "\t" << i;
            cout << endl;
            cout << endl;
            for (i = 1; i < r - 1; i++) {
                cout << i << "\t";
                for (j = 1; j < c - 1; j++) {
                        if (t[i][j] >= 9) cout << "*" << "\t";
                        else cout << t[i][j] << "\t";
                }
                cout << endl;
            }
            break;
        }
        if(if_revealed[row][col] == 1){
           if(if_revealed[row][col] == 1) cout << "This field is already revealed, choose again." << endl;
           continue;
        }
        else{
            if(t[row][col] == 0 ) check_if_zero(t, if_revealed, r, c, row, col);
            for(i = 1; i<c-1; i++) cout << "\t"<< i;
            cout << endl;
            cout << endl;
            for(i = 1; i < r-1; i ++){
                cout <<  i << "\t";
                for(j = 1; j < c-1; j++){
                    if(i == row && j == col){
                        if_revealed[i][j] = 1;
                        cout << t[i][j] << "\t";
                    }
                    else{
                        if(if_revealed[i][j] == 1){
                            if(t[i][j] >= 9) cout << "RC" << "\t";
                            else cout << t[i][j] << "\t";
                        }
                        else cout <<"R" << "C" << "\t";
                    }
                }
                cout<<endl;
            }
        }
        int check = 0;
        for(int a = 1; a < r-1; a ++){
            for(int b = 1; b < c-1; b++){
                if(if_revealed[a][b] == 1) check++;
            }
        }
        if(check == (r-2)*(c-2)-m){
            cout << "You won!" << endl;
            break;
        }
    }
}

int main(){
    srand( time( NULL ) );
    int choice, row, column, mines;
    cout << "Menu\n1. Play\n2. Finish" << endl;
    cin >> choice;
    cin.clear();
    cin.ignore(1000, '\n' );
    while(choice == 1) {
        cout << "Enter number of rows (2-20): " << endl;
        cin >> row;
        if(std::cin.fail()){
            cout << "It is not a number! Default value has been set. Row = 5" << endl;
            row = 5;
        }
        else{
            if(row < 2 || row > 20){
                cout << "Default value has been set. Row = 5" << endl;
                row = 5;
            }
        }
        cin.clear();
        cin.ignore(1000, '\n' );
        cout << "Enter number of columns (2-20): " << endl;
        cin >> column;
        if(std::cin.fail()){
            cout << "It is not a number! Default value has been set. Column = 5" << endl;
            column = 5;
        }
        else{
            if(column < 2 || column > 20){
                cout << "Default value has been set. Column = 5" << endl;
                column = 5;
            }
        }
        cin.clear();
        cin.ignore(1000, '\n' );
        cout << "Enter number of mines: " << endl;
        cin >> mines;
        if(std::cin.fail()){
            mines = (row-1)*(column-1);
            cout << "It is not a number! Default value has been set. Mines = " << mines << endl;
        }
        else{
            if(mines < 1 || mines > (row-1)*(column-1)){
                mines = (row-1)*(column-1);
                cout << "Default value has been set. Mines = " << mines << endl;
            }
        }
        cin.clear();
        cin.ignore(1000, '\n' );
        vector<vector<int>> tab((row + 2), vector<int>((column + 2), 0));
        board(row, column);
        place_mines(tab, row + 2, column + 2, mines);
        start(tab, row + 2, column + 2, mines);

        cout << "Menu\n1. Play\n2. Finish" << endl;
        cin >> choice;
    }
    cout << "Thank You for playing."<< endl;
    return 0;
}
