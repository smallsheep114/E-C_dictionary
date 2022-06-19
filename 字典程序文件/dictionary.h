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
	int capacity;//记录当前容量
	int size;//记录现存单词数量
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

//对字典处理函数的声明
void DictionaryInit(Dictionary* ps);//对字典进行初始化

void AddDictionary(Dictionary* ps);//添加新单词

void ShowDictionary(Dictionary* ps);//展示单词表

void SearchWord(Dictionary* ps);//查找单词

void ClearScreen();//清空屏幕

void DelDictionary(Dictionary* ps);//删除自己已经记住的单词

void ModifyDictionary(Dictionary* ps);//删除意思错误的单词

void SortDictionary(Dictionary* ps);//对字典按英文字母从小到大进行排序

void SaveDictionary(Dictionary* ps);//对字典修改后的内容进行保存

void Exit(Dictionary* ps);//退出字典程序

void Continue(Dictionary* ps,void(*p)(Dictionary* ps));//继续执行操作函数--还有一个参数是函数指针