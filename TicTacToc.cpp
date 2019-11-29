#include"TicTacToc.h"
using namespace std;
//菜单页面
void tictactoc::menu(void)
{
	size_t menu_position = 0;//记录菜单页光标
	draw_menu(menu_position);//绘制菜单页面
	while (true) //开始监听键盘
	{
		if (!_kbhit())//如果有键被按下则返回真，否则返回假
			continue;
		switch (_getch())//判断键值
		{
		case 72://Up
			if (menu_position > 0)
				--menu_position;
			else
				menu_position = 4;
			draw_menu(menu_position);
			break;
		case 80://Down
			if (menu_position < 4)
				++menu_position;
			else
				menu_position = 0;
			draw_menu(menu_position);
			break;
		case 27://ESC
			if (!running)//游戏开始后才能按ESC返回
				continue;
			draw();
			return;
			break;
		case 13://Enter  按下Enter键则判断被选中的选项
			switch (menu_position)
			{
			case 0://继续
				running = true;
				draw();
				return;
				break;
			case 1://重置游戏
				restart();
				running = true;
				draw();
				return;
				break;
			case 2://打开电脑玩家
				computer_flag = thisflag;
				draw_menu(menu_position);
				break;
			case 3://关闭电脑玩家
				computer_flag = 0;
				draw_menu(menu_position);
				break;
			case 4://退出游戏
				exit(0);
				break;
			}
			break;
		};
	}
}
//绘制棋局
void tictactoc::draw(void)const
{
	system("cls");
	cout << "-------------" << endl;
	for (size_t x = 0; x != 3; ++x)
	{
		cout << "|";
		for (size_t y = 0; y != 3; ++y)
		{
			if (x != cursor_position.x || y != cursor_position.y)//如果是当前光标所在位置，则加上背景色
			{
				cout << " " << chess_board[x][y] << " |";
			}
			else if (chess_board[x][y] == 0)//可走方格的背景色设为绿，不可走方格背景色设为红
			{
				printf(" \033[42m%d\033[0m |", chess_board[x][y]);
			}
			else
			{
				printf(" \033[41m%d\033[0m |", chess_board[x][y]);
			}
		}
		cout << "\n-------------" << endl;
	}
	//标注是谁的回合+操作提示
	printf("\nThis is \033[33m%dP\033[0m's trun.\n"\
		"\033[32mPress \033[33m↑↓←→\033[32m to move the cursor. Press \033[33mEnter\033[32m to place a piece. Press \033[33mESC\033[32m to back to the MENU.\033[0m\n", thisflag);
}
//绘制菜单页面,传入无符号整数表示菜单光标位置
void tictactoc::draw_menu(const size_t menu_position)const
{
	system("cls");
	const char* menu_options[] = {
		"Continue",
		"Restart",
		"Computer Player ON",
		"Computer Player OFF",
		"Exit"
	};//菜单选项
	if (!running)
		menu_options[0] = "Start";
	const char* tips[] = {
		"Press \033[33m↑↓\033[32m to select an option. Press \033[33mEnter\033[32m to confirm. Press \033[33mESC\033[32m to back to the game." ,
		"Restart the game.",
		"Turn on the computer player, and then it will take over the current round.",
		"Turn off the computer player.",
		"Quit the game"
	};//选项提示
	printf("\t\033[44m MENU \033[0m\n\n");
	for (size_t i = 0; i != 5; ++i)//显示菜单主体
	{
		if (i == menu_position)//如果是光标所在位置则设为黄色背景黑色前景
			printf("  \033[30;43m%s\033[0m\n", menu_options[i]);
		else
			printf("  %s\n", menu_options[i]);
	}
	printf("\n  \033[35mComputer: ");
	if (computer_flag != 0)
		printf("%dP\n", computer_flag);
	else
		printf("NULL\n");
	printf("  \033[32m%s\033[0m\n", tips[menu_position]);//显示选项提示
}
//重置游戏
void tictactoc::restart(void)
{
	free_grids = {
		coord(0,0),coord(0,1),coord(0,2),
		coord(1,0),coord(1,1),coord(1,2),
		coord(2,0),coord(2,1),coord(2,2)
	};
	for (auto& i : chess_board)
		for (auto& j : i)
			j = 0;
	computer_flag = 0;
	cursor_position = coord(0, 0);
	thisflag = 1;
}
//放置棋子，传入坐标类型表示要落子的位置
void tictactoc::place_piece(const coord position)
{
	if (chess_board[position.x][position.y] != 0)//光标处是否可落子
		return;
	chess_board[position.x][position.y] = thisflag;
	for (auto i = free_grids.begin(); i != free_grids.end(); ++i)
		if (*i == position)
		{
			free_grids.erase(i);
			break;
		}
	draw();
	//落子后开始判断游戏状况
	if (judger(thisflag) == 1)//如果获胜。。。
	{
		if (computer_flag != 0)
			if (thisflag == computer_flag)//是否是电脑获胜
				printf("\033[41mYou Lose!\033[0m\nPress \033[33mEnter\033[0m to back to the MENU...");
			else
				printf("\033[30;43mYou WIN!\033[0m\nPress \033[33mEnter\033[0m to back to the MENU...");
		else
			printf("\033[30;43m%dP WIN!\033[0m\nPress \033[33mEnter\033[0m to back to the MENU...", thisflag);
		cin.get();
		restart();//重置游戏
		running = false;
		menu();//回到菜单
		return;
	}
	else if (judger(thisflag) == -1)//如果和棋。。。
	{
		printf("\033[42mThe two sides draw!\033[0m\nPress \033[33mEnter\033[0m to back to the MENU...");
		cin.get();
		restart();
		running = false;
		menu();
		return;
	}
	thisflag = (thisflag == 1) ? 2 : 1;//将thisflag设为下一玩家
	draw();//刷新回合显示
}
//裁判，传入无符号整数表示刚落子的玩家，返回-1表示和棋，1表示获胜,0表示无事件
int tictactoc::judger(const size_t player)const
{
	for (size_t x = 0; x != 3; ++x)//所有横排3个是否存在3连子
	{
		for (size_t y = 0; y != 3; ++y)
			if (chess_board[x][y] != player)
				break;
			else if (y == 2)
				return 1;
	}
	for (size_t y = 0; y != 3; ++y)//所有纵排3个是否存在3连子
	{
		for (size_t x = 0; x != 3; ++x)
			if (chess_board[x][y] != player)
				break;
			else if (x == 2)
				return 1;
	}
	if (chess_board[0][0] == player && chess_board[1][1] == player && chess_board[2][2] == player)//斜对角。。。
		return 1;
	if (chess_board[0][2] == player && chess_board[1][1] == player && chess_board[2][0] == player)//反斜对角。。。
		return 1;
	if (free_grids.size() == 0)//棋盘是否已满，若已满则和棋
		return -1;
	return 0;
}
//电脑走棋，返回要落子的坐标
coord tictactoc::computer_play(void)const
{
	size_t counter = 0;
	int other_flag = (thisflag == 1) ? 2 : 1;//记录非电脑玩家的回合顺序

	//优先考虑能直接获胜的情况
	for (size_t x = 0; x != 3; ++x)//所有横排存在两连对+一空格则填空格
	{
		counter = 0;
		for (size_t y = 0; y != 3; ++y)
			if (chess_board[x][y] == computer_flag)
				++counter;
		if (counter == 2)
			for (size_t y = 0; y != 3; ++y)
				if (chess_board[x][y] == 0)
					return coord(x, y);
	}
	for (size_t y = 0; y != 3; ++y)//所有纵排存在两连对+一空格则填空格
	{
		counter = 0;
		for (size_t x = 0; x != 3; ++x)
			if (chess_board[x][y] == computer_flag)
				++counter;
		if (counter == 2)
			for (size_t x = 0; x != 3; ++x)
				if (chess_board[x][y] == 0)
					return coord(x, y);
	}
	//斜对角。。。
	counter = 0;
	for (size_t i = 0; i != 4; ++i)
	{
		if (chess_board[i][i] == computer_flag)
			counter++;
	}
	if (counter == 2)
		for (size_t i = 0; i != 4; ++i)
			if (chess_board[i][i] == 0)
				return coord(i, i);
	//反斜对角。。。
	counter = 0;
	for (size_t i = 0; i != 4; ++i)
	{
		if (chess_board[2 - i][i] == computer_flag)
			counter++;
	}
	if (counter == 2)
		for (size_t i = 0; i != 4; ++i)
			if (chess_board[2 - i][i] == 0)
				return coord(2 - i, i);

	//其次阻止对方胜利
	for (size_t x = 0; x != 3; ++x)//所有横排存在两连对+一空格则填空格
	{
		counter = 0;
		for (size_t y = 0; y != 3; ++y)
			if (chess_board[x][y] == other_flag)
				++counter;
		if (counter == 2)
			for (size_t y = 0; y != 3; ++y)
				if (chess_board[x][y] == 0)
					return coord(x, y);
	}
	for (size_t y = 0; y != 3; ++y)//所有纵排存在两连对+一空格则填空格
	{
		counter = 0;
		for (size_t x = 0; x != 3; ++x)
			if (chess_board[x][y] == other_flag)
				++counter;
		if (counter == 2)
			for (size_t x = 0; x != 3; ++x)
				if (chess_board[x][y] == 0)
					return coord(x, y);
	}
	//斜对角。。。
	counter = 0;
	for (size_t i = 0; i != 4; ++i)
	{
		if (chess_board[i][i] == other_flag)
			counter++;
	}
	if (counter == 2)
		for (size_t i = 0; i != 4; ++i)
			if (chess_board[i][i] == 0)
				return coord(i, i);
	//反斜对角。。。
	counter = 0;
	for (size_t i = 0; i != 4; ++i)
	{
		if (chess_board[2 - i][i] == other_flag)
			counter++;
	}
	if (counter == 2)
		for (size_t i = 0; i != 4; ++i)
			if (chess_board[2 - i][i] == 0)
				return coord(2 - i, i);

	//若不存在两连对+一空格，则随机选择空格子落子
	srand((unsigned)time(NULL));
	return free_grids[rand() % free_grids.size()];
}