#pragma once
#include <vector>
#include "WinApi.h"
#include <string>
#include "Berry.h"

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
	int y;
public:
	Snake(void);
	Snake(int y);
	Snake(int length, int y);
	int GetY();
	bool Empty();
	void Turn(int dir);
	void Draw(HDC hdc);
	bool Move();
	void Add(int y);
	void SetDirection(int dir);
	~Snake(void);
};

