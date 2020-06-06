# HackDalton: Heist (Writeup)

> Warning! There are spoilers ahead

If we look at the main.c file, we can see some interesting issues. First of all, the data is all stored in a `data` struct:

```c
struct data
{
    FILE *flagFile;
    char flag[FLAG_LENGTH];
    char correctPassword[PASSWORD_LENGTH];
    char enteredPassword[PASSWORD_LENGTH];
    int isValid;
};
```

If you look at the enteredPassword string, you can see that it is immediatly before the isValid int. That means that the computer will store the enteredPassword string right before the isValid int in memory.

We can see that the isValid int is used towards the end of the program:
```c
    if (d.isValid)
    {
        printf("Security system disarmed.\n");
        printf("%s\n", d.flag);
    }
```

These lines check to see if the isValid variable is a non-zero value, and if it is, prints the flag. We have to change isValid to a non-zero value.

One vunerability is in the collection of the password, on line 51.

```c
    gets(d.enteredPassword);
```
C's `gets` method (which is now deprecated due to it's unsafe nature) will read a value from stdin until a newline, regardless of it's length. This means that we can overflow the enteredPassword buffer and enter into the isValid value by typing something longer than PASSWORD_LENGTH, which is `32`. By typing a longer string, it enters the isValid int, and the if statement will return true.