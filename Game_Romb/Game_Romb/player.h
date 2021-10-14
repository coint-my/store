#pragma once
#include "entity.h"
#include "table.h"

typedef enum { NONE, CHEK1, CHEK2};

//����� ��������������
class Rectangle
{
private: float _x, _y, _wid, _hei;

public: inline float get_x() const { return _x; }
public: inline float get_y() const { return _y; }
public: inline float get_wid() const { return _wid; }
public: inline float get_hei() const { return _hei; }
public: inline float get_center_x() const { return _x + _wid / 2; }
public: inline float get_center_y() const { return _y + _hei / 2; }
public: inline float right() const { return _x + _wid; }
public: inline float bottom() const { return _y + _hei; }

public: inline void set_center(const float x, const float y) { _x = (x - _wid / 2); _y = (y - _hei / 2); }
public: inline void set_xy(const float x, const float y) { _x = x; _y = y; }
public: inline void offset(const float x, const float y) { _x += x; _y += y; }

public: static bool intersect(const Rectangle& r1, const Rectangle& _r2);

public: Rectangle() : _x(0), _y(0), _wid(1), _hei(1) {}
public: Rectangle(const float x, const float y, const float wid, const float hei) : _x(x), _y(y), _wid(wid), _hei(hei) {}
	~Rectangle() {}
};

//��������� ������ ������
typedef struct p_buff
{
	bool is_player;
	bool is_fin;
	int is_chek;
	int find_x, find_y;
	int bind_x, bind_y;

	Rectangle rec_1;
	Rectangle rec_2;

	p_buff() : is_player(false), is_chek(CHEK1), find_x(0), find_y(0), bind_x(0), bind_y(0), is_fin(false) {}
	~p_buff(void) {}
};

//���������� �������
static int number_player = 1;

class player :	public entity
{
//���������� �������
private: bool isHandle;
//������� ����
private: table* _table;
//������ �����������
private: data_figure *fig;
private: data_figure *fig2;
//������� �����
private: p_buff buff;

//������������ ����� ����������
private: int pl;
private: int en;

private: Rectangle rect[DESC_W][DESC_H];
private: bool isRect[DESC_W][DESC_H];
private: void set_init_br();
private: void draw_br();

public: void up_sec();
//����� ������ ����������
public: bool handle();
//���������� ������
public: void mouse(int button, int state, int x, int y);
//���������� ������������ ������
public: void moution_mouse(int x, int y);
//�������� �� ���������� ������ ����������� ����� � ������ ������
public: void get_sqrt(int xx, int yy);
//����������� ������ � ����� (�) � ����� (�)
public: bool run_figure();
//��������� ���������� ������ ���� �����
public: static double p_sqrt(const Position& p1, const Position& p2);
//�������� �� ����������� ��������������
public: void get_intersect(int xx, int yy);
//�������� ������ � bool ����������
private: void reset();
//������� �������� ������
public: void resetActive();

public:
	player();
	player(table& t, int pla, int ene, const wchar_t* _nam);
	~player();
};

