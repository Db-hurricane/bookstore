#pragma once
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

// 用户数据结构
typedef struct User
{
    int id;            // 用户ID
    char name[50];     // 用户名
    char password[50]; // 密码
    int is_admin;      // 是否为管理员
    int is_VIP;        // 是否为VIP
};
User users[50];

// 书籍数据结构
typedef struct {
    int id;            // 书籍ID
    char title[100];   // 书名
    char author[50];   // 作者
    float price;       // 价格
    int stock;         // 库存量
    // 其他书籍信息，如出版商、出版日期等
} Book;

// 交易数据结构
typedef struct {
    int id;            // 交易ID
    int user_id;       // 用户ID
    int book_id;       // 书籍ID
    int quantity;      // 购买数量
    float total_price; // 总价
    // 其他交易信息，如交易日期等
} Transaction;

// 书评数据结构
typedef struct {
    int id;            // 书评ID
    int user_id;       // 用户ID
    int book_id;       // 书籍ID
    char content[500]; // 书评内容
    // 其他书评信息，如评分等
} Review;


//设定管理员
void set_admin(User* users[])
{
	User *user=(User*)malloc(sizeof(User));
	user->id=rand();
	char name[50], password[50];
	printf("请输入用户名和密码：\n");
	gets_s(name);
	gets_s(password);
	strncpy(user->name,name,50);
	strncpy(user->password,password,50);
	user->is_admin = 1;
	users[0]=user;
}

//用户注册函数
int register_user(User* users[])
{
    User *user=(User*)malloc(sizeof(User));
    user->id=rand();
    char name[50], password[50];
    printf("请输入用户名和密码：\n");
    gets_s(name);
    gets_s(password);
    strncpy(user->name,name,50);
    strncpy(user->password,password,50);
    user->is_admin = 0;
}

//用户登录函数
int login_user()
{
	
}

