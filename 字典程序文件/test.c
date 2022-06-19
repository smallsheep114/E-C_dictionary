#define  _CRT_SECURE_NO_WARNINGS 1

#include"dictionary.h"

void menu()
{
	printf("*********************************\n");
	printf("***1.加单词           2.删单词***\n");
	printf("***3.查单词           4.改单词***\n");
	printf("***5.展示单词表       6.排序单词*\n");
	printf("***7.保存             8.清屏*****\n");
	printf("***          0.退出           ***\n");
}

int main()
{
	int input = 0;
	Dictionary dic;
	DictionaryInit(&dic);
	do
	{
		menu();
		printf("请选择想要实现的功能\n");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			AddDictionary(&dic);
			break;
		case DEL:
			DelDictionary(&dic);
			break;
		case SEARCH:
			SearchWord(&dic);
			break;
		case MODIFY:
			ModifyDictionary(&dic);
			break;
		case SHOW:
			ShowDictionary(&dic);
			break;
		case SORT:
			SortDictionary(&dic);
			break;
		case SAVE:
			SaveDictionary(&dic);
			break;
		case CLEAR:
			ClearScreen();
			break;
		case EXIT:
			Exit(&dic);
			break;
		default:
			printf("输入错误请重新选择\n");
			Sleep(1000);
			break;
		}
	} while (input);
	return 0;
}