#pragma once
#include "EngineBase.h"

class Player
{
private:
	float dir;
	const float speed;
	Translation pos;
public:
	Player(void);
	~Player(void);

	Translation GetPos() const { return pos; } //������� ������

	float GetRot() const { return dir; } //����� �����������

	void SetPos(const Translation &_pos); //������ �������
	void SetDir(const float _newDir, const float _speed); //������ �����������

	void Keyboard(unsigned char _button, int _x, int _y); //��������� ������
};

