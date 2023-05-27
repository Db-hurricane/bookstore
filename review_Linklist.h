#include <iostream>
using namespace std;
#include "datastruct.h"
#include "book_Linklist.h"
#include "user_Linklist.h"


// 初始化书评链表
void InitReviewList(ReviewNode* &L)
{
    L = (ReviewNode*)malloc(sizeof(ReviewNode));
    L->next = nullptr;
}

// 销毁书评链表
void DestroyReviewList(ReviewNode* L)
{
    ReviewNode* pre = L, * p = pre->next;
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

// 全局变量，用于生成书评ID
int global_review_id = 0;

// 生成新的书评ID
int generateReviewID() {
    global_review_id += 1;
    return global_review_id;
}

// 插入书评
void InsertReview(ReviewNode* &L, ReviewNode* p) {
    // 生成书评ID
    p->review.id = generateReviewID();
    
    p->next = L->next;
    L->next = p;
}

// 判断书评链表是否为空
int ReviewListEmpty(ReviewNode* L)
{
    return (L->next == nullptr);
}

// 返回书评链表的长度
int ReviewListLength(ReviewNode* L)
{
    int i = 1;
    ReviewNode* p = L->next;
    while (p->next != nullptr) {
        i++;
        p = p->next;
    }
    return i;
}

// 根据用户id和书的id查找书评，查到则返回书评指针
ReviewNode* FindReview(BookNode* L, int user_id, int book_id)
{
    ReviewNode* p=find_book(L,book_id)->reviews;
    while(p!=nullptr)
    {
        if(p->review.user_id==user_id)
            return p;
        p=p->next;
    }
}


// 根据书评指针删除书评
void DeleteReview(ReviewNode* &L, ReviewNode* p)
{
    ReviewNode* pre = L;
    while (pre->next != p)
        pre = pre->next;
    pre->next = p->next;
    free(p);
}

// 按ID查找书评,返回书评指针
ReviewNode* FindReviewByID(ReviewNode* L, int id)
{
    ReviewNode* p = L->next;
    while (p != nullptr)
    {
        if (p->review.id == id)
            return p;
        p = p->next;
    }
    return nullptr;
}

// 修改书评
void ModifyReview(ReviewNode* p)
{
    printf("请输入修改后书评分数: ");
    scanf("%f", &p->review.content);
}


//写书评
void WriteReview(User* user_list, BookNode* book_list, int user_id, int book_id, float content) {
    // 查找对应的用户
    User* user_node = find_user(user_list, user_id);
    if (user_node == nullptr) {
        cout << "未找到对应的用户。" << endl;
        return;
    }

    // 查找对应的书籍
    Book* book_node = find_book(book_list, book_id);
    if (book_node == nullptr) {
        cout << "未找到对应的书籍。" << endl;
        return;
    }

    // 创建新的书评节点
    ReviewNode* new_review = (ReviewNode*)malloc(sizeof(ReviewNode));
    new_review->review.user_id = user_id;
    new_review->review.book_id = book_id;
    new_review->review.content = content;
    // 书评ID由全局变量生成
    new_review->review.id = generateReviewID();

    // 将新的书评节点插入到书籍的书评链表中
    InsertReview(book_node->reviews, new_review);
}
