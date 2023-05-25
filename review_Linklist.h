#pragma once
#include "bookstore.h"
#include "book_Linklist.h"

// 书评数据结构
typedef struct Review
{
    int id;            // 书评IDReview
    int user_id;       // 用户ID
    int book_id;       // 书籍ID
    float content; // 书评分数
};

// 书评链表节点
typedef struct ReviewNode {
    Review review;                 // 书评数据
    struct ReviewNode* next;       // 指向下一个节点的指针
} ReviewNode;

// 创建书评链表
void CreateReviewList(ReviewNode** L, Review a[], int n)
{
    ReviewNode* s;
    *L = (ReviewNode*)malloc(sizeof(ReviewNode));
    (*L)->next = nullptr;
    for (int i = 0; i < n; i++)
    {
        s = (ReviewNode*)malloc(sizeof(ReviewNode));
        s->review = a[i];  // 复制整个结构体
        s->next = (*L)->next;
        (*L)->next = s;
    }
}

// 初始化书评链表
void InitReviewList(ReviewNode** L)
{
    *L = (ReviewNode*)malloc(sizeof(ReviewNode));
    (*L)->next = nullptr;
}

// 销毁书评链表
void DestroyReviewList(ReviewNode** L)
{
    ReviewNode* pre = *L, * p = pre->next;
    while (p != nullptr) {
        free(pre);
        pre = p;
        p = pre->next;
    }
    free(pre);
}

// 显示书评链表
void DispReviewList(ReviewNode* L)
{
    ReviewNode* p = L->next;
    while (p != nullptr)
    {
        printf("书评ID: %d, 用户ID: %d, 书籍ID: %d, 书评分数: %.2f\n",
            p->review.id, p->review.user_id, p->review.book_id, p->review.content);
        p = p->next;
    }
}

// 判断书评链表是否为空
int ReviewListEmpty(ReviewNode* L)
{
    return (L->next == nullptr);
}

// 返回书评链表的长度
int ReviewListLength(ReviewNode* L) {
    int i = 1;
    ReviewNode* p = L->next;
    while (p->next != nullptr) {
        i++;
        p = p->next;
    }
    return i;
}

// 根据位置查找书评，查到则返回1
int GetReview(ReviewNode* L, int i, Review* e)
{
    int j = 0;
    ReviewNode* p = L;
    while (p != nullptr && j < i) {
        j++;
        p = p->next;
    }
    if (p == nullptr) {
        return 0;
    }
    else {
        *e = p->review;  // 复制整个结构体
        return 1;
    }
}


// 根据书评ID查找书评，存在则返回元素位置
int LocateReview(ReviewNode* L, int id)
{
    int i = 0;
    ReviewNode* p = L->next;
    while (p != nullptr && p->review.id != id)
    {
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

// 在书评链表的指定位置插入书评，插入成功则返回1
int InsertReview(ReviewNode* L, int i, Review e)
{
    int j = 0;
    ReviewNode* p = L, * s;
    while (p != nullptr && j < i - 1) {
        j++;
        p = p->next;
    }
    if (p == nullptr) {
        return 0;
    }
    else {
        s = (ReviewNode*)malloc(sizeof(ReviewNode));
        s->review = e;  // 复制整个结构体
        s->next = p->next;
        p->next = s;
        return 1;
    }
}

// 删除书评链表的指定位置的书评，删除成功则返回1
int DelReview(ReviewNode* L, int i, Review* e)
{
    int j = 0;
    ReviewNode* p = L, * q;
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
        *e = q->review;  // 复制整个结构体
        free(q);
        return 1;
    }
}

// 按ID查找书评
void search_review_by_id(ReviewNode* reviewList) {
    int id;
    printf("请输入书评ID：");
    scanf_s("%d", &id);
    Review review;
    int result = GetReview(reviewList, id, &review);
    if (result) {
        // 找到书评
        printf("书评ID: %d, 用户ID: %d, 书籍ID: %d, 书评分数: %.2f\n",
            review.id, review.user_id, review.book_id, review.content);
    }
    else {
        printf("未找到对应的书评。\n");
    }
}

// 修改书评
void modify_review(ReviewNode* reviewList) {
    int id;
    printf("请输入要修改的书评ID：");
    scanf_s("%d", &id);
    Review review;
    int result = GetReview(reviewList, id, &review);
    if (result) {
        // 找到书评
        int newContent;
        printf("请输入新的书评分数：");
        scanf_s("%d", &newContent);
        review.content = newContent;
        printf("书评修改成功。\n");
    }
    else {
        printf("未找到对应的书评。\n");
    }
}

// 删除书评
void delete_review(ReviewNode* reviewList) {
    int id;
    printf("请输入要删除的书评ID：");
    scanf_s("%d", &id);
    Review review;
    int result = DelReview(reviewList, id, &review);
    if (result) {
        printf("书评删除成功。\n");
    }
    else {
        printf("未找到对应的书评。\n");
    }
}

// 生成书评ID
int generate_review_id() {
    static int id = 1;
    return id++;
}


 //写书评
//void write_review(ReviewNode* reviewList, int bookId, int userId,BookNode* bookList) {
//    Book *book;
//    book=find_book(bookList, bookId);
//    if (book!=nullptr) {
//        Review review;
//        review.id = generate_review_id();  // 生成书评ID
//        review.user_id = userId;
//        review.book_id = bookId;
//        printf("请输入书评分数：");
//        scanf_s("%f", &review.content);
//        // 将书评插入到书评链表中
//        int result = InsertReview(reviewList, 1, review);
//        if (result) {
//            printf("书评添加成功。\n");
//        }
//        else {
//            printf("书评添加失败。\n");
//        }
//    }
//    else {
//        printf("未找到对应的书籍。\n");
//    }
//}

