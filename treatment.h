#ifndef TREATMENT_H
#define TREATMENT_H
typedef struct treatment
{
    int treatmentId;
    char treatmentName[100];
    int treatmentCost;
    int treatmentDuration;//in days
    struct treatment *next;
}Treatment;

enum TreatmentManagementOptions
{
    ADD_TREATMENT = 1,
    UPDATE_TREATMENT_DETAILS,
    DISPLAY_ALL_TREATMENTS,
    SEARCH_TREATMENT_BY_ID,
    SEARCH_TREATMENT_BY_NAME,
    EXIT_TREATMENT_MANAGEMENT
};

enum TreatmentUpdateOptions
{
    UPDATE_TREATMENT_ID = 1,
    UPDATE_TREATMENT_NAME,
    UPDATE_TREATMENT_COST,
    UPDATE_TREATMENT_DURATION
};



void verifyTreatmentAndPriceManagementUser();
void addTreatment();
void updateTreatmentDetails();
void displayTreatment();
void searchByTreatmentId();
void searchByTreatmentName();
void saveTreatmentData();
int loadTreatmentData();


#endif // TREATMENT_H

