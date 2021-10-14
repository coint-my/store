#ifndef H_GRAPHIC_H
#define H_GRAPHIC_H

#include <gl/glut.h>
#include <cmath>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")

namespace graphic
{
	#define exp __declspec(dllexport)
	#define PI 3.14159

	struct Vector2i
	{
		int x, y;
		exp Vector2i() : x(0), y(0) { }
		exp Vector2i(int _x, int _y) : x(_x), y(_y) { }
	};

	struct Vector2f
	{
		float x, y;
		exp Vector2f() : x(0), y(0) { }
		exp Vector2f(float _x, float _y) : x(_x), y(_y) { }
	};

	struct Color
	{
		short r, g, b, a;
		exp Color() : r(255), g(255), b(255), a(0) { }
		exp Color(short _r, short _g, short _b) : r(_r), g(_g), b(_b), a(0) { }
		exp Color(short _r, short _g, short _b, short _a) : r(_r), g(_g), b(_b), a(_a) { }
	};

	class Recti
	{
	private:
		int wid, hei;
		Vector2i pos;
	public:
		//����������� �����������
		exp Recti() : pos(0, 0), wid(5), hei(5) { }
		//����������� � �����������
		exp Recti(Vector2i &_pos, int _wid, int _hei) : pos(_pos.x, _pos.y), wid(_wid), hei(_hei) { }
		//�������� X
		exp int GetX() { return pos.x; }
		//�������� Y
		exp int GetY() { return pos.y; }
		//�������� ������
		exp int GetWid() { return wid; }
		//�������� ������
		exp int GetHei() { return hei; }
		//�������� ������2
		exp Vector2i GetVect() { return this->pos; }
		//�������� �������������
		exp void Offset(Vector2i &_p) { pos.x += _p.x; pos.y += _p.y; }
		//�������� ����������� ���������������
		exp bool Intersect(Recti &_rect);
		//������ ����� ��������������
		exp int Right() { return pos.x + wid; }
		//����� ����� ��������������
		exp int Left() { return pos.x; }
		//������� ����� ��������������
		exp int Top() { return pos.y; }
		//������ ����� ��������������
		exp int Bottom() { return pos.y + hei; }
		//�������� ������������
		exp const Recti &operator=(const Recti &_r);
	};

	class Circlef
	{
	private:
		Vector2f pos;
		int rad;
		int seg;
	public:
		//����������� �����������
		Circlef() : rad(1), seg(4) {}
		//����������� � �����������
		Circlef(Vector2f &_pos, const int _rad, int _seg) : pos(_pos.x, _pos.y), rad(_rad), seg(_seg) { }
		//�������� ������
		void Offset(const Vector2f &_pos) { pos.x += _pos.x; pos.y += _pos.y; }
		//������������� �������
		exp void Init(const Vector2f &_pos, const int _rad, const int _seg);
		//�������� ������
		int GetRad() { return rad; }
		//�������� ������� ���������
		int GetSegment() { return seg; }
		//�������� �������
		Vector2f GetPos() { return pos; }
	};

	class Painter
	{
	public:
		//���������� �������
		static exp void InitUpdate(int _time, void(*update)(int _t));
		//����������� ������� ���������
		static exp void ReDraw(int _time, void (*update)(int _t));
		//���������������� ����������� ����
		static exp void Initialize2D(int _wid, int _hei, int &_argc, char** _argv, char* _nameWindow, void(*render)(), void(*mouse)(int _b, int _s, int _x, int _y));
		//���������� �������������
		static exp void DrawRect(Recti &_r, Color &_c);
		//���������� ����
		static exp void DrawCircle(Circlef &_circl, Color &_c);
		//������ ��������
		static exp void Start();
		//��������� ��������
		static exp void End();
	};
}
#endif