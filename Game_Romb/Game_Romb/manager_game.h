#pragma once
#include "table.h"
#include "player.h"
#include "enemy.h"
#include "Menu.h"

typedef enum {PL1, PL2, GAME_OVER, GAME_MENU};

typedef struct gameBuffer
{
	int round;
	bool isActive;
	int count;

	gameBuffer() : round(GAME_MENU), isActive(true), count(0) {}

}game_buff;

class manager_game
{
//����
private: Menu men;
//��������� ����
private: int state_menu;
//������� ������
private: int _counter;
//������� ����
private: table *_table;
//����� ����������
private: enemy* _enemy;
private: enemy* _enemy2;
//����� ������
private: entity *_player;
private: entity *_player2;
//����� ������ ��������
private: player * _p;
private: player * _p2;

//����� �������� ��������
private: gameBuffer g_buff;

//����� ���������
public: void render();
//������ ����� ���� ������ ���
public: void update();
//���������� ������
public: void up_second();
//���������� ������
public: void mouse(int b, int s, int x, int y);
//���������� ����������� �����
public: void m_mouse(int x, int y);
//������� �����
private: void calculate_score(const int _tupe_figure, int& score);
//������������� ������� ����� � ���������
private: void player_vs_comp();
//������������� ������� ����� � �����
private: void player_vs_player();
//������������� ������� ��������� � ���������
private: void comp_vs_comp();

private: bool Is_OVER();

public:
	manager_game();
	~manager_game();
};

