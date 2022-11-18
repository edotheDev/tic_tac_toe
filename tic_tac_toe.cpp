#include <iostream>
#include <random>
using namespace std;

void iCheck(char (&Arr)[][3],char ch){
    int x, y, a;
    cout << "  Enter Player " << "'" <<ch << "': ";
    cin >> a;
    if (cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "  Please enter only numbers between 1 to 9.";
        iCheck(Arr,ch);
    }else if(a<1 || a>9){
        cout << " Input is not valid! Please re-enter." << endl;
        iCheck(Arr,ch);
    }
    else{
        if (a % 3 == 0) {
            x = (a / 3) - 1;
            y = 2;
        } else {
            x = a / 3;
            y = (a % 3) - 1;
        }
        if (Arr[x][y] == 'X' || Arr[x][y] == 'O'){
            cout << " Position is already taken. Please re-enter." << endl;
            iCheck(Arr,ch);
        } else{
            Arr[x][y] = ch;
        }
    }
}
void sMode(char (&Arr)[][3],char ch){
    int x, y, a;
    cout << "  Computer's turn:";
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(1.0, 10.0);
    a = (int)dist(mt);
    if (a>=1 && a<=9){
        if (a % 3 == 0) {
            x = (a / 3) - 1;
            y = 2;
        } else {
            x = a / 3;
            y = (a % 3) - 1;
        }
        if (Arr[x][y] == 'X' || Arr[x][y] == 'O'){
            sMode(Arr,ch);
        } else{
            Arr[x][y] = ch;
        }
    }
}
void medium(char (&Arr)[][3],int r, int c) {
    int j = c-1;
    for (int i = 0; i < r; ++i) {
        char testArr1[3];
        char testArr2[3];
        char testArr3[3];
        char testArr4[3];
        int count1[3] = {0,0,1};
        int count2[3] = {1,2,2};
        testArr3[i] = Arr[i][i];
        testArr4[i] = Arr[i][j];
        for (int k = 0; k < c; ++k) {
            testArr1[k] = Arr[i][k];
            testArr2[k] = Arr[k][i];
        }
        int m = -1;
        for (int l = 2; l > -1; --l) {
            ++m;
            if (testArr1[count1[m]] == 'X' && testArr1[count2[m]] == 'X') {
                cout << "  1Computer's turn:";
                Arr[i][l] = 'O';
                break;
            } else if (testArr2[count1[m]] == 'X' && testArr2[count2[m]] == 'X') {
                cout << "  2Computer's turn:";
                Arr[l][i] = 'O';
                break;
            } else if (testArr3[count1[m]] == 'X' && testArr3[count2[m]] == 'X') {
                cout << "  3Computer's turn:";
                Arr[l][l] = 'O';
                break;
            } else if (testArr4[count1[m]] == 'X' && testArr4[count2[m]] == 'X') {
                cout << "  4Computer's turn:";
                Arr[l][m] = 'O';
                break;
            } else if (i == 2 && l == 0){
                sMode(reinterpret_cast<char (&)[][3]>(Arr), 'O');
                break;
            }else{
                continue;
            }
        }
        --j;
    }
}
char rNcCheck(char Arr[][3],int r, int c) {
    int j = c-1;
    for (int i = 0; i < r; ++i) {
        char testArr1[3];
        char testArr2[3];
        char testArr3[3];
        char testArr4[3];
        testArr3[i] = Arr[i][i];
        testArr4[i] = Arr[i][j];
        --j;
        for (int k = 0; k < c; ++k) {
            testArr1[k] = Arr[i][k];
            testArr2[k] = Arr[k][i];
        }
        if (testArr1[0] == 'X' && testArr1[1] == 'X' && testArr1[2] == 'X' || testArr2[0] == 'X' && testArr2[1] == 'X' && testArr2[2] == 'X' || testArr3[0] == 'X' && testArr3[1] == 'X' && testArr3[2] == 'X' || testArr4[0] == 'X' && testArr4[1] == 'X' && testArr4[2] == 'X') {
            return 'X';
        } else if (testArr1[0] == 'O' && testArr1[1] == 'O' && testArr1[2] == 'O' || testArr2[0] == 'O' && testArr2[1] == 'O' && testArr2[2] == 'O' || testArr3[0] == 'O' && testArr3[1] == 'O' && testArr3[2] == 'O' || testArr4[0] == 'O' && testArr4[1] == 'O' && testArr4[2] == 'O') {
            return 'O';
        } else {
            continue;
        }
    }
    return 0;
}
void show(char arr[][3], int l) {
    for (int i = 0; i < l; ++i) {
        cout << "  -------------------" << endl;
        for (int j = 0; j < l; ++j) {
            cout << "  |  " << arr[i][j];
        }
        cout << "  |" << endl;
    }
}

int main() {
    char sORm;
    cout << "  Choose single player or multi player(m/s):";
    cin >> sORm;
    char board[3][3] = {{'1', '2', '3'},
                        {'4', '5', '6'},
                        {'7', '8', '9'}};
    char res;
    char c;
    show(board, 3);
    cout << "  -------------------" << endl;
    if (sORm == 'm' || sORm == 'M'){
        int i = 0;
        while (i < 9) {
            if (i % 2 == 0) {
                iCheck(reinterpret_cast<char (&)[][3]>(board), 'X');
            } else {
                iCheck(reinterpret_cast<char (&)[][3]>(board), 'O');
            }
            cout << endl;
            show(board, 3);
            cout << "  -------------------" << endl;
            i++;
            res = rNcCheck(board, 3, 3);
            if (res == 'X') {
                cout << "  Player 'X' Win" << endl;
                break;
            } else if (res == 'O') {
                cout << "  Player 'O' Win" << endl;
                break;
            } else {
                continue;
            }
        }
        cout << "  Game Over" << endl;
    } else if(sORm == 's' || sORm == 'S'){
        char lev;
        cout << "  Choose level easy, medium or hard(e/m/h):";
        cin >> lev;
        int i = 0;
        while (i < 9) {
            if (i % 2 == 0) {
                iCheck(reinterpret_cast<char (&)[][3]>(board), 'X');
            } else {
                if (lev == 'e' || lev == 'E'){
                    sMode(reinterpret_cast<char (&)[][3]>(board), 'O');
                } else{
                    medium(reinterpret_cast<char (&)[][3]>(board), 3, 3);
                }
            }
            cout << endl;
            show(board, 3);
            cout << "  -------------------" << endl;
            i++;
            res = rNcCheck(board, 3, 3);
            if (res == 'X') {
                cout << "  You Win" << endl;
                break;
            } else if (res == 'O') {
                cout << "  Computer Win" << endl;
                break;
            } else {
                continue;
            }
        }
        cout << "  Game Over" << endl;
    }
    cout << "  Do you want to play again(y/n):";
    cin >> c;
    if (c == 'y' || c == 'Y'){
        main();
    }
}