#pragma once
#include <wchar.h>
#include <iostream>
#include "table.h"

#ifndef MAX_NAME_FIGURE
#define MAX_NAME_FIGURE 15
#endif

class entity
{
private: wchar_t* _name;
//����
private: int _score;
//������������� ���������� bool
public: bool isHandleMouse;

//����� ���
public: wchar_t* get_name() const;
//����� ����
public: int get_score() const;
//�������� ����
public: void add_score(const int val);
//��������� ����
public: void set_score(const int val);
//���� ����������
public: virtual bool handle();

public:
	entity();
	entity(const wchar_t *name);
	virtual ~entity();
};

