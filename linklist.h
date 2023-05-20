#include <stdio.h>
#include <malloc.h>



typedef struct LinkNode
{
	int data;
	LinkNode* next;
}LinkNode;

//����������
void CreateList(LinkNode*& L, ElemType a[], int n)
{
	LinkNode* s;
	L = (LinkNode*)malloc(sizeof(LinkNode));
	L->next = nullptr;
	for (int i = 0; i < n; i++)
	{
		s = (LinkNode*)malloc(sizeof(LinkNode));
		s->data = a[i];
		s->next = L->next;
		L->next = s;
	}
}

//��ʼ��������
void InitList(LinkNode*& L)
{
	L = (LinkNode*)malloc(sizeof(LinkNode));
	L->next = nullptr;
}

//���ٵ�����
void DestroyList(LinkNode*& L)
{
	LinkNode* pre = L, * p = pre->next;
	while (p != nullptr)
	{
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(pre);
}

//��ʾ������
void DispList(LinkNode* L)
{
	LinkNode* p = L->next;
	while (p != nullptr)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

//�жϵ������Ƿ�ձ�
bool ListEmpty(LinkNode* L)
{
	return (L->next == nullptr);
}

//���ص�����ĳ���
int ListLength(LinkNode* L)
{
	int i = 1;
	LinkNode* p = L->next;
	while (p->next != nullptr)
	{
		i++;
		p = p->next;
	}
	return i;
}


//����λ�ò��ұ�Ԫ�أ��鵽�򷵻�1
bool GetElem(LinkNode* L, int i, ElemType& e)
{
	int j = 0;
	LinkNode* p = L;
	while (p != nullptr && j < i)
	{
		j++;
		p = p->next;
	}
	if (p == nullptr)
		return false;
	else
	{
		e = p->data;
		return true;
	}
}

//�������ݲ��ұ�Ԫ�أ������򷵻�Ԫ��λ��
int LocateElem(LinkNode* L, ElemType e)
{
	int i = 0;
	LinkNode* p = L->next;
	while (p != nullptr && p->data != e)
	{
		i++;
		p = p->next;
	}
	if (p == nullptr)
		return 0;
	else
		return i + 1;
}

//�ڵ������в���Ԫ��
bool InsertElem(LinkNode* L, int i, ElemType e)
{
	int j = 0;
	LinkNode* p = L, * s;
	while (p != nullptr && j < i - 1)
	{
		j++;
		p = p->next;
	}
	if (p == nullptr)
		return false;
	else
	{
		s = (LinkNode*)malloc(sizeof(LinkNode));
		s->data = e;
		s->next = p->next;
		p->next = s;
		return true;
	}
}

//ɾ����i��Ԫ��
bool DelElem(LinkNode* L, int i, ElemType e)
{
	int j = 0;
	LinkNode* p = L, * q;
	while (p->next != nullptr && j < i - 1)
	{
		j++;
		p = p->next;
	}
	if (p->next == nullptr)
		return false;
	else
	{
		q = p->next;
		p->next = q->next;
		e = q->data;
		free(q);
		return true;
	}
}