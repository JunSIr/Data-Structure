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

typedef int Status;

typedef char QElemType; /* QElemType���͸���ʵ������������������Ϊchar */

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
	printf("%c ", c);
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
	printf("\n����Ԫ��Ϊ%c",e); 
	free(t); 
	return OK; 

}

int main()
{
	int i;
	QElemType d;
	LinkQueue q;
	/*1.��ʼ������*/
	i = InitQueue(&q);
	if (i)
		printf("1.�ɹ��ع�����һ���ն���!\n");

	/*2.�п�*/
	printf("2.�Ƿ�ն��У�%d(1:�� 0:��)  ", QueueEmpty(q));


	/*3.���ν�����abcde*/
	EnQueue(&q, 'a');
	EnQueue(&q, 'b');
	EnQueue(&q, 'c');
	EnQueue(&q, 'd');
	EnQueue(&q, 'e');
	printf("\n3.���ν�����abcdeִ�����");

	/*4.����һ��Ԫ�ز����*/
	deQueue(&q, d);
	deQueue(&q, d);

	/*5.���ν�����def*/

	EnQueue(&q, 'd');
	EnQueue(&q, 'e');
	EnQueue(&q, 'f');
	printf("\n5.���ν�����defִ�����");

	/*6.�ͷ�����*/
	DestroyQueue(&q);
	printf("���ٶ��к�,q.front=%u q.rear=%u\n", q.front, q.rear);

	system("pause");

	/*printf("���еĳ���Ϊ%d\n", QueueLength(q));
	printf("����3��Ԫ��(-5,5,10)��,���еĳ���Ϊ%d\n", QueueLength(q));
	printf("�Ƿ�ն��У�%d(1:�� 0:��)  ", QueueEmpty(q));
	printf("���е�Ԫ������Ϊ��");
	QueueTraverse(q);
	i = GetHead(q, &d);
	if (i == OK)
		printf("��ͷԪ���ǣ�%d\n", d);
	DeQueue(&q, &d);
	printf("ɾ���˶�ͷԪ��%d\n", d);
	i = GetHead(q, &d);
	if (i == OK)
		printf("�µĶ�ͷԪ���ǣ�%d\n", d);
	ClearQueue(&q);
	printf("��ն��к�,q.front=%u q.rear=%u q.front->next=%u\n", q.front, q.rear, q.front->next);
	DestroyQueue(&q);
	printf("���ٶ��к�,q.front=%u q.rear=%u\n", q.front, q.rear);

	return 0;
	*/
}


