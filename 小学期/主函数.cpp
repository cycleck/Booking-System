#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"数据结构.h"
#include"订单管理.h"
#include "登录函数.h"
#include"航班查询.h"
#include"购票.h"
#include"管理员航班查询及添加.h"
#include <graphics.h>		//包含图形库文件
#include <conio.h>
#include<windows.h>
//gettime函数删了
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
	loadimage(&img, "主菜单.jpg",1200, 800);
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