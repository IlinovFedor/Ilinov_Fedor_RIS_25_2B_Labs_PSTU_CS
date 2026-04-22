#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_EVENT_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_EVENT_H


const int evNothing = 0;
const int evMessage = 100;
const int cmAdd = 1;
const int cmDel = 2;
const int cmShow = 4;
const int cmShowNames = 5;
const int cmMake = 6;
const int cmQuit = -1;

const int typeMagazine = 'm';
const int typePrint = 'p';

struct Event {
    int what;
    union {
        int command;
        struct {
            int message;
            int a;
        };
    };
};


#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_EVENT_H
