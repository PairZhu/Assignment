#include"TicTacToc.h"
using namespace std;
int main()
{
	tictactoc game;
	game.restart();//��ʼ����Ϸ
	game.menu();//����˵�ҳ
	//��ʼ��������
	while (true) {
		if (game.running && game.thisflag==game.computer_flag)//�����Ϸδ�������ǵ�����һغ����������
			game.place_piece(game.computer_play());//�����������
		if (!_kbhit())//����м��������򷵻��棬���򷵻ؼ�
			continue;
		switch (_getch())//�жϼ�ֵ
		{
		case 72://Up
			if (game.cursor_position.x > 0)
				--game.cursor_position.x;
			else
				game.cursor_position.x = 2;
			game.draw();
			break;
		case 80://Down
			if (game.cursor_position.x < 2)
				++game.cursor_position.x;
			else
				game.cursor_position.x = 0;
			game.draw();
			break;
		case 75://Left
			if (game.cursor_position.y > 0)
				--game.cursor_position.y;
			else
				game.cursor_position.y = 2;
			game.draw();
			break;
		case 77://Right
			if (game.cursor_position.y < 2)
				++game.cursor_position.y;
			else
				game.cursor_position.y = 0;
			game.draw();
			break;
		case 27://ESC
			game.menu();//���ز˵�
			break;
		case 13://Enter
			game.place_piece(game.cursor_position);//�ڹ�괦����
			break;
		}
	}
	return 0;
}