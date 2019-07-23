#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
const int width = 60, height = 20;
int i, j;
int x[100], y[100], fx, fy, temx, temy; 
int score, len, flow=RIGHT;
bool running, ate; 

void gotoxy(int x, int y)
{
	COORD coord;
 	coord.X = x;
	coord.Y = y;
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
} 

void setup(){
	running= true;
	fx= (rand() % width-1)+2;
	fy= (rand() % height-1)+2;	
	x[0]= width/2;
	y[0]= height/2;
	len=0;
	score= 0;
}
void draw(){
	system("cls");
	for(i = 1; i<=height; i++)
		for(j = 1; j<=width; j++){
			if(i==1 || i==height || j==1 || j==width)
			{
				printf("# ");
			}
			else 
				printf("  ");
		}
	gotoxy(x[0],y[0]);
	printf("X");
	for(i=len; i>0; i--)
	{
		x[i]=x[i-1];
		y[i]=y[i-1];
	}
	for(i=1; i<=len; i++)
	{
		gotoxy(x[i],y[i]);
		printf("O");
	}
	while(ate)
	{
		fx= (rand() % width-1)+2;
		fy= (rand() % height-1)+2;
		for(i=0; i<=len-1; i++)
			if(fx!=x[i] && fy!=y[i])
			{
				ate=false;
				break;
			}
		if(ate==false)
			break;
	}
	
	gotoxy(fx,fy);
	printf("$");
	gotoxy(1, height + 2);
	printf("SCORE: %d",score);
}
void control(){
	if(kbhit())
	{
		char c=getch();
		switch(tolower(c))
		{
			case 'q': running=false; break;
			
			default:
			{
				if(c==119 && flow!=DOWN)
					flow=UP;
				else if(c==115 && flow!=UP)
					flow=DOWN;
				else if(c==97 && flow!=RIGHT)
					flow=LEFT;
				else if(c==100 && flow!=LEFT)
					flow=RIGHT;
		  		break;
			}
		}
	}
	switch(flow)
	{
		case UP: y[0]--; break;
		case DOWN: y[0]++; break;
		case LEFT: x[0]--; break;
		case RIGHT: x[0]++; break;
	}
}
void law()
{
	if(x[0]==fx && y[0]==fy)
	{
		score++;
		len++;
		ate=true;
	}
		if(x[0]>2*width)
			x[0]=1;
		if(x[0]<1)
			x[0]=2*width;
		if(y[0]>height-2)
			y[0]=1;
		if(y[0]<1)
			y[0]=height-2;
		for(i=1; i<len;i++)
			if(x[0]==x[i] && y[0]==y[i])
				running=false;
	
}
main()
{
	setup();
	srand(time(NULL));
	while(running){
		draw();
		control();
		law();
		Sleep(1);
	}	
}
