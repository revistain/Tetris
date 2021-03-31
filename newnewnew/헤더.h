#pragma once
#define WIDTH 20
typedef struct Block
{
	int ENDGAME;

	int arr[4];
	int X, Y;
	int destroy;
	int stop;
	int stop_where;
	int stop_whereP[3];
	int rgn;
	int KBHIT;
	int KBlock;
	int Time;

	int RoCon;
	int RoCheck;
	int ForRo;
	int Plus[2];	//0 RIGHT 1 RIGHT2
	int Fplus[2];
	int plus_much; //1 RIGHT 2 RIGHT2

	int colli[4][3];
	int location[3];
	int Flocation[3];



	int stone1[4];

	int stick1[4];
	int stick2[4];

	int mount1[4];
	int mount2[4];
	int mount3[4];
	int mount4[4];

	int notgi1[4];
	int notgi2[4];
	int notgi3[4];
	int notgi4[4];

	int gi1[4];
	int gi2[4];
	int gi3[4];
	int gi4[4];
}Block;





Block* RandomGenerate(Block* Broken_ptr);
void GameOver(Block* Bptr, int(*Warr)[WIDTH]);
void StartScreen();
void DrawBox();
void SetBox(Block* ptr, int(*Warr)[WIDTH]);
void gotoxy(int x, int y);
void DrawBox();
void TimeLapse(Block* Bptr);
void MoveDown(Block* Bptr);
void MoveLeft(Block* Bptr);
void MoveRight(Block* Bptr);
void Visualize(Block* Bptr, int(*arr)[WIDTH]);
void CopyInt(int* ptr1, int* ptr2, int length);
void CursorView(char show);
void ClearScreen();
int KBhit(Block* Bptr, int(*Warr)[WIDTH]);
void StopBlock(Block* Bptr, int(*Warr)[WIDTH]);
void ClearScreen();
void Collision(Block* Bptr, int(*Warr)[WIDTH]);
void Rotate(Block* ptr);
int Eraser(Block* Bptr, int(*Warr)[WIDTH]);
void LineClear(Block* Bptr, int(*Warr)[WIDTH]);
void InstantDown(Block* Bptr, int(*Warr)[WIDTH]);
//void InstantDown(Block* Bptr, int(*Warr)[WIDTH]);
