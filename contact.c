#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include<ctype.h>
//#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    int sortCriteria;
    //Sort contacts based on the chosen criteria
        printf("\nChoice Sort by:\n");
        printf("1. name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");

        scanf("%d",&sortCriteria);

    switch(sortCriteria)
    {
        case 1:// by name
        for(int i=0;i<addressBook->contactCount;i++)
        {
            for(int j=i+1;j<addressBook->contactCount;j++)
            {
                if(strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name)>0)
                {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i]=addressBook->contacts[j];
                    addressBook->contacts[j]=temp;
                }
            }
        }
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("%d\tName : %s\tPhone : %s\tEmail : %s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
        case 2: // by phone number
        for(int i=0;i<addressBook->contactCount;i++)
        {
            for(int j=i+1;j<addressBook->contactCount;j++)
            {
                if(strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone)>0)
                {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i]=addressBook->contacts[j];
                    addressBook->contacts[j]=temp;
                }
            }
        }
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("%d\tName : %s\tPhone : %s\tEmail : %s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
        case 3: // email
        for(int i=0;i<addressBook->contactCount;i++)
        {
            for(int j=i+1;j<addressBook->contactCount;j++)
            {
                if(strcmp(addressBook->contacts[i].email, addressBook->contacts[j].email)>0)
                {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i]=addressBook->contacts[j];
                    addressBook->contacts[j]=temp;
                }
            }
        }
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("%d\tName : %s\tPhone : %s\tEmail : %s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
        default:
        printf("Invalid input");
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
        printf("Enter Name : ");
        name:
        scanf("%s",addressBook->contacts[addressBook->contactCount].name);
        for(int i=0;addressBook->contacts[addressBook->contactCount].name[i]!=0;i++)
        {
            if(isalnum(addressBook->contacts[addressBook->contactCount].name[i])==0) // str is alphanumeric or not
            {
                printf("Re-nter Valid Name which should not contains panctuation Characters like !,@,#,$,%%,&,*,..... : ");
                goto name;
            }
        }
            printf("Enter Phone Number : ");
            phone:
            scanf("%s",addressBook->contacts[addressBook->contactCount].phone);
            // validation for phone number
            for(int i=0;addressBook->contacts[addressBook->contactCount].phone[i]!=0;i++)
            {
                if(isdigit(addressBook->contacts[addressBook->contactCount].phone[i])==0)
                {
                    printf("Re-enter Phone Number, First Number should be greater then 5 and phone number should be 10 digits only : ");  
                    goto phone;
                }
            }
            if(strlen(addressBook->contacts[addressBook->contactCount].phone)==10 && addressBook->contacts[addressBook->contactCount].phone[0]>'5')
            {
                printf("Enter email ID : ");
                email:
                scanf("%s",addressBook->contacts[addressBook->contactCount].email);
                // validation for email
                int at_count=0,at_pos;
                for(int i=0;addressBook->contacts[addressBook->contactCount].email[i]!=0;i++)
                {
                if(isupper(addressBook->contacts[addressBook->contactCount].email[i])!=0 || addressBook->contacts[addressBook->contactCount].email[i]==' ')
                // check uppercase and space in email
                {
                    printf("Re-Enter valid Email which should be in Lowercase and contains charecter like \".com\", \"@\" once and should not contains space : ");
                    goto email;
                }
                if(addressBook->contacts[addressBook->contactCount].email[i]=='@') // find count and position of @
                {
                    at_count++;
                    at_pos=i;
                }
                }
                int len =strlen(addressBook->contacts[addressBook->contactCount].email); // find length of email
                if(addressBook->contacts[addressBook->contactCount].email[0]=='@' || at_count!=1 || (len-4)-at_pos <2 ) 
                // check @ is in fisrt place and @ shoulb be ones occ,between @...com should be 1 charactor
                {
                   printf("Re-Enter valid Email which should be in Lowercase and contains charecter like \".com\", \"@\" once and should not contains space : ");
                   goto email; 
                }
                if(len < 4 || strcmp(&addressBook->contacts[addressBook->contactCount].email[len - 4], ".com") != 0)// check last 4 charcecter is .com or not
                {
                    printf("Re-Enter valid Email which should be in Lowercase and contains charecter like \".com\", \"@\" once and should not contains space : ");
                    goto email;
                }   
                addressBook->contactCount++;
            }
            else
            {
              printf("Re-enter Phone Number, First Number should be greater then 5 and phone number should be 10 digits only : ");  
              goto phone;
            }
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    char search[30];
    // choise method of searching
    printf("\nSearch by:\n");
        printf("1. name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");

        scanf("%d",&choice);

    printf("Enter what you wants to search: ");
    scanf("%s",search);
    switch(choice)
    {
     case 1:
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strstr(addressBook->contacts[i].name, search)!=NULL)
         {
             printf("%d\tName : %s\tPhone : %s\tEmail : %s\n",i+1,addressBook->contacts[i].name,
                 addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     break;
     case 2:
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strstr(addressBook->contacts[i].phone, search)!=NULL)
         {
             printf("%d\tName : %s\tPhone : %s\tEmail : %s\n",i+1,addressBook->contacts[i].name,
                 addressBook->contacts[i].phone,addressBook->contacts[i].email);
          }
     }
     break;
     case 3:
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strstr(addressBook->contacts[i].email, search)!=NULL)
         {
             printf("%d\tName : %s\tPhone : %s\tEmail : %s\n",i+1,addressBook->contacts[i].name,
                 addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     break;
     default:
         printf("Invalid input");
    }
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice;
    char Delete[30];
    // choise method of deleting by 
    printf("\nDelete by:\n");
        printf("1. name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");

        scanf("%d",&choice);

    printf("Enter what you wants to search: ");
    scanf("%s",Delete);
    switch(choice)
    {
     case 1:
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strcmp(addressBook->contacts[i].name, Delete)==0)
         {
            for(int j=i;j<addressBook->contactCount-1;j++)
            {
             addressBook->contacts[j]=addressBook->contacts[j+1];
            }
            addressBook->contactCount--;
            i--;
         }
     }
     break;
     case 2:
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strcmp(addressBook->contacts[i].phone, Delete)==0)
         {
            for(int j=i;j<addressBook->contactCount-1;j++)
            {
             addressBook->contacts[j]=addressBook->contacts[j+1];
            }
            addressBook->contactCount--;
            i--;
         }
     }
     break;
     case 3:
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strcmp(addressBook->contacts[i].email, Delete)==0)
         {
            for(int j=i;j<addressBook->contactCount-1;j++)
            {
             addressBook->contacts[j]=addressBook->contacts[j+1];
            }
            addressBook->contactCount--;
            i--;
         }
     }
     break;
     default:
         printf("Invalid input");
    }
    printf("Contact Successfully Deleted\n");
}