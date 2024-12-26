#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILE_NAME "students.dat"

typedef struct {
    int id;
    char name[50];
    int age;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void loadFromFile() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file != NULL) {
        studentCount = fread(students, sizeof(Student), MAX_STUDENTS, file);
        fclose(file);
    }
}

void saveToFile() {
    FILE *file = fopen(FILE_NAME, "wb");
    if (file != NULL) {
        fwrite(students, sizeof(Student), studentCount, file);
        fclose(file);
    }
}

void displayStudents() {
    printf("\nDanh sach sinh vien:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d, Name: %s, Age: %d\n", students[i].id, students[i].name, students[i].age);
    }
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Danh sach da day.\n");
        return;
    }
    Student s;
    printf("Nhap ID: ");
    scanf("%d", &s.id);
    printf("Nhap Ten: ");
    getchar();
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    printf("Nhap Tuoi: ");
    scanf("%d", &s.age);

    students[studentCount++] = s;
    saveToFile();
    printf("Them sinh vien thanh cong.\n");
}

void editStudent() {
    int id, found = 0;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Nhap Ten moi: ");
            getchar();
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;
            printf("Nhap Tuoi moi: ");
            scanf("%d", &students[i].age);
            found = 1;
            saveToFile();
            printf("Sua thong tin thanh cong.\n");
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien voi ID da nhap.\n");
    }
}

void deleteStudent() {
    int id, found = 0;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            found = 1;
            saveToFile();
            printf("Xoa sinh vien thanh cong.\n");
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien voi ID da nhap.\n");
    }
}

void searchStudent() {
    int id, found = 0;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("ID: %d, Name: %s, Age: %d\n", students[i].id, students[i].name, students[i].age);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien voi ID da nhap.\n");
    }
}

void sortStudents() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].id > students[j].id) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    saveToFile();
    printf("Sap xep danh sach sinh vien thanh cong.\n");
}

void menu() {
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: addStudent(); break;
            case 3: editStudent(); break;
            case 4: deleteStudent(); break;
            case 5: searchStudent(); break;
            case 6: sortStudents(); break;
            case 7: printf("Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (choice != 7);
}

int main() {
    loadFromFile();
    menu();
    return 0;
}

