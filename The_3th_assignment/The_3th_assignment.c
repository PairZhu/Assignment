#include <stdio.h>
#include <windows.h>
#include <conio.h>
typedef struct
{
	size_t x;
	size_t y;
}coord;//用于保存坐标
enum keyid { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13 };//保存↑ ↓ ← → Enter键的键值
void draw(const coord, const int(*)[12], const coord);
void CombineAB(int(*)[12], const int(*)[6], const int(*)[6]);
void move(coord*, int);
void modify(int(*)[6], int(*)[6], const size_t, const size_t);
int main()
{
	int A[5][6] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };
	int B[5][6] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };
	coord pos;//记录光标在显示框的位置
	pos.x = 0, pos.y = 0;
	coord location = pos;//记录显示框在数组的位置（为左上角的数据的位置）
	int combine[5][12];//用于记录A,B数组合并后的数据，方便绘制界面和判断边界
	CombineAB(combine, A, B);//将A,B数据合并进combine中
	draw(location, combine, pos);
	while (1) {
		if (!_kbhit())//如果有键被按下则返回真，否则返回假
			continue;
		switch (_getch())//判断键值
		{
		case Up:
			if (pos.x == 1)//如果光标在第二行则移动光标位置
				pos.x = 0;
			else
				move(&location, Up);//如果光标在第一行则移动显示框位置
			draw(location, combine, pos);//刷新界面
			break;
		case Down://同上
			if (pos.x == 0)
				pos.x = 1;
			else
				move(&location, Down);
			draw(location, combine, pos);
			break;
		case Left://同上
			if (pos.y == 1)
				pos.y = 0;
			else
				move(&location, Left);
			draw(location, combine, pos);
			break;
		case Right://同上
			if (pos.y == 0)
				pos.y = 1;
			else
				move(&location, Right);
			draw(location, combine, pos);
			break;
		case Enter:
			modify(A, B, location.x + pos.x, location.y + pos.y);//进入修改A或B数组数据的函数
			CombineAB(combine, A, B);//刷新combine中的数据（合并A,B数组的数据）
			draw(location, combine, pos);//刷新界面
			break;
		}
	}
}

//绘制界面，接受A,B结合后的数组bombine,显示框位置和光标位置
void draw(const coord location, const int(*combine)[12], const coord pos)
{
	system("cls");//清空屏幕
	if (location.x == 0)//如果在数组的上边界则将上边框染红
		printf("\033[31m");
	printf("\t---------\033[0m\n");
	for (size_t x = 0; x != 2; ++x)//绘制2*2的显示框内的数据
	{
		if (location.y == 0)//如果在数组的左边界则将左边框染红
			printf("\033[31m");
		printf("\t|\033[0m");
		for (size_t y = 0; y != 2; ++y)
		{
			if (x == pos.x && y == pos.y)//如果是光标所在的位置则将背景染绿
				if (combine[x + location.x][y + location.y] < 10)//数值小于10的数字前后加个空格，大于等于10小于100的加一个空格，否则不加空格
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

			if (y == 1 && location.y == 10)//如果在数组的右边界则将右边框染红
				printf("\033[31m");
			printf("|\033[0m");
		}
		if (location.x == 3 && x==1)//如果在数组的下边框，则将下边框线染红
			printf("\033[31m");
		printf("\n\t---------\033[0m\n");
	}
	printf("\n\033[31mRed\033[32m lines mean the boundary lines\nPress \033[33mEnter\033[32m to modify the data...\033[0m\n");
}

//将A,B的数据合并进新的数组combine里，方便绘制界面和判断边界
void CombineAB(int(*combine)[12], const int(*A)[6], int(*B)[6])
{
	for (size_t i = 0; i != 5; ++i)
		for (size_t j = 0; j != 12; ++j)
			combine[i][j] = (j < 6) ? A[i][j] : B[i][j - 6];
}

//移动显示框
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

//修改A或B数组中的数据，接受的x,y参数为要修改的值在数组中的横纵坐标(即显示框坐标+光标在信息框中的坐标)
void modify(int(*A)[6], int(*B)[6],const size_t x, const size_t y)
{
	printf("Please enter the new data you want to fill in:");
	int new_num;
	scanf_s("%d", &new_num);//让用户输入要修成的值
	if (y < 6)//小于6则修改A中数据否则修改B中的数据
		A[x][y] = new_num;
	else
		B[x][y - 6] = new_num;
}