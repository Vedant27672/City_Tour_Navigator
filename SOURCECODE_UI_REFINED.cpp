#include <iostream>
#include <cstring>
#include <conio.h> // Added to define getch()
using namespace std;

// ANSI color codes for terminal UI enhancement
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// Utility function to print centered text with optional color
void printCentered(const string &message, const char* color = RESET)
{
    int width = 78;
    int len = message.length();
    int padding = (width - len) / 2;
    for (int i = 0; i < padding; i++)
        cout << " ";
    cout << color << message << RESET << endl;
}

// Utility function to print a separator line
void printSeparator(char ch = '-', int length = 78)
{
    for (int i = 0; i < length; i++)
        cout << ch;
    cout << endl;
}

void printMessageCenter(const char *message)
{
    int len = 0;
    int pos = 0;
    len = (78 - strlen(message)) / 2;

    for (pos = 0; pos < len; pos++)
    {
        cout << " ";
    }

    cout << BOLD << CYAN << message << RESET << endl;
    cout << "\nDate: " << __DATE__ << "\t\t\t\t\t     Time: " << __TIME__;
    cout << "\n\n\t\t       1. PRATEEK KUMAR   - B2 - 22103052";
    cout << "\n\n\t\t       2. VEDANT SINGH    - B2 - 22103058";
    cout << "\n\n\t\t       3. SHIVAM SINGH    - B2 - 22103031";
}

void printMessageCenter2(const char *message)
{
    int len = 0;
    int pos = 0;
    len = (78 - strlen(message)) / 2;

    for (pos = 0; pos < len; pos++)
    {
        cout << " ";
    }

    cout << BOLD << MAGENTA << message << RESET << endl;
}

void loadingpage()
{
    cout << BOLD << GREEN << "\t\t\tPLEASE WAIT\n" << RESET;
    cout << BOLD << GREEN << "\t\t\tSYSTEM IS LOADING\n" << RESET;
    cout << "\n\nPress any key to start now.....";
    getch();
}

void headMessage(const char *message)
{
    system("cls");
    printSeparator('=');
    cout << BOLD << BLUE;
    cout << "\n############                                                   ############\n";
    cout << "############        CITY TOUR NAVIGATION OPTIMISATION          ############\n";
    cout << "############             SYSTEM (PROJECT IN C++)               ############\n";
    cout << "############                                                   ############\n";
    cout << "###########################################################################\n";
    cout << "\n---------------------------------------------------------------------------\n";
    printMessageCenter(message);
    cout << "\n----------------------------------------------------------------------------\n\n" << RESET;
}
