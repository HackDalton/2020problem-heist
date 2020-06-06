#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define ANSI_BOLD "\x1b[1m"
#define ANSI_RESET "\x1b[0m"

#define PASSWORD_LENGTH 32
#define FLAG_LENGTH 43

struct data
{
    FILE *flagFile;
    char flag[FLAG_LENGTH];
    char correctPassword[PASSWORD_LENGTH];
    char enteredPassword[PASSWORD_LENGTH];
    int isValid;
};

static char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (size)
    {
        --size;
        for (size_t n = 0; n < size; n++)
        {
            int key = rand() % (int)(sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

struct data d;

int main()
{
    d.isValid = 0;

    d.flagFile = fopen("./flag.txt", "r");
    fscanf(d.flagFile, "%s", d.flag);

    rand_string(d.correctPassword, 15);

    printf(ANSI_BOLD "Welcome to the Royal Mint of Spain!\n" ANSI_RESET);
    printf("Enter the password (up to %d chars) to disarm the security system.\n", PASSWORD_LENGTH);
    fflush(stdout);
    gets(d.enteredPassword);

    if (strcmp(d.enteredPassword, d.correctPassword))
    {
        printf("Incorrect password.\n");
    }
    else
    {
        printf("Disarming Security System!\n");
        d.isValid = 1;
    }

    if (d.isValid)
    {
        printf("Security system disarmed.\n");
        printf("%s\n", d.flag);
    }

    return 0;
}