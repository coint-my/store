#pragma once
#include "figure.h"
#include "player.h"

//��������� ������� class renderer
class renderer
{
	//���������� ����
public: static void draw_polygon(const data_figure& fig);
public: static void draw_Rect(const Rectangle& rec, const Color& col);
//����� ������ ��������
public: static void ShowString(const wchar_t *_string, const int _x, const int _y);
//����� ������ �����
public: static void ShowString(int _intejer, const int _x, const int _y);
public:
	renderer();
	~renderer();
};

