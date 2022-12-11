//219957564
//Musana S
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "ESD.h"
#include <time.h>
#define X 35
#define Y 23

int maze[Y][X];
int i, y, x,s,gx,gy;
int score;
int xCon, yCon, old_x, old_y;
int lives=4;
int j;

struct ghostPos {
int x;
int y;
int old_x;
int old_y;
int dir;
};

typedef struct ghostPos GHOST;

void maize(int x, int y);
void readData();
GHOST ghost_dir(GHOST g);
GHOST ghostMove(int i, GHOST g1);
GHOST bonusMove(GHOST , int, int);
void clrscr1();

GHOST g1, g2, g3;

int main()
{
    int charge=0;
    char key;
    readData();
    gotoxy(23, 5);
    printf("Pac-Man Game Menu");
    box(2,7,50,10);
    box(7,9, 12, 4);
    gotoxy(10,9);
    printf("Start (s)");
    box(7,40, 12, 4);
    gotoxy(41,9);
    printf("Quit (ESC)");
    do
    {
        key=getch();

    }while(key!='s' && key != 27);
    clrscr();
    if(key != 27){
    setColor(9*16+11);
    clrscr1();
    srand(time(NULL));

    start();
    //program main loop
    do
    {
        //key management
        if(kbhit())
        {
            key=getch();
            if(key==-32)
            {
                key=getch();
            }
        }
            switch(key)
            {
            case 72:
                if(yCon>0)--yCon;
                break;
            case 80:
                if(yCon<23)++yCon;
                break;
            case 75:
                if(xCon>0)--xCon;
                break;
            case 77:
                if(xCon<35)++xCon;
                break;
            }
            //if trying to go through a wall block the player
            if(maze[yCon][xCon]==196 || maze[yCon][xCon]==179||maze[yCon][xCon]==217 || maze[yCon][xCon]==218 || maze[yCon][xCon]==191 || maze[yCon][xCon]==192 || maze[yCon][xCon]==194)
            {
                //don't change player position
                xCon = old_x;
                yCon = old_y;
            }
            else
            {

                if(maze[old_y][old_x]==250)
                {
                    score+=10;
                }
                else if(maze[old_y][old_x]=='o')
                {
                    score+=500;
                    //start the charge
                    charge++;
                }
                //erase before print
                maze[old_y][old_x]=32;
                gotoxy(old_x,old_y);
                printf(" ");
            }
            //update new player position
            if(charge>0)setColor(9*16+1);
            else setColor(9*16+10);
            gotoxy(xCon,yCon);
            printf("%c",i%2==0?128:224);
            //update old y and x before changing them
            old_x=xCon;
            old_y=yCon;

            //increment the charge if it is less than 15... and the apple was eaten
            if(charge < 100 && charge > 0)charge++;
            else if(charge == 100)charge =0;

            // hole penetration 1st
            if(xCon==34&&yCon==11)
            {
                y = 1+rand()%2;

                if(y==1)
                {
                   yCon = 17;
                }
                else
                {
                    yCon = 5;
                }
                xCon = 1;

            }
            // hole penetration 2nd
            if(xCon==0&&yCon==5)
            {
                do
                {
                    y = rand()%3;

                }while(y==0);

                if(y==2)
                {
                    xCon = 1;
                    yCon = 17;
                }
                else
                {
                    xCon = 33;
                    yCon = 11;

                }
            }
            // hole penetration 3rd
            if(xCon==0&&yCon==17)
            {
                do
                {
                    y = rand()%3;

                }while(y==0);

                if(y==2)
                {
                   xCon = 33;
                   yCon = 11;
                }
                else
                {
                    xCon = 1;
                    yCon = 5;
                }
            }
            // get the ghost1 out of the box first
            g1 = ghostMove(i, g1);
            //move second ghost
            if(i>3 && i%2==0)
            {
                if(g2.x==20 && g2.y==11)
                {
                    g2.x=18;
                    g2.y=11;

                    gotoxy(g2.x, g2.y);
                    printf("%c",153);

                    gotoxy(20, 11);
                    printf(" ");
                }

                g2 = ghostMove(i, g2);
             }
             // ghost 3 movement
             if(i>4 && i%3!=0)
             {
                 if(g3.x==16 && g3.y==11)
                 {
                    g3.x=18;
                    g3.y=11;

                    gotoxy(g3.x, g3.y);
                    printf("%c",153);

                    gotoxy(16, 11);
                    printf(" ");
                 }
                 g3 = ghostMove(i, g3);
             }

             //if the player hasn't eaten the bigger apple yet
                if(charge==0)
                {
                     // ghost + player position = death
                     if(lives == 0)key =27;
                     if(g1.x == xCon && g1.y==yCon)key=0;
                     if(g2.x == xCon && g2.y==yCon)key=0;
                     if(g3.x == xCon && g3.y==yCon)key=0;
                     death(&g1.x,&g1.y,&xCon,&yCon);
                     death(&g2.x,&g2.y,&xCon,&yCon);
                     death(&g3.x,&g3.y,&xCon,&yCon);
                }
                else
                {

                    g1 = bonusMove(g1,xCon, yCon);
                    g2 = bonusMove(g2,xCon, yCon);
                    g3 = bonusMove(g3,xCon, yCon);
                    score += 100;
                }


            //updating score and lives
             setColor(14);
             gotoxy(45,3);
             printf("Score is %d", score);

             gotoxy(45, 2);
             printf("Lives: %d", lives-1);
             setColor(9*16+10);
            i++;

            j++;

            usleep(110000);

    }while(key!=27);
}

    if(lives==0)
    {
        int k=0;

        setColor(7);
        clrscr();
        //draw other half screen
        setColor(12);
        while(k<3)
        {

            gotoxy(35,10);
            printf("GAME OVER !!!!");
            _sleep(1000);

            gotoxy(35,10);
            printf("                ");
            _sleep(1000);


            ++k;
        }
        gotoxy(35,10);
        printf("GAME OVER !!!!");
        _sleep(1000);
     }
        setColor(7);
        return 0;
    }

void readData()
{
    i=0;
    FILE *fp;
    char buff[10];
    int x;

    y=0;

    if((fp=fopen("data.txt","rt"))==NULL)
    {
        printf("%s", fp->_ptr);
        while(1){;}
        puts("Couldn't read file!!");
    }
    else
    {
        for(int y=0;y<Y;y++)
        {
            for(i=0;i<X;++i)
            {
                fgets(buff,5,fp);

                x=atoi(buff);

                maze[y][i]=x;
            }
        }
    }
    fclose(fp);
}
void maize(int x, int y)
{
    for(int y_c=0;y_c<23;++y_c)
    {
        for(int j=0;j<35;++j)
        {
            if(maze[y_c][j]==153)
            {
                gx=j;
                gy = y_c;
            }
            if(maze[y_c][j]=='o')
            {
                setColor(9*16+13);
            }
            else if(maze[y_c][j]==250)setColor(9*16+0);
            else if(maze[y_c][j]==153)setColor(9*16+14);
            else setColor(9*16+15);

            gotoxy(x+j,y+y_c);
            printf("%c",maze[y_c][j]);
        }
    }

}
void clrscr1()
{
    int i,j;
    for(i=0;i<30;i++)
    {
        for(j=0;j<40;j++)
        {
            gotoxy(j,i);
            printf(" ");
        }
    }
    gotoxy(0,0);
}
GHOST ghost_dir(GHOST g)
{
    //possible routes array...
    int temp_dir[4]={0,0,0,0};

    //act on the previous direction
    switch(g.dir)
        {
        case 0:
            g.y--;
            break;
        case 1:
            g.y++;
            break;
        case 2:
            g.x--;
            break;
        case 3:
            g.x++;
        }
    //choose new direction
        //check for walls and establish available routes and remove the route you came from
        if((maze[g.y][g.x+1]==32||maze[g.y][g.x+1]==250 || maze[g.y][g.x+1]=='o') && (g.old_x==g.x-1|| g.x==g.old_x)) // test the right direction
        {
            temp_dir[3]=1;// establish that route is avaiable
        }
        else
        {
            temp_dir[3]=0; // route is not available
        }

        if((maze[g.y][g.x-1]==250 || maze[g.y][g.x-1]==32 || maze[g.y][g.x-1]=='o') && (g.old_x==g.x+1||g.old_x==g.x))// establish route is available
        {
            temp_dir[2]=1;
        }
        else
        {
            temp_dir[2]=0;
        }

        if((maze[g.y+1][g.x]==250|| maze[g.y+1][g.x]==32 || maze[g.y+1][g.x]=='o') && (g.old_y==g.y-1 || g.old_y==g.y))// downward route available
        {
            temp_dir[1]=1;
        }
        else
        {
            temp_dir[1]=0;
        }

        if((maze[g.y-1][g.x]==250 || maze[g.y-1][g.x]==32 || maze[g.y-1][g.x]=='o') && (g.old_y == g.y+1||g.old_y==g.y))
        {
            temp_dir[0]=1;
        }
        else
        {
            temp_dir[0]=0;
        }

        if(maze[g.y+1][g.x]==196)
        {
            temp_dir[1]=0;
        }
        if(maze[g.y][g.x+1]==179)
        {
            temp_dir[3]=0;
        }
        if(maze[g.y][g.x-1]==179)
        {
            temp_dir[2]=0;
        }
        // evaluating available directions
             if(g.y < yCon)
             {
                 if(temp_dir[1]==1)
                 {
                     g.dir=1;
                 }
                 else if(temp_dir[3]==1)
                 {
                     g.dir = 3;
                 }
                 else if(temp_dir[2]==1)
                 {
                     g.dir=2;
                 }
                 else
                 {
                     g.dir = 0; // only move up when there's no other choice
                 }
             }
             else if(g.y==yCon)
             {
                 if(g.x > xCon)
                 {
                     if(temp_dir[2]==1)
                     {
                         g.dir=2;
                     }
                     else if(temp_dir[1]==1)
                     {
                         g.dir = 1;
                     }
                     else if(temp_dir[0]==1)
                     {
                         g.dir=0;
                     }
                     else
                     {
                         g.dir = 3; // only go back when there's no other choice
                     }
                 } else if(g.x < xCon)
                     {
                         if(temp_dir[3]==1)
                         {
                             g.dir=3;
                         }
                         else if(temp_dir[1]==1)
                         {
                             g.dir = 1;
                         }
                         else if(temp_dir[0]==1)
                         {
                             g.dir=0;
                         }
                         else
                         {
                             g.dir = 2; // only go back when there's no other choice
                         }
                     }
                     else if(g.x==xCon)g.dir=5;
             }
             else if(g.y>yCon)
             {
                if(temp_dir[0]==1)
                 {
                     g.dir=0;
                 }
                 else if(temp_dir[3]==1&&temp_dir[2]==1)
                 {
                     g.dir =2+rand()%2;
                 }
                 else if(temp_dir[3]==1)
                 {
                     g.dir = 3;
                 }
                 else if(temp_dir[2]==1)
                 {
                     g.dir=2;
                 }
                 else
                 {
                     g.dir = 1; // only move down when there's no other choice
                 }
             }

             return g;
}
GHOST ghostMove(int i, GHOST g1)
{
    setColor(9*16+7);
    if(g1.y<22)
    {
        if(i%2==0)
        {
            if(g1.x==18 && g1.y==11)
            {
                g1.y++;
                gotoxy(g1.x, g1.y);
                printf("%c",153);
                gotoxy(18,11);
                printf(" ");

            }
            else if(g1.x==18 && g1.y==12)
            {
                g1.y++;
                gotoxy(g1.x, g1.y);
                printf("%c",153);
                gotoxy(18, 12);
                printf(" ");
            }
            else
                {
                    //update old pos before changing it
                    g1.old_x=g1.x;
                    g1.old_y =g1.y;
                    //get new ghost pos coordinates
                    g1 = ghost_dir(g1);
                    gotoxy(g1.x, g1.y);
                    printf("%c",153);
                }
                // move over the apples and bigger apples
                if(maze[g1.old_y][g1.old_x]==250)
                {
                    setColor(9*16+12);
                    gotoxy(g1.old_x, g1.old_y);
                    printf("%c", 250);
                }
                else if(maze[g1.old_y][g1.old_x]=='o')
                {
                    setColor(9*16+13);
                    gotoxy(g1.old_x, g1.old_y);
                    printf("%c", 'o');
                }
                else
                {
                    gotoxy(g1.old_x, g1.old_y);
                    printf(" ");
                }
               // setColor(9*16+10);
                 setColor(9*16+7);
            }
    } else
    {
        g1.x=18;
        g1.y=11;
    }

        return g1;
}
void death(int *ghostx,int *ghosty, int *playerx, int *playery)
{
    char key;
    if(*playerx == *ghostx && *playery == *ghosty)
    {
        setColor(14);
        gotoxy(45, 5);
        printf("You died....");
        gotoxy(45, 6);
        printf("Press S to continue....ESC key to quit");

        do
        {
            key=getch();

        }while(key!='s' && key!=27);
        if(key == 's' && lives >0)
        {
            start();
            lives --;
        }
        gotoxy(45, 7);
        printf("Press S to start.....");

        do
        {
            key=getch();

        }while(key!='s');

        setColor(7);
        gotoxy(45, 7);
        printf("                        ");
    }
}
void start()
{
    i=0;                y=1;              x=3;
    s=0;                xCon = 18;        yCon = 17;
    old_x = xCon;       old_y = yCon;     g1.x =18;
    g1.y=11;            g1.old_y =g1.y;   g1.old_x =0;
    g2.x= 20;           g2.y = 11;        g2.old_y = g2.y;
    g2.old_x = 0;       g3.x = 16;        g3.y = 11;
    g3.old_y =g3.y;     g3.old_x = 0;

    g1.dir = 2+rand()%2;   g2.dir = 2+rand()%2;  g3.dir = 2+rand()%2;

    setColor(7);
    //draw a maze
    maize(0,0);

    gotoxy(xCon,yCon);
    printf("%c",128);
}
GHOST bonusMove(GHOST g, int playerX, int PlayerY)
{
    if(g.x == playerX && g.y==PlayerY)
    {
        g.x = 18;
        g.y = 11;

        gotoxy(playerX, PlayerY);
        printf("%c",128);
    }

    return g;
}
