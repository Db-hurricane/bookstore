#include "bookstore.h"

//函数声明
void user_operations(User* users, BookNode* bookList);
void admin_operations(User* users, BookNode* bookList);

//初始化建立用户数据
void create_initial_data(User *userList)
{

    // 创建管理员账户
    User admin = { 0, "admin", "0", 0.0, 1, 0, nullptr, nullptr };
    InsertUser(userList, 1, admin);

    // 随机创建3个用户
    User users[3] = {
        {1, "user1", "1", 300.0, 0, 0, nullptr, nullptr},
        {2, "user2", "2", 200.0, 0, 1, nullptr, nullptr},
        {3, "user3", "3", 300.0, 0, 0, nullptr, nullptr},
    };
    InsertUser(userList, 2, users[0]);
    InsertUser(userList, 3, users[1]);
    InsertUser(userList, 4, users[2]);
}

//初始化建立书籍数据
void create_initial_book(BookNode *bookList)
{
    // Initialize some books
    Book books[10] = {
        {1, "红楼梦", "曹雪芹", 39.99f, rand() % 5, nullptr},
        {2, "西游记", "吴承恩", 49.99f, rand() % 5, nullptr},
        {3, "三国演义", "罗贯中", 59.99f, rand() % 5, nullptr},
        {4, "水浒传", "施耐庵", 49.99f, rand() % 5, nullptr},
        {5, "哈姆雷特", "威廉·莎士比亚", 29.99f, rand() % 5, nullptr},
        {6, "简·爱", "夏洛蒂·勃朗特", 39.99f, rand() % 5, nullptr},
        {7, "傲慢与偏见", "简·奥斯汀", 49.99f, rand() % 5, nullptr},
        {8, "百年孤独", "加西亚·马尔克斯", 59.99f, rand() % 5, nullptr},
        {9, "飘", "玛格丽特·米切尔", 69.99f, rand() % 5, nullptr},
        {10, "1984", "乔治·奥威尔", 39.99f, rand() % 5, nullptr}
    };

    // Create the book list
    CreateBookList(bookList, books, 10);
}

//初始化建立书评数据
void create_initial_review(BookNode *&bookList)
{
    //初始化书评数据
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


// 主函数
int main() {
    User* currentUser = nullptr;
    InitUserList(&currentUser);
    BookNode* bookList=nullptr;
    InitBookList(bookList);
    create_initial_data(currentUser);
    create_initial_book(bookList);
    create_initial_review(bookList);

    while (1) {
        printf("请选择操作：\n");
        printf("1. 注册\n");
        printf("2. 用户登录\n");
        printf("3. 管理员登录\n");
        printf("4. 退出\n");

        int choice;
        scanf("%d", &choice);
        int e = 0;

        switch (choice) {
        case 1:
	        {
		        // 注册新用户
        		user_register(currentUser);
        		break;
	        }
        case 2:
	        {
		        // 用户登录
        		user_login(currentUser,e);
                if(e == 1) {
                    user_operations(currentUser, bookList);
				}
                else
                {
                    printf("登录失败，请重新登录。\n");
                }
        		break;
	        }
        case 3:
	        {
		        // 管理员登录
        		admin_login(currentUser,e);
                if (e == 1) {
                    admin_operations(currentUser, bookList);
                }
                else
                {
                    printf("登录失败，请重新登录。\n");
                }
        		break;
	        }
        case 4:
	        {
		        // 退出程序
        		exit(0);
	        }
        default:
	        {
		        printf("无效的选项，请重新选择。\n");
        		break;
	        }
        }
    }

    return 0;
}

// 用户操作
void user_operations(User* user,BookNode *bookList) {
    while (1) {
        printf("请选择操作：\n");
        printf("1. 查找书籍\n");
        printf("2. 借阅书籍或归还书籍\n");
        printf("3. 购买书籍\n");
        printf("4. 写书评\n");
        printf("5. 注册会员\n");
        printf("6. 充值账户\n");
        printf("7. 退出\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 1:
	        {
		        // 查找书籍
        		printf("请输入要查找的书籍");
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
                printf("请选择操作：\n");
                printf("1. 借阅书籍\n");
                printf("2. 归还书籍\n");
                scanf("%d", &borrow_or_return);
                if(borrow_or_return==1)
                {
                    // 借阅书籍
                    borrow_book(bookList, user);
                }
                else if(borrow_or_return==2)
                {
                    // 归还书籍
                    return_book(bookList, user);
                }
                else
                {
                    printf("无效的选项，请重新选择。\n");
                }
        		break;
	        }
        case 3:
	        {
		        // 购买书籍
		        buy_books(user, bookList);
        		break;
	        }
        case 4:
	        {
		        // 写书评
                int id;
                printf("请输你的id");
                scanf("%d", &id);
                printf("请输入要写书评的书籍id");
                int book_id;
                scanf("%d", &book_id);
                float content;
                printf("请输入书评分数");
                scanf("%f", &content);
                WriteReview(user, bookList,id,book_id,content);
        		break;
	        }
        case 5:
	        {
		        // 注册会员
        		user_registerVIP(user);
        		break;
	        }
        case 6:
	        {
		        // 充值账户
				user_recharge(user);
				break;
	        }
        case 7:
	        {
		        // 退出用户操作界面
        		return;
	        }
        default:
	        {
		        printf("无效的选项，请重新选择。\n");
        		break;
	        }
        }
    }
}

// 管理员操作
void admin_operations(User* userlist,BookNode *BookList) {
    while (1) {
        printf("请选择操作：\n");
        printf("1. 增加书籍\n");
        printf("2. 修改书籍\n");
        printf("3. 修改用户信息\n");
        printf("4. 查找书籍\n");
        printf("5. 删除书评\n");
        printf("6. 修改书评\n");
        printf("7. 退出\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 1:
	        {
		        //// 增加书籍
        		add_book(BookList);
        		break;
	        }
        case 2:
	        {
		        // 修改书籍
        		printf("请输入要修改的书籍\n");
                fflush(stdin);
        		char book_title[100];
                cin>>book_title;
        		int p=LocateBook(BookList, book_title);
        		Book *book=find_book(BookList,p);
                displayBook(book);
        		int changebook_choice=1;
        		while (changebook_choice)
        		{
        			printf("请输入要修改的书籍信息\n0修改书籍ID，1修改书籍价格，2删除图书，3退出修改\n");
                    scanf("%d",&changebook_choice);
        			if(changebook_choice==0)
        			{
        				printf("请输入修改后的书籍ID\n");
        				scanf("%d",&book->id);
        				modifyBooksID(book, book->id);
        			}
        			else if(changebook_choice==1)
        			{
        				printf("请输入修改后的书籍价格\n");
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
        				printf("无效的选项，请重新选择。\n");
        			}
        		}
        		break;
	        }
        case 3:
	        {
                printf("请输入要修改的用户ID\n");
                int user_id;
                scanf("%d", &user_id);
                display_user(userlist, user_id);
                int user_choice = 1;
                while(user_choice!=0)
                {
                    printf("请输入要修改的用户信息\n");
                    printf("1. 修改用户ID\n");
                    printf("2. 修改用户密码\n");
                    printf("3. 修改用户的用户名\n");
                    printf("4. 修改用户的会员状态\n");
                    printf("5. 修改用户的余额\n");
                    printf("6.退出修改");
                    scanf("%d", &user_choice);
                    if(user_choice==1)
                    {
                        printf("请输入修改后的用户ID\n");
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
		        // 查找书籍
        		printf("请选择查找方式\n1.通过ID查找\n2.通过书名查找\n");
        		int search_choice;
        		scanf("%d", &search_choice);
        		if (search_choice == 1)
        		{
        			printf("请输入要查找的图书ID\n");
        			int search_id = scanf("%d", &search_id);
        			Book* search_book = find_book(BookList, search_id);
        			displayBook(search_book);
        		}
        		if (search_choice == 2)
        		{
        			printf("请输入要查找的图书的书名\n");
        			char search_bookname[100];
        			cin>>search_bookname;
        			int position = LocBook_position(BookList, search_bookname);
        			Book* search_book = find_book(BookList, position);
        			displayBook(search_book);
        		}
                else
                {
                    printf("无效的选项，请重新选择。\n");
                }
        		break;
	        }
        case 5:
	        {
		        // 删除书评
        		printf("请输入要删除的书的ID\n");
                int book_id;
                scanf("%d", &book_id);
                printf("请输入该书评的用户id\n");
                int user_id;
                scanf("%d", &user_id);
                Book* book = find_book(BookList, book_id);
                ReviewNode* review = FindReview(BookList, user_id, book_id);
                DeleteReview(book->reviews, review);
        		break;
	        }
        case 6:
	        {
		        // 修改书评
        		printf("请输入要修改的书的ID\n");
                int book_id;
                scanf("%d", &book_id);
                printf("请输入该书评的用户id\n");
                int user_id;
                scanf("%d", &user_id);
                Book* book = find_book(BookList, book_id);
                ReviewNode* review = FindReview(BookList, user_id, book_id);
                ModifyReview(review);
        		break;
	        }
        case 7:
	        {
		        // 退出管理员操作界面
        		return;
	        }
        default:
	        {
		        printf("无效的选项，请重新选择。\n");
        		break;
	        }
        }
    }
}