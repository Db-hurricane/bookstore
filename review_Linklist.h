#pragma once
#include "bookstore.h"
#include "book_Linklist.h"

// �������ݽṹ
typedef struct Review
{
    int id;            // ����IDReview
    int user_id;       // �û�ID
    int book_id;       // �鼮ID
    float content; // ��������
};

// ��������ڵ�
typedef struct ReviewNode {
    Review review;                 // ��������
    struct ReviewNode* next;       // ָ����һ���ڵ��ָ��
} ReviewNode;

// ������������
void CreateReviewList(ReviewNode** L, Review a[], int n)
{
    ReviewNode* s;
    *L = (ReviewNode*)malloc(sizeof(ReviewNode));
    (*L)->next = nullptr;
    for (int i = 0; i < n; i++)
    {
        s = (ReviewNode*)malloc(sizeof(ReviewNode));
        s->review = a[i];  // ���������ṹ��
        s->next = (*L)->next;
        (*L)->next = s;
    }
}

// ��ʼ����������
void InitReviewList(ReviewNode** L)
{
    *L = (ReviewNode*)malloc(sizeof(ReviewNode));
    (*L)->next = nullptr;
}

// ������������
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

// ��ʾ��������
void DispReviewList(ReviewNode* L)
{
    ReviewNode* p = L->next;
    while (p != nullptr)
    {
        printf("����ID: %d, �û�ID: %d, �鼮ID: %d, ��������: %.2f\n",
            p->review.id, p->review.user_id, p->review.book_id, p->review.content);
        p = p->next;
    }
}

// �ж����������Ƿ�Ϊ��
int ReviewListEmpty(ReviewNode* L)
{
    return (L->next == nullptr);
}

// ������������ĳ���
int ReviewListLength(ReviewNode* L) {
    int i = 1;
    ReviewNode* p = L->next;
    while (p->next != nullptr) {
        i++;
        p = p->next;
    }
    return i;
}

// ����λ�ò����������鵽�򷵻�1
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
        *e = p->review;  // ���������ṹ��
        return 1;
    }
}


// ��������ID���������������򷵻�Ԫ��λ��
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

// �����������ָ��λ�ò�������������ɹ��򷵻�1
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
        s->review = e;  // ���������ṹ��
        s->next = p->next;
        p->next = s;
        return 1;
    }
}

// ɾ�����������ָ��λ�õ�������ɾ���ɹ��򷵻�1
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
        *e = q->review;  // ���������ṹ��
        free(q);
        return 1;
    }
}

// ��ID��������
void search_review_by_id(ReviewNode* reviewList) {
    int id;
    printf("����������ID��");
    scanf_s("%d", &id);
    Review review;
    int result = GetReview(reviewList, id, &review);
    if (result) {
        // �ҵ�����
        printf("����ID: %d, �û�ID: %d, �鼮ID: %d, ��������: %.2f\n",
            review.id, review.user_id, review.book_id, review.content);
    }
    else {
        printf("δ�ҵ���Ӧ��������\n");
    }
}

// �޸�����
void modify_review(ReviewNode* reviewList) {
    int id;
    printf("������Ҫ�޸ĵ�����ID��");
    scanf_s("%d", &id);
    Review review;
    int result = GetReview(reviewList, id, &review);
    if (result) {
        // �ҵ�����
        int newContent;
        printf("�������µ�����������");
        scanf_s("%d", &newContent);
        review.content = newContent;
        printf("�����޸ĳɹ���\n");
    }
    else {
        printf("δ�ҵ���Ӧ��������\n");
    }
}

// ɾ������
void delete_review(ReviewNode* reviewList) {
    int id;
    printf("������Ҫɾ��������ID��");
    scanf_s("%d", &id);
    Review review;
    int result = DelReview(reviewList, id, &review);
    if (result) {
        printf("����ɾ���ɹ���\n");
    }
    else {
        printf("δ�ҵ���Ӧ��������\n");
    }
}

// ��������ID
int generate_review_id() {
    static int id = 1;
    return id++;
}


 //д����
//void write_review(ReviewNode* reviewList, int bookId, int userId,BookNode* bookList) {
//    Book *book;
//    book=find_book(bookList, bookId);
//    if (book!=nullptr) {
//        Review review;
//        review.id = generate_review_id();  // ��������ID
//        review.user_id = userId;
//        review.book_id = bookId;
//        printf("����������������");
//        scanf_s("%f", &review.content);
//        // ���������뵽����������
//        int result = InsertReview(reviewList, 1, review);
//        if (result) {
//            printf("������ӳɹ���\n");
//        }
//        else {
//            printf("�������ʧ�ܡ�\n");
//        }
//    }
//    else {
//        printf("δ�ҵ���Ӧ���鼮��\n");
//    }
//}

