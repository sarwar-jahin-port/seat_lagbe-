#include<stdio.h>
#include<string.h>
#include<process.h>
#include<windows.h>
#include<time.h>


/// This function used to put cursor in different co-ordinates in console.
void gotoxy(int x, int y)
{
    COORD c; ///COORD is a structure to hold screen COORDinates X and Y.
    c.X=x;
    c.Y=y;
    /// SetConsoleCursorPosition function sets the cursor position in the console screen buffer.
    /// The GetStdHandle() function gives us a mechanism for retrieving(get something from somewhere) the standard input
    /// STD_OUTPUT_HANDLE is the standard output device. Initially, this is the active console screen buffer
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);     //1. HANDLE 2. COORD
}

struct User
{
    char id[20], pass[100], route[100], role[10];
};
struct User u[100];
struct c_user{
    char c_id[20], c_pass[100], route[100], role[10], c_seat[2][4];
    int c_seat_no;
};
struct c_user cu_user;

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


int n; //global variable for count users from userDB.txt file
int current; // global variable for showing data on 'my profile' for particular user1
char seatArray[50][4];
//using this for password encryption
//char key[70] = "PgEfTYaWGHjDAmxQqFLRpCJBownyUKZXkbvzIdshurMilNSVOtec#@_!=.+-*/";
//char org[70] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int hour, min, sec; // globar variable for storing time (hour, minute, second)

void c_time()
{
    //while(1){
    time_t s = time(NULL);
    struct tm* cur_time;
    cur_time= localtime(&s);
    gotoxy(94, 10);
    printf("Time: %02d:%02d:%02d", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
    // }
    hour = cur_time->tm_hour;
    min = cur_time->tm_min;
    sec = cur_time->tm_sec;
}


void towardsVarsity()
{
    int seat_available; //value of seat_available 1 means towards varsity and 2 means from varsity

    FILE *to = fopen("to_varsity_seat.txt", "r");
    for(int a=0; fscanf(to, "%s", seatArray[a])!=-1; a++)
    {
    }
    fclose(to);

    FILE *fp = fopen("Bus information.txt","r");
    fscanf(fp, "%d", &seat_available);
    fclose(fp);

    if(seat_available != 1)
    {
        FILE *fp = fopen("Bus information.txt","w");
        fprintf(fp, "%d\n", 1);
        fprintf(fp, "%d\n", 0);
        fclose(fp);
    }

}


//This function is used for Operating Menu by upper and lower key
// It improves user experience
void menuArrow(int realPosition, int arrowPosition)
{
    if(realPosition == arrowPosition)
    {
        printf(" ==>> - ");
    }
    else
    {
        printf("        ");
    }
}
/// Logo for app.
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
/// This function reads user informations(id, pass, role, route) from file(userdb.txt).
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
    n=i; ///global variable declared above. Used to count total users.
    fclose(fp);
}
/// Login function. User type there username & pass correctly to log into there account.
void login()
{
    system("cls");
    logo();
    char u_id[100], password[100], ch;
    int checkingIfUserfound = 0, index=0;
    gotoxy(50, 10);
    printf("  LOGIN\t\t");
    gotoxy(50, 12);
    printf("\t\t");
    gotoxy(50, 14);
    printf("\t\t\t");
    gotoxy(50, 12);
    printf("  Enter ID: ");
    scanf("%s", u_id);
    gotoxy(50, 14);
    printf("  Enter Password: ");
    /* 13 is ASCII value of Enter key */
    while((ch = getch()) != 13)
    {
        if(index < 0) index = 0;
        /* 8 is ASCII value of BACKSPACE character */
        if(ch == 8)
        {
            putch('\b');
            putch(' ');
            putch('\b');
            index--;
            continue;
        }
        password[index++] = ch;
        putch('*');
    }
    password[index] = '\0';
    /// the below loop will continue upto total user number in userDB.txt file
    for(int i = 0; i<n; i++)
    {
        if(strcmp(u_id,u[i].id) == 0 && strcmp(password, u[i].pass) == 0)
        {
            current = i; /// here current represents the logged in user index number in userDB.txt file.
            checkingIfUserfound = 1;
            if(strcmp("admin",u[i].role) == 0)
            {
                adminPanel();
                break;
            }
            else
            {
                homepage();
                break;
            }
        }
    }

    if(checkingIfUserfound == 0)
    {
        gotoxy(52, 16);
        printf("Wrong Username or Password entered.");
        sleep(1);
        login();
    }
}
/// signup function used to register new users to the app. And there data stores in userDB.txt file.
void signup()
{
    system("cls");
    logo();
    int x;
    char uid[10], key[100], route[100];
    gotoxy(50, 10);
    printf("  REGISTER\t\t");
    gotoxy(50, 12);
    printf("               ");
    gotoxy(50, 14);
    printf("                   ");
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

    /// Here u is a user structure array which has datatypes(id, pass, route, role);
    strcpy(u[n].id, uid); /// n(global variable) is new user index number.
    strcpy(u[n].pass,key);
    strcpy(u[n].role, "user");
    if(x == 1) strcpy(u[n].route, "Chawkbazar");
    else if(x == 2) strcpy(u[n].route, "Bahaddarhat");

    n++;
    writeData();
    gotoxy(50, 24);
    printf("Your signup is successfully done!");
    sleep(1);
    login();
}
/// stores all data from struct user u[100] to userDB.txt file.
void writeData()
{
    FILE *fr = fopen("userDB.txt", "w");
    /// below loop is used to put data in userDB.txt file.
    for(int i = 0; i<n; i++)
    {
        fprintf(fr, "%s\n", u[i].id);
        fprintf(fr, "%s\n", u[i].pass);
        fprintf(fr, "%s\n", u[i].role);
        fprintf(fr, "%s\n", u[i].route);
    }
    fclose(fr);
}
/// adminpanel function is the homepage for admin users. This function used to -
/// 1. view all users data except passwords.
/// 2. can add new users to the app.
/// 3. delete and update user data.
/// 4. manage bus schedule & bus related other functionalities.
void adminPanel()
{
    system("cls");
    logo();
    int q;
    int a_position = 1, keyPressed = 0;

    // 13 is the ASCII value of Enter KEY
    while(keyPressed != 13)
    {
        //system("cls");
        gotoxy(24, 10);
        menuArrow(1,a_position);
        printf("1. VIEW USERS\n");
        gotoxy(24, 12);
        menuArrow(2,a_position);
        printf("2. ADD USER\n");
        gotoxy(24, 14);
        menuArrow(3,a_position);
        printf("3. DELETE USER(ID): ");
        gotoxy(24, 16);
        menuArrow(4,a_position);
        printf("4. UPDATE USER(ID): ");
        gotoxy(24, 18);
        menuArrow(5,a_position);
        printf("5. LOG OUT ");

        keyPressed = getch();
        if(keyPressed == 80 && a_position != 5) a_position++;
        else if(keyPressed == 72 && a_position != 1) a_position--;
        else a_position = a_position;
        printf("\e[?25l"); /// used to hide cursor in console
    }

    switch(a_position)
    {
    case(1):
        view_user();
        break;
    case(2):
        add_user();
        break;
    case(3):
        printf("\e[?25h"); /// used to show hidden cursor in console.
        delete_user();
        break;
    case(4):
        printf("\e[?25h"); /// used to show hidden cursor in console.
        update_user();
        break;
    case(5):
        main();
    default:
        printf("SYSTEM ERROR!");
    }

}
/// view_user() used to print all users data from userDB.txt file
void view_user()
{
    getData();
    int i, j;
    for(i=1, j=9; i<n; i++, j+=3)
    {
        gotoxy(74, j+i);
        printf("ID:%s\t\t\n", u[i].id);
        gotoxy(74, j+1+i);
        printf("ROLE:%s\t\t\n", u[i].role);
        gotoxy(74, j+2+i);
        printf("ROUTE:%s\t\n\n", u[i].route);
    }
    go_back(j);
    getchar();
}
/// add_user used for add new users in userDB.txt file
void add_user()
{
    getData();
    gotoxy(24, 10);
    printf("                             ");
    gotoxy(55, 10);
    printf("ADD USER");
    gotoxy(24, 12);
    printf("                             ");
    gotoxy(24, 14);
    printf("                             ");
    gotoxy(24, 16);
    printf("                             ");
    gotoxy(24, 18);
    printf("                             ");
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
void go_back_user(int j)
{
    gotoxy(24, j+8);
    printf("Press 0 to Return ");
    int q = getch();
    if(q==48) homepage();
    else go_back_user(j);
}

void go_back(int j)
{

    gotoxy(24, j+7);
    printf("Press 0 to return ");
    int q = getch();
    if(q==48) adminPanel();
    else go_back(j);
}

void Myprofile(int r)
{
    int seat_no=0, s1_found=-1, s2_found=-1;
    char seat1[30],seat2[30];
    getData();
    gotoxy(24, 10);
    printf("                     ");
    gotoxy(55, 12);
    printf("                          ");
    gotoxy(24, 12);
    printf("                            ");
    gotoxy(24, 14);
    printf("                            ");
    gotoxy(24, 16);
    printf("                            ");
    gotoxy(24, 18);
    printf("                     ");
    gotoxy(24, 20);
    printf("                    ");
    gotoxy(24, 10);
    printf("My ID: %s\n", u[current].id);
    gotoxy(24, 12);
    printf("Password: %s\n", u[current].pass);
    gotoxy(24, 14);
    printf("Role: %s\n", u[current].role);
    gotoxy(24, 16);
    printf("Route: %s\n", u[current].route);
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
        cu_user.c_seat_no=seat[i].seat_no;
        for(int j=0; j<seat[i].seat_no; j++)
        {
            fscanf(fp, "%s",seat[i].seat_name[j]);
        }
    }
    //printf("%d", i);
    fclose(fp);

    if(s1_found != -1)
    {
        strcpy(cu_user.c_seat[0], seat1);
        gotoxy(24, 14);
        printf("Booked Seat: %s",seat1);
        if(s2_found != -1) {printf(" %s",seat2); strcpy(cu_user.c_seat[1], seat2);}
    }
    if(r!=0) go_back_user(12);
    //getchar();
}

void delete_seat(char seatToDelete[], int seat_available)
{
    int i;
    if(seat_available == 2)
    {
        FILE *af=fopen("seat_info.txt", "r");

        for(i = 0; fscanf(af, "%s", num[i].seat) != -1; i++)
        {
        }
        fclose(af);
    }
    if(seat_available == 1)
    {
        FILE *af=fopen("to_varsity_seat.txt", "r");
        for(i = 0; fscanf(af, "%s", num[i].seat) != -1; i++)
        {
        }
        fclose(af);
    }

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
        if(seat_available == 1)
        {
            FILE *af = fopen("to_varsity_seat.txt", "w");
            for(int u = 0; u<i; u++)
            {
                fprintf(af, "%s\n", num[u].seat);
            }
            fclose(af);
        }
        if(seat_available == 2)
        {
            FILE *af = fopen("seat_info.txt", "w");
            for(int u = 0; u<i; u++)
            {
                fprintf(af, "%s\n", num[u].seat);
            }
            fclose(af);
        }
    }

}


void book_seat()
{
    system("cls");
    int a_position = 1, keyPressed = 0;
    getData();
    logo();
    int seat_available, seat_booked, user_input;

    if(hour >= 13 && min >= 0)
    {
        towardsVarsity();
        gotoxy(45,10);
        printf("SEAT BOOKING FOR TOWARDS VARSITY");
    }

    if(hour >= 9 && min >= 0 && hour < 13)
    {
        FILE *af=fopen("seat_info.txt", "r");
        for(int a=0; fscanf(af, "%s", seatArray[a])!=-1; a++)
        {
        }
        fclose(af);

        FILE *fp = fopen("Bus information.txt","r");
        fscanf(fp, "%d", &seat_available);
        fclose(fp);
        gotoxy(45,10);
        printf("SEAT BOOKING FOR FROM VARSITY");
        if(seat_available != 2)
        {
            FILE *fp = fopen("Bus information.txt","w");
            fprintf(fp, "%d\n", 2);
            fprintf(fp, "%d\n", 0);
            fclose(fp);
        }
    }

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

    FILE *fp = fopen("Bus information.txt","r");
    fscanf(fp, "%d", &seat_available); // checks if the value is 1 or 2
    fscanf(fp, "%d", &seat_booked);
    int i=0;
    for(i = 0; fscanf(fp, "%s", seat[i].uid)!=-1; i++)
    {
        if((strcmp(seat[i].uid, u[current].id))==0)
        {
            printf("YOU ALREADY BOOKED SEAT");
            go_back_user(10);
        }
        fscanf(fp, "%d", &seat[i].seat_no);
        for(int j=0; j<seat[i].seat_no; j++)
        {
            fscanf(fp, "%s",seat[i].seat_name[j]);
        }
    }

    fclose(fp);

    // 13 is the ASCII value of Enter KEY
    while(keyPressed != 13)
    {
        //system("cls");
        gotoxy(45,12);
        printf("SELECT NUMBER OF SEATS -");
        gotoxy(45,14);
        menuArrow(1,a_position);
        printf("1.ONE SEAT");
        gotoxy(45, 16);
        menuArrow(2,a_position);
        printf("2.TWO SEAT");


        keyPressed = getch();

        if(keyPressed == 80 && a_position != 2)
        {
            a_position++;
        }
        else if(keyPressed == 72 && a_position != 1)
        {
            a_position--;
        }
        else
        {
            a_position = a_position;
        }
    }

    FILE *fr = fopen("Bus information.txt","w");
    if(a_position == 1)
    {
        strcpy(seat[i].uid,u[current].id);
        seat[i].seat_no=1;
        strcpy(seat[i].seat_name, seatArray[0]);
        seat_booked++;

        gotoxy(40, 16);
        printf("SEAT NUMBER- %s BOOKED SUCCESSFULLY", seat[i].seat_name);
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
                    delete_seat(seat[y].seat_name[0], seat_available);
                    fprintf(fr, "%s\n", seat[y].seat_name[0]);


                }
                if(seat[x].seat_no==2)
                {
                    delete_seat(seat[y].seat_name[0], seat_available);
                    fprintf(fr, "%s ", seat[y].seat_name[0]);
                    fprintf(fr, "%s\n", seat[y].seat_name[1]);
                }

            }
        }
    }
    else if(a_position == 2)
    {
        //printf("%s", u[current].id);
        strcpy(seat[i].uid,u[current].id);
        //printf("%s", seat[i].uid);
        seat[i].seat_no=2;
        strcpy(seat[i].seat_name[0], seatArray[0]);
        strcpy(seat[i].seat_name[1], seatArray[1]);
        seat_booked+=2;

        gotoxy(40, 16);
        printf("SEAT NUMBER- %s %s BOOKED SUCCESSFULLY", seat[i].seat_name[0],seat[i].seat_name[1]);

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
                    delete_seat(seat[y].seat_name[0], seat_available);
                    fprintf(fr, "%s\n", seat[y].seat_name[0]);
                }
                if(seat[x].seat_no==2)
                {
                    fprintf(fr, "%s", seat[y].seat_name[0]);
                    fprintf(fr, " %s\n", seat[y].seat_name[1]);

                    delete_seat(seat[y].seat_name[0], seat_available);
                    delete_seat(seat[y].seat_name[1], seat_available);
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

                seat_booked--;

                fprintf(fr,"%d\n", seat_available);
                fprintf(fr, "%d\n", seat_booked);

                for(int m = 0; m<i; m++)
                {
                    fprintf(fr, "%s\n", seat[m].uid);
                    fprintf(fr, "%d\n", seat[m].seat_no);

                    if(seat[m].seat_no == 1)
                    {
                        for(int y=m; y<m+1 ; y++)
                        {
                            fprintf(fr, "%s\n", seat[y].seat_name[0]);
                        }
                    }
                    if(seat[m].seat_no == 2)
                    {
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

                seat_booked--;

                fprintf(fr,"%d\n", seat_available);
                fprintf(fr, "%d\n", seat_booked);

                for(int m = 0; m<i; m++)
                {
                    fprintf(fr, "%s\n", seat[m].uid);
                    fprintf(fr, "%d\n", seat[m].seat_no);
                    if(seat[m].seat_no == 1)
                    {
                        for(int y=m; y<m+1 ; y++)
                        {
                            fprintf(fr, "%s\n", seat[y].seat_name[0]);
                        }
                    }
                    if(seat[m].seat_no == 2)
                    {
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
    printf("                           ");
    gotoxy(24, 12);
    printf("                           ");
    gotoxy(24, 14);
    printf("                           ");
    gotoxy(24, 16);
    printf("                    ");
    gotoxy(24, 18);
    printf("                    ");
    char confirm;
    gotoxy(24, 10);
    printf("Enter (X) to Cancel!");
    gotoxy(24, 12);
    scanf(" %c",&confirm);
    //printf("%c", confirm);
    if(confirm==88 || confirm==120)
    {
        seat_cancel();
        homepage();
    }
    else
    {
        gotoxy(24, 12);
        printf("Enter Correctly.\n");
        sleep(1);
        Cancelseat();
    }
    go_back_user(6);
}

void credits()
{
    system("cls");
    logo();

    gotoxy(45,10);
    printf("==:DEVELOPED BY:==");
    gotoxy(45,12);
    printf("   SARWAR JAHIN");
    gotoxy(45,13);
    printf("     C223143");
    gotoxy(45,15);
    printf("  SHAHARIAR RIJON");
    gotoxy(45,16);
    printf("     C223155");
    gotoxy(45,18);
    printf("   ANAYET ULLAH");
    gotoxy(45,19);
    printf("     C2231xx");
    gotoxy(45,21);
    printf("    MAINUR RAHAT");
    gotoxy(45,22);
    printf("     C2231xx");

    go_back_user(16);
}

void homepage()
{
    cu_user.c_seat_no=0;
    Myprofile(0);
    system("cls");
    //gotoxy(94, 10);
    logo();
    c_time();
    int i, j;
    for(int i=12; i<22; i++)
    {
        gotoxy(90, i);
        printf("|XX");
        gotoxy(93, i);
        printf("|");

        gotoxy(94, i);
        printf("|XX");
        gotoxy(97, i);
        printf("|");
    }

    for(int i=12; i<22; i++)
    {
        gotoxy(101, i);
        printf("|XX");
        gotoxy(104, i);
        printf("|");

        gotoxy(105, i);
        printf("|XX");
        gotoxy(108, i);
        printf("|");
    }
    int x, y, n;

    for(n=0;n<cu_user.c_seat_no;n++)
    {
        if(cu_user.c_seat[n][1]=='A') x=91;
        if(cu_user.c_seat[n][1]=='B') x=95;
        if(cu_user.c_seat[n][1]=='C') x=102;
        if(cu_user.c_seat[n][1]=='D') x=106;
        y = cu_user.c_seat[n][0] - 37;
        gotoxy(x, y);
        printf("%s", cu_user.c_seat[n]);
    }

    //printf("%d %d", x, y);
    int a_position = 1, keyPressed = 0;

    // 13 is the ASCII value of Enter KEY

    while(keyPressed != 13)
    {
        gotoxy(24, 10);
        menuArrow(1,a_position);
        printf("1. MY PROFILE");
        gotoxy(24, 12);
        menuArrow(2,a_position);
        printf("2. BOOK YOUR SEAT");
        gotoxy(24, 14);
        menuArrow(3,a_position);
        printf("3. CANCEL YOUR SEAT");
        gotoxy(24, 16);
        menuArrow(4,a_position);
        printf("4. CREDITS");
        gotoxy(24, 18);
        menuArrow(5,a_position);
        printf("5. LOG OUT");
        gotoxy(24,20);
        keyPressed = getch();

        if(keyPressed == 80 && a_position != 5)
        {
            a_position++;
        }
        else if(keyPressed == 72 && a_position != 1)
        {
            a_position--;
        }
        else
        {
            a_position = a_position;
        }
    }
    c_time();
    if(a_position==1) Myprofile(1);
    if(a_position==2) book_seat();
    if(a_position==3) Cancelseat();
    if(a_position==4) credits();
    if(a_position==5) main();

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
    gotoxy(51, 14);
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
    gotoxy(51, 16);
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

/// Initiate page of the app. Users can register or login from here.
int main()
{
    system("cls");
    printf("\e[?25l"); /// used to hide cursor in console
    getData();
    logo();
    int a_position = 1, keyPressed = 0;

    // 13 is the ASCII value of Enter KEY
    while(keyPressed != 13)
    {
        //system("cls");
        gotoxy(45, 10);
        menuArrow(1,a_position);
        printf("1. LOGIN\n");
        gotoxy(45, 12);
        menuArrow(2,a_position);
        printf("2. REGISTER\n");

        keyPressed = getch();
        if(keyPressed == 80 && a_position != 2) a_position++;
        else if(keyPressed == 72 && a_position != 1) a_position--;
        else a_position = a_position;
    }
    switch(a_position)
    {
    case(1):
        login();
        break;
    case(2):
        signup();
        break;
    default:
        printf("SYSTEM ERROR!");
    }
    getchar();
}
