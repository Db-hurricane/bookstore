#pragma once
#include <stdio.h>
#include <string.h>
#include "user_Linklist.h"
#include "book_Linklist.h"
#include "review_Linklist.h"
#include <iostream>
using namespace std;

// 交易数据结构
typedef struct {
    int user_id;       // 用户ID
    int book_id;       // 书籍ID
    int quantity;      // 购买数量
    float total_price; // 总价
} Transaction;

// 用户注册函数
void user_register(User* userList)
{
    User newUser;
    printf("请输入您的ID：");
    scanf("%d", &(newUser.id));
    printf("请输入您的用户名：");
    fflush(stdin);
    cin>>newUser.name;
    printf("请输入您的密码：");
    fflush(stdin);
    cin>>newUser.password;
    newUser.money = 0.0;
    newUser.is_admin = 0;
    newUser.is_VIP = 0;
    newUser.borrowed_books = nullptr;
    newUser.next = nullptr;

    // 在链表末尾添加新用户
    User* p = userList;
    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = (User*)malloc(sizeof(User));
    *(p->next) = newUser;
}

// 用户登录函数
User* user_login(User* userList,int &e) {
    int id;
    char password[50];
    printf("请输入您的ID：");
    scanf("%d", &id);
    printf("请输入您的密码：");
    fflush(stdin);
    cin>>password;

    User* p = userList->next;
    while (p != nullptr) {
        if (p->id == id && strcmp(p->password, password) == 0) {
            e = 1;
            return p;
        }
        p = p->next;
    }

    printf("登录失败，ID或密码错误。\n");
    e = 0;
    return nullptr;
}

// 管理员登录函数
User* admin_login(User* userList,int &e) {
    int id;
    char password[50];
    printf("请输入您的管理员ID：");
    scanf("%d", &id);
    printf("请输入您的密码：");
    fflush(stdin);
    cin>>password;
    User* p = userList->next;
    while (p != nullptr) {
        if (p->id == id && strcmp(p->password, password) == 0 && p->is_admin == 1) {
            e = 1;
            return p;
        }
        p = p->next;
    }

    printf("登录失败，ID或密码错误，或者您不是管理员。\n");
    e = 0;
    return nullptr;
}

// 用户充值函数
void user_recharge(User* user) {
	float money;
	printf("请输入您要充值的金额：");
	scanf("%f", &money);
	user->money += money;
	printf("充值成功，您的余额为%.2f元。\n", user->money);
}

//用户注册VIP
void user_registerVIP(User* user) {
	if (user->is_VIP == 1) {
		printf("您已经是VIP用户了。\n");
		return;
	}
	if (user->money < 50) {
		printf("您的余额不足，无法注册VIP。\n");
		return;
	}
	user->money -= 50;
	user->is_VIP = 1;
	printf("注册VIP成功，您的余额为%.2f元。\n", user->money);
}

// 用户购买书籍函数
int buy_books(User*user,BookNode *L)
{
	int book_id;
	int quantity;
	printf("请输入您要购买的书籍ID：");
	scanf("%d", &book_id);
	printf("请输入您要购买的数量：");
	scanf("%d", &quantity);
    Book* book = find_book(L, book_id);
	if (book == nullptr) {
		printf("购买失败，没有找到该书籍。\n");
		return 0;
	}
	if (book->stock < quantity) {
		printf("购买失败，库存不足。\n");
		return 0;
	}
	if (user->money < book->price * quantity) {
		printf("购买失败，您的余额不足。\n");
		return 0;
	}
    if (user->is_VIP == 1)
    {
        user->money -= book->price * quantity*0.95;
        book->stock -= quantity;
        printf("您是VIP用户，购书享受95折，您的余额为%.2f元。\n", user->money);
    }
    else 
    {
        user->money -= book->price * quantity;
        book->stock -= quantity;
        printf("购买成功，您的余额为%.2f元。\n", user->money);
    }
	return 1;
}
