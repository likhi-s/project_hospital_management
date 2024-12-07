#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "treatment.h"
#include "menu.h"
#define USER_ID "treatment_user"
#define USER_PASSWORD "treatment@123"

Treatment *treatmentHead = NULL ;
void verifyTreatmentAndPriceManagementUser()
{
    char userId[15];
    char userPass[15];
    int option;

    printf("User Id:\n");
    scanf(" %[^\n]", userId);
    printf("User Password:\n");
    scanf(" %[^\n]", userPass);

    if (strcmp(userId, USER_ID) == 0 && strcmp(userPass, USER_PASSWORD) == 0)
    {
        while (true)
        {
            printf("\n--- Treatment Management System ---\n");
            printf("1. Add Treatment\n2. Update Treatment Details\n3. Display All Treatments\n4. Search Treatment by ID\n5. Search Treatment by Name\n6. Exit Treatment Management\n");
            printf("Enter your option: ");
            scanf("%d", &option);

            switch (option)
            {
            case ADD_TREATMENT:
                addTreatment();
                saveData();
                break;
            case UPDATE_TREATMENT_DETAILS:
                updateTreatmentDetails();
                saveData();
                break;
            case DISPLAY_ALL_TREATMENTS:
                displayTreatment();
                break;
            case SEARCH_TREATMENT_BY_ID:
                searchByTreatmentId();
                break;
            case SEARCH_TREATMENT_BY_NAME:
                searchByTreatmentName();
                break;
            case EXIT_TREATMENT_MANAGEMENT:
                printf("Exiting from Treatment Management menu.\n");
                return;
            default:
                printf("Invalid choice, try again\n");
                break;
            }
        }
    }
    else
    {
        printf("Invalid User ID or Password!\n");
    }
}

void addTreatment()
{
    Treatment *newTreatment = (Treatment *)malloc(sizeof(Treatment));

    printf("Enter Treatment ID: ");
    scanf("%d", &newTreatment->treatmentId);

    Treatment *temp = treatmentHead;
    int idExists = 0;
    while (temp != NULL)
    {
        if (temp->treatmentId == newTreatment->treatmentId)
        {
            idExists = 1;
            break;
        }
        temp = temp->next;
    }

    if (idExists)
    {
        printf("Treatment with ID %d already exists....try again\n", newTreatment->treatmentId);
        free(newTreatment);
        addTreatment();
    }
    else
    {
        printf("Enter Treatment Name: ");
        scanf(" %[^\n]", newTreatment->treatmentName);
        printf("Enter Treatment Cost: ");
        scanf("%d", &newTreatment->treatmentCost);
        printf("Enter Treatment Duration (in days): ");
        scanf("%d", &newTreatment->treatmentDuration);

        newTreatment->next = treatmentHead;
        treatmentHead = newTreatment;

        printf("Treatment added successfully!\n");
    }
}

void updateTreatmentDetails()
{
    int id, choice;
    printf("Enter Treatment ID to update: ");
    scanf("%d", &id);

    Treatment *temp = treatmentHead;
    int treatmentFound = 0;

    while (temp != NULL)
    {
        if (temp->treatmentId == id)
        {
            treatmentFound = 1;

            printf("Updating details for %s...\n", temp->treatmentName);
            printf("Which details do you want to update?\n");
            printf("1. Update Treatment Name\n2. Update Treatment Cost\n3. Update Treatment Duration\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case UPDATE_TREATMENT_NAME:
                printf("Enter New Treatment Name: ");
                scanf(" %[^\n]", temp->treatmentName);
                break;
            case UPDATE_TREATMENT_COST:
                printf("Enter New Treatment Cost: ");
                scanf("%d", &temp->treatmentCost);
                break;
            case UPDATE_TREATMENT_DURATION:
                printf("Enter New Treatment Duration (in days): ");
                scanf("%d", &temp->treatmentDuration);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Required treatment details updated successfully.\n");
            break;
        }
        temp = temp->next;
    }

    if (!treatmentFound)
    {
        printf("Treatment with ID %d not found.\n", id);
    }
}

void displayTreatment()
{
    if (treatmentHead == NULL)
    {
        printf("No treatments found.\n");
        return;
    }

    Treatment *temp = treatmentHead;
    printf("\n--- Treatment Details ---\n");
    while (temp != NULL)
    {
        printf("Treatment ID: %d\n", temp->treatmentId);
        printf("Name: %s\n", temp->treatmentName);
        printf("Cost: %d\n", temp->treatmentCost);
        printf("Duration: %d days\n", temp->treatmentDuration);
        temp = temp->next;
    }
}

void searchByTreatmentId()
{
    int id;
    printf("Enter Treatment ID to search: ");
    scanf("%d", &id);
    int searchIdFound = 0;
    Treatment *temp = treatmentHead;
    while (temp != NULL)
    {
        if (temp->treatmentId == id)
        {
            printf("\n--- Treatment Found ---\n");
            printf("Name: %s\n", temp->treatmentName);
            printf("Cost: %d\n", temp->treatmentCost);
            printf("Duration: %d days\n", temp->treatmentDuration);
            searchIdFound = 1;
            break;
        }
        temp = temp->next;
    }
    if (!searchIdFound)
    {
        printf("Treatment with ID %d not found.\n", id);
    }
}

void searchByTreatmentName()
{
    char searchName[100];
    printf("Enter Treatment Name to search: ");
    scanf(" %[^\n]", searchName);

    Treatment *temp = treatmentHead;
    int searchNameFound = 0;

    while (temp != NULL)
    {
        if (strcasecmp(searchName, temp->treatmentName) == 0)
        {
            printf("\n--- Treatment Found ---\n");
            printf("Treatment ID: %d\n", temp->treatmentId);
            printf("Cost: %d\n", temp->treatmentCost);
            printf("Duration: %d days\n", temp->treatmentDuration);
            searchNameFound = 1;
            break;
        }
        temp = temp->next;
    }

    if (!searchNameFound)
    {
        printf("Treatment with Name '%s' not found.\n", searchName);
    }
}

