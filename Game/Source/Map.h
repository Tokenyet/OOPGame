/*#include "ILocation.h"
#include "gamelib.h"
class CMovingBitmap;
class Map : public ILocation
{
private:
	int movX,movY;
	int windows_Width,windows_Heigth;
	CMovingBitmap *picture;
public:
	Map();
	~Map();
	void Initialize(int width,int heigth,char* path);
	void SetScreenSize(int width,int height);
	int &GetX();
	int &GetY();
	void SetMapLocation(int x,int y);
	bool CheckWidthOutOfWindowsLeft();
	bool CheckWidthOnLeftBorder();
	bool CheckWidthOutOfWindowsRight(); //�H�����������a�Ϥ��P�_�k
	void OnShow();
	void OnMove();
	void LoadMap(char *);//LoadBitmap
	int GetWidth();
	int GetHeight();
};*/