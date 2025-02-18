#include "function.h"

int main() {
	loadAccountsFromFile();
    int choice;
    do {
        printf("***Bank Management System Using C***\n\n");
        printf("%10s%16s\n"," ","CHOOSE YOUR ROLE");
        printf("%6s%25s\n"," ","=========================");
        printf("%6s%10s\n"," ","[1] Admin.");
        printf("%6s%9s\n"," ","[2] User.");
        printf("%5s%22s\n"," ","[0] Exit The Program.");
        printf("%6s%25s\n"," ","=========================");
        printf("%6s%18s"," ","Enter the choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
            	system("cls");
                adminLogin();
                break;
            case 2:
            	system("cls");
            	loginUser();
            	break;
            case 0:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Try again!\n");
        }
    }while(choice!= 0);
    return 0;
}
