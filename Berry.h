#pragma once
class Berry
{
private: 
	int x, y;
public:
	Berry(void);
	int GetX();
	int GetY();
	void Draw(HDC hdc);
	~Berry(void);
};

