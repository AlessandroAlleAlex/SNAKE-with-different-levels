#include <iostream>
#include <ncurses.h>
/*
ncurses (new curses) is a programming library providing an application
programming interface (API) that allows the programmer to write
text-based user interfaces in a terminal-independent manner. It is
a toolkit for developing "GUI-like" application software that
runs under a terminal emulator.
*/
#include <cstdlib>
/*
C Standard General Utilities Library. This header defines several
general purpose functions, including dynamic memory management, random
number generation, communication with the environment, integer arithmetics,
searching, sorting and converting.
*/
#include <ctime>
using namespace std;

bool gameOver;

const int width = 30;
const int height = 20;
//the const keyword specifies that the object or variable is not modifiable.

int x, y, score, sum;
int FruitX, FruitY;
int BonusX, BonusY;
int Bonus2X, Bonus2Y;
int Bonus3X, Bonus3Y;
int Bonus4X, Bonus4Y;
int Bonus5X, Bonus5Y;
int N1, N2, N3, N4, N5, N6;

int TailX[100], TailY[100];
// Max = 100 elements

int nTail=0;
// starts with 0 elelmets


enum eDirecton {STOP = 0, LEFT, RIGHT, UP, DOWN};
/*
Enumerations allow you to create you own data type within the
constructs of your application. You can determine the scope and
the significance of the custom type.
*/

eDirecton dir;

void Setup()
{
    initscr();
    /*
    The initscr code determines the terminal type and initializes
    all curses data structures. If errors occur, initscr writes
    an appropriate error message to standard error and exits;
    otherwise, a pointer is returned to stdscr.
    */
    clear();
    //clear the window
    noecho();
    //To suppress the automatic echoing of typed characters,
    cbreak();
    //makes the characters typed by the user immediately available to the program.
    //One-character-a-time.
    curs_set(0);
    /*
    sets the cursor state is set to invisible, normal,
    or very visible for visibility equal to 0, 1, or 2 respectively.
    */

    gameOver = false;
    dir = STOP;
    //set to stop when the game starts

    x = width / 2;
    y = height / 2;
    //centered snake head
    srand(time(NULL));

    FruitX = (rand() % width)+1;
    FruitY = (rand() % height)+1;

    BonusX = (rand() % width)+1;
    BonusY = (rand() % height)+1;

    Bonus2X = (rand() % width)+1;
    Bonus2Y = (rand() % height)+1;

    Bonus3X = (rand() % width)+1;
    Bonus3Y = (rand() % height)+1;

    Bonus4X = (rand() % width)+1;
    Bonus4Y = (rand() % height)+1;

    Bonus5X = (rand() % width)+1;
    Bonus5Y = (rand() % height)+1;

    N1 = rand() % 9+1;
    N2 = rand() % 9+1;
    N3 = rand() % 9+1;
    N4 = rand() % 9+1;
    N5 = rand() % 9+1;
    N6 = rand() % 9+1;

    sum = 0;
    score = 0;
    //initaial score = 0
}

void Draw()
{
    clear(); //system("clear");

    //for (int i = 0; i < width+2; i++)
       // mvprintw(0,i,"+");


    for (int i = 0; i < height+2; i++)
    {
        for (int j = 0; j < width+2; j++)
        {
            if (i == 0 || i == 21)
                mvprintw(i,j,"+"); //vertical check
/*
This prints to the current window, but allows you to specify
the cursor position to print at.
mvprintw( Line,  Column, Format, [Argument ...])
*/

            else if (j == 0 || j== 31)
                mvprintw(i,j,"+"); //horizontal check

            else if (i == y && j == x)
                mvprintw(i,j,"O"); // print centered head

            else
                for (int k = 0; k < nTail; k++)
                {
                    if (TailX[k] == j && TailY[k] == i)
                        mvprintw(i,j,"o"); //print tail

                }
            if (i == FruitY && j == FruitX){
               mvprintw(i,j,"0"); //print fruit
            }

        }
    }

    mvprintw(23,0,"Score %d", score);
    mvprintw(0,34,"Welcome to Level:");
    mvprintw(1,34,"Baby");

    refresh();

}

void Draw_NoWay()
{
    clear(); //system("clear");

    //for (int i = 0; i < width+2; i++)
       // mvprintw(0,i,"+");

    mvprintw(0,0,"+"); //up left
    mvprintw(0,31,"+"); //up right

    mvprintw(21,0,"+"); //down left
    mvprintw(21,31,"+"); //down right

    for (int i = 0; i < height+2; i++)
    {
        for (int j = 0; j < width+2; j++)
        {


            if (i == y && j == x)
                mvprintw(i,j,"O"); // print centered head

            else
                for (int k = 0; k < nTail; k++)
                {
                    if (TailX[k] == j && TailY[k] == i)
                        mvprintw(i,j,"o"); //print tail

                }
            if (i == FruitY && j == FruitX){
               mvprintw(i,j,"0"); //print fruit
            }

        }
    }

    mvprintw(23,0,"Score %d", score);
    mvprintw(25,0,"Welcome to Level:");
    mvprintw(26,0,"No Way!");

    refresh();

}

void Draw_SoSo()
{
    clear(); //system("clear");
    //for (int i = 0; i < width+2; i++)
        //mvprintw(0,i,"+");


    for (int i = 0; i < height+2; i++)
    {
        for (int j = 0; j < width+2; j++)
        {
            if (i == 0 || i == 21)
                mvprintw(i,j,"+");

            else if (j == 0 || j== 31)
                mvprintw(i,j,"+");

            else if (i == y && j == x)
                mvprintw(i,j,"O");

            else
                for (int k = 0; k < nTail; k++)
                {
                    if (TailX[k] == j && TailY[k] == i)
                        mvprintw(i,j,"o");

                }
            if (i == FruitY && j == FruitX){
               mvprintw(i,j,"0");
            }
            if (i == BonusY && j == BonusX){
               mvprintw(i,j,"Bonus"); //print bonus fruit

            }

        }
    }

    mvprintw(23,0,"Score %d", score);
    mvprintw(0,34,"Welcome to Level:");
    mvprintw(1,34,"So So");

    refresh();

}

void Draw_Annoying()
{

    clear(); //system("clear");
    //for (int i = 0; i < width+2; i++)
        //mvprintw(0,i,"+");



    for (int i = 0; i < height+2; i++)
    {
        for (int j = 0; j < width+2; j++)
        {

            //if (i == 0 || i == 21)
                //mvprintw(i,j,"+");

            //else if (j == 0 || j== 31)
                //mvprintw(i,j,"+");

            if (i == y && j == x)
                mvprintw(i,j,"O");

            else
                for (int k = 0; k < nTail; k++)
                {

                    if (TailX[k] == j && TailY[k] == i)
                        mvprintw(i,j,"o");

                }


            if (i == FruitY && j == FruitX){
                mvprintw(i,j,"%d", N1);

            }

            if (i == BonusY && j == BonusX){
                mvprintw(i,j,"%d", N2);

            }
            if (i == Bonus2Y && j == Bonus2X){
                mvprintw(i,j,"%d", N3);

            }
            if (i == Bonus3Y && j == Bonus3X){
                mvprintw(i,j,"%d", N4);
            }
            if (i == Bonus4Y && j == Bonus4X){
                mvprintw(i,j,"%d", N5);
            }
            if (i == Bonus5Y && j == Bonus5X){
                mvprintw(i,j,"%d", N6);
            }

        }
    }

    mvprintw(23,0,"Score: %d.", score);
    mvprintw(24,0,"Sum: %d.", sum);
    mvprintw(25,0,"Welcome to Level:");
    mvprintw(26,0,"Annoying");
    refresh();

}

void Input_Baby()
{

    keypad(stdscr, TRUE); //gets key values
    halfdelay(2); //click only once (2 seconds)

    int c = getch();
    switch(c){
    case KEY_LEFT:
        dir = LEFT;
        break;
    case KEY_RIGHT:
        dir = RIGHT;
        break;
    case KEY_UP:
        dir = UP;
        break;
    case KEY_DOWN:
        dir = DOWN;
        break;
    case 113: //q: ASCII position (yu can quit the game by pressing keyboard q)
        gameOver = true;
        break;
    }

}

void Input_SoSo()
{

    keypad(stdscr, TRUE); //gets key values
    halfdelay(1); //click only once (1 second)

    int c = getch();
    switch(c){
    case KEY_LEFT:
        dir = LEFT;
        break;
    case KEY_RIGHT:
        dir = RIGHT;
        break;
    case KEY_UP:
        dir = UP;
        break;
    case KEY_DOWN:
        dir = DOWN;
        break;
    case 113: //q
        gameOver = true;
        break;
    }

}

void Input_NoWay()
{

    keypad(stdscr, TRUE); //gets key values
    halfdelay(1); //click only once (1 second)

    int c = getch();
    switch(c){
    case KEY_LEFT:
        dir = RIGHT;
        break;
    case KEY_RIGHT:
        dir = LEFT;
        break;
    case KEY_UP:
        dir = DOWN;
        break;
    case KEY_DOWN:
        dir = UP;
        break;
    case 113: //q
        gameOver = true;
        break;
    }

}

void Input_Annoying()
{

    keypad(stdscr, TRUE); //gets key values

    int c = getch();
    switch(c){
    case KEY_LEFT:
        dir = LEFT;
        break;
    case KEY_RIGHT:
        dir = RIGHT;
        break;
    case KEY_UP:
        dir = UP;
        break;
    case KEY_DOWN:
        dir = DOWN;
        break;
    case 113: //q
        gameOver = true;
        break;
    }

}


void Logic(){

    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;
    TailX[0] = x;
    TailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    srand(time(NULL));

    if (x > width || x < 1 || y < 1|| y > height){ //die if you touch walls your tails
        gameOver = true;
    }

    if (x == FruitX && y == FruitY){
        score++;
        FruitX = (rand() % width)+1;
        FruitY = (rand() % height)+1;
        nTail++;
    }
    else if (x == BonusX && y == BonusY){
        score++;
        BonusX = (rand() % width)+1;
        BonusY = (rand() % height)+1;
        nTail++;
    }

    for (int i = 0; i < nTail; i++){
        if (TailX[i] == x && TailY[i] == y)
            gameOver = true;
    }
}

void Logic_Annoying(){

    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;
    TailX[0] = x;
    TailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x > width || x < 1 || y < 1|| y > height){
        gameOver = true;
    }

    if (x == FruitX && y == FruitY){
        if (N1<=N2 && N1<=N3 && N1<=N4 && N1<=N5 && N1<=N6){
            score++;
            sum = sum + N1;
            FruitX = (rand() % width)+1;
            FruitY = (rand() % height)+1;
            nTail++;
            N1 = rand() % 9+1;
        }
        else{
            gameOver = true;
        }
    }
    else if (x == BonusX && y == BonusY){
        if (N2<=N1 && N2<=N3 && N2<=N4 && N2<=N5 && N2<=N6){
            score++;
            sum = sum + N2;
            BonusX = (rand() % width)+1;
            BonusY = (rand() % height)+1;
            nTail++;
            N2 = rand() % 9+1;
        }
        else{
            gameOver = true;
        }
    }

    else if (x == Bonus2X && y == Bonus2Y){
        if (N3<=N1 && N3<=N2 && N3<=N4 && N3<=N5 && N3<=N6){
    	    score++;
            sum = sum + N3;
            Bonus2X = (rand() % width)+1;
            Bonus2Y = (rand() % height)+1;
            nTail++;
            N3 = rand() % 9+1;
    	}
        else{
            gameOver = true;
        }
    }
    else if (x == Bonus3X && y == Bonus3Y){
        if (N4<=N1 && N4<=N2 && N4<=N3 && N4<=N5 && N4<=N6){
    	    score++;
            sum = sum + N4;
            Bonus3X = (rand() % width)+1;
            Bonus3Y = (rand() % height)+1;
            nTail++;
            N4 = rand() % 9+1;
        }
        else{
            gameOver = true;
        }

    }
    else if (x == Bonus4X && y == Bonus4Y){
        if (N5<=N1 && N5<=N2 && N5<=N3 && N5<=N4 && N5<=N6){
    	    score++;
            sum = sum + N5;
            Bonus4X = (rand() % width)+1;
            Bonus4Y = (rand() % height)+1;
            nTail++;
            N5 = rand() % 9+1;
        }
        else{
            gameOver = true;
        }
    }
    else if (x == Bonus5X && y == Bonus5Y){
        if (N6<=N1 && N6<=N2 && N6<=N3 && N6<=N4 && N6<=N5){
    	    score++;
            sum = sum + N6;
            Bonus5X = (rand() % width)+1;
            Bonus5Y = (rand() % height)+1;
            nTail++;
            N6 = rand() % 9+1;
        }
        else{
            gameOver = true;
        }
    }

    for (int i = 0; i < nTail; i++){
        if (TailX[i] == x && TailY[i] == y)
            gameOver = true;
    }
}

int main(){

	int level;

	cout << endl;
	cout << "              SNAKE GAME             " << endl;
	cout << "#---------------MENU----------------#" << endl;
	cout << "# Enter 1. Baby Level               #" << endl;
	cout << "# Enter 2. So So Level              #" << endl;
	cout << "# Enter 3. Annoying Level           #" << endl;
	cout << "# Enter 4. No Way Level             #" << endl;
	cout << "# Enter 5: Exit                     #" << endl;
	cout << "#-----------------------------------#" << endl;
	cin >> level;

	switch(level){

		case 1:

			Setup();
    		while (!gameOver)
    		{
        		Draw();
        		Input_Baby();
        		Logic();
    		}
    		getch();
    		endwin();
            break;

		case 2:

			Setup();
    		while (!gameOver)
    		{
        		Draw_SoSo();
        		Input_SoSo();
        		Logic();
    		}
    		getch();
    		endwin();
            break;

		case 3:

			Setup();
    		while (!gameOver)
    		{
        		Draw_Annoying();
        		Input_Annoying();
        		Logic_Annoying();
    		}
    		getch();
    		endwin();
            break;

		case 4:

            Setup();
            while (!gameOver)
            {
                Draw_NoWay();
                Input_NoWay();
                Logic();
            }
            getch();
            endwin();

		case 5:
			cout << "End Game." << endl;
			break;
		default:
			cout << "Invalid Enter!";
		}

/*
    Setup();
    while (!gameOver)
    {

        Draw();
        Input();
        Logic();
    }
    getch();
    endwin();*/

    return 0;
}
