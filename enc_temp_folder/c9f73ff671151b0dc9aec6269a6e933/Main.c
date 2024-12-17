#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <mysql.h>
struct Items {
    int price;
    char items[30][50];
};
struct Items beverage(int price) {
    int sop = price;
    int i;
    struct Items item;
    char ch;
    char items[30][50];
    int prices[] = { 170, 250, 280, 270, 290, 40, 180, 180, 300, 320, 310, 280, 310, 230 };
    char food[14][50] = {
        "COCO COLA",
        "FRENCH FRIES(NORMAL)",
        "FRENCH FRIES(CHEESE OVERLOAD)",
        "POPCORN(NORMAL)",
        "POPCORN(CHOCOLATE MASHUP)",
        "MINERAL WATER",
        "CAPPUCCINO",
        "CAFE LATTE 250 ML",
        "CHICKEN NUGGETS",
        "CHICKEN TIKKA PIZZA 25 CM",
        "CHICKEN TIKKA ROLL",
        "NACHOS LARGE 130GM",
        "PERI PERI CHICKEN BURGER",
        "CHICKEN SESAME DUMSUMS 5 PCS"
    };

    int count = 0;

    while (1) {
        printf("1. COCO COLA 170\n");
        printf("2. FRENCH FRIES(NORMAL) 250\n");
        printf("3. FRENCH FRIES(CHEESE OVERLOAD) 280\n");
        printf("4. POPCORN(NORMAL) 270\n");
        printf("5. POPCORN(CHOCOLATE MASHUP) 290\n");
        printf("6. MINERAL WATER 40\n");
        printf("7. CAPPUCCINO 180\n");
        printf("8. CAFE LATTE 250 ML 180\n");
        printf("9. CHICKEN NUGGETS 300\n");
        printf("10. CHICKEN TIKKA PIZZA 25 CM 320\n");
        printf("11. CHICKEN TIKKA ROLL 310\n");
        printf("12. NACHOS LARGE 130GM 280\n");
        printf("13. PERI PERI CHICKEN BURGER 310\n");
        printf("14. CHICKEN SESAME DUMSUMS 5 PCS 230\n");
        printf("15.Exit\n");
        printf("Enter Your Food Choice From Above: ");
        scanf("%d", &i);
        if (i <= 15 || i > 0)
        {
            sop += prices[i - 1];
            strcpy(item.items[count], food[i - 1]);
            strcpy(items[count], food[i - 1]);
            printf("Added \n");
            count++;
            printf("Do you want to continue? (y/n): ");
            scanf(" %c", &ch);
            if (ch == 'n' || ch == 'N') {
                break;
            }
        }
        else {
            printf("Invalid input");
        }
    }

    printf("Your items:\n");
    for (int j = 0; j < count; j++) {
        printf("%s\n", items[j]);
    }

    item.price = sop;
}

void Book(MYSQL* conn, const char* mov, const char* slot) {
    char seatschart[40][5] = { "a1","a2","a3","a4","a5","a6","a7","a8","a9","a10","b1","b2","b3","b4","b5","b6","b7","b8","b9","b10","c1","c2","c3","c4","c5","c6","c7","c8","c9","c10","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10" };
    int m;
    MYSQL_RES* res;
    MYSQL_ROW row;
    char query[256];
    char seats[41];
    int urseats[41];
    struct Items bill;
    int price = 0;
    char urseatsco = 0;
    char seatchoice[3];
    int seatchosen;
    while (1)
    {
        snprintf(query, sizeof(query), "SELECT seats FROM %s WHERE movie='%s'", slot, mov);
        if (mysql_query(conn, query)) {
            printf("Error querying database: %s\n", mysql_error(conn));
            return;
        }
        res = mysql_store_result(conn);
        seatchosen = -1;

        if (res) {
            row = mysql_fetch_row(res);
            if (row) {
                strcpy(seats, row[0]);
            }
            mysql_free_result(res);
        }
        else {
            printf("Error fetching result: %s\n", mysql_error(conn));
            return;
        }
        int c = 0;
        int c2 = 0;

        for (int j = 0;j < 4;j++) {
            for (int a = 0;a < 10;a++) {
                printf("     %s", seatschart[c2]);
                c2 += 1;
            }
            printf("\n");
            for (int g = 0;g < 10;g++) {
                if (seats[c] == '0') {
                    printf("    | |");
                }
                else if (seats[c] == '1') {
                    printf("    |\\|");
                }
                c += 1;
            }
            printf("\n");
        }
        printf("\n |  | Represent Empty Seats |\\| Represent  Booked Seats\n");
        printf("1: Choose Seats \n");
        printf("2: Buy\n");
        printf("3: Clear Selection\n");
        printf("4: Leave\n");
        printf("What Do You Want To Do ");
        scanf("%d", &m);
        if (m==1) {
           
            printf("\nEnter Your Seat From Above: ");
            scanf("%s", seatchoice);
            
            for (int g=0;g<40;g++) {
                if (strcmp(seatchoice, seatschart[g])==0) {
                    seatchosen=g;
                    break;
                }
            }
            if (seats[seatchosen]=='1') {
                printf("\n\nSorry This Seats Has Already Been Booked\n\n");
            }
            else {
                int f = 0;
                for (int g = 0;g < urseatsco;g++) {
                    if (urseats[g] == seatchosen) {
                        f = 1;
                    }
                }
                if (f == 0) {
                    char choice;
                    printf("\nDo You Want To Add This Seat Y/N\n");
                    getchar();
                    scanf("%c", &choice);
                    if (choice == 'Y' || choice =='y') {
                        printf("\nSelected\n");
                        urseats[urseatsco] = seatchosen;
                        urseatsco += 1;
                        price += 300;
                    }
                    else {
                        printf("Ok\n");
                    }
                }
                else {
                    printf("You Have Already Chosen This Seat\n");
                }
            }
        }
        else if (m == 2) {
            if (urseatsco != 0) {
                char refreshment_flag;
                printf("Do You Want Refreshments Y/N\n");
                getchar();
                scanf("%c", &refreshment_flag);

                if (refreshment_flag == 'Y') {
                    bill = beverage(price);
                    price += bill.price;


                }
                printf("Do You Want To Buy These Tickets For %d Y/N: ", price);
                char cont;
                getchar();
                scanf("%c", &cont);
                if (cont == 'Y') {
                    while (1) {
                        printf("Select A Payment Method\n");
                        printf("1: Pay At Theater\n");
                        printf("2: Online Transaction\n");
                        int choice;
                        printf(": ");
                        scanf("%d", &choice);
                        if (choice == 1) {
                            for (int i = 0; i < urseatsco; i++) {
                                seats[urseats[i]] = '1';
                            }
                            sprintf(query, "UPDATE %s SET seats='%s' WHERE movie='%s'", slot, seats, mov);
                            if (mysql_query(conn, query)) {
                                printf("Error uq    pdating database: %s\n", mysql_error(conn));
                            }
                            else {
                                printf("Seats Booked Successfully\n");
                                price = 0;
                                for (int i = 0; i < urseatsco; i++) {
                                    urseats[i] = -1;
                                }
                                urseatsco = 0;
                            }
                            break;
                        }
                        else {
                            printf("Our Services Are Currently Down, Please Select Other Methods\n");
                        }
                    }
                }
            }
            else {
                printf("\nYou Have Not Selected Any Seats\n");
            }
        }
        else if (m==3) {
            printf("Cleared\n");
            price = 0;
            for (int i = 0; i < urseatsco; i++) {
                urseats[i] = -1;
            }
            urseatsco = 0;
        }
        else if (m == 4) {
            break;
        }
    }
}
void createac(MYSQL* conn) {
    char name[100], p[20], un[50], query[256];
    printf("Enter Your Name: ");
    scanf(" %[^\n]", name);

    if (strlen(name) > 3 && strlen(name) < 30) {
        printf("Enter Your Password: ");
        scanf(" %[^\n]", p);

        if (strlen(p) > 3 && strlen(p) < 11) {
            printf("Enter Your User Id: ");
            scanf(" %[^\n]", un);

            for (int i = 0; un[i]; i++) un[i] = tolower(un[i]);

            sprintf(query, "SELECT user FROM users WHERE user='%s'", un);
            if (mysql_query(conn, query)) {
                printf("Error checking user ID: %s\n", mysql_error(conn));
                return;
            }
            MYSQL_RES* result = mysql_store_result(conn);
            if (result) {
                if (mysql_num_rows(result) > 0) {
                    printf("User ID is already being used\n");
                    mysql_free_result(result);
                    return;
                }
                mysql_free_result(result);
            }
            else {
                printf("Error retrieving result set: %s\n", mysql_error(conn));
                return;
            }

            if (strlen(un) > 4 && strlen(un) < 50) {
                sprintf(query, "INSERT INTO users (user, pass, name) VALUES('%s', '%s', '%s')", un, p, name);
                if (mysql_query(conn, query)) {
                    printf("Error inserting data: %s\n", mysql_error(conn));
                }
                else {
                    printf("\nAccount Has Been Successfully Created\n");
                    
                }
            }
            else {
                printf("\nUser ID must be between 5 and 50 characters\n");
            }
        }
        else {
            printf("Password should be between 4 to 10 characters\n");
        }
    }
    else {
        printf("\nName must be over 3 characters and below 30 characters\n");
    }
}
void nowShowing(MYSQL* conn) {
    char query[256];
    char movies[60][60];
    int slotchosen;
    char slots[3][50];
    int c = 0;
    int m;
    sprintf(query, "SELECT movie FROM movies");
    if (mysql_query(conn, query)) {
        printf("Error checking user ID: %s\n", mysql_error(conn));
        return;
    }
    MYSQL_RES* result = mysql_store_result(conn);
    if (result) {
        if (mysql_num_rows(result) > 0) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                strcpy(movies[c], row[0]);
                c += 1;
            }
                while (1) {
                    slotchosen = -1;
                    for (int g = 0;g < c;g++) {
                        printf("%d) %s\n", g, movies[g]);
                    }
                    
                    printf("Enter The Movie: ");
                    scanf("%d", &m);
                    sprintf(query, "SELECT slot1,slot2,slot3 FROM movies WHERE movie='%s'", movies[m]);
                    if (mysql_query(conn, query)) {
                        printf("Error checking user ID: %s\n", mysql_error(conn));
                        return;
                    }
                    MYSQL_RES* result = mysql_store_result(conn);
                    if (result) {;
                        if (mysql_num_rows(result) > 0) {
                            MYSQL_ROW row;
                            while ((row = mysql_fetch_row(result))) {
                                strcpy(slots[0],row[0]);
                                strcpy(slots[1], row[1]);
                                strcpy(slots[2], row[2]);
                            }
                            for (int g = 0;g < 3;g++) {
                                printf("%d) %s\n",g, slots[g]);
                            }
                            printf("Enter The Time Slot: ");
                            scanf("%d", &slotchosen);
                            if (slotchosen == 0) {
                                 Book(conn, movies[m], "Slot1");
                                 return;
                            }
                            else if (slotchosen == 1) {
                                Book(conn, movies[m], "Slot2");
                                return;
                            }
                            else if (slotchosen == 2) {
                                Book(conn, movies[m], "Slot3");
                                return;
                            }
                            else {
                                printf("Pls Enter A Valid Option\n");
                            }
                        }
                        else {
                            printf("Movie Not Found\n");
                        }
                        mysql_free_result(result);
                    }
                    else {
                        printf("Error retrieving result: %s\n", mysql_error(conn));
                        return;
                    }
                    if (m == c) {
                        break;
                    }
                    
                }
        }
        else {
            printf("There Are No Movies Currently Runnig");
        }
        mysql_free_result(result);
    }
    else {
        printf("Error retrieving result: %s\n", mysql_error(conn));
        return;
    }
    
}


void login(char un[100], MYSQL* conn) {
    int lm;
    while (1)
    {
        printf("1: Book Tickets\n");
        printf("2: Log Out\n");
        getchar();
        scanf("%d", &lm);
        if (lm == 1) {
            nowShowing(conn);

        }
        else if (lm == 2) {
            break;
        }
        else {
            printf("\nInvalid Entry\n");
            
        }
    }
}


void checklogin(MYSQL* conn) {
    char un[100];
    char pas[100];
    printf("Enter Your User-Name: ");
    scanf("%s", &un);
    printf("\nEnter Password: ");
    scanf("%s", &pas);
    char query[256];
    sprintf(query, "SELECT user,pass FROM users WHERE user='%s'", un);
    if (mysql_query(conn, query)) {
        printf("Error checking user ID: %s\n", mysql_error(conn));
        return;
    }
    MYSQL_RES* result = mysql_store_result(conn);
    if (result) {
        if (mysql_num_rows(result) > 0) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                if (strcmp(row[1], pas) == 0) {
                    login(row[0], conn);
                }
                else {
                    printf("Wrong Password\n");
                }
            }
        }
        else {
            printf("User Name Not Found");
        }
        mysql_free_result(result);
    }
    else {
        printf("Error retrieving result: %s\n", mysql_error(conn));
        return;
    }


}


void start(MYSQL* conn) {
    int m;
    while (1)
    {
        printf("AMC Booking\n");
        printf("1: Sign Up\n");
        printf("2: Login\n");
        printf("3: Quit\n");
        printf("Enter Mode: ");

        scanf("%d", &m);
        if (m == 1) {
           createac(conn);
        }
        else if (m == 2) {
            checklogin(conn);
        }
        else if (m == 3) {
            break;
        }
        else {
            printf("Invalid Entry\n");

        }
    }

}

int main() {
    MYSQL* conn = mysql_init(NULL);

    if (conn == NULL) {
        printf("mysql_init failed\n");
        return 1;
    }

    if (mysql_real_connect(conn, "localhost", "root", "abhinav2004@", "pvr", 0, NULL, 0) == NULL) {
        printf("mysql_real_connect failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    start(conn);
    printf("Thank You");
    mysql_close(conn);
    return 0;

}