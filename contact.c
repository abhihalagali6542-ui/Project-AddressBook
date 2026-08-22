#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include<ctype.h>
//#include "populate.h"
//---------------------------------------diplay contacts-------------------------------------------//
void listContacts(AddressBook *addressBook) 
{
    int sortCriteria;
    //----display based on the chosen criteria----//
        printf("\nDisplay contacts by:\n");
        printf("1. name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");

        scanf("%d",&sortCriteria);

    switch(sortCriteria)
    {
        //---------------------------sort and display by name------------------------------//
        case 1:
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=i+1;j<addressBook->contactCount-1-i;j++)
            {
                if(strcasecmp(addressBook->contacts[i].name, addressBook->contacts[j].name)>0)
                {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i]=addressBook->contacts[j];
                    addressBook->contacts[j]=temp;
                }
            }
        }
        printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
        //---------------------------sort and display by phone number-------------------------------//
        case 2: 
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=i+1;j<addressBook->contactCount-1-i;j++)
            {
                if(strcasecmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone)>0)
                {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i]=addressBook->contacts[j];
                    addressBook->contacts[j]=temp;
                }
            }
        }
        printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
        //----------------------------sort and display by email id----------------------------------//
        case 3: 
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=i+1;j<addressBook->contactCount-1-i;j++)
            {
                if(strcasecmp(addressBook->contacts[i].email, addressBook->contacts[j].email)>0)
                {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i]=addressBook->contacts[j];
                    addressBook->contacts[j]=temp;
                }
            }
        }
        printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
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

//-----------------------------------------creat contacts-------------------------------------------//
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
        //-------------------------------reading name--------------------------------------------//
        printf("Enter Name : ");
        name:
        scanf("%s",addressBook->contacts[addressBook->contactCount].name);
        for(int i=0;i<addressBook->contactCount;i++)
        //----check Entered name is duplicate or not----//
        {
               if(strcasecmp(addressBook->contacts[addressBook->contactCount].name, addressBook->contacts[i].name)==0)
            {
                printf("Re-nter Valid Name, Entered name is alreday Exist : ");
                goto name;
            }
        }
        for(int i=0;addressBook->contacts[addressBook->contactCount].name[i]!=0;i++)
        {
            if(isalnum(addressBook->contacts[addressBook->contactCount].name[i])==0) 
            //----check alphanumeric or not----//
            {
                printf("Re-nter Valid Name which should not contains panctuation Characters like !,@,#,$,%%,&,*,..... : ");
                goto name;
            }
        }
            //------------------------------reading Phone number---------------------------------------//     
            printf("Enter Phone Number : ");
            phone:
            scanf("%s",addressBook->contacts[addressBook->contactCount].phone);
            //----validation for phone number----//
            for(int i=0;addressBook->contacts[addressBook->contactCount].phone[i]!=0;i++)
            {
                if(isdigit(addressBook->contacts[addressBook->contactCount].phone[i])==0)
                //----check Entered phone number is digits or not----/
                {
                    printf("Re-enter Valid Phone Number, shuold 0 to 9 : ");  
                    goto phone;
                }
            }
            if(strlen(addressBook->contacts[addressBook->contactCount].phone)==10 && addressBook->contacts[addressBook->contactCount].phone[0]>'5')
            //----check phone number is 10 digit and non-duplicate----//
            {
                for(int i=0;i<addressBook->contactCount;i++)
                {
                  if(strcmp(addressBook->contacts[addressBook->contactCount].phone, addressBook->contacts[i].phone)==0)
                  {
                        printf("Re-nter Valid Phone Number, Entered Number alreday Exist : ");
                        goto phone;
                  }
                }
                //------------------------------reading email id--------------------------------------//
                printf("Enter email ID : ");
                email:
                scanf("%s",addressBook->contacts[addressBook->contactCount].email);
                //----validation for email----//
                for(int i=0;i<addressBook->contactCount;i++)
                //----check duplicate or not----//
                {
                    if(strcasecmp(addressBook->contacts[addressBook->contactCount].email, addressBook->contacts[i].email)==0)
                    {
                       printf("Re-nter Valid email, Entered email is alreday Exist : ");
                       goto email;
                    }
                }
                int at_count=0,at_pos;
                for(int i=0;addressBook->contacts[addressBook->contactCount].email[i]!=0;i++)
                {
                if(isupper(addressBook->contacts[addressBook->contactCount].email[i])!=0 || addressBook->contacts[addressBook->contactCount].email[i]==' ')
                //----check uppercase and space----//
                {
                    printf("Re-Enter valid Email which should be in Lowercase and should not contains space : ");
                    goto email;
                }
                if(addressBook->contacts[addressBook->contactCount].email[i]=='@') 
                //----find count and position of @----//
                {
                    at_count++;
                    at_pos=i;
                }
                }
                int len =strlen(addressBook->contacts[addressBook->contactCount].email); // find length of email
                if(addressBook->contacts[addressBook->contactCount].email[0]=='@' || at_count!=1 || (len-4)-at_pos <2 ) 
                //----check @ is in fisrt place and @ shoulb be ones occ,between @...com should be 1 charactor----//
                {
                   printf("Re-Enter valid Email which should contains charecter like \".com\", \"@\" once\n"); 
                   printf("Between @ and .com there should be least one charector : ");
                   goto email; 
                }
                if(len < 4 || strcmp(&addressBook->contacts[addressBook->contactCount].email[len - 4], ".com") != 0)
                // check last 4 charcecter is .com or not
                {
                    printf("Re-Enter valid Email, \".com\" should be at last in Email : ");
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
//---------------------------------------search contacts-------------------------------------------//
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    char search[30];
    //----choise method of searching----//
    printf("\nSearch by:\n");
        printf("1. name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");

        scanf("%d",&choice);

    printf("Enter what you wants to search: ");
    scanf("%s",search);
    switch(choice)
    {
    //-------------------sreach and display by name-----------------------//
     case 1:
     printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strcasestr(addressBook->contacts[i].name, search)!=NULL)
         {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     break;
     //-------------------sreach and display by phone number-----------------------//
     case 2:
     printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strcasestr(addressBook->contacts[i].phone, search)!=NULL)
         {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
          }
     }
     break;
     //-------------------sreach and display by email id-----------------------//
     case 3:
     printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strcasestr(addressBook->contacts[i].email, search)!=NULL)
         {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     break;
     default:
         printf("Invalid input");
    }
}
//-------------------------------edit contact----------------------------------------------//
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice,index;
    char edit[30];
    //----choise method of editing by----// 
    printf("\nchoose the method of editing the contcat by:\n");
        printf("1. name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");

        scanf("%d",&choice);

    printf("Enter what you wants to search: ");
    scanf("%s",edit);
    switch(choice)
    {
    //-------------------edit by name-----------------------//
     case 1:
      printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strcasestr(addressBook->contacts[i].name, edit)!=NULL)
         {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     printf("Select the index number of Contcat which you want to edit : ");
     re_enter_indx:
     scanf("%d",&index);
     if(index>=1 && index<=addressBook->contactCount)
     {
        printf("Enter New Name : ");
        name:
        scanf("%s",addressBook->contacts[index-1].name);
        for(int i=0;i<addressBook->contactCount;i++)
        //----check duplicate is present or not----//
        {
            if(i != index - 1 && strcasecmp(addressBook->contacts[index-1].name, addressBook->contacts[i].name)==0)
            {
                printf("Re-nter Valid Name, Entered name is alreday Exist : ");
                goto name;
            }
        }
        for(int i=0;addressBook->contacts[index-1].name[i]!=0;i++)
        {
            if(isalnum(addressBook->contacts[index-1].name[i])==0) // str is alphanumeric or not
            {
                printf("Re-nter Valid Name which should not contains panctuation Characters like !,@,#,$,%%,&,*,..... : ");
                goto name;
            }
        }
     }
     else
     {     
        printf("Invalid index number, re enter : ");
        goto re_enter_indx;
    }
     break;
    //-------------------edit by phone number-----------------------//
     case 2:
      printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strcasestr(addressBook->contacts[i].phone, edit)!=NULL)
         {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     printf("Select the index number of Contcat which you want to edit : ");
     re_enter_indxe:
     scanf("%d",&index);
    if(index>=1 && index<=addressBook->contactCount)
     {

        printf("Enter New Phone Number : ");
        phone:
        scanf("%s",addressBook->contacts[index-1].phone); 
        int Phone_len=strlen(addressBook->contacts[index-1].phone);
        if(Phone_len<10 && Phone_len>10 && addressBook->contacts[index-1].phone[0]<'6')
        {
            printf("Re-enter valid Phone Number of 10 Digits and first number should be greter than 5 : ");
            goto phone;
        }
        for(int i=0;i<addressBook->contactCount;i++)
        //----check duplicate is present or not----//
        {
              if(i != index - 1 && strcmp(addressBook->contacts[index-1].phone, addressBook->contacts[i].phone)==0)
              {
                    printf("Re-nter Valid Phone Number, Entered Number alreday Exist : ");
                    goto phone;
             }
        }
     }
     else
     {     
        printf("Invalid index number, re enter : ");
        goto re_enter_indxe;
    }
     break;
    //-------------------edit by email id-----------------------//
     case 3:
     printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strstr(addressBook->contacts[i].email, edit)!=NULL)
         {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     printf("Select the index number of Contcat which you want to edit : ");
     re_enter_index:
     scanf("%d",&index);
     if(index>=1 && index<=addressBook->contactCount)
     {
        printf("Enter New email ID : ");
        email:
        scanf("%s",addressBook->contacts[index-1].email); 
        for(int i=0;i<addressBook->contactCount;i++)
        //----check duplicate is present or not----//
        {
            if(i != index - 1 && strcasecmp(addressBook->contacts[index-1].email, addressBook->contacts[i].email)==0)
            {
                printf("Re-nter Valid email, Entered email is alreday Exist : ");
                goto email;
            }
        }
        int at_count=0,at_pos;
        for(int i=0;addressBook->contacts[index-1].email[i]!=0;i++)
        {
            if(isupper(addressBook->contacts[index-1].email[i])!=0 || addressBook->contacts[index-1].email[i]==' ')
            //----check uppercase and space----//
            {
                printf("Re-Enter valid Email which should be in Lowercase and should not contains space : ");
                goto email;
            }
            if(addressBook->contacts[index-1].email[i]=='@') 
            //----find count and position of @----//
            {
                at_count++;
                at_pos=i;
            }
        }
            int len =strlen(addressBook->contacts[index-1].email); // find length of email

            if(addressBook->contacts[index-1].email[0]=='@' || at_count!=1 || (len-4)-at_pos <2 ) 
            //----check @ is in fisrt place and @ shoulb be ones occ,between @...com should be 1 charactor----//
            {
                printf("Re-Enter valid Email which should contains charecter like \".com\", \"@\" once\n"); 
                printf("Between @ and .com there should be least one charector : ");
                goto email; 
            }
            if(len < 4 || strcmp(&addressBook->contacts[index-1].email[len - 4], ".com") != 0)
            // check last 4 charcecter is .com or not
            {
                printf("Re-Enter valid Email, \".com\" should be at last in Email : ");
                goto email;
            }
     }
     else
     {     
        printf("Invalid index number, re enter : ");
        goto re_enter_index;
     }
     break;
     default:
         printf("Invalid input");
    }
    printf("Contact Successfully edit...\n");
}
//-------------------------------delete contact----------------------------------------------//
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice,index;
    char Delete[30];
    //----choise method of deleting by----// 
    printf("\nchoose the method of Delete the contact by:\n");
        printf("1. name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");

        scanf("%d",&choice);

    printf("Enter what you wants to search: ");
    scanf("%s",Delete);
    switch(choice)
    {
    //----search by name and delete the selected contact----//
     case 1:
      printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strstr(addressBook->contacts[i].name, Delete)!=NULL)
         {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     printf("Select the index number of Contcat which you want to Delete : ");
     index_a:
     scanf("%d",&index);
     if(index>=1 && index<=addressBook->contactCount)
     //----validation for index----//
     {
        for(int j=index-1;j<addressBook->contactCount-1;j++)
        {
          addressBook->contacts[j]=addressBook->contacts[j+1];
        }  
     }
     else
     {     
        printf("Invalid index number, re enter : ");
        goto index_a;
    }
     addressBook->contactCount--;
     break;
    //----search by phone number and delete the selected contact----//
     case 2:
      printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strcasestr(addressBook->contacts[i].phone, Delete)!=NULL)
         {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     printf("Select the index number of Contcat which you want to Delete : ");
     index_b:
     scanf("%d",&index);
    if(index>=1 && index<=addressBook->contactCount)
    //----validation for index----//
     {
        for(int j=index-1;j<addressBook->contactCount-1;j++)
        {
          addressBook->contacts[j]=addressBook->contacts[j+1];
        }  
     }
     else
     {     
        printf("Invalid index number, re enter : ");
        goto index_b;
    }
     addressBook->contactCount--;
     break;
    //----search by phone number and delete the selected contact----//
     case 3:
     printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strstr(addressBook->contacts[i].email, Delete)!=NULL)
         {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     printf("Select the index number of Contcat which you want to Delete : ");
     index_c:
     scanf("%d",&index);
     if(index>=1 && index<=addressBook->contactCount)
     //----validation for index----//
     {
        for(int j=index-1;j<addressBook->contactCount-1;j++)
        {
          addressBook->contacts[j]=addressBook->contacts[j+1];
        }  
     }
     else
     {     
        printf("Invalid index number, re enter : ");
        goto index_c;
    }
    addressBook->contactCount--;
     break;
     default:
         printf("Invalid input");
    }
    printf("Contact Successfully Deleted...\n");
}