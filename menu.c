#include <stdio.h>
#include "patient.h"
#include "doctor.h"
#include "staff.h"
#include "treatment.h"
#include "pharmacy.h"
#include "room.h"
#include "bill.h"
#include "menu.h"
#define SUCCESS 0
#define EXIT 1

void menu()
{
    loadData();
    while(1)
    {
        int choice;
        printf("____Administrative Menu____\n");
        printf("1.Verify patient Management user\n2.Verify Doctor Management user\n3.verify Staff Management user\n4.Verify Treatment and price Management user\n5.Verify Pharmacy Management user\n6.Verify Room management user\n7.Verify Bill Managemnet user\n8.Exit Administrative menu\n");
        printf("enter the choice:");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            verifyPatientManagementUser();
            break;
        case 2:
            verifyDoctorManagementUser();
            break;
        case 3:
            verifyStaffManagementUser();
            break;
        case 4:
            verifyTreatmentAndPriceManagementUser();
            break;
        case 5:
            verifyPharmacyManagementUser();
            break;
        case 6:
            verifyRoomManagementUser();
            break;
        case 7:
            verifyBillManagementUser();
            break;
        case 8:
            printf("Exiting the administrative Menu");
            break;
        default:
            printf("invalid choice\n");
            break;

        }
    }

}

void saveData()
{
    FILE *file = fopen("Hospital.csv", "w");
    if (file == NULL)
    {
        printf("Error saving data!\n");
        return;
    }

    fprintf(file, "PATIENT_DATA\n");
    fprintf(file, "PatientID,Name,Gender,Age,Address,ContactNumber,EmergencyContactNumber\n");
    Patient *patientTemp = patientHead;
    while (patientTemp != NULL)
    {
        fprintf(file, "%d,\"%s\",%s,%d,\"%s\",%s,%s\n",patientTemp->patientId, patientTemp->patientName, patientTemp->patientGender, patientTemp->patientAge, patientTemp->patientAddress,patientTemp->patientContactNumber, patientTemp->patientEmergencyContactNumber);
        patientTemp = patientTemp->next;
    }


    fprintf(file, "DOCTOR_DATA\n");
    fprintf(file, "DoctorID,Name,Specialization,ConsultationFee,ContactNumber,Experience,Qualification\n");
    Doctor *doctorTemp = doctorHead;
    while (doctorTemp != NULL)
    {
        fprintf(file, "%d,\"%s\",%s,%f,%s,%d,\"%s\"\n",doctorTemp->doctorId, doctorTemp->doctorName, doctorTemp->doctorSpecialization,doctorTemp->doctorConsultationFee, doctorTemp->doctorContactNumber,doctorTemp->doctorExperience, doctorTemp->doctorQualification);
        doctorTemp = doctorTemp->next;
    }


    fprintf(file, "STAFF_DATA\n");
    fprintf(file, "StaffID,Name,Role,Shift,Salary,ContactNumber\n");
    Staff *staffTemp = staffHead;
    while (staffTemp != NULL)
    {
        fprintf(file, "%d,\"%s\",%s,%s,%f,%s\n",staffTemp->staffId, staffTemp->staffName, staffTemp->staffRole, staffTemp->staffShift, staffTemp->staffSalary, staffTemp->staffContactNumber);
        staffTemp = staffTemp->next;
    }


    fprintf(file, "TREATMENT_DATA\n");
    fprintf(file, "TreatmentID,Name,Cost,Duration\n");
    Treatment *treatmentTemp = treatmentHead;
    while (treatmentTemp != NULL)
    {
        fprintf(file, "%d,\"%s\",%d,%d\n",treatmentTemp->treatmentId, treatmentTemp->treatmentName,treatmentTemp->treatmentCost, treatmentTemp->treatmentDuration);
        treatmentTemp = treatmentTemp->next;
    }


    fprintf(file, "PHARMACY_DATA\n");
    fprintf(file, "MedicineID,Name,Cost,StockQuantity,Type,Dosage\n");
    Pharmacy *pharmacyTemp = pharmacyHead;
    while (pharmacyTemp != NULL)
    {
        fprintf(file, "%d,\"%s\",%f,%d,%s,\"%s\"\n",pharmacyTemp->medicineId, pharmacyTemp->medicineName, pharmacyTemp->medicineCost,pharmacyTemp->medicineStockQuantity, pharmacyTemp->medicineType,pharmacyTemp->medicineDosage);
        pharmacyTemp = pharmacyTemp->next;
    }

    fprintf(file, "ROOM_DATA\n");
    fprintf(file, "RoomID,Type,BedCount,AvailableBeds,BedStatus,Fee\n");
    Room *roomTemp = roomHead;
    while (roomTemp != NULL)
    {
        fprintf(file, "%d,%s,%d,%d,%s,%f\n",roomTemp->roomId, roomTemp->roomType, roomTemp->bedCount,roomTemp->availableBeds, roomTemp->bedStatus, roomTemp->roomFee);
        roomTemp = roomTemp->next;
    }

    fprintf(file, "BILL_DATA\n");
    fprintf(file, "BillID,PatientID,TreatmentID,ConsultationFee,PharmacyFee,RoomFee,TotalAmount,BillDate\n");
    Bill *billTemp = billHead;
    while (billTemp != NULL)
    {
        fprintf(file, "%d,%d,%d,%f,%f,%f,%f,%s\n",billTemp->billId, billTemp->patientId, billTemp->treatmentId,billTemp->consultationFee, billTemp->pharmacyFee, billTemp->roomFee,billTemp->totalBillAmount, billTemp->billDate);
        billTemp = billTemp->next;
    }

    fclose(file);
    printf("All data saved successfully!\n");
}

int loadData()
{
    FILE *file = fopen("Hospital.csv", "r");
    if (file == NULL)
    {
        printf("No previous data found.\n");
        return EXIT;
    }

    char line[1024];
    char section[50] = "";

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] == '\n') continue;


        if (strncmp(line, "PATIENT_DATA", 12) == 0)
        {
            strcpy(section, "PATIENT_DATA");
            continue;
        }
        else if (strncmp(line, "DOCTOR_DATA", 11) == 0)
        {
            strcpy(section, "DOCTOR_DATA");
            continue;
        }
        else if (strncmp(line, "STAFF_DATA", 10) == 0)
        {
            strcpy(section, "STAFF_DATA");
            continue;
        }
        else if (strncmp(line, "TREATMENT_DATA", 14) == 0)
        {
            strcpy(section, "TREATMENT_DATA");
            continue;
        }
        else if (strncmp(line, "PHARMACY_DATA", 13) == 0)
        {
            strcpy(section, "PHARMACY_DATA");
            continue;
        }
        else if (strncmp(line, "ROOM_DATA", 9) == 0)
        {
            strcpy(section, "ROOM_DATA");
            continue;
        }
        else if (strncmp(line, "BILL_DATA", 9) == 0)
        {
            strcpy(section, "BILL_DATA");
            continue;
        }


        if (strcmp(section, "PATIENT_DATA") == 0)
        {
            Patient *temp = (Patient *)malloc(sizeof(Patient));
            sscanf(line, "%d,\"%[^\"]\",%[^,],%d,\"%[^\"]\",%[^,],%s",&temp->patientId, temp->patientName, temp->patientGender,&temp->patientAge, temp->patientAddress, temp->patientContactNumber, temp->patientEmergencyContactNumber);
            temp->next = patientHead;
            patientHead = temp;
        }
        else if (strcmp(section, "DOCTOR_DATA") == 0)
        {
            Doctor *temp = (Doctor *)malloc(sizeof(Doctor));
            sscanf(line, "%d,\"%[^\"]\",%[^,],%f,%[^,],%d,\"%[^\"]\"",&temp->doctorId, temp->doctorName, temp->doctorSpecialization,&temp->doctorConsultationFee, temp->doctorContactNumber,&temp->doctorExperience, temp->doctorQualification);
            temp->next = doctorHead;
            doctorHead = temp;
        }
        else if (strcmp(section, "STAFF_DATA") == 0)
        {
            Staff *temp = (Staff *)malloc(sizeof(Staff));
            sscanf(line, "%d,\"%[^\"]\",%[^,],%[^,],%f,%[^,]",&temp->staffId, temp->staffName, temp->staffRole,temp->staffShift, &temp->staffSalary, temp->staffContactNumber);
            temp->next = staffHead;
            staffHead = temp;
        }
        else if (strcmp(section, "TREATMENT_DATA") == 0)
        {
            Treatment *temp = (Treatment *)malloc(sizeof(Treatment));
            sscanf(line, "%d,\"%[^\"]\",%d,%d",&temp->treatmentId, temp->treatmentName,&temp->treatmentCost, &temp->treatmentDuration);
            temp->next = treatmentHead;
            treatmentHead = temp;
        }
        else if (strcmp(section, "PHARMACY_DATA") == 0)
        {
            Pharmacy *temp = (Pharmacy *)malloc(sizeof(Pharmacy));
            sscanf(line, "%d,\"%[^\"]\",%f,%d,%[^,],\"%[^\"]\"", &temp->medicineId, temp->medicineName, &temp->medicineCost,&temp->medicineStockQuantity, temp->medicineType, temp->medicineDosage);
            temp->next = pharmacyHead;
            pharmacyHead = temp;
        }
        else if (strcmp(section, "ROOM_DATA") == 0)
        {
            Room *temp = (Room *)malloc(sizeof(Room));
            sscanf(line, "%d,%[^,],%d,%d,%[^,],%f", &temp->roomId, temp->roomType, &temp->bedCount,&temp->availableBeds, temp->bedStatus, &temp->roomFee);
            temp->next = roomHead;
            roomHead = temp;
        }
        else if (strcmp(section, "BILL_DATA") == 0)
        {
            Bill *temp = (Bill *)malloc(sizeof(Bill));
            sscanf(line, "%d,%d,%d,%f,%f,%f,%f,%s", &temp->billId, &temp->patientId, &temp->treatmentId,&temp->consultationFee, &temp->pharmacyFee, &temp->roomFee,&temp->totalBillAmount, temp->billDate);
            temp->next = billHead;
            billHead = temp;
        }
    }

    fclose(file);
    printf("All data loaded successfully!\n");
    return SUCCESS;
}
