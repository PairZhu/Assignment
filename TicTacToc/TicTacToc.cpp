#include"TicTacToc.h"
using namespace std;
//�˵�ҳ��
void tictactoc::menu(void)
{
	size_t menu_position = 0;//��¼�˵�ҳ���
	draw_menu(menu_position);//���Ʋ˵�ҳ��
	while (true) //��ʼ��������
	{
		if (!_kbhit())//����м��������򷵻��棬���򷵻ؼ�
			continue;
		switch (_getch())//�жϼ�ֵ
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
			if (!running)//��Ϸ��ʼ����ܰ�ESC����
				continue;
			draw();
			return;
			break;
		case 13://Enter  ����Enter�����жϱ�ѡ�е�ѡ��
			switch (menu_position)
			{
			case 0://����
				running = true;
				draw();
				return;
				break;
			case 1://������Ϸ
				restart();
				running = true;
				draw();
				return;
				break;
			case 2://�򿪵������
				computer_flag = thisflag;
				draw_menu(menu_position);
				break;
			case 3://�رյ������
				computer_flag = 0;
				draw_menu(menu_position);
				break;
			case 4://�˳���Ϸ
				exit(0);
				break;
			}
			break;
		};
	}
}
//�������
void tictactoc::draw(void)const
{
	system("cls");
	cout << "-------------" << endl;
	for (size_t x = 0; x != 3; ++x)
	{
		cout << "|";
		for (size_t y = 0; y != 3; ++y)
		{
			if (x != cursor_position.x || y != cursor_position.y)//����ǵ�ǰ�������λ�ã�����ϱ���ɫ
			{
				cout << " " << chess_board[x][y] << " |";
			}
			else if (chess_board[x][y] == 0)//���߷���ı���ɫ��Ϊ�̣������߷��񱳾�ɫ��Ϊ��
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
	//��ע��˭�Ļغ�+������ʾ
	printf("\nThis is \033[33m%dP\033[0m's trun.\n"\
		"\033[32mPress \033[33m��������\033[32m to move the cursor. Press \033[33mEnter\033[32m to place a piece. Press \033[33mESC\033[32m to back to the MENU.\033[0m\n", thisflag);
}
//���Ʋ˵�ҳ��,�����޷���������ʾ�˵����λ��
void tictactoc::draw_menu(const size_t menu_position)const
{
	system("cls");
	const char* menu_options[] = {
		"Continue",
		"Restart",
		"Computer Player ON",
		"Computer Player OFF",
		"Exit"
	};//�˵�ѡ��
	if (!running)
		menu_options[0] = "Start";
	const char* tips[] = {
		"Press \033[33m����\033[32m to select an option. Press \033[33mEnter\033[32m to confirm. Press \033[33mESC\033[32m to back to the game." ,
		"Restart the game.",
		"Turn on the computer player, and then it will take over the current round.",
		"Turn off the computer player.",
		"Quit the game"
	};//ѡ����ʾ
	printf("\t\033[44m MENU \033[0m\n\n");
	for (size_t i = 0; i != 5; ++i)//��ʾ�˵�����
	{
		if (i == menu_position)//����ǹ������λ������Ϊ��ɫ������ɫǰ��
			printf("  \033[30;43m%s\033[0m\n", menu_options[i]);
		else
			printf("  %s\n", menu_options[i]);
	}
	printf("\n  \033[35mComputer: ");
	if (computer_flag != 0)
		printf("%dP\n", computer_flag);
	else
		printf("NULL\n");
	printf("  \033[32m%s\033[0m\n", tips[menu_position]);//��ʾѡ����ʾ
}
//������Ϸ
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
//�������ӣ������������ͱ�ʾҪ���ӵ�λ��
void tictactoc::place_piece(const coord position)
{
	if (chess_board[position.x][position.y] != 0)//��괦�Ƿ������
		return;
	chess_board[position.x][position.y] = thisflag;
	for (auto i = free_grids.begin(); i != free_grids.end(); ++i)
		if (*i == position)
		{
			free_grids.erase(i);
			break;
		}
	draw();
	//���Ӻ�ʼ�ж���Ϸ״��
	if (judger(thisflag) == 1)//�����ʤ������
	{
		if (computer_flag != 0)
			if (thisflag == computer_flag)//�Ƿ��ǵ��Ի�ʤ
				printf("\033[41mYou Lose!\033[0m\nPress \033[33mEnter\033[0m to back to the MENU...");
			else
				printf("\033[30;43mYou WIN!\033[0m\nPress \033[33mEnter\033[0m to back to the MENU...");
		else
			printf("\033[30;43m%dP WIN!\033[0m\nPress \033[33mEnter\033[0m to back to the MENU...", thisflag);
		cin.get();
		restart();//������Ϸ
		running = false;
		menu();//�ص��˵�
		return;
	}
	else if (judger(thisflag) == -1)//������塣����
	{
		printf("\033[42mThe two sides draw!\033[0m\nPress \033[33mEnter\033[0m to back to the MENU...");
		cin.get();
		restart();
		running = false;
		menu();
		return;
	}
	thisflag = (thisflag == 1) ? 2 : 1;//��thisflag��Ϊ��һ���
	draw();//ˢ�»غ���ʾ
}
//���У������޷���������ʾ�����ӵ���ң�����-1��ʾ���壬1��ʾ��ʤ,0��ʾ���¼�
int tictactoc::judger(const size_t player)const
{
	for (size_t x = 0; x != 3; ++x)//���к���3���Ƿ����3����
	{
		for (size_t y = 0; y != 3; ++y)
			if (chess_board[x][y] != player)
				break;
			else if (y == 2)
				return 1;
	}
	for (size_t y = 0; y != 3; ++y)//��������3���Ƿ����3����
	{
		for (size_t x = 0; x != 3; ++x)
			if (chess_board[x][y] != player)
				break;
			else if (x == 2)
				return 1;
	}
	if (chess_board[0][0] == player && chess_board[1][1] == player && chess_board[2][2] == player)//б�Խǡ�����
		return 1;
	if (chess_board[0][2] == player && chess_board[1][1] == player && chess_board[2][0] == player)//��б�Խǡ�����
		return 1;
	if (free_grids.size() == 0)//�����Ƿ������������������
		return -1;
	return 0;
}
//�������壬����Ҫ���ӵ�����
coord tictactoc::computer_play(void)const
{
	size_t counter = 0;
	int other_flag = (thisflag == 1) ? 2 : 1;//��¼�ǵ�����ҵĻغ�˳��

	//���ȿ�����ֱ�ӻ�ʤ�����
	for (size_t x = 0; x != 3; ++x)//���к��Ŵ���������+һ�ո�����ո�
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
	for (size_t y = 0; y != 3; ++y)//�������Ŵ���������+һ�ո�����ո�
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
	//б�Խǡ�����
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
	//��б�Խǡ�����
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

	//�����ֹ�Է�ʤ��
	for (size_t x = 0; x != 3; ++x)//���к��Ŵ���������+һ�ո�����ո�
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
	for (size_t y = 0; y != 3; ++y)//�������Ŵ���������+һ�ո�����ո�
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
	//б�Խǡ�����
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
	//��б�Խǡ�����
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

	//��������������+һ�ո������ѡ��ո�������
	srand((unsigned)time(NULL));
	return free_grids[rand() % free_grids.size()];
}