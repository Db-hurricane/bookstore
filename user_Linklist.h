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
    struct BorrowedBook* borrowed_books; // 指向借阅书籍的链表
    struct User* next;
} User;


// 创建用户链表
void CreateUserList(User** L, User a[], int n) {
    User* s;
    *L = (User*)malloc(sizeof(User));
    (*L)->next = nullptr;
    for (int i = 0; i < n; i++) {
        s = (User*)malloc(sizeof(User));
        *s = a[i];  // 注意这里是复制整个结构体
        s->next = (*L)->next;
        (*L)->next = s;
    }
}

// 初始化用户链表
void InitUserList(User** L) {
    *L = (User*)malloc(sizeof(User));
    (*L)->next = nullptr;
}

// 销毁用户链表
void DestroyUserList(User** L) {
    User* pre = *L, * p = pre->next;
    while (p != nullptr) {
        free(pre);
        pre = p;
        p = pre->next;
    }
    free(pre);
}

// 显示用户链表
void DispUserList(User* L) {
    User* p = L->next;
    while (p != nullptr) {
        printf("用户ID: %d, 用户名: %s, 余额: %.2f,是否为VIP: %d\n",
            p->id, p->name, p->money, p->is_VIP);
        p = p->next;
    }
}

// 判断用户链表是否为空
int UserListEmpty(User* L) {
    return (L->next == nullptr);
}

// 返回用户链表的长度
int UserListLength(User* L) {
    int i = 1;
    User* p = L->next;
    while (p->next != nullptr) {
        i++;
        p = p->next;
    }
    return i;
}

// 根据ID查找用户，找到后返回用户指针
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


// 根据用户ID查找用户，存在则返回元素位置
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

// 在用户链表中插入用户
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
        *s = e;  // 注意这里是复制整个结构体
        s->next = p->next;
        p->next = s;
        return 1;
    }
}

// 删除第i个用户
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
        *e = *q;  // 注意这里是复制整个结构体
        free(q);
        return 1;
    }
}

// 根据用户ID删除用户
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

//修改用户ID
void change_user_id(User* userList, int new_id,int old_id)
{
    User* p = find_user(userList, old_id);
    p->id = new_id;
}

//修改用户VIP状态
void change_user_VIP(User* userList, int id)
{
    User* p = find_user(userList, id);
    printf("请选择要修改的VIP状态\n0为非VIP\n1为VIP\n");
    int vip;
    scanf_s("%d", &vip);
    p->is_VIP = vip;
}

//修改用户余额
void change_user_money(User* userList, int id)
{
    User* p = find_user(userList, id);
    printf("请输入修改后的余额\n");
    int money = scanf_s("%d", &money);
    p->money = money;
}