#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

#define LENGTH 20

enum Color{
	RED = BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
	GREEN = BACKGROUND_GREEN|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
	BLUE = BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
	CYAN = BACKGROUND_BLUE|BACKGROUND_GREEN|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
	YELLOW = BACKGROUND_RED|BACKGROUND_GREEN|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
	PURPLE = BACKGROUND_RED|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
	WHITE = BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE,
	BLACK = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE
};

enum Direction{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77
};

void sleep(int ms)
{
	unsigned int time = clock();
	while(clock()-time<ms);
}

void setpos(int i,int j)
{
	COORD coor;
	coor.X=2*j;
	coor.Y=i;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coor);
}

void color(int color)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle,color);
}

void cursor(bool visible)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize=1;
	info.bVisible=visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
}

bool move(int dir, int snake[][2], int apple[2], int& head, int& length)
{
	if(dir==UP && snake[head][0]>0)
	{
		snake[(head+1)%(LENGTH*LENGTH)][0]=snake[head][0]-1;
		snake[(head+1)%(LENGTH*LENGTH)][1]=snake[head][1];
	}
	else if(dir == DOWN && snake[head][0]<LENGTH-1)
	{
		snake[(head+1)%(LENGTH*LENGTH)][0]=snake[head][0]+1;
		snake[(head+1)%(LENGTH*LENGTH)][1]=snake[head][1];
	}
	else if(dir == LEFT && snake[head][1]>0)
	{
		snake[(head+1)%(LENGTH*LENGTH)][0]=snake[head][0];
		snake[(head+1)%(LENGTH*LENGTH)][1]=snake[head][1]-1;
	}
	else if(dir == RIGHT && snake[head][1]<LENGTH-1)
	{
		snake[(head+1)%(LENGTH*LENGTH)][0]=snake[head][0];
		snake[(head+1)%(LENGTH*LENGTH)][1]=snake[head][1]+1;
	}
	else
	{
		system("cls");
		setpos(0,0);
		cout << "You hit the wall!";
		sleep(1000);
		return false;
	}
	setpos(snake[head][0]+1,snake[head][1]+1);
	color(YELLOW);
	cout << "  ";
	color(BLACK);
	
	head=(head+1)%(LENGTH*LENGTH);
	
	{
		int i;
		for(i=1;i<length;i++)
		{
			if(head-i<0 && snake[head-i+LENGTH*LENGTH][0]==snake[head][0] && snake[head-i+LENGTH*LENGTH][1]==snake[head][1])
				break;
			else if(snake[head-i][0]==snake[head][0] && snake[head-i][1]==snake[head][1])
				break;
		}
		if(i!=length)
		{
			system("cls");
			setpos(0,0);
			cout << "You hit the yourself!";
			sleep(1000);
			return false;
		}
	}
	
	if(snake[head][0]==apple[0]&&snake[head][1]==apple[1])
	{
		length++;
		while(1)
		{
			int i;
			apple[0]=rand()%LENGTH;
			apple[1]=rand()%LENGTH;
			for(i=0;i<length;i++)
			{
				if(head-i<0 && snake[head-i+LENGTH*LENGTH][0]==apple[0] && snake[head-i+LENGTH*LENGTH][1]==apple[1])
					break;
				else if(snake[head-i][0]==apple[0] && snake[head-i][1]==apple[1])
					break;
			}
			if(i==length)
				break;
		}
		setpos(apple[0]+1,apple[1]+1);
		color(RED);
		cout << "  ";
		color(BLACK);
	}
		
	if(head-length<0)
		setpos(snake[head-length+LENGTH*LENGTH][0]+1,snake[head-length+LENGTH*LENGTH][1]+1);
	else
		setpos(snake[head-length][0]+1,snake[head-length][1]+1);
	color(BLACK);
	cout << "  ";
	
	setpos(snake[head][0]+1,snake[head][1]+1);
	color(GREEN);
	cout << "  ";
	color(BLACK);
	setpos(0,LENGTH+5);
	cout << "Time: " << 250-(length-2)*5 << " ";
	return true;
}

int main () 
{	
	srand(time(NULL));
	int apple[2];
	int snake[LENGTH*LENGTH][2];
	char input;
	int dir;
	int head, length;
	
	int time=-500,begin=clock();
	
	cursor(false);
	
	while(true)
	{
		head=1;
		length=2;
		dir = UP;
		time = clock();
		do{
			apple[0]=rand()%LENGTH;
			apple[1]=rand()%LENGTH;
		}while(apple[0]==LENGTH/2 && apple[1]==LENGTH/2 && apple[0]!=LENGTH/2+1);
		setpos(apple[0]+1,apple[1]+1);
		color(RED);
		cout << "  ";
		color(BLACK);
		
		for(int i=0;i<LENGTH;i++)
			for(int j=0;j<LENGTH;j++)
				snake[i*LENGTH+j][0]=snake[i*LENGTH+j][1]=-1;
		snake[head][0]=snake[head][1]=snake[head-1][1]=LENGTH/2;
		snake[head-1][0]=LENGTH/2+1;	
	
		for(int i=0;i<LENGTH+2;i++)
		{
			setpos(0,i);
			cout << "x ";
			setpos(LENGTH+1,i);
			cout << "x ";
			setpos(i,0);
			cout << "x ";
			setpos(i,LENGTH+1);
			cout << "x ";
		}
	
		while(input != 27)
		{
			if(kbhit())
			{
				input = getch();
				if(input == 'w'|| input == UP)
				{
					if(snake[head][0]!=(head<1?snake[LENGTH*LENGTH-1][0]:snake[head-1][0])+1)
						dir = UP;
				}
				else if(input == 'd' || input == RIGHT)
				{
					if(snake[head][1]!=(head<1?snake[LENGTH*LENGTH-1][1]:snake[head-1][1])-1)
						dir = RIGHT;
				}
				else if(input == 's' || input == DOWN)
				{
					if(snake[head][0]!=(head<1?snake[LENGTH*LENGTH-1][0]:snake[head-1][0])-1)
						dir = DOWN;
				}
				else if(input == 'a' || input == LEFT)
				{
					if(snake[head][1]!=(head<1?snake[LENGTH*LENGTH-1][1]:snake[head-1][1])+1)
						dir = LEFT;
				}
			}
			if(clock()-time>250-(length-2)*5)
			{
				time = clock();
				if(!move(dir, snake, apple, head, length))
					break;
			}
		}
		system("cls");
		input = 0;
		setpos(0,0);
		cout << "Continue? (Y?N)";
		while(input!='y' && input!='n')
			input = getch();
		if(input=='n')
			break;
	}
	cursor(true);
  	return 0;
}

