#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"���ݽṹ.h"
#include"��������.h"
#include "��¼����.h"
#include"�����ѯ.h"
#include"��Ʊ.h"
#include"����Ա�����ѯ�����.h"
#include <graphics.h>		//����ͼ�ο��ļ�
#include <conio.h>
#include<windows.h>
//gettime����ɾ��
void firstmuea();
int main()
{
	firstmuea();
	

	return 0;
}


void firstmuea()
{
	initgraph(1200,800, SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();
	IMAGE img;
	loadimage(&img, "���˵�.jpg",1200, 800);
	putimage(0, 0, &img);
	while (1) {
		ExMessage msg;
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 0 && msg.x < 1200 && msg.y>0 && msg.y < 800)
				{
					closegraph();
					retFirst();

				}
				break;

			}
		}
	}
	getchar();
	
}