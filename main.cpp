#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

// Kod zoptymalizowany i poprawiony (ostatecznie)
// Filip Misztal 310276

using namespace std;

struct position     //coordinates of certain objects
{
    int x;
    int y;
};

void Instruction();
void Board(position board1, position player1, position treasure1, position rock1);
void Movement(position *player1, char move1);
int SizeSet(int minimum, int maximum);

int main()
{
    position player, treasure, rock, board;
    int deaths=0, points=0, captured=1;
    char move;

    cout << "Set the size of the board (minimum size: 2x2, maximum size: 40x100):" << endl;
    cout << "Height: ";
    board.y=SizeSet(2, 40);
    cout << "Width: ";
    board.x=SizeSet(2, 100);

    system("cls");

    player.x=board.x/2+1;   //initial player position
    player.y=board.y/2+1;

    rock.y=board.y+1;

    while(deaths==0)
    {
        srand(time(NULL));

        if(captured==1)
        {                  //treasure setting
            do
            {
                treasure.x=1+rand()%(board.x);
                treasure.y=1+rand()%(board.y);
            }
            while(treasure.x==player.x && treasure.y==player.y);
            captured--;
        }

        if(rock.y==board.y+1)       //rock replacement
        {
            rock.x=1+rand()%(board.x);
            rock.y=0;
        }

        Board(board, player, treasure, rock);

        Instruction();

        cout << "Your current score: " << points << endl << endl;
        cin >> move;

        Movement(&player, move);

        if(rock.y!=board.y+1)       //rock fall
            rock.y+=1;

        if(player.x==0 || player.x==board.x+1 || player.y==0 || player.y==board.y+1 || (player.x==rock.x && player.y==rock.y))
        {
            deaths++;       //failure conditions
            break;
        }

        if(player.x==treasure.x && player.y==treasure.y)
        {
            captured++;       //conditions for scoring a point
            points++;
        }

        system("cls");
    }

    cout << endl << "\a" << "Oops, you've lost!" << endl;
    cout << "Your final score: " << points << endl;
    return 0;
}


void Instruction()
{
    cout << "Let's play Indiana Jones!" << endl;
    cout << "Collect artifacts \"T\" and watch out for falling rocks \"R\"!" << endl << endl;
    cout << "Controls:" << endl;
    cout << "w+ENTER - move upwards" << endl;
    cout << "s+ENTER - move downwards" << endl;
    cout << "a+ENTER - move left" << endl;
    cout << "d+ENTER - move right" << endl << endl;
}

void Board(position board1, position player1, position treasure1, position rock1)
{
    int tab[board1.y][board1.x];

    for(int i=0; i<board1.y; i++)       //writing a board
    {
        for(int k=0; k<board1.x; k++)
        {
            tab[i][k]=0;

            if(k==player1.x-1 && i==player1.y-1 )
                tab[i][k]=1;                            //1-player
            if(k==treasure1.x-1 && i==treasure1.y-1 )
                tab[i][k]=2;                            //2-treasure
            if(k==rock1.x-1 && i==rock1.y-1 )
                tab[i][k]=3;                            //3-rock
        }
    }

    for(int i=0; i<=board1.y+1; i++)        //reading a board
    {
        if(i==0)
        {
            for(int k=0; k<board1.x+2; k++)
                cout << "_";
            cout << endl;
        }

        if(i>0 && i<board1.y+1)
        {
            cout << "|";
            for(int k=0; k<board1.x; k++)
            {
                switch(tab[i-1][k])
                {
                    case 1:
                        cout << "P";
                    break;

                    case 2:
                        cout << "T";
                    break;

                    case 3:
                        cout << "R";
                    break;

                    default:
                        cout << " ";
                    break;
                }
            }
            cout << "|" << endl;
        }

        if(i==board1.y+1)
        {
            for(int k=0; k<board1.x+2; k++)
                cout << "I";
            cout << endl;
        }
    }
}

void Movement(position *player1, char move1)
{
    switch(move1)
        {
        case 'w':           //move up
            player1->y-=1;
        break;

        case 's':           //move down
            player1->y+=1;;
        break;

        case 'a':           //move left
            player1->x-=1;
        break;

        case 'd':           //move right
            player1->x+=1;
        break;
        }
}

int SizeSet(int minimum, int maximum)
{
    double n;
    int a;

    while(1)
    {
        if(cin.fail())      //clearing the stream
        {
            cin.clear();
            cin.ignore(20000,'\n');
        }

        cin >> n;
        a=round(n);

        if(cin.fail())
        {
            cout << "Invalid character entered!" << endl << "Please re-enter the size: ";
            continue;
        }

        if((a<minimum || a>maximum) && minimum!=maximum)
        {
            cout << "This size is out of range!" << endl << "Please re-enter the size: ";
            continue;
        }
        break;
    }
    return a;
}

