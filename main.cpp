#include"TicTacToc.h"
using namespace std;
int main()
{
	tictactoc game;
	game.restart();//初始化游戏
	game.menu();//进入菜单页
	//开始监听键盘
	while (true) {
		if (game.running && game.thisflag==game.computer_flag)//如果游戏未结束且是电脑玩家回合则电脑下棋
			game.place_piece(game.computer_play());//电脑玩家落子
		if (!_kbhit())//如果有键被按下则返回真，否则返回假
			continue;
		switch (_getch())//判断键值
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
			game.menu();//返回菜单
			break;
		case 13://Enter
			game.place_piece(game.cursor_position);//在光标处落子
			break;
		}
	}
	return 0;
}