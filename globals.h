#ifndef GLOBALS_H
#define GLOBALS_H
#include "patient.h"
#include "doctor.h"
#include "staff.h"
#include "treatment.h"
#include"pharmacy.h"
#include"room.h"
#include "bill.h"

extern Patient *patientHead;
extern Doctor *doctorHead;
extern Staff *staffHead;
extern Treatment *treatmentHead;
extern Pharmacy *pharmacyHead;
extern Room *roomHead;
extern Bill *billHead;

#endif // GLOBALS_H
