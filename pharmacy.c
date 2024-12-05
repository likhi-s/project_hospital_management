#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pharmacy.h"
#include "globals.h"
#define USER_ID "pharmacy_user"
#define USER_PASSWORD "pharmacy@123"


void verifyPharmacyManagementUser()
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
        while (true) {
            printf("\n--- Pharmacy Management System ---\n");
            printf("1. Add Medicine\n2. Update Medicine Details\n3. Display Available Medicines\n4. Search Medicine by ID\n5. Search Medicine by Name\n6. Check Medicine Stock\n7. Exit from Pharmacy Management\n");
            printf("Enter your option: ");
            scanf("%d", &option);

            switch (option)
            {
            case ADD_NEW_MEDICINE:
                addMedicine();
                saveData();
                break;
            case UPDATE_MEDICINE_DETAILS:
                updateMedicineDetails();
                saveData();
                break;
            case DISPLAY_AVAILABLE_MEDICINES:
                displayMedicineDetails();
                break;
            case SEARCH_MEDICINE_BY_ID:
                searchByMedicineId();
                break;
            case SEARCH_MEDICINE_BY_NAME:
                searchByMedicineName();
                break;
            case CHECK_STOCK:
                checkMedicineStock();
                break;
            case EXIT_PHARMACY_MANAGEMENT:
                printf("Exiting from Pharmacy Management menu.\n");
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

void addMedicine()
{
    Pharmacy *newMedicine = (Pharmacy *)malloc(sizeof(Pharmacy));

    printf("Enter Medicine ID: ");
    scanf("%d", &newMedicine->medicineId);

    Pharmacy *temp = pharmacyHead;
    int idExists = 0;
    while (temp != NULL)
    {
        if (temp->medicineId == newMedicine->medicineId)
        {
            idExists = 1;
            break;
        }
        temp = temp->next;
    }

    if (idExists)
    {
        printf("Medicine with ID %d already exists....try again\n", newMedicine->medicineId);
        free(newMedicine);
        addMedicine();
    }
    else
    {
        printf("Enter Medicine Name: ");
        scanf(" %[^\n]", newMedicine->medicineName);
        printf("Enter Medicine Cost: ");
        scanf("%f", &newMedicine->medicineCost);
        printf("Enter Medicine Stock Quantity: ");
        scanf("%d", &newMedicine->medicineStockQuantity);
        printf("Enter Medicine Type (tablet/injection): ");
        scanf(" %[^\n]", newMedicine->medicineType);
        printf("Enter Medicine Dosage: ");
        scanf(" %[^\n]", newMedicine->medicineDosage);

        newMedicine->next = pharmacyHead;
        pharmacyHead = newMedicine;

        printf("Medicine added successfully!\n");
    }
}

void updateMedicineDetails()
{
    int id, choice;
    printf("Enter Medicine ID to update: ");
    scanf("%d", &id);

    Pharmacy *temp = pharmacyHead;
    int medicineFound = 0;

    while (temp != NULL)
    {
        if (temp->medicineId == id)
        {
            medicineFound = 1;

            printf("Updating details for %s...\n", temp->medicineName);
            printf("Which details do you want to update?\n");
            printf("1. Update Medicine Name\n2. Update Medicine Cost\n3. Update Medicine Stock\n4. Update Medicine Type\n5. Update Medicine Dosage\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case UPDATE_MEDICINE_NAME:
                printf("Enter New Medicine Name: ");
                scanf(" %[^\n]", temp->medicineName);
                break;
            case UPDATE_MEDICINE_COST:
                printf("Enter New Medicine Cost: ");
                scanf("%f", &temp->medicineCost);
                break;
            case UPDATE_MEDICINE_STOCK:
                printf("Enter New Stock Quantity: ");
                scanf("%d", &temp->medicineStockQuantity);
                break;
            case UPDATE_MEDICINE_TYPE:
                printf("Enter New Medicine Type: ");
                scanf(" %[^\n]", temp->medicineType);
                break;
            case UPDATE_MEDICINE_DOSAGE:
                printf("Enter New Medicine Dosage: ");
                scanf(" %[^\n]", temp->medicineDosage);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Medicine details updated successfully.\n");
            break;
        }
        temp = temp->next;
    }

    if (!medicineFound)
    {
        printf("Medicine with ID %d not found.\n", id);
    }
}

void displayMedicineDetails()
{
    if (pharmacyHead == NULL)
    {
        printf("No medicines found.\n");
        return;
    }

    Pharmacy *temp = pharmacyHead;
    printf("\n--- Medicine Details ---\n");
    while (temp != NULL)
    {
        printf("Medicine ID: %d\n", temp->medicineId);
        printf("Name: %s\n", temp->medicineName);
        printf("Cost: %f\n", temp->medicineCost);
        printf("Stock Quantity: %d\n", temp->medicineStockQuantity);
        printf("Type: %s\n", temp->medicineType);
        printf("Dosage: %s\n", temp->medicineDosage);
        temp = temp->next;
    }
}

void searchByMedicineId()
{
    int id;
    printf("Enter Medicine ID to search: ");
    scanf("%d", &id);
    int searchIdFound = 0;
    Pharmacy *temp = pharmacyHead;
    while (temp != NULL)
    {
        if (temp->medicineId == id)
        {
            printf("\n--- Medicine Found ---\n");
            printf("Name: %s\n", temp->medicineName);
            printf("Cost: %f\n", temp->medicineCost);
            printf("Stock Quantity: %d\n", temp->medicineStockQuantity);
            printf("Type: %s\n", temp->medicineType);
            printf("Dosage: %s\n", temp->medicineDosage);
            searchIdFound = 1;
            break;
        }
        temp = temp->next;
    }

    if (!searchIdFound)
    {
        printf("Medicine with ID %d not found.\n", id);
    }
}

void searchByMedicineName()
{
    char name[100];
    printf("Enter Medicine Name to search: ");
    scanf(" %[^\n]", name);

    Pharmacy *temp = pharmacyHead;
    int searchNameFound = 0;

    while (temp != NULL)
    {
        if (strcasecmp(name, temp->medicineName) == 0)
        {
            printf("\n--- Medicine Found ---\n");
            printf("Medicine ID: %d\n", temp->medicineId);
            printf("Cost: %f\n", temp->medicineCost);
            printf("Stock Quantity: %d\n", temp->medicineStockQuantity);
            printf("Type: %s\n", temp->medicineType);
            printf("Dosage: %s\n", temp->medicineDosage);
            searchNameFound = 1;
            break;
        }
        temp = temp->next;
    }

    if (!searchNameFound)
    {
        printf("Medicine with Name '%s' not found.\n", name);
    }
}

void checkMedicineStock()
{
    int id;
    printf("Enter Medicine ID to check stock: ");
    scanf("%d", &id);
    int stockFound = 0;
    Pharmacy *temp = pharmacyHead;
    while (temp != NULL)
    {
        if (temp->medicineId == id)
        {
            printf("\n--- Stock Details ---\n");
            printf("Medicine ID: %d\n", temp->medicineId);
            printf("Stock Quantity: %d\n", temp->medicineStockQuantity);
            stockFound = 1;
            break;
        }
        temp = temp->next;
    }

    if (!stockFound)
    {
        printf("Medicine with ID %d not found.\n", id);
    }
}

