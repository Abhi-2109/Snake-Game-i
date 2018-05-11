#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
using namespace std;
bool gameOver;
int height =20;         // for the boundary
int width = 40;         // for the boundary
int headX,headY;       //Cordinates for the head of the snake
int fruitX,fruitY;      //Cordinates for the fruit
int score;
enum eDirection {STOP=0,LEFT,RIGHT,UP,DOWN};        // for the direction of the snake
eDirection dir;
int tailX[100];
int tailY[100];
int LengthTail;

void setup()
{
    gameOver=false;     // to start the game
    dir = STOP;    // To pause the game
    headX = width/2;    // to make the head of the snake at the center
    headY = height/2;
    fruitX = rand()%width;              // for getting the position of the fruit
    fruitY = rand()%height;
    score = 0;                          // initializing the score to zero
}
void draw()                                     // to draw the map
{
    system("cls");                    // to clear the system all the time
    for(int i=0;i<=width; i++)
        cout<<"#";
    cout<<endl;
    for(int i=0;i<height;i++)
    {
        for(int j =0; j<=width;j++)
        {
            if(j==0||j==width)
                cout<<"#";
            else
            {
                if(i==headY && j== headX)
                  cout<<"O";
                else
                {
                    if(i==fruitY && j == fruitX)
                        cout<<"$";
                    else{
                        bool print = false;
                        for(int k =0;k<LengthTail;k++)
                        {
                            if(tailX[k]==j && tailY[k]==i)
                                {
                                    cout<<"o";
                                    print = true;
                                }
                        }
                        if(!print)
                            cout<<" ";
                    }
                }
            }
        }
        cout<<endl;
    }
    for(int i=0;i<=width; i++)
        cout<<"#";
    cout<<endl;
    cout<<"score :"<<score<<endl;
}
void input()                                       // to take the input
{
    if(_kbhit())                        // function to check whether the input  is taken from the keyboard or not
    {
        switch(_getch())
        {
        case 'a' :
            dir= LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir= UP;
            break;
        case 's' :
            dir= DOWN;
            break;
        case 'x':
            gameOver=true;
            break;
        default:
            break;
        }
    }
}
void logic()
{
    int prevX = tailX[0];           // to store the previous value of X
    int prevY = tailY[0];           // to store the previous value of y
    int tempX,tempY;
    tailX[0] = headX;
    tailY[0] = headY;
    for(int i = 1; i<LengthTail;i++)
    {
        tempX = tailX[i];
        tempY = tailY[i];
        tailX[i]= prevX;
        tailY[i]= prevY;
        prevX = tempX;
        prevY = tempY;
    }

    switch(dir)
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default:
        break;

    }
    if(headX>width|| headX<=0|| headY>height || headY<-1)
        gameOver=true;              // end of the game
    if(headX==fruitX && headY==fruitY)
    {
        score+=10;
        fruitX = rand()%width;
        fruitY = rand()%height;
        LengthTail+=1;          // as the snake its the fruit its size will increase.
    }
}
int main()
{
    setup();
    while(!gameOver)
    {
        draw();
        input();
        logic();
        clock_t start_time = clock();               // for delay
        while(clock() < start_time + 50);
    }
    getch();
    return 0;
}
