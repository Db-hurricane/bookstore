#pragma once
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

// �û����ݽṹ
typedef struct User
{
    int id;            // �û�ID
    char name[50];     // �û���
    char password[50]; // ����
    int is_admin;      // �Ƿ�Ϊ����Ա
    int is_VIP;        // �Ƿ�ΪVIP
};
User users[50];

// �鼮���ݽṹ
typedef struct {
    int id;            // �鼮ID
    char title[100];   // ����
    char author[50];   // ����
    float price;       // �۸�
    int stock;         // �����
    // �����鼮��Ϣ��������̡��������ڵ�
} Book;

// �������ݽṹ
typedef struct {
    int id;            // ����ID
    int user_id;       // �û�ID
    int book_id;       // �鼮ID
    int quantity;      // ��������
    float total_price; // �ܼ�
    // ����������Ϣ���罻�����ڵ�
} Transaction;

// �������ݽṹ
typedef struct {
    int id;            // ����ID
    int user_id;       // �û�ID
    int book_id;       // �鼮ID
    char content[500]; // ��������
    // ����������Ϣ�������ֵ�
} Review;


//�趨����Ա
void set_admin(User* users[])
{
	User *user=(User*)malloc(sizeof(User));
	user->id=rand();
	char name[50], password[50];
	printf("�������û��������룺\n");
	gets_s(name);
	gets_s(password);
	strncpy(user->name,name,50);
	strncpy(user->password,password,50);
	user->is_admin = 1;
	users[0]=user;
}

//�û�ע�ắ��
int register_user(User* users[])
{
    User *user=(User*)malloc(sizeof(User));
    user->id=rand();
    char name[50], password[50];
    printf("�������û��������룺\n");
    gets_s(name);
    gets_s(password);
    strncpy(user->name,name,50);
    strncpy(user->password,password,50);
    user->is_admin = 0;
}

//�û���¼����
int login_user()
{
	
}

