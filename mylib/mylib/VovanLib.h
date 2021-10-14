#ifndef VOVANLIB_H
#define VOVANLIB_H
namespace vovan
{
	#define expd __declspec(dllexport)
	#define PI 3.14159

	struct Vector2i
	{
		int x, y;
		expd Vector2i() : x(0), y(0) { }
		expd Vector2i(const int _x, const int _y) : x(_x), y(_y) { }
		expd Vector2i(const Vector2i &_v) : x(_v.x), y(_v.y) { }
	};

	struct Vector2f
	{
		float x, y;
		expd Vector2f() : x(0), y(0) { }
		expd Vector2f(const float _x, const float _y) : x(_x), y(_y) { }
		expd Vector2f(const Vector2f &_v) : x(_v.x), y(_v.y) { }
	};
	//�������� ���� ����� RGBA
	//(0 - 255)
	struct Color
	{
		short r, g, b, a;
		expd Color() : r(255), g(255), b(255), a(0) { }
		expd Color(short _r, short _g, short _b) : r(_r), g(_g), b(_b), a(0) { }
		expd Color(short _r, short _g, short _b, short _a) : r(_r), g(_g), b(_b), a(_a) { }
		expd bool operator==(Color &_col);
		expd bool operator!=(Color &_col);
	};

	class Recti
	{
	private:
		int wid, hei;
		Vector2i pos;
	public:
		//����������� �����������
		expd Recti() : pos(0, 0), wid(5), hei(5) { }
		//����������� � �����������
		expd Recti(Vector2i &_pos, int _wid, int _hei) : pos(_pos.x, _pos.y), wid(_wid), hei(_hei) { }
		//����������� �����������
		expd Recti(const Recti &_r) : pos(_r.pos), wid(_r.wid), hei(_r.hei) { }
		//���������������� �������������
		expd void Initialize(const Recti &_rect) { pos = _rect.pos; wid = _rect.wid; hei = _rect.hei; }
		//�������� ������
		expd int GetWid() { return wid; }
		//�������� ������
		expd int GetHei() { return hei; }
		//�������� ������� ������2
		expd Vector2i GetVect() { return this->pos; }
		//�������� �������������
		void Offset(Vector2i &_p) { pos.x += _p.x; pos.y += _p.y; }
		//�������� ����������� ���������������
		expd bool Intersect(Recti &_rect);
		//������ ����� ��������������
		int Right() { return pos.x + wid; }
		//����� ����� ��������������
		int Left() { return pos.x; }
		//������� ����� ��������������
		int Top() { return pos.y; }
		//������ ����� ��������������
		int Bottom() { return pos.y + hei; }
		//�������� ������������
		expd const Recti &operator=(const Recti &_r);
	};

	class Rectf
	{
	private:
		float wid, hei;
		Vector2f pos;
	public:
		//����������� �����������
		expd Rectf() : pos(0, 0), wid(5), hei(5) { }
		//����������� � �����������
		expd Rectf(Vector2f &_pos, float _wid, float _hei) : pos(_pos.x, _pos.y), wid(_wid), hei(_hei) { }
		//����������� �����������
		expd Rectf(const Rectf &_r) : pos(_r.pos), wid(_r.wid), hei(_r.hei) { }
		//���������������� �������������
		expd void Initialize(const Rectf &_rect) { pos = _rect.pos; wid = _rect.wid; hei = _rect.hei; }
		//�������� ������
		expd float GetWid() { return wid; }
		//�������� ������
		expd float GetHei() { return hei; }
		//�������� ������� ������2
		expd Vector2f GetVect() { return this->pos; }
		//�������� �������������
		void Offset(Vector2f &_p) { pos.x += _p.x; pos.y += _p.y; }
		//�������� ����������� ���������������
		expd bool Intersect(Rectf &_rect);
		//������ ����� ��������������
		float Right() { return pos.x + wid; }
		//����� ����� ��������������
		float Left() { return pos.x; }
		//������� ����� ��������������
		float Top() { return pos.y; }
		//������ ����� ��������������
		float Bottom() { return pos.y + hei; }
		//�������� ������������
		//expd const Rectf &operator=(const Rectf &_r);
	};

	class Circlef
	{
	private:
		Vector2f pos;
		int rad;
		int seg;
	public:
		//����������� �����������
		expd Circlef() : rad(1), seg(4) {}
		//����������� � �����������
		expd Circlef(Vector2f &_pos, const int _rad, int _seg) : pos(_pos.x, _pos.y), rad(_rad), seg(_seg) { }
		//����������� �����������
		expd Circlef(const Circlef &_c) : pos(_c.pos), rad(_c.rad), seg(_c.seg) { }
		//�������� ������
		void Offset(const Vector2f &_pos) { pos.x += _pos.x; pos.y += _pos.y; }
		//������������� �������
		expd void Init(const Vector2f &_pos, const int _rad, const int _seg);
		//�������� ������
		int GetRad() { return rad; }
		//�������� ������� ���������
		int GetSegment() { return seg; }
		//�������� �������
		Vector2f GetPos() { return pos; }
	};
}
#endif