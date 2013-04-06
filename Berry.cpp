#include "StdAfx.h"
#include "Berry.h"


Berry::Berry(void)
{
	x = rand() % 1000;
	y = -(rand() % 1000);
}

int Berry::GetX()
{
	return x;
}

int Berry::GetY()
{
	return y;
}

void Berry::Draw(HDC hdc)
{
	SetMapMode(hdc, MM_LOMETRIC);
	Rectangle(hdc, x-5, y+5, x+5, y-5);
	SetPolyFillMode(hdc, WINDING);
}

Berry::~Berry(void)
{
}
