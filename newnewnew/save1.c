#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "���.h"
#include <Windows.h>
#include <wchar.h>
#define WIDTH 20
#define TIME 100
enum Direction {
	LEFT, RIGHT, DOWN, MIDDLE
};

int main()
{
	system("mode con cols=80 lines=50 | title Tetris");
	int arr[WIDTH*2][WIDTH] = {0,};	//������ ��

	CursorView(0);	//Ŀ�� �����
	Block* ptr;
	Block* new_ptr;
	Block* trash_ptr = (int*)malloc(sizeof(int));	//ù��°�� ���� ������ ��
	trash_ptr->destroy = 1;


	ptr = RandomGenerate(trash_ptr);	//ù��° �����Ҵ�
	free(trash_ptr);

	//ù���۸� Ư��(trash ptr)
	SetBox(ptr, arr);	//�⺻ ������ ����
	TimeLapse(ptr, arr);	//��ǻ� ����

	//�ι�°����
	while (1) {
		new_ptr = RandomGenerate(ptr);
		SetBox(new_ptr, arr);	//�⺻ ������ ����
		TimeLapse(new_ptr, arr);	//��ǻ� ����
	}

	printf("\n\n\n");
}

Block* RandomGenerate(Block* Broken_ptr)//�ι�° �̻���� ������ �Լ�(�ı��� ����� ������ ����)
{
	int rgn;
	rgn = rand() % 4;	//���� ���� ���� (0~4)

	Block* ptr = (int*)malloc(sizeof(Block));
	ptr->rgn = rgn;
	return ptr;
}

void CursorView(char show)//Ŀ�������
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void SetBox(Block* ptr, int(*Warr)[WIDTH])
{
	ptr->destroy = 0;
	ptr->stop = 0;
	ptr->KBHIT = 0;
	ptr->stop = 0;
	ptr->stop_where = MIDDLE;


	int stone1[4] = { (WIDTH * 1 + 1 + 8),(WIDTH*1 + 2 + 8),(WIDTH * 2 + 1 + 8),(WIDTH * 2 + 2 + 8) };
	int stick1[4] = { (WIDTH * 1 + 1 + 7),(WIDTH * 1 + 2 + 7),(WIDTH * 1 + 3 + 7),(WIDTH * 1 + 4 + 7) };
	int mount1[4] = { (WIDTH * 1 + 2 + 8),(WIDTH * 2 + 1 + 8),(WIDTH * 2 + 2 + 8),(WIDTH * 2 + 3 + 8) };
	int notgi1[4] = { (WIDTH * 1 + 3 + 8),(WIDTH * 2 + 1 + 8),(WIDTH * 2 + 2 + 8),(WIDTH * 2 + 3 + 8) };
	int gi1[4] = { (WIDTH * 1 + 1 + 8),(WIDTH * 2 + 1 + 8),(WIDTH * 2 + 2 + 8),(WIDTH * 2 + 3 + 8) };

	switch (ptr->rgn) {
	case 0:
		CopyInt(ptr->arr, stone1, 4);
		break;
	case 1:
		CopyInt(ptr->arr, stick1, 4);
		break;
	case 2:
		CopyInt(ptr->arr, mount1, 4);
		break;
	case 3:
		CopyInt(ptr->arr, notgi1, 4);
		break;
	case 4:
		CopyInt(ptr->arr, gi1, 4);
		break;
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
	printf("��");

	for (int i = 0; i < WIDTH*2 + 1; i++)
	{
		printf("��");
	}
	printf("��");

	gotoxy(1, WIDTH*2 + 2);
	printf("��");
	for (int i = 0; i < WIDTH*2 + 1; i++)
	{
		printf("��");
	}
	printf("��");

	for (int i = 0; i < WIDTH * 2; i++)
	{
		gotoxy(1, i + 2);
		printf("��");
		gotoxy(WIDTH*2 + 2 + 1, i + 2);
		printf("��");
	}
}

void TimeLapse(Block* Bptr, int(*Warr)[WIDTH])
{	
	Visualize(Bptr, Warr);
	DrawBox();	//���� �׸���
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
				Sleep(TIME / 10);
			}

			StopBlock(Bptr, Warr);

			if ((Bptr->destroy) == 0)
			{
				MoveDown(Bptr);
			}
			Visualize(Bptr, Warr);
		}
		if ((Bptr->destroy) == 1)
		{
			break;
		}
	}
}

void CopyInt(int* ptr1, int* ptr2, int length)
{
	for (int i = 0; i < length; i++)
	{
		ptr1[i] = ptr2[i];
	}
}


void Collide(Block* Bptr, int(*Warr)[WIDTH]) {

}

void StopBlock(Block* Bptr, int(*Warr)[WIDTH])
{
	int check = 0;
	int save[4];	//�ӽ� ����
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

		if ((save[i]) >= WIDTH * ((2 * WIDTH)))	//���� �Լ� ���ϴܿ� ��Ƽ� �μ����� �Լ�
		{
			check = 1;
			Bptr->destroy = 1;

		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (check == 1)
		{
			X_temp[i] = save[i] % WIDTH;	//0���� ����
			Y_temp[i] = (save[i] / WIDTH) - 1;
			Warr[Y_temp[i]][X_temp[i]] = 1;
		}
	}
	/*
	SideCheck(Bptr, Warr);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++)
		{
			if (Bptr->Fpt[j][i] != Bptr->pt[j][i])
			{
				Bptr->location[i] = 1;
			}
		}
	}*/
}

/*void SideCheck(Block* Bptr, int(*Warr)[WIDTH])
{
	int saveArr[4];
	int saveTemp[3];
	int count[3][4];
	int direction[4];	//LEFT RIGHT DOWN
	
	int X_temp[4], Y_temp[4];

	for (int i = 0; i < 4; i++)	//�迭�� ��� �� �޾Ƴ���
	{
		CopyInt(saveArr, Bptr->arr, 4);
		X_temp[i] = saveArr[i] % WIDTH;	//0���� ����
		Y_temp[i] = saveArr[i] / WIDTH;
	}

	for (int i = 0; i < 3; i++)
	{
		saveTemp[LEFT] = Bptr->arr[i] - 1;		//LEFT
		saveTemp[RIGHT] = Bptr->arr[i] + 1;		//RIGHT
		saveTemp[DOWN] = Bptr->arr[i] + WIDTH;	//DOWN
		if (saveTemp[DOWN] / WIDTH > WIDTH - 1)
		{
			saveTemp[DOWN] -= WIDTH;
		}
	}

	for (int i = 0; i < 3; i++)	//�迭�� ��� �� �޾Ƴ���
	{
		X_temp[i] = saveTemp[i] % WIDTH;	//0���� ����
		Y_temp[i] = saveTemp[i] / WIDTH;
		if (Y_temp[i] >= WIDTH)
		{
			Y_temp[i]--;
		}
	}

	for (int j = 0; j < 4; j++)	//����for�� ������ count[j]
	{
		for (int i = 0; i < 3; i++)	//�迭�� ��� �� �޾Ƴ���
		{
			if (Warr[1][2] == 1) 
			{
				count[j][i]++;
				Bptr->pt[j][i] = count[j][i];
			}
		}
	}
}*/

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
				//InstantDown(Bptr, Warr);
				Bptr->KBHIT = 1;
				break;
			case 'd':
				if ((Bptr->stop_where) == RIGHT)
				{
					return 0;
				}
					MoveRight(Bptr);
					Bptr->KBHIT = 1;
				break;
			}
		}
	return 0;
}

void Visualize(Block* Bptr, int (*Warr)[WIDTH])
{
	char BOX[3] = "��";
	int save[4];
	int X_temp[4], Y_temp[4];

	for (int i = 0; i < 4; i++)	//�迭�� ��� �� �޾Ƴ���
	{
		CopyInt(save, Bptr->arr, 4);
		X_temp[i] = save[i] % WIDTH;	//0���� ����
		Y_temp[i] = save[i] / WIDTH;
		Warr[Y_temp[i]][X_temp[i]] = 1;
	}
	for(int a = 0; a < WIDTH*2; a++)
	{
		for (int i = 0; i < WIDTH; i++)	//�ǿ� ���� �迭 �ð�ȭ
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
		for (int i = 0; i < 4; i++)	//�迭�� ��� �� 0���� �ʱ�ȭ
		{
			Warr[Y_temp[i]][X_temp[i]] = 0;
		}
	}
}

void MoveDown(Block* Bptr)
{
	for (int i = 0; i < 4; i++)
	{
		Bptr->arr[i] += 20;	//arr[i]�� 0,0�� ��/ X�� Ű���� �� �ð� ����/�� �Լ��� Ű���� �� �ð� ���� ����(Y = MoveDown ī����)
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
/*void InstantDown(Block* Bptr, int(*Warr)[WIDTH])
{
	int re = 3;
	int save[4];
	int X_temp[4], Y_temp[4];
	int height = 0;

	for (int i = 0; i < 4; i++)	//�迭�� ��� �� �޾Ƴ���
	{
		CopyInt(save, Bptr->arr, 4);
		X_temp[i] = save[i] % WIDTH;	//0���� ����
		Y_temp[i] = save[i] / WIDTH;
		
		if (Y_temp[(re - i)] - Y_temp[(re - i - 1)] > 0)	//�� ���ٸ� �ƴϸ� ���ų�
		{
			Warr[2 * WIDTH - height][X_temp[(re - i)]] = 1;
			height++;
		}
		
	}
	if (Bptr->destroy == 0) {
		for (int i = 0; i < 4; i++)	//�迭�� ��� �� 0���� �ʱ�ȭ
		{
			Warr[Y_temp[i]][X_temp[i]] = 0;
		}
	}
}*/
void ClearScreen()
{
	for (int a = 0; a < WIDTH * 2; a++)
	{
		gotoxy(2, 2 + a);
		for (int i = 0; i < WIDTH; i++)	//�� �ʱ�ȭ
		{
			gotoxy(2 + i, 2 + a);
				printf("  ");
		}
	}
}