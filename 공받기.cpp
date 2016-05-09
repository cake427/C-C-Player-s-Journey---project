#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "Screen.c"
#include <windows.h>
#include <time.h>

typedef struct _GOAL
{
	int gMoveX, gMoveY;
	int gLength; //����� ���� 
	int gLineX[9]; //����� ���ν� ��ǥ 
	int gDistance; // ��� �̵��Ÿ� 
	clock_t MoveTime;
	clock_t OldTime;
} GOAL;




typedef struct _Ball
{
	int ReadyB; // 1 = �غ�, 0 = �� 
	int bMoveX, bMoveY; //�� �̵� ��ǥ
	clock_t MoveTime; // �̵��� �ɸ� �ð�
	clock_t OldTime; // ���� �̵��ð� 
} BALL; 


typedef struct _Player
{
	int CenterX, CenterY; //X, Y ��ǥ ���� 
	int MoveX, MoveY; // X, Y ��ǥ �̵� 
	int X, Y; // X, Y ���� ��� ��ǥ �� 
	int Index; // �߽���ǥ�� �ε��� 
} PLAYER;


typedef struct _Position
{
	int X, Y; // X, Y ���� ��ǥ 
} Position; 


GOAL Goal;
BALL Ball;
PLAYER Player;
char StrPlayer[] = {"|__O__|"}; //ĳ����
int Length; // ���ΰ� ĳ���� ����

// �ʱ�ȭ 

void Init() {
	Player.CenterX = 3; //���ΰ� X �߽� ��ǥ
	Player.CenterY = 0; //���ΰ� Y �߽� ��ǥ 
 	Player.MoveX = 20; // ���ΰ� �̵� ����ǥ �ʱ�ȭ
	Player.Y = Player.MoveY = 22; // ���ΰ� �̵� Y��ǥ �ʱ�ȭ
	Player.X = Player.MoveX - Player.CenterX; //���ΰ� ĳ���� ��� ��ǥ
	Length = strlen(StrPlayer); //���ΰ� ��ü ���� 

	
	Ball.ReadyB = 1;
	Ball.bMoveX = Player.MoveX;
	Ball.bMoveY = Player.MoveY - 1;
	Ball.MoveTime = 100;
}

// ������ ����

void Update()
{
	clock_t CurTime = clock();
	if(Ball.ReadyB == 0) {//�̵����� ���
		if ((CurTime - Ball.OldTime) > Ball.MoveTime) 
	 		{
			 if(Ball.bMoveY - 1 > 0)
	 			Ball.bMoveY--;
	 			Ball.OldTime = CurTime;
			 	}else{
			 		Ball.ReadyB = 1;
			 		Ball.bMoveX = Player.MoveX;
			 		Ball.bMoveY = Player.MoveY - 1;
				 }
	 		}else{
		Ball.bMoveX = Player.MoveX;
	}
}

// ���

void Render()
{
	char string[100] = {0};
	ScreenClear();
	
	// ��� ����
	// �¿쿡 ���� ���� (Ŭ����) 
	
	if(Player.X < 0) //���� Ŭ���� 
		{ScreenPrint(0, Player.MoveY, &StrPlayer[Player.X*-1]);}
	else if(Player.MoveX + (Length - ((Player.MoveX + Player.CenterX + 1) > 79 )))
	{
		strncat(string, StrPlayer, Length - ((Player.MoveX + Player.CenterX + 1) -79));	
	 	ScreenPrint(Player.X, Player.Y, StrPlayer);
	 }else{
		ScreenPrint(Player.X, Player.Y, StrPlayer);
	}

	sprintf(string, "���ΰ� �̵���ǥ : %d, %d", Player.MoveX, Player.Y);
	ScreenPrint(0, 0, string);
	
	//��� ��
	
	ScreenFlipping(); 
 }
 
 //����
 
 void Release()
 {
  }
  
  
int main (void){
	int Key, Remain;
	
	ScreenInit();
	Init(); // �ʱ�ȭ
	
	while( 1 ) //���ѹݺ� 
	{
		if(_kbhit())
		{
			Key = _getch();
			if(Key == 'q')
				break;
			switch(Key)
			{
				case '1' :
					Player.MoveX--; 
					Remain =  Length - (Player.CenterX + 1); // �������� = ��ü ���� - (�߽���ǥ + 1)
					if(Player.MoveX + Remain > 79 || Player.MoveX - Player.CenterX < 0)
					Player.MoveX++;
					Player.X = Player.MoveX - Player.CenterX;
					break;
				case '2' :
					Player.MoveX++;
					Remain = Length - (Player.CenterX + 1);
					if(Player.MoveX + Remain >79 || Player.MoveX - Player.CenterX < 0)
						Player.MoveX++;
					Player.X = Player.MoveX - Player.CenterX;
					break;
				case '3' :
					if(Ball.ReadyB)
					{
						Ball.bMoveX = Player.MoveX;
						Ball.bMoveY = Player.MoveY - 1;
						Ball.OldTime = clock();
						Ball.ReadyB = 0;
					}
					break;	
			}
		}
		
		Update();//������ ���� 
		Render(); //ȭ�� ��� 
		
	 } 
	 
	 Release();
	 ScreenRelease();
	 return 0;
}
