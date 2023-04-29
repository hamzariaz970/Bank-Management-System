#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


struct customer 
{
    char name[80];
    int month, day, year;
    unsigned long long int phone ,CNIC;
    char address[80];
    double balance;
    char password[80];
}c;

void ReplaceChars(char array[1], char x) // Function to replace character
{
    int i = 0;
    while (array[i]!= '\0') // Read till end line character
    {
        if (array[i] == x) // if the character to be removed is reached, replace it with a character of choice
        {
            putchar(' ');
        }
        else 
        {
            putchar(array[i]);
        }
    }


}


// Function to remove a specific character from string
void RemoveChar(char str[], char x_remove)
{
    int i, j;
    int len = strlen(str); // getting length of string
    for (i = 0; i < len; i++)
    {
        if (str[i] == x_remove) // if the character in array equals the character we want to remove
        {
            for (j = i; j < len; j++)
            {
                str[j] = str[j + 1]; // Copying the next element to the current position, essentially removing the character from the array

            }
            len--;
            i--;
        }
    } 

}


// Function to print a struct customer
void printCustomer(struct customer c) 
{
    printf("\t\t\t\tCustomer Name: %s", c.name);
    printf("\t\t\t\tCustomer DOB Day: %d Month: %d Year: %d\n", c.day, c.month, c.year);
    printf("\t\t\t\tCustomer Phone: 0%llu\n", c.phone);
    printf("\t\t\t\tCustomer CNIC: %llu\n", c.CNIC);
    printf("\t\t\t\tCustomer Balance: %.2lf\n", c.balance);
}


// Function to read accounts for Account creation
void readAccounts()
{
    // read previously existing binary file here in read mode .. if it exists
    FILE *fileOpen = NULL;
    fileOpen = fopen("data.dat", "rb");
    if (fileOpen != NULL)
    {
        printf("\t\t\t\tReading contents of %s\n\n", "data.dat");
        struct customer c; 
        // from binary file, read each customer struct, one at a time
        while((fread(&c, sizeof(struct customer), 1, fileOpen)) == 1)
        {
            // if EOF reached, break out of while loop
            if(feof(fileOpen))
            {
                break;
            }
            // display details of read struct
            printCustomer(c);
            printf("\n");
        }

        fclose(fileOpen); //Closing file in read mode
    }
    else
    {
        printf("\n\t\t\t\tNo previously existing customer data file found.\n\n");
    }
    //Sleep(30000);
    usleep(3000);
    printf("\n\t\t\t\t\tPress any key to continue\n");
    fflush(stdin);
    getchar();
}

// Function to create account and store details in file
void createAccount()
{   
    struct customer c;
    unsigned long long CNIC = 0;
    char name[80];
    int options;
    
    system("cls");
    start:
    fflush(stdin);

    while (1)
    {   
        system("cls");
        printf("\t\t\t\tEnter name: \n\t\t\t\t(Enter -1 to exit)"); // Asking for name
        
        fgets(name, (sizeof(name)/sizeof(char)), stdin);
        if (strcmp(name, '-1') == 0)
        {
            menu_employee();
        }
        int digits = 0;
        int i = 0;
        
        for (int i = 0; name[i] != '\0'; i++) // Checking if name entered is correct
        {    
            if (name[i] == ' ' || name[i] == '\n')
            {
                continue;
            }
            else if (isalpha(name[i]) != 0)
            {
                continue;
            }
            else
            {
                digits+= 1;
            }
       
        }
        if (digits != 0)
        {
            printf("\t\t\t\tError!Name can only include alphabets.\n"); // Printing error otherwise
            goto start;
            system("cls");
        }
        else
        {
            // assign name here
            strcpy(c.name, name);
            break;
        }    
    }


    
    
     while (1)
    {   

        int errors = 0;
        char buff1[14], buff2[14];
        int numRead = 0;

        printf("\t\t\t\tEnter 13-digit long CNIC number (without '-'): "); // Asking for ID
        numRead = scanf("%llu", &CNIC);
        
        while (numRead != 1)
        {
            printf("\t\t\t\tError. Invalid CNIC entered. Please try again.\n\t\t\t\t");
            scanf("%*[^\n]");
            printf("\t\t\t\tEnter 13-digit long CNIC number (without '-'): "); // Asking for ID again
            numRead = scanf("%llu", &CNIC);
        }
        //printf("%llu\n", CNIC);

        int count = 0; 
        unsigned long long num = CNIC;
        if(CNIC > 0)
        {   
            
            do // Counting number of digits of CNIC. Should be 13
            {
                num = num/10;
                count ++;
        
            } while (num != 0);

            if (count == 13)
            {
                // assign CNIC value here
                c.CNIC = CNIC;
                break;
            }
            else
            {   
                
                continue;
            }

        }
    }   


    while (1)
    {       
        char day[50];
        char month[50];
        char year[50];

        int dd,mm,yyyy;        


        int numRead = 0;

        stop1:
        printf("\t\t\t\tEnter your day of birth:\n\t\t\t\t"); // Asking for date of birth
        numRead = scanf("%d", &dd);
        while (numRead != 1)    
        {
            printf("\t\t\t\tError. Please try again.\n\t\t\t\t");
            scanf("%*[^\n]");
            printf("\t\t\t\tEnter your date of birth:\n\t\t\t\t");    
            numRead = scanf("%d", &dd);
        }    

        if (dd < 0 || dd > 31)
        {
            printf("\t\t\t\tError! Invalid date\n\t\t\t\t");
            goto stop1;
        }    
        else
        {
            c.day = dd;
        }
        
        numRead = 0;

        stop2:
        printf("\t\t\t\tEnter your month of birth:\n\t\t\t\t"); // Asking for month of birth
        numRead = scanf("%d", &mm);
        while (numRead != 1)    
        {
            printf("\t\t\t\tError. Please try again.\n\t\t\t\t");
            scanf("%*[^\n]");
            printf("\t\t\t\tEnter your month of birth:\n\t\t\t\t");    
            numRead = scanf("%d", &mm);
        }

        if (mm < 0 || mm > 12)
        {
            printf("\t\t\t\tError! Invalid month\n\t\t\t\t");
            goto stop2;
        }

        else
        {
            c.month = mm;
        }

        numRead = 0;

        stop3:
        printf("\t\t\t\tEnter your year of birth:\n\t\t\t\t"); // Asking for year of birth
        numRead = scanf("%d", &yyyy);
        while (numRead != 1)    
        {
            printf("\t\t\t\tError. Please try again.\n\t\t\t\t");
            scanf("%*[^\n]");
            printf("\t\t\t\tEnter your year of birth:\n\t\t\t\t");    
            numRead = scanf("%d", &yyyy);
        }

        if (yyyy < 1900 || yyyy > 3000)
        {
            printf("\t\t\t\tError! Invalid year.\n");
            goto stop3;
        }

        else
        {
            c.year = yyyy;
        }

        break;
    }     
    



    int numRead = 0;
    unsigned long long phone;


    while (1)
    {   
        stop4:
        
        printf("\t\t\t\tEnter your 11-digit long primary mobile number (starting with 0): ");
        numRead = scanf("%llu", &phone);
        while (numRead != 1)
        {
            printf("\t\t\t\tError! incorrect number added. Please try again.\n");
            scanf("%*[^\n]");
            printf("\t\t\t\tEnter your 11-digit long primary mobile number(starting with 0): ");
            numRead = scanf("%llu", &phone);
        }
        
        int num = phone;
        int count = 0;
        do 
        {
            num /= 10;
            count++;
        } while (num != 0);

        if (count != 10)
        {
            printf("\t\t\t\tIncorrect phone number. Try again.\n");
            goto stop4;
        }


        break;       

    }

    c.phone = phone;


    // set password of user here
    char password[80];
    while (1)
    {
        stop5:

        printf("\n\t\t\t\tSet your password: ");
        fflush(stdin);
        scanf("%[^\n]", password);
        // check if password is not empty
        if (password[0] != '\0')
        {
            break;
        }
        else
        {
            printf("\t\t\t\tPassword is empty string. Please try again.\n");
            goto stop5;
        }
    }

    strcpy(c.password, password);

    // set initial balance of user here
    double balance;

    while(1)
    {
        stop6:

        printf("\n\t\t\t\tEnter a valid starting balance for this account:");
        fflush(stdin);
        if (scanf("%lf", &balance) != 1) 
        {
            printf("\n\t\t\t\tEntered balance value is not valid. Please try again.\n");
            goto stop6;
        }
        else
        {
            break;
        }

    }

    // set balance here
    c.balance = balance;
    
    printf("\n");

    printf("\t\t\t\tContents of struct to be written to binary file:\n");

    printCustomer(c);

    // read previously existing binary file here in read mode .. if it exists
    FILE *fileOpen1 = NULL;
    fileOpen1 = fopen("data.dat","rb");

    if (fileOpen1 != NULL)
    {
        printf("\n\t\t\t\tChecking if acceptable customer data was provided in struct...\n\n");
        usleep(2000);
        //Sleep(2000);
        fflush(stdin);
        char temp1[50];
        sprintf(temp1, "%llu", c.CNIC); // Storing CNIC into a temporary string for comparison later on

        while(!feof(fileOpen1))
        {   
            // from binary file, read previous customer data into this customer and compare with customer data that was written now
            struct customer prev_c; 
            fread(&prev_c, sizeof(struct customer), 1, fileOpen1);  // Reading one struct at a time
            
            char temp2[50];
            sprintf(temp2, "%llu", prev_c.CNIC);


            //printf("New customer's entered CNIC: %s vs a previous customer's existing CNIC in database: %s\n\n", temp1, temp2);

            if (strcmp(temp1, temp2) == 0) // Going back if CNIC already registered/saved in file 
            {
                printf("\t\t\t\tError! CNIC is already registered with an account.\n");
                usleep(2000);
                //Sleep(2000);  
                fclose(fileOpen1); //Closing file in read mode
                goto start;
                //break;
            }
           //printf("\nChecking next previously written customer account in database...\n");
        }

        fclose(fileOpen1); //Closing file in read mode
    }
    else
    {
        printf("\n\t\t\t\tNo previously existing customer data file found..moving on to creating one.\n");
        //usleep(3000);
        Sleep(3000);
    }


    // begin writing struct to binary file here
    FILE *fileOpen2 = NULL;
    fileOpen2 = fopen("data.dat", "ab"); // Opening file that contains all user Accounts

    if (fileOpen2 == NULL)
    {
        printf("\t\t\t\tError opening file that contains Accounts records.");
        // goto main menu
        system("cls");
        createAccount();
    }

    // go to EOF before writing struct - if file is empty, end is same as start of file
    //fseek(fileOpen2, 0, SEEK_END);

    fwrite(&c, sizeof(struct customer), 1, fileOpen2);

    // closing file in append mode
    fclose(fileOpen2);


    printf("\n\t\t\t\tNo problems found with provided customer data....Account creation successful!\n\n");
    printf("\n\t\t\t\tPress any key to continue.....\n\t\t\t\t");
    //Sleep(5000);
    //usleep(5000);
    getchar();
    //menu_employee();


}





void deposit(struct customer* cust ) /*Function to deposit amount in account
                                      passing pointer to struct customer*/ 
{   fflush(stdin);
	float amount_to_deposit;
    int choice;
    int number_Read = 0;

	printf("\n\t\t\t\tEnter the amount you want to deposit: "); // taking input from user
	number_Read = scanf("%f", &amount_to_deposit);
    
    while (number_Read != 1 || amount_to_deposit < 0) // Handling errors
    {
        printf("\n\t\t\t\tError. Incorrect key pressed. Try again.\n");
        scanf("%*[^\n]"); // reading till \n character of input but not storing it
        printf("\n\t\t\t\tEnter the amount you want to deposit: ");
        number_Read = scanf("%f", &amount_to_deposit);
    }
	
    c.balance += amount_to_deposit;
	
    printf("\n\t\t\t\tThank you for depositing.\n\t\t\t\tYour updated balance is: Rs.%.2f\n", c.balance); // printing result

	do
	{   fflush(stdin);
		printf("\n\t\t\t\tDo you want to make another deposit? (1=yes and 2=no):"); // asking if user wants to recall function
        scanf("%d", &choice);

		if (choice == 1)
        {
            deposit(&c); // recursive call to function 
			break;

		}

		else if (choice != 2) 
        {
            printf("\n\t\t\t\tError! Please enter choice again:"); // error handling
        }
		else
		{
			return;
		}

	} while (1);
}


void check_balance(struct customer* cust)
{	
	printf("\n\t\t\t\tYour current balance is: Rs.%.2f\n", c.balance); //returning balance from struct customer
    fflush(stdin);
    getchar();
    //Sleep(20000);
    usleep(2000);
}


void withdraw(struct customer* cust) /* Function to withdraw amount
                                      passing pointer to struct customer*/
{
    float amount_to_withdraw;
    int choice;
    int num_Read = 0;
    
    printf("\n\t\t\t\tEnter the amount you want to withdraw: "); // Asking user for input
	num_Read = scanf("%f", &amount_to_withdraw);
    
	while (num_Read != 1 || amount_to_withdraw > c.balance) // Handling the case where withrawal amount is greater than balance and if input is correct
	{
		printf("\n\n\t\t\t\tRequest not processed.\nPlease try again:");
        scanf("%*[^\n]"); // reading till \n character of input but not storing it
        printf("\n\n\t\t\t\tEnter the amount you want to withdraw: ");
        num_Read = scanf("%f", &amount_to_withdraw);
    }	
   
    c.balance -= amount_to_withdraw;
    printf("\n\t\t\t\tYour updated balance is: %.2f", c.balance); // printing balance
    num_Read = 0;     
    printf("\n\t\t\t\tdo you want to withdraw any other amount? (1=yes and 2=no):\n\t\t\t\t"); // asking if user wants to call function again
	num_Read = scanf("%d", &choice);

    while (num_Read != 1 || choice < 1 || choice > 2)
	{
        printf("\n\t\t\t\tIncorrect key pressed. Please try again:");
        scanf("%*[^\n]"); // reading till \n character of input but not storing it

        printf("\n\n\t\t\t\tdo you want to withdraw any other amount?(1=yes and 2=no):");
        num_Read = scanf("%d", &choice);
    }
    if (choice == 1)
    {
        withdraw(&c); // recursive call

    }
    else
    {
        return;
    }

}

void deleteAccount()
{
    int numRead = 0;
    unsigned long long CNIC;
    printf("\n\t\t\t\tEnter the CNIC of customer whose account you want to delete: ");
    numRead = scanf("%llu", &CNIC);
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
        // don't write this customer's struct to temp file (same as deleting it)
        if (cust1.CNIC == CNIC)
        {
            printf("\n\t\t\t\tAccount of USER: %s is successfully deleted!\n", cust1.name);
            found = 1;
        }
        // write every other struct to temp file
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
    else
    {
        printf("\n\t\t\t\tA customer with this CNIC does not exist in the database, hence cannot be deleted!\n");
    }

}

void updateAccount()
{
    int numRead = 0;
    unsigned long long CNIC;
    printf("\n\t\t\t\tEnter the CNIC of customer whose account you want to modify: ");
    numRead = scanf("%llu", &CNIC);
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
        if (cust1.CNIC == CNIC)
        {
            printf("\n\t\t\t\tFor USER: %s:\n\n", cust1.name);
            found = 1;
            // update in-place details of struct cust1 (that has matching CNIC)
            char name[80];
            system("cls");
            start:
            fflush(stdin);
            while (1)
            {
                printf("\t\t\t\tEnter updated name: "); // Asking for name
                fgets(name, (sizeof(name)/sizeof(char)), stdin);
                int digits = 0;
                int i = 0;
        
                for (int i = 0; name[i] != '\0'; i++) // Checking if name entered is correct
                {    
                    if (name[i] == ' ' || name[i] == '\n')
                    {
                        continue;
                    }
                    else if (isalpha(name[i]) != 0)
                    {
                        continue;
                    }
                    else
                    {
                        digits+= 1;
                    }
       
                }
                if (digits != 0)
                {
                    printf("\t\t\t\tError!Name can only include alphabets.\n"); // Printing error otherwise
                    goto start;
                    system("cls");
                }
                else
                {
                    // assign name here
                    strcpy(cust1.name, name);
                    break;
                }    
            }
    
            while (1)
            {   

                int errors = 0;
                char buff1[14], buff2[14];
                int numRead = 0;

                printf("\t\t\t\tEnter updated 13-digit long CNIC number (without '-'): "); // Asking for ID
                numRead = scanf("%llu", &CNIC);
        
                while (numRead != 1)
                {
                    printf("\t\t\t\tError. Invalid CNIC entered. Please try again.\n\t\t\t\t");
                    scanf("%*[^\n]");
                    printf("\t\t\t\tEnter updated 13-digit long CNIC number (without '-'): "); // Asking for ID again
                    numRead = scanf("%llu", &CNIC);
                }
                //printf("%llu\n", CNIC);

                int count = 0; 
                unsigned long long num = CNIC;
                if(CNIC > 0)
                {   
                    
                    do // Counting number of digits of CNIC. Should be 13
                    {
                        num = num/10;
                        count ++;
                
                    } while (num != 0);

                    if (count == 13)
                    {
                        // assign CNIC value here
                        cust1.CNIC = CNIC;
                        break;
                    }
                    else
                    {   
                        
                        continue;
                    }

                }
            }   


            while (1)
            {       
                char day[50];
                char month[50];
                char year[50];

                int dd,mm,yyyy;        


                int numRead = 0;

                stop1:
                printf("\t\t\t\tEnter your updated day of birth:\n\t\t\t\t"); // Asking for date of birth
                numRead = scanf("%d", &dd);
                while (numRead != 1)    
                {
                    printf("\t\t\t\tError. Please try again.\n\t\t\t\t");
                    scanf("%*[^\n]");
                    printf("\t\t\t\tEnter your updated date of birth:\n\t\t\t\t");    
                    numRead = scanf("%d", &dd);
                }    

                if (dd < 0 || dd > 31)
                {
                    printf("\t\t\t\tError! Invalid date\n\t\t\t\t");
                    goto stop1;
                }    
                else
                {
                    cust1.day = dd;
                }
                
                numRead = 0;

                stop2:
                printf("\t\t\t\tEnter your updated month of birth:\n\t\t\t\t"); // Asking for month of birth
                numRead = scanf("%d", &mm);
                while (numRead != 1)    
                {
                    printf("\t\t\t\tError. Please try again.\n\t\t\t\t");
                    scanf("%*[^\n]");
                    printf("\t\t\t\tEnter your updated month of birth:\n\t\t\t\t");    
                    numRead = scanf("%d", &mm);
                }

                if (mm < 0 || mm > 12)
                {
                    printf("\t\t\t\tError! Invalid month\n\t\t\t\t");
                    goto stop2;
                }

                else
                {
                    cust1.month = mm;
                }

                numRead = 0;

                stop3:
                printf("\t\t\t\tEnter your updated year of birth:\n\t\t\t\t"); // Asking for year of birth
                numRead = scanf("%d", &yyyy);
                while (numRead != 1)    
                {
                    printf("\t\t\t\tError. Please try again.\n\t\t\t\t");
                    scanf("%*[^\n]");
                    printf("\t\t\t\tEnter your updated year of birth:\n\t\t\t\t");    
                    numRead = scanf("%d", &yyyy);
                }

                if (yyyy < 1900 || yyyy > 3000)
                {
                    printf("\t\t\t\tError! Invalid year.\n");
                    goto stop3;
                }

                else
                {
                    cust1.year = yyyy;
                }

                break;
            }     
    



            int numRead = 0;
            unsigned long long phone;


            while (1)
            {   
                stop4:
                
                printf("\t\t\t\tEnter your updated 11-digit long primary mobile number (starting with 0): ");
                numRead = scanf("%llu", &phone);
                while (numRead != 1)
                {
                    printf("\t\t\t\tError! incorrect number added. Please try again.\n");
                    scanf("%*[^\n]");
                    printf("\t\t\t\tEnter your updated 11-digit long primary mobile number(starting with 0): ");
                    numRead = scanf("%llu", &phone);
                }
                
                int num = phone;
                int count = 0;
                do 
                {
                    num /= 10;
                    count++;
                } while (num != 0);

                if (count != 10)
                {
                    printf("\t\t\t\tIncorrect phone number. Try again.\n");
                    goto stop4;
                }


                break;       

            }

            cust1.phone = phone;


            // set password of user here
            char password[80];
            while (1)
            {
                stop5:

                printf("\n\t\t\t\tSet your updated password: ");
                fflush(stdin);
                scanf("%[^\n]", password);
                // check if password is not empty
                if (password[0] != '\0')
                {
                    break;
                }
                else
                {
                    printf("\t\t\t\tPassword is empty string. Please try again.\n");
                    goto stop5;
                }
            }

            strcpy(cust1.password, password);

            // set initial balance of user here
            double balance;

            while(1)
            {
                stop6:

                printf("\n\t\t\t\tEnter an updated valid starting balance for this account: ");
                fflush(stdin);
                if (scanf("%lf", &balance) != 1) 
                {
                    printf("\n\t\t\t\tEntered balance value is not valid. Please try again.\n");
                    goto stop6;
                }
                else
                {
                    break;
                }

            }

            // set balance here
            cust1.balance = balance;
            
            printf("\n");

            // write updated struct cust1 to temp.dat file
            printf("\n\t\t\t\tThe followiing updated user information will be saved:\n");
            printCustomer(cust1);
            fwrite(&cust1, sizeof(struct customer), 1, fp1);
        }
        // write struct cust1 as it is to temp.dat file
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
            // write record to original file data.dat
            fwrite(&cust1, sizeof(cust1), 1, fp);
        }
        fclose(fp);
        fclose(fp1);
    }

}


    