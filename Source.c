#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct personalData
{
    char address[100];
    long int phone;
    char birthday[20];
};
struct bank_custumers_details
{
    char name[20];
    char IBAN[20];
    double balance;
    struct personalData pData;
};

int readFile(struct bank_custumers_details bank[1000]);

int main()
{
    int row_count;
    struct bank_custumers_details bank[1000];

    row_count = readFile(bank);


    for (int i = 2; i <= row_count; i++)
    {
        printf("%s\n", bank[i].name);
    }

    return 0;
}

int readFile(struct bank_custumers_details bank[1000])
{
    // struct bank_custumers_details bank[1000];

    char buf[1024];
    int row_count = 0;
    int field_count = 0;

    FILE *fp = fopen("data1.csv", "r");

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
    return row_count;
}