#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include<ctype.h>
//#include "populate.h"


//============================================================================================//


void display(AddressBook *addressBook)
{
           printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
}


void sortby_name(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=i+1;j<addressBook->contactCount;j++)
            {
                if(strcasecmp(addressBook->contacts[i].name, addressBook->contacts[j].name)>0)
                {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i]=addressBook->contacts[j];
                    addressBook->contacts[j]=temp;
                }
            }
        }
        display(addressBook);
}


void sortby_phone(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++)
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
        display(addressBook);
}


void sortby_email(AddressBook *addressBook)
{
        for(int i=0;i<addressBook->contactCount-1;i++)
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
         display(addressBook);
}


//---------------------------------------diplay contacts-------------------------------------------//


void listContacts(AddressBook *addressBook) 
{
    int sortCriteria;
    //----display based on the chosen criteria----//
    do
    {   
        printf("\nchoise method of Displaying contacts by:\n");
        printf("1. name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");
        printf("4. Exit\n");

        scanf("%d",&sortCriteria);

    switch(sortCriteria)
    {
        //---------------------------sort and display by name------------------------------//
        case 1:
            sortby_name(addressBook);
        break;
        //---------------------------sort and display by phone number-------------------------------//
        case 2: 
            sortby_phone(addressBook);
        break;
        //----------------------------sort and display by email id----------------------------------//
        case 3: 
            sortby_email(addressBook);
        break;
        case 4:
            printf("\nExiting.....\n");
            return;
    
        default:
            printf("Invalid input, Re-enter : ");
    }
    }while(1);
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


//=========================================================================================//


int name_validtion(char *name,AddressBook *addressBook,int index)
{
          for(int i=0;i<addressBook->contactCount;i++)
        //----check Entered name is duplicate or not----//
        {
               if(i!= index && strcasecmp(name, addressBook->contacts[i].name)==0)
            {
                printf("Re-nter Valid Name, Entered name is alreday Exist : ");
                return 0;
            }
        }
        for(int i=0;name[i]!=0;i++)
        {
            if(isalnum(name[i])==0) 
            //----check alphanumeric or not----//
            {
                printf("Re-nter Valid Name which should not contains panctuation Characters like !,@,#,$,%%,&,*,..... : ");
                return 0;
            }
        }
        return 1;
}

int phone_validtion(char *phone,AddressBook *addressBook,int index)
{
      //----validation for phone number----//
    for(int i=0;phone[i]!=0;i++)
    {
        if(isdigit(phone[i])==0)
        //----check Entered phone number is digits or not----/
        {
            printf("Re-enter Valid Phone Number, shuold 0 to 9 : "); 
            return 0; 
        }
    }
    if(strlen(phone)!=10|| phone[0]<'6')
    //----check phone number is 10 digit and non-duplicate----//
    {
          printf("Re-enter Phone Number, First Number should be greater then 5 and phone number should be 10 digits only : ");  
          return 0;
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(i != index && strcmp(phone, addressBook->contacts[i].phone)==0)
        {
            printf("Re-nter Valid Phone Number, Entered Number alreday Exist : ");
            return 0;
        }
    }
    return 1;
}

int email_validtion(char *email,AddressBook *addressBook,int index)
{
//----validation for email----//

for(int i=0;i<addressBook->contactCount;i++)
        //----check duplicate is present or not----//
        {
            if(i!= index && strcmp(email, addressBook->contacts[i].email)==0)
            {
                printf("Re-nter Valid email, Entered email is alreday Exist : ");
                return 0;
            }
        }

/*for(int i=0;i<addressBook->contactCount;i++)
//----check duplicate or not----//
{
    if(strcasecmp(email, addressBook->contacts[i].email)==0)
    {
    printf("Re-nter Valid email, Entered email is alreday Exist : ");
    return 0;
    }
}*/
int at_count=0,at_pos;
for(int i=0;email[i]!=0;i++)
{
    if(isupper(email[i])!=0 || email[i]==' ')
    //----check uppercase and space----//
    {
    printf("Re-Enter valid Email which should be in Lowercase and should not contains space : ");
    return 0;
    }
    if(email[i]=='@') 
    //----find count and position of @----//
    {
    	at_count++;
        at_pos=i;
    }
}
int len =strlen(email); // find length of email
    if(email[0]=='@' || at_count!=1 || (len-4)-at_pos <2 ) 
    //----check @ is in fisrt place and @ shoulb be ones occ,between @...com should be 1 charactor----//
    {
        printf("Re-Enter valid Email which should contains charecter like \".com\", \"@\" once and Between @ and .com there should be least one charector : ");
        return 0;     
    }
    if(len < 4 || strcmp(&email [len - 4], ".com") != 0)
    // check last 4 charcecter is .com or not   
    {
        printf("Re-Enter valid Email, \".com\" should be at last in Email : ");
        return 0;
    } 
    return 1;
}


//-----------------------------------------creat contacts-------------------------------------------//


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
        //-------------------------------reading name--------------------------------------------//
        printf("Enter Name : ");
        scanf("%s",addressBook->contacts[addressBook->contactCount].name);

        while(!name_validtion(addressBook->contacts[addressBook->contactCount].name,addressBook,-1))
        {
                scanf("%s",addressBook->contacts[addressBook->contactCount].name);
        }

        //------------------------------reading Phone number---------------------------------------//     
           
        printf("Enter Phone Number : ");
        scanf("%s",addressBook->contacts[addressBook->contactCount].phone);
        while(!phone_validtion(addressBook->contacts[addressBook->contactCount].phone,addressBook,-1))
        {
            scanf("%s",addressBook->contacts[addressBook->contactCount].phone);
        }       
        
        //------------------------------reading email id--------------------------------------//

        printf("Enter email ID : ");
        scanf("%s",addressBook->contacts[addressBook->contactCount].email);
        while(!email_validtion(addressBook->contacts[addressBook->contactCount].email,addressBook,-1))
        {
            scanf("%s",addressBook->contacts[addressBook->contactCount].email);
        }        
        addressBook->contactCount++;
}


 //-------------------sreach and display by name-----------------------//
void search_desplay_name(AddressBook *addressBook, char *whatever)
{
    int flag=0;
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strcasestr(addressBook->contacts[i].name, whatever)!=NULL)
         {
            if(flag==0)
            {
                printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
                flag=1;
            }
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     if(flag==0)
     {
        printf("Contact not found\n");
     }
}

 //-------------------sreach and display by phone number-----------------------//
void search_desplay_phone(AddressBook *addressBook, char *whatever)
{
    int flag=0;
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strstr(addressBook->contacts[i].phone, whatever)!=NULL)
         {
            if(flag==0)
            {
                printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
                flag=1;
            }
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     if(flag==0)
     {
        printf("Contact not found\n");
     }
}

 //-------------------sreach and display by email id-----------------------//
void search_desplay_email(AddressBook *addressBook, char *whatever)
{
    int flag=0;
     for(int i=0;i<addressBook->contactCount;i++)
     {
         if(strstr(addressBook->contacts[i].email, whatever)!=NULL)
         {
            if(flag==0)
            {
                printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
                flag=1;
            }
            printf("  %d\t%s\t\t%s\t%s\n",i+1,addressBook->contacts[i].name,
                addressBook->contacts[i].phone,addressBook->contacts[i].email);
         }
     }
     if(flag==0)
     {
        printf("Contact not found\n");
     }
}

//---------------------------------------search contacts-------------------------------------------//


void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    char search[30];
    //----choise method of searching----//
    do
    {
    printf("\nchoise method of searching by:\n");
        printf("1. name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");
        printf("4. Exit\n");
        
        scanf("%d",&choice);
        if(choice==4)
        {
            printf("\nExiting.....\n");
            return;   
        }

    printf("Enter what you wants to search : ");
    scanf("%s",search);
    switch(choice)
    {
     case 1:
       search_desplay_name(addressBook, search);
     break;

     case 2:
        search_desplay_phone(addressBook, search);
     break;

     case 3:
        search_desplay_email(addressBook, search);
     break;

     default:
         printf("Invalid input, Re-enter : ");
    }
    }while(1);
}

//============================================================================================//

void read_index(int *index, AddressBook *addressBook)
{
    while(1) //----validation for index----//
      {
        scanf("%d",index);
        if(*index>0 && *index<=addressBook->contactCount)
            break;
        else
        printf("Invalid index number, re enter : ");
      }
}

//-------------------------------edit contact----------------------------------------------//


void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice,index;
    char edit[30];
    //----choise method of editing by----// 
    do{
    printf("\nchoose the method of editing the contcat by:\n");
        printf("1. name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");
        printf("4. Exit\n");

        scanf("%d",&choice);
        if(choice==4)
        {
            printf("\nExiting.....\n");
            return;   
        }

    printf("Enter what you wants to search : ");
    scanf("%s",edit);
    switch(choice)
    {
    //-------------------edit by name-----------------------//
     case 1:
        search_desplay_name(addressBook, edit);
        printf("Select the index number of Contcat which you want to edit : ");
        read_index(&index, addressBook);

        printf("Enter New Name : ");
        scanf("%s",addressBook->contacts[index-1].name);
        while(!name_validtion(addressBook->contacts[index-1].name,addressBook,index-1))
        {
                scanf("%s",addressBook->contacts[index-1].name);
        }
        printf("\nContact Successfully edit...\n");
     break;

    //-------------------edit by phone number-----------------------//
     case 2:
        search_desplay_phone(addressBook, edit);
        printf("Select the index number of Contcat which you want to edit : ");
        read_index(&index, addressBook); 

        printf("Enter New Phone Number : ");
        scanf("%s",addressBook->contacts[index-1].phone);
        while(!phone_validtion(addressBook->contacts[index-1].phone,addressBook,index-1))
        {
                scanf("%s",addressBook->contacts[index-1].phone);
        }
        printf("\nContact Successfully edit...\n");
     break;

    //-------------------edit by email id-----------------------//
     case 3:
        search_desplay_email(addressBook, edit);
        printf("Select the index number of Contcat which you want to edit : ");
        read_index(&index, addressBook);

        printf("Enter New email ID : ");
        scanf("%s",addressBook->contacts[index-1].email); 
        while(!email_validtion(addressBook->contacts[index-1].email,addressBook,index-1))
        {
                scanf("%s",addressBook->contacts[index-1].email);
        }
        printf("\nContact Successfully edit...\n");
     break;

     default:
         printf("Invalid input, Re-enter : ");
    }
    }while(1);
}



//======================================================================================//
void delete_contact(AddressBook *addressBook,int index)
{
    for(int j=index;j<addressBook->contactCount-1;j++)
    {
        addressBook->contacts[j]=addressBook->contacts[j+1];
    } 
     addressBook->contactCount--;
    printf("\nContact Successfully Deleted...\n");
}


//-------------------------------delete contact----------------------------------------------//


void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice,index;
    char Delete[30];
    //----choise method of deleting by----// 
    do{
    printf("\nchoose the method of Delete the contact by:\n");
        printf("1. name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");
        printf("4. Exit\n");

        scanf("%d",&choice);
        if(choice==4)
        {
            printf("\nExiting.....\n");
            return;   
        }

    printf("Enter what you wants to search: ");
    scanf("%s",Delete);
    switch(choice)
    {
    //----search by name and delete the selected contact----//
     case 1:
      search_desplay_name(addressBook, Delete);
      printf("Select the index number of Contcat which you want to Delete : ");
      read_index(&index, addressBook);
      delete_contact(addressBook,index-1); 
     break;

    //----search by phone number and delete the selected contact----//
     case 2:
      search_desplay_phone(addressBook, Delete);
      printf("Select the index number of Contcat which you want to Delete : ");
      read_index(&index, addressBook);
      delete_contact(addressBook,index-1); 
     break;

    //----search by phone number and delete the selected contact----//
     case 3:
     search_desplay_email(addressBook, Delete);
     printf("Select the index number of Contcat which you want to Delete : ");
     read_index(&index, addressBook);
     delete_contact(addressBook,index-1); 
     break;

     default:
         printf("Invalid input, Re-enter : "); 
    }
}while(1);
}