#include <stdio.h>
#include <stdlib.h>



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int day;
    int month;
    int year;
} date;

typedef struct
{
    date DOB;
    char FirstName[100];
    char LastName[100];
    char address[200];
    char phone[100];
    char email[100];


} agent;


agent a[1000];
int counter;
int unsaved=0;
int validNumber (char phone [])
{
    int i;
    for (i=0; i<strlen(phone); i++)
    {
        if(!isdigit(phone [i]))
            return 0;
    }
    return 1;
}
int validemail (char Email[])
{
    int j;
    int atIndex;
    int dotIndex;
    int atFound = 0;
    int dotFound = 0;

    for(j=0; j<strlen(Email); j++)
    {
        if(Email[j]=='.')
        {
            dotIndex=j;
            dotFound=1;
        }
        if(Email[j]=='@')
        {
            atIndex=j;
            atFound += 1;
        }
    }
    if ((dotIndex-atIndex)>1&&atFound==1&&dotFound==1)
        return 1;
    else
        return 0;
}
void load()
{
    counter = 0;
    FILE*f;

    f=fopen("phonebook.txt","r+");
    if (f!=NULL)
    {

        while(!feof(f))
        {

            fscanf(f,"%[^,],",a[counter].LastName);
            fscanf(f,"%[^,],",a[counter].FirstName);
            fscanf(f,"%d-%d-%d,",&a[counter].DOB.day,&a[counter].DOB.month,&a[counter].DOB.year);
            fscanf(f,"%[^,],",a[counter].address);
            fscanf(f,"%[^,],",a[counter].phone);
            fscanf(f," %s\n",a[counter].email);
            counter++;
        }
        fclose(f);
    }
    else
        printf("file is not found \n");
}
void ADD()
{
    printf("Enter data of the new Agent  ");
    printf("\nplease enter last name : ");
    scanf("%s",a[counter].LastName);
    while(atoi(a[counter].LastName)>0)
    {
        printf("Please enter a valid last name that doesn't contain numbers: \n");
        scanf("%s",a[counter].LastName);
    }
    printf("\nplease enter first name :");
    scanf("%s",a[counter].FirstName);
    while(atoi(a[counter].FirstName)>0)
    {
        printf("Please enter a valid First name that doesn't contain numbers: \n");
        scanf("%s",a[counter].FirstName);
    }
    printf("\nplease enter date of birth as dd-mm-yyyy :");
    scanf("%d-%d-%d,",&a[counter].DOB.day,&a[counter].DOB.month,&a[counter].DOB.year);
    while (a[counter].DOB.day>31||a[counter].DOB.month>12||a[counter].DOB.year>2021||a[counter].DOB.day==0||a[counter].DOB.month==0||a[counter].DOB.year==0)
    {
        printf("\nThe date of birth you wrote is incorrect please enter date of birth as dd-mm-yyyy CORRECTLY :");
        scanf("%d-%d-%d,",&a[counter].DOB.day,&a[counter].DOB.month,&a[counter].DOB.year);
    }

    printf("\nplease enter address : ");
    getchar();
    gets(a[counter].address);
    printf("\nplease enter phone number : ");
    scanf("%s",a[counter].phone);
    while (validNumber(a[counter].phone)==0)
    {
        printf("\nplease enter phone number correctly : ");
        scanf("%s",a[counter].phone);
    }
    printf("\nplease enter email : ");
    scanf("%s",a[counter].email);
    while(validemail(a[counter].email)==0)
    {
        printf("please enter email correctly :");
        scanf("%s",a[counter].email);

    }
    counter = counter + 1;
    unsaved=1;
}
void DELETE()
{
    char x[20],y[20];
    int i=0;
    int ch=0;
    printf("\nenter the last name which you want to delete : ");
    scanf("%s",x);
    printf("\nenter the first name which you want to delete : ");
    scanf("%s",y);
    while(i<counter)
    {
        if (strcasecmp(x,a[i].LastName)==0&&strcasecmp(y,a[i].FirstName)==0)
        {
            while(i<counter-1)
            {
                a[i]=a[i+1];
                i=i+1;

            }
            counter=counter-1;
            i--;
            ch=1;
        }
        else
            i=i+1;
    }
    if(ch==0)
    {
        printf("\nUser not found! Please enter a valid user\n\n");
    }
    unsaved=1;
}
void PRINT_SORTED()
{
    int n;
    int i;
    int pass;
    agent temp;
    int x;
    printf("choose the way you want the agents to be sorted:\n");
    printf("1-by last name\n2-by date of birth\n");
    scanf("%d",&n);
    if(n==1)
    {
        for(pass=0; pass<counter-1; pass++)
        {
            for(i=0; i<counter-pass-1; i++)
            {
                if(strcasecmp(a[i].LastName,a[i+1].LastName)>0)
                {
                    temp=a[i];
                    a[i]=a[i+1];
                    a[i+1]=temp;
                }
            }
        }
    }
    else if(n==2)
    {

        for(x=0; x<counter-1; x++)
        {

            for(i=0; i<counter-x-1; i++)
            {
                if(a[i].DOB.year<a[i+1].DOB.year)
                {
                    temp=a[i];
                    a[i]=a[i+1];
                    a[i+1]=temp;
                }
                else if(a[i].DOB.year==a[i+1].DOB.year && a[i].DOB.month<a[i+1].DOB.month)
                {
                    temp=a[i];
                    a[i]=a[i+1];
                    a[i+1]=temp;
                }
                else if(a[i].DOB.year==a[i+1].DOB.year && a[i].DOB.month==a[i+1].DOB.month && a[i].DOB.day<a[i+1].DOB.day)
                {
                    temp=a[i];
                    a[i]=a[i+1];
                    a[i+1]=temp;
                }
            }
        }
    }
    else
    {
        printf("choose again either 1 or 2\n");
    }
    if(n==1 || n==2)
    {
        printf("Data are sorted in the following order:\n");

       for(i=0;i<counter;i++)
    {
       printf("last name : ");
        printf("%s, ",a[i].LastName);
        printf("first name : ");
        printf("%s, ",a[i].FirstName);
        printf("Date of birthday : ");
        printf("%d-%d-%d, ",a[i].DOB.day,a[i].DOB.month,a[i].DOB.year);
        printf("address : ");
        printf("%s, ",a[i].address);
        printf("phone number : ");
        printf("%s, ",a[i].phone);
        printf("email : ");
        printf("%s \n",a[i].email);
        printf("----------------------------------------------------------------------------\n");
    }
    }
     unsaved=1;
}
void Modify()
{
    int i;
   char lsname[100];
   int c=0;
   int ival[100];
   char cc[100];
   int cast;
   char xl[100];
   int x;
   int y=1;
   printf("Please enter the last name of the contact you want to modify : \n");
   scanf("%s", lsname);
   for(i=0;i<counter;i++)
   {
       if(strcasecmp(lsname,a[i].LastName)==0)
       {
           ival[c]=i;
           c++;
       }
   }
   if(c>0)
   {
       printf("Please choose one of the following contacts (just choose the number written beside the contact) : \n");
       for(i=0;i<c;i++)
       {
        printf("%d %s ",i+1,a[ival[i]].FirstName);
       printf("%s\n",a[ival[i]].LastName);
       }
       scanf("%s",cc);
       while(atoi(cc)==0 || atoi(cc)>c)
       {
           printf("Please choose correctly by entering a number from 1 to %d!\n",c);
           scanf("%s",cc);
       }
       cast=atoi(cc);
       while(y)
       {
       printf("What would you like to modify: \n");
       printf("1-First name\n2-Last name\n3-Date of birth\n4-Number\n5-Address\n6-Email\n");
       scanf("%s",xl);
       while(atoi(xl)==0 || atoi(xl)>6)
       {
           printf("Please select correctly between 1 and 6: \n");
           scanf("%s",xl);
       }
       x=atoi(xl);
           switch(x)
           {
               case 1:
               printf("Please enter new first name: \n");
               scanf("%s",a[ival[cast-1]].FirstName);
               break;
               case 2:
               printf("Please enter new last name: \n");
               scanf("%s",a[ival[cast-1]].LastName);
               break;
               case 3:
               printf("\nplease enter the new date of birth as dd-mm-yyyy :");
               scanf("%d-%d-%d,",&a[ival[cast-1]].DOB.day,&a[ival[cast-1]].DOB.month,&a[ival[cast-1]].DOB.year);
               while (a[ival[cast-1]].DOB.day>31||a[ival[cast-1]].DOB.month>12||a[ival[cast-1]].DOB.year>2021||a[ival[cast-1]].DOB.day==0||a[ival[cast-1]].DOB.month==0||a[ival[cast-1]].DOB.year==0)
             {
               printf("\nThe date of birth you wrote is incorrect please enter date of birth as dd-mm-yyyy CORRECTLY :");
               scanf("%d-%d-%d,",&a[ival[cast-1]].DOB.day,&a[ival[cast-1]].DOB.month,&a[ival[cast-1]].DOB.year);
             }
               break;
               case 4:
               printf("Please enter new number: \n");
               scanf("%s",a[ival[cast-1]].phone);
               while (validNumber(a[ival[cast-1]].phone)==0)
              {
                printf("\nplease enter phone number correctly : ");
                scanf("%s",a[ival[cast-1]].phone);
              }
               break;
               case 6:
               printf("Please enter new email: \n");
               scanf("%s",a[ival[cast-1]].email);
                while(validemail(a[ival[cast-1]].email)==0)
              {
               printf("please enter email correctly :");
               scanf("%s",a[ival[cast-1]].email);
              }
               break;
               case 5:
               printf("Please enter new address: \n");
               fflush(stdin);
               gets(a[ival[cast-1]].address);
               break;
           }

               printf("Would you like to edit something else? 1 means yes and 0 means no: \n");
               scanf("%d",&y);
               while((y<0 && y>1))
               {
                   printf("Please enter 1 or 0");
                   scanf("%d",&y);
               }
       }
   }
   else
   {
       printf("Couldn't find this user! please try again\n");
       Modify();
   }
   unsaved=1;
}
void searchbylastname()
{
    int i;
    char Last_Name[100];
    int co=0;
    printf("Enter the last name of the agent you want to find: ");
    scanf("%s",Last_Name);
    for(i=0; i<counter; i++)
    {
        if((strcasecmp(Last_Name,a[i].LastName)==0))
        {
            printf("First Name:%s\n",a[i].FirstName);
            printf("Address:%s\n",a[i].address);
            printf("Email:%s\n",a[i].email);
            printf("Phone Number:%s\n",a[i].phone);
            printf("--------------------------------------------------------------------------------\n");
            co+=1;
        }
    }
    if(co==0)
    {
        printf("\nYou entered a final name that doesn't exist! please enter a valid one.\n\n");
    }
    unsaved=1;
}

void SAVE()
{
    int i;
    FILE*f;
    f=fopen("phonebook.txt","w");
    for (i=0; i<counter; i++)
    {
        fprintf(f,"%s,",a[i].LastName);
        fprintf(f,"%s,",a[i].FirstName);
        fprintf(f,"%d-%d-%d,",a[i].DOB.day,a[i].DOB.month,a[i].DOB.year);
        fprintf(f,"%s,",a[i].address);
        fprintf(f,"%s,",a[i].phone);
        fprintf(f,"%s\n",a[i].email);
    }
    fclose(f);
    unsaved=0;
}
int QUIT()
{
    if(unsaved==1)
    {
        printf("Are you sure you would like to exit without saving ? 1 for yes and anything else for no");
        scanf("%d",&unsaved);
        if(unsaved==1)
            exit(0);
            else if(unsaved==0)
                return 0;
    }
    else
    exit(0);
}
int main()
{
char i[100];
    int y=1;
    while(y==1)
    {
        char x[100];
        int vald;
        printf("choose the task you want to excute : ");
        printf("\n1)LOAD");
        printf("\n2)SEARCH");
        printf("\n3)ADD");
        printf("\n4)DELETE");
        printf("\n5)MODIFY");
        printf("\n6)SORTTED PRINT");
        printf("\n7)SAVE");
        printf("\n8)QUIT\n");
        scanf("%s",x);
        while(atoi(x)==0 || atoi(x)>8 || atoi(x)==0)
        {
            printf("Please choose from 1 to 8: \n");
            scanf("%s",x);
        }
        vald=atoi(x);
        switch (vald)
        {
        case(1):
            load();
            break;
        case (2):
            searchbylastname();
            break;
        case (3):
            ADD();
            break;
        case(4):
            DELETE();
            break;
        case(5):
            Modify();
            break;
        case(6):
            PRINT_SORTED();
            break;
        case (7):
            SAVE();
            break;
        case (8):
            QUIT();
            break;
        }
            printf("would you like to excute any other tasks ? 1 for yes 2 for no: \n");
            scanf("%s",i);
            while((atoi(i)!=1&&atoi(i)!=2) || atoi(i)==0)
            {
                printf("Please enter 1 or 2: \n");
                scanf("%s",i);
            }
            y=atoi(i);
    }
        if(unsaved==1)
            {
                printf("Are you sure you would like to leave without saving ? 1 for yes 2 for no: \n ");
                scanf("%s",i);
            while((atoi(i)!=1&&atoi(i)!=2) || atoi(i)==0)
            {
                printf("Please enter 1 or 2: \n");
                scanf("%s",i);
            }
            y=atoi(i);
            if(y==2)
                main();
                else
                    return 0;
            }
    return 0;
}







