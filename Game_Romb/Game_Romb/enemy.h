#pragma once
#include "entity.h"
#include <vector>

class Rectangle;

typedef struct s_index
{
	int x, y;
	s_index() : x(0), y(0) {}
	s_index(int xx, int yy) : x(xx), y(yy) {}
	~s_index() {}
};

//��������� ������ �����
typedef struct best_ind
{
	int x1, y1, x2, y2;
	int value;
	bool isRang1;
	best_ind() : x1(0), y1(0), x2(0), y2(0), value(0), isRang1(true) {}
	best_ind(int _x1, int _y1, int _x2, int _y2, int _val, bool _isRang1) : x1(_x1), y1(_y1), x2(_x2), y2(_y2), value(_val), isRang1(_isRang1) {}
	~best_ind() {}
};

class enemy :	public entity
{
//������� ����
private: table* _table;
//������������ ����� ����������
private: int pl;
private: int en;
//������� ��� ���������
best_ind curr_turn;

//��������� ������
private: std::vector<s_index> init_ind;
//����� ���������� ��������� ����� 
private: std::vector<best_ind> list_vars;
//������ �����������
private: data_figure *fig;

//������������� ��������� ������
private: void init();
//������������� ����� ����� 1
private: void init_rang1(const int xx, const int yy, std::vector<best_ind>& _list);
//������������� ����� ����� 2
private: void init_rang2(const int xx, const int yy, std::vector<best_ind>& _list);
private: inline const Rectangle& get_r1(const int xx, const int yy) const;
private: inline const Rectangle& get_r1(const int xx, const int yy, const int _size) const;
private: const best_ind& get_best_var() const;
private: const best_ind& empty_turn() const;
//����������� ������ � ����� (�) � ����� (�)
private: bool run_figure();
//���������� �����������
public: bool isHandle;

public: bool handle();
public:
	enemy(table &_t, int pla, int ene, const wchar_t* _nam);
	~enemy();
};

