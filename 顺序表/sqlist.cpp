#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;          /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char ElemType;        /* ElemType类型根据实际情况而定，这里假设为int */


Status visit(ElemType c)
{
	printf("%c ", c);
	return OK;
}

typedef struct
{
	ElemType data[MAXSIZE];        /* 数组，存储数据元素 */
	int length;                                /* 线性表当前长度 */
}SqList;

/* 1.初始化顺序线性表 */
Status InitList(SqList *L)
{
	L->length = 0;
	return OK;
}

/* 2.初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(SqList *L, int i, ElemType e)
{
	int k;
	if (L->length == MAXSIZE)  /* 顺序线性表已经满 */
		return ERROR;
	if (i<1 || i>L->length + 1)/* 当i比第一位置小或者比最后一位置后一位置还要大时 */
		return ERROR;

	if (i <= L->length)        /* 若插入数据位置不在表尾 */
	{
		for (k = L->length - 1; k >= i - 1; k--)  /* 将要插入位置之后的数据元素向后移动一位 */
			L->data[k + 1] = L->data[k];
	}
	L->data[i - 1] = e;          /* 将新元素插入 */
	L->length++;

	return OK;
}


/* 3.初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(SqList L)
{
	int i;
	for (i = 0; i<L.length; i++)
		visit(L.data[i]);
	printf("\n");
	return OK;
}

/* 4.初始条件：顺序线性表L已存在。
操作结果：返回L中数据元素个数 */
int ListLength(SqList L)
{
	return L.length;
}

/* 5.初始条件：顺序线性表L已存在。
操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(SqList L)
{
	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}

/* 6.初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值,注意i是指位置，第1个位置的数组是从0开始 */
Status GetElem(SqList L, int i, ElemType *e)
{
	if (L.length == 0 || i<1 || i>L.length)
		return ERROR;
	*e = L.data[i - 1];

	return OK;
}

/* 7.初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
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



/* 初始条件：顺序线性表L已存在。
操作结果：将L重置为空表 */
Status ClearList(SqList *L)
{
	L->length = 0;
	return OK;
}







/* 10.初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(SqList *L, int i, ElemType *e)
{
	int k;
	if (L->length == 0)               /* 线性表为空 */
		return ERROR;
	if (i<1 || i>L->length)         /* 删除位置不正确 */
		return ERROR;
	*e = L->data[i - 1];
	if (i<L->length)                /* 如果删除不是最后位置 */
	{
		for (k = i; k<L->length; k++)/* 将删除位置后继元素前移 */
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
	/*1.初始化*/
	i = InitList(&L);
	printf("1.初始化L后：L.length=%d\n", L.length);

	/*2.依次插入abcde*/
	i = ListInsert(&L, 1, 'e');
	i = ListInsert(&L, 1, 'd');
	i = ListInsert(&L, 1, 'c');
	i = ListInsert(&L, 1, 'b');
	i = ListInsert(&L, 1, 'a');
	printf("2.abcde插入执行完毕\n");

	/*3.输出顺序表*/
	printf("3.在L的表头依次插入a～e后：L.data=\n");
	ListTraverse(L);

	/*4.顺序表长度*/
	printf("4.L.length=%d \n", L.length);

	/*5.判空*/
	i = ListEmpty(L);
	printf("5.L是否空：i=%d(1:是 0:否)\n", i);

	/*6.输出顺序表L的第三个元素*/
	GetElem(L, 3, &e);
	printf("6.第3个元素的值为：%c\n", e);

	/*7.输出顺序表a的位置*/
	int l = LocateElem(L, 'a');
	printf("7.返回元素a的位序：%d\n", l);

	/*8.在第4个元素位置上插入f元素*/
	i = ListInsert(&L, 5, 'f');
	printf("8.在第4个元素位置上插入f元素执行完毕\n", L.length);

	/*9.输出顺序表*/
	printf("9.在L的第4个元素位置上插入f元素后：L.data=\n");
	ListTraverse(L);

	/*10.删除顺序表L的第三个元素*/

	i = ListDelete(&L, 3, &e); /* 删除第j个数据 */
	if (i == ERROR)
		printf("删除第%d个数据失败\n", 3);
	else
		printf("10.删除第个的元素成功\n");

	/*11.输出顺序表L*/
	printf("11.输出顺序表\n");
	ListTraverse(L);

	/*12.释放顺序表*/
	i = ClearList(&L);
	printf("释放顺序表执行完毕\n"); 
	system("pause");
		return 0;
}

/*
	printf("清空L后：L.length=%d\n", L.length);
	i = ListEmpty(L);
	printf("L是否空：i=%d(1:是 0:否)\n", i);

	for (j = 1; j <= 10; j++)
		ListInsert(&L, j, j);
	printf("在L的表尾依次插入1～10后：L.data=");
	ListTraverse(L);

	printf("L.length=%d \n", L.length);

	ListInsert(&L, 1, 0);
	printf("在L的表头插入0后：L.data=");
	ListTraverse(L);
	printf("L.length=%d \n", L.length);

	GetElem(L, 5, &e);
	printf("第5个元素的值为：%d\n", e);
	for (j = 3; j <= 4; j++)
	{
		k = LocateElem(L, j);
		if (k)
			printf("第%d个元素的值为%d\n", k, j);
		else
			printf("没有值为%d的元素\n", j);
	}


	k = ListLength(L); /* k为表长 */
	/*
	for (j = k + 1; j >= k; j--)
	{
		i = ListDelete(&L, j, &e); /* 删除第j个数据 */

		/*
		if (i == ERROR)
			printf("删除第%d个数据失败\n", j);
		else
			printf("删除第%d个的元素值为：%d\n", j, e);
	}
	printf("依次输出L的元素：");
	ListTraverse(L);

	j = 5;
	ListDelete(&L, j, &e); /* 删除第5个数据 */
	/*
	printf("删除第%d个的元素值为：%d\n", j, e);

	printf("依次输出L的元素：");
	ListTraverse(L);

	//构造一个有10个数的Lb
	i = InitList(&Lb);
	for (j = 6; j <= 15; j++)
		i = ListInsert(&Lb, 1, j);

	unionL(&L, Lb);

	printf("依次输出合并了Lb的L的元素：");
	ListTraverse(L);
	*/
	


