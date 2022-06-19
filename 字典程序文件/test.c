#define  _CRT_SECURE_NO_WARNINGS 1

#include"dictionary.h"

void menu()
{
	printf("*********************************\n");
	printf("***1.�ӵ���           2.ɾ����***\n");
	printf("***3.�鵥��           4.�ĵ���***\n");
	printf("***5.չʾ���ʱ�       6.���򵥴�*\n");
	printf("***7.����             8.����*****\n");
	printf("***          0.�˳�           ***\n");
}

int main()
{
	int input = 0;
	Dictionary dic;
	DictionaryInit(&dic);
	do
	{
		menu();
		printf("��ѡ����Ҫʵ�ֵĹ���\n");
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
			printf("�������������ѡ��\n");
			Sleep(1000);
			break;
		}
	} while (input);
	return 0;
}