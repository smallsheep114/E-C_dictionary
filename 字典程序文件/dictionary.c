#define  _CRT_SECURE_NO_WARNINGS 1
#define  _CRT_SECURE_NO_WARNINGS 1
#include"dictionary.h"

//11.
void Continue(Dictionary* ps, void* (*p)(Dictionary* ps))
{
	char ch = 0;
	printf("是否要继续执行上述操作\n");
	printf("Y或y--是，否则退回菜单\n");
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
{//1.打开文件
	char ch = 0;//用来接收每一行的\n
	FILE* pfread = fopen("dictionary.txt", "r");
	if (pfread == NULL)
	{
		perror("open FILE:");
		return;
	}
	//2.读入磁盘文件内容fscanf
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
	ps->data = (word*)calloc(DEFAULT_SZ, sizeof(word));//首元素地址
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
		word* ptr = realloc(ps->data, (ps->capacity + 2) * sizeof(word));//注意重新申请动态内存的方式
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			printf("增容成功\n");
		}
		else
		{
			printf("增容失败\n");
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
		printf("该英语单词应存在你的单词表中\n");
		printf("\t%s \t%s\n", ps->data[i].english, ps->data[i].chinese);
	}
	else
	{
		strcpy(ps->data[ps->size].english, word);
		printf("它的词性和意思是？\n");
		scanf("%s", ps->data[ps->size].chinese);
		ps->size++;
		printf("添加成功\n");
	}
}

void AddDictionary(Dictionary* ps)
{
	CheckCapacity(ps);

	printf("请输入新添加的英文单词\n");
	//检擦一遍是否字典里面已经有该单词了
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
	printf("请输入想要查找的英文单词\n");
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
		printf("查无此单词\n");
	}
	Continue(ps, SearchWord);
}

//5.
void ClearScreen()
{
	system("cls");
}

//6.
//写一个查单词函数，返回其下标,找不到该单词返回-1
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
	return -1;//因为第一个单词的下标是0
}

void DelDictionary(Dictionary* ps)
{
	char word[MAX_ENGLISH] = "";
	printf("请输入想要删除的单词\n");
	scanf("%s", word);
	int ret = Search(ps, word);
	if (ret == -1)
		printf("查无此单词\n");
	else
	{
		for (int i = ret; i < ps->size; i++)
		{
			strcpy(ps->data[i].english, ps->data[i + 1].english);
			strcpy(ps->data[i].chinese, ps->data[i + 1].chinese);
		}
		printf("删除成功\n");
	}
	Continue(ps, DelDictionary);
}

//7.
void ModifyDictionary(Dictionary* ps)
{
	char word[MAX_ENGLISH];
	printf("请输入需要修改的单词\n");
	scanf("%s", word);
	int ret = Search(ps, word);
	if (ret == -1)
	{
		printf("查无此单词\n");
	}
	else
	{
		printf("该单词\n");
		printf("%-40s%-40s\n", ps->data[ret].english, ps->data[ret].chinese);
		printf("请输入想要修改的正确的中文意思\n");
		scanf("%s", word);
		strcpy(ps->data[ret].chinese, word);
		printf("修改成功\n");
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
	printf("排序成功,如图所示\n");
	Sleep(1000);
	ShowDictionary(ps);
}

//9.
void SaveDictionary(Dictionary* ps)
{//1.打开文件
	FILE* pf = fopen("dictionary.txt", "w");
	if (pf == NULL)
	{
		perror("open memory:%s\n");
		return;
	}
	//2.对文件进行操作
	for (int i = 0; i < ps->size; i++)
	{
		fprintf(pf, "%s %s\n", ps->data[i].english, ps->data[i].chinese);
	}
	printf("保存成功\n");
	//3.关闭文件
	fclose(pf);
	pf = NULL;
}

//10.
void Exit(Dictionary* ps)
{
	char ch;
	ClearScreen();
	printf("即将退出字典，是否要对你刚刚进行的操作进行保存\n");
	printf("Y或y--保存\t否则不保存\n");
	getchar();//吃掉多余的\n
	ch = getchar();//吃掉多余的\n
	if ((ch == 'Y') || (ch == 'y'))
	{
		SaveDictionary(ps);
	}
	printf("退出程序\n");
}
