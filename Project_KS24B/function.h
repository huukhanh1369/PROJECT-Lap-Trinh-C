#include "datatype.h"

bool isDuplicate(const char *userId, const char *email, const char *phone, const char *username);
bool isValidDate(int day, int month, int year);
bool isValidGmail();
void getPassword();


void addAccount();
void showAllAccounts();
void lockUnlockAccount();
void searchUserByID();
void sortAccounts();

void adminMenu();


void adminLogin();
void loginUser();


void waitForBackOrExit();

bool isValidName();
bool isValidNumber();


void saveAccountsToFile();
void loadAccountsFromFile();
void saveAdminAccount();