#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>

#define ADMIN_FILE "admin.bin"
#define FILE_NAME "account.bin"
#define MAX_ACCOUNTS 100
#define MAX_USERNAME_LENGTH 30
typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char userId[13];
    char fullName[50];
    char email[50];
    char phone[15];
    char username[30];
    char password[30];
    int gender; // 0: Male, 1: Female
    Date dateOfBirth;
    float balance;
    bool status; // true: Open, false: Locked
} Account;

typedef struct {
    char username[30];
    char password[30];
} AdminAccount;

extern Account accounts[MAX_ACCOUNTS];
extern int accountCount;
