#include"���ݽṹ.h"
#ifndef �����ѯ_h
#define �����ѯ_h 

//�������ѯ��
void Select_Flight();

//ͨ������źͳ���ʱ�䣨�죩������ѡ   num---����ţ�date---��������
void select_Flightnum_Date(char* num, char* Date,List_F F);
//ͨ����������+�������+����ʱ�䣨�죩������ѡ   start---�������У�down---������У�date---��������
void select_City_Date(char* start, char* down, char* Date,List_F F);

//�Ƿ�ѡ����˲�ѯ���       F1---������Ϣ�Ľṹ��  Date---����
void if_filter(List_F F1,char*Date);
//ѡ��yes�Ĺ��˲�ѯ����       F1---������Ϣ�Ľṹ��  Date---����
void if_filter_yes(List_F F1,char*Date);
//ͨ��ʱ��ι���       F1---������Ϣ�Ľṹ��  Date---����
void filter_time(List_F F1,char*Date);
//ͨ�����չ�˾����       F1---������Ϣ�Ľṹ��  Date---����
void filter_company(List_F F1,char*Date);
//ͨ����λ����       F1---������Ϣ�Ľṹ��  Date---����
void filter_class(List_F F1,char*Date);
//ͨ�����͹���       F1---������Ϣ�Ľṹ��  Date---����
void filter_type(List_F F1,char*Date);

//�������ʱ������      F1---������Ϣ�Ľṹ�� k---������
void sort_by_Time(List_F F1, int k);
//���ݼ۸�����     F1---������Ϣ�Ľṹ��ָ�� i---sort_by_Time���еĵ�i+1��ѭ��
void sortTime(List_F* F1, int i);
//���ݼ۸�����     F1---������Ϣ�Ľṹ��ָ�� i---sort_by_Price���еĵ�i+1��ѭ��
void sortPrice(List_F* F1, int i);
//���ݼ۸�������ʾ      F1---������Ϣ�Ľṹ��ָ�� k---������
void sort_by_Price(List_F* F1, int k);

//�Ƿ�ѡ��Ʊ      F1---������Ϣ�Ľṹ�� Date---����
void if_buy_ticket(char*Flightnum,char*Date);
//�����������ʱ������      F1---������Ϣ�Ľṹ��ָ��
void sort_All_by_Time(List_F* F1);
//�жϺ���������Ƿ���ȷ,���ҵ���Ӧ���ڵĺ����       Flightnum---����� Date---�����ں����ļ���Ϣ��·��
char* judge_Flightnum(char* Flightnum, char* Date);
//�ж����������Ƿ���ȷ��������ȷ���ļ���Ϣ�����뵽�ṹ����     Date---����
char* judge_Date(char* Date);
//�ж����������Ƿ���ȷ      Date---����
char* judgedate(char*Date);
//�û��õ��ĺ����ѯ���       F---������Ϣ�Ľṹ��ָ�� Date---�����ں����ļ���Ϣ��·��
void user_readinfo(List_F* F, char* Date);


#endif 
