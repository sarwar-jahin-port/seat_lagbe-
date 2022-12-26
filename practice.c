#include<stdio.h>
#include<string.h>
#include<process.h>
#include<windows.h>
#include<time.h>

void gotoxy(int x, int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);     //1. HANDLE 2. COORD
}

struct User
{
    char id[20], pass[100], route[100], role[10];
};
struct User u[100];

struct SeatBooking
{
    char seat_name[2][4], uid[20];
    int seat_no;
};
struct SeatBooking seat[100];

struct SeatNumber
{
    char seat[10];
};
struct SeatNumber num[100];


int n; //global variable for count users
int current; // global variable for showing data on 'my profile' for particular user1
char seatArray[50][4];
//using this for password encryption
//char key[70] = "PgEfTYaWGHjDAmxQqFLRpCJBownyUKZXkbvzIdshurMilNSVOtec#@_!=.+-*/";
//char org[70] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
void c_time()
{
    time_t s = time(NULL);
    struct tm* cur_time;
    cur_time= localtime(&s);
    printf("Time: %02d:%02d:%02d", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
}
void logo()
{
    gotoxy(20, 2);
    printf("   _____ ______       _______   _               _____ ____  ______ ___  \n");
    gotoxy(20, 3);
    printf("  / ____|  ____|   /\\|__   __| | |        /\\   / ____|  _ \\|  ____|__ \\ \n");
    gotoxy(20, 4);
    printf(" | (___ | |__     /  \\  | |    | |       /  \\ | |  __| |_) | |__     ) |\n");
    gotoxy(20, 5);
    printf("  \\___ \\|  __|   / /\\ \\ | |    | |      / /\\ \\| | |_ |  _ <|  __|   / / \n");
    gotoxy(20, 6);
    printf("  ____) | |____ / ____ \\| |    | |____ / ____ \\ |__| | |_) | |____ |_|  \n");
    gotoxy(20, 7);
    printf(" |_____/|______/_/    \\_\\_|    |______/_/    \\_\\_____|____/|______|(_)  \n");
}

void getData()
{
    int i;
    FILE *fp;
    fp = fopen("userDB.txt", "r");

    for(i=0; fscanf(fp, "%s", u[i].id) != -1; i++)
    {
        fscanf(fp,"%s", u[i].pass);
        fscanf(fp,"%s", u[i].role);
        fscanf(fp,"%s", u[i].route);
    }
    n=i;
    fclose(fp);
}

void writeData()
{
    FILE *fr;
    fr = fopen("userDB.txt", "w");

    for(int i = 0; i<n; i++)
    {
        fprintf(fr, "%s\n", u[i].id);
        fprintf(fr, "%s\n", u[i].pass);
        fprintf(fr, "%s\n", u[i].role);
        fprintf(fr, "%s\n", u[i].route);
    }
    fclose(fr);
}

void signup()
{
    int x;
    char uid[10], key[100], route[100];
    gotoxy(50, 10);
    printf("  REGISTER\t\t");
    gotoxy(50, 12);
    printf("\t\t");
    gotoxy(50, 14);
    printf("\t\t\t");
    gotoxy(50, 12);
    printf("  Enter ID: ");
    scanf("%s", uid);
    gotoxy(50, 14);
    printf("  Enter Password: ");
    scanf("%s", key);

    gotoxy(50, 16);
    printf("  Routes Available:\n");
    gotoxy(50, 18);
    printf("  1. IIUC - Chawkbazar\n");
    gotoxy(50, 20);
    printf("  2. IIUC - Bahaddarhat\n");
    gotoxy(50, 22);
    printf("  Enter Your Route: ");
    scanf("%d", &x);

    strcpy(u[n].id, uid);
    strcpy(u[n].pass,key);
    strcpy(u[n].role, "user");
    if(x == 1)
    {
        strcpy(u[n].route, "Chawkbazar");
    }
    else if(x == 2)
    {
        strcpy(u[n].route, "Bahaddarhat");
    }

    n++;

}

void login()
{
    system("cls");
    logo();
    char str[100], password[100];
    int checkingIfUserfound = 0;
    gotoxy(50, 10);
    printf("  LOGIN\t\t");
    gotoxy(50, 12);
    printf("\t\t");
    gotoxy(50, 14);
    printf("\t\t\t");
    gotoxy(50, 12);
    printf("  Enter ID: ");
    scanf("%s", str);

    gotoxy(50, 14);
    printf("  Enter Password: ");
    scanf("%s", password);

    for(int i = 0; i<n; i++)
    {
        if(strcmp(str,u[i].id) == 0 && strcmp(password, u[i].pass) == 0)
        {
            current = i; // takes the value of i, so that we can use it to show profile information
            checkingIfUserfound = 1;
            if(strcmp("admin",u[i].role) == 0)
            {
                system("cls");
                adminPanel();
                break;
            }
            else
            {
                system("cls");
                homepage();
                break;
            }

        }
    }

    if(checkingIfUserfound == 0)
    {
        printf("\n\nWrong Username or Password\n\n");
    }

}
void go_back_user(int j)
{
    int q;
    gotoxy(24, j+7);
    printf("Press 0 to return: ");
    scanf("%d", &q);
    if(q==0) homepage();
    else go_back(j);
}
void Myprofile()
{
    int seat_no=0, s1_found=-1, s2_found=-1;
    char seat1[30],seat2[30];
    getData();
    gotoxy(24, 10);
    printf("                     ");
    gotoxy(55, 10);
    printf("                     ");
    gotoxy(24, 12);
    printf("                     ");
    gotoxy(24, 14);
    printf("                    ");
    gotoxy(24, 16);
    printf("                    ");
    gotoxy(24, 18);
    printf("                    ");
    gotoxy(24, 10);
    printf("%s\n", u[1].id);
    gotoxy(24, 12);
    printf("%s\n", u[1].pass);
    gotoxy(24, 14);
    printf("%s\n", u[1].role);
    gotoxy(24, 16);
    printf("%s\n", u[1].route);
    FILE *fp = fopen("Bus information.txt","r");
    int seat_available, seat_booked;
    fscanf(fp, "%d", &seat_available); // available seat
    fscanf(fp, "%d", &seat_booked);
    int i=0;
    for(i = 0; fscanf(fp, "%s", seat[i].uid)!=-1; i++)
    {
        if((strcmp(seat[i].uid, u[current].id))==0)
        {
            fscanf(fp, "%d", &seat[i].seat_no);
            seat_no = seat[i].seat_no;
            for(int j=0; j<seat[i].seat_no; j++)
            {
                fscanf(fp, "%s",seat[i].seat_name[j]);
                if(j==0)
                {
                    s1_found=1;
                    strcpy(seat1, seat[i].seat_name[j]);
                }
                if(j==1)
                {
                    s2_found=2;
                    strcpy(seat2, seat[i].seat_name[j]);
                }
            }
        }
        //printf("entered in loop");
        fscanf(fp, "%d", &seat[i].seat_no);
        for(int j=0; j<seat[i].seat_no; j++)
        {
            fscanf(fp, "%s",seat[i].seat_name[j]);
        }
    }
    //printf("%d", i);
    fclose(fp);

    if(s1_found != -1)
    {
        gotoxy(24, 14);
        printf("Booked seat:%s",seat1);
        if(s2_found != -1) printf(" %s",seat2);
    }
    go_back_user(12);
    getchar();
}

void delete_seat(char seatToDelete[])
{

    FILE *af=fopen("seat_info.txt", "r");

    int i;

    for(i = 0; fscanf(af, "%s", num[i].seat) != -1; i++)
    {

    }

    fclose(af);

    int position = -1;

    for(int j = 0; j<i; j++)
    {
        //temp = user[i].numOfFriend;
        if(strcmp(seatToDelete, num[j].seat) == 0)
        {
            position = j;
            break;
        }
    }


    if(position != -1)
    {
        for(int x = position; x<i-1; x++)
        {
            strcpy(num[x].seat, num[x+1].seat);
        }
        i--;


        FILE *af = fopen("seat_info.txt", "w");
        for(int u = 0; u<i; u++)
        {
            fprintf(af, "%s\n", num[u].seat);
        }
        fclose(af);
    }

}


void book_seat()
{
    getData();
    printf("book seat function called");
    FILE *af=fopen("seat_info.txt", "r");
    for(int a=0; fscanf(af, "%s", seatArray[a])!=-1; a++)
    {
        // printf("%s", seatArray[a]);
    }
    fclose(af);
    /*char seatArray[50][4] = {"1A", "1B", "1C", "1D",
                             "2A", "2B", "2C", "2D",
                             "3A", "3B", "3C", "3D",
                             "4A", "4B", "4C", "4D",
                             "5A", "5B", "5C", "5D",
                             "6A", "6B", "6C", "6D",
                             "7A", "7B", "7C", "7D",
                             "8A", "8B", "8C", "8D",
                             "9A", "9B", "9C", "9D",
                             "10A", "10B", "10C", "10D"};*/ // total seat 40
    /*for(int i =0;i<40;i++){
        printf("%s\n", seatArray[i]);
    }*/
    int seat_available, seat_booked, user_input;

    FILE *fp = fopen("Bus information.txt","r");
    fscanf(fp, "%d", &seat_available); // available seat
    fscanf(fp, "%d", &seat_booked);
    int i=0;
    for(i = 0; fscanf(fp, "%s", seat[i].uid)!=-1; i++)
    {
        if((strcmp(seat[i].uid, u[current].id))==0)
        {
            printf("You have already booked your seat.");
            printf("%s", seat[i].uid);
            printf("%s", u[current].id);
            go_back_user(10);
        }
        printf("entered in loop");
        fscanf(fp, "%d", &seat[i].seat_no);
        for(int j=0; j<seat[i].seat_no; j++)
        {
            fscanf(fp, "%s",seat[i].seat_name[j]);
        }
    }

    printf("%d", i);
    fclose(fp);
    printf("How many seats do you want?\n");
    printf("1.One\n");
    printf("2.Two\n");
    printf("Enter Number: ");
    scanf("%d", &user_input);


    FILE *fr = fopen("Bus information.txt","w");
    if(user_input == 1)
    {
        printf("asked for one seat");
        seat_available--;
        strcpy(seat[i].uid,u[current].id);
        seat[i].seat_no=1;
        strcpy(seat[i].seat_name, seatArray[0]);
        seat_booked++;
        printf("%s\n", seat[i].uid);
        printf("%d\n", seat[i].seat_no);
        printf("%s\n", seat[i].seat_name);
        fprintf(fr,"%d\n", seat_available);
        fprintf(fr, "%d\n", seat_booked);

        for(int x = 0; x<=i; x++)
        {
            fprintf(fr, "%s\n", seat[x].uid);
            fprintf(fr, "%d\n", seat[x].seat_no);
            for(int y=x; y<x+1 ; y++)
            {
                if(seat[x].seat_no==1)
                {
                    delete_seat(seat[y].seat_name[0]);
                    fprintf(fr, "%s\n", seat[y].seat_name[0]);


                }
                if(seat[x].seat_no==2)
                {
                    delete_seat(seat[y].seat_name[0]);
                    fprintf(fr, "%s ", seat[y].seat_name[0]);
                    fprintf(fr, "%s\n", seat[y].seat_name[1]);
                }

            }
        }
    }
    else if(user_input == 2)
    {
        printf("asked for two seat");
        seat_available-=2;
        //printf("%s", u[current].id);
        strcpy(seat[i].uid,u[current].id);
        //printf("%s", seat[i].uid);
        seat[i].seat_no=2;
        strcpy(seat[i].seat_name[0], seatArray[0]);
        strcpy(seat[i].seat_name[1], seatArray[1]);
        seat_booked+=2;
        //printf("%s\n", seat[i].uid);
        //printf("%d\n", seat[i].seat_no);
        //printf("%s\n", seat[i].seat_name[0]);
        //printf("%s\n", seat[i].seat_name[1]);
        fprintf(fr,"%d\n", seat_available);
        fprintf(fr, "%d\n", seat_booked);
        for(int x = 0; x<=i; x++)
        {
            fprintf(fr, "%s\n", seat[x].uid);
            fprintf(fr, "%d\n", seat[x].seat_no);
            for(int y=x; y<x+1 ; y++)
            {
                if(seat[x].seat_no==1){
                    delete_seat(seat[y].seat_name[0]);
                    fprintf(fr, "%s\n", seat[y].seat_name[0]);
                }
                if(seat[x].seat_no==2)
                {
                    fprintf(fr, "%s", seat[y].seat_name[0]);
                    fprintf(fr, " %s\n", seat[y].seat_name[1]);

                    delete_seat(seat[y].seat_name[0]);
                    delete_seat(seat[y].seat_name[1]);
                }
            }
        }
    }
    fclose(fr);
    go_back_user(10);
}


void seat_cancel()
{

    FILE *af = fopen("seat_info.txt", "r");

    int n;

    for(n = 0; fscanf(af, "%s", num[n].seat) != -1; n++)
    {

    }

    fclose(af);

    int seat_available, seat_booked;

    FILE *fp = fopen("Bus information.txt","r");
    fscanf(fp, "%d", &seat_available); // available seat
    fscanf(fp, "%d", &seat_booked);
    int i;
    for(i = 0; fscanf(fp, "%s", seat[i].uid)!=-1; i++)
    {
        fscanf(fp, "%d", &seat[i].seat_no);
        for(int j=0; j<seat[i].seat_no; j++)
        {
            fscanf(fp, "%s",seat[i].seat_name[j]);
        }
    }
    fclose(fp);

    for(int x = 0; x<i; x++)
    {
        if(strcmp(u[current].id, seat[x].uid) == 0)
        {
            if(seat[x].seat_no == 1)
            {

                strcpy(num[n].seat, seat[x].seat_name[0]);
                n++;
                FILE *af = fopen("seat_info.txt", "w");

                for(int w = 0; w<n ; w++)
                {
                    fprintf(af, "%s\n", num[w].seat);
                }
                fclose(af);

                int position = x;

        for(int z = position; z<i-1; z++)
        {
            seat[z] = seat[z+1];
        }
        i--;


        FILE *fr = fopen("Bus information.txt", "w");
        seat_available++;
        seat_booked--;

        fprintf(fr,"%d\n", seat_available);
        fprintf(fr, "%d\n", seat_booked);

        for(int m = 0; m<i; m++)
        {
            fprintf(fr, "%s\n", seat[m].uid);
            fprintf(fr, "%d\n", seat[m].seat_no);

            if(seat[m].seat_no == 1){
               for(int y=m; y<m+1 ; y++)
            {
                fprintf(fr, "%s\n", seat[y].seat_name[0]);
            }
            }
            if(seat[m].seat_no == 2){
                 for(int y=m; y<m+1 ; y++)
            {
                fprintf(fr, "%s ", seat[y].seat_name[0]);
                fprintf(fr, "%s\n", seat[y].seat_name[1]);
            }
            }

    }
            fclose(fr);

            }
            if(seat[x].seat_no == 2)
            {

                strcpy(num[n].seat, seat[x].seat_name[0]);
                strcpy(num[n+1].seat, seat[x].seat_name[1]);
                n+=2;

                FILE *af = fopen("seat_info.txt", "w");

                for(int w = 0; w<n ; w++)
                {
                    fprintf(af, "%s\n", num[w].seat);
                }
                fclose(af);

                int position = x;

        for(int z = position; z<i-1; z++)
        {
            seat[z] = seat[z+1];
        }
        i--;


        FILE *fr = fopen("Bus information.txt", "w");
        seat_available++;
        seat_booked--;

        fprintf(fr,"%d\n", seat_available);
        fprintf(fr, "%d\n", seat_booked);

        for(int m = 0; m<i; m++)
        {
            fprintf(fr, "%s\n", seat[m].uid);
            fprintf(fr, "%d\n", seat[m].seat_no);
            if(seat[m].seat_no == 1){
               for(int y=m; y<m+1 ; y++)
            {
                fprintf(fr, "%s\n", seat[y].seat_name[0]);
            }
            }
            if(seat[m].seat_no == 2){
                 for(int y=m; y<m+1 ; y++)
            {
                fprintf(fr, "%s ", seat[y].seat_name[0]);
                fprintf(fr, "%s\n", seat[y].seat_name[1]);
            }
            }
    }
            fclose(fr);
            }
        }
    }

}

void Cancelseat()
{
    gotoxy(24, 10);
    printf("                     ");
    gotoxy(55, 10);
    printf("                     ");
    gotoxy(24, 12);
    printf("                     ");
    gotoxy(24, 14);
    printf("                    ");
    gotoxy(24, 16);
    printf("                    ");
    gotoxy(24, 18);
    printf("                    ");
    char confirm;
    gotoxy(24, 10);
    printf("Click X to cancel!\n");
    gotoxy(24, 12);
    scanf(" %c",&confirm);
    //printf("%c", confirm);
    if(confirm==88 || confirm==120)
    {
       seat_cancel();
    }
    else
    {
        gotoxy(24, 12);
        printf("Enter Correctly.\n");
    }
    go_back_user(6);
}

void homepage()
{
    system("cls");
    gotoxy(94, 10);
    c_time();
    logo();
    gotoxy(24, 10);
    printf("1. MY PROFILE");
    gotoxy(24, 12);
    printf("2. BOOK YOUR SEAT");
    gotoxy(24, 14);
    printf("3. CANCEL YOUR SEAT");
    gotoxy(24, 16);
    printf("4. FAQ");
    gotoxy(24, 18);
    printf("5. LOG OUT");
    gotoxy(24, 20);
    printf("Enter Number: ");
    int q;
    scanf("%d", &q);
    if(q==1) Myprofile();
    if(q==2) book_seat();
    if(q==3) Cancelseat();
    //if(q==4) faqBot();
    if(q==5) main();
}
void go_back(int j)
{
    int q;
    gotoxy(24, j+7);
    printf("Press 0 to return: ");
    scanf("%d", &q);
    if(q==0) adminPanel();
    else go_back(j);
}
void view_user()
{
    getData();
    int i, j;
    gotoxy(24, 10);
    printf("                     ");
    gotoxy(55, 10);
    printf("ALL USERS");
    gotoxy(24, 12);
    printf("                     ");
    gotoxy(24, 14);
    printf("                    ");
    gotoxy(24, 16);
    printf("                    ");
    gotoxy(24, 18);
    printf("                    ");
    for(i=1, j=10; i<n; i++, j+=3)
    {
        gotoxy(24, j+i);
        printf("id:%s\t\t\n", u[i].id);
        gotoxy(24, j+1+i);
        printf("pass:%s\t\n", u[i].pass);
        gotoxy(24, j+2+i);
        printf("role:%s\t\t\n", u[i].role);
        gotoxy(24, j+3+i);
        printf("route:%s\t\n", u[i].route);
        /*printf("frds: %d", u[i].frds);
        if(u[i].frds>0)
        {
            printf("\n");
            printf("flist: ");
            for(j=0; j<u[i].frds; j++)
            {
                printf("%d ", u[i].flist[j]);
            }
        }
        if(i!=n-1) printf("\n");*/
    }
    go_back(j);
    getchar();
}

void add_user()
{
    getData();
    gotoxy(24, 10);
    printf("                     ");
    gotoxy(55, 10);
    printf("ADD USER");
    gotoxy(24, 12);
    printf("                     ");
    gotoxy(24, 14);
    printf("                    ");
    gotoxy(24, 16);
    printf("                    ");
    gotoxy(24, 18);
    printf("                    ");
    //printf("nextind=%d", exi.nextind);
    int x;
    char uid[10], key[100], route[100];
    gotoxy(24, 12);
    printf("  Enter ID: ");
    scanf("%s", uid);
    gotoxy(24, 14);
    printf("  Enter Password: ");
    scanf("%s", key);

    gotoxy(24, 16);
    printf("  Routes Available:\n");
    gotoxy(24, 18);
    printf("  1. IIUC - Chawkbazar\n");
    gotoxy(24, 20);
    printf("  2. IIUC - Bahaddarhat\n");
    gotoxy(24, 22);
    printf("  Enter Your Route: ");
    scanf("%d", &x);
    strcpy(u[n].id, uid);
    strcpy(u[n].pass,key);
    strcpy(u[n].role, "user");
    if(x == 1)
    {
        strcpy(u[n].route, "Chawkbazar");
    }
    else if(x == 2)
    {
        strcpy(u[n].route, "Bahaddarhat");
    }
    n++;
    writeData();
    go_back(17);
}

int search_by_id()
{
    getData();
    char search_id[20];
    int searched_ind;
    scanf("%s", &search_id);

    int i=0;
    for(i=0; i<n; i++)
    {
        if(strcmp(search_id,u[i].id) == 0)
        {
            //printf("matched");
            searched_ind=i;
        }
    }
    return searched_ind;
}

void delete_user()
{
    int searched_ind;
    gotoxy(43, 14);
    searched_ind=search_by_id();
    //printf("%d", searched_ind);

    int i, j;

    for(j=searched_ind; j<n-1; j++)
    {
        strcpy(u[j].id, u[j+1].id);
        //printf("%s\n", arr[j].name);
        strcpy(u[j].pass, u[j+1].pass);
        //printf("%s\n", arr[j].pass);
        strcpy(u[j].role, u[j+1].role);
        //printf("%s\n", arr[j].mail);
        strcpy(u[j].route, u[j+1].route);
    }
    n--;
    writeData();
    adminPanel();
}

void update_user()
{
    int searched_ind;
    gotoxy(43, 16);
    searched_ind=search_by_id();
    //printf("%d", searched_ind);

    gotoxy(24, 10);
    printf("                     ");
    gotoxy(55, 10);
    printf("UPDATE USER");
    gotoxy(24, 12);
    printf("                     ");
    gotoxy(24, 14);
    printf("                    ");
    gotoxy(24, 16);
    printf("                              ");
    gotoxy(24, 18);
    printf("                    ");

    int x;
    char uid[10], key[100], route[100];
    //gotoxy(24, 8);printf("  Enter ID: ");
    //scanf("%s", uid);
    gotoxy(24, 12);
    printf("  Enter Password: ");
    scanf("%s", key);

    gotoxy(24, 14);
    printf("  Routes Available:\n");
    gotoxy(24, 16);
    printf("  1. IIUC - Chawkbazar\n");
    gotoxy(24, 18);
    printf("  2. IIUC - Bahaddarhat\n");
    gotoxy(24, 20);
    printf("  Enter Your Route: ");
    scanf("%d", &x);
    //strcpy(u[searched_ind].id, uid);
    strcpy(u[searched_ind].pass,key);
    strcpy(u[searched_ind].role, "user");
    if(x == 1)
    {
        strcpy(u[searched_ind].route, "Chawkbazar");
    }
    else if(x == 2)
    {
        strcpy(u[searched_ind].route, "Bahaddarhat");
    }
    writeData();
    go_back(15);
}

void adminPanel()
{
    system("cls");
    logo();
    int q;
    gotoxy(24, 10);
    printf("1. VIEW USERS");
    gotoxy(24, 12);
    printf("2. ADD USER");
    gotoxy(24, 14);
    printf("3. DELETE USER(ID): ");
    gotoxy(24, 16);
    printf("4. UPDATE USER(ID): ");
    gotoxy(24, 18);
    printf("Enter Number: ");
    scanf("%d", &q);
    if(q==1) view_user();
    if(q==2) add_user();
    if(q==3) delete_user();
    if(q==4) update_user();
}

int main()
{
    system("cls");
    int q;
    getData();
    logo();
    gotoxy(50, 10);
    printf("  1. Login\n");
    gotoxy(50, 12);
    printf("  2. Register\n");
    gotoxy(50, 14);
    printf("  Enter Number: ");
    scanf("%d", &q);

    switch(q)
    {
    case(1):
        login();
        break;
    case(2):
        signup();
        writeData();
        system("cls");
        login();
        break;
    default:
        printf("Enter the correct number.");
    }
    //homepage();
    //adminPanel();
    getchar();
}
