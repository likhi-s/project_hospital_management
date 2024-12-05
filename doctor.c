#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include "doctor.h"
#include "menu.h"
#include "globals.h"
#define USER_ID "doctor_user"
#define USER_PASSWORD "doctor@123"

void verifyDoctorManagementUser()
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
            printf("\n--- Doctor Management System ---\n");
            printf("1. Add doctor\n2. Update doctor details\n3. Display Available Doctors\n4. Search Doctor by ID\n5. Search Doctor by Specialization\n6. Exit from Doctor management\n");
            printf("Enter your option: ");
            scanf("%d", &option);

            switch (option)
            {
            case ADD_DOCTOR:
                addDoctor();
                saveData();
                break;
            case UPDATE_DOCTOR_DETAILS:
                updateDoctorDetails();
                saveData();
                break;
            case DISPLAY_AVAILABLE_DOCTORS:
                displayDoctorDetails();
                break;
            case SEARCH_DOCTOR_BY_ID:
                searchByDoctorId();
                break;
            case SEARCH_DOCTOR_BY_SPECIALIZATION:
                searchByDoctorSpecialization();
                break;
            case EXIT_DOCTOR_MANAGEMENT:
                printf("Exiting from Doctor Management menu.\n");
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

void addDoctor()
{
    Doctor *newDoctor = (Doctor *)malloc(sizeof(Doctor));

    printf("Enter Doctor ID: ");
    scanf("%d", &newDoctor->doctorId);

    Doctor *doctorTemp = doctorHead;
    int idExists = 0;
    while (doctorTemp != NULL)
    {
        if (doctorTemp->doctorId == newDoctor->doctorId)
        {
            idExists = 1;
            break;
        }
        doctorTemp = doctorTemp->next;
    }

    if (idExists)
    {
        printf("Doctor with ID %d already exists....try again\n", newDoctor->doctorId);
        free(newDoctor);
        addDoctor();
    }
    else
    {
        printf("Enter Doctor Name: ");
        scanf(" %[^\n]", newDoctor->doctorName);
        printf("Enter Doctor Specialization: ");
        scanf(" %[^\n]", newDoctor->doctorSpecialization);
        printf("Enter Doctor Consultation Fee: ");
        scanf("%f", &newDoctor->doctorConsultationFee);
        printf("Enter Doctor Contact Number: ");
        scanf("%s", newDoctor->doctorContactNumber);
        printf("Enter Doctor Experience (in years): ");
        scanf("%d", &newDoctor->doctorExperience);
        printf("Enter Doctor Qualification: ");
        scanf(" %[^\n]", newDoctor->doctorQualification);

        newDoctor->next = doctorHead;
        doctorHead = newDoctor;

        printf("Doctor added successfully!\n");
    }
}

void updateDoctorDetails()
{
    int id, choice;
    printf("Enter Doctor ID to update: ");
    scanf("%d", &id);

    Doctor *temp = doctorHead;
    int doctorFound = 0;

    while (temp != NULL)
    {
        if (temp->doctorId == id)
        {
            doctorFound = 1;

            printf("Updating details for Dr. %s...\n", temp->doctorName);
            printf("Which details do you want to update?\n");
            printf("1. Update Doctor Name\n2. Update Specialization\n3. Update Consultation Fee\n4. Update Contact Number\n5. Update Experience\n6. Update Qualification\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case UPDATE_DOCTOR_NAME:
                printf("Enter New Doctor Name: ");
                scanf(" %[^\n]", temp->doctorName);
                break;
            case UPDATE_DOCTOR_SPECIALIZATION:
                printf("Enter New Specialization: ");
                scanf(" %[^\n]", temp->doctorSpecialization);
                break;
            case UPDATE_DOCTOR_CONSULTATION_FEE:
                printf("Enter New Consultation Fee: ");
                scanf("%f", &temp->doctorConsultationFee);
                break;
            case UPDATE_DOCTOR_CONTACT_NUMBER:
                printf("Enter New Contact Number: ");
                scanf("%s", temp->doctorContactNumber);
                break;
            case UPDATE_DOCTOR_EXPERIENCE:
                printf("Enter New Experience (years): ");
                scanf("%d", &temp->doctorExperience);
                break;
            case UPDATE_DOCTOR_QUALIFICATION:
                printf("Enter New Qualification: ");
                scanf(" %[^\n]", temp->doctorQualification);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Doctor details updated successfully.\n");
            break;
        }
        temp = temp->next;
    }

    if (!doctorFound)
    {
        printf("Doctor with ID %d not found.\n", id);
    }
}

void displayDoctorDetails()
{
    if (doctorHead == NULL)
    {
        printf("No doctors found.\n");
        return;
    }

    Doctor *temp = doctorHead;
    printf("\n--- Doctor Details ---\n");
    while (temp != NULL)
    {
        printf("Doctor ID: %d\n", temp->doctorId);
        printf("Name: %s\n", temp->doctorName);
        printf("Specialization: %s\n", temp->doctorSpecialization);
        printf("Consultation Fee: %.2f\n", temp->doctorConsultationFee);
        printf("Contact Number: %s\n", temp->doctorContactNumber);
        printf("Experience: %d years\n", temp->doctorExperience);
        printf("Qualification: %s\n", temp->doctorQualification);
        temp = temp->next;
    }
}

void searchByDoctorId()
{
    int id;
    printf("Enter Doctor ID to search: ");
    scanf("%d", &id);
    int searchIdFound = 0;
    Doctor *temp = doctorHead;
    while (temp != NULL)
    {
        if (temp->doctorId == id)
        {
            printf("\n--- Doctor Found ---\n");
            printf("Name: %s\n", temp->doctorName);
            printf("Specialization: %s\n", temp->doctorSpecialization);
            printf("Consultation Fee: %.2f\n", temp->doctorConsultationFee);
            printf("Contact Number: %s\n", temp->doctorContactNumber);
            printf("Experience: %d years\n", temp->doctorExperience);
            printf("Qualification: %s\n", temp->doctorQualification);
            searchIdFound = 1;
            break;
        }
        temp = temp->next;
    }

    if (!searchIdFound)
    {
        printf("Doctor with ID %d not found.\n", id);
    }
}

void searchByDoctorSpecialization()
{
    char specialization[50];
    printf("Enter Doctor Specialization to search: ");
    scanf(" %[^\n]", specialization);

    Doctor *temp = doctorHead;
    int searchSpecializationFound = 0;

    while (temp != NULL)
    {
        if (strcasecmp(specialization, temp->doctorSpecialization) == 0)
        {
            printf("\n--- Doctor Found ---\n");
            printf("Doctor ID: %d\n", temp->doctorId);
            printf("Name: %s\n", temp->doctorName);
            printf("Specialization: %s\n", temp->doctorSpecialization);
            printf("Consultation Fee: %.2f\n", temp->doctorConsultationFee);
            printf("Contact Number: %s\n", temp->doctorContactNumber);
            printf("Experience: %d years\n", temp->doctorExperience);
            printf("Qualification: %s\n", temp->doctorQualification);
            searchSpecializationFound = 1;
            break;
        }
        temp = temp->next;
    }

    if (!searchSpecializationFound)
    {
        printf("Doctor with Specialization '%s' not found.\n", specialization);
    }
}

