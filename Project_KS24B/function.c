#include "function.h"

struct accountInfo accounts[MAX_ACCOUNTS];  // Mảng chứa tài khoản
int accountCount = 0; // Số lượng tài khoản hiện tại


bool isDuplicate(char *userId, char *email, char *phone) {
    for (int i = 0; i < accountCount; i++) {
        if ((userId[0] != '\0' && strcmp(accounts[i].userId, userId) == 0) ||
            (email[0] != '\0' && strcmp(accounts[i].email, email) == 0) ||
            (phone[0] != '\0' && strcmp(accounts[i].phone, phone) == 0)) {
            return true;
        }
    }
    return false;
}


// Hàm kiểm tra ngày hợp lệ
bool isValidDate(int day, int month, int year) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) 
        daysInMonth[1] = 29;  // Năm nhuận
    return day > 0 && day <= daysInMonth[month - 1];
}

// Thêm tài khoản mới
void addAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Cannot add account, list is full!\n");
        return;
    }

    struct accountInfo newAccount;
    printf("\n*** Add New Account ***\n");

    // Nhập ID (12 ký tự và không trùng)
do {
    printf("Enter ID (exactly 12 characters): ");
    scanf("%12s", newAccount.userId);  // Đọc đúng 12 ký tự
    getchar(); // Xóa ký tự '\n' còn lại trong bộ nhớ đệm
} while (strlen(newAccount.userId) != 12 || isDuplicate(newAccount.userId, "", ""));

    // Nhập thông tin khác
    
    char *fields[] = {"Full name", "Email", "Phone", "Username", "Password"};
    char *inputs[] = {newAccount.fullName, newAccount.email, newAccount.phone, newAccount.username, newAccount.password};

for (int i = 0; i < 5; i++) {
    do {
        printf("Enter %s: ", fields[i]);
        getchar();
        fgets(inputs[i], 50, stdin);
        inputs[i][strcspn(inputs[i], "\n")] = 0; // Xóa ký tự xuống dòng
    } while (strlen(inputs[i]) == 0 || 
             (i == 1 && isDuplicate("", newAccount.email, "")) || 
             (i == 2 && isDuplicate("", "", newAccount.phone)));
}

    // Giới tính
    do {
        printf("Enter gender (0: Male, 1: Female): ");
        scanf("%d", &newAccount.gender);
    } while (newAccount.gender != 0 && newAccount.gender != 1);

    // Ngày sinh
    do {
        printf("Enter date of birth (dd mm yyyy): ");
        scanf("%d %d %d", &newAccount.dateOfBirth.day, &newAccount.dateOfBirth.month, &newAccount.dateOfBirth.year);
    } while (!isValidDate(newAccount.dateOfBirth.day, newAccount.dateOfBirth.month, newAccount.dateOfBirth.year));

    // Số dư
    do {
        printf("Enter balance: ");
        scanf("%f", &newAccount.balance);
    } while (newAccount.balance < 0);

    newAccount.status = true; // Mặc định tài khoản mở
    accounts[accountCount++] = newAccount;
    printf("Account added successfully!\n");
}

// Hiển thị danh sách tài khoản
void showAllAccounts() {
    if (accountCount == 0) {
        printf("No account yet!\n");
        return;
    }

    printf("|=============|====================|====================|====================|==========|\n");
    printf("|%-13s|%-20s|%-20s|%-10s|%-10s|\n", "ID", "Full Name", "Email", "Phone", "Status");
    printf("|=============|====================|====================|====================|==========|\n");

    for (int i = 0; i < accountCount; i++) {
    	
		printf("Debug: ID=%s, FullName=%s, Email=%s, Phone=%s\n", 
       accounts[i].userId, accounts[i].fullName, accounts[i].email, accounts[i].phone);
    	
        printf("| %-12s | %-18s | %-20s | %-10s | %-10s |\n",
       accounts[i].userId, accounts[i].fullName, accounts[i].email, accounts[i].phone,
       accounts[i].status ? "Open" : "Lock");
        printf("|-------------|--------------------|--------------------|--------------------|----------|\n");
    }
}

// Khóa/mở khóa tài khoản
void lockUnlockAccount() {
    char userId[13];
    printf("Enter account ID to lock/unlock: ");
    scanf("%12s", userId);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].userId, userId) == 0) {
            accounts[i].status = !accounts[i].status;
            printf("Account %s has been %s!\n", userId, accounts[i].status ? "Unlocked" : "Locked");
            return;
        }
    }
    printf("Account with ID %s not found.\n", userId);
}

// Tìm kiếm người dùng theo tên
void searchUserByName() {
    char name[50];
    printf("Enter full name to search: ");
    getchar(); // Xóa bộ nhớ đệm
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;

    bool found = false;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].fullName, name) == 0) {
            printf("\nAccount Found:\nID: %s\nFull Name: %s\nEmail: %s\nPhone: %s\nGender: %s\nDate of Birth: %02d/%02d/%04d\nBalance: %.2f\nStatus: %s\n",
                   accounts[i].userId, accounts[i].fullName, accounts[i].email, accounts[i].phone,
                   accounts[i].gender ? "Female" : "Male", accounts[i].dateOfBirth.day, accounts[i].dateOfBirth.month, accounts[i].dateOfBirth.year,
                   accounts[i].balance, accounts[i].status ? "Open" : "Lock");
            found = true;
            break;
        }
    }
    if (!found) {
        printf("No user found with the name: %s\n", name);
    }
}

// Menu quản lý Admin
void adminMenu() {
    int choice;
    while (1) {
        printf("\n=========== MENU ===========\n");
        printf("[1] Add a new user.\n");
        printf("[2] Show all user.\n");
        printf("[3] Lock (Unlock) an user.\n");
        printf("[4] Search user by full name.\n");
        printf("[0] Exit the Program.\n");
        printf("============================\n");
        printf("Enter the choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                showAllAccounts();
                break;
            case 3:
                lockUnlockAccount();
                break;
            case 4:
                searchUserByName();
                break;
            case 0:
                printf("Exit...\n");
                return;
            default:
                printf("Invalid selection!\n");
        }
    }
}

// Đăng nhập Admin
void adminLogin() {
    char adminUser[] = "admin";
    char adminPass[] = "admin123";
    char username[30], password[30];
    
	printf("\n***Bank Management System Using C***\n\n");
    printf("%10s%11s\n"," ","Admin Login");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, adminUser) == 0 && strcmp(password, adminPass) == 0) {
        printf("Login successful!\n");
        adminMenu();
    } else {
        printf("Wrong username or password!\n");
    }
}
