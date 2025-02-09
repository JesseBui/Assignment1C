#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct province
{
    char provinceName[20];
    unsigned int numberOfTestCenters;
    unsigned int totalNumberOfInfections;
    struct province *nextPtr;
};

typedef struct province Province;
typedef struct province *ProvincePtr;

// misc functions
ProvincePtr createProvince(char provinceName[20], int numberOfTestCenters);
bool isProvinceInList(ProvincePtr listPtr, char provinceName[20]);
void printProvince(ProvincePtr listPtr, char provinceName[20]);
void printList(ProvincePtr listPtr);
void printMenu();

// homework functions
ProvincePtr insertAndComputeTotalNumberOfInfections(ProvincePtr listPtr, char provinceName[20], int numberOfTestCenters);
void deleteAndDetermineLeastInfectedProvince(ProvincePtr listPtr);

// MAIN
int main() 
{
    ProvincePtr head;
    head = NULL;

    char choice;
    char input[20];
    char provinceName[20];
    int numberOfTestCenters;
  	int totalNumberOfInfections;
    printMenu();
    fgets(choice, 20, stdin);
    while (strcmp(choice, '5') != 0)
    {
        switch (choice)
        {
            case '1':
                printf("Enter province name: ");
                fgets(provinceName, 20, stdin);
                printf("Enter number of test centers: ");
                fgets(input, 20, stdin);
                head = insertAndComputeTotalNumberOfInfections(head, provinceName, strtol(input, NULL, 10));
                printList(head);
                break;
            case '2':
                deleteAndDetermineLeastInfectedProvince(head);
                break;
            case '3':
                printf("Enter province name: ");
                fgets(provinceName, 20, stdin);
                printProvince(head, provinceName);
                break;
             case '4':
                 printList(head);
                 break;
             case '5':
                 break;
             default:
                 puts("Invalid choice.");
                 break;
        }
    }
}

// CHECK - constructor
ProvincePtr createProvince(char provinceName[20], int numberOfTestCenters)
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

// CHECK - check if province is in list
bool isProvinceInList(ProvincePtr listPtr, char provinceName[20])
{
    while (listPtr != NULL)
    {
        if (strcmp(listPtr->provinceName, provinceName) == 0)
        {
            return true;
        }
        listPtr = listPtr->nextPtr;
    }
    return false;
}

// CHECK - prints province data
void printProvince(ProvincePtr listPtr, char provinceName[20])
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
            if (strcmp(listPtr->provinceName, provinceName) == 0)
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

// CHECK - prints entire list
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
    printf("1. Insert Province and Compute Total Number of Infections\n");
    printf("2. Delete and Determine Least Infected Province\n");
    printf("3. Print Province\n");
    printf("4. Print List\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

// CHECK - insert province into linked list, then calculates total no of infections
ProvincePtr insertAndComputeTotalNumberOfInfections(ProvincePtr listPtr, char provinceName[20], int numberOfTestCenters)
{
    ProvincePtr prev = NULL;
    ProvincePtr curr = listPtr;

    // use for loop to get total
    int i;
    char cases[20];
    int total = 0;
    for (i = 0; i < numberOfTestCenters; i++)
    {
        printf("Enter number of cases in test center # %d", i + 1);
        // replace with fgets()/string to int
        fgets(cases, 20, stdin);
        total += strtol(cases, NULL, 10);
    }

    // traverse list and look for province
    // strcmp() returns:
    // -1 when first arg appears earlier in the alphabet 
    // 1 when first arg appears later,
    // 0 when first arg is equal to the second arg
    // 
    while (curr != NULL && strcmp(curr->provinceName, provinceName) < 0)
    {
        prev = curr;
        curr = curr->nextPtr;
    }

    // if not found, make new province and assign ssign total to newProv->totalNumberOfInfections
    if (curr == NULL)
    {
        ProvincePtr newProv = createProvince(provinceName, numberOfTestCenters);
        newProv->totalNumberOfInfections = total;
        // insert newProv into linked list
        // if list is empty, assign newProv to be the head of the linked list
        if (prev == NULL) {
            listPtr = newProv;
        }
        else // if not empty
        {
            prev->nextPtr = newProv;
            newProv->nextPtr = curr;
        }
    }

    // if found, assign total to curr->totalNumberOfInfections
    else
    {
        curr->totalNumberOfInfections = total;
    }
    return listPtr;
}

// TODO
void deleteAndDetermineLeastInfectedProvince(ProvincePtr listPtr)
{
    ProvincePtr minPtr, currentPtr, tempPtr;
    minPtr = currentPtr = listPtr; // minPtr was NULL, we'll get a segfault in line 207
    tempPtr = NULL;
    
    while (currentPtr != NULL)
    {
        // find the least infected province
        if (currentPtr->totalNumberOfInfections < minPtr->totalNumberOfInfections)
        {
            minPtr = currentPtr;
        }
        currentPtr = currentPtr->nextPtr;
    }
    
    printf("Province with least cases : %s\nTotal cases: %d\n", minPtr->provinceName, minPtr->totalNumberOfInfections);
    
    //nuke the whole list
    while (listPtr != NULL)
    {
        tempPtr = listPtr;
        listPtr = listPtr->nextPtr;
        free(tempPtr);
    }
    listPtr = NULL;
}