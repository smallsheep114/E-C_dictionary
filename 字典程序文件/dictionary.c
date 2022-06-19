#define  _CRT_SECURE_NO_WARNINGS 1
#define  _CRT_SECURE_NO_WARNINGS 1
#include"dictionary.h"

//11.
void Continue(Dictionary* ps, void* (*p)(Dictionary* ps))
{
	char ch = 0;
	printf("�Ƿ�Ҫ����ִ����������\n");
	printf("Y��y--�ǣ������˻ز˵�\n");
	getchar();
	ch = getchar();
	if ((ch == 'Y') || (ch == 'y'))
	{
		ClearScreen();
		p(ps);
	}
	ClearScreen();
}

//1.
void loadDictionary(Dictionary* ps)
{//1.���ļ�
	char ch = 0;//��������ÿһ�е�\n
	FILE* pfread = fopen("dictionary.txt", "r");
	if (pfread == NULL)
	{
		perror("open FILE:");
		return;
	}
	//2.��������ļ�����fscanf
	for (int i = 0; i < ps->capacity; i++)
	{
		int len = fscanf(pfread,"%s %s",ps->data[i].english,ps->data[i].chinese);
		if (len == EOF)
		{
			ps->size = i+1;
			break;
		}
	}
	fclose(pfread);
	pfread = NULL;
}

void DictionaryInit(Dictionary* ps)
{
	ps->data = (word*)calloc(DEFAULT_SZ, sizeof(word));//��Ԫ�ص�ַ
	if (ps == NULL)
	{
		perror("advocate memory block:%s\n");
		return;
	}
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;
	loadDictionary(ps);
}

//2.
void CheckCapacity(Dictionary* ps)
{
	if (ps->capacity == ps->size)
	{
		word* ptr = realloc(ps->data, (ps->capacity + 2) * sizeof(word));//ע���������붯̬�ڴ�ķ�ʽ
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			printf("���ݳɹ�\n");
		}
		else
		{
			printf("����ʧ��\n");
		}
	}
}

void CheckDictionary(Dictionary* ps)
{
	char word[MAX_ENGLISH];
	int i = 0;
	scanf("%s", word);
	for (i = 0; i < ps->size; i++)
	{
		if (strcmp((ps->data[i].english), word) == 0)
			break;
	}
	if (i < ps->size)
	{
		printf("��Ӣ�ﵥ��Ӧ������ĵ��ʱ���\n");
		printf("\t%s \t%s\n", ps->data[i].english, ps->data[i].chinese);
	}
	else
	{
		strcpy(ps->data[ps->size].english, word);
		printf("���Ĵ��Ժ���˼�ǣ�\n");
		scanf("%s", ps->data[ps->size].chinese);
		ps->size++;
		printf("��ӳɹ�\n");
	}
}

void AddDictionary(Dictionary* ps)
{
	CheckCapacity(ps);

	printf("����������ӵ�Ӣ�ĵ���\n");
	//���һ���Ƿ��ֵ������Ѿ��иõ�����
	CheckDictionary(ps);
	Continue(ps, AddDictionary);
}

//3.
void ShowDictionary(Dictionary* ps)
{
	for (int i = 0; i < ps->size-1; i++)
	{
		printf("%-40s%-40s\n", ps->data[i].english, ps->data[i].chinese);
	}
}

//4.

void SearchWord(Dictionary* ps)
{
	int i = 0;
	char word[MAX_ENGLISH] = "";
	printf("��������Ҫ���ҵ�Ӣ�ĵ���\n");
	scanf("%s", word);
	for (i = 0; i < ps->size; i++)
	{
		if (strstr(ps->data[i].english, word)!=NULL)
		{
			printf("%-40s%-40s\n", ps->data[i].english, ps->data[i].chinese);
			break;
		}
	}
	if (i == ps->size)
	{
		printf("���޴˵���\n");
	}
	Continue(ps, SearchWord);
}

//5.
void ClearScreen()
{
	system("cls");
}

//6.
//дһ���鵥�ʺ������������±�,�Ҳ����õ��ʷ���-1
int Search(Dictionary* ps, char* word)
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (strstr(ps->data[i].english, word) != NULL)
		{
			return i;
		}
	}
	return -1;//��Ϊ��һ�����ʵ��±���0
}

void DelDictionary(Dictionary* ps)
{
	char word[MAX_ENGLISH] = "";
	printf("��������Ҫɾ���ĵ���\n");
	scanf("%s", word);
	int ret = Search(ps, word);
	if (ret == -1)
		printf("���޴˵���\n");
	else
	{
		for (int i = ret; i < ps->size; i++)
		{
			strcpy(ps->data[i].english, ps->data[i + 1].english);
			strcpy(ps->data[i].chinese, ps->data[i + 1].chinese);
		}
		printf("ɾ���ɹ�\n");
	}
	Continue(ps, DelDictionary);
}

//7.
void ModifyDictionary(Dictionary* ps)
{
	char word[MAX_ENGLISH];
	printf("��������Ҫ�޸ĵĵ���\n");
	scanf("%s", word);
	int ret = Search(ps, word);
	if (ret == -1)
	{
		printf("���޴˵���\n");
	}
	else
	{
		printf("�õ���\n");
		printf("%-40s%-40s\n", ps->data[ret].english, ps->data[ret].chinese);
		printf("��������Ҫ�޸ĵ���ȷ��������˼\n");
		scanf("%s", word);
		strcpy(ps->data[ret].chinese, word);
		printf("�޸ĳɹ�\n");
	}
	Continue(ps, ModifyDictionary);
}


//8.
void compare_english(const void* e1, const void* e2)
{
	return strcmp(  ((word*)e1)->english  ,  ((word*)e2)->english  );
}

void SortDictionary(Dictionary* ps)
{
	qsort(ps->data, ps->size, sizeof(ps->data[0]), compare_english);
	printf("����ɹ�,��ͼ��ʾ\n");
	Sleep(1000);
	ShowDictionary(ps);
}

//9.
void SaveDictionary(Dictionary* ps)
{//1.���ļ�
	FILE* pf = fopen("dictionary.txt", "w");
	if (pf == NULL)
	{
		perror("open memory:%s\n");
		return;
	}
	//2.���ļ����в���
	for (int i = 0; i < ps->size; i++)
	{
		fprintf(pf, "%s %s\n", ps->data[i].english, ps->data[i].chinese);
	}
	printf("����ɹ�\n");
	//3.�ر��ļ�
	fclose(pf);
	pf = NULL;
}

//10.
void Exit(Dictionary* ps)
{
	char ch;
	ClearScreen();
	printf("�����˳��ֵ䣬�Ƿ�Ҫ����ոս��еĲ������б���\n");
	printf("Y��y--����\t���򲻱���\n");
	getchar();//�Ե������\n
	ch = getchar();//�Ե������\n
	if ((ch == 'Y') || (ch == 'y'))
	{
		SaveDictionary(ps);
	}
	printf("�˳�����\n");
}
