#include "bookstore.h"

//��������
void user_operations(User* users, BookNode* bookList);
void admin_operations(User* users, BookNode* bookList);

//��ʼ�������û�����
void create_initial_data(User *userList)
{

    // ��������Ա�˻�
    User admin = { 0, "admin", "0", 0.0, 1, 0, nullptr, nullptr };
    InsertUser(userList, 1, admin);

    // �������3���û�
    User users[3] = {
        {1, "user1", "1", 300.0, 0, 0, nullptr, nullptr},
        {2, "user2", "2", 200.0, 0, 1, nullptr, nullptr},
        {3, "user3", "3", 300.0, 0, 0, nullptr, nullptr},
    };
    InsertUser(userList, 2, users[0]);
    InsertUser(userList, 3, users[1]);
    InsertUser(userList, 4, users[2]);
}

//��ʼ�������鼮����
void create_initial_book(BookNode *bookList)
{
    // Initialize some books
    Book books[10] = {
        {1, "��¥��", "��ѩ��", 39.99f, rand() % 5, nullptr},
        {2, "���μ�", "��ж�", 49.99f, rand() % 5, nullptr},
        {3, "��������", "�޹���", 59.99f, rand() % 5, nullptr},
        {4, "ˮ䰴�", "ʩ����", 49.99f, rand() % 5, nullptr},
        {5, "��ķ����", "������ɯʿ����", 29.99f, rand() % 5, nullptr},
        {6, "�򡤰�", "����١�������", 39.99f, rand() % 5, nullptr},
        {7, "������ƫ��", "�򡤰�˹͡", 49.99f, rand() % 5, nullptr},
        {8, "����¶�", "�����ǡ������˹", 59.99f, rand() % 5, nullptr},
        {9, "Ʈ", "������ء����ж�", 69.99f, rand() % 5, nullptr},
        {10, "1984", "���Ρ�������", 39.99f, rand() % 5, nullptr}
    };

    // Create the book list
    CreateBookList(bookList, books, 10);
}

//��ʼ��������������
void create_initial_review(BookNode *&bookList)
{
    //��ʼ����������
    Review reviews[10] =
    {
        {1, rand()%3, 1, 8.5f},
        {2, rand()%3, 2, 8.0f},
        {3, rand()%3, 3, 8.5f},
        {4, rand()%3, 4, 9.0f},
        {5, rand()%3, 5, 9.5f},
        {6, rand()%3, 6, 8.0f},
        {7, rand()%3, 7, 9.5f},
        {8, rand()%3, 8, 8.0f},
        {9, rand()%3, 9, 7.5f},
        {10, rand()%3, 10, 9.0f}
    };
    for(int i = 0; i < 10; i++)
    {
        Book *p=find_book(bookList, reviews[i].book_id);
        if(p!=nullptr)
        {
            if (p->reviews == nullptr) {
                InitReviewList(p->reviews);
            }
            ReviewNode *q = new ReviewNode;
            q->review = reviews[i];
            q->next = nullptr;
            InsertReview(p->reviews, q);
        }
    }
}


// ������
int main() {
    User* currentUser = nullptr;
    InitUserList(&currentUser);
    BookNode* bookList=nullptr;
    InitBookList(bookList);
    create_initial_data(currentUser);
    create_initial_book(bookList);
    create_initial_review(bookList);

    while (1) {
        printf("��ѡ�������\n");
        printf("1. ע��\n");
        printf("2. �û���¼\n");
        printf("3. ����Ա��¼\n");
        printf("4. �˳�\n");

        int choice;
        scanf("%d", &choice);
        int e = 0;

        switch (choice) {
        case 1:
	        {
		        // ע�����û�
        		user_register(currentUser);
        		break;
	        }
        case 2:
	        {
		        // �û���¼
        		user_login(currentUser,e);
                if(e == 1) {
                    user_operations(currentUser, bookList);
				}
                else
                {
                    printf("��¼ʧ�ܣ������µ�¼��\n");
                }
        		break;
	        }
        case 3:
	        {
		        // ����Ա��¼
        		admin_login(currentUser,e);
                if (e == 1) {
                    admin_operations(currentUser, bookList);
                }
                else
                {
                    printf("��¼ʧ�ܣ������µ�¼��\n");
                }
        		break;
	        }
        case 4:
	        {
		        // �˳�����
        		exit(0);
	        }
        default:
	        {
		        printf("��Ч��ѡ�������ѡ��\n");
        		break;
	        }
        }
    }

    return 0;
}

// �û�����
void user_operations(User* user,BookNode *bookList) {
    while (1) {
        printf("��ѡ�������\n");
        printf("1. �����鼮\n");
        printf("2. �����鼮��黹�鼮\n");
        printf("3. �����鼮\n");
        printf("4. д����\n");
        printf("5. ע���Ա\n");
        printf("6. ��ֵ�˻�\n");
        printf("7. �˳�\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 1:
	        {
		        // �����鼮
        		printf("������Ҫ���ҵ��鼮");
        		char title[100];
                fflush(stdin);
                cin>>title;
        		int findbook_id=LocateBook(bookList, title);
        		Book* findbook = find_book(bookList, findbook_id);
                displayBook(findbook);
        		break;
	        }
        case 2:
	        {
                int borrow_or_return;
                printf("��ѡ�������\n");
                printf("1. �����鼮\n");
                printf("2. �黹�鼮\n");
                scanf("%d", &borrow_or_return);
                if(borrow_or_return==1)
                {
                    // �����鼮
                    borrow_book(bookList, user);
                }
                else if(borrow_or_return==2)
                {
                    // �黹�鼮
                    return_book(bookList, user);
                }
                else
                {
                    printf("��Ч��ѡ�������ѡ��\n");
                }
        		break;
	        }
        case 3:
	        {
		        // �����鼮
		        buy_books(user, bookList);
        		break;
	        }
        case 4:
	        {
		        // д����
                int id;
                printf("�������id");
                scanf("%d", &id);
                printf("������Ҫд�������鼮id");
                int book_id;
                scanf("%d", &book_id);
                float content;
                printf("��������������");
                scanf("%f", &content);
                WriteReview(user, bookList,id,book_id,content);
        		break;
	        }
        case 5:
	        {
		        // ע���Ա
        		user_registerVIP(user);
        		break;
	        }
        case 6:
	        {
		        // ��ֵ�˻�
				user_recharge(user);
				break;
	        }
        case 7:
	        {
		        // �˳��û���������
        		return;
	        }
        default:
	        {
		        printf("��Ч��ѡ�������ѡ��\n");
        		break;
	        }
        }
    }
}

// ����Ա����
void admin_operations(User* userlist,BookNode *BookList) {
    while (1) {
        printf("��ѡ�������\n");
        printf("1. �����鼮\n");
        printf("2. �޸��鼮\n");
        printf("3. �޸��û���Ϣ\n");
        printf("4. �����鼮\n");
        printf("5. ɾ������\n");
        printf("6. �޸�����\n");
        printf("7. �˳�\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 1:
	        {
		        //// �����鼮
        		add_book(BookList);
        		break;
	        }
        case 2:
	        {
		        // �޸��鼮
        		printf("������Ҫ�޸ĵ��鼮\n");
                fflush(stdin);
        		char book_title[100];
                cin>>book_title;
        		int p=LocateBook(BookList, book_title);
        		Book *book=find_book(BookList,p);
                displayBook(book);
        		int changebook_choice=1;
        		while (changebook_choice)
        		{
        			printf("������Ҫ�޸ĵ��鼮��Ϣ\n0�޸��鼮ID��1�޸��鼮�۸�2ɾ��ͼ�飬3�˳��޸�\n");
                    scanf("%d",&changebook_choice);
        			if(changebook_choice==0)
        			{
        				printf("�������޸ĺ���鼮ID\n");
        				scanf("%d",&book->id);
        				modifyBooksID(book, book->id);
        			}
        			else if(changebook_choice==1)
        			{
        				printf("�������޸ĺ���鼮�۸�\n");
        				scanf("%f",&book->price);
        				modifyBooksPrice(book, book->price);
        			}
        			else if(changebook_choice==2)
        			{
        				int locate = LocBook_position(BookList, book_title);
        				DelBook(BookList, locate, book);
        			}
        			else if(changebook_choice==3)
        			{
        				break;
        			}
        			else
        			{
        				printf("��Ч��ѡ�������ѡ��\n");
        			}
        		}
        		break;
	        }
        case 3:
	        {
                printf("������Ҫ�޸ĵ��û�ID\n");
                int user_id;
                scanf("%d", &user_id);
                display_user(userlist, user_id);
                int user_choice = 1;
                while(user_choice!=0)
                {
                    printf("������Ҫ�޸ĵ��û���Ϣ\n");
                    printf("1. �޸��û�ID\n");
                    printf("2. �޸��û�����\n");
                    printf("3. �޸��û����û���\n");
                    printf("4. �޸��û��Ļ�Ա״̬\n");
                    printf("5. �޸��û������\n");
                    printf("6.�˳��޸�");
                    scanf("%d", &user_choice);
                    if(user_choice==1)
                    {
                        printf("�������޸ĺ���û�ID\n");
	                    int new_id=scanf("%d", &new_id);
                        change_user_id(userlist, new_id, user_id);
                    }
                    if(user_choice==2)
                    {
                        change_user_password(userlist, user_id);
                    }
                    if(user_choice==3)
                    {
                    	change_user_name(userlist, user_id);
					}
                    if (user_choice==4)
                    {
                        change_user_VIP(userlist, user_id);
                    }
                    if(user_choice==5)
                    {
                        change_user_money(userlist, user_id);
                    }
                    if (user_choice==6)
                    {
                        break;
                    }
                }
        		break;
	        }
        case 4:
	        {
		        // �����鼮
        		printf("��ѡ����ҷ�ʽ\n1.ͨ��ID����\n2.ͨ����������\n");
        		int search_choice;
        		scanf("%d", &search_choice);
        		if (search_choice == 1)
        		{
        			printf("������Ҫ���ҵ�ͼ��ID\n");
        			int search_id = scanf("%d", &search_id);
        			Book* search_book = find_book(BookList, search_id);
        			displayBook(search_book);
        		}
        		if (search_choice == 2)
        		{
        			printf("������Ҫ���ҵ�ͼ�������\n");
        			char search_bookname[100];
        			cin>>search_bookname;
        			int position = LocBook_position(BookList, search_bookname);
        			Book* search_book = find_book(BookList, position);
        			displayBook(search_book);
        		}
                else
                {
                    printf("��Ч��ѡ�������ѡ��\n");
                }
        		break;
	        }
        case 5:
	        {
		        // ɾ������
        		printf("������Ҫɾ�������ID\n");
                int book_id;
                scanf("%d", &book_id);
                printf("��������������û�id\n");
                int user_id;
                scanf("%d", &user_id);
                Book* book = find_book(BookList, book_id);
                ReviewNode* review = FindReview(BookList, user_id, book_id);
                DeleteReview(book->reviews, review);
        		break;
	        }
        case 6:
	        {
		        // �޸�����
        		printf("������Ҫ�޸ĵ����ID\n");
                int book_id;
                scanf("%d", &book_id);
                printf("��������������û�id\n");
                int user_id;
                scanf("%d", &user_id);
                Book* book = find_book(BookList, book_id);
                ReviewNode* review = FindReview(BookList, user_id, book_id);
                ModifyReview(review);
        		break;
	        }
        case 7:
	        {
		        // �˳�����Ա��������
        		return;
	        }
        default:
	        {
		        printf("��Ч��ѡ�������ѡ��\n");
        		break;
	        }
        }
    }
}