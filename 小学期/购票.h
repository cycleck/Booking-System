#include"���ݽṹ.h"
#ifndef ��Ʊ_h
#define ��Ʊ_h 

void ui();//�û�����
void ticketBuy(char* Fnum, char* Ftime, char* Uname, char* Upassword); // ���ڹ��򺽰�ĺ��������뺽���,�����������,��ǰ�û�������������
void myTicket(char* Uname);//�鿴�ҵĶ���
void UserReadorder(List_P *P);//�û��鿴�ҵĶ���ʱ�����ڴ��ļ�����.txt��ȡȫ�������ĺ���

void checkPass(char *Upassword);//��֤֧������
char* checkSeatFir();//��֤��λ��
char* checkSeatEco();//��֤��λ��
#endif

//�޸����� 2021.9.6.18��45