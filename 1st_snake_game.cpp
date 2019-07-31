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

#define WIDTH 60
#define HEIGHT 20 
void gotoxy(int x, int y)
{
	COORD coord;
 	coord.X = x;
	coord.Y = y;
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
} 
int main()
{		
	short speed, i, j;
	
	hidecursor();
	
	system("COLOR F");
	printf("\n\tWELCOME TO SNAKE's LIFE\n");
	printf("\n\tPRESS CORRESPONDING NUMBER TO CHOOSE SNAKE's SPEED:\n");
	printf("\n\t1. SLOW		2. NORMAL	3. FAST\n");
	scanf("%d",&speed);
	switch (speed)
	{
		case 1: speed = 200; break;
		case 2: speed = 100; break;
		case 3: speed = 50; break;
	}
	gotoxy (WIDTH-5, HEIGHT-5);
	printf("READY");
	Sleep(1000);
	system("cls");
	for (i = 3; i>=1; i--)
	{
		gotoxy (WIDTH-5, HEIGHT-5);
		printf("%d",i);
		Sleep (1000);
		system("cls");
	}
	
	int fx, fy;
	int x[100], y[100], score, len, flow;
	bool again, running, ate;
	
	again=true;
	running=true;
	
	srand(time(NULL));
	
	while(again)
	{
		//setup 
		score=0;
		len=1;
		x[0]= WIDTH/2;
		y[0]= HEIGHT/2;
		fx= rand() % (2*WIDTH-6)+5;
		fy= rand() % (HEIGHT-6)+5;
		flow=RIGHT;
		
		// Draw a hollow rectangle, which border the playing-zone	
		for(i = 1; i<=HEIGHT; i++) 			
			for(j = 1; j<=WIDTH; j++) 
			{
				if(i==1 || i==HEIGHT
					|| j==1 || j==WIDTH)
					printf("# ");
				else 
					printf("  ");
			}
			
		gotoxy(1, HEIGHT + 2);
		printf("Press Q to quit");	

		// Update screen	
		while(running)
		{	
			// delete the snake's trace
			gotoxy(x[len-1], y[len-1]);
			printf(" ");
			
			// Coordinate of snake's segment will be assigned to the following segments
			for(i=len-1; i>=1; i--)  
			{				
				x[i] = x[i-1]; 
				y[i] = y[i-1];
			}
			
			// input from keyboard
			if (kbhit())
			{
				char c = getch();
				switch (tolower(c))
				{
					case 'q':{
						running=false;
						again=false; 
						break;
					}
					default:
					{
						if ((c=='w' || c=='W')&& flow!=DOWN)
							flow=UP;
						else if((c=='s' || c=='S') && flow!=UP)
							flow=DOWN;
						else if((c=='a' || c=='A')&& flow!=RIGHT)
							flow=LEFT;
						else if((c=='d' || c=='D') && flow!=LEFT)
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
			
			//draw snake head
			gotoxy(x[0],y[0]);
			printf("X");
			
			// draw snake's body
			for(i=1; i<=len-1; i++)
			{
				gotoxy(x[i],y[i]);
				printf("0");
			}
			
			// draw score
			gotoxy(1, HEIGHT + 1);
			printf("SCORE: %d\n",score);
			
			// Snake get $
			if(x[0]==fx && y[0]==fy)
			{
				score++;
				len++;
				ate=true;	
			}
			
			// create a new $ at diferrent location in random way
			while(ate) 
			{
				fx= rand() % (2*WIDTH-6) + 5;
				fy= rand() % (HEIGHT-6) + 5;
				for(i=0; i<=len-1; i++)			
					if(fx!=x[i] && fy!=y[i]) 
						ate=false;
			}
				
			// draw $
			gotoxy(fx,fy);
			printf("$");
			
			// snake hits border
			if (x[0] == (2*WIDTH - 2) || x[0] == 1 
				|| y[0] == 1 || y[0] == (HEIGHT -1))
			{  
				running = false;
				for(i=0;i<=len-1;i++)
				{
					gotoxy(x[i],y[i]);
					printf("+");
				}
			}
			
			// Snake kills itself	
			for(i=1; i<=len-1; i++)
				if(x[0]==x[i] && y[0]==y[i])
				{
					running=false;
					for(i=0;i<=len-1;i++)
					{
						gotoxy(x[i],y[i]);
						printf("*");
					}
				}
			
			gotoxy(0,0);
			
			Sleep ( speed );
		}
		
	// play again ?
	if(!running )
		{
			system("cls");
			if(!again)
				break;
			gotoxy(WIDTH-20, HEIGHT-10);
			printf("Press SPACE to play again or 'Q' to finish");
			while(kbhit() || !running)
			{
				char playagain=getch();
				switch(tolower(playagain))
				{
					case 'q' : running=true; again=false; break;
					case ' ' : running=true; system("cls");
				}
			}
		}
	}
	return 0;
}
