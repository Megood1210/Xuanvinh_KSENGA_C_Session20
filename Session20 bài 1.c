#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
    char bookID[100];
    char title[100];
    char author[100];
    float price;
    char category[100];
} Book;
Book books[100];
int bookCount = 0;
void inputBook(Book *b) {
    printf("Nhap ma sach: ");
    scanf("%s", b->bookID);
    getchar();
    printf("Nhap ten sach: ");
    fgets(b->title, 100, stdin);
    b->title[strcspn(b->title, "\n")] = 0; 
    printf("Nhap tac gia: ");
    fgets(b->author, 100, stdin);
    b->author[strcspn(b->author, "\n")] = 0; 
    printf("Nhap gia sach: ");
    scanf("%f", &b->price);
    getchar();
    printf("Nhap the loai: ");
    fgets(b->category, 100, stdin);
    b->category[strcspn(b->category, "\n")] = 0; 
}
void showBook(Book b) {
    printf("Ma sach: %s\n", b.bookID);
    printf("Ten sach: %s\n", b.title);
    printf("Tac gia: %s\n", b.author);
    printf("Gia tien: %.2f\n", b.price);
    printf("The loai: %s\n", b.category);
    printf("-----------------------------\n");
}
void inputBooks() {
    printf("Nhap so luong sach: ");
    scanf("%d", &bookCount);
    getchar(); 
    for (int i = 0; i < bookCount; i++) {
        printf("\nNhap thong tin sach thu %d: \n", i + 1);
        inputBook(&books[i]);
    }
}
void showBooks() {
    if (bookCount == 0) {
        printf("Khong co sach trong danh sach.\n");
    } else {
        for (int i = 0; i < bookCount; i++) {
            showBook(books[i]);
        }
    }
}
void addBookAtPosition() {
    int pos;
    printf("Nhap vi tri can them (0 den %d): ", bookCount);
    scanf("%d", &pos);
    getchar();  
    if (pos < 0 || pos > bookCount) {
        printf("Vi tri khong hop le.\n");
        return;
    }
    for (int i = bookCount; i > pos; i--) {
        books[i] = books[i - 1];
    }
    printf("Nhap thong tin sach moi:\n");
    inputBook(&books[pos]);
    bookCount++;
}
void deleteBookByID() {
    char bookID[100];
    printf("Nhap ma sach can xoa: ");
    scanf("%s", bookID);
    int i;
    for (i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookID, bookID) == 0) {
            // Di chuy?n các sách t? v? trí i v? tru?c m?t v? trí
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            printf("Da xoa sach co ma: %s\n", bookID);
            return;
        }
    }
    printf("Khong tim thay sach co ma: %s\n", bookID);
}
void updateBookByID() {
    char bookID[100];
    printf("Nhap ma sach can cap nhat: ");
    scanf("%s", bookID);
    int i;
    for (i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookID, bookID) == 0) {
            printf("Nhap thong tin moi cho sach:\n");
            inputBook(&books[i]);
            printf("Da cap nhat thong tin sach.\n");
            return;
        }
    }
    printf("Khong tim thay sach co ma: %s\n", bookID);
}
void sortBooksByPrice(int ascending) {
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = i + 1; j < bookCount; j++) {
            if ((ascending && books[i].price > books[j].price) || 
                (!ascending && books[i].price < books[j].price)) {
                // Hoán d?i hai sách
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }
    printf("Da sap xep sach theo gia.\n");
}
void searchBookByTitle() {
    char title[100];
    printf("Nhap ten sach can tim: ");
    getchar();  
    fgets(title, 100, stdin);
    title[strcspn(title, "\n")] = 0; 
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, title) != NULL) {
            showBook(books[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay sach theo ten: %s\n", title);
    }
}
int main() {
	 int choice;
    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin sach\n");
        printf("2. Hien thi thong tin sach\n");
        printf("3. Them sach vao vi tri\n");
        printf("4. Xoa sach theo ma sach\n");
        printf("5. Cap nhat thong tin sach theo ma sach\n");
        printf("6. Sap xep sach theo gia (tang/giam)\n");
        printf("7. Tim kiem sach theo ten\n");
        printf("8. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                inputBooks();
                break;
            case 2:
                showBooks();
                break;
            case 3:
                addBookAtPosition();
                break;
            case 4:
                deleteBookByID();
                break;
            case 5:
                updateBookByID();
                break;
            case 6: {
                int sortChoice;
                printf("1. Sap xep tang theo gia\n");
                printf("2. Sap xep giam theo gia\n");
                printf("Lua chon: ");
                scanf("%d", &sortChoice);
                sortBooksByPrice(sortChoice == 1);
                break;
            }
            case 7:
                searchBookByTitle();
                break;
            case 8:
                printf("Thoat chuong trinh \n");
                break;
            default:
                printf("Lua chon khong hop le \n");
                break;
        }
    } while (choice != 8);
    return 0;
}




