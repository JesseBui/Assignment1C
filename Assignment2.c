#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct province
{
    char provinceName[30];
    unsigned int numberOfTestCenters;
    unsigned int totalNumberOfInfections;
    struct province *nextPtr;
};

char provinces[13][30] = {
	"Alberta",
    "British Columbia",
    "Manitoba",
    "New Brunswick",
    "Newfoundland and Labrador",
    "Northwest Territories",
    "Nova Scotia",
    "Nunavut",
    "Ontario",
    "Prince Edward Island",
    "Quebec",
    "Saskatchewan",
    "Yukon"
};

typedef struct province Province;
typedef struct province *ProvincePtr;

// misc functions
ProvincePtr createProvince(char provinceName[30], int numberOfTestCenters);
void printProvince(ProvincePtr listPtr, char provinceName[30]);
void printList(ProvincePtr listPtr);
void printMenu();
bool inProvArray(char provinceName[30]);
void removeNewline(char word[30]);

// homework functions
ProvincePtr insertAndComputeTotalNumberOfInfections(ProvincePtr listPtr, char provinceName[30], int numberOfTestCenters);
void deleteAndDetermineLeastInfectedProvince(ProvincePtr listPtr);

// MAIN
int main() 
{
    ProvincePtr head;
    head = NULL;

    char choice[30];
    char input[30];
    char provinceName[30];
    int numberOfTestCenters;
  	int totalNumberOfInfections;
    printMenu();
    fgets(choice, 30, stdin);
    removeNewline(choice);
    while (strcasecmp(choice, "5") != 0)
    {
        switch (strtol(choice, NULL, 10))
        {
            case 1:
                printf("Enter province name: ");
                fgets(provinceName, 30, stdin);
                removeNewline(provinceName);
                while (inProvArray(provinceName) != true)
                {
                    puts("Invalid province name.");
                    printf("Enter province name: ");
                    fgets(provinceName, 30, stdin);
                    removeNewline(provinceName);
                }
                printf("Enter number of test centers: ");
                fgets(input, 30, stdin);
                while (strtol(input, NULL, 10) < 1 || strtol(input, NULL, 10) > 10)
                {
                    puts("Invalid number of test centers (1 - 10).");
                    printf("Enter number of test centers: ");
                    fgets(input, 25, stdin);
                }
                head = insertAndComputeTotalNumberOfInfections(head, provinceName, strtol(input, NULL, 10));
                printList(head);
                break;
            case 2:
                deleteAndDetermineLeastInfectedProvince(head);
                head = NULL;
                break;
            case 3:
                printf("Enter province name: ");
                fgets(provinceName, 30, stdin);
                removeNewline(provinceName);
                while (inProvArray(provinceName) != true)
                {
                    puts("Invalid province name.");
                    printf("Enter province name: ");
                    fgets(provinceName, 30, stdin);
                    removeNewline(provinceName);
                }
                printProvince(head, provinceName);
                break;
             case 4:
                 printList(head);
                 break;
             case 5:
                 break;
             default:
                 puts("Invalid choice.");
                 break;
        }
        printMenu();
        fgets(choice, 25, stdin);
        removeNewline(choice);
    }
}

// DONE - constructor
ProvincePtr createProvince(char provinceName[30], int numberOfTestCenters)
{
    ProvincePtr newProvince;
    newProvince = (ProvincePtr)malloc(sizeof(Province));
    if (newProvince != NULL)
    {
        strcpy(newProvince->provinceName, provinceName);
        newProvince->numberOfTestCenters = numberOfTestCenters;
        newProvince->totalNumberOfInfections = 0;
        newProvince->nextPtr = NULL;
    }
    return newProvince;
}

// DONE - prints province data
void printProvince(ProvincePtr listPtr, char provinceName[30])
{
    int position = 0;
    if (listPtr == NULL)
    {
        printf("List is empty\n.");
    }
    else
    {
        while (listPtr != NULL)
        {
            if (strcasecmp(listPtr->provinceName, provinceName) == 0)
            {
                printf("Province: %s\n", listPtr->provinceName);
                printf("Found at position %d\n", position);
                printf("No. of Testing Centers: %u\n", listPtr->numberOfTestCenters);
                printf("No. of Infections: %u\n", listPtr->totalNumberOfInfections);
                return;
            }
            listPtr = listPtr->nextPtr;
            position++;
        }
        printf("Province not found.\n");
    }
}

// DONE - prints entire list
void printList(ProvincePtr listPtr)
{
    if (listPtr == NULL)
    {
        puts("List is empty.\n");
    }
    else
    {
        while (listPtr != NULL)
        {
            printf("Province: %s\n", listPtr->provinceName);
            printf("No. of Testing Centers: %u\n", listPtr->numberOfTestCenters);
            printf("No. of Infections: %u\n\n", listPtr->totalNumberOfInfections);
            listPtr = listPtr->nextPtr;
        }
    }
}

// DONE - prints menu
void printMenu()
{
    printf("1. Insert province (HW - 1)\n");
    printf("2. Delete entire list, print province w/ least cases (HW - 2)\n");
    printf("3. Print Province\n");
    printf("4. Print List\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

// DONE - check if province is in provinces array
bool inProvArray(char provinceName[30])
{
    int i;
    for (i = 0; i < 13; i++)
    {
        if (strcmp(provinceName, provinces[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

// DONE - removes newline char
void removeNewline(char word[30])
{
	    int i = 0;
    while (word[i] != '\0')
    {
        if (word[i] == '\n')
        {
            word[i] = '\0';
        }
        i++;
    }
}

// DONE - insert province into linked list, then calculates total no of infections
ProvincePtr insertAndComputeTotalNumberOfInfections(ProvincePtr listPtr, char provinceName[30], int numberOfTestCenters)
{
    ProvincePtr prev = NULL;
    ProvincePtr curr = listPtr;

    // use for loop to get total
    int i;
    char cases[30];
    int total = 0;
    for (i = 0; i < numberOfTestCenters; i++)
    {
        printf("Enter number of cases in test center #%d: ", i + 1);
        fgets(cases, 30, stdin);
        total += strtol(cases, NULL, 10);
    }

    // traverse list and look for province
    while (curr != NULL && strcasecmp(curr->provinceName, provinceName) != 0)
    {
        prev = curr;
        curr = curr->nextPtr;
    }

    // if found, remove old copy
    if (curr != NULL && strcasecmp(curr->provinceName, provinceName) == 0)
    {
        if (prev == NULL)
        {
            listPtr = curr->nextPtr;
        }
        else
        {
            prev->nextPtr = curr->nextPtr;
        }
        free(curr);
		
    }
    prev = NULL;
    curr = listPtr;
    ProvincePtr newProv = createProvince(provinceName, numberOfTestCenters);
    newProv->totalNumberOfInfections = total;
    // insert newProv into linked list
    while (curr != NULL && curr->totalNumberOfInfections < total)
    {
        prev = curr;
        curr = curr->nextPtr;
    }
    if (prev == NULL)
    {
        newProv->nextPtr = listPtr;
        listPtr = newProv;
    }
    else
    {
        prev->nextPtr = newProv;
        newProv->nextPtr = curr;
    }
    
    return listPtr;
}

// DONE
// DONE
void deleteAndDetermineLeastInfectedProvince(ProvincePtr listPtr)
{
    if (listPtr == NULL)
    {
        puts("List is empty.");
        return;
    }
    
    ProvincePtr minPtr, currentPtr, tempPtr;
    minPtr = currentPtr = listPtr; 
    tempPtr = NULL;
    
    if (listPtr == NULL)
    {
        puts("The list is empty");
        return;
    }
    while (currentPtr != NULL)
    {
        // find the least infected province
        if (currentPtr->totalNumberOfInfections < minPtr->totalNumberOfInfections)
        {
            minPtr = currentPtr;
        }
        currentPtr = currentPtr->nextPtr;
    }
    printf("Province with least cases: %s\nTotal cases: %d\n", minPtr->provinceName, minPtr->totalNumberOfInfections);
    //nuke the whole list
    while (listPtr != NULL)
    {
        tempPtr = listPtr;
        listPtr = listPtr->nextPtr;

        tempPtr->numberOfTestCenters= 0;
        tempPtr->provinceName[0]= '\0';
        tempPtr->totalNumberOfInfections = 0;
        free(tempPtr);
    }
    listPtr = NULL;
}