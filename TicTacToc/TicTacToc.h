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
//���ݳ�Ա
private:
	vector<coord> free_grids;//��¼�ո���
	int chess_board[3][3] = {};//��¼���
public:
	int computer_flag = 0;//��¼���Իغ�λ�ã��ر�ģ�0�����޵������
	int thisflag = 1;//��¼��ǰ��˭�Ļغ�
	bool running = false;//��¼��Ϸ�Ƿ��ѿ�ʼ
	coord cursor_position = coord(0, 0);//��¼��ǰ���λ��

//��Ա����
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
//������ע����Դ�ļ���
#endif