#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>

#define PI		3.1415926															// ����Բ����
#define BRIGHT	5																	// ������ɫ����(�����������)

// �ֵ�������Ľṹ��
struct Window
{
	int length;																		// �����ĳ�
	int width;																		// �����Ŀ�
};
// ��������1
struct House1
{
	int length;																		// ���ӵĳ�
	int width;																		// ���ӵĿ�
	Window win;																		// �����ϵĴ���
};
// ��������2
struct House2
{
	int length;																		// ���ӵĳ�
	int width;																		// ����ǽ�ڵĸ߶�
	int top;																		// ���Ӷ�����׶�ĸ�
};

IMAGE temp;																			// ���ڱ�������ǰ�Ľֵ�ͼ��

// ��������
int CirJudgeZero(int index1, int index2);											// �õ�һ��������������index1��index2��ʾ�����Χ��ָ��
void Light(int x);																	// ��������
void Building();																	// ���ƽֵ�(�������)
int DrawHou1(int Sumbor);															// ����������1
int DrawHou2(int Sumbor);															// ����������2
void LightChange();																	// ���Ƹ����ֵ�

// ��ں���
int main()
{
	srand((unsigned)time(NULL));													// �����������
	initgraph(640, 480);

	setorigin(0, 480);																// ��������ԭ�������½�
	setaspectratio(1, -1);															// ��������y�ᷴ��
	setbkcolor(RGB(20, 20, 20));													// ���ñ���ɫ
	cleardevice();

	Building();																		// �Ȼ��ƽֵ�������image
	
	int seedtime,time,Xpoint;

	while (true)																	// ����Ҽ��˳�����
	{
		do {
			seedtime = rand() % 500;
		} while (seedtime <= 150);
		
		time = rand() % 3000 + seedtime;
		Xpoint = rand() % 590 + 50;													// ���������ֵĺ�����
		Sleep(time);																// �ȴ�һ�����ʱ�䣬��������
		Light(Xpoint);																// ������
		LightChange();																// �߹�ͼ���㷨�Լ��ָ�
	}

	closegraph();
}

// �õ�һ��������������index1��index2��ʾ�����Χ��ָ��
int CirJudgeZero(int index1,int index2)												// ѭ����������õ�һ��������������index1��index2��ʾ�����Χ��ָ��
{
	int rec = 0;																	// ���ڴ��ݵķ����������ʼ��Ϊ0
	while (rec == 0)
	{
		rec = rand() % index1 + index2;
	}
	return rec;
}

// ��������
void Light(int x)
{
	int RanTimes = CirJudgeZero(3, 0);												// ����Ƿ����˫������
	int EndPoi;																		// ���ڼ�¼������յ�
	for (int i = 0; i < RanTimes; i++)
	{
		int Xpoint = x, Ypoint = 480;
		EndPoi = Ypoint - rand() % 120 - 120;										// ���������յ�
		while (Ypoint >= EndPoi)													// �ж��Ƿ񵽴��յ� && ����ÿ��С�߶�
		{
			int Dis = rand() % 20;													// �������ÿ�εĳ���
			int Ang1 = rand() % 120 - 60;											// �������ĽǶ�(x��)
			int Ang2 = rand() % 120 - 60;											// �������ĽǶ�(y��)
			int NextX = Xpoint + (int)(Dis * sin(Ang1 * PI / 180));					// ��������̵����һ��(x��)
			int NextY = Ypoint - (int)(Dis * cos(Ang2 * PI / 180));					// ��������̵����һ��(y��)
			setlinecolor(RGB(125, 250, 255));										// ����������ɫ
			setlinestyle(PS_ENDCAP_ROUND | PS_SOLID, 2);							// ����������ʽ(�߶ζϵ�Ϊƽ��ʵ�ߡ����)
			line(Xpoint, Ypoint, NextX, NextY);										// ��������
			Xpoint = NextX;															// ���˵㸳ֵ����ʼ��(x��)
			Ypoint = NextY;															// ���˵㸳ֵ����ʼ��(y��)
			Sleep((rand() % 100) > 66 ? 1 : 0);										// ����ͣ��ʱ��
		}
	}
}

// ����������1
int DrawHou1(int Sumbor)															
{
	House1 hou1;
	hou1.length = CirJudgeZero(40, 60);												// ������ӵĳ�
	hou1.width = CirJudgeZero(160, 80);												// ������ӵĿ�
	hou1.win.length = 10;															// �����ĳ�
	hou1.win.width = 8;																// �����Ŀ�
	int point1[8] = { Sumbor,0,
						Sumbor + hou1.length,0,
						Sumbor + hou1.length,hou1.width,
						Sumbor,hou1.width };										// ���巿�ӵ���������
	setfillcolor(RGB(30, 30, 60));													// ���÷��ӵ����ɫ
	solidpolygon((POINT*)point1, 4);												// ������䷿��(�ı���)

	// ���Ʒ����ϵĴ���
	int WinLefDis = CirJudgeZero(10, 18);											// �����������ߵľ���
	int WinTopDis = CirJudgeZero(10, 10);											// ��������붥���ľ���
	int WinInvDis = CirJudgeZero(10, 10);											// ��������봰��֮��ļ��(���������Ҷ������ֵ)
	for (int Ypoint = hou1.width - WinTopDis; Ypoint > hou1.width / 3;)				// ���ƴ���������
	{
		for (int Xpoint = Sumbor + WinLefDis; Xpoint < Sumbor + hou1.length - 19;)	//  ����ÿ�л���������
		{
			int WinPoint[8] = { Xpoint ,Ypoint ,
				Xpoint + hou1.win.length ,Ypoint ,
				Xpoint + hou1.win.length ,Ypoint - hou1.win.width,
				Xpoint ,Ypoint - hou1.win.width };									// ���崰����������
			int ran = CirJudgeZero(3, 0);											// ���ֵ�����ж���ɫ(���ŵĺͰ��ŵ�)
			if (ran == 1)
				setfillcolor(RGB(240, 240, 150));									// ���ô�������
			else if (ran == 2)
				setfillcolor(RGB(30, 44, 40));										// ���ô�������

			solidpolygon((POINT*)WinPoint, 4);										// ���ޱ߿����䴰(�ı���)
			Xpoint += (hou1.win.length + WinInvDis);								// �����Ͻǵ�xֵÿ�λ��궼���ӣ����㻭��һ������
		}
		Ypoint -= (hou1.win.width + WinInvDis);										// �����Ͻǵ�yֵÿ�λ��궼���ӣ����㻭��һ������
	}
	Sumbor += hou1.length;															// x��������������ӵĳ��������ж��Ƿ񻭳���Ļ��Χ
	return Sumbor;																	// ����x����
}

// ����������2
int DrawHou2(int Sumbor)															
{
	House2 hou2;
	hou2.length = CirJudgeZero(20, 80);												// ������ӵĳ�
	hou2.width = CirJudgeZero(40, 60);												// ������ӵĿ�
	hou2.top = CirJudgeZero(10, 100);												// ������ӵĶ�����y����
	int point2[10] = { Sumbor,0,
						Sumbor ,hou2.width ,
						Sumbor + (hou2.length / 2),hou2.top ,
						hou2.length + Sumbor,hou2.width,
						hou2.length + Sumbor,0 };									// ���巿�ӵ�����
	setfillcolor(RGB(30, 44, 83));													// ���÷��ӵ����ɫ
	solidpolygon((POINT*)point2, 5);												// �����ķ���(5����)

	// ������2��װ��
	int ran = CirJudgeZero(3, 0);													// ����һ��������������жϻ�ʲô���Ĵ���
	if (ran == 1)																	// ��Բ�δ���
	{
		int ranlight = CirJudgeZero(3, 0);											// ����һ��������������жϴ����Ƿ�����
		if (ranlight == 1)															// ���ŵĴ���
			setfillcolor(RGB(30, 44, 50));
		else if(ranlight == 2)														// ���ŵĴ���
			setfillcolor(RGB(150, 200, 130));
		int radius = rand() % 10 + (hou2.width / 6);								// ����뾶
		solidcircle(Sumbor + (hou2.length / 2), hou2.width * 2 / 3, radius);		// ������ޱ߿�Բ�δ���
	}
	else if (ran == 2)																// �����δ���
	{
		int ranlight = CirJudgeZero(3, 0);											// ����һ��������������жϴ����Ƿ�����
		if (ranlight == 1)															// ���ŵĴ���
			setfillcolor(RGB(30, 44, 50));
		else if (ranlight == 2)														// ���ŵĴ���
			setfillcolor(RGB(150, 200, 130));
		int radius = rand() % 10 + (hou2.width / 6);								// ����뾶
		solidcircle(Sumbor + (hou2.length / 2), hou2.width * 3 / 5, radius);		// ��������Բ�κ��ı���Ƕ�����
		solidrectangle(Sumbor + (hou2.length / 2) - radius, hou2.width * 3 / 5, Sumbor + (hou2.length / 2) + radius, hou2.width * 3 / 5 - radius);
	}
	Sumbor += hou2.length;															// x��������������ӵĳ��������ж��Ƿ񻭳���Ļ��Χ
	return Sumbor;
}

// ��������
void Building()																		
{
	int index = 0;																	// ���ֵ�����жϻ���ʲô����
	// �����������
	for (int Sumbor = 0; Sumbor < 640; )											// ��¼��������ұ߽磬���ó���ͣ��������
	{
		index = CirJudgeZero(3, 0);
		switch (index)
		{
		case 1:																		// ����������1
			Sumbor = DrawHou1(Sumbor);
			break;
		case 2:																		// ����������2
			Sumbor = DrawHou2(Sumbor);
			break;
		}
	}
	getimage(&temp, 0, 0, 640, 480);												// ��¼��ʱ��ͼ��Ϊ�������ָ�ͼ��
}

// �������ʱ��???��
void LightChange()																
{
	// �������(��Ļ)������
	float Lightness = (float)CirJudgeZero(10,(CirJudgeZero(15, 10) / 10));

	IMAGE image;																	// ����һ��ͼ��������ڻ��Ƹ�����ͼ��
	getimage(&image, 0, 0, 640, 480);												// ��ȡͼ��Χ
	DWORD *pMem = GetImageBuffer(&image);											// ��ȡָ���Դ��ָ��
	int r, g, b;																	// ����ֱ��ȡ���RGB��ɫֵ
	for (int i = 0; i < (640 * 480); i++)											// ѭ����ȡÿ�����RGBֵ���ж��Ƿ����255
	{
		r = min((int)(GetRValue(pMem[i])*Lightness), 255);							// �����������ص㶼����һ������1����ֵ�������ɫ�ͱ�����
		b = min((int)(GetBValue(pMem[i])*Lightness), 255);
		g = min((int)(GetGValue(pMem[i])*Lightness), 255);
		pMem[i] = RGB(r, g, b);
	}
	putimage(0, 0, &image);															// ����߹�ͼ��
	Sleep(100);																		// ͣ��ʱ��
	cleardevice();																	// �����Ļͼ��(����putimage���ͼ���ڶ�������һ�ο�϶��,���ֱ������,�Ϳ�������϶��)
	putimage(0, 0, &temp);															// �������ԭ���ֵ���ͼ��
}