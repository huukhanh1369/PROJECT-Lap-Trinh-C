#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define FILE_NAME "account.bin"
#define MAX_ACCOUNTS 100

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

extern Account accounts[MAX_ACCOUNTS];
extern int accountCount;
