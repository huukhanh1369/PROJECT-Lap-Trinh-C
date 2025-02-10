#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ACCOUNTS 100

struct date {
    int day, month, year;
};

struct transaction {
    char transferId[12];
    char receivingId[12];
    double amount;
    char type[10];
    char message[50];
    struct date transactionDate;
};

struct accountInfo {
    char userId[12];
    float balance;
    bool status;
    char username[30];
    char password[30];
    struct transaction history;
};

struct user {
    char userId[12];
    char name[30];
    struct date dateOfBirth;
    bool gender;
    char phone[11];
    char email[30];
};

struct accountInfo accounts[MAX_ACCOUNTS];
int accountCount = 0;

void addAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Cannot add a new account!\n");
        return;
    }
    
    struct accountInfo newAccount;
    printf("Enter account ID (10 characters): ");
    scanf("%s", newAccount.userId);
    if (strlen(newAccount.userId) < 10) {
        printf("Error: ID must be at least 10 characters long!\n");
        return;
    }
    printf("Enter name: ");
    scanf(" %s", newAccount.username);
    printf("Enter email: ");
    scanf("%s", newAccount.password);
    printf("Enter phone number: ");
    scanf("%s", newAccount.history.transferId);
    printf("Enter gender (0 - Male, 1 - Female): ");
    scanf("%d", &newAccount.status);
    
    printf("Enter date of birth:\n");
    printf("  Enter day: ");
    scanf("%d", &newAccount.history.transactionDate.day);
    printf("  Enter month: ");
    scanf("%d", &newAccount.history.transactionDate.month);
    printf("  Enter year: ");
    scanf("%d", &newAccount.history.transactionDate.year);
    
    printf("Enter initial balance: ");
    scanf("%f", &newAccount.balance);
    newAccount.status = true;
    
    accounts[accountCount++] = newAccount;
    printf("\nAccount successfully added!\n");
    int user[MAX_ACCOUNTS];
};
void displayAccounts() {
    if (accountCount == 0) {
        printf("No accounts available!\n");
        return;
    }
    printf("|%13s|%20s|%30s|%20s|%10s|\n","=","=","=","=","=");
    printf("| %-12s | %-20s | %-30s | %-15s | %-10s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("|%13s|%20s|%30s|%20s|%10s|\n","=","=","=","=","=");
    for (int i = 0; i < accountCount; i++) 
    {
    printf("| %-12s | %-20s | %-30s | %-15s | %-10s |\n",
               user[i].userId,
               user[i].username,
               user[i].email,  
               user[i].phone,  
               user[i].status ? "Open" : "Lock");
    }
}
int main (){
    while(1){
        printf("***Bank Management System Using C***\n\n");
        printf("%10s%16s\n"," ","CHOOSE YOUR ROLE");
        printf("%6s%25s\n"," ","=========================");
        printf("%6s%10s\n"," ","[1] Admin.");
        printf("%6s%9s\n"," ","[2] User.");
        printf("%6s%22s\n"," ","[0]. Exit The Program.");
        printf("%6s%25s\n"," ","=========================");
        int choice;
        printf("%6s%18s\n"," ","Enter the choice: ");
        scanf("%d",&choice);
        switch (choice) 
        {
            case 1: 
                printf("***Bank Management System Using C***\n\n");
                printf("%13s%5s\n"," ","LOGIN");
                printf("%6s%25s\n"," ","=========================");
                printf("%6s%25s\n");
                printf("%6s%25s\n"," ","=========================");
        }
    }
}