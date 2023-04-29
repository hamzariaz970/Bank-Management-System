//menu.bank
#include<stdio.h>
#include<stdlib.h>
//#include<windows.h>
#include<string.h>
//#include<conio.h>
#include<math.h>
#include<ctype.h>
#include <unistd.h> // for mac OS


#include "functions.h" // inlcuding our custom functions header file

void menu_employee(); //It provide access to the employee menu after inputting correct Employee Id and Password
void menu_customer(struct customer *cust); //It provide access to the customer menu after inputting correct customer Id and Password
void admin(); //It provide access to the admin menu after inputting correct admin Id and Password
int verify(); // Verifies details
void menuexit(); // exiting menu



// type variable means the person logging in is user or administrator
int type;

char admin_id[20], admin_password[20];

int main(void)
{
    struct customer c;
    


    //draw logo
    int input;
    printf("\n\n\n");
    printf("\t\t     ~~~~~~~~~~~~~~~~~~\n");
    printf("\t\t\t\t\t\tWELCOME\n");
    printf("\t\t\t\t--------------    TO\n");
    printf("\t\t\t\t|============| MHA BANK\n");
    printf("\t\t\t\t|---  --     |\n");
    printf("\t\t\t\t|            |\n");
    printf("\t\t\t\t--------------\n");
    printf("\t\t\t\t             ---------------\n");
    printf("\t\t\t\t             |          *|\n");
    printf("\t\t\t\t             |             |\n");
    printf("\t\t\t\t             |=============|\n");
    printf("\t\t\t\t             ---------------\n");
    printf("\t\t     ~~~~~~~~~~~~~~~~~\n\n");
    printf("\t\t\t\t\t...PLEASE WAIT...\n\n\n");
    Sleep(2000);
    //usleep(2000); // or nanosleep(2000000000)
    system("cls");
    printf("\n\n\n\n");
    printf("\t\t\t\t");
    






    // most upper-level menu. Asks for either becoming an admin or a customer.
    printf("WELCOME TO MHA BANKING SYSTEM\n\n");
    printf("\t\t\t\t1.CUSTOMER\t\t\t 2.ADMIN\n");
    printf("\t\t\t\tEnter your choice: ");
    scanf("%d", &type);
    if (type != 1 && type != 2)
    {
        system("cls");
        main();
    }
    system("cls");
    admin();
    
    return 0;
}

void admin()
{
    printf("\t\t\t\tWELCOME TO MHA BANKING SYSTEM\n\n");


    if (verify()==1) //verify returns 1 on successful login by user or employee
    {
        if (type==1) //type == 1 means user/customer login
        {
            menu_customer(&c);
        }
        else
        {
            menu_employee(); // type == 2 means employee or administration login
        }
    }
    else if (verify() == 0)
    {
        system("cls");
        printf("\t\t\t\tINCORRECT TYPE or USERNAME OR PASSWORD\n");
        admin(); //use of recursion to call admin function and take input again
    }
    else{

    }
}



int verify()
{ 
    
    // takes the username and password of customer and verifies it
    if(type==1)
    {
        //int i = 0;
        fflush(stdin);
        char password[80];
        unsigned long long int CNIC;
        printf("\n\t\t\t\tEnter The Username/CNIC: \n\t\t\t\tEnter -1 to return \n\t\t\t\t\t");
        //scanf(" %[^\n]", id); // To take input till new line character
        scanf("%llu", &CNIC);
        if (CNIC == -1)
        {
            main();
        }
        fflush(stdin);
        printf("\n\t\t\t\tEnter The Password : \n\t\t\t\tEnter -1 to return \n\t\t\t\t\t");
        //scanf(" %[^\n]", password); // To take input till newline character
        scanf("%[^\n]", password);
        if (strcmp(password, "-1") == 0)
        {
            main();
        }
        // read previously existing binary file here in read mode .. if it exists
        FILE *fileOpen1 = NULL;
        fileOpen1 = fopen("data.dat","rb");
        if (fileOpen1 != NULL)
        {   
            // read all existing structs from .DAT file and check if any struct's CNIC 
            // and password matches with the CNIC and password entered by the user.
            while(!feof(fileOpen1))
            {
                struct customer prev_c; 
                fread(&prev_c, sizeof(struct customer), 1, fileOpen1);  // Reading one struct at a time
                if (prev_c.CNIC == CNIC && strcmp(prev_c.password, password) == 0)
                {
                    printf("\n\t\t\t\tFound matching customer entry with CNIC: %llu!\n", prev_c.CNIC);
                    // assign struct c to be the same as prev_c struct
                    c = prev_c;
                    printf("\n\t\t\t\tLOGIN SUCESSFUL, WELCOME: %s\n\t\t\t\t\n", c.name);

                    printf("\n\t\t\t\tPress any key to continue .... \n");
                    fflush(stdin);
                    getchar();
                    system("cls");
                    return 1;
                }

            }
            return 0;

        }
       
        else
        {
            printf("\n\t\t\t\t No previously existing customer data file found."); // in case of error
            sleep(3000);
            system("cls");
            main();
            
        }

    }
    else if (type == 2)
    {
        fflush(stdin);
        printf("\t\t\t\tEnter admin username/id: \n\t\t\t\tEnter -1 to return \n\t\t\t\t\t");
        scanf("%[^\n]", admin_id);
        fflush(stdin);
        printf("\t\t\t\tEnter admin password: \n\t\t\t\tEnter -1 to return \n\t\t\t\t\t");
        scanf("%[^\n]", admin_password);

        if (strcmp(admin_id, "admin") == 0 && strcmp(admin_password, "123") == 0)
        {
            printf("\t\t\t\tADMIN LOGIN SUCCESSFUL!\n");
            printf("\t\t\t\tPress any key to continue .... \n");
            //getch();
            getchar();
            return 1;

        }
        else
        {
            return 0;
        }

    }
    return 0;
}
void menu_customer(struct customer *cust)
{
    //displays menu for user/customer to use the functions and perform desired tasks
    system("cls");

    printf("\n\t\t\t\tUSER: %s\n\t\t\t\t\n\n\t\t\t\t\tWELCOME!\n\n\t\t\t\t", cust->name);

    printf("\t\t\t\t USER MENU\n");

    printf("\t\t\t\t1. Check Balance\n");

    printf("\t\t\t\t2. Cash Deposit\n");

    printf("\t\t\t\t3. Cash Withdrawal\n");

    printf("\t\t\t\t4. Issue Debit Card\n");



    if (type == 1) {

        printf("\t\t\t\t5. Exit\n");
    } else {

        printf("\t\t\t\t5. Exit\n");
    }

    printf("\t\t\t\t6. Return to main menu\n");

    printf("\n\t\t\t\tPlease Enter Your Choice (1-8) : ");
    int a;
    scanf("%d", &a);
    switch (a) {
        case 1:
            system("cls");
            check_balance(cust);
            menu_customer(cust);
        case 2:
            system("cls");
            deposit(cust);
            menu_customer(cust);
        case 3:
            system("cls");
            withdraw(cust);
            menu_customer(cust);
        case 4:
            system("cls");
            if (type == 1)
                //loan();
            break;
        case 5:
            system("cls");
            //printf("\n\t\t\t\tBefore exiting, here are the (updated) customer details I will be saving to file:\n");
            //printCustomer(*cust);

            FILE *fp, *fp1;
            struct customer cust1;
            int found = 0, count = 0;
            fp = fopen("data.dat", "rb");
            fp1 = fopen("temp.dat", "wb");
            while(1)
            {
                fread(&cust1, sizeof(cust1), 1, fp);
                if (feof(fp))
                {
                    break;
                }
                if (cust1.CNIC == cust->CNIC)
                {
                    found = 1;
                    fwrite(cust, sizeof(struct customer), 1, fp1);
                }
                else
                {   
                    fwrite(&cust1, sizeof(cust1), 1, fp1);
                }
            }
            fclose(fp);
            fclose(fp1);

            if (found==1)
            {
                fp=fopen("data.dat", "wb"); //  blanks out content of original file data.dat
                fp1=fopen("temp.dat", "rb");
                while(1)
                {
                    // force re-initialization of struct customer here
                    struct customer cust1;
                    // read records from temp file
                    fread(&cust1, sizeof(cust1), 1, fp1);

                    if(feof(fp1))
                    {
                        break;
                    }
                    // write records to original file data.dat
                    fwrite(&cust1, sizeof(cust1), 1, fp);
                }
                fclose(fp);
                fclose(fp1);
            }    
            exit(0);
            break;
        case 6:
            system("cls");
            //printf("\n\t\t\t\tBefore exiting, here are the (updated) customer details I will be saving to file:\n");
            //printCustomer(*cust);

            //FILE *fp, *fp1;
            //struct customer cust1;
            found = 0, count = 0;
            fp = fopen("data.dat", "rb");
            fp1 = fopen("temp.dat", "wb");
            while(1)
            {
                fread(&cust1, sizeof(cust1), 1, fp);
                if (feof(fp))
                {
                    break;
                }
                if (cust1.CNIC == cust->CNIC)
                {
                    found = 1;
                    fwrite(cust, sizeof(struct customer), 1, fp1);
                }
                else
                {   
                    fwrite(&cust1, sizeof(cust1), 1, fp1);
                }
            }
            fclose(fp);
            fclose(fp1);

            if (found==1)
            {
                fp=fopen("data.dat", "wb"); //  blanks out content of original file data.dat
                fp1=fopen("temp.dat", "rb");
                while(1)
                {
                    // force re-initialization of struct customer here
                    struct customer cust1;
                    // read records from temp file
                    fread(&cust1, sizeof(cust1), 1, fp1);

                    if(feof(fp1))
                    {
                        break;
                    }
                    // write records to original file data.dat
                    fwrite(&cust1, sizeof(cust1), 1, fp);
                }
                fclose(fp);
                fclose(fp1);
            } 
            main();
            break;

        default:
            menu_customer(cust);
    }
}
void menu_employee()
{
    //displays menu for employee to perform tasks and operations
    system("cls");

    printf("\t\t\t\tADMIN MENU\n");

    printf("\t\t\t\t1. Create New Account\n");

    printf("\t\t\t\t2. Delete Account\n");

    printf("\t\t\t\t3. View All Accounts\n");

    printf("\t\t\t\t4. View All Transactions\n");

    printf("\t\t\t\t5. Update Account Details\n");

    if (type == 2) {

        printf("\t\t\t\t6. Main Menu\n");
        printf("\t\t\t\t7. Terminate Program\n");
    } else {

        printf("\t\t\t\t6. Exit\n");
    }

    printf("\t\t\t\tPlease Enter Your Choice (1-7) : ");
    int a;
    scanf("%d", &a);
    switch (a) {
        case 1:
            system("cls");
            createAccount();
            fflush(stdin);
            printf("\n\t\t\t\tPress any key to continue...\n");
            getchar();
            menu_employee();
        case 2:
            system("cls");
            deleteAccount();
            fflush(stdin);
            printf("\n\t\t\t\tPress any key to continue...\n");
            getchar();
            menu_employee();
        case 3:
            system("cls");
            readAccounts();
            fflush(stdin);
            printf("\n\t\t\t\tPress any key to continue...\n");
            getchar();
            menu_employee();
        case 4:
            system("cls");
            fflush(stdin);
            printf("\n\t\t\t\tPress any key to continue...\n");
            getchar();
           // alltransactions();
            break;
        case 5:
            system("cls");
            updateAccount();
            fflush(stdin);
            printf("\n\t\t\t\tPress any key to continue...\n");
            getchar();
            menu_employee();
            //editaccountdetails();
            break;

        case 6:
            //if (type == 2)
                system("cls");
                main();
            //else
                //menuexit();
            break;
        case 7:
            exit(0);
        default:
            menu_employee();
    }

}
void menuexit()
{
    system("cls");

    printf("\t\t\t\t!!! THANK YOU !!!\n");

    printf("\t\t\t\tUSER :: %s", admin_id);
    //getch();
    getchar();

    exit(0);
}