#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
COORD coord={0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
using namespace std;
bool gameOver;
const int height =20;         // for the boundary
const int width = 40;         // for the boundary
int headX,headY;       //Cordinates for the head of the snake
int fruitX,fruitY;      //Cordinates for the fruit
int score;
enum eDirection {STOP=0,LEFT,RIGHT,UP,DOWN};        // for the direction of the snake
eDirection dir;
int tailX[100];
int tailY[100];
int LengthTail=0;

void setup()
{
    gameOver=false;     // to start the game
    dir = STOP;    // To pause the game
    headX = width/2;    // to make the head of the snake at the center
    headY = height/2;
    fruitX = (rand()%(width-2))+1;              // for getting the position of the fruit
    fruitY = (rand()%(height-2)) +1;
    score = 0;                          // initializing the score to zero
}
void grid()
{
    for(int i=0;i<width;i++)
    {gotoxy(i,0); cout<<'#';gotoxy(i,height-1); cout<<'#';}
    for(int i=0;i<height;i++)
    {gotoxy(0,i); cout<<'#'; gotoxy(width-1,i); cout<<'#';}
}
int  check(int x,int y)
{
    if(x==headX&&y==headY)
        return 0;
    if(x==fruitX&&y==fruitY)
        return 0;
    for(int k =0;k<LengthTail;k++)
    {
        if(tailX[k]==x&&tailY[k]==y)
            return 0;
    }
    return 1;
}
void draw()                                     // to draw the map
{
    //system("cls");                    // to clear the system all the time
   /* for(int i=0;i<width;i++)
    {gotoxy(i,0); cout<<'#';gotoxy(i,height-1); cout<<'#';}
    for(int i=0;i<height;i++)
    {gotoxy(0,i); cout<<'#'; gotoxy(width-1,i); cout<<'#';}
    */
    gotoxy(headX,headY);
        cout<<'O';
    gotoxy(fruitX,fruitY);
        cout<<'$';
    for(int k=0;k<LengthTail;k++)
    {
        gotoxy(tailX[k],tailY[k]);
        cout<<'o';
    }
    for(int i=1;i<width-1;i++)
    {
        for(int j =1; j<height-1;j++)
        {
            if(check(i,j))
            {
                gotoxy(i,j);
                cout<<' ';
            }
        }
    }
        gotoxy(0,height);
          cout<<"Score  :"<<score<<endl;

    /*
    for(int i=0;i<height;i++)
    {
        for(int j =0; j<=width;j++)
        {
            if(j==0||j==width)
                cout<<"#";
            else
            {
                if(i==headY && j== headX)
                  { gotoxy(i,j);cout<<"O";}
                else
                {
                    if(i==fruitY && j == fruitX)
                      {
                          gotoxy(i,j);cout<<"$";
                      }
                    else{
                        bool print = false;
                        for(int k =0;k<LengthTail;k++)
                        {
                            if(tailX[k]==j && tailY[k]==i)
                                {
                                    gotoxy(i,j);
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
    */
   // cout<<"score :"<<score<<endl;
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
        if(LengthTail>0)
        {
        if((headX==tailX[0]+1)&&(headY==tailY[0]))
            break;
        else
            {headX--;break;}
        }
        else
            {headX--;break;}

    case RIGHT:
         if(LengthTail>0)
        {
            if((headX==tailX[0]-1)&&(headY==tailY[0]))
                break;
            else
                {headX++; break;}
        }
        else
            {headX++; break;}

    case UP:
         if(LengthTail>0)
        {
            if((headX==tailX[0])&&(headY==tailY[0]-1))
                break;
            else
            {headY--; break;}
        }
        else
            {headY--; break;}

    case DOWN:
         if(LengthTail>0)
        {
            if((headX==tailX[0])&&(headY==tailY[0]+1))
                break;
        else
            {headY++;break;}
        }
        else
        {headY++;break;}
    default:
        break;

    }
    if(headX==width-1|| headX==0|| headY==height-1 || headY==0)
        gameOver=true;              // end of the game
    for(int i=0;i<LengthTail;i++)
    {
        if(tailX[i]==headX&&tailY[i]==headY)
        {
            gameOver=true;
            break;
        }
    }
    if(headX==fruitX && headY==fruitY)
    {
        score+=10;
        fruitX = rand()%(width-2) +1;
        fruitY = rand()%(height-2) +1;
        LengthTail+=1;          // as the snake its the fruit its size will increase.
    }
}
int main()
{
    setup();
    grid();
    while(!gameOver)
    {
        draw();
        input();
        logic();
        clock_t start_time = clock();               // for delay
        while(clock() < start_time + 200);
    }
    getch();
    return 0;
}

