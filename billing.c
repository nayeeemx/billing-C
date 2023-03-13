#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>

FILE *fp;  //declaring file pointer (creating buffer)

COORD coord= {0,0};  //setting the central axis for reference as (0,0)

//defining gotoxy function for setting the cursor position
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//defining a global structure variable
struct record
{
    char x[14];
    float r;
    float q;
    float total;
}item2;

//function declaration
struct record item;
void mainmenu();
void delay();
void exit();


//defining the delay function to delay the system execution
void delay(int n)
{
    int milliseconds=1000*n;
    clock_t start_time=clock();
    while (clock()<start_time+milliseconds);

}


//defining the mainmenu function
void mainmenu()
{
    /opening file data1.txt using file pointer fp/
    fp=fopen("data1.txt","ab+");
    system("color 0f");
    int i,choice,j,billno,size;
    char save[1];
    float total1=0;
    const char *menu[]= {" 1.Calculate Bill"," 2.Clear Record", " 3.Show Sales"," 4.Exit","\n","Enter choice:","\n"};
    system("cls");
    window(25,50,20,32);
    gotoxy(33,18);
    printf("MAIN MENU");
    for (i=0; i<=6; i++)
    {
        gotoxy(30,22+i+1);
        printf("%s\n\n\n",menu[i]);
    }
    gotoxy(44,22+5+1);
    scanf("%d",&choice);
    if (choice==1)
    {
        system("cls");//clearing output screen
        shopname();
        gotoxy(10,17);
        printf("Bill No:");
        scanf("%d",&billno);
        gotoxy(26,15);
        printf("enter  \"end\" to finish input");
        i=29;
        while(1)
        {
            gotoxy(25,18);
            printf("                             ");
            gotoxy(25,19);
            printf("                             ");
            gotoxy(25,20);
            printf("                             ");
            gotoxy(25,18);
            printf("Enter item name:");
            scanf("%s",item.x);

            if(strcmp(item.x,"end")==0)
            {
                gotoxy(30,48);
                mainmenu();
                break;
            }

            else
                gotoxy(13,i);
                printf("%s",item.x);

                gotoxy(13,27);
                printf("Item Name     Quantity     Rate          Total");
                gotoxy(25,19);
                printf("Enter quantity:");
                scanf("%f",&item.q);
                gotoxy(28,i);
                printf("%6.2f",item.q);
                gotoxy(25,20);
                printf("Enter rate:");
                scanf("%f",&item.r);
                gotoxy(40,i);
                printf("%6.2f",item.r);
                gotoxy(53,i);
                item.total=item.q*item.r;
                printf("%6.2f",item.total);
                gotoxy(30,25);
                printf("CUSTOMER'S BILL") ;
                i++;
                total1=total1+item.total;
                gotoxy(34,45);
                printf("TOTAL AMOUNT = Rs. %6.2f",total1);
                fwrite(&item,26,1,fp);

        }
        fclose(fp); /closing file/
    }


    if(choice==2)
    {
         fp=fopen("data1.txt","w");
         fclose(fp);
         printf("\n\n\n");
         system("cls");
         shopname();
         gotoxy(25,18);
         printf("ALL THE RECORDS ARE DELETED!!!\n");
         delay(2);
         mainmenu();
         return 0;
    }

    if(choice==3)
    {
        system("cls");
        shopname();
        window1(25,50,20,36);
        gotoxy(36,18);
        printf("SALES");
        fp=fopen("data1.txt","rb+");
        fseek(fp,0,SEEK_SET);
        int n=1,var;
        int i=26;
        gotoxy(28,24);
        printf("NAME\tQUANTITY\n");
        while(n)
        {

            gotoxy(25,i);
            fread(&item2,26,1,fp);
            printf("%s",item2.x);
            gotoxy(40,i);
            printf("%6.2f\n",item2.q);
            if(feof(fp)!=0)
                n=0;
            i++;
            printf("\n\n\n");
            if(n==0)
                break;
        }
        gotoxy(28,i+3);
        printf("Enter 1 to exit:");
        scanf("%d",&var);
        if(var==1)
        {
            delay(1);
            mainmenu();
        }

        fclose(fp);
    }

    if (choice==4)
    {
        printf("\n\n\n");
    }
    if(choice>4)
    {
        system("cls");
        printf("INVALID CHOICE");
        mainmenu();
    }

}


//defining window function to print the table
void window(int a,int b,int c,int d)
{
    int i;
    shopname();
    for (i=a; i<=b; i++)
    {
        gotoxy(i,17);
        printf("\xcd");
        gotoxy(i,19);
        printf("\xcd");
        gotoxy(i,c);
        printf("\xcd");
        gotoxy(i,d);
        printf("\xcd");
    }

    gotoxy(a,17);
    printf("\xc9");
    gotoxy(a,18);
    printf("\xba");
    gotoxy(a,19);
    printf("\xc8");
    gotoxy(b,17);
    printf("\xbb");
    gotoxy(b,18);
    printf("\xba");
    gotoxy(b,19);
    printf("\xbc");
    for(i=c; i<=d; i++)
    {
        gotoxy(a,i);
        printf("\xba");
        gotoxy(b,i);
        printf("\xba");
    }
    gotoxy(a,c);
    printf("\xc9");
    gotoxy(a,d);
    printf("\xc8");
    gotoxy(b,c);
    printf("\xbb");
    gotoxy(b,d);
    printf("\xbc");
}


//defining window1 function to print the smaller table
void window1(int a,int b,int c,int d)
{
    int i;
    shopname();
    for (i=a; i<=b; i++)
    {
        gotoxy(i,17);
        printf("\xcd");
        gotoxy(i,19);
        printf("\xcd");

    }

    gotoxy(a,17);
    printf("\xc9");
    gotoxy(a,18);
    printf("\xba");
    gotoxy(a,19);
    printf("\xc8");
    gotoxy(b,17);
    printf("\xbb");
    gotoxy(b,18);
    printf("\xba");
    gotoxy(b,19);
    printf("\xbc");
}


//defining function to write shopname
void shopname()
{
    int i;
    gotoxy(12,10);
    for (i=1; i<=10; i++)
            printf("*");
    printf(" * PSG COLLEGE OF TECHNOLOGY * ");
    for (i=1; i<=10; i++)
            printf("*");
    printf("\n\n");
    gotoxy(30,11);
    printf("DEPARTMENTAL STORE");
}


//function execution starts (int main)
int main()
{
   FILE *fp;
   int pcode;
   char username[50];
   char custname[25];

   user:

        window1(25,50,20,36);
        gotoxy(28,18);
        printf("USER NAME:");
        scanf("%s", &username);
        if (strcmp(username,"nithiesh")==0 ||strcmp(username,"nayeem")==0)
            {
              goto pass;
            }
        else
            {
               system("cls");
               printf("INVALID USERNAME\n");
               goto user;
            }
   char password[50],c;
   int i=0;
   pass:
        system("cls");
        window1(25,50,36,52);
        gotoxy(28,18);
        printf("PASSWORD :");
        int p=0;
        do
            {
                password[p]=getch();/reading password/
               if(password[p]!='\r')
               {
                   printf("*");
               }
                p++;
            }while(password[p-1]!='\r');
             password[p-1]='\0';
         if (strcmp(password,"mscss2022")==0)
            {
              system("cls");
              goto mainmenu;
            }
        else
            {
               system("cls");
               printf("INVALID PASSWORD\n");
               goto user;
            }

   mainmenu:
           {
           mainmenu();
           return 0;
           }

           /function execution ends/

   return 0;/function execution was successfull/
}