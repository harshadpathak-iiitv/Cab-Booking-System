#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define Speed 40
#define BIKE_RATES 10
#define AUTO_RATES 20
#define ECONOMY_RATES 30
#define PREMIUM_RATES 40
#define MAX_USERS 100

typedef struct data_in
{
    char username[50];
    char password[50];
} User;

// Global variables
User users[MAX_USERS];
int numUsers = 0;

typedef struct Coordinates
{
    int x;
    int y;
} Sectorselection;

typedef struct Drivers
{
    float net_availability;
    int auto1;
    int bike;
    int economyCabs;
    int premiumCabs;
    int brate;
    int condition2;
} data_check;

typedef struct availability
{
    // in
    int sector;
    // return
    int autoo;
    int bike;
    int ecocabs;
    int precabs;
    int net_availability;
} available;

typedef struct Calculations
{

    float distance;
    int time;
    int sector;
    int availabilty_time;
    float cost;
    int condition;

} data;

void display_secline();

void display(void);

void displayGrid(void);

void driver_coordinates();

available availability_(data tempppp);

data current_time();

int time_multiplier();

int randomizerx(int seed);

int randomizery(int seed);

Sectorselection coordinates(int sector);

float price_calculator(data dist, float distance, float dum_dum);

void display_nth_line(const char *filename, int n);

data distance_();

float speed_time(float distance);

float distance_calculator(int x1, int y1, int x2, int y2);

void view_availability();

int availability_multiplier(data dum);

void booking();

data_check baserate(data dum);

void driver_details();

void menu();

void registerUser();

int userMenu();

void readUsersFromFile();

void writeUsersToFile();

void display_line();

int main()
{
    int choice;
    int logIn = 0; // Flag to track login status

    // Load users from the file
    readUsersFromFile();

    printf("\n[ WELCOME TO OUR CAB BOOKING SERVICES ]\n");

    do
    {
        display_line();
        printf("Main Menu\n");
        display_line();

        if (!logIn) // Show only if the user is not logged in
        {

            printf("1. User Registration\n");
            printf("2. User Login\n");
        }

        if (logIn) // Show only if the user is logged in
        {
            // display();
            displayGrid();
            printf("\n1. Book a Preferred Cab\n");
            printf("2. View Available Cabs\n");
        }

        printf("3. Exit\n");
        display_line();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        display_line();

        if (!logIn && (choice == 1 || choice == 2 || choice == 3)) // Handle registration and login
        {
            switch (choice)
            {
            case 1:
                registerUser();
                break;
            case 2:
                logIn = userMenu(); // Update login status
                break;
            case 3:
                printf("Thank You for using our Cab Booking Services.\nHope you have a safe Journey :)\n");
                printf("Exiting...\n");
                display_line();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
        else if (choice == 1 || choice == 2 || choice == 3) // Handle logged-in user actions
        {
            switch (choice)
            {
            case 1:
                booking();
                break;
            case 2:
                view_availability();
                break;
            case 3:
                printf("Thank You for using our Cab Booking Services.\nHope you have a safe Journey :)\n");
                printf("Exiting...\n");
                display_line();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 3 && (choice == 1 || choice == 2 || choice == 3));

    return 0;
}

// gives the current time in hours
data current_time()
{
    data temp;
    time_t t = time(NULL);
    struct tm hour = *localtime(&t);
    temp.availabilty_time = hour.tm_hour;

    // printf("%d", hours);
    return temp;
}

// finds the time multiplier using current_time()
int time_multiplier()
{
    data temp2;
    temp2 = current_time();
    if (temp2.availabilty_time >= 22 && temp2.availabilty_time <= 23)
    {
        return 2;
    }
    if (temp2.availabilty_time >= 0 && temp2.availabilty_time <= 7)
    {
        return 2;
    }
    if (temp2.availabilty_time >= 17 && temp2.availabilty_time <= 20)
    {
        return 1.5;
    }
    else
    {
        return 1;
    }
}

// returns the distance and time
data distance_()
{
    Sectorselection ref1, ref2;
    int sectorin, sectorout;
    data deref;
    printf("ENTER YOUR LOCATION : ");
    scanf("%d", &sectorin);

    if (sectorin <= 16 && sectorin >= 1)
    {
        ref1 = coordinates(sectorin);
        deref.sector = sectorin;

        printf("ENTER DESTINATION : ");
        scanf("%d", &sectorout);
        display_line();
        if (sectorout < 17 && sectorout > 0)
        {
            ref2 = coordinates(sectorout);

            float distance;
            distance = distance_calculator(ref1.x, ref1.y, ref2.x, ref2.y);
            float time;
            distance = distance / 1000;
            time = speed_time(distance);
            deref.distance = distance;
            display_line();
            printf("Total Distance          : %.2f km\n", distance);
            printf("Total Time for Journey  : %.2f min\n", time);
            deref.condition = 0;
        }
    }
    else
    {
        printf("Invalid choice. Please try again.\n");
        deref.condition = 1;
    }
    return deref;
}

// finds the total time of travel using an average speed which is predifined
float speed_time(float distance)
{
    float time;
    time = (distance / Speed) * 100;
    return time;
}

// calculates distance to be travelled
float distance_calculator(int x1, int y1, int x2, int y2)
{

    float distance, x, y;
    distance = fabs(x2 - x1) + fabs(y2 - y1);
    return distance;
}

// randomizes x coordinate
int randomizerx(int seed)
{
    int random;
    random = ((seed + time(NULL) * 982) % 1000) + seed;
    return random;
}

// randomizes y coordinate
int randomizery(int seed)
{
    int random;
    random = ((seed + time(NULL) * 967) % 1000) + seed;
    return random;
}

// returns values according to the selected sectors
Sectorselection coordinates(int sector)
{
    Sectorselection crd;
    switch (sector)
    {
    case 1:
    case 2:
    case 3:
    case 4:
        crd.y = 0;
        crd.x = (sector - 1) * 1000;
        goto randomize;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        crd.y = 1000;
        crd.x = (sector - 5) * 1000;
        goto randomize;
        break;
    case 9:
    case 10:
    case 11:
    case 12:
        crd.y = 2000;
        crd.x = (sector - 9) * 1000;
        goto randomize;
        break;
    case 13:
    case 14:
    case 15:
    case 16:
        crd.y = 3000;
        crd.x = (sector - 13) * 1000;
        goto randomize;
        break;

    default:
        display_line();
        printf("Not a valid responce \n");
        break;
    }

randomize:
    crd.x = randomizerx(crd.x);
    crd.y = randomizery(crd.y);

    return crd;
}

// calculates the price
float price_calculator(data dum, float distance, float dum_dum)
{
    float cost;
    // base cell3;
    int cell;
    int cell2, cell3;
    cell = availability_multiplier(dum);
    cell2 = time_multiplier();
    cell3 = dum_dum; // base price
    cost = distance * cell * cell2 * cell3;
    return cost;
}

// reads nth line
void display_nth_line(const char *filename, int n)
{
    FILE *file = fopen(filename, "r");
    char line[256];
    int currentline = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (currentline == n)
        {
            printf("%s\n\n", line);
            fclose(file);
            return;
        }
        currentline++;
    }
    fclose(file);
}

// returns the availability in the area
available availability_(data tempppp)
{
    data neet = tempppp;
    int sector_;
    sector_ = neet.sector;
    available yeet;

    switch (sector_)
    {
    case 1:
        yeet.autoo = 3, yeet.bike = 5, yeet.ecocabs = 4, yeet.precabs = 7;
        break;
    case 2:
        yeet.autoo = 3, yeet.bike = 6, yeet.ecocabs = 9, yeet.precabs = 7;
        break;
    case 3:
        yeet.autoo = 2, yeet.bike = 6, yeet.ecocabs = 9, yeet.precabs = 1;
        break;
    case 4:
        yeet.autoo = 1, yeet.bike = 3, yeet.ecocabs = 8, yeet.precabs = 0;
        break;
    case 5:
        yeet.autoo = 4, yeet.bike = 5, yeet.ecocabs = 7, yeet.precabs = 11;
        break;
    case 6:
        yeet.autoo = 5, yeet.bike = 6, yeet.ecocabs = 14, yeet.precabs = 13;
        break;
    case 7:
        yeet.autoo = 5, yeet.bike = 6, yeet.ecocabs = 11, yeet.precabs = 6;
        break;
    case 8:
        yeet.autoo = 3, yeet.bike = 3, yeet.ecocabs = 10, yeet.precabs = 2;
        break;
    case 9:
        yeet.autoo = 3, yeet.bike = 4, yeet.ecocabs = 3, yeet.precabs = 8;
        break;
    case 10:
        yeet.autoo = 7, yeet.bike = 7, yeet.ecocabs = 9, yeet.precabs = 12;
        break;
    case 11:
        yeet.autoo = 7, yeet.bike = 8, yeet.ecocabs = 7, yeet.precabs = 11;
        break;
    case 12:
        yeet.autoo = 5, yeet.bike = 6, yeet.ecocabs = 7, yeet.precabs = 6;
        break;
    case 13:
        yeet.autoo = 3, yeet.bike = 2, yeet.ecocabs = 3, yeet.precabs = 5;
        break;
    case 14:
        yeet.autoo = 7, yeet.bike = 4, yeet.ecocabs = 7, yeet.precabs = 9;
        break;
    case 15:
        yeet.autoo = 7, yeet.bike = 6, yeet.ecocabs = 4, yeet.precabs = 10;
        break;
    case 16:
        yeet.autoo = 5, yeet.bike = 5, yeet.ecocabs = 4, yeet.precabs = 6;
        break;
    }
    yeet.net_availability = yeet.autoo + yeet.bike + yeet.ecocabs + yeet.precabs;

    return yeet;
}

// shows the availability in the area
void view_availability()
{
    available temp4;
    printf("Enter the Sector you wish to check availabilities of : ");
    int sector_to_view;
    scanf("%d", &sector_to_view);
    data dum;
    dum.sector = sector_to_view;
    temp4 = availability_(dum);
    if (sector_to_view >= 1 && sector_to_view <= 16)
    {
        printf("\nCurrent Availibility : \nBike         : %d \nAuto         : %d \nEconomy Cabs : %d \nPremium Cabs : %d\n", temp4.bike, temp4.autoo, temp4.ecocabs, temp4.precabs);
    }
    else
    {
        printf("Invalid choice. Please try again.\n");
    }
    display_line();
}

// gives a multiplier according to the availability for cost calculations
int availability_multiplier(data dum)
{
    available yemp;
    yemp = availability_(dum);
    if (yemp.net_availability < 4)
    {
        return 3;
    }
    else if (yemp.net_availability >= 4 && yemp.net_availability <= 8)
    {
        return 2;
    }
    else
    {
        return (int)1;
    }
}

// books a cab
void booking()
{
    float dummy;
    data_check dum_dum;
    data dum;
    dum = distance_();
    if (dum.condition == 0 || dum.condition != 1)
    {
        if (dum_dum.condition2 == 1 || dum_dum.condition2 != 0)
        {
            dum_dum = baserate(dum);

            dummy = price_calculator(dum, dum.distance, dum_dum.brate);

            printf("\nTotal Cost of Journey: %.2f Rs\n\n", dummy);

            printf("Your driver details are : \n");
            display_line();

            driver_details(dum_dum);

            driver_coordinates();
            display_line();
        }
    }
    else
    {
        printf("Invalid choice. Please try again.\n");
    }
}

// defines base rate according to the selection of ride
data_check baserate(data dum)
{

    data_check ref;
    available temp1;
    int n, base_rate = 0;
    temp1 = availability_(dum);
    printf("Select your Ride : \n");
    display_line();

    if (temp1.bike != 0)
    {
        printf("\t1. Bike                 Availability : %d\n", temp1.bike);
    }
    if (temp1.autoo != 0)
    {
        printf("\t2. Auto                 Availability : %d\n", temp1.autoo);
    }
    if (temp1.ecocabs != 0)
    {
        printf("\t3. Economy Cab          Availability : %d\n", temp1.ecocabs);
    }
    if (temp1.precabs != 0)
    {
        printf("\t4. Premium Cab          Availability : %d\n", temp1.precabs);
    }
    scanf("%d", &n);
    if (n == 1 && temp1.bike != 0)
    {
        base_rate = BIKE_RATES;
        temp1.bike--;
        ref.bike = 1;
        ref.condition2 = 1;
    }
    else if (n == 2 && temp1.autoo != 0)
    {
        base_rate = AUTO_RATES;
        temp1.autoo--;
        ref.auto1 = 1;
        ref.condition2 = 1;
    }
    else if (n == 3 && temp1.ecocabs != 0)
    {
        base_rate = ECONOMY_RATES;
        temp1.ecocabs--;
        ref.condition2 = 1;
        ref.economyCabs = 1;
    }
    else if (n == 4 && temp1.precabs != 0)
    {
        base_rate = PREMIUM_RATES;
        temp1.precabs--;
        ref.condition2 = 1;
        ref.premiumCabs = 1;
    }
    else
    {
        display_line();
        printf("Invalid Responce \n");
        ref.condition2 = 0;
    }
    ref.brate = base_rate;
    return ref;
}

// gives the details of the driver according to the selection
void driver_details(data_check ref2)
{

    int x = randomizerx(x);
    x = (x % 10) + 1;

    if (ref2.bike == 1)
    {
        const char *bikefile = "bikedrivers.txt";
        return display_nth_line(bikefile, x);
    }
    if (ref2.auto1 == 1)
    {
        const char *autofile = "autodrivers.txt";
        return display_nth_line(autofile, x);
    }
    if (ref2.economyCabs == 1)
    {
        const char *ecofile = "economydrivers.txt";
        return display_nth_line(ecofile, x);
    }
    if (ref2.premiumCabs == 1)
    {
        const char *premiumfile = "premiumdrivers.txt";
        return display_nth_line(premiumfile, x);
    }
}

// driver coordinates
void driver_coordinates()
{
    int x1, y1, x2, y2;
    x2 = randomizerx(1000);
    y2 = randomizery(1000);
    // printf("%d %d\n", x2, y2);
    float distance;
    distance = x2 + y2;
    float time;
    time = speed_time(distance);
    time = time / 1000;

    printf("Your ride shall arrive in %.2f mins\n", time);
    // return time;
}

void display_secline()
{
    // display
    for (int i = 1; i <= 4; i++)
    {
        printf(" _____ ");
    }
}

void menu()
{
    int choice;
    do
    {
        printf("Main Menu\n");
        display_line();

        printf("1. User Registration\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        display_line();

        printf("Enter your choice: ");
        scanf("%d", &choice);
        display_line();

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            userMenu();
            break;
        case 3:
            printf("Exiting...\n");
            display_line();
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3 && (choice == 1 || choice == 2 || choice == 3));
}

// Function to register a new user
void registerUser()
{
    if (numUsers < MAX_USERS)
    {
        printf("-: User Registration :- \n");
        // display_line();

        printf("\nEnter username: ");
        scanf("%s", users[numUsers].username);
        printf("Enter password: ");
        scanf("%s", users[numUsers].password);
        // display_line();

        numUsers++; // Increment the number of registered users
        printf("User registered successfully!\n");
        display_line();
        writeUsersToFile();
    }
    else
    {
        printf("Maximum user registrations reached. Cannot register more users.\n");
    }
}

// User menu function
int userMenu()
{
    char username[50], password[50];
    printf("-: User Login :-\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Validate user credentials
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            printf("Valid credentials. Access granted.\n");
            display_line();
            return 1; // Login successful
        }
    }

    printf("Invalid credentials. Access denied.\n");
    return 0; // Login failed
}

// Function to read users' data from file
void readUsersFromFile()
{
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening users file for reading.\n");
        return;
    }

    while (fscanf(fp, "%s %s", users[numUsers].username, users[numUsers].password) != EOF)
    {
        numUsers++;
        if (numUsers >= MAX_USERS)
        {
            break;
        }
    }
    fclose(fp);
}

// Function to write users' data to file
void writeUsersToFile()
{
    FILE *fp = fopen("users.txt", "a");
    for (int i = 0; i < numUsers; i++)
    {
        fprintf(fp, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(fp);
}

void display_line()
{
    printf("--------------------------------------------------------------------------------------------------\n");
}

void displayGrid()
{
    int rows = 4, cols = 4;
    int sector = 1; // Sector counter

    // printf("\n     Gandhinagar\n\n");
    printf(" ----- ----- ----- -----\n");

    for (int i = 0; i < rows; i++)
    {
        // Print each row
        for (int j = 0; j < cols; j++)
        {
            printf("| S%02d ", sector); // %2d ensures proper alignment
            sector++;
        }
        printf("|\n"); // End the row

        // Print a horizontal separator
        for (int j = 0; j < cols; j++)
        {
            printf(" -----");
        }
        printf("\n");
    }
}

void display(void)
{ // display
    display_secline();
    printf("\n");

    for (int i = 1; i <= 4; i++)
    {
        printf("| S%02d |", i);
    }
    printf("\n");
    display_secline();
    printf("\n");

    display_secline();
    printf("\n");

    for (int i = 5; i <= 8; i++)
    {
        printf("| S%02d |", i);
    }
    printf("\n");
    display_secline();
    printf("\n");

    display_secline();
    printf("\n");

    for (int i = 9; i <= 12; i++)
    {
        printf("| S%02d |", i);
    }
    printf("\n");
    display_secline();
    printf("\n");

    display_secline();
    printf("\n");

    for (int i = 13; i <= 16; i++)
    {
        printf("| S%02d |", i);
    }
    printf("\n");

    display_secline();
    printf("\n");
}
