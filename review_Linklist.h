#include <iostream>
using namespace std;
#include "datastruct.h"
#include "book_Linklist.h"
#include "user_Linklist.h"


// ��ʼ����������
void InitReviewList(ReviewNode* &L)
{
    L = (ReviewNode*)malloc(sizeof(ReviewNode));
    L->next = nullptr;
}

// ������������
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

// ȫ�ֱ�����������������ID
int global_review_id = 0;

// �����µ�����ID
int generateReviewID() {
    global_review_id += 1;
    return global_review_id;
}

// ��������
void InsertReview(ReviewNode* &L, ReviewNode* p) {
    // ��������ID
    p->review.id = generateReviewID();
    
    p->next = L->next;
    L->next = p;
}

// �ж����������Ƿ�Ϊ��
int ReviewListEmpty(ReviewNode* L)
{
    return (L->next == nullptr);
}

// ������������ĳ���
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

// �����û�id�����id�����������鵽�򷵻�����ָ��
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


// ��������ָ��ɾ������
void DeleteReview(ReviewNode* &L, ReviewNode* p)
{
    ReviewNode* pre = L;
    while (pre->next != p)
        pre = pre->next;
    pre->next = p->next;
    free(p);
}

// ��ID��������,��������ָ��
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

// �޸�����
void ModifyReview(ReviewNode* p)
{
    printf("�������޸ĺ���������: ");
    scanf("%f", &p->review.content);
}


//д����
void WriteReview(User* user_list, BookNode* book_list, int user_id, int book_id, float content) {
    // ���Ҷ�Ӧ���û�
    User* user_node = find_user(user_list, user_id);
    if (user_node == nullptr) {
        cout << "δ�ҵ���Ӧ���û���" << endl;
        return;
    }

    // ���Ҷ�Ӧ���鼮
    Book* book_node = find_book(book_list, book_id);
    if (book_node == nullptr) {
        cout << "δ�ҵ���Ӧ���鼮��" << endl;
        return;
    }

    // �����µ������ڵ�
    ReviewNode* new_review = (ReviewNode*)malloc(sizeof(ReviewNode));
    new_review->review.user_id = user_id;
    new_review->review.book_id = book_id;
    new_review->review.content = content;
    // ����ID��ȫ�ֱ�������
    new_review->review.id = generateReviewID();

    // ���µ������ڵ���뵽�鼮������������
    InsertReview(book_node->reviews, new_review);
}
