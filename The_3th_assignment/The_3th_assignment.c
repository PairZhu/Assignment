#include <stdio.h>
#include <windows.h>
#include <conio.h>
typedef struct
{
	size_t x;
	size_t y;
}coord;
enum keyid { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13 };
void draw(const coord, const int(*)[12], const coord);
void CombineAB(int(*)[12], const int(*)[6], const int(*)[6]);
void move(coord*, int);
void modify(int(*)[6], int(*)[6], const size_t, const size_t);
int main()
{
	int A[5][6] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };
	int B[5][6] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };
	coord pos;
	pos.x = 0, pos.y = 0;
	coord location = pos;
	location.x = 0, location.y = 0;
	int combine[5][12];
	CombineAB(combine, A, B);
	draw(location, combine, pos);
	while (1) {
		if (!_kbhit())//如果有键被按下则返回真，否则返回假
			continue;
		switch (_getch())//判断键值
		{
		case Up:
			if (pos.x == 1)
				pos.x = 0;
			else
				move(&location, Up);
			draw(location, combine, pos);
			break;
		case Down:
			if (pos.x == 0)
				pos.x = 1;
			else
				move(&location, Down);
			draw(location, combine, pos);
			break;
		case Left:
			if (pos.y == 1)
				pos.y = 0;
			else
				move(&location, Left);
			draw(location, combine, pos);
			break;
		case Right:
			if (pos.y == 0)
				pos.y = 1;
			else
				move(&location, Right);
			draw(location, combine, pos);
			break;
		case Enter:
			modify(A, B, location.x + pos.x, location.y + pos.y);
			CombineAB(combine, A, B);
			draw(location, combine, pos);
			break;
		}
	}
}
void draw(const coord location, const int(*combine)[12], const coord pos)
{
	system("cls");
	if (location.x == 0)
		printf("\033[31m");
	printf("\t---------\033[0m\n");
	for (size_t x = 0; x != 2; ++x)
	{
		if (location.y == 0)
			printf("\033[31m");
		printf("\t|\033[0m");
		for (size_t y = 0; y != 2; ++y)
		{
			if (x == pos.x && y == pos.y)
				if (combine[x + location.x][y + location.y] < 10)
					printf(" \033[42m%d\033[0m ", combine[x + location.x][y + location.y]);
				else if (combine[x + location.x][y + location.y] < 100)
					printf("\033[42m%d\033[0m ", combine[x + location.x][y + location.y]);
				else
					printf("\033[42m%d\033[0m", combine[x + location.x][y + location.y]);
			else
					if (combine[x + location.x][y + location.y] < 10)
						printf(" %d ", combine[x + location.x][y + location.y]);
					else if(combine[x + location.x][y + location.y] < 100)
						printf("%d ", combine[x + location.x][y + location.y]);
					else
						printf("%d", combine[x + location.x][y + location.y]);

			if (y == 1 && location.y == 10)
				printf("\033[31m");
			printf("|\033[0m");
		}
		if (location.x == 3 && x==1)
			printf("\033[31m");
		printf("\n\t---------\033[0m\n");
	}
	printf("\n\033[31mRed\033[32m lines mean the boundary lines\nPress \033[33mEnter\033[32m to modify the data...\033[0m\n");
}
void CombineAB(int(*combine)[12], const int(*A)[6], int(*B)[6])
{
	for (size_t i = 0; i != 5; ++i)
		for (size_t j = 0; j != 12; ++j)
			combine[i][j] = (j < 6) ? A[i][j] : B[i][j - 6];
}
void move(coord* location, int direct)
{
	switch (direct)
	{
	case Up:
		if (location->x <= 0)
			return;
		--location->x;
		break;
	case Down:
		if (location->x >= 3)
			return;
		++location->x;
		break;
	case Left:
		if (location->y <= 0)
			return;
		--location->y;
		break;
	case Right:
		if (location->y >= 10)
			return;
		++location->y;
		break;
	}
}
void modify(int(*A)[6], int(*B)[6],const size_t x, const size_t y)
{
	printf("Please enter the new data you want to fill in:");
	int new_num;
	scanf_s("%d", &new_num);
	if (y < 6)
		A[x][y] = new_num;
	else
		B[x][y - 6] = new_num;
}