#define  _CRT_SECURE_NO_WARNINGS 1

#define  _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>


#define MAX_ENGLISH 40
#define MAX_CHINESE 40
#define DEFAULT_SZ 3500

typedef struct Word
{
	char english[MAX_ENGLISH];
	char chinese[MAX_CHINESE];
}word;

typedef struct ditionary
{
	word* data;
	int capacity;//��¼��ǰ����
	int size;//��¼�ִ浥������
}Dictionary;

enum option
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT,
	SAVE,
	CLEAR
};

//���ֵ䴦����������
void DictionaryInit(Dictionary* ps);//���ֵ���г�ʼ��

void AddDictionary(Dictionary* ps);//����µ���

void ShowDictionary(Dictionary* ps);//չʾ���ʱ�

void SearchWord(Dictionary* ps);//���ҵ���

void ClearScreen();//�����Ļ

void DelDictionary(Dictionary* ps);//ɾ���Լ��Ѿ���ס�ĵ���

void ModifyDictionary(Dictionary* ps);//ɾ����˼����ĵ���

void SortDictionary(Dictionary* ps);//���ֵ䰴Ӣ����ĸ��С�����������

void SaveDictionary(Dictionary* ps);//���ֵ��޸ĺ�����ݽ��б���

void Exit(Dictionary* ps);//�˳��ֵ����

void Continue(Dictionary* ps,void(*p)(Dictionary* ps));//����ִ�в�������--����һ�������Ǻ���ָ��