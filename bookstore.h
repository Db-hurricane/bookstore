#pragma once
#include <stdio.h>
#include <string.h>
#include "user_Linklist.h"
#include "book_Linklist.h"
#include "review_Linklist.h"
#include <iostream>
using namespace std;

// �������ݽṹ
typedef struct {
    int user_id;       // �û�ID
    int book_id;       // �鼮ID
    int quantity;      // ��������
    float total_price; // �ܼ�
} Transaction;

// �û�ע�ắ��
void user_register(User* userList)
{
    User newUser;
    printf("����������ID��");
    scanf("%d", &(newUser.id));
    printf("�����������û�����");
    fflush(stdin);
    cin>>newUser.name;
    printf("�������������룺");
    fflush(stdin);
    cin>>newUser.password;
    newUser.money = 0.0;
    newUser.is_admin = 0;
    newUser.is_VIP = 0;
    newUser.borrowed_books = nullptr;
    newUser.next = nullptr;

    // ������ĩβ������û�
    User* p = userList;
    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = (User*)malloc(sizeof(User));
    *(p->next) = newUser;
}

// �û���¼����
User* user_login(User* userList,int &e) {
    int id;
    char password[50];
    printf("����������ID��");
    scanf("%d", &id);
    printf("�������������룺");
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

    printf("��¼ʧ�ܣ�ID���������\n");
    e = 0;
    return nullptr;
}

// ����Ա��¼����
User* admin_login(User* userList,int &e) {
    int id;
    char password[50];
    printf("���������Ĺ���ԱID��");
    scanf("%d", &id);
    printf("�������������룺");
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

    printf("��¼ʧ�ܣ�ID��������󣬻��������ǹ���Ա��\n");
    e = 0;
    return nullptr;
}

// �û���ֵ����
void user_recharge(User* user) {
	float money;
	printf("��������Ҫ��ֵ�Ľ�");
	scanf("%f", &money);
	user->money += money;
	printf("��ֵ�ɹ����������Ϊ%.2fԪ��\n", user->money);
}

//�û�ע��VIP
void user_registerVIP(User* user) {
	if (user->is_VIP == 1) {
		printf("���Ѿ���VIP�û��ˡ�\n");
		return;
	}
	if (user->money < 50) {
		printf("�������㣬�޷�ע��VIP��\n");
		return;
	}
	user->money -= 50;
	user->is_VIP = 1;
	printf("ע��VIP�ɹ����������Ϊ%.2fԪ��\n", user->money);
}

// �û������鼮����
int buy_books(User*user,BookNode *L)
{
	int book_id;
	int quantity;
	printf("��������Ҫ������鼮ID��");
	scanf("%d", &book_id);
	printf("��������Ҫ�����������");
	scanf("%d", &quantity);
    Book* book = find_book(L, book_id);
	if (book == nullptr) {
		printf("����ʧ�ܣ�û���ҵ����鼮��\n");
		return 0;
	}
	if (book->stock < quantity) {
		printf("����ʧ�ܣ���治�㡣\n");
		return 0;
	}
	if (user->money < book->price * quantity) {
		printf("����ʧ�ܣ��������㡣\n");
		return 0;
	}
    if (user->is_VIP == 1)
    {
        user->money -= book->price * quantity*0.95;
        book->stock -= quantity;
        printf("����VIP�û�����������95�ۣ��������Ϊ%.2fԪ��\n", user->money);
    }
    else 
    {
        user->money -= book->price * quantity;
        book->stock -= quantity;
        printf("����ɹ����������Ϊ%.2fԪ��\n", user->money);
    }
	return 1;
}
