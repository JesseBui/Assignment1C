#include <stdio.h>
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
ProvincePtr createProvince(char provinceName[20], int numberOfTestCenters, int totalNumberOfInfections);
void printProvince(ProvincePtr head, char provinceName[20]);
void printList(ProvincePtr head);

// homework functions
ProvincePtr insertAndComputeTotalNumberOfInfections(ProvincePtr listPtr, char provinceName[20] int numberOfTestCenters);
void deleteAndDetermineLeastInfectedProvince (ProvincePtr listPtr);

int main() 
{
    
}
// DONE - constructor
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

// DONE - prints province data
void printProvince(ProvincePtr head, char provinceName[20])
{
    int position = 0;
    if (head == NULL)
    {
        printf("List is empty\n.");
    }
    else
    {
        while (head != NULL)
        {
            if (strcmp(head->provinceName, provinceName) == 0)
            {
                printf("Province: %s\n", head->provinceName);
                printf("Found at position %d\n", position);
                printf("No. of Testing Centers: %u\n", head->numberOfTestCenters);
                printf("No. of Infections: %u\n", head->totalNumberOfInfections);
                return;
            }
            head = head->nextPtr;
            position++;
        }
        printf("Province not found.\n");
    }
}

// DONE - prints entire list
void printList(ProvincePtr head)
{
    if (head == NULL)
    {
        puts("List is empty.\n")
    }
    else
    {
        while (head != NULL)
        {
            printf("Province: %s\n", head->provinceName);
            printf("No. of Testing Centers: %u\n", head->numberOfTestCenters);
            printf("No. of Infections: %u\n\n", head->totalNumberOfInfections);
            head = head->nextPtr;
        }
    }
}

// TODO insert province into linked list, then calculates total no of infections
ProvincePtr insertAndComputeTotalNumberOfInfections(ProvincePtr listPtr, char provinceName[20] int numberOfTestCenters)
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
        // TODO REPLACE WITH FGETS()
        scanf("%d", &cases);
        total += cases;
    }
    // traverse list and look for province
    while (current != NULL && strcmp(current->provinceName, provinceName) != 0)
    {
        prev = curr;
        curr = curr->nextPtr;
    }
    // if found, assign total to curr->totalNumberOfInfections
    
    // if not, make new province and assign ssign total to newProv->totalNumberOfInfections
    // ProvincePtr newProv = createProvince(provinceName, numberOfTestCenters);



    return listPtr;
}

// TODO
void deleteAndDetermineLeastInfectedProvince (ProvincePtr listPtr)
{
    // deletes each province from the linked-list and attaches to a new ProvincePtr
    // call printProvince maybe?
}