#include "function.h"

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

// Kiểm tra trùng lặp ID, Email, SĐT
bool isDuplicate(char *userId, char *email, char *phone) {
    for (int i = 0; i < accountCount; i++) {
        if ((userId[0] && strcmp(accounts[i].userId, userId) == 0) ||
            (email[0] && strcmp(accounts[i].email, email) == 0) ||
            (phone[0] && strcmp(accounts[i].phone, phone) == 0)) {
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
    } while (strlen(newAccount.userId) != 12 || isDuplicate(newAccount.userId, "", ""));

    printf("Enter full name: ");
    fgets(newAccount.fullName, 50, stdin);
    newAccount.fullName[strcspn(newAccount.fullName, "\n")] = 0;

    printf("Enter email: ");
    fgets(newAccount.email, 50, stdin);
    newAccount.email[strcspn(newAccount.email, "\n")] = 0;

    printf("Enter phone: ");
    fgets(newAccount.phone, 15, stdin);
    newAccount.phone[strcspn(newAccount.phone, "\n")] = 0;

    printf("Enter username: ");
    fgets(newAccount.username, 30, stdin);
    newAccount.username[strcspn(newAccount.username, "\n")] = 0;

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
        printf("| %-12s| %-18s| %-20s| %-10s| %-6s|\n",
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
            accounts[i].status = !accounts[i].status;
            printf("Account %s has been %s!\n", userId, accounts[i].status ? "Unlocked" : "Locked");
            waitForBackOrExit();
            return;
        }
    }
    printf("Account not found!\n");
    waitForBackOrExit();
}

// Tìm kiếm người dùng theo username
void searchUserByUsername() {
    char username[30];
    printf("Enter username to search: ");
    scanf("%s", username);
    
    for (int i = 0; i < accountCount; i++) {
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
            waitForBackOrExit;
            return;
        }
    }
    printf("No user found with username: %s\n", username);
    waitForBackOrExit();
}

// Menu quản lý Admin
void adminMenu() {
    int choice;
    while (1) {
        printf("\n1. Add Account\n2. Show All Accounts\n3. Lock/Unlock Account\n4. Search User by Username\n0. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addAccount(); break;
            case 2: showAllAccounts(); break;
            case 3: lockUnlockAccount(); break;
            case 4: searchUserByUsername(); break;
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
