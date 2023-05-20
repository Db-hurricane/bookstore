#include "bookstore.h"


#include <stdio.h>

// 定义你的函数和数据结构...

void user_interface(int user_id) {
    while (1) {
        printf("\nWelcome, user! Please select an option:\n");
        printf("1. Search for books\n");
        printf("2. Purchase a book\n");
        printf("3. Leave a review\n");
        printf("4. Logout\n");

        int option;
        scanf("%d", &option);

        switch (option) {
        case 1:
            // Call your search_books function...
            break;
        case 2:
            // Call your purchase_book function...
            break;
        case 3:
            // Call your add_review function...
            break;
        case 4:
            printf("You have logged out. Goodbye!\n");
            return;
        default:
            printf("Invalid option. Please try again.\n");
        }
    }
}

void admin_interface(int admin_id) {
    while (1) {
        printf("\nWelcome, admin! Please select an option:\n");
        printf("1. Manage users\n");
        printf("2. Manage books\n");
        printf("3. Manage reviews\n");
        printf("4. Logout\n");

        int option;
        scanf("%d", &option);

        switch (option) {
        case 1:
            // Call your manage_user_admin function...
            break;
        case 2:
            // Call your manage_book_admin function...
            break;
        case 3:
            // Call your manage_review_admin function...
            break;
        case 4:
            printf("You have logged out. Goodbye!\n");
            return;
        default:
            printf("Invalid option. Please try again.\n");
        }
    }
}

int main() {
    while (1) {
        printf("\nWelcome to the online bookstore! Please select an option:\n");
        printf("1. Register\n");
        printf("2. User Login\n");
        printf("3. Admin Login\n");
        printf("4. Exit\n");

        int option;
        scanf("%d", &option);

        switch (option) {
        case 1:
            // Call your register_user function...
            break;
        case 2: {
            int user_id = login_user();
            if (user_id != -1) {
                user_interface(user_id);
            }
            else {
                printf("Login failed. Please try again.\n");
            }
            break;
        }
        case 3: {
            int admin_id = login_admin(/* 输入用户名和密码 */);
            if (admin_id != -1) {
                admin_interface(admin_id);
            }
            else {
                printf("Login failed. Please try again.\n");
            }
            break;
        }
        case 4:
            printf("Thank you for visiting our online bookstore. Goodbye!\n");
            return 0;
        default:
            printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
