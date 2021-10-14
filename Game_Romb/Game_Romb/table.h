#pragma once
#include "figure.h"
#include "setting.h"

//������������ ��������� �����
enum { IMPOSIBLE = 1, POSIBLE, PLAYER, ENEMY, ACTIVE };

//������� ���� ����������
class table
{
private: int _field[DESC_W][DESC_H];
private: Position pos[DESC_W][DESC_H];
private: data_figure _data[MAX_STATE];

//���������� ����
public: void draw_field();
//������ ���� ��������
public: int get_field(const int x, const int y) const;
//��������� �����
public: const data_figure& get_figure(const int val) const;
//������ �������� ���� ��������
public: bool set_field(const int x, const int y, const int _val);
//����� ������� ������
public: const Position& get_pos(const int x, const int y) const;
//�������� ������� ����
public: void reset_pole();

public:
	table();
	~table();
};

