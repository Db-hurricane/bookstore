#pragma once
#include <iostream>
using namespace std;
#include "datastruct.h"


// �����鼮����
void CreateBookList(BookNode* &L, Book a[], int n)
{
    BookNode* s;
    for(int i=0;i<n;i++)
    {
    	s = (BookNode*)malloc(sizeof(BookNode));
		s->book = a[i];
		s->next = L->next;
		L->next = s;
    }
}

// ��ʼ���鼮����
void InitBookList(BookNode* &L)
{
    L = (BookNode*)malloc(sizeof(BookNode));
    L->next = nullptr;
}

// �����鼮����
void DestroyBookList(BookNode* L)
{
    BookNode* pre = L, * p = pre->next;
    while (p != nullptr) {
        free(pre);
        pre = p;
        p = pre->next;
    }
    free(pre);
}

// ��ʾ�鼮����
void DispBookList(BookNode* L)
{
    BookNode* p = L->next;
    while (p != nullptr) {
        printf("�鼮ID: %d, ����: %s, ����: %s, �۸�: %.2f\n",
            p->book.id, p->book.title, p->book.author, p->book.price);
        p = p->next;
    }
}

// �ж��鼮�����Ƿ�Ϊ��
int BookListEmpty(BookNode* L)
{
    return (L->next == nullptr);
}

// �����鼮����ĳ���
int BookListLength(BookNode* L) {
    int i = 1;
    BookNode* p = L->next;
    while (p->next != nullptr) {
        i++;
        p = p->next;
    }
    return i;
}

// ����λ�ò����鼮���鵽�򷵻�1
int GetBook(BookNode* L, int i, Book* e)
{
    int j = 0;
    BookNode* p = L;
    while (p != nullptr && j < i) {
        j++;
        p = p->next;
    }
    if (p == nullptr) {
        return 0;
    }
    else {
        *e = p->book;  // ���������ṹ��
        return 1;
    }
}

//�����鼮�������鼮�������λ�ã��鵽�򷵻�λ�ã����򷵻�0
int LocBook_position(BookNode* L, char title[])
{
	int i = 1;
	BookNode* p = L->next;
	while (p != nullptr && strcmp(p->book.title, title) != 0) {
		i++;
		p = p->next;
	}
	if (p == nullptr) {
		return 0;
	}
	else {
		return i-1;
	}
}


// �����鼮�������鼮id���鵽�򷵻�id�����򷵻�0
int LocateBook(BookNode* L, char title[])
{
    int i;
	BookNode* p = L->next;
	while (p != nullptr && strcmp(p->book.title, title) != 0)
	{
        i=p->book.id;
		p = p->next;
	}
	if (p == nullptr)
	{
		return 0;
	}
	else
	{
		return i-1;
	}
}

// ���鼮�����ָ��λ�ò����鼮������ɹ��򷵻�1
int InsertBook(BookNode* L, int i, Book e)
{
    int j = 0;
    BookNode* p = L, * s;
    while (p != nullptr && j < i - 1) {
        j++;
        p = p->next;
    }
    if (p == nullptr) {
        return 0;
    }
    else {
        s = (BookNode*)malloc(sizeof(BookNode));
        s->book = e;  // ���������ṹ��
        s->next = p->next;
        p->next = s;
        return 1;
    }
}

// ɾ���鼮�����ָ��λ�õ��鼮��ɾ���ɹ��򷵻�1
int DelBook(BookNode* L, int i, Book* e)
{
    int j = 0;
    BookNode* p = L, * q;
    while (p->next != nullptr && j < i - 1) {
        j++;
        p = p->next;
    }
    if (p->next == nullptr) {
        return 0;
    }
    else {
        q = p->next;
        p->next = q->next;
        *e = q->book;  // ���������ṹ��
        free(q);
        return 1;
    }
}

//����id�����鼮�������鼮ָ��
Book *find_book(BookNode* L, int id)
{
    BookNode* p = L->next;
	while (p != nullptr && p->book.id != id)
	{
		p = p->next;
	}
	if (p == nullptr) 
    {
		return nullptr;
	}
	else
    {
        return &p->book;
	}
}

// ��ʾͼ����Ϣ
void displayBook(const struct Book* book) {
    printf("ͼ��ID: %d\n", book->id);
    printf("����: %s\n", book->title);
    printf("����: %s\n", book->author);
    printf("�۸�: %.2f\n", book->price);
    printf("���: %d\n", book->stock);
    // �������������ʾ��������
    ReviewNode* temp = book->reviews;
    while (temp != NULL)
    {
        printf("�������� : %.2f\n", temp->review.content);
        temp = temp->next;
    }
}

//���ͼ��
void add_book(BookNode *bookList)
{
	Book book;
	printf("�������鼮ID:");
	scanf("%d", &book.id);
	printf("�������鼮����:");
    fflush(stdin);
	cin>>book.title;
	printf("�������鼮����:");
    fflush(stdin);
	cin>>book.author;
	printf("�������鼮�۸�:");
	scanf("%f", &book.price);
	printf("�������鼮���:");
	scanf("%d", &book.stock);
    book.reviews = NULL;
	InsertBook(bookList, BookListLength(bookList) + 1, book);
	printf("��ӳɹ�\n");
}

// ����ͼ��
void borrowBook(struct Book* book) {
    if (book->stock > 0) {
        book->stock--;
        printf("���ѳɹ������鼮: %s\n", book->title);
    }
    else {
        printf("�鼮: %s ��治�㣬�޷����ġ�\n", book->title);
    }
}

// �黹ͼ��
void returnBook(struct Book* book) {
    book->stock++;
    printf("���ѳɹ��黹�鼮: %s\n", book->title);
}

// �޸�ͼ��ID
void modifyBooksID(struct Book* book, int newID) {
    book->id = newID;
    printf("�鼮%s��ID���޸�Ϊ: %d\n", book->title, book->id);
}

// �޸�ͼ��۸�
void modifyBooksPrice(struct Book* book, float newPrice) {
    book->price = newPrice;
    printf("�鼮%s�۸����޸�Ϊ: %.2f\n", book->title, book->price);
}

//�����鼮
void borrow_book(BookNode* bookList,User *user)
{
    int id;
    printf("������Ҫ���ĵ��鼮ID:");
    scanf("%d", &id);
    Book* book = find_book(bookList, id);
    if (book == nullptr) {
        printf("δ�ҵ�IDΪ%d���鼮\n", id);
    }
    else {
        borrowBook(book);
        // ��ӽ��ļ�¼
        BorrowedBook* borrowedBook = (BorrowedBook*)malloc(sizeof(BorrowedBook));
        borrowedBook->book = book;
        borrowedBook->next = user->borrowed_books;
        user->borrowed_books = borrowedBook;
    }
}

//�黹�鼮
void return_book(BookNode* bookList,User *user)
{
    int id;
    printf("������Ҫ�黹���鼮ID:");
    scanf("%d", &id);
    Book* book = find_book(bookList, id);
    if (book == nullptr) {
        printf("δ�ҵ�IDΪ%d���鼮\n", id);
    }
    else {
        returnBook(book);
        // ɾ�����ļ�¼
        BorrowedBook* p = user->borrowed_books, * q;
        if (p->book == book) {
            user->borrowed_books = p->next;
            free(p);
        }
        else {
            while (p->next != nullptr && p->next->book != book) {
                p = p->next;
            }
            if (p->next != nullptr) {
                q = p->next;
                p->next = q->next;
                free(q);
            }
        }
    }
}
