#include "function.h"

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

void getPassword(char* password) {
    char ch;
    int i = 0;

    while (1) {
        ch = getch(); // Lấy ký tự mà người dùng nhập vào
        if (ch == 13) { // Kiểm tra nếu người dùng nhấn Enter (13 là mã ASCII của Enter)
            password[i] = '\0'; // Kết thúc chuỗi mật khẩu
            break;
        } else if (ch == 8) { // Kiểm tra nếu người dùng nhấn phím Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // Xóa ký tự vừa nhập
            }
        } else {
            password[i] = ch; // Lưu ký tự mật khẩu
            i++;
            printf("*"); // In dấu * ra màn hình thay vì ký tự thực tế
        }
    }
    printf("\n");
}

bool isValidNumber(const char *str) {
    if (strlen(str) == 0) return false;
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}
//kiem tra gmail hop le hay khong
bool isValidGmail(const char *email) {
    int len = strlen(email);
    
    // Kiểm tra email có chứa ít nhất một ký tự trước "@gmail.com" hay không
    if (len < 11 || strstr(email, "@gmail.com") == NULL) {
        return false;
    }
    
    // Kiểm tra phần cuối của email có đúng là "@gmail.com" không
    if (strcmp(email + (len - 10), "@gmail.com") != 0) {
        return false;
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
    } while (choice != 'B'); system("cls");
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
    fflush(stdin);
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
    fflush(stdin);
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
        newAccount.email[strcspn(newAccount.email, "\n")] = 0; // Xóa ký tự xuống dòng

        if (strlen(newAccount.email) == 0) {
            printf("Email cannot be empty. Please enter again.\n");
        } else if (!isValidGmail(newAccount.email)) {
            printf("Invalid email! Please enter a valid Gmail address (example@gmail.com).\n");
        } else if (isDuplicate("", newAccount.email, "", "")) {
            printf("Email must be unique. Please enter another email.\n");
        }
    } while (strlen(newAccount.email) == 0 || !isValidGmail(newAccount.email) || isDuplicate("", newAccount.email, "", ""));

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
	printf("|-------------|---------------------|----------------------|------------|--------|\n");
    printf("| ID          | Full Name           | Email                | Phone      | Status |\n");
    printf("|-------------|---------------------|----------------------|------------|--------|\n");

    for (int i = 0; i < accountCount; i++) {
        printf("|%-13s|%-21s|%-22s|%-12s|%-8s|\n",
               accounts[i].userId, accounts[i].fullName, accounts[i].email, accounts[i].phone,
               accounts[i].status ? "Open" : "Locked");
        printf("|-------------|---------------------|----------------------|------------|--------|\n");
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



    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].userId, userId) == 0) {
        	printf("\n|%-12s|%-21s|%-20s|%-15s|%-10s|%-10s|%-15s|%-8s|\n", 
           "User ID", "Full Name", "Email", "Phone", "Gender", "DOB", "Balance", "Status");
    		printf("|------------|---------------------|--------------------|---------------|----------|----------|---------------|--------|\n");
            printf("|%-12s|%-21s|%-20s|%-15s|%-10s|%02d/%02d/%04d|%-15.2f|%-8s|\n",
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
    		printf("|------------|---------------------|--------------------|---------------|----------|----------|---------------|--------|\n");
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
        qsort(accounts, accountCount, sizeof(Account), compareNamesAsc); system("cls");
        printf("Sorted A-Z successfully!\n");
        showAllAccounts();
    } else if (sortChoice == 2) {
        qsort(accounts, accountCount, sizeof(Account), compareNamesDesc); system("cls");
        printf("Sorted Z-A successfully!\n");
        showAllAccounts();
    } else {
        printf("Invalid choice!\n");
    }
}

// Menu quản lý Admin
void adminMenu() {
    int choice;
    do {
        printf("***Bank Management System Using C***\n\n");
        printf("%6s%25s\n"," ","=========================");
        printf("%6s%10s\n"," ","[1] add Account.");
        printf("%6s%9s\n"," ","[2] show All Accounts.");
        printf("%6s%9s\n"," ","[3] loc kUnlock Account.");
        printf("%6s%9s\n"," ","[4] search User By ID.");
    	printf("%6s%9s\n"," ","[5] sort Accounts.");
        printf("%5s%22s\n"," ","[0] Exit The Program.");
        printf("%6s%25s\n"," ","=========================");
        printf("%6s%18s"," ","Enter the choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: system("cls"); addAccount(); break;
            case 2: system("cls"); showAllAccounts(); break;
            case 3: system("cls"); lockUnlockAccount(); break;
            case 4: system("cls"); searchUserByID(); break;
            case 5: system("cls"); sortAccounts(); break;
            case 0: system("cls"); return;
            default:printf("Invalid choice!\n"); 
        }
        }while(choice!=0);
    }


// Đăng nhập Admin
void adminLogin() {
    char username[30], password[30], fileUser[30], filePass[30];
    FILE *file;

    printf("*** Bank Management System Using C ***\n\n");
    printf("%10s%11s\n", " ", "ADMIN LOGIN");
    printf("%6s%25s\n", " ", "=========================");
    printf("%6s%10s", " ", "Username: ");
    scanf("%s", username);
    printf("%6s%10s", " ", "Password: ");
    getPassword(password);

    // Mở file chứa thông tin admin
    file = fopen(ADMIN_FILE, "r");
    if (file == NULL) {
        printf("Error! Cannot open admin file.\n");
        return;
    }

    // Đọc username và password từ file
    fscanf(file, "%s %s", fileUser, filePass);
    fclose(file);

    // Kiểm tra thông tin đăng nhập
    if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
        printf("Login successful!\n");
        system("cls");
        adminMenu();
    } else {
        system("cls");
        printf("Wrong username or password!\n");
    }
}

//dang nhap nguoi dung
void loginUser() {
    char userId[30];
    char password[30];
    int found;

    while (1) { // Lặp vô hạn đến khi đăng nhập thành công hoặc tài khoản bị khóa
        printf("Enter User ID: ");
        fgets(userId, sizeof(userId), stdin); // Dùng fgets để nhập an toàn
        userId[strcspn(userId, "\n")] = 0; // Loại bỏ ký tự newline

        printf("Enter Password: ");
        //fgets(password, sizeof(password), stdin); // Dùng fgets để nhập an toàn
        //password[strcspn(password, "\n")] = 0; // Loại bỏ ký tự newline
        getPassword(password);

        found = 0; // Biến kiểm tra xem tài khoản có tồn tại hay không

        for (int i = 0; i < accountCount; i++) {
            if (strcmp(accounts[i].userId, userId) == 0) { // Tìm thấy tài khoản
                found = 1;

                if (strcmp(accounts[i].password, password) == 0) { // Mật khẩu đúng
                    if (accounts[i].status == 0) { // Tài khoản bị khóa
                    	system("cls");
                        printf("Your account is locked. Returning to the main menu...\n");
                        return; // Quay lại menu chính
                    } else {
                        printf("Login successful! Welcome, %s.\n", accounts[i].fullName);
                        return; // Thoát khi đăng nhập thành công
                    }
                }
                break;
            }
        }

        if (found == 0) { // Nếu không tìm thấy tài khoản
            printf("Invalid User ID or Password. Please try again.\n");
        }
    }
}
