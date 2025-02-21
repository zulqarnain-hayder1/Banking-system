#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Bank_Account {
    int Money_Deposit;
    char type;
    int acno;
    char name[70];
};

void write_Bank_Account();
//Delete account 
void delete_Bank_Account(int);
void display_sp(int);
//Delete ALL account 
void display_all();
//Update account 
void Updation_Bank_Account(int);
//Deposit 
void Money_Deposit_withdraw(int, int);

int main() {
    char ch;
    int num;
    do {
        system("cls");
        printf("\n\n\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        printf("\n\t\tBANK MANAGEMENT SYSTEM");
        printf("\n\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        printf("\n\t\t    ::MAIN MENU::\n");
        printf("\n\t\t1. NEW Bank_Account");
        printf("\n\t\t2. Money_Deposit Total-Money");
        printf("\n\t\t3. WITHDRAW Total-Money");
        printf("\n\t\t4. BALANCE ENQUIRY");
        printf("\n\t\t5. ALL Bank_Account HOLDER LIST");
        printf("\n\t\t6. CLOSE AN Bank_Account");
        printf("\n\t\t7. Updation AN Bank_Account");
        printf("\n\t\t8. EXIT");
        printf("\n\n\t\tSelect Your Option (1-8): ");
        scanf(" %c", &ch);

        switch(ch) {
            case '1':
                write_Bank_Account();
                break;
            case '2':
                system("cls");
                printf("\n\n\tPlease Enter The Bank_Account No. : ");
                scanf("%d", &num);
                Money_Deposit_withdraw(num, 1);
                break;
            case '3':
                system("cls");
                printf("\n\n\tPlease Enter The Bank_Account No. : ");
                scanf("%d", &num);
                Money_Deposit_withdraw(num, 2);
                break;
            case '4':
                system("cls");
                printf("\n\n\tPlease Enter The Bank_Account No. : ");
                scanf("%d", &num);
                display_sp(num);
                break;
            case '5':
                display_all();
                break;
            case '6':
                system("cls");
                printf("\n\n\tPlease Enter The Bank_Account No. : ");
                scanf("%d", &num);
                delete_Bank_Account(num);
                break;
            case '7':
                system("cls");
                printf("\n\n\tPlease Enter The Bank_Account No. : ");
                scanf("%d", &num);
                Updation_Bank_Account(num);
                break;
            case '8':
                system("cls");
                
                break;
            default:
                printf("\a");
        }
        while ((ch = getchar()) != '\n' && ch != EOF); // Clear the input buffer
        getchar(); // Wait for Enter key press
    } while(ch != '8');
    return 0;
}
//Create new account 
void write_Bank_Account() {
    FILE *outFile;
    struct Bank_Account ac;
    outFile = fopen("Bank_Account.dat", "ab");
    if (outFile == NULL) {
        printf("File could not be open !! Press any Key...");
        return;
    }
    printf("\n\tPlease Enter the Bank_Account No. : ");
    scanf("%d", &ac.acno);
    printf("\n\n\tPlease Enter the Name of the Bank_Account holder : ");
    scanf(" %[^\n]", ac.name);
    printf("\n\tPlease Enter Type of the Bank_Account (C/S) : ");
    scanf(" %c", &ac.type);
    // toupper convert lower letter to upper 
    ac.type = toupper(ac.type);
    printf("\n\tPlease Enter The Starting Total-Money : ");
    scanf("%d", &ac.Money_Deposit);
    fwrite(&ac, sizeof(struct Bank_Account), 1, outFile);
    fclose(outFile);
    printf("\n\n\tBank_Account Created..");
}

void delete_Bank_Account(int n) {
    FILE *inFile, *outFile;
    struct Bank_Account ac;
    inFile = fopen("Bank_Account.dat", "rb");
    if (inFile == NULL) {
        printf("File could not be open !! Press any Key...");
        return;
    }
    outFile = fopen("Temp.dat", "wb");
    while (fread(&ac, sizeof(struct Bank_Account), 1, inFile)) {
        if (ac.acno != n) {
            fwrite(&ac, sizeof(struct Bank_Account), 1, outFile);
        }
    }
    fclose(inFile);
    fclose(outFile);
    remove("Bank_Account.dat");
    rename("Temp.dat", "Bank_Account.dat");
    printf("\n\nRecord Deleted ..");
}

void display_sp(int n) {
    FILE *inFile;
    struct Bank_Account ac;
    int flag = 0;
    inFile = fopen("Bank_Account.dat", "rb");
    if (inFile == NULL) {
        printf("File could not be open !! Press any Key...");
        return;
    }
    printf("\n\tBALANCE DETAILS\n");
    while (fread(&ac, sizeof(struct Bank_Account), 1, inFile)) {
        if (ac.acno == n) {
            printf("\n\tBank_Account No. : %d", ac.acno);
            printf("\n\tBank_Account Holder Name : %s", ac.name);
            printf("\n\tType of Bank_Account : %c", ac.type);
            printf("\n\tBalance Total-Money : %d", ac.Money_Deposit);
            flag = 1;
        }
    }
    fclose(inFile);
    if (flag == 0)
        printf("\n\n\tBank_Account number does not exist");
}

void display_all() {
    system("cls");
    FILE *inFile;
    struct Bank_Account ac;
    inFile = fopen("Bank_Account.dat", "rb");
    if (inFile == NULL) {
        printf("File could not be open !! Press any Key...");
        return;
    }
    printf("\n\n\t\tBank_Account HOLDER LIST\n\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!========\n");
    printf("A/c no.      NAME           Type  Balance\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!========\n");
    while (fread(&ac, sizeof(struct Bank_Account), 1, inFile)) {
        printf("%-12d%-15s%-6c%-10d\n", ac.acno, ac.name, ac.type, ac.Money_Deposit);
    }
    fclose(inFile);
}

void Updation_Bank_Account(int n) {
    FILE *File;
    struct Bank_Account ac;
    int found = 0;
    File = fopen("Bank_Account.dat", "rb+");
    if (File == NULL) {
        printf("File could not be open !! Press any Key...");
        return;
    }
    while (fread(&ac, sizeof(struct Bank_Account), 1, File)) {
        if (ac.acno == n) {
            printf("\n\tBank_Account No. : %d", ac.acno);
            printf("\n\tBank_Account Holder Name : %s", ac.name);
            printf("\n\tType of Bank_Account : %c", ac

.type);
            printf("\n\tBalance Total-Money : %d", ac.Money_Deposit);
            printf("\n\n\tPlease Enter The New Details of Bank_Account\n");
            printf("\n\tUpdation Bank_Account Holder Name : ");
            scanf(" %[^\n]", ac.name);
            printf("\n\tUpdation Type of Bank_Account : ");
            scanf(" %c", &ac.type);
            ac.type = toupper(ac.type);
            printf("\n\tUpdation Balance Total-Money : ");
            scanf("%d", &ac.Money_Deposit);
            fseek(File, -sizeof(struct Bank_Account), SEEK_CUR);
            fwrite(&ac, sizeof(struct Bank_Account), 1, File);
            printf("\n\n\tRecord Updated");
            found = 1;
        }
    }
    fclose(File);
    if (found == 0)
        printf("\n\n\tRecord Not Found ");
}

void Money_Deposit_withdraw(int n, int option) {
    int amt;
    int found = 0;
    FILE *File;
    struct Bank_Account ac;
    File = fopen("Bank_Account.dat", "rb+");
    if (File == NULL) {
        printf("File could not be open !! Press any Key...");
        return;
    }
    while (fread(&ac, sizeof(struct Bank_Account), 1, File)) {
        if (ac.acno == n) {
            printf("\n\tBank_Account No. : %d", ac.acno);
            printf("\n\tBank_Account Holder Name : %s", ac.name);
            printf("\n\tType of Bank_Account : %c", ac.type);
            printf("\n\tBalance Total-Money : %d", ac.Money_Deposit);
            if (option == 1) {
                printf("\n\n\tTO Money_DepositSS Total-Money");
                printf("\n\n\tPlease Enter The Total-Money to be Money_Deposited: ");
                scanf("%d", &amt);
                ac.Money_Deposit += amt;
            }
            if (option == 2) {
                printf("\n\n\tTO WITHDRAW Total-Money");
                printf("\n\n\tPlease Enter The Total-Money to be withdraw: ");
                scanf("%d", &amt);
                int bal = ac.Money_Deposit - amt;
                if (bal < 0)
                    printf("Insufficience balance");
                else
                    ac.Money_Deposit -= amt;
            }
            fseek(File, -sizeof(struct Bank_Account), SEEK_CUR);
            fwrite(&ac, sizeof(struct Bank_Account), 1, File);
            printf("\n\n\tRecord Updated");
            found = 1;
        }
    }
    fclose(File);
    if (found == 0)
        printf("\n\n\tRecord Not Found ");
}