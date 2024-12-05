#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "staff.h"
#include "globals.h"
#define USER_ID "staff_user"
#define USER_PASSWORD "staff@123"


void verifyStaffManagementUser()
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
            printf("\n--- Staff Management System ---\n");
            printf("1. Add Staff\n2. Update Staff details\n3. Display Available Staff\n4. Search Staff by ID\n5. Search Staff by Role\n6. Exit from Staff Management\n");
            printf("Enter your option: ");
            scanf("%d", &option);

            switch (option)
            {
            case ADD_STAFF:
                addStaff();
                saveData();
                break;
            case UPDATE_STAFF_DETAILS:
                updateStaffDetails();
                saveData();
                break;
            case DISPLAY_AVAILABLE_STAFF:
                displayStaffDetails();
                break;
            case SEARCH_STAFF_BY_ID:
                searchByStaffId();
                break;
            case SEARCH_STAFF_BY_ROLE:
                searchByStaffRole();
                break;
            case EXIT_STAFF_MANAGEMENT:
                printf("Exiting from Staff Management menu.\n");
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

void addStaff()
{
    Staff *newStaff = (Staff *)malloc(sizeof(Staff));

    printf("Enter Staff ID: ");
    scanf("%d", &newStaff->staffId);

    Staff *temp = staffHead;
    int idExists = 0;
    while (temp != NULL)
    {
        if (temp->staffId == newStaff->staffId)
        {
            idExists = 1;
            break;
        }
        temp = temp->next;
    }

    if (idExists)
    {
        printf("Staff with ID %d already exists....try again\n", newStaff->staffId);
        free(newStaff);
        addStaff();
    }
    else
    {
        printf("Enter Staff Name: ");
        scanf(" %[^\n]", newStaff->staffName);
        printf("Enter Staff Role (e.g., Nurse, Technician, Receptionist): ");
        scanf(" %[^\n]", newStaff->staffRole);
        printf("Enter Staff Shift (Day/Night): ");
        scanf("%s", newStaff->staffShift);
        printf("Enter Staff Salary: ");
        scanf("%f", &newStaff->staffSalary);
        printf("Enter Staff Contact Number: ");
        scanf("%s", newStaff->staffContactNumber);

        newStaff->next = staffHead;
        staffHead = newStaff;

        printf("Staff added successfully!\n");
    }
}

void updateStaffDetails()
{
    int id, choice;
    printf("Enter Staff ID to update: ");
    scanf("%d", &id);

    Staff *temp = staffHead;
    int staffFound = 0;

    while (temp != NULL)
    {
        if (temp->staffId == id)
        {
            staffFound = 1;

            printf("Updating details for %s...\n", temp->staffName);
            printf("Which details do you want to update?\n");
            printf("1. Update Staff Name\n2. Update Role\n3. Update Shift\n4. Update Salary\n5. Update Contact Number\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case UPDATE_STAFF_NAME:
                printf("Enter New Staff Name: ");
                scanf(" %[^\n]", temp->staffName);
                break;
            case UPDATE_STAFF_ROLE:
                printf("Enter New Role: ");
                scanf(" %[^\n]", temp->staffRole);
                break;
            case UPDATE_STAFF_SHIFT:
                printf("Enter New Shift (Day/Night): ");
                scanf("%s", temp->staffShift);
                break;
            case UPDATE_STAFF_SALARY:
                printf("Enter New Salary: ");
                scanf("%f", &temp->staffSalary);
                break;
            case UPDATE_STAFF_CONTACT_NUMBER:
                printf("Enter New Contact Number: ");
                scanf("%s", temp->staffContactNumber);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Required staff details updated successfully.\n");
            break;
        }
        temp = temp->next;
    }

    if (!staffFound)
    {
        printf("Staff with ID %d not found.\n", id);
    }
}

void displayStaffDetails()
{
    if (staffHead == NULL)
    {
        printf("No staff found.\n");
        return;
    }

    Staff *temp = staffHead;
    printf("\n--- Staff Details ---\n");
    while (temp != NULL)
    {
        printf("Staff ID: %d\n", temp->staffId);
        printf("Name: %s\n", temp->staffName);
        printf("Role: %s\n", temp->staffRole);
        printf("Shift: %s\n", temp->staffShift);
        printf("Salary: %f\n", temp->staffSalary);
        printf("Contact Number: %s\n", temp->staffContactNumber);
        temp = temp->next;
    }
}

void searchByStaffId()
{
    int id;
    printf("Enter Staff ID to search: ");
    scanf("%d", &id);
    int searchIdFound = 0;
    Staff *temp = staffHead;
    while (temp != NULL)
    {
        if (temp->staffId == id)
        {
            printf("\n--- Staff Found ---\n");
            printf("Name: %s\n", temp->staffName);
            printf("Role: %s\n", temp->staffRole);
            printf("Shift: %s\n", temp->staffShift);
            printf("Salary: %f\n", temp->staffSalary);
            printf("Contact Number: %s\n", temp->staffContactNumber);
            searchIdFound = 1;
            break;
        }
        temp = temp->next;
    }
    if (!searchIdFound)
    {
        printf("Staff with ID %d not found.\n", id);
    }
}

void searchByStaffRole()
{
    char searchRole[50];
    printf("Enter Staff Role to search: ");
    scanf(" %[^\n]", searchRole);

    Staff *temp = staffHead;
    int searchRoleFound = 0;

    while (temp != NULL)
    {
        if (strcasecmp(searchRole, temp->staffRole) == 0)
        {
            printf("\n--- Staff Found ---\n");
            printf("Staff ID: %d\n", temp->staffId);
            printf("Name: %s\n", temp->staffName);
            printf("Role: %s\n", temp->staffRole);
            printf("Shift: %s\n", temp->staffShift);
            printf("Salary: %f\n", temp->staffSalary);
            printf("Contact Number: %s\n", temp->staffContactNumber);
            searchRoleFound = 1;
            break;
        }
        temp = temp->next;
    }

    if (!searchRoleFound)
    {
        printf("Staff with Role '%s' not found.\n", searchRole);
    }
}
