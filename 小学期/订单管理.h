#include"���ݽṹ.h"
#include <graphics.h>		//����ͼ�ο��ļ�
#include <conio.h>
#include<windows.h>
#ifndef ��������_h
#define ��������_h 
void ReadInfo(List_F *);    //���뺽����Ϣ
void PrintAirmsg_U(List_F );  //��ӡ������Ϣ(�û���)
void PrintAirmsg_A(List_F);  //��ӡ������Ϣ(����Ա��)

void Readorder(List_P *);   //���빺Ʊ��Ϣ
void Printorder(List_P );   //��ӡ��Ʊ��Ϣ

void ReadInfo_otherday(List_F *,int);//���������պ�����Ϣ
void calculate_F(List_F *);// �����������Լ���Ʊ��Ʊ��
void Income_Rank(List_F *);//������������
void Rate_Rank(List_F *);  //��������������
void Book_Rank(List_F *F,Admination); //���չ�Ʊ������
void Showorder(List_F ,List_P , Admination ); //���ݺ��չ�˾��ѯ�û�����
void ReadAdmination(Admination*);//��ȡ��ǰ����Ա��Ϣ
void Recommend(List_F *F);

void QRcode();//����������
void Boardcheck(Passenger ,List_F ,int);//�����ǻ���
#endif 


