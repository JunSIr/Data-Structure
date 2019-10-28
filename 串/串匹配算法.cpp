#include "string.h"
#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

typedef int Status;		/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;	/* ElemType���͸���ʵ������������������Ϊint */

typedef char String[MAXSIZE + 1]; /*  0�ŵ�Ԫ��Ŵ��ĳ��� */

								  /* ����һ����ֵ����chars�Ĵ�T */
Status StrAssign(String T, char *chars)
{
	int i;
	if (strlen(chars)>MAXSIZE)
		return ERROR;
	else
	{
		T[0] = strlen(chars);
		for (i = 1; i <= T[0]; i++)
			T[i] = *(chars + i - 1);
		return OK;
	}
}

Status ClearString(String S)
{
	S[0] = 0;/*  ���Ϊ�� */
	return OK;
}

/*  ����ַ���T�� */
void StrPrint(String T)
{
	int i;
	for (i = 1; i <= T[0]; i++)
		printf("%c", T[i]);
	printf("\n");
}

/*  ���Next����ֵ�� */
void NextPrint(int next[], int length)
{
	int i;
	for (i = 1; i <= length; i++)
		printf("%d", next[i]);
	printf("\n");
}

/* ���ش���Ԫ�ظ��� */
int StrLength(String S)
{
	return S[0];
}

/* ���ص�ģʽƥ�䷨ */
int Index(String S, String T, int pos)
{
	int i = pos;	/* i��������S�е�ǰλ���±�ֵ����pos��Ϊ1�����posλ�ÿ�ʼƥ�� */
	int j = 1;				/* j�����Ӵ�T�е�ǰλ���±�ֵ */
	while (i <= S[0] && j <= T[0]) /* ��iС��S�ĳ��Ȳ���jС��T�ĳ���ʱ��ѭ������ */
	{
		if (S[i] == T[j]) 	/* ����ĸ�������� */
		{
			++i;
			++j;
		}
		else 				/* ָ��������¿�ʼƥ�� */
		{
			i = i - j + 2;		/* i�˻ص��ϴ�ƥ����λ����һλ */
			j = 1; 			/* j�˻ص��Ӵ�T����λ */
		}
	}
	if (j > T[0])
		return i - T[0];
	else
		return 0;
}

/* ͨ�����㷵���Ӵ�T��next���顣 */
void get_next(String T, int *next)
{
	int i, j;
	i = 1;
	j = 0;
	next[1] = 0;
	while (i<T[0])  /* �˴�T[0]��ʾ��T�ĳ��� */
	{
		if (j == 0 || T[i] == T[j]) 	/* T[i]��ʾ��׺�ĵ����ַ���T[j]��ʾǰ׺�ĵ����ַ� */
		{
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];	/* ���ַ�����ͬ����jֵ���� */
	}
}

/* �����Ӵ�T������S�е�pos���ַ�֮���λ�á��������ڣ���������ֵΪ0�� */
/*  T�ǿգ�1��pos��StrLength(S)�� */
int Index_KMP(String S, String T, int pos)
{
	int i = pos;		/* i��������S�е�ǰλ���±�ֵ����pos��Ϊ1�����posλ�ÿ�ʼƥ�� */
	int j = 1;			/* j�����Ӵ�T�е�ǰλ���±�ֵ */
	int next[255];		/* ����һnext���� */
	get_next(T, next);	/* �Դ�T���������õ�next���� */
	while (i <= S[0] && j <= T[0]) /* ��iС��S�ĳ��Ȳ���jС��T�ĳ���ʱ��ѭ������ */
	{
		if (j == 0 || S[i] == T[j]) 	/* ����ĸ�����������������㷨������j=0�ж� */
		{
			++i;
			++j;
		}
		else 			/* ָ��������¿�ʼƥ�� */
			j = next[j];/* j�˻غ��ʵ�λ�ã�iֵ���� */
	}
	if (j > T[0])
		return i - T[0];
	else
		return 0;
}

/* ��ģʽ��T��next��������ֵ����������nextval */
void get_nextval(String T, int *nextval)
{
	int i, j;
	i = 1;
	j = 0;
	nextval[1] = 0;
	while (i<T[0])  /* �˴�T[0]��ʾ��T�ĳ��� */
	{
		if (j == 0 || T[i] == T[j]) 	/* T[i]��ʾ��׺�ĵ����ַ���T[j]��ʾǰ׺�ĵ����ַ� */
		{
			++i;
			++j;
			if (T[i] != T[j])      /* ����ǰ�ַ���ǰ׺�ַ���ͬ */
				nextval[i] = j;	/* ��ǰ��jΪnextval��iλ�õ�ֵ */
			else
				nextval[i] = nextval[j];	/* �����ǰ׺�ַ���ͬ����ǰ׺�ַ��� */
											/* nextvalֵ��ֵ��nextval��iλ�õ�ֵ */
		}
		else
			j = nextval[j];			/* ���ַ�����ͬ����jֵ���� */
	}
}

int Index_KMP1(String S, String T, int pos)
{
	int i = pos;		/* i��������S�е�ǰλ���±�ֵ����pos��Ϊ1�����posλ�ÿ�ʼƥ�� */
	int j = 1;			/* j�����Ӵ�T�е�ǰλ���±�ֵ */
	int next[255];		/* ����һnext���� */
	get_nextval(T, next);	/* �Դ�T���������õ�next���� */
	while (i <= S[0] && j <= T[0]) /* ��iС��S�ĳ��Ȳ���jС��T�ĳ���ʱ��ѭ������ */
	{
		if (j == 0 || S[i] == T[j]) 	/* ����ĸ�����������������㷨������j=0�ж� */
		{
			++i;
			++j;
		}
		else 			/* ָ��������¿�ʼƥ�� */
			j = next[j];/* j�˻غ��ʵ�λ�ã�iֵ���� */
	}
	if (j > T[0])
		return i - T[0];
	else
		return 0;
}

int main()
{
	int i, *p;
	String s1, s2;
	String s, t;

	/*����Ŀ�괮s = abcabcdabcdeabcdeabcdefabcdefg��ģʽ��t = abcdeabcdefab*/
	StrAssign(s, "abcabcdabcdeabcdeabcdefabcdefg");
	StrAssign(t, "abcdeabcdefab");
	printf("1.����Ŀ�괮s��ģʽ��t�ɹ�\n");

	/*���ü�ƥ���㷨(����ģʽƥ��)��t��s�е�λ��*/
	int index1 = Index(s, t, 1);
	printf("2.t��s�е�λ��:%d", index1);

	/*��ģʽ��t���next����ֵ��nextval����ֵ*/
	printf("\n3.��ģʽ��t���next����ֵ��nextval����ֵ: ��ʼִ��\n");
	i = StrLength(t);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next(t, p);
	printf(".NextΪ: ");
	NextPrint(p, StrLength(t));

	printf(".NextValΪ: ");
	get_nextval(t, p);
	NextPrint(p, StrLength(t));

	/*����KMP�㷨��t��s�е�λ��*/
	int len = 
	Index_KMP(s, t, 1); 
	printf("4.����KMP�㷨��t��s�е�λ��:%d", len);

	/*���øĽ���KMP�㷨��t��s�е�λ��*/
	int len1 =
		Index_KMP1(s, t, 1);
	printf("\n5.���øĽ���KMP�㷨��t��s�е�λ��:%d", len1);

	system("pause") ; 



	return 0;
}


