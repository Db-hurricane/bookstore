#pragma once
#include <iostream>
using namespace std;


// �������ݽṹ
typedef struct Review
{
    int id;            // ����ID
    int user_id;       // �û�ID
    int book_id;       // �鼮ID
    float content; // ��������
};

// ��������ڵ�
typedef struct ReviewNode {
    Review review;                 // ��������
    struct ReviewNode* next;       // ָ����һ���ڵ��ָ��
} ReviewNode;


// �鼮���ݽṹ
typedef struct Book {
    int id;            // �鼮ID
    char title[100];   // ����
    char author[50];   // ����
    float price;       // �۸�
    int stock;         // �����
    mutable ReviewNode* reviews;   // ����
};

//������洢�鼮
typedef struct BookNode {
    Book book;
    struct BookNode* next;
} BookNode;


// ��������鼮�Ľṹ
typedef struct BorrowedBook {
    Book *book;	   // �鼮ID
    struct BorrowedBook* next;
} BorrowedBook;

// �����û��Ľṹ
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