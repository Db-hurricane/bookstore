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
void create_initial_review()
{
    //��ʼ����������
    Review reviews[10] =
    {
         {3, 9, 6, 4},
         {6, 7, 8, 5},
         {3, 5, 9, 7},
         {8, 6, 8, 7},
         {5, 7, 5, 9},
         {8, 6, 6, 4},
         {7, 7, 7, 5},
         {8, 9, 8, 5},
         {9, 9, 9, 6},
         {10, 7, 10, 5}
    };

    // ���������б�
    ReviewNode* reviewList;
    CreateReviewList(&reviewList, reviews, 10);
}


// ������
int main() {
    User* currentUser = nullptr;
    InitUserList(&currentUser);
    BookNode* bookList=nullptr;
    InitBookList(bookList);
    create_initial_data(currentUser);
    create_initial_book(bookList);

    while (1) {
        printf("��ѡ�������\n");
        printf("1. ע��\n");
        printf("2. �û���¼\n");
        printf("3. ����Ա��¼\n");
        printf("4. �˳�\n");

        int choice;
        scanf_s("%d", &choice);
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
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
	        {
		        // �����鼮
        		printf("������Ҫ���ҵ��鼮");
        		char title[100];
                fflush(stdin);
                cin>>title;
        		int findbook_id=LocateBook(bookList, title)-1;
        		Book* findbook = find_book(bookList, findbook_id);
                displayBook(findbook);
        		break;
	        }
        case 2:
	        {
		        // �����鼮
            
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
void admin_operations(User* admin,BookNode *BookList) {
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
        scanf_s("%d", &choice);

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
        		int changebook_choice=1;
        		while (changebook_choice)
        		{
        			printf("������Ҫ�޸ĵ��鼮��Ϣ\n0�޸��鼮ID��1�޸��鼮�۸�2ɾ��ͼ�飬3�˳��޸�\n");
                    scanf_s("%d",&changebook_choice);
        			if(changebook_choice==0)
        			{
        				printf("�������޸ĺ���鼮ID\n");
        				scanf_s("%d",&book->id);
        				modifyBooksID(book, book->id);
        			}
        			else if(changebook_choice==1)
        			{
        				printf("�������޸ĺ���鼮�۸�\n");
        				scanf_s("%f",&book->price);
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
            {break;}
        case 4:
	        {
		        // �����鼮
        		printf("��ѡ����ҷ�ʽ\n1.ͨ��ID����\n2.ͨ����������\n");
        		int search_choice;
        		scanf_s("%d", &search_choice);
        		if (search_choice == 1)
        		{
        			printf("������Ҫ���ҵ�ͼ��ID\n");
        			int search_id = scanf_s("%d", &search_id);
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
        		//delete_review();
        		break;
	        }
        case 6:
	        {
		        // �޸�����
        		//modify_review(admin);
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