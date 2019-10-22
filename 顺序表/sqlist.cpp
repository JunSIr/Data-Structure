#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;          /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef char ElemType;        /* ElemType���͸���ʵ������������������Ϊint */


Status visit(ElemType c)
{
	printf("%c ", c);
	return OK;
}

typedef struct
{
	ElemType data[MAXSIZE];        /* ���飬�洢����Ԫ�� */
	int length;                                /* ���Ա�ǰ���� */
}SqList;

/* 1.��ʼ��˳�����Ա� */
Status InitList(SqList *L)
{
	L->length = 0;
	return OK;
}

/* 2.��ʼ������˳�����Ա�L�Ѵ���,1��i��ListLength(L)�� */
/* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
Status ListInsert(SqList *L, int i, ElemType e)
{
	int k;
	if (L->length == MAXSIZE)  /* ˳�����Ա��Ѿ��� */
		return ERROR;
	if (i<1 || i>L->length + 1)/* ��i�ȵ�һλ��С���߱����һλ�ú�һλ�û�Ҫ��ʱ */
		return ERROR;

	if (i <= L->length)        /* ����������λ�ò��ڱ�β */
	{
		for (k = L->length - 1; k >= i - 1; k--)  /* ��Ҫ����λ��֮�������Ԫ������ƶ�һλ */
			L->data[k + 1] = L->data[k];
	}
	L->data[i - 1] = e;          /* ����Ԫ�ز��� */
	L->length++;

	return OK;
}


/* 3.��ʼ������˳�����Ա�L�Ѵ��� */
/* ������������ζ�L��ÿ������Ԫ����� */
Status ListTraverse(SqList L)
{
	int i;
	for (i = 0; i<L.length; i++)
		visit(L.data[i]);
	printf("\n");
	return OK;
}

/* 4.��ʼ������˳�����Ա�L�Ѵ��ڡ�
�������������L������Ԫ�ظ��� */
int ListLength(SqList L)
{
	return L.length;
}

/* 5.��ʼ������˳�����Ա�L�Ѵ��ڡ�
�����������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
Status ListEmpty(SqList L)
{
	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}

/* 6.��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* �����������e����L�е�i������Ԫ�ص�ֵ,ע��i��ָλ�ã���1��λ�õ������Ǵ�0��ʼ */
Status GetElem(SqList L, int i, ElemType *e)
{
	if (L.length == 0 || i<1 || i>L.length)
		return ERROR;
	*e = L.data[i - 1];

	return OK;
}

/* 7.��ʼ������˳�����Ա�L�Ѵ��� */
/* �������������L�е�1����e�����ϵ������Ԫ�ص�λ�� */
/* ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
int LocateElem(SqList L, ElemType e)
{
	int i;
	if (L.length == 0)
		return 0;
	for (i = 0; i<L.length; i++)
	{
		if (L.data[i] == e)
			break;
	}
	if (i >= L.length)
		return 0;

	return i + 1;
}



/* ��ʼ������˳�����Ա�L�Ѵ��ڡ�
�����������L����Ϊ�ձ� */
Status ClearList(SqList *L)
{
	L->length = 0;
	return OK;
}







/* 10.��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
Status ListDelete(SqList *L, int i, ElemType *e)
{
	int k;
	if (L->length == 0)               /* ���Ա�Ϊ�� */
		return ERROR;
	if (i<1 || i>L->length)         /* ɾ��λ�ò���ȷ */
		return ERROR;
	*e = L->data[i - 1];
	if (i<L->length)                /* ���ɾ���������λ�� */
	{
		for (k = i; k<L->length; k++)/* ��ɾ��λ�ú��Ԫ��ǰ�� */
			L->data[k - 1] = L->data[k];
	}
	L->length--;
	return OK;
}

void unionL(SqList *La, SqList Lb)
{
	int La_len, Lb_len, i;
	ElemType e;
	La_len = ListLength(*La);
	Lb_len = ListLength(Lb);
	for (i = 1; i <= Lb_len; i++)
	{
		GetElem(Lb, i, &e);
		if (!LocateElem(*La, e))
			ListInsert(La, ++La_len, e);
	}
}

int main()
{

	SqList L;
	SqList Lb;

	ElemType e;
	Status i;
	int j, k;
	/*1.��ʼ��*/
	i = InitList(&L);
	printf("1.��ʼ��L��L.length=%d\n", L.length);

	/*2.���β���abcde*/
	i = ListInsert(&L, 1, 'e');
	i = ListInsert(&L, 1, 'd');
	i = ListInsert(&L, 1, 'c');
	i = ListInsert(&L, 1, 'b');
	i = ListInsert(&L, 1, 'a');
	printf("2.abcde����ִ�����\n");

	/*3.���˳���*/
	printf("3.��L�ı�ͷ���β���a��e��L.data=\n");
	ListTraverse(L);

	/*4.˳�����*/
	printf("4.L.length=%d \n", L.length);

	/*5.�п�*/
	i = ListEmpty(L);
	printf("5.L�Ƿ�գ�i=%d(1:�� 0:��)\n", i);

	/*6.���˳���L�ĵ�����Ԫ��*/
	GetElem(L, 3, &e);
	printf("6.��3��Ԫ�ص�ֵΪ��%c\n", e);

	/*7.���˳���a��λ��*/
	int l = LocateElem(L, 'a');
	printf("7.����Ԫ��a��λ��%d\n", l);

	/*8.�ڵ�4��Ԫ��λ���ϲ���fԪ��*/
	i = ListInsert(&L, 5, 'f');
	printf("8.�ڵ�4��Ԫ��λ���ϲ���fԪ��ִ�����\n", L.length);

	/*9.���˳���*/
	printf("9.��L�ĵ�4��Ԫ��λ���ϲ���fԪ�غ�L.data=\n");
	ListTraverse(L);

	/*10.ɾ��˳���L�ĵ�����Ԫ��*/

	i = ListDelete(&L, 3, &e); /* ɾ����j������ */
	if (i == ERROR)
		printf("ɾ����%d������ʧ��\n", 3);
	else
		printf("10.ɾ���ڸ���Ԫ�سɹ�\n");

	/*11.���˳���L*/
	printf("11.���˳���\n");
	ListTraverse(L);

	/*12.�ͷ�˳���*/
	i = ClearList(&L);
	printf("�ͷ�˳���ִ�����\n"); 
	system("pause");
		return 0;
}

/*
	printf("���L��L.length=%d\n", L.length);
	i = ListEmpty(L);
	printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n", i);

	for (j = 1; j <= 10; j++)
		ListInsert(&L, j, j);
	printf("��L�ı�β���β���1��10��L.data=");
	ListTraverse(L);

	printf("L.length=%d \n", L.length);

	ListInsert(&L, 1, 0);
	printf("��L�ı�ͷ����0��L.data=");
	ListTraverse(L);
	printf("L.length=%d \n", L.length);

	GetElem(L, 5, &e);
	printf("��5��Ԫ�ص�ֵΪ��%d\n", e);
	for (j = 3; j <= 4; j++)
	{
		k = LocateElem(L, j);
		if (k)
			printf("��%d��Ԫ�ص�ֵΪ%d\n", k, j);
		else
			printf("û��ֵΪ%d��Ԫ��\n", j);
	}


	k = ListLength(L); /* kΪ�� */
	/*
	for (j = k + 1; j >= k; j--)
	{
		i = ListDelete(&L, j, &e); /* ɾ����j������ */

		/*
		if (i == ERROR)
			printf("ɾ����%d������ʧ��\n", j);
		else
			printf("ɾ����%d����Ԫ��ֵΪ��%d\n", j, e);
	}
	printf("�������L��Ԫ�أ�");
	ListTraverse(L);

	j = 5;
	ListDelete(&L, j, &e); /* ɾ����5������ */
	/*
	printf("ɾ����%d����Ԫ��ֵΪ��%d\n", j, e);

	printf("�������L��Ԫ�أ�");
	ListTraverse(L);

	//����һ����10������Lb
	i = InitList(&Lb);
	for (j = 6; j <= 15; j++)
		i = ListInsert(&Lb, 1, j);

	unionL(&L, Lb);

	printf("��������ϲ���Lb��L��Ԫ�أ�");
	ListTraverse(L);
	*/
	


