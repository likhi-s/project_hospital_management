#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bill.h"
#include "menu.h"
#define USER_ID "bill_user"
#define USER_PASSWORD "bill@123"

Bill *billHead = NULL;
void verifyBillManagementUser()
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
            printf("\n--- Bill Management System ---\n");
            printf("1. Add Bill\n2. Update Bill Details\n3. Display Bill Details\n4. Search Bill by Patient ID\n5. Calculate Bill\n6. Exit Bill Management\n");
            printf("Enter your option: ");
            scanf("%d", &option);

            switch (option)
            {
            case ADD_BILL:
                addBill();
                saveData();
                break;
            case UPDATE_BILL_DETAILS:
                updateBillDetails();
                saveData();
                break;
            case DISPLAY_BILL_DETAILS:
                displayBillDetails();
                break;
            case SEARCH_BILL_BY_PATIENT_ID:
                searchBillByPatientId();
                break;
            case CALCULATE_BILL:
                calculateBill();
                break;
            case EXIT_BILL_MANAGEMENT:
                printf("Exiting from Bill Management menu.\n");
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

void addBill()
{
    Bill *newBill = (Bill *)malloc(sizeof(Bill));

    printf("Enter Bill ID: ");
    scanf("%d", &newBill->billId);

    Bill *billTemp = billHead;
    int idExists = 0;
    while (billTemp != NULL)
    {
        if (billTemp->billId == newBill->billId)
        {
            idExists = 1;
            break;
        }
        billTemp = billTemp->next;
    }

    if (idExists)
    {
        printf("Bill with ID %d already exists....try again\n", newBill->billId);
        free(newBill);
        addBill();
    }
    else
    {
        printf("Enter Patient ID: ");
        scanf("%d", &newBill->patientId);
        printf("Enter Treatment ID: ");
        scanf("%d", &newBill->treatmentId);
        printf("Enter Consultation Fee: ");
        scanf("%f", &newBill->consultationFee);
        printf("Enter Pharmacy Fee: ");
        scanf("%f", &newBill->pharmacyFee);
        printf("Enter Room Fee: ");
        scanf("%f", &newBill->roomFee);
        printf("Enter Bill Date (DD/MM/YYYY): ");
        scanf(" %[^\n]", newBill->billDate);

        newBill->totalBillAmount = newBill->consultationFee + newBill->pharmacyFee + newBill->roomFee;

        newBill->next = billHead;
        billHead = newBill;

        printf("Bill added successfully!\n");
    }
}

void updateBillDetails()
{
    int id, choice;
    printf("Enter Bill ID to update: ");
    scanf("%d", &id);

    Bill *billTemp = billHead;
    int billFound = 0;

    while (billTemp != NULL)
    {
        if (billTemp->billId == id)
        {
            billFound = 1;

            printf("Updating details for Bill ID %d...\n", billTemp->billId);
            printf("Which details do you want to update?\n");
            printf("1. Update Patient ID\n2. Update Treatment ID\n3. Update Consultation Fee\n4. Update Pharmacy Fee\n5. Update Room Fee\n6. Update Bill Date\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case UPDATE_BILL_WITH_PATIENT_ID:
                printf("Enter New Patient ID: ");
                scanf("%d", &billTemp->patientId);
                break;
            case UPDATE_BILL_WITH_TREATMENT_ID:
                printf("Enter New Treatment ID: ");
                scanf("%d", &billTemp->treatmentId);
                break;
            case UPDATE_BILL_WITH_CONSULTATION_FEE:
                printf("Enter New Consultation Fee: ");
                scanf("%f", &billTemp->consultationFee);
                break;
            case UPDATE_BILL_WITH_PHARMACY_FEE:
                printf("Enter New Pharmacy Fee: ");
                scanf("%f", &billTemp->pharmacyFee);
                break;
            case UPDATE_BILL_WITH_ROOM_FEE:
                printf("Enter New Room Fee: ");
                scanf("%f", &billTemp->roomFee);
                break;
            case UPDATE_BILL_DATE:
                printf("Enter New Bill Date (DD/MM/YYYY): ");
                scanf(" %[^\n]", billTemp->billDate);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            billTemp->totalBillAmount = billTemp->consultationFee + billTemp->pharmacyFee + billTemp->roomFee;
            printf("Bill details updated successfully.\n");
            break;
        }
        billTemp = billTemp->next;
    }

    if (!billFound)
    {
        printf("Bill with ID %d not found.\n", id);
    }
}

void displayBillDetails()
{
    if (billHead == NULL)
    {
        printf("No bills available.\n");
        return;
    }

    Bill *billTemp = billHead;
    printf("\n--- Bill Details ---\n");
    while (billTemp != NULL)
    {
        printf("Bill ID: %d\n", billTemp->billId);
        printf("Patient ID: %d\n", billTemp->patientId);
        printf("Treatment ID: %d\n", billTemp->treatmentId);
        printf("Consultation Fee: %f\n", billTemp->consultationFee);
        printf("Pharmacy Fee: %f\n", billTemp->pharmacyFee);
        printf("Room Fee: %f\n", billTemp->roomFee);
        printf("Total Bill Amount: %.2f\n", billTemp->totalBillAmount);
        printf("Bill Date: %s\n", billTemp->billDate);
        billTemp = billTemp->next;
    }
}

void searchBillByPatientId()
{
    int patientId;
    printf("Enter Patient ID to search: ");
    scanf("%d", &patientId);
    int searchIdFound = 0;
    Bill *billTemp = billHead;
    while (billTemp != NULL)
    {
        if (billTemp->patientId == patientId)
        {
            printf("\n--- Bill Found ---\n");
            printf("Bill ID: %d\n", billTemp->billId);
            printf("Treatment ID: %d\n", billTemp->treatmentId);
            printf("Consultation Fee: %f\n", billTemp->consultationFee);
            printf("Pharmacy Fee: %f\n", billTemp->pharmacyFee);
            printf("Room Fee: %f\n", billTemp->roomFee);
            printf("Total Bill Amount: %f\n", billTemp->totalBillAmount);
            printf("Bill Date: %s\n", billTemp->billDate);
            searchIdFound = 1;
            break;
        }
        billTemp = billTemp->next;
    }

    if (!searchIdFound)
    {
        printf("Bill for Patient ID %d not found.\n", patientId);
    }
}

void calculateBill()
{
    int id;
    printf("Enter Bill ID to calculate: ");
    scanf("%d", &id);
    Bill *billTemp = billHead;
    int billFound = 0;
    while (billTemp != NULL)
    {
        if (billTemp->billId == id)
        {
            printf("\n--- Bill Calculation ---\n");
            printf("Consultation Fee: %f\n", billTemp->consultationFee);
            printf("Pharmacy Fee: %f\n", billTemp->pharmacyFee);
            printf("Room Fee: %f\n", billTemp->roomFee);
            billTemp->totalBillAmount = billTemp->consultationFee + billTemp->pharmacyFee + billTemp->roomFee;
            printf("Total Bill Amount: %f\n", billTemp->totalBillAmount);
            billFound = 1;
            break;
        }
        billTemp = billTemp->next;
    }

    if (!billFound)
    {
        printf("Bill with ID %d not found.\n", id);
    }
}

