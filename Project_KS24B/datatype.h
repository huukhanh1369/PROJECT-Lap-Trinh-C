#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ACCOUNTS 100  


struct date {
    int day, month, year;
};


struct accountInfo {
    char userId[12];
    char fullName[30];
    char username[30];
    char password[30];
    char email[30];
    char phone[11];
    bool gender;
    struct date dateOfBirth;
    float balance;
    bool status; 
};
