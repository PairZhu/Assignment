#pragma once
#ifndef _tictactoc_
#define _tictactoc_

#include<vector>
#include<windows.h>
#include<iostream>
#include<conio.h>
#include<time.h>
using namespace std;
class coord
{
public:
	size_t x = 0, y = 0;
	coord(size_t _x, size_t _y) :x(_x), y(_y) {}
	bool operator== (const coord& coord1)
	{
		return (x == coord1.x && y == coord1.y);
	}
};
class tictactoc
{
//数据成员
private:
	vector<coord> free_grids;//记录空格子
	int chess_board[3][3] = {};//记录棋局
public:
	int computer_flag = 0;//记录电脑回合位置，特别的，0代表无电脑玩家
	int thisflag = 1;//记录当前是谁的回合
	bool running = false;//记录游戏是否已开始
	coord cursor_position = coord(0, 0);//记录当前光标位置

//成员函数
private:
	void draw_menu(const size_t)const;
	int judger(const size_t)const;
public:
	void menu(void);
	void draw(void)const;
	void restart(void);
	void place_piece(const coord);
	coord computer_play(void)const;
};
//函数的注释在源文件内
#endif