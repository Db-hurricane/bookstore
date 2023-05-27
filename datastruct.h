#pragma once
#include <iostream>
using namespace std;


// 书评数据结构
typedef struct Review
{
    int id;            // 书评ID
    int user_id;       // 用户ID
    int book_id;       // 书籍ID
    float content; // 书评分数
};

// 书评链表节点
typedef struct ReviewNode {
    Review review;                 // 书评数据
    struct ReviewNode* next;       // 指向下一个节点的指针
} ReviewNode;


// 书籍数据结构
typedef struct Book {
    int id;            // 书籍ID
    char title[100];   // 书名
    char author[50];   // 作者
    float price;       // 价格
    int stock;         // 库存量
    mutable ReviewNode* reviews;   // 书评
};

//用链表存储书籍
typedef struct BookNode {
    Book book;
    struct BookNode* next;
} BookNode;


// 定义借阅书籍的结构
typedef struct BorrowedBook {
    Book *book;	   // 书籍ID
    struct BorrowedBook* next;
} BorrowedBook;

// 定义用户的结构
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