#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
const char LibrarianFile[ ] = "Librarian.bin";

typedef struct {
    char ID[30];
    char Password[30];
} LoginIDPass;


void Login() {
    while(1) {
        char LoginID[30], Password[30];
        printf("Please enter your Librarian ID: ");
        scanf("%s", LoginID);
        printf("Please enter your Librarian Password: ");
        scanf("%s", Password);
        printf("\n\n\n");

        int fd = open(LibrarianFile, O_RDONLY);
        LoginIDPass Temp;
        int login = 0;

        while(1) {
            read(fd, &Temp.ID, sizeof(Temp));
            if(strcmp(Temp.ID, LoginID) == 0) {
                if(strcmp(Temp.Password, Password)) {
                    printf("Login Successful !!\n");
                    login = 1;
                } else {
                    printf("Wrong Password Entered!!\n");
                    Login();
                }
                break;
            }
        }
        close(fd);
        if(login) return;
        Login();
    }
}

void CreateNewAccount() {
    char LoginID[30], Password[30];
    printf("New LibrarianID: ");
    scanf("%s", LoginID);
    printf("New password");
    scanf("%s", Password);
    int fd = open(LibrarianFile, O_RDWR);
    LoginIDPass Temp;
    int login = 0;

    while(read(fd, &Temp, sizeof(Temp)) != 0) {
        if(strcmp(Temp.ID, LoginID) == 0) {
            printf("Account aldready exists!!");
            login = 1;
            break;
        }
    }
    close(fd);
    if(login) return;
    
}

int main(void)  {
    Login();
    return 0;
}
