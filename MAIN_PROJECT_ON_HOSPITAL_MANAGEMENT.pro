TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bill.c \
        doctor.c \
        globals.c \
        main.c \
        menu.c \
        patient.c \
        pharmacy.c \
        room.c \
        staff.c \
        treatment.c

HEADERS += \
    bill.h \
    doctor.h \
    globals.h \
    menu.h \
    patient.h \
    pharmacy.h \
    room.h \
    staff.h \
    treatment.h