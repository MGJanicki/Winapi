#pragma once
#include <vector>
#include "WinApi.h"
#include <string>

using namespace std;

enum {UP, RIGHT, DOWN, LEFT};
const UINT GOLEFT = RegisterWindowMessage("goleft");
const UINT GORIGHT = RegisterWindowMessage("goright");

class Snake
{
	vector<POINT> turns;
	vector<POINT>::iterator it;
	int direction;
	bool block;
public:
	Snake(void);
	void Turn(int dir);
	void Draw(HDC hdc);
	bool Move();
	void Add(int y);
	void SetDirection(int dir);
	~Snake(void);
};

