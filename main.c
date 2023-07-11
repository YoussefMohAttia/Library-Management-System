#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    int month;
    int year;
} date;
typedef struct
{
    char isbn[20];
    char title[50];
    char name[50];
    int quantity;
    float price;
    date d;
} book;
char m [20][20];
book x[100];
int count=0;
void month(int i)
{
    if ((x[i].d.month)==1)
        strcpy(m[i],"January");
    else if ((x[i].d.month)==2)
        strcpy(m[i],"February");
    else if ((x[i].d.month)==3)
        strcpy(m[i],"March");
    else if ((x[i].d.month)==4)
        strcpy(m[i],"April");
    else if ((x[i].d.month)==5)
        strcpy(m[i],"May");
    else if ((x[i].d.month)==6)
        strcpy(m[i],"June");
    else if ((x[i].d.month)==7)
        strcpy(m[i],"July");
    else if ((x[i].d.month)==8)
        strcpy(m[i],"August");
    else if ((x[i].d.month)==9)
        strcpy(m[i],"September");
    else if ((x[i].d.month)==10)
        strcpy(m[i],"October");
    else if ((x[i].d.month)==11)
        strcpy(m[i],"November");
    else if ((x[i].d.month)==12)
        strcpy(m[i],"December");
}
void validatedate(int count)
{
    char month[10],year[10];
    int flag;
    do
    {
        flag=0;
        printf("Please enter month  \n");
        gets(month);
        for (int i=0; i<strlen(month); i++)
        {
            if (!isdigit(month[i]))
                flag=1;
            if (atoi(month)>12 || atoi(month)<1)
                flag=1;
        }
    }
    while(flag==1);
    do
    {
        flag=0;
        printf("Please enter year  \n");
        gets(year);
        for (int i=0; i<strlen(year); i++)
        {
            if (!isdigit(year[i]))
                flag=1;
            if (atoi(year)>2022 || atoi(year)<1)
                flag=1;
        }
    }
    while(flag==1);
    x[count].d.month=atoi(month);
    x[count].d.year=atoi(year);
}

void validateisbn(int j)
{
    int i,flag,m=0,flag2;
    char z[20];
    do
    {
        flag=0;
        flag2=0;
        printf("please enter isbn \n");
        scanf("%s",z);
        for (i=0; z[i]=='\0' ; i++)
        {
            if (z[i]<'0' || z[i]>'9')
                flag=1;
        }
        while(z[m]!='\0')
        {
            m++;
        }
        if(m!=13)
            flag=1;
    }
    while (flag==1);
    strcpy(x[j].isbn,z);
}

int Login()
{
    char user[50],userx[50];
    int pass[50],passx[50],flag=1,c;
    FILE *f1;
    f1=fopen("credentials.txt","r");
    if(f1!=NULL)
    {
        fscanf(f1,"%s",&userx);
        fscanf(f1,"%s",&passx);
    }
    else
        printf("Error File not found!\n\a");
    printf("Please enter user\n");
    gets(user);
    if(strcmp(user,userx)!=0)
        flag=0;
    printf("Please enter pass\n");
    gets(pass);
    if(strcmp(pass,passx)!=0)
        flag=0;
    if(flag==0)
    {
        printf("User or Password is not verified!\a\n\n");
        printf("1.If you want to Login again!\n");
        printf("2.Quit \n");
        scanf("%d",&c);
        if(c==1)
        {
            getchar();
            Login();
        }
        if(c==2)
            QUIT();
    }
    fclose(f1);
}

int LOAD()
{
    int i=0;
    char c;
    FILE *f = fopen("books.txt","r");
    if (f == NULL)
    {
        printf("Error! Could not open file\n");
        exit(0);
    }
    do
    {
        fscanf(f,"%[^,],",x[i].isbn);
        fscanf(f,"%[^,],",x[i].title);
        fscanf(f,"%[^,],",x[i].name);
        fscanf(f,"%d,",&x[i].quantity);
        fscanf(f,"%f,",&x[i].price);
        fscanf(f,"%d-%d",&x[i].d.month,&x[i].d.year);
        count++;
        i++;
    }
    while ((c=getc(f))!=EOF);
    count--;
    fclose(f);
}
void AdvancedSearch()
{
    int i,flag=0;
    char s[20];
    printf("Please enter Keyword \n");
    getchar();
    gets(s);
    for (i=0; i<count; i++)
    {
        if (strstr(x[i].title,s)!=NULL)
        {
            flag=1;
            month(i);
            printf("ISBN: %s \n",x[i].isbn);
            printf("Title: %s \n",x[i].title);
            printf("Author: %s \n",x[i].name);
            printf("quantity: %d \n",x[i].quantity);
            printf("Price: %.2f$ \n",x[i].price);
            printf("Published: %s %d\n",m[i],x[i].d.year);
            printf("\n\n");
        }
    }
    if(flag==0)
    {
        printf("There is no Book with matching Keyword\a\n\n");
        Menu();
    }
}
void SEARCH()
{
    int i,flag=0;
    char s[20];
    printf("Please enter ISBN \n");
    scanf("%s",s);
    for (i=0; i<count; i++)
    {
        if (strcmp(x[i].isbn,s)==0)
        {
            flag=1;
            month(i);
            printf("ISBN: %s \n",x[i].isbn);
            printf("Title: %s \n",x[i].title);
            printf("Author: %s \n",x[i].name);
            printf("quantity: %d \n",x[i].quantity);
            printf("Price: %.2f$ \n",x[i].price);
            printf("Published: %s %d\n",m[i],x[i].d.year);
            printf("\n\n");
        }
    }
    if(flag==0)
    {
        printf("There is no Book with this ISBN\a\n\n");
        Menu();
    }
}

void ADD ()
{
    validateisbn(count);
    printf("Please enter Title \n");
    getchar();
    gets(x[count].title);
    printf("Please enter Author Name \n");
    gets(x[count].name);
    validatedate(count);
    printf("Please enter Quantity \n");
    scanf("%d",&x[count].quantity);
    printf("Please enter Price \n");
    scanf("%f",&x[count].price);
    count++;
}
void DELETE_REC()
{
    int i,j,flag=0;
    char z[20];
    printf("Please enter the book ISBN you want to delete \n");
    scanf("%s",z);
    for (i=0; i<count; i++)
    {
        if (strcmp(x[i].isbn,z)==0)
        {
            for (j=i; j<count-1; j++)
            {
                x[j]=x[j+1];
            }
            flag=1;
            i--;
            count--;
        }
    }
    if (flag==0)
    {
        printf("Not Found! Please enter again \a\n\n");
        Menu();
    }
}

void MODIFY()
{
    int i,flag=0,y;
    char z[20];
    printf("Please enter the ISBN you want to modify \n");
    scanf("%s",z);
    for (i=0; i<count; i++)
    {
        if (strcmp(x[i].isbn,z)==0)
        {
            flag=1;
            do
            {
                printf("What do you want to modify? \n");
                printf("1.ISBN \n");
                printf("2.Title \n");
                printf("3.Name \n");
                printf("4.Quantity \n");
                printf("5.Price \n");
                printf("6.Date  \n");
                scanf("%d",&y);
                if (y==1)
                {
                    validateisbn(i);
                    break;
                }
                else if (y==2)
                {
                    printf("Please enter Title \n");
                    getchar();
                    gets(x[i].title);
                    break;
                }
                else if (y==3)
                {
                    printf("Please enter Author Name \n");
                    getchar();
                    gets(x[i].name);
                    break;
                }
                else if (y==4)
                {
                    printf("Please enter Quantity \n");
                    scanf("%d",&x[i].quantity);
                    break;
                }
                else if (y==5)
                {
                    printf("Please enter Price \n");
                    scanf("%f",&x[i].price);
                    break;
                }
                else if (y==6)
                {
                    getchar();
                    validatedate(i);
                    break;
                }
                else printf("Please enter again.\a\n\n");
            }
            while (1);
        }
    }
    if(flag==0)
    {
        printf("There is no Book with this ISBN\a\n\n");
        Menu();
    }

}

void SortByDate()
{
    int i,pass;
    book temp;
    for (pass=1; pass<count; pass++)
    {
        for (i=0; i<count-pass; i++)
        {
            if (x[i].d.year<x[i+1].d.year)
            {
                temp=x[i];
                x[i]=x[i+1];
                x[i+1]=temp;
            }
            if (x[i].d.year==x[i+1].d.year)
            {
                if (x[i].d.month<x[i+1].d.month)
                {
                    temp=x[i];
                    x[i]=x[i+1];
                    x[i+1]=temp;
                }
            }
        }

    }
}

void SortByprice()
{
    int i,pass;
    book temp;
    for (pass=1; pass<count; pass++)
    {
        for (i=0; i<count-pass; i++)
        {
            if (x[i].price>x[i+1].price)
            {
                temp=x[i];
                x[i]=x[i+1];
                x[i+1]=temp;
            }
        }
    }
}
void SortBytitle()
{
    int i,pass;
    book temp;
    for (pass=1; pass<count; pass++)
    {
        for (i=0; i<count-pass; i++)
        {
            if (strcasecmp(x[i].title,x[i+1].title)>0)
            {
                temp=x[i];
                x[i]=x[i+1];
                x[i+1]=temp;
            }
        }
    }
}

void PRINT()
{
    int y,i;
    printf("How do you want to sort the array? \n");
    printf("1.Sort By Title \n");
    printf("2.Sort By price \n");
    printf("3.Sort By Date \n");
    scanf("%d",&y);
    if (y==1)
        SortBytitle();
    else if (y==2)
        SortByprice();
    else if (y==3)
        SortByDate();
    for (i=0; i<count; i++)
    {
        month(i);
        printf("ISBN: %s \n",x[i].isbn);
        printf("Title: %s \n",x[i].title);
        printf("Author: %s \n",x[i].name);
        printf("quantity: %d \n",x[i].quantity);
        printf("Price: %.2f$ \n",x[i].price);
        printf("Published: %s %d\n",m[i],x[i].d.year);
        printf("\n\n");
    }
}

void SAVE()
{
    int i;
    FILE *f;
    f=fopen("Books.txt","w");
    for (i=0; i<count; i++)
    {
        fprintf(f,"%s,",x[i].isbn);
        fprintf(f,"%s,",x[i].title);
        fprintf(f,"%s,",x[i].name);
        fprintf(f,"%d,",x[i].quantity);
        fprintf(f,"%.2f,",x[i].price);
        fprintf(f,"%d-%d\n",x[i].d.month,x[i].d.year);
    }
    fclose(f);
}
void QUIT()
{
    exit(0);
}
void Menu()
{
    char ch;
    int x;
    do
    {
        printf("1.Add \n");
        printf("2.Delete \n");
        printf("3.Modify \n");
        printf("4.Search \n");
        printf("5.ADV.Search \n");
        printf("6.Print \n");
        printf("7.Save \n");
        printf("8.Quit \n");
        scanf("%d",&x);
        if (x==1)
            ADD();
        else if (x==2)
            DELETE_REC();
        else if (x==3)
            MODIFY();
        else if (x==4)
            SEARCH();
        else if (x==5)
            AdvancedSearch();
        else if (x==6)
            PRINT();
        else if (x==7)
            SAVE();
        else if (x==8)
        {
            printf("Are you sure you don't want to save press? If you want to save press 'y' \n");
            getchar();
            scanf("%c",&ch);
            if (ch=='y' || ch=='Y')
                SAVE();
            QUIT();
        }
        else printf("Please enter again.\a\n");
    }
    while (1);
}
int main()
{
    char ch;
    int x;
    Login();
    LOAD();
    Menu();
    return 0;
}
