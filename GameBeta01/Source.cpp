#include<stdio.h>
#include <SFML/Graphics.hpp>
#include<windows.h>
#include<conio.h>
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y);
	printf("*");
}
void erase_ship(int x, int y)
{
	gotoxy(x, y);
	printf(" ");
}
void drawanderase(int x, int y)
{
	int jump = 1;
	while (jump!=8)
	{erase_ship(x, y); draw_ship(x, --y); Sleep(50); jump++;}
	while (jump!=1)
	{ erase_ship(x, y); draw_ship(x, ++y); Sleep(50); jump--;}
}
void move(int x, int y)
{
	char ch = ' ';
	do {
		if (_kbhit()) {
			ch = _getch();

			if (ch == 'a') { drawanderase(x, y); }
			if (ch == ' ') { drawanderase(x, y); }
			fflush(stdin);
		}
		Sleep(50);
	} while (ch != 'x');
}
int main()
{
	int x = 10, y = 15;
	draw_ship(x, y);
	move(x, y);
	return 0;
}