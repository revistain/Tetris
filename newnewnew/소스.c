#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "헤더.h"
#include <Windows.h>
#include <wchar.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#define WIDTH 20
enum Direction {
	LEFT, RIGHT, DOWN, MIDDLE, RIGHT2, ROTATE, RIGHT3
};

int main()
{

	CursorView(0);	//커서 숨기기
	system("mode con cols=130 lines=50 | title Tetris");
	StartScreen();
	PlaySound(L"C:\\Users\\pc\\source\\repos\\newnewnew\\tett.wav", NULL, SND_ASYNC | SND_LOOP);

	system("mode con cols=47 lines=50 | title Tetris");

	int score = 0;
	int time = 0;
	int a = 200;
	int TIMEC = 0;


	int arr[WIDTH*2][WIDTH] = {0,};	//게임의 판

	Block* new_ptr;

	gotoxy(3, 46);
	printf("[너의 점수]: %d점         [제작자: 정우김]", score);

	while (1)
	{
		new_ptr = (int*)malloc(sizeof(Block));
		new_ptr = RandomGenerate(new_ptr);
		new_ptr->Time = a;

		SetBox(new_ptr, arr);	//기본 데이터 설정
		TimeLapse(new_ptr, arr);	//사실상 메인
		if (Eraser(new_ptr, arr))
		{
			score += 100;
			gotoxy(3, 46);
			printf("[너의 점수] : %d점", score);
			new_ptr->Time = a / ((score / 100) * 1.1);
		}
		Eraser(new_ptr, arr);
		if (new_ptr->ENDGAME)
			break;
		free(new_ptr);
	}

	system("cls");
	gotoxy(18, 24);
	PlaySound(NULL, 0, 0);
	printf("[GAME OVER]");
	Sleep(2000);

	for (int i = 0; i < 50; i++)
		printf("\n");
	return 0;
}

void StartScreen()
{

	gotoxy(1, 1);
	printf("┌");

	for (int i = 0; i < WIDTH * 6 + 3; i++)
	{
		printf("─");
	}
	printf("┐");

	gotoxy(1, WIDTH * 2 + 7);
	printf("└");
	for (int i = 0; i < WIDTH * 6 + 3; i++)
	{
		printf("─");
	}
	printf("┘");

	for (int i = 0; i < WIDTH * 2 + 5; i++)
	{
		gotoxy(1, i + 2);
		printf("│");
		gotoxy(WIDTH * 6 + 2 + 3, i + 2);
		printf("│");
	}

	char start;
	int x = 10;
	gotoxy(x, 15);
	printf("■■■■■■■■                                      ■■■■■■■■■■■\n");
	gotoxy(x, 16);
	printf("          ■                                                        ■                 ■\n");
	gotoxy(x, 17);
	printf("          ■                                                        ■\n");
	gotoxy(x, 18);
	printf("          ■     ■        ■      ■  ■■■■       ■■          ■      ■    ■   ■      ■■■■■\n");
	gotoxy(x, 19);
	printf("          ■     ■        ■      ■■      ■     ■    ■        ■      ■  ■     ■    ■\n");
	gotoxy(x, 20);
	printf("          ■     ■        ■      ■        ■    ■      ■       ■      ■ ■      ■    ■\n");
	gotoxy(x, 21);
	printf("  ■	    ■     ■        ■      ■        ■    ■      ■       ■      ■■       ■    ■■■■■■\n");
	gotoxy(x, 22);
	printf("   ■     ■     ■        ■      ■        ■    ■      ■       ■      ■         ■                ■\n");
	gotoxy(x, 23);
	printf("    ■■■■      ■■■■■■     ■        ■      ■■■■       ■      ■         ■    ■■■■■■■\n");
	gotoxy(x, 24);
	printf("                                                           ■\n");
	gotoxy(x, 25);
	printf("                                                           ■\n");
	gotoxy(x, 26);
	printf("                                                           ■\n");
	gotoxy(x, 27);
	printf("                                        ■■■■■■■■■■\n");

	
	printf("\n\n\n │           [아무키나 눌러서 시작하시오....]                                              ※ W,A,S,D로 조작");
	printf("\n\n\n │           [제작 김정우]                                                                 ※ S: 수직 하강");
	printf("\n\n\n │           [기획 김정우]                                                                 ※ W: 점진적 하강");
	printf("\n\n\n │           [v2.1]                                                                        ※ SPACEBAR: 회전");


	/*	while (1) {
			Beep(493.8833, 500);
			Beep(65, 13);
			Beep(369.9944, 250);
			Beep(65, 13);
			Beep(391.9954, 250);
			Beep(65, 13);
			Beep(440, 500);
			Beep(65, 13);
			Beep(391.9954, 250);
			Beep(65, 13);
			Beep(369.9944, 250);
			Beep(65, 13);
			Beep(65, 13);
			Beep(329.6276, 550);
			Beep(65, 13);
			Beep(329.6276, 250);
			Beep(65, 13);
			Beep(391.9954, 250);
			Beep(493.8833, 550);
			Beep(440, 250);
			Beep(391.9954, 250);
			Beep(369.9944, 550);
			Beep(369.9944, 250);
			Beep(391.9954, 250);
			Beep(440, 500);
			Beep(493.8833, 500);
			Beep(391.9954, 500);
			Beep(329.6276, 700);
			Beep(65, 13);
			Sleep(50);
			Beep(65, 13);
			Sleep(50);
			Beep(65, 13);
			Sleep(50);
			Beep(65, 13);
			Sleep(50);
			Beep(65, 13);
			Sleep(50);
			Beep(65, 13);
			Sleep(50);
			Beep(65, 13);
			Sleep(50);
			Beep(65, 13);
			Sleep(50);
			Beep(65, 13);
			Sleep(50);
			Beep(65, 13);
			Sleep(50);
			Beep(440, 500);
			Beep(440, 300);
			Beep(523.2511, 250);
			Beep(659.2551, 500);
			Beep(587.3295, 250);
			Beep(523.2511, 250);
			Beep(493.8833, 500);
			Beep(493.8833, 250);
			Beep(391.9954, 250);
			Beep(493.8833, 500);
			Beep(440, 300);
			Beep(391.9954, 250);
			Beep(369.9944, 500);
			Beep(369.9944, 250);
			Beep(391.9954, 250);
			Beep(440, 500);
			Beep(493.8833, 500);
			Beep(391.9954, 500);
			Beep(329.6276, 600);
			Sleep(1000);
			break;
		}*/
	
	while (1) {
		if (_kbhit())
		{
			break;
		}
	}
}

Block* RandomGenerate(Block* ptr)//두번째 이상부터 가능한 함수(파괴된 블록의 포인터 받음)
{
	int rgn1;
	rgn1 = rand() % 4;	//랜덤 생성 숫자 (0~4)
	ptr->rgn = rgn1;//rgn
	return ptr;
}

void CursorView(char show)//커서숨기기
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void Rotate(Block* ptr, int(*Warr)[WIDTH])
{
	int Tarr[4];
	int a = ptr->rgn;
	ptr->ForRo = 0;

	switch (a) {
		//stone = 회전 X

	case 1:
		if (ptr->RoCon == 0)
		{

			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->mount1[i] + ptr->mount2[i];
				CopyInt(ptr->arr, Tarr, 4);
			}

		}
		else if (ptr->RoCon == 1)
		{

			for (int i = 0; i < 4; i++)
			{

				Tarr[i] = ptr->arr[i] - ptr->mount2[i] + ptr->mount3[i];
				CopyInt(ptr->arr, Tarr, 4);
			}
		}
		else if (ptr->RoCon == 2)
		{

			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->mount3[i] + ptr->mount4[i];
				CopyInt(ptr->arr, Tarr, 4);
			}
		}
		else if (ptr->RoCon == 3)
		{

			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->mount4[i] + ptr->mount1[i];
				CopyInt(ptr->arr, Tarr, 4);
			}
			ptr->RoCon = 10;
		}
		break;
	case 2:
		if (ptr->RoCon == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->stick1[i] + ptr->stick2[i];
				CopyInt(ptr->arr, Tarr, 4);
			}



		}
		else if (ptr->RoCon == 1)
		{
			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->stick2[i] + ptr->stick1[i];
				CopyInt(ptr->arr, Tarr, 4);
			}
			ptr->RoCon = 10;
		}

		break;

	case 3:
		if (ptr->RoCon == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->notgi1[i] + ptr->notgi2[i];
				CopyInt(ptr->arr, Tarr, 4);
			}
		}
		else if (ptr->RoCon == 1)
		{
			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->notgi2[i] + ptr->notgi3[i];
				CopyInt(ptr->arr, Tarr, 4);
			}
		}
		else if (ptr->RoCon == 2)
		{
			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->notgi3[i] + ptr->notgi4[i];
				CopyInt(ptr->arr, Tarr, 4);
			}
		}
		else if (ptr->RoCon == 3)
		{
			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->notgi4[i] + ptr->notgi1[i];
				CopyInt(ptr->arr, Tarr, 4);
			}
			ptr->RoCon = 10;
		}

		break;

	case 4:
		if (ptr->RoCon == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->gi1[i] + ptr->gi2[i];
				CopyInt(ptr->arr, Tarr, 4);
			}
		}
		else if (ptr->RoCon == 1)
		{
			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->gi2[i] + ptr->gi3[i];
				CopyInt(ptr->arr, Tarr, 4);
			}
		}
		else if (ptr->RoCon == 2)
		{
			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->gi3[i] + ptr->gi4[i];
				CopyInt(ptr->arr, Tarr, 4);
			}
		}
		else if (ptr->RoCon == 3)
		{
			for (int i = 0; i < 4; i++)
			{
				Tarr[i] = ptr->arr[i] - ptr->gi3[i] + ptr->gi1[i];
				CopyInt(ptr->arr, Tarr, 4);
			}
			ptr->RoCon = 10;
		}
		break;

		}
		if (ptr->RoCon == 10) {
			ptr->RoCon = 0;
		}
		else {
			(ptr->RoCon)++;
		}
	
}


void SetBox(Block* ptr, int(*Warr)[WIDTH])
{
	ptr->destroy = 0;
	ptr->stop = 0;
	ptr->KBHIT = 0;
	ptr->stop = 0;
	ptr->stop_where = MIDDLE;
	ptr->RoCon = 0;
	ptr->ENDGAME = 0;


	int stone1[4] = { (WIDTH * 3 + 1 + 8),(WIDTH * 3 + 2 + 8),(WIDTH * 4 + 1 + 8),(WIDTH * 4 + 2 + 8) };

	int stick1[4] = { (WIDTH * 1 + 1 + 9),(WIDTH * 2 + 1 + 9),(WIDTH * 3 + 1 + 9),(WIDTH * 4 + 1 + 9) };
	int stick2[4] = { (WIDTH * 3 + 1 + 7),(WIDTH * 3 + 2 + 7),(WIDTH * 3 + 3 + 7),(WIDTH * 3 + 4 + 7) };

	int mount1[4] = { (WIDTH * 3 + 2 + 8),(WIDTH * 4 + 1 + 8),(WIDTH * 4 + 2 + 8),(WIDTH * 4 + 3 + 8) };
	int mount2[4] = { (WIDTH * 2 + 1 + 8),(WIDTH * 3 + 1 + 8),(WIDTH * 3 + 2 + 8),(WIDTH * 4 + 1 + 8) };
	int mount3[4] = { (WIDTH * 3 + 1 + 8),(WIDTH * 3 + 2 + 8),(WIDTH * 3 + 3 + 8),(WIDTH * 4 + 2 + 8) };
	int mount4[4] = { (WIDTH * 2 + 2 + 8),(WIDTH * 3 + 1 + 8),(WIDTH * 3 + 2 + 8),(WIDTH * 4 + 2 + 8) };

	int notgi1[4] = { (WIDTH * 3 + 3 + 8),(WIDTH * 4 + 1 + 8),(WIDTH * 4 + 2 + 8),(WIDTH * 4 + 3 + 8) };
	int notgi2[4] = { (WIDTH * 2 + 1 + 8),(WIDTH * 2 + 2 + 8),(WIDTH * 3 + 2 + 8),(WIDTH * 4 + 2 + 8) };
	int notgi3[4] = { (WIDTH * 3 + 1 + 8),(WIDTH * 3 + 2 + 8),(WIDTH * 3 + 3 + 8),(WIDTH * 4 + 1 + 8) };
	int notgi4[4] = { (WIDTH * 2 + 1 + 8),(WIDTH * 3 + 1 + 8),(WIDTH * 4 + 1 + 8),(WIDTH * 4 + 2 + 8) };

	int gi1[4] = { (WIDTH * 3 + 1 + 8),(WIDTH * 4 + 1 + 8),(WIDTH * 4 + 2 + 8),(WIDTH * 4 + 3 + 8) };
	int gi2[4] = { (WIDTH * 2 + 2 + 8),(WIDTH * 3 + 2 + 8),(WIDTH * 4 + 1 + 8),(WIDTH * 4 + 2 + 8) };
	int gi3[4] = { (WIDTH * 3 + 1 + 8),(WIDTH * 3 + 2 + 8),(WIDTH * 3 + 3 + 8),(WIDTH * 4 + 3 + 8) };
	int gi4[4] = { (WIDTH * 2 + 1 + 8),(WIDTH * 2 + 2 + 8),(WIDTH * 3 + 1 + 8),(WIDTH * 4 + 1 + 8) };


	CopyInt(ptr->stone1, stone1, 4);

	CopyInt(ptr->stick1, stick1, 4);
	CopyInt(ptr->stick2, stick2, 4);

	CopyInt(ptr->mount1, mount1, 4);
	CopyInt(ptr->mount2, mount2, 4);
	CopyInt(ptr->mount3, mount3, 4);
	CopyInt(ptr->mount4, mount4, 4);

	CopyInt(ptr->notgi1, notgi1, 4);
	CopyInt(ptr->notgi2, notgi2, 4);
	CopyInt(ptr->notgi3, notgi3, 4);
	CopyInt(ptr->notgi4, notgi4, 4);

	CopyInt(ptr->gi1, gi1, 4);
	CopyInt(ptr->gi2, gi2, 4);
	CopyInt(ptr->gi3, gi3, 4);
	CopyInt(ptr->gi4, gi4, 4);

	switch (ptr->rgn) {
	case 0:
		CopyInt(ptr->arr, stone1, 4);
		break;
	case 1:
		CopyInt(ptr->arr, mount1, 4);
		break;
	case 2:
		CopyInt(ptr->arr, stick1, 4);
		break;
	case 3:
		CopyInt(ptr->arr, notgi1, 4);
		break;
	case 4:
		CopyInt(ptr->arr, gi1, 4);
		break;
	}



	Collision(ptr, Warr);
	for (int i = 0; i < 3; i++)
	{
		ptr->Flocation[i] = ptr->location[i];
	}

}

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void DrawBox()
{
	gotoxy(1, 1);
	printf("┌");

	for (int i = 0; i < WIDTH*2 + 1; i++)
	{
		printf("─");
	}
	printf("┐");

	gotoxy(1, WIDTH*2 + 2);
	printf("└");
	for (int i = 0; i < WIDTH*2 + 1; i++)
	{
		printf("─");
	}
	printf("┘");

	for (int i = 0; i < WIDTH * 2; i++)
	{
		gotoxy(1, i + 2);
		printf("│");
		gotoxy(WIDTH*2 + 2 + 1, i + 2);
		printf("│");
	}
}

int Eraser(Block* Bptr, int(*Warr)[WIDTH])
{
	int check;
	for (int i = 0; i < WIDTH * 2; i++)
	{
		check = 0;
		for (int j = 0; j < WIDTH; j++)
		{
			if (Warr[i][j] == 1) {
				check++;
			}

			if (check >= WIDTH )
			{
				LineClear(Bptr, Warr, i);

				return 1;
			}
		}

	}

	return 0;
}

void LineClear(Block* Bptr, int(*Warr)[WIDTH], int temp)
{
	int arr[WIDTH * 2][WIDTH] = { 0, };

		for (int i = 0; i < WIDTH * 2; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				arr[i][j] = Warr[i][j];
				if (Warr[i][j] == 1)
				{
					if (i == temp)
					{
						Warr[i][j] = 0;
					}
				}
		
			}
		}

		for (int i = 1; i < WIDTH * 2; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
					if (i <= temp)
					{
						Warr[i][j] = arr[i - 1][j];
					}
			}
		}

		Sleep(1000);
}

void TimeLapse(Block* Bptr, int(*Warr)[WIDTH])
{	
	Visualize(Bptr, Warr);
	DrawBox();	//상자 그리기
	while (1)
	{	
		while (!(Bptr->destroy))
		{
			for (int i = 0; i < 10; i++)
			{
				StopBlock(Bptr, Warr);

				if (Bptr->destroy)
				{
					break;
				}

				KBhit(Bptr, Warr);
				if (Bptr->KBHIT == 1)
				{
					Visualize(Bptr, Warr);
					Bptr->KBHIT = 0;
					Bptr->stop = 0; 
					continue;
				}
				Sleep(Bptr->Time / 10);
			}

			StopBlock(Bptr, Warr);
			Visualize(Bptr, Warr);
			if ((Bptr->destroy) == 0)
			{
				MoveDown(Bptr);
				Visualize(Bptr, Warr);
			}

		}
		if ((Bptr->destroy) == 1)
		{
			break;
		}
	}
	GameOver(Bptr, Warr);
}

void CopyInt(int* dest, int* src, int length)
{
	for (int i = 0; i < length; i++)
	{
		dest[i] = src[i];
	}
}

void StopBlock(Block* Bptr, int(*Warr)[WIDTH])
{
	int check = 0;
	int direction[3] = { 100,100,100 };
	int save[4];	//임시 저장
	int X_temp[4], Y_temp[4];

	CopyInt(save, Bptr->arr, 4);

	for (int i = 0; i < 4; i++)
	{
		if ((save[i] + 1) % 20 == 0)
		{
			Bptr->stop = 1;
			Bptr->stop_where = RIGHT;
		}
		else if ((save[i]) % 20 == 0)
		{
			Bptr->stop = 1;
			Bptr->stop_where = LEFT;
		}
		else if (Bptr->stop != 1)
		{
			Bptr->stop_where = MIDDLE;
		}

		if ((save[i]) >= (WIDTH) * ((2 * WIDTH - 1)))	//정지 함수 최하단에 닿아서 부서지는 함수
		{
			check = 1;
			Bptr->destroy = 1;

		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (check == 1)
		{
			X_temp[i] = save[i] % WIDTH;	//0부터 시작
			Y_temp[i] = (save[i] / WIDTH);
			Warr[Y_temp[i]][X_temp[i]] = 1;
		}
	}
	
	Collision(Bptr, Warr);
	for (int i = 0; i < 3; i++)
	{
		if (Bptr->Flocation[i] != Bptr->location[i])
		{
			direction[i] = 1;
		}
	}

	if (direction[LEFT] == 1)
	{
		Bptr->stop_where = LEFT;
	}
	if (direction[RIGHT] == 1)
	{
		Bptr->stop_where = RIGHT;
	}
	if (direction[DOWN] == 1)
	{
		check = 1;
		Bptr->destroy = 1;
	}

}

void Collision(Block* Bptr, int(*Warr)[WIDTH])
{
	int tempArr[4][3] = { 0 , };
	int X_temp[4][3] = { 0 , };
	int Y_temp[4][3] = { 0 , };

	for (int i = 0; i < 3; i++)
	{
		Bptr->location[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		tempArr[i][LEFT] = Bptr->arr[i] - 1;
		tempArr[i][RIGHT] = Bptr->arr[i] + 1;
		tempArr[i][DOWN] = Bptr->arr[i] + WIDTH;

	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++) {
			X_temp[i][j] = tempArr[i][j] % WIDTH;	//0부터 시작
			Y_temp[i][j] = tempArr[i][j] / WIDTH;	//0부터 시작
		}
		
	}


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)	//배열에 담긴 수 받아내기
		{
			
			if (Warr[Y_temp[i][j]][X_temp[i][j]] == 1)
			{
				(Bptr->location[j])++;
			}
		}
	}
}

int KBhit(Block* Bptr, int(*Warr)[WIDTH])
{
	char input;

		if (_kbhit() && (Bptr->destroy == 0))
		{
			input = _getch();

			StopBlock(Bptr, Warr);
			switch (input) {
			case 'w':
				MoveDown(Bptr);
				Bptr->KBHIT = 1;
				break;

			case 'a':
				if ((Bptr->stop_where) == LEFT)
				{
					return 0;
				}
				MoveLeft(Bptr);
				Bptr->KBHIT = 1;
				break;

			case 's':
				InstantDown(Bptr, Warr);
				Bptr->KBHIT = 1;
				break;

			case 'd':
				if ((Bptr->stop_where) == RIGHT)
				{
					return 0;
				}
					Bptr->KBHIT = 1;
					MoveRight(Bptr);
				break;

			case ' ':
				if ((Bptr->stop_where) == LEFT || (Bptr->stop_where) == RIGHT)
				{
					return 0;
				}
				Rotate(Bptr, Warr);
				Visualize(Bptr, Warr);
				break;
			}
		}
	return 0;
}

void Visualize(Block* Bptr, int (*Warr)[WIDTH])
{
	char BOX[3] = "■";
	int save[4];
	int X_temp[4], Y_temp[4];

	for (int i = 0; i < 4; i++)	//배열에 담긴 수 받아내기
	{
		CopyInt(save, Bptr->arr, 4);
		X_temp[i] = save[i] % WIDTH;	//0부터 시작
		Y_temp[i] = save[i] / WIDTH;
		Warr[Y_temp[i]][X_temp[i]] = 1;
	}
	for(int a = 0; a < WIDTH*2; a++)
	{
		for (int i = 0; i < WIDTH; i++)	//판에 따라 배열 시각화
		{	
			gotoxy(3 + (i * 2), 2 + a);
			if (Warr[a][i] == 1)
			{
				printf("%s", BOX);
			}
			else
			{
				printf("  ");
			}
		}
	}
	if (Bptr->destroy == 0) {
		for (int i = 0; i < 4; i++)	//배열에 담긴 수 0으로 초기화
		{
			Warr[Y_temp[i]][X_temp[i]] = 0;
		}
	}
}

void MoveDown(Block* Bptr)
{
	for (int i = 0; i < 4; i++)
	{
		Bptr->arr[i] += WIDTH;	//arr[i]는 0,0의 값/ X로 키보드 및 시간 제어/이 함수로 키보드 및 시간 동작 실행(Y = MoveDown 카운터)
	}
}
void MoveLeft(Block* Bptr)
{
	for (int i = 0; i < 4; i++)
	{
		Bptr->arr[i]--;
	}
}
void MoveRight(Block* Bptr)
{
	for (int i = 0; i < 4; i++)
	{
		Bptr->arr[i]++;
	}
}
void InstantDown(Block* Bptr, int(*Warr)[WIDTH])
{
	while (1) {
		MoveDown(Bptr);
		StopBlock(Bptr, Warr);
		if (Bptr->destroy)
		{
			break;
		}
	}
}
void ClearScreen()
{
	for (int a = 0; a < WIDTH * 2; a++)
	{
		gotoxy(2, 2 + a);
		for (int i = 0; i < WIDTH; i++)	//판 초기화
		{
			gotoxy(2 + i, 2 + a);
				printf("  ");
		}
	}
}

void GameOver(Block* Bptr, int(*Warr)[WIDTH])
{
	int save[4];
	int X_temp[4], Y_temp[4];

	for (int i = 0; i < 4; i++)	//배열에 담긴 수 받아내기
	{
		CopyInt(save, Bptr->arr, 4);
		X_temp[i] = save[i] % WIDTH;	//0부터 시작
		Y_temp[i] = save[i] / WIDTH;
		Warr[Y_temp[i]][X_temp[i]] = 1;
	}
	for (int i = 0; i < WIDTH; i++)
	{
		if (Warr[4][i] == 1 && Bptr->destroy == 1)
		{
			Bptr->ENDGAME = 1;
		}
	}

	if (Bptr->ENDGAME) {
		
	}
}


	                                          