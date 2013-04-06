#include "StdAfx.h"
#include "Snake.h"


Snake::Snake(void)
{
	direction = LEFT;
	block = false;
}

Snake::Snake(int y)
{
	direction = LEFT;
	block = false;
	this->y = y;
	POINT p;
	p.x = 999;
	p.y = y;
	turns.push_back(p);
}

Snake::Snake(int length, int y)
{	
	POINT p;
	p.x = rand() % 300 + 100;
	p.y = -(rand() % 300) - 100;
	turns.push_back(p);
	for(int i = 0; i < length; i++)
	{
		p.x = p.x - 5;
		turns.push_back(p);
	}
	direction = LEFT;
	block = false;
	this->y = y;
}

int Snake::GetY()
{
	return y;
}

bool Snake::Empty()
{
	if(turns.size() == 0) return true;
	else return false;
}

void Snake::Draw(HDC hdc)
{
	if(turns.size() == 0) return;
	SetMapMode(hdc, MM_LOMETRIC);
	MoveToEx(hdc, turns[0].x, turns[0].y, NULL);
	for(unsigned int i = 1; i < turns.size(); i++) LineTo(hdc, turns[i].x, turns[i].y);
}

bool Snake::Move()
{
	if(turns.size() == 0)
	{
		block = false;
		return true;
	}
	for(unsigned int i = 0 ; i < turns.size()-1; i++) 
	{
		if(turns[i].y - turns[i+1].y <= 5)
		{
			turns[i].x = turns[i+1].x; 
			turns[i].y = turns[i+1].y; 
		}
	}
	switch(direction)
	{
		case UP:	if(turns[turns.size()-1].y > 0) return false;
					turns[turns.size()-1].y += 5;
					break;
		case RIGHT:	if(turns[turns.size()-1].x >= 1000) 
					{
						block = true;
						PostMessage(HWND_BROADCAST, GORIGHT, turns[turns.size()-1].y, NULL);
						turns.pop_back();
						break;
					}
					turns[turns.size()-1].x += 5;
					break;
		case DOWN:	if(turns[turns.size()-1].y < -1000) return false;
					turns[turns.size()-1].y -= 5;
					break;
		case LEFT:	if(turns[turns.size()-1].x < 0) return false;
					turns[turns.size()-1].x -= 5;
					break;
	}
	return true;
}

void Snake::Turn(int dir)
{
	if(block) return;
	switch(dir)
	{
	case LEFT:
		direction = (direction + 3) % 4;
		break;
	case RIGHT:
		direction = (direction+1) % 4;
		break;
	default:
		break;
	}
}

void Snake::Add(int y)
{
	POINT p;
	it = turns.begin();
	p.x = 999;
	p.y = y;
	turns.insert(it, p);
}

void Snake::SetDirection(int dir)
{
	if(turns.size() == 1)  direction = dir;
}

Snake::~Snake(void)
{
}
