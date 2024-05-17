#include <stdio.h>
#include <sys/socket.h>
#include <string.h>

const char LibrarianFile[ ] = "Librarian.bin";

typedef struct {
    char ID[30];
    char Password[30];
} LoginIDPass;

int main(void) {
    // First Create a Login:
    // Login: Option 1:Login, Option 2: Create a new account.
    // Login:
    //      Ask for LoginID, and Password.
    //      Retrieve the LoginID and Password from the Librarian.bin.
    //      Check if it is correct, then proceed.
    //      else Send message: Invalid ID (or) Invalid Password.
    while(1) {
        char LoginID[30], Password[30];
        printf("Please enter your Librarian ID: ");
        scanf("%s", LoginID);
        printf("Please enter your Librarian Password: ");
        scanf("%s", Password);

        printf("\n\n\n");

        FILE* fptr = fopen(LibrarianFile, "rb+");

        LoginIDPass Temp;
        int login = 0;

        while(fread(&Temp, sizeof(Temp), 1, fptr) != 0) {
            if(strcmp(Temp.ID, LoginID) == 0) {
                if(strcmp(Temp.Password, Password)) {
                    printf("Login Successful !!\n");
                    login = 1;
                } else {
                    printf("Wrong Password Entered!!\n");
                }
                break;
            }
        }

        if(login) break;
    }

    // Create a TCP Socket which is used to create new thread and service the 
    int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    
    return 0;
}
