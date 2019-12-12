/**
 * @file Source.c
 * @author Kornelijus Petronis
 * @brief 
 * @version 1.3
 * @date 2019-12-12
 * 
 * @copyright Copyright (c) 2019
 * 
 * 
 * <<<<# This program read bank customers list from csv file and create two new files #>>>>
 * 
 * First file is all clients sorted from smallest to biggest by bank balance and in the begin of list is number of clients.
 * 
 * Second file is only for one client what you searching.
 * 
 */

// Library list
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define fileName "data2.csv"
int sizeOfArray;
/**
 * @brief Structure
 * 
 */
struct personalData
{
    char address[100];
    long int phone;
    char birthday[20];
};
struct bank_custumers_details
{
    char name[20];
    char IBAN[30];
    double balance;
    struct personalData pData;
};

// Prototypes
void readFile(struct bank_custumers_details bank[sizeOfArray]);
int countRows();
void sortByBalance(struct bank_custumers_details bank[sizeOfArray]);
void writeToFileSorted(struct bank_custumers_details bank[sizeOfArray]);
void writeToFileOnly(struct bank_custumers_details bank[sizeOfArray]);

int main()
{
    sizeOfArray = countRows() + 1;

    struct bank_custumers_details bank[sizeOfArray];

    readFile(bank);

    sortByBalance(bank);

    writeToFileSorted(bank);

    writeToFileOnly(bank);

    for (int i = 2; i < sizeOfArray; i++)
    {
        // printf("%s\n", bank[i].IBAN);
        // printf("%.2lf | %s | %s | %s\n", bank[i].balance, bank[i].name, bank[i].pData.address, bank[i].IBAN);
    }

    return 0;
}
// ==============================================================================================
// ==============================================================================================
/**
 * @brief write to file only found clients.
 * 
 * @param bank 
 */
void writeToFileOnly(struct bank_custumers_details bank[sizeOfArray])
{
    char name[20];
    int state = 0;

    FILE *fptr;

    fptr = (fopen("Clients_Searching.txt", "w"));
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    printf("Write name of client you searching: ");
    scanf("%s", &name[0]);

    for (int i = 2; i < sizeOfArray; i++)
    {
        if (!strcmp(bank[i].name, name))
        {
            fprintf(fptr, "===========================\nName: %s\nIBAN: %s\nBalance: %.2lf\n-------------------------\nAddress: %s\nPhone: %ld\nBirthday: %s\n===========================\n\n", bank[i].name, bank[i].IBAN, bank[i].balance, bank[i].pData.address, bank[i].pData.phone, bank[i].pData.birthday);

            state++;
        }
    }
    
    fclose(fptr);

    if (!state)
        printf("No clients with this name. :(\n");
    else
        printf("OK!\n%d was found!\n", state);
}
/**
 * @brief Write to file all clients sorted by balance
 * 
 * @param bank 
 */
void writeToFileSorted(struct bank_custumers_details bank[sizeOfArray])
{
    char name[50];
    int mark, i, num;

    FILE *fptr;

    fptr = (fopen("Clients_Sorted.txt", "w"));
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    fprintf(fptr, "Clients list sorted by balance\nClients number: %d\n\n\n", sizeOfArray - 2);
    for (i = 2; i < sizeOfArray; ++i)
    {
        fprintf(fptr, "===========================\nName: %s\nIBAN: %s\nBalance: %.2lf\n-------------------------\nAddress: %s\nPhone: %ld\nBirthday: %s\n===========================\n\n", bank[i].name, bank[i].IBAN, bank[i].balance, bank[i].pData.address, bank[i].pData.phone, bank[i].pData.birthday);
    }
    fclose(fptr);
}
/**
 * @brief Sort bank array by balance
 * 
 * @param bank 
 */
void sortByBalance(struct bank_custumers_details bank[sizeOfArray])
{
    double t_balance;
    long int t_phone;
    char t_str[100];

    for (int i = 0; i < sizeOfArray; i++)
    {
        for (int j = i + 1; j < sizeOfArray; j++)
        {
            if (bank[i].balance > bank[j].balance)
            {
                t_balance = bank[i].balance;
                bank[i].balance = bank[j].balance;
                bank[j].balance = t_balance;

                strcpy(t_str, bank[i].name);
                strcpy(bank[i].name, bank[j].name);
                strcpy(bank[j].name, t_str);

                strcpy(t_str, bank[i].IBAN);
                strcpy(bank[i].IBAN, bank[j].IBAN);
                strcpy(bank[j].IBAN, t_str);

                strcpy(t_str, bank[i].pData.address);
                strcpy(bank[i].pData.address, bank[j].pData.address);
                strcpy(bank[j].pData.address, t_str);

                strcpy(t_str, bank[i].pData.birthday);
                strcpy(bank[i].pData.birthday, bank[j].pData.birthday);
                strcpy(bank[j].pData.birthday, t_str);

                t_phone = bank[i].pData.phone;
                bank[i].pData.phone = bank[j].pData.phone;
                bank[j].pData.phone = t_phone;
            }
        }
    }
}
/**
 * @brief Count rows(Clients) in csv file.
 * 
 * @return int 
 */
int countRows()
{

    char buf[1024];
    int row_count = 0;

    FILE *fp = fopen(fileName, "r");

    if (!fp)
    {
        printf("Can't open file\n");
    }

    while (fgets(buf, 1024, fp))
    {
        row_count++;

        if (row_count == 1)
        {
            continue;
        }
    }
    fclose(fp);
    return row_count;
}

/**
 * @brief Read file and collect all data to bank array
 * 
 * @param bank 
 */
void readFile(struct bank_custumers_details bank[sizeOfArray])
{
    // struct bank_custumers_details bank[1000];

    char buf[1024];
    int row_count = 0;
    int field_count = 0;

    FILE *fp = fopen(fileName, "r");

    if (!fp)
    {
        printf("Can't open file\n");
        // return 0;
    }

    while (fgets(buf, 1024, fp))
    {
        field_count = 0;
        row_count++;

        if (row_count == 1)
        {
            continue;
        }

        char *field = strtok(buf, ",");
        while (field)
        {
            switch (field_count)
            {
            case 0:
                strcpy(bank[row_count].name, field);
                break;
            case 1:
                strcpy(bank[row_count].IBAN, field);
                break;
            case 2:
                bank[row_count].balance = atof(field);
                break;
            case 3:
                strcpy(bank[row_count].pData.address, field);
                break;
            case 4:
                bank[row_count].pData.phone = atol(field);
                break;
            case 5:
                strcpy(bank[row_count].pData.birthday, field);
                break;
            }
            field = strtok(NULL, ",");

            field_count++;
        }
    }
    fclose(fp);
}