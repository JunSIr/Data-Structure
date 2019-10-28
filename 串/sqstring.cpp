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

#define MAXSIZE 40 /* �洢�ռ��ʼ������ */

typedef int Status;		/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;	/* ElemType���͸���ʵ������������������Ϊint */

typedef char String[MAXSIZE + 1]; /*  0�ŵ�Ԫ��Ŵ��ĳ��� */

 /* ����һ����ֵ����chars�Ĵ�T */
Status StrAssign(String T, char *chars)
{

													/*strlen-->����ַ�������*/
	int i;
	if (strlen(chars)>MAXSIZE)
		return ERROR;
	else
	{	
		/*T[0]��Ŵ��ĳ���*/
		T[0] = strlen(chars);


		for (i = 1; i <= T[0]; i++)
			T[i] = *(chars + i - 1);
		return OK;
	}
}

/* �ɴ�S���Ƶô�T */
Status StrCopy(String T, String S)
{
	int i;
	for (i = 0; i <= S[0]; i++)
		T[i] = S[i];
	return OK;
}

/* ��SΪ�մ�,�򷵻�TRUE,���򷵻�FALSE */
Status StrEmpty(String S)
{
	if (S[0] == 0)
		return TRUE;
	else
		return FALSE;
}

/*  ��ʼ����: ��S��T���� */
/*  �������: ��S>T,�򷵻�ֵ>0;��S=T,�򷵻�ֵ=0;��S<T,�򷵻�ֵ<0 */
int StrCompare(String S, String T)
{
	int i;
	for (i = 1; i <= S[0] && i <= T[0]; ++i)
		if (S[i] != T[i])
			return S[i] - T[i];
	return S[0] - T[0];
}

/* ���ش���Ԫ�ظ��� */
int StrLength(String S)
{
	return S[0];
}

/* ��ʼ����:��S���ڡ��������:��S��Ϊ�մ� */
Status ClearString(String S)
{
	S[0] = 0;/*  ���Ϊ�� */
	return OK;
}

/* ��T����S1��S2���Ӷ��ɵ��´�����δ�ضϣ��򷵻�TRUE������FALSE */
Status Concat(String T, String S1, String S2)
{
	int i;
	if (S1[0] + S2[0] <= MAXSIZE)
	{ /*  δ�ض� */
		for (i = 1; i <= S1[0]; i++)
			T[i] = S1[i];
		for (i = 1; i <= S2[0]; i++)
			T[S1[0] + i] = S2[i];
		T[0] = S1[0] + S2[0];
		return TRUE;
	}
	else
	{ /*  �ض�S2 */
		for (i = 1; i <= S1[0]; i++)
			T[i] = S1[i];
		for (i = 1; i <= MAXSIZE - S1[0]; i++)
			T[S1[0] + i] = S2[i];
		T[0] = MAXSIZE;
		return FALSE;
	}
}

/* ��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ��� */
Status SubString(String Sub, String S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S[0] || len<0 || len>S[0] - pos + 1)
		return ERROR;
	for (i = 1; i <= len; i++)
		Sub[i] = S[pos + i - 1];
	Sub[0] = len;
	return OK;
}

/* �����Ӵ�T������S�е�pos���ַ�֮���λ�á���������,��������ֵΪ0�� */
/* ����,T�ǿ�,1��pos��StrLength(S)�� */
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


/*  TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ��� */
/*  �򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�0 */
int Index2(String S, String T, int pos)
{
	int n, m, i;
	String sub;
	if (pos > 0)
	{
		n = StrLength(S);	/* �õ�����S�ĳ��� */
		m = StrLength(T);	/* �õ��Ӵ�T�ĳ��� */
		i = pos;
		while (i <= n - m + 1)
		{
			SubString(sub, S, i, m);	/* ȡ�����е�i��λ�ó�����T��ȵ��Ӵ���sub */
			if (StrCompare(sub, T) != 0)    /* ������������ */
				++i;
			else 				/* ���������� */
				return i;		/* �򷵻�iֵ */
		}
	}
	return 0;	/* �����Ӵ���T��ȣ�����0 */
}


/*  ��ʼ����: ��S��T����,1��pos��StrLength(S)+1 */
/*  �������: �ڴ�S�ĵ�pos���ַ�֮ǰ���봮T����ȫ���뷵��TRUE,���ֲ��뷵��FALSE */
Status StrInsert(String S, int pos, String T)
{
	int i;
	if (pos<1 || pos>S[0] + 1)
		return ERROR;
	if (S[0] + T[0] <= MAXSIZE)
	{ /*  ��ȫ���� */
		for (i = S[0]; i >= pos; i--)
			S[i + T[0]] = S[i];
		for (i = pos; i<pos + T[0]; i++)
			S[i] = T[i - pos + 1];
		S[0] = S[0] + T[0];
		return TRUE;
	}
	else
	{ /*  ���ֲ��� */
		for (i = MAXSIZE; i <= pos; i--)
			S[i] = S[i - T[0]];
		for (i = pos; i<pos + T[0]; i++)
			S[i] = T[i - pos + 1];
		S[0] = MAXSIZE;
		return FALSE;
	}
}

/*  ��ʼ����: ��S����,1��pos��StrLength(S)-len+1 */
/*  �������: �Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ� */
Status StrDelete(String S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S[0] - len + 1 || len<0)
		return ERROR;
	for (i = pos + len; i <= S[0]; i++)
		S[i - len] = S[i];
	S[0] -= len;
	return OK;
}

/*  ��ʼ����: ��S,T��V����,T�Ƿǿմ����˺����봮�Ĵ洢�ṹ�޹أ� */
/*  �������: ��V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ� */
Status Replace(String S, String T, String V)
{
	int i = 1; /*  �Ӵ�S�ĵ�һ���ַ�����Ҵ�T */
	if (StrEmpty(T)) /*  T�ǿմ� */
		return ERROR;
	do
	{
		i = Index(S, T, i); /*  ���iΪ����һ��i֮���ҵ����Ӵ�T��λ�� */
		if (i) /*  ��S�д��ڴ�T */
		{
			StrDelete(S, i, StrLength(T)); /*  ɾ���ô�T */
			StrInsert(S, i, V); /*  ��ԭ��T��λ�ò��봮V */
			i += StrLength(V); /*  �ڲ���Ĵ�V����������Ҵ�T */
		}
	} while (i);
	return OK;
}

/*  ����ַ���T */
void StrPrint(String T)
{
	int i;
	for (i = 1; i <= T[0]; i++)
		printf("%c", T[i]);
	printf("\n");
}

/*�Ӵ����滻*/
Status RepStr1(String T, int i, int j, String V) {

	int k;
	/*��������*/
	
	String str;

	/*���������Ϊ�մ�*/
	str[0] = 0;

	/*λ���������ȷʱ���ؿմ�*/
	if (i <= 0 || i > T[0] || i + j - 1 > T[0])
		return FALSE; 

	/*iǰ�滻�������*/
	for (k = 1; k <= i-1; k++) 
		str[k] = T[k]; 
	printf("iǰ�滻������������");
	str[0] = i - 1; 
	StrPrint(str);
	
	/*���滻�����������*/
	for (k = 1; k <= V[0]; k++) 
		str[i + k -1] = V[k]; 		
		str[0] = i - 1+V[0];
	printf("\n���滻�������������");
	StrPrint(str);
	
	/*��ǰ���ĺ�����ֵ�������*/
		
	for (int m = i  ; m <= T[0]; m++)
		str[i-1+V[0]+1] = T[m];
		printf("\n��ԭ�������Ӹ��������");
		str[0] = i - 1 + V[0] + T[0] - j; 
		StrPrint(str);

	printf("8.����s�ĵ�2���ַ���ʼ�ĵ�5���ַ��滻�ɴ�s1��������s2-->ִ�����\n");
	printf("******************************************************");
	/*�����s2*/
	printf("\n9.�����s2--->");
	StrPrint(str);


}

int main()
{

	int i, j ,h;
	Status k;
	//char ss;
	String t, s, s1;
	String s2; 
	String s3;
	String s4;


	/*����
	String s3, s4; 
	StrAssign(s3 ,"abcd");
	StrAssign(s4 ,"efg");
	RepStr1(s3, 2, 3, s4); 
	*/

	/*������s*/
	k = StrAssign(s, "abcdefghijklnm");
	if (!k)
	{
		printf("��������MAXSIZE(=%d)\n", MAXSIZE);
		exit(0);
	}
	printf("1.1��s�����ɹ�\n"); 
	

	/*������s1*/

	h = StrAssign(s1, "abcdefghijklnm");
	if (!h)
	{
		printf("��������MAXSIZE(=%d)\n", MAXSIZE);
		exit(0);
	}
	printf("1.2��s1�����ɹ�\n");


	/*�����s*/
	printf("2.�����s--->"); 
	StrPrint(s);

	/*�����s�ĳ���*/	
	int l = StrLength(s); 
	printf("3.�����s�ĳ���:-->%d",l);

	/*�ڴ�s�ĵ�9���ַ�λ���봮s1��������s2*/

		/* �ɴ�s���Ƶ�s2 */
		StrCopy(s2, s); 	

	StrInsert(s2, 9, s1);
	printf("\n4.�ڴ�s�ĵ�9���ַ�λ���봮s1��������s2--->����ɹ�\n"); 

	/*�����s*/
	printf("5.�����s2--->");
	StrPrint(s);

	/*ɾ����s�ĵ�2���ַ���ʼ��5���ַ���������s2*/
	StrDelete(s, 2,5);
	printf("6.��ִ�У�ɾ����s�ĵ�2���ַ���ʼ��5���ַ���������s2\n"); 
	
	/*�����s*/
	printf("7.�����s--->");
	StrPrint(s);

	/*����s�ĵ�2���ַ���ʼ�ĵ�5���ַ��滻�ɴ�s1��������s2*/
	printf("******************************************************\n");
	printf("\n8.����s�ĵ�2���ַ���ʼ�ĵ�5���ַ��滻�ɴ�s1��������s2��ʼִ��\n");
		RepStr1(s,2,5,s1);
	
	/*��ȡ��s�ĵ�2���ַ���ʼ��10���ַ���������s3*/
		printf("10.��ȡ��s�ĵ�2���ַ���ʼ��10���ַ���������s3��ʼִ��\n");

		
		int le = StrLength(s);
		printf("��s�ĳ��ȣ�%d\n", le); 

		StrAssign(s3, "");
		SubString(s3, s, 2, 7); 
		printf("10.��ȡ��s�ĵ�2���ַ���ʼ��10���ַ���������s3ִ�����\n");

		/*�����s3*/
		printf("11.�����s3--->");
		StrPrint(s3);


		/*����s1�ʹ�s2����������������s4*/
		printf("12.����s1�ʹ�s2����������������s4\n");
		StrAssign(s4, "");
		Concat(s4, s1, s2); 
		printf("12.����s1�ʹ�s2����������������s4ִ�����\n");


		/*�����s4*/
		printf("13.�����s4--->");
		StrPrint(s4);


		system("pause"); 

		return 0;

	

}


