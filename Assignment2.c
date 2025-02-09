#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct province {
    char provinceName[20];
    unsigned int numberOfTestCenters;
    unsigned int totalNumberOfInfections;
    struct province *nextPtr;
};

typedef struct province Province;
typedef struct province * ProvincePtr;


// misc functions
ProvincePtr createProvince(char provinceName[20], int numberOfTestCenters);
bool isProvinceInList(ProvincePtr listPtr, char provinceName[20]);
void printProvince(ProvincePtr listPtr, char provinceName[20]);
void printList(ProvincePtr listPtr);
void printMenu();

// homework functions
ProvincePtr insertAndComputeTotalNumberOfInfections(ProvincePtr listPtr, char provinceName[20], int numberOfTestCenters);
void deleteAndDetermineLeastInfectedProvince (ProvincePtr listPtr);

int main() 
{
    
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

// TODO prints menu
void printMenu()
{

}

// TODO insert province into linked list, then calculates total no of infections
ProvincePtr insertAndComputeTotalNumberOfInfections(ProvincePtr listPtr, char provinceName[20], int numberOfTestCenters)
{
    ProvincePtr prev = NULL;
    ProvincePtr curr = listPtr;
    
    // use for loop to get total
    int i;
    int cases = 0;
    int total = 0;
    // 
    for (i = 0; i < numberOfTestCenters; i++)
    {
        printf("Enter number of cases in test center # %d", i + 1);
        // TODO replace with fgets()/string to int
        scanf("%d", &cases);
        total += cases;
    }
    // traverse list and look for province
    while (curr != NULL && strcmp(curr->provinceName, provinceName) != 0)
    {
        prev = curr;
        curr = curr->nextPtr;
    }
    // if not found, make new province and assign ssign total to newProv->totalNumberOfInfections
    if (curr == NULL)
    {
        ProvincePtr newProv = createProvince(provinceName, numberOfTestCenters);
        newProv->totalNumberOfInfections = total;

        // TODO insert newProv into linked list
        curr->nextPtr = newProv;
    }
    
    // if found, assign total to curr->totalNumberOfInfections
    // 
    else
    {
        curr->totalNumberOfInfections = total;
    }
    return listPtr;
}

// TODO
void deleteAndDetermineLeastInfectedProvince (ProvincePtr listPtr)
{
    // deletes each province from the linked-list and attaches to a new ProvincePtr
    // call printProvince maybe?
}