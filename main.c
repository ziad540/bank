#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"
#define sizeOfStruct 10000
#include<stddef.h>
#include <stdio.h>

typedef struct date
{
    int month;
    int year;
} date;
typedef struct account
{
    long long  accountNumber;
    char accountName[50];
    char accountAddress[50];
    char accountMobile[50];
    float accountBalance;
    date date_open;
} account;

int check_name(char mystring[]);
int check_mail(char mystring[]);
int saveAccounts(account accounts[], int *accountCount);
int loadFile(account accounts[]);
int loginAccount();
void addinfo(long long x, char c, float l);
void addAccount(account accounts[], int *accountCount);
void deleteAccount(account accounts[], int *accountCount);
void query(account accounts[], int accountCount);
void advanced_search(account *ans, int size);
void printCustomer(const account *customer);
void convertToLowerCase(char *str);
int checkNumber_float(char amount_to_deposit[], int size);
int checkInt_Number(char amount_to_deposit[], int size);
void deposit(account accounts[], int accountCount);
void WithDraw(account *accounts, int accountCount);
void transfer(account accounts[], int accountCount);
void report(account *ans, int accountCount);
void modfy(account accounts[],int accountCount);
const char *monthNames[] =
{
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"
};

int advsearchcheck(char x[])
{
    int counter=0;
    for(int i=0; i<strlen(x); i++)
    {
        if(x[i]==' ')
            counter++;
    }

    if(counter>1)
    {
        printf("Name consists of two names only.\n");
        return 0;
    }

    for(int i=0; i<strlen(x); i++)
    {
        if(x[i]!=' ')
            if(!(isalpha(x[i])))
            {
                printf("Name consists of char only.\n");
                return 0;
            }
    }
    return 1;
}

int check_test(char test[])
{
    for(int i=0; i<(int)strlen(test); i++)
    {
        if(!((test[i])>='0'&&(test[i])<='9'))
        {
            printf(RED"Try again please ,number must be digits ONLY.\n"RESET);
            return 0;
        }
    }
    return 1;

}

int check_phone(char phone[])
{
    for(int i=0; i<strlen(phone); i++)
    {
        if(!(phone[i]>='0'&&phone[i]<='9'))
        {
            printf("NUMBER MUST BE DIGITS ONLY\n");
            return 0;
        }
    }
    if(strlen(phone)>15)
    {
        printf("phone numbers cannot contain more than 15 digits \n");
        return 0;
    }
    if(strlen(phone)<7)
    {
        printf("The shortest international phone numbers in use contain seven digits\n");
        return 0;
    }
    return 1;
}

int check_name(char mystring[])
{

    int check_point = 0;
    int flag = 0;

    for (int i = 0; i < strlen(mystring); i++)
    {
        if (i == 0)
        {
            if (!(isalpha((unsigned char)mystring[i])))
            {
                printf(RED"Try again please.\a\n"RESET);
                return 0;
            }
        }
        else
        {
            if (mystring[i] == ' ')
            {
                check_point = i + 1;
                flag = 1;
                break;
            }
            if (!(isalpha((unsigned char)mystring[i])) )
            {
                printf(RED"Try again please.\a\n"RESET);
                return 0;
            }
        }
    }

    if (flag == 0)
    {
        printf(RED"Try again please , The name shall include a space between first and second name .\a\n"RESET);
        return 0;
    }

    for (int i = check_point; i < strlen(mystring); i++)
    {
        if (i == check_point)
        {
            if (!(isalpha((unsigned char)mystring[i])) )
            {
                printf(RED"Try again please.\a\n"RESET);
                return 0;
            }
        }
        else
        {
            if (!(isalpha((unsigned char)mystring[i])) )
            {
                printf(RED"Try again please.\a\n"RESET);
                return 0;
            }
        }
    }
    for(int i=0; i<strlen(mystring); i++)
    {
        if(mystring[i]!=' ')
            mystring[i]=tolower(mystring[i]);
    }
    mystring[0]=toupper(mystring[0]);
    mystring[check_point]=toupper(mystring[check_point]);
    printf(GREEN"String is valid.\n"RESET);
    return 1;

}

int first_menu ()
{
    printf(RED"\t\t\tZAY BANK\n"RESET);
    printf(RED"\t\t\t========\n"RESET);
    int x;
    printf("To LOGIN press 1.\n");
    printf("To QUIT press 0.\n");
    printf("=================\n");
    printf("Your order is : ");

    char inp[20];

    scanf(" %19[^\n]",inp);
    while( !(check_test(inp)))
    {
        printf("enter input again coreectly pls : \n");
        scanf(" %19[^\n]",inp);
    }
    x=atoi(inp);
    while (x>1)
    {
        printf("enter input again coreectly pls from 0 to 1 : \n");
        scanf(" %19[^\n]",inp);
        while( !(check_test(inp)))
        {
            printf("enter input again coreectly pls from 0 to 1 : \n");
            scanf(" %19[^\n]",inp);
        }
        x=atoi(inp);
    }

        if(x==1)
    {
        int y= loginAccount();
        printf("=============================================================================\n");
        if(y==1)
            return 1;
        else
            first_menu ();
    }
    else
        return 0;
}

int check_mail( char *email)
{

   if(!(isalpha(email[0])||(email[0]>='0'&&email[0]<='9')))
   {
       printf("_____________________________________________________________________________\n");
       printf(RED"ERROR TRY AGAIN.\a\n"RESET);
       return 0;
   }

   if(!(isalpha(email[strlen(email)-1])||(email[strlen(email)-1]>='0'&&email[strlen(email)-1]<='9')))
   {
       printf("_____________________________________________________________________________\n");
       printf(RED"ERROR TRY AGAIN.\a\n"RESET);
       return 0;
   }

   int index;

   for(int i=0;i<strlen(email);i++)
   {
       if(email[i]=='.')
        index=i;
   }
   int counter =0;
   for(int i=index+1;i<strlen(email);i++)
   {
       counter ++;
   }
   if(!(counter>=2))
   {
       printf("_____________________________________________________________________________\n");
       printf(RED"ERROR TRY AGAIN.\a\n"RESET);
       return 0;
   }

   for(int i=0;i<strlen(email);i++)
   {
        if(email[i]=='.'&&email[i+1]=='.')
        {
            printf("_____________________________________________________________________________\n");
                   printf(RED"ERROR TRY AGAIN.\a\n"RESET);
          return 0;
        }
   }
   int l=0;
   int left;
   for(int i=0;i<strlen(email);i++)
   {
       if(email[i]=='@')
       {l++;
       left =i;}
   }

   if(l!=1)
   {
       printf("_____________________________________________________________________________\n");
        printf(RED"ERROR TRY AGAIN.\a\n"RESET);
          return 0;
   }

    if(!(isalpha(email[left-1])||(email[left-1]>='0'&&email[left-1]<='9')))
   {
       printf("_____________________________________________________________________________\n");
       printf(RED"ERROR TRY AGAIN.\a\n"RESET);
       return 0;
   }

    if(!(isalpha(email[left+1])||(email[left+1]>='0'&&email[left+1]<='9')))
   {
       printf("_____________________________________________________________________________\n");
       printf(RED"ERROR TRY AGAIN.\a\n"RESET);
       return 0;
   }

   int z=0;

   for(int i=0;i<left-1;i++)
   {
       if(isalpha(email[i]))
        z++;
   }

   if(z==0)
   {
    {
        printf("_____________________________________________________________________________\n");
       printf(RED"ERROR TRY AGAIN.\a\n"RESET);
       return 0;
   }
   }
 int k=0;
 for(int i=left+1;i<strlen(email);i++)
   {
       if(email[i]=='.')
        k++;
   }

if(k!=1)
{
    printf("_____________________________________________________________________________\n");
    printf(RED"ERROR TRY AGAIN.\a\n"RESET);
       return 0;
}

for(int i=0;i<strlen(email);i++)
{
    if(email[i]==' ')
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"ERROR TRY AGAIN.\a\n"RESET);
       return 0;
    }
}
   return 1;
}

int saveAccounts(account accounts[], int *accountCount)
{
    char answer[20];
    printf("Do you want to save changes?");
    printf("press (1) if yes\n");
    printf("press (0)if no\n");

    int g;

    scanf(" %19[^\n]",answer);
    while( !(check_test(answer)))
    {
        printf(RED"Enter input again correctly pls : \n\a"RESET);
        scanf(" %19[^\n]",answer);
    }
    g=atoi(answer);
    while (g>1)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Enter input again coreectly pls from 0 to 1 : \n\a"RESET);
        scanf(" %19[^\n]",answer);
        while( !(check_test(answer)))
        {
            printf("_____________________________________________________________________________\n");
            printf(RED"Enter input again correctly pls from 0 to 1 : \a\n"RESET);
            scanf(" %19[^\n]",answer);
        }
        g=atoi(answer);
    }

    if (g == 1)
    {
        FILE *file = fopen("accounts.txt", "w");

        if (file == NULL)
        {
            printf("_____________________________________________________________________________\n");
            printf(RED"Error opening file\n\a"RESET);
            printf("_____________________________________________________________________________\n");
            return 0;
        }

        for (int i = 0; i < *accountCount; ++i)
        {
            fprintf(file, "%lld,%s,%s,%.2f,%s,%d-%d\n", accounts[i].accountNumber,
                    accounts[i].accountName, accounts[i].accountAddress, accounts[i].accountBalance,
                    accounts[i].accountMobile, accounts[i].date_open.month, accounts[i].date_open.year);
        }

        fclose(file);
        return 1;
    }
    else
    {
        *accountCount = loadFile(accounts);
        return 0;
    }
}

int loadFile(account accounts[])
{
    FILE *f = fopen("accounts.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file\n");
        return 0;
    }

    char line[1024];
    int accountCount = 0;

    while (fgets(line, sizeof(line), f) != NULL)
    {
        account newAccount;

        if (sscanf(line, "%lld,%49[^,],%49[^,],%f,%49[^,],%d-%d",
                   &newAccount.accountNumber, newAccount.accountName,
                   newAccount.accountAddress, &newAccount.accountBalance,
                   newAccount.accountMobile, &newAccount.date_open.month, &newAccount.date_open.year) == 7)
        {
            accounts[accountCount++] = newAccount;
        }
    }
    fclose(f);
    return accountCount;
}

int loginAccount()
{
    FILE* pf1 = fopen("users.txt", "r");
    int line_counter = 0, i;
    char USER[10000];
    char PASS[10000];
    char C_USER[10000];
    char C_PASS[10000];
    int s1 = 0, s2 = 0;
    char N;
    if (pf1 == NULL)
    {
        printf("_____________________________________________________________________________\n");
        printf("Could not open the file.\n");
        printf("_____________________________________________________________________________\n");
        exit(0);
    }

    while ((N = fgetc(pf1)) != EOF)
    {
        if (N == '\n')
        {
            line_counter++;
        }
    }

    fseek(pf1, 0, SEEK_SET);


    printf("=============================================================================\n");
    printf("Please Enter the Username:");
    scanf(" %49[^\n]",USER);

    printf("Please Enter the password:");
    scanf(" %49[^\n]",PASS);

    for (i = 0; i < line_counter; i++)
    {
        fscanf(pf1, "%s", C_USER);
        fscanf(pf1, "%s", C_PASS);
        if (strcmp(C_USER, USER) == 0)
        {
            printf("=============================================================================\n");
            printf(GREEN"Your email matches.\n"RESET);
            s1 = 1;
            printf("=============================================================================\n");


        }
        if (strcmp(C_PASS, PASS) == 0)
        {
            printf(GREEN"Your password matches.\n"RESET);
            s2 = 1;
            printf("=============================================================================\n");

            break;
        }
    }


    if (s1!=1)
    {
        printf("=============================================================================\n");
        printf(RED"Please,Check your E-mail.\n\a"RESET);
        printf("=============================================================================\n");

    }

    if (s2!=1)
    {
        printf("=============================================================================\n");
        printf(RED"Please,Check your Password.\n\a"RESET);
        printf("=============================================================================\n");

    }

    if (s1 == 1 && s2 == 1)
    {
        printf("=============================================================================\n");
        printf(GREEN"Successful login.\n"RESET);
        printf("=============================================================================\n");

    }
    else
    {
            printf("=============================================================================\n");
            printf(RED"Failed to login.\n"RESET);
            printf("=============================================================================\n");

    }
    fclose(pf1);
    if (s1 == 1 && s2 == 1) return 1;

}

void addinfo(long long  x, char c, float l)
{

    FILE *file;

    char filename[20];
    sprintf(filename, "%lld.txt", x);
    file = fopen(filename, "a");

    if (file == NULL)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Error opening the file.\n\a"RESET);
        return;
    }

    fprintf(file, "%c %f ", c, l);
    fclose(file);
}

double checkbalance_add(char amount_to_deposit[])
{
    int dotCount = 0;

    for (int i = 0; i < strlen(amount_to_deposit); i++)
    {
        if (!isdigit(amount_to_deposit[i]) && amount_to_deposit[i] != '.')
        {
            printf("_____________________________________________________________________________\n");
            printf(RED"Enter a valid number please.\a\n"RESET);
            return 0;
        }
        else if (amount_to_deposit[i] == '.')
        {
            dotCount++;
            if (dotCount > 1)
            {
                printf("_____________________________________________________________________________\n");
                printf(RED"Enter a valid number please.\a\n"RESET);
                return 0;
            }
        }
    }
    printf("_____________________________________________________________________________\n");
    double afterT=atof(amount_to_deposit);
    return afterT;
}

long long check_accnum(char str[])
{
    char *endptr;
    long long result;

    result = strtoll(str, &endptr, 10);

    if (*endptr != '\0')
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Error: The input is must be numbers only \n"RESET);
        printf("_____________________________________________________________________________\n");
        return 0;
    }

    if(strlen(str)!=10)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Error: The account number must be 10 nmbers \n"RESET);
        printf("_____________________________________________________________________________\n");
        return 0;
    }
    return result;
}

void addAccount(account accounts[],int *accountCount)
{
    account newAccount;
    long long numberCheck;
    char nn[50];
    char ll[50];

    printf("Please enter the account number :");
    scanf(" %49[^\n]",nn);

    while(!check_accnum(nn))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Please enter the account number again :\a"RESET);
        scanf(" %49[^\n]",nn);
    }
    numberCheck=check_accnum(nn);

    for (int i = 0; i < *(accountCount); i++)
    {

        if (accounts[i].accountNumber == numberCheck)
        {
            printf("_____________________________________________________________________________\n");
            printf(RED"Account with the same number already exists.\a\n"RESET);
            printf("_____________________________________________________________________________\n");
            return ;
        }
    }
    newAccount.accountNumber=numberCheck;

    char test1 [50];
    printf("Enter Name: ");
    scanf(" %49[^\n]", test1);
    while (!check_name(test1))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Enter Name again correctly pls: \a"RESET);
        scanf(" %49[^\n]", test1);

    }

    strcpy(newAccount.accountName, test1);

    printf("Enter Address: ");
    scanf(" %49[^\n]", test1);
    while (!check_mail(test1))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Enter mail again correctly pls: \a"RESET);
        scanf(" %49[^\n]", test1);

    }
    strcpy(newAccount.accountAddress, test1);

    printf("Enter Balance: ");
    scanf(" %49[^\n]",ll);
    while(!checkbalance_add(ll))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Please enter the balance again :\a"RESET);
        scanf(" %49[^\n]",ll);
    }
    newAccount.accountBalance=checkbalance_add(ll);

    char phone[50];
    printf("Enter Mobile: ");
    scanf(" %49[^\n]", phone);
    while(!check_phone(phone))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Enter Mobile again correctly\n: \a"RESET);
        scanf(" %49[^\n]", phone);
    }

    strcpy(newAccount.accountMobile,phone);

    time_t t;
    struct tm *current_time;

    time(&t);
    current_time = localtime(&t);

    newAccount.date_open.month = current_time->tm_mon + 1; // Months are zero-based
    newAccount.date_open.year = current_time->tm_year + 1900; // Years since 1900

    (*accountCount)++;
    accounts[*accountCount-1]=newAccount;

    saveAccounts(accounts,accountCount);
}

void deleteAccount(account accounts[],int *accountCount)
{
    long long numberSearch;
    char nn[50];

    printf("Please enter the account number to delete it  :");
    scanf(" %49[^\n]",nn);
    printf("_____________________________________________________________________________\n");

    while(!check_accnum(nn))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Please enter the account number again correctly pls :"RESET);
        scanf(" %49[^\n]",nn);
        printf("_____________________________________________________________________________\n");
    }

    numberSearch=check_accnum(nn);

    int index=-2;
    for(int i=0; i<*accountCount; i++)
    {
        if(accounts[i].accountNumber==numberSearch)
            index=i;
    }

    if(index==-2)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"The account not exist.\n\a"RESET);
        printf("_____________________________________________________________________________\n");
        return;
    }
    else if(accounts[index].accountBalance>0)
    {

        for(int i=index; i<*accountCount; i++)
        {
            accounts[i]=accounts[i+1];

        }
        (*accountCount)--;
        saveAccounts(accounts,accountCount);
    }
    else
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"The balance should be greater than zero.\n"RESET);
        printf("_____________________________________________________________________________\n");
    }

}

void query(account accounts[], int accountCount)
{
    int z = accountCount;
    long long acc_numberSearch;
    char nn[50];

    printf("Enter account number to be searched: ");
    scanf(" %49[^\n]",nn);

    while(!check_accnum(nn))
    {
        printf("Please enter the account number again correctly pls :");

        scanf(" %49[^\n]",nn);
    }

    acc_numberSearch=check_accnum(nn);

    int i = 0, flag = 0;

    const char *monthNames[] =
    {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    do
    {
        if (acc_numberSearch == accounts[i].accountNumber)
        {
            flag = 1;
            printf("_____________________________________________________________________________\n");
            printf(GREEN"The account is found:\n"RESET);
            printCustomer(&accounts[i]);
            break;
        }
        else
            i++;
    }
    while (--z);

    if (!flag)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"The account is not found.\a\n"RESET);
    }
    }

void modify(account accounts[],int accountCount)
{
    long long  accNo;
    int i, flag =0, response;
    char newAccountName[50], newAccountMobile[50], newAccountAddress[50];

    printf("Enter the account number of the account to be modified :");

   char test1 [50];


    scanf(" %49[^\n]",test1);
    while(!check_accnum(test1))
    {
        printf("_____________________________________________________________________________\n");
        printf("Please enter the account number again :\a"RESET);
        scanf(" %49[^\n]",test1);
    }
    accNo=check_accnum(test1);

    for(i=0; i<accountCount; i++)
    {
        if (accNo==accounts[i].accountNumber)
        {
            flag=1;

            printf("Do you want to change the account name :?",accounts[i].accountName);
            printf(" (1)YES\t\t(0)NO\n");


            char inp[20];
            scanf(" %19[^\n]",inp);
            while( !(check_test(inp)))
            {
                printf("_____________________________________________________________________________\n");
                printf(RED"Enter input again correctly pls : \n\a"RESET);
                scanf(" %19[^\n]",inp);
            }
            response=atoi(inp);
            while (response>1)
            {
                printf(RED"Enter input again correctly pls either 0 or 1 : \a\n"RESET);
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again coreectly pls either 0 or 1 : \a\n"RESET);
                    scanf(" %19[^\n]",inp);
                }
                response=atoi(inp);
            }


            printf("\n");
            if(response==1)
            {
                char test1 [50];
                printf("Enter NEW Name: ");
                scanf(" %49[^\n]", test1);
                while (!check_name(test1))
                {
                    printf("Enter NEW Name again coreectly pls: ");
                    scanf(" %49[^\n]", test1);

                }

                strcpy(accounts[i].accountName, test1);
            }

            printf("Do you want to change the account mobile number :?",accounts[i].accountMobile);
            printf("(1)YES\t(0)NO\n");

            scanf(" %19[^\n]",inp);
            while( !(check_test(inp)))
            {
                printf("_____________________________________________________________________________\n");
                printf(RED"Enter input again correctly pls : \n\a"RESET);
                scanf(" %19[^\n]",inp);
            }
            response=atoi(inp);
            while (response>1)
            {
                printf("_____________________________________________________________________________\n");
                printf(RED"Enter input again coreectly pls either 0 or 1 : \n\a"RESET);
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls either 0 or 1 : \n\a"RESET);
                    scanf(" %19[^\n]",inp);
                }
                response=atoi(inp);
            }


            if(response==1)
            {
                char phone[50];
                printf("Enter the NEW account mobile number: ");
                scanf(" %49[^\n]", phone);
                while(!check_phone(phone))
                {
                    printf("Enter the NEW account mobile number again correctly\n: ");
                    scanf(" %49[^\n]", phone);

                }

                strcpy(accounts[i].accountMobile,phone);

            }

            printf("Do you want to change the account e-mail adress :?",accounts[i].accountAddress);
            printf("(1)YES\t(0)NO");
            scanf(" %19[^\n]",inp);
            while( !(check_test(inp)))
            {
                printf("_____________________________________________________________________________\n");
                printf(RED"Enter input again correctly pls : \n\a"RESET);
                scanf(" %19[^\n]",inp);
            }
            response=atoi(inp);
            while (response>1)
            {
                printf(RED"Enter input again correctly pls either 0 or 1 : \a\n"RESET);
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls from 0 to 1 : \a\n"RESET);
                    scanf(" %19[^\n]",inp);
                }
                response=atoi(inp);
            }


            printf("\n");
            if(response==1)
            {
                char test1 [50];
                printf("Enter new email Address: ");
                scanf(" %49[^\n]", test1);
                while (!check_mail(test1))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter new mail again correctly pls: \a"RESET);
                    scanf(" %49[^\n]", test1);

                }
                strcpy(accounts[i].accountAddress, test1);
            }

        }
    }

    if(flag==0)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"The account can't be found :'( \n Please , check the account number and try again .\a"RESET);
        modify(accounts,accountCount);
    }
    else
        saveAccounts(accounts,&accountCount);
}

void advanced_search(account *ans, int size)
{
    int toprint[50];
    int v = 0;
    char given[50];
    printf("SEARCH :");
    scanf(" %49[^\n]",given);

    while(!(advsearchcheck(given)))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Enter again :"RESET);
        scanf(" %49[^\n]",given);
    }

    printf("\n");
    int k = strlen(given);

    for (int j = 0; j < size; j++)
    {
        int counter = 0;
        int f = 0;
        int e=strlen(ans[j].accountName);
        for (int i = 0; i < e; i++)
        {
            if (ans[j].accountName[i] == given[f])
            {
                counter++;
                f++;
            }
            else
            {
                counter = 0;
                f = 0;
            }

            if (counter == k)
            {
                toprint[v++] = j;
                break;
            }
        }
    }

    if (v == 0)
        printf(RED"NOT found\n\a"RESET);
    else
    {
        for (int i = 0; i < v; i++)
            printCustomer(&ans[toprint[i]]);
    }
}

void printCustomer(const account *customer)
{
    const char *monthNames[] =
    {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    printf("Customer ID: %lld\n", customer->accountNumber);
    printf("Name: %s\n", customer->accountName);
    printf("Address: %s\n", customer->accountAddress);
    printf("Phone Number: %s\n", customer->accountMobile);
    printf("Date Opened: %d-%d\n", monthNames[customer->date_open.month -1], customer->date_open.year);
    printf("Balance: %f $\n", customer->accountBalance);
    printf("\n\n");
}

void convertToLowerCase(char *str)
{
    while (*str)
    {
        *str = tolower(*str);
        str++;
    }
}

int checkNumber_float(char amount_to_deposit[],int size)
{
    int dotCount = 0;

    for (int i = 0; i < strlen(amount_to_deposit); i++)
    {
        if (!isdigit(amount_to_deposit[i]) && amount_to_deposit[i] != '.')
        {
            return 0;
        }
        else if (amount_to_deposit[i] == '.')
        {
            dotCount++;
            if (dotCount > 1)
            {
                return 0;
            }
        }
    }
    int l=0;
    for (int i = 0; i < strlen(amount_to_deposit); i++)
    {
        if(amount_to_deposit[i]>'0')
            l++;
    }

    if(l<=0)
        return 0;

    return 1;
}

int checkInt_Number(char amount_to_deposit[],int size )
{
    for(int i=0; i<strlen(amount_to_deposit); i++)
    {
        if(!isdigit(amount_to_deposit[i]))
            return 0;
    }
    return 1;
}

void deposit(account accounts[],int accountCount)
{
    int i;
    int found = 0;
    int size=accountCount;
    int flag =0;
    char amount_to_deposit[size];
    char test1[50];
    test1[49]=NULL;
    float max_deposit = 10000.0;
    long long accountnumber;
    char extra;
    float afterT;
    printf("Please enter the account number :");

    scanf(" %49[^\n]",test1);
    while(!check_accnum(test1))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Please enter the account number again :\a"RESET);
        scanf(" %49[^\n]",test1);
    }
    accountnumber=check_accnum(test1);

    for (long long i = 0; i < accountCount; i++)
    {
        if (accountnumber == accounts[i].accountNumber)
        {
            flag = 1;
            break;
        }
    }

    if (!flag)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"The account is not found.\\n"RESET);
        printf("_____________________________________________________________________________\n");
        return;
    }
    printf("Enter the amount to be deposited, please: ");
    scanf(" %49[^\n]",amount_to_deposit);

    while (!(checkNumber_float(amount_to_deposit,size)))
    {
        printf("Enter the amount to be deposited correctly, please: ");
        scanf(" %49[^\n]",amount_to_deposit);
    }

    afterT=atof(amount_to_deposit);

    for (i = 0; i < accountnumber; i++)
    {
        if (accounts[i].accountNumber == accountnumber)
        {
            if (max_deposit < afterT)
            {
                printf("Error, you have exceeded the maximum deposit amount. Try again.\n");
                return;
            }
            else
            {
                accounts[i].accountBalance += afterT;
                printf("Successful deposit. Your account balance = %f\n", accounts[i].accountBalance);
            }
            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("Account not found. Try again.\n");
        //deposit(accounts,accountCount);
        return;
    }
    int ans =saveAccounts(accounts,&accountCount);
    if(ans==1)
        addinfo(accountnumber,'d',afterT);
}

void WithDraw(account *accounts, int accountCount)
{
    int i = 0;
    int found = 0,flag=0;
    char amount_to_withdraw[20];
    float max_withdraw = 10000.0;
    char test1[50];
    test1[49]=NULL;
    long long accountnumber;
    float afterT;
    int size=50;
    printf("Please enter the account number :");

    scanf(" %49[^\n]",test1);
    while(!check_accnum(test1))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Please enter the account number again :"RESET);
        scanf(" %49[^\n]",test1);
    }
    accountnumber=check_accnum(test1);
    for (int i = 0; i < accountCount; i++)
    {
        if (accountnumber == accounts[i].accountNumber)
        {
            flag = 1;
            break;
        }
    }

    if (!flag)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"The account is not found."RESET);
        printf("_____________________________________________________________________________\n");
        return;
    }

    printf("Enter the amount to be withdrawn, please: ");

    scanf(" %49[^\n]",amount_to_withdraw);

    while (!(checkNumber_float(amount_to_withdraw,size)))
    {
        printf("Enter the amount to be withdrawn correctly numbers only, please: ");
        scanf(" %49[^\n]",amount_to_withdraw);
    }

    afterT=atof(amount_to_withdraw);

    while (i < accountCount)
    {
        if (accounts[i].accountNumber == accountnumber)
        {
            if (accounts[i].accountBalance < afterT)
            {
                printf(RED"Error, Your account has insufficient balance.\n"RESET);
                return;
            }
            else if (max_withdraw < afterT)
            {
                printf(RED"Error, You have exceeded the maximum withdrawal amount. Try again.\n"RESET);
                return;
            }
            else if (accounts[i].accountBalance >= afterT && max_withdraw >= afterT)
            {
                accounts[i].accountBalance -= afterT;
                printf(GREEN"Successful Withdraw,"RESET);
                printf(" Your account balance=%f\n", accounts[i].accountBalance);
            }
            found = 1;
            break;
        }
        i++;
    }

    if (found == 0)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Error in your input ,Try again\n\a"RESET);
        //WithDraw(accounts,accountCount);
        return;
    }
    int ans =saveAccounts(accounts,&accountCount);
    if(ans==1)
        addinfo(accountnumber,'w',afterT);
    else
        return;
}

void transfer(account accounts[],int accountCount)
{
    long long check2;
    int i,s,check1,r;
    char S[50];
    char R[50];
    long long accountNS,accountNR;
    char money[50];
    float moneyAf;
    int flag1=0;
    int flag2=0;

    printf("Please enter the account number for sender and the receiver:\n");
    printf("sender:");
    scanf(" %49[^\n]",S);

    while(!check_accnum(S))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"ERROR ! Please enter the account number again :\a"RESET);
        scanf(" %49[^\n]",S);
    }
    accountNS=check_accnum(S);

    printf("receiver:");

    scanf(" %49[^\n]",R);

    while(!check_accnum(R))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"ERROR ! Please enter the account number again :\a"RESET);
        scanf(" %49[^\n]",S);
    }
    accountNR=check_accnum(R);
    if(accountNS==accountNR)
    {
        printf("ERROR:Account number of receiver must be differnet enter it again \n");
        printf("receiver:");
        scanf(" %49[^\n]",R);
        while(!check_accnum(R))
        {
        printf("_____________________________________________________________________________\n");
        printf(RED"ERROR ! Please enter the account number again :\a"RESET);
        scanf(" %49[^\n]",S);
        }
    }

    for(i=0; i<accountCount; i++)
    {
        if (accountNS==accounts[i].accountNumber)
        {
            s=i;
            flag1=1;
        }
        if(accountNR==accounts[i].accountNumber)
        {
            r=i;
            flag2=1;
        }
    }
    if(flag1==0)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"ERROR:account number of the sender is not found\n\a"RESET);
        printf("_____________________________________________________________________________\n");
        return ;
    }
    if(flag2==0)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"ERROR:account number of receiver is not found\n"RESET);
        printf("_____________________________________________________________________________\n");
        return;
    }

    check2=accounts[s].accountNumber;

    printf("please enter the amount of money:");
    scanf(" %49[^\n]",money);

    while (!(checkNumber_float(money,50)))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Enter the amount to be transfered correctly, please: \a"RESET);
        scanf(" %49[^\n]",money);
    }

    moneyAf=atof(money);

    if(moneyAf>accounts[s].accountBalance)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"\n NOT ENOGHT MONEY"RESET);
        return;
    }
    else
    {
        accounts[s].accountBalance-=moneyAf;
        accounts[r].accountBalance+=moneyAf;
    }
    if(check2>accounts[s].accountNumber)
        printf(GREEN"Successful transfer"RESET);
    int ans =saveAccounts( accounts,  &accountCount);
    if(ans==1)
    {
        addinfo(accountNS, 't',-moneyAf);
        addinfo(accountNR, 't',moneyAf);

    }
}

void report(account *ans, int accountCount)
{
    FILE *file;
    char g[50];

    long long numberCheck;

    printf("Please enter the account number :");
    scanf(" %49[^\n]",g);

    while(!check_accnum(g))
    {
        printf("Please enter the account number again :");
        scanf(" %49[^\n]",g);
    }

    numberCheck=check_accnum(g);

    strcat(g, ".txt");
    int flag=0;
    for(int i=0; i<accountCount; i++)
    {
        if(ans[i].accountNumber==numberCheck)
        {
            flag =1;
        }
    }

    if(flag==0)
    {
        printf("account not found\n");
        return;
    }

    file = fopen(g, "r");

    if (file == NULL)
    {
        printf("no previous transactions\n");
        return ; // Return an error code
    }

    int counter = 1;
    char lines;
    while (!feof(file))
    {
        lines = fgetc(file);
        if (lines == ' ')
            counter++;
    }
    counter = counter / 2;

    char x[counter + 1];
    float y[counter];
    int i = 0;
    x[counter] = '\0';
    rewind(file);

    while (!feof(file) && i < counter)
    {
        if (fscanf(file, " %c %f", &x[i], &y[i]) == 2)
        {
            i++;
        }
    }

    if(counter<=5)
        for (int j = counter-1; j >= 0; j--)
        {
            if(x[j]=='w')
                printf("WITHDRAW");
            else if(x[j]=='d')
                printf("DEPOSIT");
            else
                printf("transfer");
            printf("   %f\n", y[j]);
        }
    else
        for (int j = counter-1; j >= counter-5; j--)
        {
            if(x[j]=='w')
                printf("WITHDRAW");
            else if(x[j]=='d')
                printf("DEPOSIT");
            else
                printf("transfer");
            printf("   %f\n", y[j]);
        }

    fclose(file);

}

void swap(account *ac1,account *ac2)
{
    account temp=*ac1;
    *ac1=*ac2;
    *ac2=temp;
}

void SortByName( account *accounts, int accountCount)
{
    for (int i = 0; i < accountCount; i++)
    {
        for (int j = 0; j < accountCount - i - 1; j++)
        {
            if (accounts[j].accountName[0] != '\0' && accounts[j + 1].accountName[0] != '\0')
            {
                if (strcmp(accounts[j].accountName, accounts[j + 1].accountName) > 0)
                {
                    swap(&accounts[j], &accounts[j + 1]);
                }
            }
        }
    }
}

void SortByDate(account *accounts, int accountCount)
{
    for (int i = 0; i < accountCount; i++)
    {
        for (int j = 0; j < accountCount - i - 1; j++)
        {
            if (accounts[j].date_open.year > accounts[j + 1].date_open.year)
            {
                swap(&accounts[j], &accounts[j + 1]);
            }
            else if (accounts[j].date_open.year == accounts[j + 1].date_open.year &&
                     accounts[j].date_open.month > accounts[j + 1].date_open.month)
            {
                swap(&accounts[j], &accounts[j + 1]);
            }
        }
    }
}

account* SortByBalance(account accounts[], int accountCount)
{
    account* Accounts = malloc(accountCount * sizeof(account));
    if (Accounts == NULL)
    {
        exit(0);
    }
    memcpy(Accounts, accounts, accountCount * sizeof(account));

    for (int i = 0; i < accountCount; i++)
    {
        for (int j = 0; j < accountCount - i - 1; j++)
        {
            if (Accounts[j].accountBalance > Accounts[j + 1].accountBalance)
            {
                swap(&Accounts[j], &Accounts[j + 1]);
            }
        }
    }
    return Accounts;
}

void Print(account accounts[], int accountCount)
{
    int select;
    printf("Please select the number:\n");
    printf("(1) Sort by balance.\n");
    printf("(2) Sort by date.\n");
    printf("(3) Sort by name.\n");

    char inp [20];
    scanf(" %19[^\n]",inp);
    while( !(check_test(inp)))
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Enter input again correctly pls : \a\n"RESET);
        scanf(" %19[^\n]",inp);
    }
    select=atoi(inp);
    while (select>3||select<=0)
    {
        printf("_____________________________________________________________________________\n");
        printf(RED"Enter input again correctly pls from 1 to 3 : \n\a"RESET);
        scanf(" %19[^\n]",inp);
        while( !(check_test(inp)))
        {
            printf("_____________________________________________________________________________\n");
            printf(RED"Enter input again correctly pls from 1 to 3 : \a\n"RESET);
            scanf(" %19[^\n]",inp);
        }
        select=atoi(inp);
    }

    if (select == 1)
    {
        account* sortedAccounts = SortByBalance(accounts, accountCount);

        for (int i = 0; i < accountCount; i++)
        {
            printf("Account Number: %lld\n", sortedAccounts[i].accountNumber);
            printf("Name: %s\n", sortedAccounts[i].accountName);
            printf("Email: %s\n", sortedAccounts[i].accountAddress);
            printf("Balance: %f $\n", sortedAccounts[i].accountBalance);
            printf("Mobile: %s\n", sortedAccounts[i].accountMobile);
            printf("Date opened : %s %d\n", monthNames[sortedAccounts[i].date_open.month - 1], sortedAccounts[i].date_open.year);
            printf("\n");
        }

        free(sortedAccounts);
    }
    else if (select == 2)
    {
        SortByDate(accounts, accountCount);
        for(int i=0; i<accountCount; i++)
        {
            printf("Account Number : %lld\n", accounts[i].accountNumber);
            printf("Name : %s\n", accounts[i].accountName);
            printf("Email : %s\n", accounts[i].accountAddress);
            printf("Balance : %f $\n", accounts[i].accountBalance);
            printf("Mobile : %s\n", accounts[i].accountMobile);
            printf("Date opened : %s %d\n", monthNames[accounts[i].date_open.month - 1], accounts[i].date_open.year);
            printf("\n");
        }
    }
    else if (select == 3)
    {
        SortByName(accounts, accountCount);
        for(int i=0; i<accountCount; i++)
        {
            printf("Account Number : %lld\n", accounts[i].accountNumber);
            printf("Name : %s\n", accounts[i].accountName);
            printf("Email : %s\n", accounts[i].accountAddress);
            printf("Balance : %f $\n", accounts[i].accountBalance);
            printf("Mobile : %s\n", accounts[i].accountMobile);
            printf("Date opened : %s %d\n", monthNames[accounts[i].date_open.month - 1], accounts[i].date_open.year);
            printf("\n");
        }
    }

    int loadFile(account accounts[]);
}

int main()
{
    int f =first_menu ();
    if(f==0)
    {
        printf("\nBye Bye<3\n");
        return 0;
    }

    account accounts[1024];
    int accountCount=loadFile(accounts);

    int order;
    int acc_numberSearch;
    int size;

    while(1)
    {
        printf("\t\t\tWELCOME TO ");
        printf(RED"ZAY BANK<3\n"RESET);
        printf("=============================================================================\n");
        printf(CYAN"Select one of the following options (Enter the number of the desired order): \n"RESET);
        printf("_____________________________________________________________________________\n");
        printf("\t(1)ADD\n\t(2)DELETE\n\t(3)MODIFY\n\t(4)SEARCH\n\t(5)ADVANCED SEARCH\n\t(6)WITHDRAW\n\t(7)DEPOSIT\n\t(8)TRANSFER\n\t(9)REPORT\n\t(10)PRINT\n\t(0)QUIT\n");
        printf("_____________________________________________________________________________\n");
        printf("\tOrder : ");

        char otdertTest[20];
        scanf(" %19[^\n]",otdertTest);

        while( !(check_test(otdertTest)))
        {
            printf("\n");
            printf("_____________________________________________________________________________\n");
            printf(RED"Enter order again correctly pls : \a\n"RESET);
            scanf(" %19[^\n]",otdertTest);
        }
        order=atoi(otdertTest);
        while (order>10)
        {
            printf("\n");
            printf("_____________________________________________________________________________\n");
            printf(RED"Enter order again correctly pls either 0 or 10 : \a\n"RESET);
            scanf(" %19[^\n]",otdertTest);
            while( !(check_test(otdertTest)))
            {
                printf("\n");
                printf("_____________________________________________________________________________\n");
                printf(RED"Enter order again correctly pls either 0 or 10 : \a\n"RESET);
                scanf(" %19[^\n]",otdertTest);
            }
            order=atoi(otdertTest);
        }
        printf("\n");
        printf("=============================================================================\n");

        switch(order)
        {
        case 1:
        {
            addAccount(accounts,&accountCount);

            while(1)
            {
                printf("_____________________________________________________________________________\n");
                printf("If you want to add again press 1.\n");
                printf("If you want tO return to the Menu press 0.\n");
                int g;
                char inp[20];
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls : \a\n"RESET);
                    scanf(" %19[^\n]",inp);
                }
                g=atoi(inp);
                while(g>1)
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter order again correctly pls either 0 or 1 : \a\n"RESET);
                    scanf(" %19[^\n]",inp);
                    while( !(check_test(inp)))
                    {
                        printf("_____________________________________________________________________________\n");
                        printf(RED"Enter order again correctly pls either 0 or 1 : \a\n"RESET);
                        scanf(" %19[^\n]",inp);
                    }
                    g=atoi(inp);
                }

                if(g==1)
                    addAccount(accounts,&accountCount);
                else
                    break ;
            }
            break;
        }
        case 2:
        {
            deleteAccount(accounts,&accountCount);
            while(1)
            {
                printf("_____________________________________________________________________________\n");
                printf("If you want to Delete again press 1.\n");
                printf("If you want to return to the Menu press 0.\n");
                int g;
                char inp[20];
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls : \a\n"RESET);
                    scanf(" %19[^\n]",inp);
                }
                g=atoi(inp);
                while (g>1)
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter order again correctly pls from 0 to 1 : \n\a"RESET);
                    scanf(" %19[^\n]",inp);
                    while( !(check_test(inp)))
                    {
                        printf("_____________________________________________________________________________\n");
                        printf(RED"Enter order again correctly pls from 0 to 1 : \n"RESET);
                        scanf(" %19[^\n]",inp);
                    }
                    g=atoi(inp);
                }

                if(g==1)
                    deleteAccount(accounts,&accountCount);
                else
                    break ;
            }
            break;
        }
        case 3:
        {
            modify(accounts,accountCount);
            while(1)
            {
                printf("_____________________________________________________________________________\n");
                printf("If you want to Modify again press 1.\n");
                printf("If you want tO return to the Menu press 0.\n");
                int g;
                char inp[20];
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls : \n"RESET);
                    scanf(" %19[^\n]",inp);
                }
                g=atoi(inp);
                while (g>1)
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter order again correctly pls either 0 or 1 : \n"RESET);
                    scanf(" %19[^\n]",inp);
                    while( !(check_test(inp)))
                    {
                        printf("_____________________________________________________________________________\n");
                        printf(RED"Enter order again correctly pls either 0 or 1 : \n"RESET);
                        scanf(" %19[^\n]",inp);
                    }
                    g=atoi(inp);
                }

                if(g==1)
                    modify(accounts,accountCount);
                else
                    break ;
            }
            break;
        }
        case 4:
        {
            query(accounts,accountCount);
            while(1)
            {
                printf("_____________________________________________________________________________\n");
                printf("If you want to search again press 1.\n");
                printf("If you want to return to the Menu press 0.\n");
                int g;
                char inp[20];
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls : \a\n"RESET);
                    scanf(" %19[^\n]",inp);
                }
                g=atoi(inp);
                while (g>1)
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter order again correctly pls either 0 or 1 : \a\n"RESET);
                    scanf("%19s",inp);
                    while( !(check_test(inp)))
                    {
                        printf("_____________________________________________________________________________\n");
                        printf(RED"Enter order again correctly pls either 0 or 1 : \a\n"RESET);
                        scanf(" %19[^\n]",inp);
                    }
                    g=atoi(inp);
                }

                if(g==1)
                    query(accounts,accountCount);
                else
                    break ;
            }
            break ;
        }
        case 5:
        {
            advanced_search(accounts,accountCount);

            while(1)
            {
                printf("_____________________________________________________________________________\n");
                printf("If you want to make another advanced search again press 1.\n");
                printf("If you want TO return to the Menu press 0.\n");
                int g;
                char inp[20];
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls : \a\n"RESET);
                    scanf(" %19[^\n]",inp);
                }
                g=atoi(inp);
                while (g>1)
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter order again correctly pls either 0 or 1 : \a\n"RESET);
                    scanf("%19s",inp);
                    while( !(check_test(inp)))
                    {
                        printf("_____________________________________________________________________________\n");
                        printf(RED"Enter order again correctly pls either 0 or 1 : \n\a"RESET);
                        scanf(" %19[^\n]",inp);
                    }
                    g=atoi(inp);
                }

                if(g==1)
                    advanced_search(accounts,accountCount);
                else
                    break ;
            }
            break;
        }
        case 6:
        {
            WithDraw(accounts,accountCount);
            while(1)
            {
                printf("_____________________________________________________________________________\n");
                printf("If you want to Withdraw again press 1\n");
                printf("If you want TO return to the Menu press 0\n");
                int g;
                char inp[20];
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls : \n"RESET);
                    scanf(" %19[^\n]",inp);
                }
                g=atoi(inp);
                while (g>1)
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls either 0 or 1 : \n"RESET);
                    scanf(" %19[^\n]",inp);
                    while( !(check_test(inp)))
                    {
                        printf("_____________________________________________________________________________\n");
                        printf(RED"Enter input again correctly pls either 0 or 1 : \n"RESET);
                        scanf(" %19[^\n]",inp);
                    }
                    g=atoi(inp);
                }

                if(g==1)
                    WithDraw(accounts,accountCount);
                else
                    break ;
            }
            break;
        }
        case 7:
        {
            deposit(accounts,accountCount);

            while(1)
            {
                printf("_____________________________________________________________________________\n");
                printf("If you want to Deposit again press 1\n");
                printf("If you want tO return to the Menu press 0\n");
                int g;
                char inp[20];
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls : \n"RESET);
                    scanf(" %19[^\n]",inp);
                }
                g=atoi(inp);
                while(g>1)
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls either 0 or 1 : \n"RESET);
                    scanf(" %19[^\n]",inp);
                    while( !(check_test(inp)))
                    {
                        printf("_____________________________________________________________________________\n");
                        printf(RED"Enter input again correctly pls either 0 or 1 : \n"RESET);
                        scanf(" %19[^\n]",inp);
                    }
                    g=atoi(inp);
                }

                if(g==1)
                    deposit(accounts,accountCount);
                else
                    break ;
            }
            break;
        }
        case 8:
        {
            transfer(accounts,accountCount);
            while(1)
            {
                printf("_____________________________________________________________________________\n");
                printf("If you want to transfer again press 1\n");
                printf("If you want to return to the Menu press 0\n");
                int g;
                char inp[20];
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls : \n\a"RESET);
                    scanf(" %19[^\n]",inp);
                }
                g=atoi(inp);
                while (g>1)
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls either 0 or 1 : \n\a"RESET);
                    scanf(" %19[^\n]",inp);
                    while( !(check_test(inp)))
                    {
                        printf("_____________________________________________________________________________\n");
                        printf(RED"Enter input again correctly pls from 0 to 1 : \n"RESET);
                        scanf(" %19[^\n]",inp);
                    }
                    g=atoi(inp);
                }

                if(g==1)
                    transfer(accounts,accountCount);
                else
                    break ;
            }
            break;
        }
        case 9:
        {
            report(accounts,accountCount);
            while(1)
            {
                printf("_____________________________________________________________________________\n");
                printf("If you want another Report press 1\n");
                printf("If you want to return to the Menu press 0\n ");
                int g;
                char inp[20];
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls : \n\a"RESET);
                    scanf(" %19[^\n]",inp);
                }
                g=atoi(inp);
                while (g>1)
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls either 0 or 1 : \a\n"RESET);
                    scanf(" %19[^\n]",inp);
                    while( !(check_test(inp)))
                    {
                        printf("_____________________________________________________________________________\n");
                        printf(RED"Enter input again correctly pls either 0 or 1 : \a\n"RESET);
                        scanf(" %19[^\n]",inp);
                    }
                    g=atoi(inp);
                }
                if(g==1)
                    report(accounts,accountCount);
                else
                    break ;
            }
            break;
        }
        case 10:
        {
            Print(accounts,accountCount);
            while(1)
            {
                printf("_____________________________________________________________________________\n");
                printf("If you want to print again PRESS 1\n");
                printf("If you want tO return to the Menu press 0\n");
                int g;
                char inp[20];
                scanf(" %19[^\n]",inp);
                while( !(check_test(inp)))
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"enter input again correctly pls : \a\n"RESET);
                    scanf(" %19[^\n]",inp);
                }
                g=atoi(inp);
                while (g>1)
                {
                    printf("_____________________________________________________________________________\n");
                    printf(RED"Enter input again correctly pls either 0 or 1 : \n"RESET);
                    scanf(" %19[^\n]",inp);
                    while( !(check_test(inp)))
                    {
                        printf("_____________________________________________________________________________\n");
                        printf(RED"Enter input again correctly pls either 0 or 1 : \a\n"RESET);
                        scanf(" %19[^\n]",inp);
                    }
                    g=atoi(inp);
                }
                if(g==1)
                    Print(accounts,accountCount);
                else
                    break ;
            }

            break;
        }
        case 0:
        {
            printf(CYAN"\nBYE BYE <3\n"RESET);
            return 0;
            break;
        }
        }
    }
}

