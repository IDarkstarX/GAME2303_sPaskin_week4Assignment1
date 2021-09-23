
#include <iostream>

using namespace std;

int globalRow;
int globalCol;

class TicTacToe
{
public:
    // TTT board, empty by default
    char board[3][3] =
    {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    // used for keeping track what's in each space, and what value each player has
    enum Entry
    {
        EMPTY = ' ',
        PLAYER_ONE = 'x',
        PLAYER_TWO = 'o'
    };

    // has the board been completely filled?
    bool isFull()
    {
        bool result = true;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == Entry::EMPTY)
                    result = false;
            }
        }

        return result;
    }

    // has someone won?
    bool isVictory(Entry e)
    {

        // first col
        if (board[0][0] == (char)e && board[0][1] == (char)e && board[0][2] == (char)e)
        {
            return true;
        }

        // second col
        else if (board[1][0] == (char)e && board[1][1] == (char)e && board[1][2] == (char)e)
        {
            return true;
        }

        // third col
        else if (board[2][0] == (char)e && board[2][1] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // first row
        else if (board[0][0] == (char)e && board[1][0] == (char)e && board[2][0] == (char)e)
        {
            return true;
        }

        // second row
        else if (board[0][1] == (char)e && board[1][1] == (char)e && board[2][1] == (char)e)
        {
            return true;
        }

        // third row
        else if (board[0][2] == (char)e && board[1][2] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // diagonal 1
        else if (board[0][0] == (char)e && board[1][1] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // diagonal 2
        else if (board[0][2] == (char)e && board[1][1] == (char)e && board[2][0] == (char)e)
        {
            return true;
        }

        return false;
    }

    // return size of the board; mostly just in case I wanted to make the board expandable
    int getSize()
    {
        return 3;
    }


    void dump()
    {
        cout << "----------------------------------------" << endl << endl;
        for (int i = 0; i < getSize(); i++)
        {
            for (int j = 0; j < getSize(); j++)
            {
                cout << " | " << board[i][j] << " | ";
            }

            cout << endl;
        }
        cout << "----------------------------------------" << endl << endl;
    }

};

static bool getHumanMove(int maxValue, TicTacToe::Entry human, TicTacToe& t)
{
    // check if player is able to move
    if (t.isVictory(t.PLAYER_ONE) || t.isVictory(t.PLAYER_TWO) || t.isFull())
        return true;

    int rowChoice = 0;
    int colChoice = 0;

    do {

        do {

            cout << "Enter column number (x) : 0 ... 2 : ";
            cin >> colChoice;
            cout << endl;

        } while (colChoice > maxValue || colChoice < 0);

        do {

            cout << "Enter row number (y) : 0 ... 2 : ";
            cin >> rowChoice;
            cout << endl;

        } while (rowChoice > maxValue || rowChoice < 0);


        if (t.board[rowChoice][colChoice] == t.EMPTY)
        {
            t.board[rowChoice][colChoice] = (char)human;

            return false;
        }

        else
        {
            cout << "Not a valid option! Please try again..." << endl;
        }


    } while (t.board[rowChoice][colChoice] != t.EMPTY);

    // move complete
    return false;
}

static int canWin(TicTacToe::Entry e, TicTacToe& t) {
    //cout << "\n\nCPU: Checking if "<< e << " can win...\n" << endl;
    int count = 0;
    int style = -1;

    //////////////////
    // HORIZONTAL ////
    //////////////////

    //cout << "\nHORIZONTAL\n";

    for (int i = 0; i < t.getSize(); i++) {
        for (int j = 0; j < t.getSize(); j++) {

            //cout << "Checking " << "[" << i << "]" << "[" << j << "]" << ": " << t.board[i][j] << endl;

            //cout << "i : " << i << endl;
            //cout << "j : " << j << endl;

            if (t.board[i][j] == (char)e) {
                count++;
                //cout << "Found!: " << t.board[i][j] << endl;
            }

            if (count == 2 && t.board[i][0] == ' ') { // is the empty spot before the other two?
                style = 0;
                //cout << "Style: " << style << endl;
                break;
            }

            if (count == 2 && t.board[i][1] == t.EMPTY) { // is the empty spot in the middle?
                style = 1;
                //cout << "Style: "<< style << endl;
                break;
            }
        }
        if (count == 2 && style == 0 ) { // no yes yes

            //cout << "Found!: no yes yes" << endl;

            globalRow = i;
            globalCol = 0;

            //cout << "globalRow : "<< globalRow << endl;
            //cout << "globalCol : "<< globalCol << endl;

            return true;

        }
        else if (count == 2 && style == 1) { // yes no yes

            //cout << "Found!: yes no yes" << endl;

            globalRow = i;
            globalCol = 1;

            //cout << "globalRow : "<< globalRow << endl;
            //cout << "globalCol : "<< globalCol << endl;

            return true;

        }
        else if (count == 2 && t.board[i][2] == t.EMPTY) { // yes yes no

            //cout << "Found!: yes yes no" << endl;

            globalRow = i;
            globalCol = 2;

            //cout << "globalRow : "<< globalRow << endl;
            //cout << "globalCol : "<< globalCol << endl;

            return true;

        }
        else {
            count = 0;
            style = 3;
        }
    }

    //////////////////
    // VERTICAL //////
    //////////////////

    //cout << "\nVERTICAL\n";
    
    for (int i = 0; i < t.getSize(); i++) {
        for (int j = 0; j < t.getSize(); j++) {

            //cout << "Checking " << "[" << j << "]" << "[" << i << "]" << ": " << t.board[j][i] << endl;

            //cout << "j : " << j << endl;
            //cout << "i : " << i << endl;

            if (t.board[j][i] == (char)e) {
                count++;
                //cout << "Found!: " << t.board[j][i] << endl;
            }

            if (count == 2 && t.board[0][i] == ' ') { // is the empty spot before the other two?
                style = 0;
                //cout << "Style: " << style << endl;
                break;
            }

            if (count == 2 && t.board[1][i] == ' ') { // is the empty spot in the middle?
                style = 1;
                //cout << "Style: "<< style << endl;
                break;
            }
        }

        if (count == 2 && style == 0) { // no yes yes

            //cout << "Found!: no yes yes" << endl;

            globalRow = 0;
            globalCol = i;

            //cout << "globalRow : "<< globalRow << endl;
            //cout << "globalCol : "<< globalCol << endl;

            return true;

        }
        else if (count == 2 && style == 1) { // yes no yes

            //cout << "Found!: yes no yes" << endl;

            globalRow = 1;
            globalCol = i;

            //cout << "globalRow : "<< globalRow << endl;
            //cout << "globalCol : "<< globalCol << endl;

            return true;

        }
        else if (count == 2 && t.board[2][i] == t.EMPTY) { // yes yes no

            //cout << "Found!: yes yes no" << endl;

            globalRow = 2;
            globalCol = i;

            //cout << "globalRow : "<< globalRow << endl;
            //cout << "globalCol : "<< globalCol << endl;

            return true;

        }
        else {
            count = 0;
            style = 3;
        }
    }

    //////////////////
    // DIAGONAL //////
    //////////////////

    //cout << "\nDIAGONAL\n";

    for (int i = 0; i < t.getSize(); i++) {

        //cout << "Checking " << "[" << i << "]" << "[" << i << "]" << ": " << t.board[i][i] << endl;

        //cout << "i: " << i << endl;

        if (t.board[i][i] == (char)e) {
            count++;
            style = 1;
        }
        else if (t.board[2][0] == (char)e && t.board[0][2] == ' ') {
            count++;
            style = 2;
        }
        else if (t.board[0][2] == (char)e && t.board[2][0] == ' ') {
            count++;
            style = 2;
        }

        if (count == 2 && t.board[0][0] == ' ' && t.board[1][1] == (char)e && style == 1) {
            globalRow = 0;
            globalCol = 0;
            return true;
        } else if (count == 2 && t.board[2][2] == ' ' && t.board[1][1] == (char)e && style == 1) {
            globalRow = 2;
            globalCol = 2;
            return true;
        } else if (count == 2 && t.board[0][2] == ' ' && t.board[1][1] == (char)e && style == 2) {
            globalRow = 0;
            globalCol = 2;
            return true;
        } else if (count == 2 && t.board[2][0] == ' ' && t.board[1][1] == (char)e && style == 2) {
            globalRow = 2;
            globalCol = 0;
            return true;
        }
    }

    return false; // No possible wins!
}

static bool getComputerMove(TicTacToe::Entry computer, TicTacToe& t)
{
    // check if computer is able to move
    if (t.isVictory(t.PLAYER_ONE) || t.isVictory(t.PLAYER_TWO) || t.isFull())
        return true;

    // handle computer's move

    int rowChoice = 0;
    int colChoice = 0;

    ///////////////////////////////////
    // STEP 1 - CAN I WIN? ////////////
    ///////////////////////////////////

    
    if (canWin(computer, t)) {

        //cout << "CPU: I can win! :D" << endl;
        rowChoice = globalRow;
        colChoice = globalCol;

        //cout << "rowChoice: " << rowChoice << endl;
        //cout << "colChoice: " << colChoice << endl;
    }

    ///////////////////////////////////
    // STEP 2 - CAN YOU WIN? //////////
    ///////////////////////////////////

    else if (canWin(t.PLAYER_ONE, t)) {

        //cout << "CPU: You can win! D:" << endl;
        rowChoice = globalRow;
        colChoice = globalCol;

        //cout << "rowChoice: " << rowChoice << endl;
        //cout << "colChoice: " << colChoice << endl;
    }

    ///////////////////////////////////
    // STEP 3 - IS CENTER EMPTY? //////
    ///////////////////////////////////

    else if (t.board[1][1] == t.EMPTY) {
        rowChoice = 1;
        colChoice = 1;
    }

    ///////////////////////////////////
    // STEP 4 - ARE CORNERS EMPTY? ////
    ///////////////////////////////////

    else if (t.board[0][0] == t.EMPTY) {
        rowChoice = 0;
        colChoice = 0;
    }
    else if (t.board[2][0] == t.EMPTY) {
        rowChoice = 2;
        colChoice = 0;
    }
    else if (t.board[0][2] == t.EMPTY) {
        rowChoice = 0;
        colChoice = 2;
    }
    else if (t.board[2][2] == t.EMPTY) {
        rowChoice = 2;
        colChoice = 2;
    }

    ///////////////////////////////////
    // STEP 5 - ANYWHERE ELSE /////////
    ///////////////////////////////////

    else {
        // choose at random until we find a space that's empty

        //cout << "Picking a random spot..." << endl;

        do {
            do {

            rowChoice = rand() % ((t.getSize() - 0) + 1) + 0;

        } while (rowChoice > t.getSize() || rowChoice < 0);

        do {

            colChoice = rand() % ((t.getSize() - 0) + 1) + 0;

        } while (colChoice > t.getSize() || colChoice < 0);
        if (t.board[rowChoice][colChoice] == t.EMPTY) {
            
            t.board[rowChoice][colChoice] = (char)computer;
            
            return false;
        }
        else
        {
                //cout << "Not a valid option! Please try again..." << endl;
        }
    
    } while (t.board[rowChoice][colChoice] != t.EMPTY);
    }

    t.board[rowChoice][colChoice] = (char)computer;

    // move complete
    return false;
}

// ----------------------------
// main
// ----------------------------

int main()
{
    TicTacToe t;
    TicTacToe::Entry human = TicTacToe::PLAYER_ONE;
    TicTacToe::Entry computer = TicTacToe::PLAYER_TWO;

    int maxValue = t.getSize();

    cout << "----------------------------------------" << endl;

    cout << "You are '" << (char)human << "', " <<
        "the computer is: '" << (char)computer << "'" << endl;

    cout << "----------------------------------------" << endl << endl;

    // run the game until one player isn't able to go again
    do
    {
        // show board
        t.dump();
    } while (!getHumanMove(maxValue, human, t) && !getComputerMove(computer, t));


    t.dump();

    cout << endl;

    if (t.isVictory(human))
        cout << "Human Victory" << endl;

    else if (t.isVictory(computer))
        cout << "Computer Victory" << endl;

    else if (t.isFull())
        cout << "Tie" << endl;

    return(0);
}





