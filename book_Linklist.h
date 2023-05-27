#pragma once
#include <iostream>
using namespace std;
#include "datastruct.h"


// 创建书籍链表
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

// 初始化书籍链表
void InitBookList(BookNode* &L)
{
    L = (BookNode*)malloc(sizeof(BookNode));
    L->next = nullptr;
}

// 销毁书籍链表
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

// 显示书籍链表
void DispBookList(BookNode* L)
{
    BookNode* p = L->next;
    while (p != nullptr) {
        printf("书籍ID: %d, 书名: %s, 作者: %s, 价格: %.2f\n",
            p->book.id, p->book.title, p->book.author, p->book.price);
        p = p->next;
    }
}

// 判断书籍链表是否为空
int BookListEmpty(BookNode* L)
{
    return (L->next == nullptr);
}

// 返回书籍链表的长度
int BookListLength(BookNode* L) {
    int i = 1;
    BookNode* p = L->next;
    while (p->next != nullptr) {
        i++;
        p = p->next;
    }
    return i;
}

// 根据位置查找书籍，查到则返回1
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
        *e = p->book;  // 复制整个结构体
        return 1;
    }
}

//根据书籍名查找书籍在链表的位置，查到则返回位置，否则返回0
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


// 根据书籍名查找书籍id，查到则返回id，否则返回0
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

// 在书籍链表的指定位置插入书籍，插入成功则返回1
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
        s->book = e;  // 复制整个结构体
        s->next = p->next;
        p->next = s;
        return 1;
    }
}

// 删除书籍链表的指定位置的书籍，删除成功则返回1
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
        *e = q->book;  // 复制整个结构体
        free(q);
        return 1;
    }
}

//根据id查找书籍，返回书籍指针
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

// 显示图书信息
void displayBook(const struct Book* book) {
    printf("图书ID: %d\n", book->id);
    printf("书名: %s\n", book->title);
    printf("作者: %s\n", book->author);
    printf("价格: %.2f\n", book->price);
    printf("库存: %d\n", book->stock);
    // 如果有书评，显示书评分数
    ReviewNode* temp = book->reviews;
    while (temp != NULL)
    {
        printf("书评分数 : %.2f\n", temp->review.content);
        temp = temp->next;
    }
}

//添加图书
void add_book(BookNode *bookList)
{
	Book book;
	printf("请输入书籍ID:");
	scanf("%d", &book.id);
	printf("请输入书籍名称:");
    fflush(stdin);
	cin>>book.title;
	printf("请输入书籍作者:");
    fflush(stdin);
	cin>>book.author;
	printf("请输入书籍价格:");
	scanf("%f", &book.price);
	printf("请输入书籍库存:");
	scanf("%d", &book.stock);
    book.reviews = NULL;
	InsertBook(bookList, BookListLength(bookList) + 1, book);
	printf("添加成功\n");
}

// 借阅图书
void borrowBook(struct Book* book) {
    if (book->stock > 0) {
        book->stock--;
        printf("你已成功借阅书籍: %s\n", book->title);
    }
    else {
        printf("书籍: %s 库存不足，无法借阅。\n", book->title);
    }
}

// 归还图书
void returnBook(struct Book* book) {
    book->stock++;
    printf("你已成功归还书籍: %s\n", book->title);
}

// 修改图书ID
void modifyBooksID(struct Book* book, int newID) {
    book->id = newID;
    printf("书籍%s的ID已修改为: %d\n", book->title, book->id);
}

// 修改图书价格
void modifyBooksPrice(struct Book* book, float newPrice) {
    book->price = newPrice;
    printf("书籍%s价格已修改为: %.2f\n", book->title, book->price);
}

//借阅书籍
void borrow_book(BookNode* bookList,User *user)
{
    int id;
    printf("请输入要借阅的书籍ID:");
    scanf("%d", &id);
    Book* book = find_book(bookList, id);
    if (book == nullptr) {
        printf("未找到ID为%d的书籍\n", id);
    }
    else {
        borrowBook(book);
        // 添加借阅记录
        BorrowedBook* borrowedBook = (BorrowedBook*)malloc(sizeof(BorrowedBook));
        borrowedBook->book = book;
        borrowedBook->next = user->borrowed_books;
        user->borrowed_books = borrowedBook;
    }
}

//归还书籍
void return_book(BookNode* bookList,User *user)
{
    int id;
    printf("请输入要归还的书籍ID:");
    scanf("%d", &id);
    Book* book = find_book(bookList, id);
    if (book == nullptr) {
        printf("未找到ID为%d的书籍\n", id);
    }
    else {
        returnBook(book);
        // 删除借阅记录
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
