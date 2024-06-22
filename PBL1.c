#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
// #include <math.h>

// danh sách mẫu tin
struct NumberInfo
{
    char *number;
    char *owner;
    char *address;
    char *city;
};

typedef struct NumberInfo *numberInfo;

// danh bạ
struct Node
{
    struct Node *next;
    struct NumberInfo value;
    struct Node *prev;
};

typedef struct Node *List;
typedef struct Node *Position;

// create a list of number
List create()
{
    List L = malloc(sizeof(struct Node));
    L->next = NULL;
    L->prev = NULL;
    return L;
}

int countList(List L)
{
    int count = 0;
    while (L != NULL)
    {
        ++count;
        L = L->next;
    }
    return count;
}

Position findex(List L, int index)
{
    if (index > countList(L))
        return NULL;

    Position p = L;
    int count = 1;
    while (count != index)
    {
        ++count;
        p = p->next;
    }
    return p;
}

void loaibokhoangtrang(char *str)
{
    if (str == NULL || *str == '\0')
        return;

    char *start = str;
    while (isspace(*start))
        start++;

    char *dest = str;
    while (*start != '\0')
        *dest++ = *start++;

    while (dest > str && isspace(*(dest - 1)))
        dest--;

    *dest = '\0';
}

void check(int *choice, int n)
{
    int chck, count = 3;
    for (;;)
    {
        if (!count)
        {
            printf("Error!\n");
            return;
        }
        count--;
        printf("\nYour choice: ");
        chck = scanf("%d", choice);
        getchar();
        if (!(chck == 1 && *choice >= 1 && *choice <= n))
        {
            printf("Value must be a number from 1 to %d\n!! Please choose again.\n", n);
            continue;
        }
        else
            break;
    }
}

/*-------------------------------------------------INSERT--------------------------------------------------*/
//------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
// nhap vao mot so dien thoai moi va them vao contacts L
void viethoa(char *str)
{
    int length = strlen(str);
    int i;

    if (length > 0)
        str[0] = toupper(str[0]);

    for (i = 1; i < length; i++)
        if (isspace(str[i]) && islower(str[i + 1]))
            str[i + 1] = toupper(str[i + 1]);
}

void insertFirst(List *pL, struct NumberInfo num)
{
    Position newItem = malloc(sizeof(struct Node));

    if (newItem == NULL)
    {
        printf("Not enough memory!\n");
        return;
    }

    newItem->value = num;
    newItem->next = *pL;
    newItem->prev = NULL;

    if (*pL != NULL)
    {
        (*pL)->prev = newItem;
    }
    *pL = newItem;
}

// chèn vị trí bất kì
Position insert(List *pL, struct NumberInfo e, Position p)
{
    Position newItem = malloc(sizeof(struct Node));
    newItem->value = e;
    if (*pL == NULL || p == NULL)
    {
        newItem->next = NULL;
        *pL = newItem;
    }
    else
    {
        newItem->next = p->next;
        newItem->prev = p;
        p->next = newItem;
        if (newItem->next != NULL)
        {
            newItem->next->prev = newItem;
        }
    }
    return newItem;
}

// chèn vào đầu hoặc cuối danh sách
void add(List *L, struct NumberInfo num, int choose)
{
    Position q = *L;
    switch (choose)
    {
    case 1:
        insertFirst(L, num);
        break;
    case 2: // chen cuoi danh sach
        if (q == NULL)
        {
            insertFirst(L, num);
        }
        else
        {
            while (q->next != NULL)
                q = q->next;
            insert(L, num, q);
        }
        break;
    default:
        break;
    }
}

// chèn bất kỳ
void insertP(List *L, struct NumberInfo e, int index)
{
    Position p = findex(*L, index);
    if (p == NULL)
    {
        printf("\nElement non-exist!\n");
        return;
    }
    if (index == 1)
        insertFirst(L, e);
    else
        insert(L, e, p->prev);
}

/*-------------------------------------------------SET NUMBER-------------------------------------------------------*/
//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------
// create one new number element

int isAllDigits(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (!isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int is_Alpha(char *str)
{
    int i, len = strlen(str);
    for (i = 0; i < len; i++)
        if (!isalpha(str[i]) && !isspace(str[i]))
            return 0;
    return 1;
}

void set(char *str, int choose)
{
    do
    {
        fgets(str, 100, stdin);
        str[strcspn(str, "\n")] = '\0';
        viethoa(str);
        if (choose == 2)
            return;
        if (!is_Alpha(str))
            printf("Should only in alphabet!\nPlease type again: ");
    } while (!is_Alpha(str));
    loaibokhoangtrang(str);
}

struct NumberInfo setNumber()
{
    struct NumberInfo one;
    char str[100];

    do
    {
        printf("\nSo dien thoai: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        if (!isAllDigits(str) || strlen(str) != 10)
            printf("\nSdt phai la 1 day so gom 10 so!");
    } while (!isAllDigits(str) || strlen(str) != 10);
    one.number = strdup(str);

    printf("Chu so huu: ");
    set(str, 1);
    one.owner = strdup(str);

    printf("Dia chi: ");
    set(str, 2);
    one.address = strdup(str);

    printf("Thanh pho: ");
    set(str, 1);
    one.city = strdup(str);

    return one;
}

/*-------------------------------------------------DISPLAY----------------------------------------------------------*/
//-----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
// in danh sách thông tin tất cả danh bạ
void display(List L, int choose) // choose = 0 <=> in 1 Position
{
    printf("\n");
    printf("    -----------------------------------------------------------------------------------------\n");
    printf("   |  Number  |     owner      |                Address                 |        City        |\n");
    printf("    -----------------------------------------------------------------------------------------\n");
    int count = 1;
    if (!choose && L != NULL)
    {
        printf("   |%-10s|%-15s |%-39s |%-20s|\n", L->value.number, L->value.owner, L->value.address, L->value.city);

        printf(" --------------------------------------------------------------------------------------- \n");
        return;
    }
    while (L != NULL)
    {
        printf("%2d |%-10s|%-15s |%-40s|%-20s|\n", count++, L->value.number, L->value.owner, L->value.address, L->value.city);
        L = L->next;
    }
    printf(" ---------------------------------------------------------------------------------------\n");
    printf("\n");
}

void displayCity(List L)
{
    printf("\nCurrent cities: \n");
    int count = 1;
    while (L != NULL)
    {
        printf("%d. %s\n", count++, L->value.city);
        L = L->next;
    }
    printf("\n");
}

/*-------------------------------------------------FIND--------------------------------------------------------------*/
//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
// tìm kiếm theo các tiêu chí
int findNumber(struct NumberInfo one, char *data)
{
    return strcmp(one.number, data);
}

int findCity(struct NumberInfo one, char *data)
{
    return strcmp(one.city, data);
}

int findAddress(struct NumberInfo one, char *data)
{
    return strcmp(one.address, data);
}

int findOwner(struct NumberInfo one, char *data)
{
    return strcmp(one.owner, data);
}

Position find(List L, int (*f)(struct NumberInfo, char *), char *data)
{
    while (L != NULL)
    {
        if (!(*f)(L->value, data))
            return L;
        L = L->next;
    }
    return NULL;
}

List findAll(List L, int (*f)(struct NumberInfo, char *), char *data, int *count)
{
    List resultList = create();
    resultList = NULL;
    Position p;
    *count = 0;

    while (L != NULL)
    {
        if (!(*f)(L->value, data))
        {
            p = insert(&resultList, L->value, p);
            (*count)++;
        }
        L = L->next;
    }
    return resultList;
}

/*-------------------------------------------------COUNT NUMBER BY CITY && LIST CITY--------------------------------------------*/
//---------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
// list all city in Contacts
List City(List L)
{
    List City = create();
    City = NULL;
    Position q;

    if (L != NULL)
        q = insert(&City, L->value, City);
    L = L->next;
    while (L != NULL)
    {
        if (find(City, findCity, L->value.city) == NULL)
            q = insert(&City, L->value, q);
        L = L->next;
    }

    return City;
}

// liệt kê danh bạ từng tỉnh thành + thống kê số lượng thuê bao
void listCity(List L, int choose) // choose sẽ được handle trong main (switch case)
{
    List listCity = City(L);
    List findCities;
    int count;
    printf("  --------------------\n");
    while (listCity != NULL)
    {
        findCities = findAll(L, findCity, listCity->value.city, &count);
        printf("  |%-15s| %d|\n", listCity->value.city, count);
        printf("  --------------------\n");

        if (choose == 4)
            display(findCities, 1);
        listCity = listCity->next;
    }
}

/*-------------------------------------------------ARRANGE--------------------------------------------------------------*/
//------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
int compareByNumber(struct NumberInfo a, struct NumberInfo b)
{
    return strcmp(a.number, b.number);
}

int compareByCity(struct NumberInfo a, struct NumberInfo b)
{
    return strcmp(a.city, b.city);
}

int compareByOwner(struct NumberInfo a, struct NumberInfo b)
{
    return strcmp(a.owner, b.owner);
}

int compareByAddress(struct NumberInfo a, struct NumberInfo b)
{
    return strcmp(a.address, b.address);
}

void swapNodes(List *pL, Position first, Position second)
{
    struct NumberInfo temp = first->value;
    first->value = second->value;
    second->value = temp;
}

// sắp xếp theo các tiêu chí
void Arrange(List *pL, int (*compare)(struct NumberInfo, struct NumberInfo), int ascending)
{
    int swapped;
    Position L, next, lastPtr = NULL;

    if (*pL == NULL || (*pL)->next == NULL)
        return;

    do
    {
        swapped = 0;
        L = *pL;

        while (L->next != lastPtr)
        {
            next = L->next;
            if ((ascending && compare(L->value, next->value) > 0) ||
                (!ascending && compare(L->value, next->value) < 0))
            {
                swapNodes(pL, L, next);
                swapped = 1;
            }
            L = next;
        }
        lastPtr = L;
    } while (swapped);
}
/*--------------------------------------------------DELETE && DUPLICATE-------------------------------------------------*/
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
// xóa mẫu tin
void delete(List *L, Position p)
{
    if (p == NULL)
        return;

    if ((*L) == p)
        *L = p->next;
    else
        p->prev->next = p->next;

    if (p->next != NULL)
        p->next->prev = p->prev;

    free(p);
}

// xóa theo index
void deleteP(List *L, int index)
{
    Position p = findex(*L, index);
    if (p == NULL)
    {
        printf("\nElement non-exist!\n");
        return;
    }
    delete (L, p);
}

// Tìm và thông báo nếu có trùng lặp, xóa
int duplicate(List *L)
{
    Position p = *L, temp, nextTemp;
    int found = 0;

    while (p != NULL && p->next != NULL)
    {
        temp = p->next;
        while (temp != NULL)
        {
            nextTemp = temp->next;
            if (strcmp(p->value.number, temp->value.number) == 0 && strcmp(p->value.city, temp->value.city) == 0)
            {
                printf("Co su trung lap giua hai phan tu:\n");
                display(p, 0);
                display(temp, 0);
                printf("Ban muon xoa phan tu nao?\n1. Phan tu dau\n2. Phan tu sau\n3. Khong xoa\n");
                int choose;
                scanf("%d", &choose);
                switch (choose)
                {
                case 1:
                    delete (L, p);
                    p = p->prev;
                    if (p == NULL)
                        p = *L;
                    else
                        p = p->next;
                    break;
                case 2:
                    delete (L, temp);
                    break;
                default:
                    break;
                }
                if (choose != 3)
                    found = 1;
            }
            temp = nextTemp;
        }
        if (p != NULL)
            p = p->next;
    }
    return found;
}

/*---------------------------------------------------FILE HANDLING------------------------------------------------------*/
//------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

void doc(char *file)
{
    FILE *f;
    int count = 3;
    while (1)
    {
        if (!count)
        {
            printf("Error!\n");
            return;
        }
        printf("\nNhap file : ");
        scanf("%s", file);
        f = fopen(file, "r");

        if (f == NULL)
        {
            count--;
            printf("File khong ton tai! \n");
            continue;
        }
        break;
    }
}

void Doc_File_Thong_Tin_So_Dien_Thoai(FILE *filein, struct NumberInfo *e)
{
    char line[256];
    if (fgets(line, sizeof(line), filein) != NULL)
    { // Loại bỏ ký tự xuống dòng cuối dòng
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ",");
        loaibokhoangtrang(token);
        e->number = strdup(token);

        token = strtok(NULL, ",");
        loaibokhoangtrang(token);
        viethoa(token);
        e->owner = strdup(token);

        token = strtok(NULL, ",");
        loaibokhoangtrang(token);
        viethoa(token);
        e->address = strdup(token);

        token = strtok(NULL, "\n");
        loaibokhoangtrang(token);
        viethoa(token);
        e->city = strdup(token);
    }
}

// Hàm đọc danh sách số điện thoại từ file
void Doc_Danh_Sach_So_Dien_Thoai(List *pL, char *file)
{
    FILE *f = fopen(file, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Khong mo duoc file\n");
        exit(EXIT_FAILURE);
    }

    struct NumberInfo e;
    while (!feof(f))
    {
        e.number = NULL;
        Doc_File_Thong_Tin_So_Dien_Thoai(f, &e);

        if (e.number != NULL)
        {
            add(pL, e, 2);
        }
    }
    fclose(f);
}

void outFile(char *file, List L)
{
    FILE *f;
    f = fopen(file, "w");

    if (f == NULL)
    {
        perror("Unable to open the file");
        return 1;
    }
    while (L != NULL)
    {
        fprintf(f, "%s, %s, %s, %s\n", L->value.number, L->value.owner, L->value.address, L->value.city);
        L = L->next;
    }

    fclose(f);
    return 0;
}

/*---------------------------------------------------MENU INTERFACE-----------------------------------------------------------*/
//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------

void intro()
{
    printf("\n");
    printf("--------------------------------------------------------------\n");
    printf("-------------- DE TAI : QUAN LY DANH BA DIEN THOAI -----------\n");
    printf("--------------------------------------------------------------\n");
    printf("\n");
    printf("GIAO VIEN HUONG DAN : DO THI TUYET HOA\n");
    printf("\n");
    printf("NHOM SINH VIEN THUC HIEN :\n");
    printf("\n   + DOAN DINH HOANG\n");
    printf("   + HOANG NGUYEN TAI DANH\n");
    printf("\n");
    printf("--------------------------------------------------------------\n");
}

void menu(int *choice)
{

    printf("\t           --------MENU--------\n");
    printf("\t  ------------------------------------\n");
    printf("\t |1. DOC FILE LAY DU LIEU             |      \n");
    printf("\t |2. HIEN THI DANH BA                 |     \n");
    printf("\t |3. QUAN LY DANH BA                  |     \n");
    printf("\t |4. TIM KIEM THEO TIEU CHI           |     \n");
    printf("\t |5. LIET KE THEO TINH THANH          |     \n");
    printf("\t |6. THONG KE SO LUONG THEO TINH THANH|     \n");
    printf("\t |7. THONG BAO NEU CO TRUNG LAP VA XOA|     \n");
    printf("\t |8. CHINH SUA 1 SO TRONG DANH BA     |     \n");
    printf("\t |9. THOAT                            |     \n");
    printf("\t  ------------------------------------\n");

    check(choice, 9);
}

int sapxep()
{
    printf("\n1. Tang dan\n2. Giam dan\n");
    int choose;
    check(&choose, 2);
    if (choose == 2)
        return 0;
    return 1;
}

void sapxeptheo(List *pL)
{
    printf("\t  --------------------------------------------\n");
    printf("\t |1. SAP XEP THEO SDT                           |     \n");
    printf("\t |2. SAP XEP THEO TINH THANH                    |     \n");
    printf("\t |3. SAP XEP THEO CHU SO HUU                    |     \n");
    printf("\t |4. SAP XEP THEO DIA CHI                       |     \n");
    printf("\t |5. QUAY LAI MENU                              |     \n");
    printf("\t  --------------------------------------------\n");
    int chck, choose, (*f)(struct NumberInfo, struct NumberInfo);
    check(&choose, 5);
    switch (choose)
    {
    case 1:
        f = compareByNumber;
        break;
    case 2:
        f = compareByCity;
        break;
    case 3:
        f = compareByOwner;
        break;
    case 4:
        f = compareByAddress;
        break;
    case 5:
        return;
    }
    Arrange(pL, f, sapxep());
    display(*pL, 1);
}

void chen(List *L)
{
    Position p = *L;
    int choose;
    struct NumberInfo one;
    char str[100];
    int count = 3;
    int a = 0;

sdt:
    do
    {
        printf("\nSo dien thoai: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        if (!isAllDigits(str) || strlen(str) != 10)
            printf("\nSdt phai la 1 day so gom 10 so!");
    } while (!isAllDigits(str) || strlen(str) != 10);
    one.number = strdup(str);

    while (p != NULL)
    {
        if (strcmp(p->value.number, one.number) == 0)
        {
            count--;
            display(p, 0);
            printf("\nThe number is existed!\n");
            if (!count)
            {
                printf("Qua so lan quy dinh");
                return;
            }

            printf("\n1. Nhap lai sdt\n2. Cap nhat thong tin sdt nay\n3. Quay lai");
            check(&choose, 3);
            switch (choose)
            {
            case 1:
                goto sdt;

            case 2:
                a = 1;
                goto nhay;

            case 3:
                return;
            }
        }
        p = p->next;
    }

nhay:
    if (a == 1)
    {
        printf("Chu so huu: ");
        set(str, 1);
        free(p->value.owner);
        p->value.owner = strdup(str);

        printf("Dia chi: ");
        set(str, 2);
        free(p->value.address);
        p->value.address = strdup(str);

        printf("Thanh pho: ");
        set(str, 1);
        free(p->value.city);
        p->value.city = strdup(str);

        display(p, 0);
        return;
    }

    printf("Chu so huu: ");
    set(str, 1);
    one.owner = strdup(str);

    printf("Dia chi: ");
    set(str, 2);
    one.address = strdup(str);

    printf("Thanh pho: ");
    set(str, 1);
    one.city = strdup(str);

    printf("\n1. Chen vao dau danh sach\n2. Chen cuoi danh sach\n3. Chen vao mot vi tri\n");
    int index;
    check(&choose, 3);

    switch (choose)
    {
    case 1:
        add(L, one, 1);
        break;
    case 2:
        add(L, one, 2);
        break;
    case 3:
        display(*L, 1);
        printf("\n\nNhap vi tri ban muon chen: ");
        check(&index, countList(*L));
        insertP(L, one, index);
        break;
    }
    printf("Ban co muon sap xep lai danh sach khong?\n1. Yes\n2. No\n");
    check(&choose, 2);
    if (choose == 1)
        sapxeptheo(L);
}

void option3(List *Contacts)
{
    int choice, index;
    printf("\t  --------------------------------------------\n");
    printf("\t |1. THEM SO DIEN THOAI                       |     \n");
    printf("\t |2. SAP XEP                                  |     \n");
    printf("\t |3. XOA MOT SO DIEN THOAI                    |     \n");
    printf("\t |4. TRO VE MENU                              |     \n");
    printf("\t  --------------------------------------------\n");

    check(&choice, 4);

    switch (choice)
    {
    case 1:
        chen(Contacts);
        break;

    case 2:
        sapxeptheo(Contacts);
        break;

    case 3:
        display(*Contacts, 1);
        printf("\n\nNhap vi tri ban muon xoa :  ");
        check(&index, countList(*Contacts));
        deleteP(Contacts, index);
        printf("\n DA XOA VI TRI %d XONG!", index);
        break;

    case 4:
        return;
    }
}

void option4(List Contacts)
{
    {
        display(Contacts, 1);
        int choice;
        printf("\t  --------------TIM KIEM THEO--------------\n");
        printf("\t |1. SDT                                   |     \n");
        printf("\t |2. TINH THANH                            |     \n");
        printf("\t |3. DIA CHI                               |     \n");
        printf("\t |4. CHU SO HUU                            |      \n");
        printf("\t |5. TRO VE MENU                           |     \n");
        printf("\t  -----------------------------------------\n");
        check(&choice, 5);
        int count;
        char str[100];
        int (*f)(struct NumberInfo, char *);
        List findby;
        if (choice == 1)
        {
            printf("VUI LONG NHAP SDT MUON TIM :");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0';
            f = findNumber;
        }
        if (choice == 2)
        {
            printf("VUI LONG NHAP TEN TINH THANH :");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0';
            viethoa(str);
            f = findCity;
        }
        if (choice == 3)
        {
            printf("VUI LONG NHAP TEN DIA CHI :");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0';
            viethoa(str);
            f = findAddress;
        }
        if (choice == 4)
        {
            printf("VUI LONG NHAP TEN CHU SO HUU :");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0';
            viethoa(str);
            f = findOwner;
        }
        if (choice == 5)
        {
            return;
        }
        findby = findAll(Contacts, f, str, &count);
        if (findby != NULL)
        {
            printf("\nFOUND: ");
            display(findby, 1);
        }
        else
            printf("\nNOT FOUND\n");
    }
}

void menu_edit()
{
    printf("\n1. So dien thoai\n2. Chu so huu\n3. Dia chi\n4. Thanh pho\n5. Quay ve menu\n");
}

void edit(List *L, char *file)
{
    int index, chck, choose;
    char str[100];
    display(*L, 1);
    for (;;)
    {
        printf("\nVi tri danh ba ban muon chinh sua: ");
        chck = scanf("%d", &index);
        getchar();
        if (!(index > 0 && chck == 1 && index <= countList(*L)))
        {
            printf("Value must be a number from 1 to %d\n!! Please choose again.\n", countList(*L));
            continue;
        }
        else
            break;
    }
    Position p = findex(*L, index);
    menu_edit();
    check(&choose, 5);
    switch (choose)
    {
    case 1:
        printf("\nSo dien thoai hien tai: %s\n", p->value.number);
        printf("Nhap so dien thoai moi: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        strcpy(p->value.number, str);
        break;
    case 2:
        printf("\nChu so huu hien tai: %s\n", p->value.owner);
        printf("Nhap chu so huu moi: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        strcpy(p->value.owner, str);
        break;
    case 3:
        printf("\nDia chi hien tai: %s\n", p->value.address);
        printf("Nhap dia chi moi: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        strcpy(p->value.address, str);
        break;
    case 4:

        printf("\nThanh pho hien tai: %s\n", p->value.city);
        printf("Nhap thanh pho moi: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        strcpy(p->value.city, str);
        break;
    case 5:
        break;
    }

    outFile(file, *L);
}

int check_null(List L, int choose)
{
    if (L == NULL)
    {
        if (choose != 1)
            printf("Ban chua doc file!\nHay quay lai menu de doc du lieu!\n");
        return 1;
    }
    return 0;
}

int main()
{
    int choice = 1;
    system("cls");
    intro();
    printf("\nPress to start!\n");
    getch();
    system("cls");
    List Contacts = create();
    Contacts = NULL;
    char file[100];
    strcpy(file, "contacts2.txt");
    Doc_Danh_Sach_So_Dien_Thoai(&Contacts, file);
    List Current = Contacts;

    while (Current != NULL)
    {
        if (!isAllDigits(Current->value.number) || strlen(Current->value.number) != 10)
        {
            printf("FILE CHUA SDT KHONG HOP LE!!!\nVUI LONG NHAP LAI\n");
            goto nhapten;
        }
        if (!is_Alpha(Current->value.city))
        {
            printf("FILE CHUA TEN THANH PHO KHONG HOP LE!!!\nVUI LONG NHAP LAI\n");
            goto nhapten;
        }
        Current = Current->next;
    }

menu:
    menu(&choice);

    if (choice == 9)
        exit(1);
nhapten:
    if (choice == 1)
    {
        int solan = 5;
        Contacts = NULL;
        while (solan)
        {
            file[0] = '\0';
            doc(file);
            Doc_Danh_Sach_So_Dien_Thoai(&Contacts, file);
            List Current = Contacts;
            while (Current != NULL)
            {
                if (!isAllDigits(Current->value.number) || strlen(Current->value.number) != 10)
                {
                    printf("\nFILE CHUA SO DIEN THOAI KHONG HOP LE!!!\n");
                    break;
                }
                if (is_Alpha(Current->value.city) == 0)
                {
                    printf("FILE CHUA TEN THANH PHO KHONG HOP LE!!!\n");
                    break;
                }
                Current = Current->next;
            }
            if (Current == NULL)
                break;
            solan--;
        }
        if (!solan)
            exit(1);
        else
            printf("Doc file thanh cong!\n");
    }

    else
    {
        if (check_null(Contacts, choice))
        {
        }
        else
            switch (choice)
            {
            case 2:
                display(Contacts, 1);
                break;
            case 3:
                option3(&Contacts);
                outFile(file, Contacts);

                break;
            case 4:
                option4(Contacts);
                break;
            case 5:
                listCity(Contacts, 4);
                break;
            case 6:
                listCity(Contacts, 0);
                break;
            case 7:
                if (duplicate(&Contacts))
                {
                    display(Contacts, 1);
                    outFile(file, Contacts);
                }
                else
                    printf("\nKhong co phan tu trung lap!\n");
                break;
            case 8:
                edit(&Contacts, file);
                break;
            }
    }
    printf("\n Nhan phim bat ky de quay lai menu...");
    getch();

    system("cls");
    goto menu;
    free(Contacts);
    return 0;
}
