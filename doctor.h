
#ifndef DOCTOR_H
#define DOCTOR_H


typedef struct doctor
{
    int doctorId;
    char doctorName[100];
    char doctorSpecialization[20];
    float doctorConsultationFee;
    char doctorContactNumber[15];
    int doctorExperience;
    char doctorQualification[50];
    struct doctor *next;
} Doctor;
extern Doctor *doctorHead ;

enum DoctorManagementMenu
{
    ADD_DOCTOR = 1,
    UPDATE_DOCTOR_DETAILS,
    DISPLAY_AVAILABLE_DOCTORS,
    SEARCH_DOCTOR_BY_ID,
    SEARCH_DOCTOR_BY_SPECIALIZATION,
    EXIT_DOCTOR_MANAGEMENT
} ;

enum DoctorUpdateDetail
{
    UPDATE_DOCTOR_NAME=1,
    UPDATE_DOCTOR_SPECIALIZATION,
    UPDATE_DOCTOR_CONSULTATION_FEE,
    UPDATE_DOCTOR_CONTACT_NUMBER,
    UPDATE_DOCTOR_EXPERIENCE,
    UPDATE_DOCTOR_QUALIFICATION
};



void verifyDoctorManagementUser();
void addDoctor();
void updateDoctorDetails();
void displayDoctorDetails();
void searchByDoctorId();
void searchByDoctorSpecialization();




#endif // DOCTOR_H


