#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"
#include"string.h"
#include<iostream>

using namespace std; 

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;

typedef int QElemType; /* QElemType���͸���ʵ������������������Ϊchar */

typedef struct QNode	/* ���ṹ */
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct			/* ���е�����ṹ */
{
	QueuePtr front, rear; /* ��ͷ����βָ�� */
}LinkQueue;

Status visit(QElemType c)
{
	printf("%d ", c);
	return OK;
}

/* ����һ���ն���Q */
Status InitQueue(LinkQueue *Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(OVERFLOW);
	Q->front->next = NULL;
	return OK;
}

/* ���ٶ���Q */
Status DestroyQueue(LinkQueue *Q)
{
	while (Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}

/* ��Q��Ϊ�ն��� */
Status ClearQueue(LinkQueue *Q)
{
	QueuePtr p, q;
	Q->rear = Q->front;
	p = Q->front->next;
	Q->front->next = NULL;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	return OK;
}

/* ��QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

/* ����еĳ��� */
int QueueLength(LinkQueue Q)
{
	int i = 0;
	QueuePtr p;
	p = Q.front;
	while (Q.rear != p)
	{
		i++;
		p = p->next;
	}
	return i;
}

/* �����в���,����e����Q�Ķ�ͷԪ��,������OK,���򷵻�ERROR */
Status GetHead(LinkQueue Q, QElemType *e)
{
	QueuePtr p;
	if (Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;
	*e = p->data;
	return OK;
}


/* ����Ԫ��eΪQ���µĶ�βԪ�� */
Status EnQueue(LinkQueue *Q, QElemType e)
{
	QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
	if (!s) /* �洢����ʧ�� */
		exit(OVERFLOW);
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;	/* ��ӵ��Ԫ��e���½��s��ֵ��ԭ��β���ĺ�̣���ͼ�Т� */
	Q->rear = s;		/* �ѵ�ǰ��s����Ϊ��β��㣬rearָ��s����ͼ�Т� */
	return OK;
}

/* �����в���,ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK,���򷵻�ERROR */
Status DeQueue(LinkQueue *Q, QElemType *e)
{
	QueuePtr p;
	if (Q->front == Q->rear)
		return ERROR;
	p = Q->front->next;		/* ����ɾ���Ķ�ͷ����ݴ��p����ͼ�Т� */
	*e = p->data;				/* ����ɾ���Ķ�ͷ����ֵ��ֵ��e */
	Q->front->next = p->next;/* ��ԭ��ͷ���ĺ��p->next��ֵ��ͷ����̣���ͼ�Т� */
	if (Q->rear == p)		/* ����ͷ���Ƕ�β����ɾ����rearָ��ͷ��㣬��ͼ�Т� */
		Q->rear = Q->front;
	visit(p->data);
	free(p);
	return OK;
}

/* �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ����� */
Status QueueTraverse(LinkQueue Q)
{
	QueuePtr p;
	p = Q.front->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}
//*&��ָ�����͵�����
/*������*/
Status deQueue(LinkQueue *q, QElemType &e)
{
	QueuePtr t;
	if (q->rear == NULL)
		return FALSE; 
	t = q->front;            /*tָ���׽��*/
	if (q->front == q->rear)	/*ԭ����ֻ��һ�����ݽ��ʱ*/
		q->front = q->rear = NULL;
	else                                /*ԭ����ֻ�������������������ݽ��ʱ*/
		q->front = q->front->next; 
	e = t->data; 
	printf("\n����Ԫ��Ϊ%d",e); 
	free(t); 
	return OK; 

}

Status AllDeQueue(LinkQueue *Q, QElemType *e)
{
	while (Q->front != Q->rear)
	{
		QueuePtr p;
		/*
		*if (Q->front == Q->rear)
			return ERROR;
		*/
		
		p = Q->front->next;		/* ����ɾ���Ķ�ͷ����ݴ��p����ͼ�Т� */
		*e = p->data;				/* ����ɾ���Ķ�ͷ����ֵ��ֵ��e */
		Q->front->next = p->next;/* ��ԭ��ͷ���ĺ��p->next��ֵ��ͷ����̣���ͼ�Т� */
		if (Q->rear == p)		/* ����ͷ���Ƕ�β����ɾ����rearָ��ͷ��㣬��ͼ�Т� */
			Q->rear = Q->front;
		visit(p->data);
		free(p);

	}
	
	return OK;
}

int  showmenu() {

	/*���ܲ˵������ѡ������*/
	int w;
	cout << "\n\n*********��ӭʹ�þ�����п���ϵͳ*********\n";
	cout << "1-�Ŷ�\n2-����\n3-�鿴�Ŷ�\n4-�����Ŷӣ��������ξ���\n5-�°�";
	cout << "\n*****************************************";
	cout << "\n���������ѡ��";
	

	cin >> w;
	return w; 
}



int  operation(int w, LinkQueue *q, QElemType &d) {
	
	int num; 

	if (w == 1) {
		/*����1.�Ŷ�--->�����ŶӲ��˵Ĳ����ţ����뵽�����ŶӶ�����*/
		cin >> num;
		EnQueue(q, num);
		printf("��ӳɹ�\n\n\n");
	}
	else if (w == 2) {

		printf("����һλ���˾��");
		DeQueue(q, &d);
	}
	else if (w == 3) {

		printf("��ʾ���в����ţ�");
		QueueTraverse(*q);
	}
	else if (w == 4) {

		printf("�����²���ֱ�Ӿ��");
		QueueTraverse(*q);
		AllDeQueue(q, &d); 
		printf("\n���ϲ�����ȫ������");	
	}
	else if (w == 5) {
		DestroyQueue(q);
		printf("�����Ѿ��ͷţ�����ֹͣ����");
		
	}


	return w; 
}

int main()
{
	int i;
	int num; 
	
	
	QElemType d;
	LinkQueue q;
	/*��ʼ������*/
	i = InitQueue(&q);

	/*���ܲ˵������ѡ������*/
	int w = 0;
	while (0<=w<5)
	{
		w = showmenu();
		operation(w, &q, d);
	}
	
	


	system("pause");

	/*
	*/
}


