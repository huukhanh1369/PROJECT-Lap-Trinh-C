#include "function.h"

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

// Kiểm tra trùng lặp ID, Email, SĐT
bool isDuplicate(const char *userId, const char *email, const char *phone, const char *username) {
    for (int i = 0; i < accountCount; i++) {
        if ((strlen(userId) > 0 && strcmp(accounts[i].userId, userId) == 0) ||
            (strlen(email) > 0 && strcmp(accounts[i].email, email) == 0) ||
            (strlen(phone) > 0 && strcmp(accounts[i].phone, phone) == 0) ||
            (strlen(username) > 0 && strcmp(accounts[i].username, username) == 0)) {
            return true;
        }
    }
    return false;
}


void waitForBackOrExit() {
    char choice;
    do {
        printf("\nPress Back(B) or Exit(0) : ");
        scanf(" %c", &choice);
        choice = toupper(choice);
        if (choice == '0') {
            printf("Exiting the program...\n");
            exit(0);
        }
    } while (choice != 'B');
}

// Kiểm tra ngày hợp lệ
bool isValidDate(int day, int month, int year) {
    if (year < 1900 || year > 2100 || month < 1 || month > 12) return false;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) 
        daysInMonth[1] = 29;  
    return day > 0 && day <= daysInMonth[month - 1];
}

// Thêm tài khoản mới
void addAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Cannot add account, list is full!\n");
        waitForBackOrExit();
        return;
    }

    Account newAccount;
    printf("\n*** Add New Account ***\n");

    do {
    printf("Enter ID (12 characters): ");
    scanf("%12s", newAccount.userId);
    getchar();
} while (strlen(newAccount.userId) != 12 || isDuplicate(newAccount.userId, "", "", ""));

    printf("Enter full name: ");
    fgets(newAccount.fullName, 50, stdin);
    newAccount.fullName[strcspn(newAccount.fullName, "\n")] = 0;

    do {
    	printf("Enter email: ");
    	fgets(newAccount.email, 50, stdin);
    	newAccount.email[strcspn(newAccount.email, "\n")] = 0;
		} while (isDuplicate("", newAccount.email, "", ""));

    do {
    	printf("Enter phone: ");
    	fgets(newAccount.phone, 15, stdin);
    	newAccount.phone[strcspn(newAccount.phone, "\n")] = 0;
		} while (isDuplicate("", "", newAccount.phone, ""));

	do {
    	printf("Enter username: ");
    	fgets(newAccount.username, 30, stdin);
    	newAccount.username[strcspn(newAccount.username, "\n")] = 0;
		} while (isDuplicate("", "", "", newAccount.username));

    printf("Enter password: ");
    fgets(newAccount.password, 30, stdin);
    newAccount.password[strcspn(newAccount.password, "\n")] = 0;

    printf("Enter gender (0: Male, 1: Female): ");
    scanf("%d", &newAccount.gender);

    do {
        printf("Enter date of birth (dd mm yyyy): ");
        scanf("%d %d %d", &newAccount.dateOfBirth.day, &newAccount.dateOfBirth.month, &newAccount.dateOfBirth.year);
    } while (!isValidDate(newAccount.dateOfBirth.day, newAccount.dateOfBirth.month, newAccount.dateOfBirth.year));

    printf("Enter balance: ");
    scanf("%f", &newAccount.balance);

    newAccount.status = true;
    accounts[accountCount++] = newAccount;
    printf("Account added successfully!\n");
    waitForBackOrExit();
}

// Hiển thị danh sách tài khoản
void showAllAccounts() {
    if (accountCount == 0) {
        printf("No account yet!\n");
        waitForBackOrExit();
        return;
    }
	printf("|-------------|--------------------|----------------------|------------|--------|\n");
    printf("| ID          | Full Name          | Email                | Phone      | Status |\n");
    printf("|-------------|--------------------|----------------------|------------|--------|\n");

    for (int i = 0; i < accountCount; i++) {
        printf("|%-13s|%-20s|%-22s|%-12s|%-8s|\n",
               accounts[i].userId, accounts[i].fullName, accounts[i].email, accounts[i].phone,
               accounts[i].status ? "Open" : "Locked");
        printf("|-------------|--------------------|----------------------|------------|--------|\n");
    }
    waitForBackOrExit();
}

// Khóa/Mở khóa tài khoản
void lockUnlockAccount() {
    char userId[13];
    printf("Enter account ID to lock/unlock: ");
    scanf("%12s", userId);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].userId, userId) == 0) {
            if (accounts[i].status) {
                printf("User is currently unlocked. Confirm locking the account? (Y/N): ");
            } else {
                printf("User is currently locked. Confirm unlocking the account? (Y/N): ");
            }
            char confirm;
            scanf(" %c", &confirm);
            confirm = toupper(confirm);
            if (confirm == 'Y') {
                accounts[i].status = !accounts[i].status;
                printf("Account %s has been %s!\n", userId, accounts[i].status ? "Unlocked" : "Locked");
            } else {
                printf("Operation cancelled.\n");
            }
            waitForBackOrExit();
            return;
        }
    }
    printf("Account not found!\n");
    waitForBackOrExit();
}

// Tìm kiếm người dùng theo username
//void debugShowAllUsers() {
//    printf("\n--- Debug: Danh sách tài khoản ---\n");
 //   for (int i = 0; i < accountCount; i++) {
 //       printf("Username: %s\n", accounts[i].username);
 //   }
//    printf("-------------------------------\n");
//}

void searchUserByUsername() {
    char username[30];
    printf("Enter username to search: ");
    scanf("%s", username);

   // debugShowAllUsers(); // Hiển thị danh sách tài khoản để kiểm tra dữ liệu

    for (int i = 0; i < accountCount; i++) {
        printf("Comparing with: %s\n", accounts[i].username); // Debug so sánh

        if (strcmp(accounts[i].username, username) == 0) {
            printf("\n*** Account Information ***\n");
            printf("ID: %s\n", accounts[i].userId);
            printf("Full Name: %s\n", accounts[i].fullName);
            printf("Email: %s\n", accounts[i].email);
            printf("Phone Number: %s\n", accounts[i].phone);
            printf("Username: %s\n", accounts[i].username);
            printf("Gender: %s\n", accounts[i].gender == 0 ? "Male" : "Female");
            printf("Date of Birth: %02d/%02d/%04d\n", accounts[i].dateOfBirth.day,
                   accounts[i].dateOfBirth.month, accounts[i].dateOfBirth.year);
            printf("Account Balance: %.2f\n", accounts[i].balance);
            printf("Status: %s\n", accounts[i].status ? "Open" : "Locked");
            waitForBackOrExit();
            return;
        }
    }
    printf("No user found with username: %s\n", username);
    waitForBackOrExit();
}

// Hàm so sánh tên để sắp xếp A-Z
int compareNamesAsc(const void *a, const void *b) {
    return strcmp(((Account *)a)->fullName, ((Account *)b)->fullName);
}

// Hàm so sánh tên để sắp xếp Z-A
int compareNamesDesc(const void *a, const void *b) {
    return strcmp(((Account *)b)->fullName, ((Account *)a)->fullName);
}

// Sắp xếp tài khoản theo tên
void sortAccounts() {
    int sortChoice;
    printf("\n1. Sort A-Z\n2. Sort Z-A\nEnter choice: ");
    scanf("%d", &sortChoice);

    if (sortChoice == 1) {
        qsort(accounts, accountCount, sizeof(Account), compareNamesAsc);
        printf("Sorted A-Z successfully!\n");
        showAllAccounts();
    } else if (sortChoice == 2) {
        qsort(accounts, accountCount, sizeof(Account), compareNamesDesc);
        printf("Sorted Z-A successfully!\n");
        showAllAccounts();
    } else {
        printf("Invalid choice!\n");
    }
    waitForBackOrExit();
}

// Menu quản lý Admin
void adminMenu() {
    int choice;
    while (1) {
    	printf("***Bank Management System Using C***\n\n");
        printf("\n1. Add Account\n2. Show All Accounts\n3. Lock/Unlock Account\n4. Search User by Username\n5. Sort Accounts\n0. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addAccount(); break;
            case 2: showAllAccounts(); break;
            case 3: lockUnlockAccount(); break;
            case 4: searchUserByUsername(); break;
            case 5: sortAccounts(); break;
            case 0: return;
            default: printf("Invalid choice!\n");
        }
    }
}

// Đăng nhập Admin
void adminLogin() {
    char username[30], password[30];
    printf("***Bank Management System Using C***\n\n");
    printf("%10s%11s\n"," ","ADMIN LOGIN");
    printf("%6s%25s\n"," ","=========================");
    printf("%6s%10s"," ","Username: ");
    scanf("%s", username);
    printf("%6s%10s"," ","Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Login successful!\n");
        adminMenu();
    } else {
        printf("Wrong username or password!\n");
    }
}
