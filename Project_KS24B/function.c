#include "function.h"

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

bool isValidNumber(const char *str) {
    if (strlen(str) == 0) return false;
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

// Kiểm tra chuỗi chỉ chứa chữ cái và khoảng trắng
bool isValidName(const char *str) {
    if (strlen(str) == 0) return false;
    for (int i = 0; i < strlen(str); i++) {
        if (isdigit(str[i]) || ispunct(str[i])) return false;
    }
    return true;
}

void saveAccountsToFile() {
    FILE *file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error saving data!\n");
        return;
    }
    fwrite(&accountCount, sizeof(int), 1, file);
    fwrite(accounts, sizeof(Account), accountCount, file);
    fclose(file);
}

// Đọc danh sách tài khoản từ file khi khởi động
void loadAccountsFromFile() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No previous account data found.\n");
        return;
    }
    fread(&accountCount, sizeof(int), 1, file);
    fread(accounts, sizeof(Account), accountCount, file);
    fclose(file);
}



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

    // Nhập userId (12 ký tự, không trùng)
    do {
    printf("Enter ID (12 digits): ");
    fgets(newAccount.userId, 13, stdin);
    newAccount.userId[strcspn(newAccount.userId, "\n")] = 0; // Xóa dấu xuống dòng

    if (strlen(newAccount.userId) == 0) { 
        printf("ID cannot be empty. Please enter again.\n");
        continue;
    }
    if (strlen(newAccount.userId) != 12 || !isValidNumber(newAccount.userId) || isDuplicate(newAccount.userId, "", "", "")) {
        printf("ID must be exactly 12 digits and unique. Please enter again.\n");
    }
} while (strlen(newAccount.userId) == 0 || strlen(newAccount.userId) != 12 || !isValidNumber(newAccount.userId) || isDuplicate(newAccount.userId, "", "", ""));

    // Nhập họ tên (không để trống)
    do {
    printf("Enter full name: ");
    fgets(newAccount.fullName, 50, stdin);
    newAccount.fullName[strcspn(newAccount.fullName, "\n")] = 0;

    if (strlen(newAccount.fullName) == 0) {
        printf("Full name cannot be empty. Please enter again.\n");
        continue;
    }

    if (!isValidName(newAccount.fullName)) {
        printf("Full name must not contain numbers or special characters. Please enter again.\n");
    }
} while (!isValidName(newAccount.fullName) || strlen(newAccount.fullName) == 0);

    // Nhập email (không trống, không trùng)
    do {
        printf("Enter email: ");
        fgets(newAccount.email, 50, stdin);
        newAccount.email[strcspn(newAccount.email, "\n")] = 0;

        if (strlen(newAccount.email) == 0 || isDuplicate("", newAccount.email, "", "")) {
            printf("Email cannot be empty and must be unique. Please enter again.\n");
        }
    } while (strlen(newAccount.email) == 0 || isDuplicate("", newAccount.email, "", ""));

    // Nhập số điện thoại (không trống, không trùng)
     do {
        printf("Enter phone number: ");
        fgets(newAccount.phone, 15, stdin);
        newAccount.phone[strcspn(newAccount.phone, "\n")] = 0;
        if (!isValidNumber(newAccount.phone) || isDuplicate("", "", newAccount.phone, "")) {
            printf("Phone number must contain only digits and be unique. Please enter again.\n");
        }
    } while (!isValidNumber(newAccount.phone) || isDuplicate("", "", newAccount.phone, ""));


    // Nhập username (không trống, không trùng)
    do {
        printf("Enter username: ");
        fgets(newAccount.username, 30, stdin);
        newAccount.username[strcspn(newAccount.username, "\n")] = 0;

        if (strlen(newAccount.username) == 0 || isDuplicate("", "", "", newAccount.username)) {
            printf("Username cannot be empty and must be unique. Please enter again.\n");
        }
    } while (strlen(newAccount.username) == 0 || isDuplicate("", "", "", newAccount.username));

    // Nhập password (không để trống)
    do {
        printf("Enter password: ");
        fgets(newAccount.password, 30, stdin);
        newAccount.password[strcspn(newAccount.password, "\n")] = 0;

        if (strlen(newAccount.password) == 0) {
            printf("Password cannot be empty. Please enter again.\n");
        }
    } while (strlen(newAccount.password) == 0);

    // Nhập giới tính (0 hoặc 1)
    do {
        printf("Enter gender (0: Male, 1: Female): ");
        if (scanf("%d", &newAccount.gender) != 1 || (newAccount.gender != 0 && newAccount.gender != 1)) {
            printf("Invalid gender. Please enter 0 for Male or 1 for Female.\n");
        }
        while (getchar() != '\n'); // Xóa bộ đệm
    } while (newAccount.gender != 0 && newAccount.gender != 1);

    // Nhập ngày sinh (hợp lệ)
    do {
        printf("Enter date of birth (dd mm yyyy): ");
        if (scanf("%d %d %d", &newAccount.dateOfBirth.day, &newAccount.dateOfBirth.month, &newAccount.dateOfBirth.year) != 3
            || !isValidDate(newAccount.dateOfBirth.day, newAccount.dateOfBirth.month, newAccount.dateOfBirth.year)) {
            printf("Invalid date of birth. Please enter again.\n");
        }
        while (getchar() != '\n'); // Xóa bộ đệm
    } while (!isValidDate(newAccount.dateOfBirth.day, newAccount.dateOfBirth.month, newAccount.dateOfBirth.year));

    // Nhập số dư (không âm)
    do {
        printf("Enter balance: ");
        char balanceStr[20];
        fgets(balanceStr, 20, stdin);
        balanceStr[strcspn(balanceStr, "\n")] = 0;
        if (!isValidNumber(balanceStr) || atof(balanceStr) < 0) {
            printf("Balance must be a valid non-negative number. Please enter again.\n");
        } else {
            newAccount.balance = atof(balanceStr);
            break;
        }
    } while (1);

    newAccount.status = true;
    accounts[accountCount++] = newAccount;
    saveAccountsToFile();
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
                saveAccountsToFile();
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


void searchUserByID() {
    char userId[30];
    printf("Enter User ID to search: ");
    scanf("%s", userId);

    printf("\n|%-12s|%-20s|%-20s|%-15s|%-10s|%-10s|%-15s|%-10s|\n", 
           "User ID", "Full Name", "Email", "Phone", "Gender", "DOB", "Balance", "Status");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].userId, userId) == 0) {
            printf("|%-12s|%-20s|%-20s|%-15s|%-10s|%02d/%02d/%04d|%-15.2f|%-10s|\n",
                   accounts[i].userId,
                   accounts[i].fullName,
                   accounts[i].email,
                   accounts[i].phone,
                   accounts[i].gender == 0 ? "Male" : "Female",
                   accounts[i].dateOfBirth.day,
                   accounts[i].dateOfBirth.month,
                   accounts[i].dateOfBirth.year,
                   accounts[i].balance,
                   accounts[i].status ? "Open" : "Locked");
    		printf("------------------------------------------------------------------------------------------------------------------------\n");
            waitForBackOrExit();
            return;
        }
    }
    printf("No user found with User ID: %s\n", userId);
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
            case 4: searchUserByID(); break;
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
