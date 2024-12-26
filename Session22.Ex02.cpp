#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define FILE_NAME "accounts.dat"

typedef struct {
    char username[50];
    char password[50];
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

void loadFromFile() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file != NULL) {
        accountCount = fread(accounts, sizeof(Account), MAX_ACCOUNTS, file);
        fclose(file);
    }
}

void saveToFile() {
    FILE *file = fopen(FILE_NAME, "wb");
    if (file != NULL) {
        fwrite(accounts, sizeof(Account), accountCount, file);
        fclose(file);
    }
}

int isUsernameExist(char *username) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void registerAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Danh sach tai khoan da day.\n");
        return;
    }
    Account newAccount;
    char confirmPassword[50];

    while (1) {
        printf("Nhap tai khoan: ");
        scanf("%s", newAccount.username);

        if (isUsernameExist(newAccount.username)) {
            printf("Tai khoan da ton tai. Vui long nhap tai khoan khac.\n");
        } else {
            break;
        }
    }

    printf("Nhap mat khau: ");
    scanf("%s", newAccount.password);

    printf("Xac nhan lai mat khau: ");
    scanf("%s", confirmPassword);

    if (strcmp(newAccount.password, confirmPassword) != 0) {
        printf("Mat khau xac nhan khong khop. Dang ky that bai.\n");
        return;
    }

    accounts[accountCount++] = newAccount;
    saveToFile();
    printf("Dang ky thanh cong.\n");
}

void login() {
    char username[50], password[50];
    printf("Nhap tai khoan: ");
    scanf("%s", username);
    printf("Nhap mat khau: ");
    scanf("%s", password);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 &&
            strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong.\n");
            return;
        }
    }

    printf("Dang nhap that bai. Vui long kiem tra lai thong tin.\n");
}

void menu() {
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: login(); break;
            case 2: registerAccount(); break;
            case 3: printf("Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (choice != 3);
}

int main() {
    loadFromFile();
    menu();
    return 0;
}

