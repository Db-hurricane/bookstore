#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bookstore.h"

typedef struct User {
    int id;
    char name[50];
    char password[50];
    float money;
    int is_admin;
    int is_VIP;
    struct BorrowedBook* borrowed_books; // ָ������鼮������
    struct User* next;
} User;


// �����û�����
void CreateUserList(User** L, User a[], int n) {
    User* s;
    *L = (User*)malloc(sizeof(User));
    (*L)->next = nullptr;
    for (int i = 0; i < n; i++) {
        s = (User*)malloc(sizeof(User));
        *s = a[i];  // ע�������Ǹ��������ṹ��
        s->next = (*L)->next;
        (*L)->next = s;
    }
}

// ��ʼ���û�����
void InitUserList(User** L) {
    *L = (User*)malloc(sizeof(User));
    (*L)->next = nullptr;
}

// �����û�����
void DestroyUserList(User** L) {
    User* pre = *L, * p = pre->next;
    while (p != nullptr) {
        free(pre);
        pre = p;
        p = pre->next;
    }
    free(pre);
}

// ��ʾ�û�����
void DispUserList(User* L) {
    User* p = L->next;
    while (p != nullptr) {
        printf("�û�ID: %d, �û���: %s, ���: %.2f,�Ƿ�ΪVIP: %d\n",
            p->id, p->name, p->money, p->is_VIP);
        p = p->next;
    }
}

// �ж��û������Ƿ�Ϊ��
int UserListEmpty(User* L) {
    return (L->next == nullptr);
}

// �����û�����ĳ���
int UserListLength(User* L) {
    int i = 1;
    User* p = L->next;
    while (p->next != nullptr) {
        i++;
        p = p->next;
    }
    return i;
}

// ����ID�����û����ҵ��󷵻��û�ָ��
User* find_user(User* user, int user_id)
{
    User* p = user->next;
    while (p != nullptr&&p->id!=user_id)
    {
        p = p->next;
    }
    if (p == nullptr)
    {
        return nullptr;
    }
    else
    {
        return p;
    }
}


// �����û�ID�����û��������򷵻�Ԫ��λ��
int LocateUser(User* L, int id) {
    int i = 0;
    User* p = L->next;
    while (p != nullptr && p->id != id) {
        i++;
        p = p->next;
    }
    if (p == nullptr) {
        return 0;
    }
    else {
        return i + 1;
    }
}

// ���û������в����û�
int InsertUser(User* L, int i, User e) {
    int j = 0;
    User* p = L, * s;
    while (p != nullptr && j < i - 1) {
        j++;
        p = p->next;
    }
    if (p == nullptr) {
        return 0;
    }
    else {
        s = (User*)malloc(sizeof(User));
        *s = e;  // ע�������Ǹ��������ṹ��
        s->next = p->next;
        p->next = s;
        return 1;
    }
}

// ɾ����i���û�
int DelUser(User* L, int i, User* e) {
    int j = 0;
    User* p = L, * q;
    while (p->next != nullptr && j < i - 1) 
    {
        j++;
        p = p->next;
    }
    if (p->next == nullptr) 
    {
        return 0;
    }
    else 
    {
        q = p->next;
        p->next = q->next;
        *e = *q;  // ע�������Ǹ��������ṹ��
        free(q);
        return 1;
    }
}

// �����û�IDɾ���û�
void DelUserByID(User* L, int id) 
{
	int i = LocateUser(L, id);
	User* e;
    InitUserList(&e);
	if (i != 0) 
    {
		DelUser(L, i, e);
	}
}

//�޸��û�ID
void change_user_id(User* userList, int new_id,int old_id)
{
    User* p = find_user(userList, old_id);
    p->id = new_id;
}

//�޸��û�VIP״̬
void change_user_VIP(User* userList, int id)
{
    User* p = find_user(userList, id);
    printf("��ѡ��Ҫ�޸ĵ�VIP״̬\n0Ϊ��VIP\n1ΪVIP\n");
    int vip;
    scanf_s("%d", &vip);
    p->is_VIP = vip;
}

//�޸��û����
void change_user_money(User* userList, int id)
{
    User* p = find_user(userList, id);
    printf("�������޸ĺ�����\n");
    int money = scanf_s("%d", &money);
    p->money = money;
}