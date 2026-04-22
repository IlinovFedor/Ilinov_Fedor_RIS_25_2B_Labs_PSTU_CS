#include "Dialog.h"
#include <iostream>
#include "Magazine.h"

Dialog::Dialog() : Vector() {
    EndState = 0;
}

Dialog::~Dialog() {
}

void Dialog::GetEvent(Event &event) {
    std::string OpInt = "+-s/qam";
    std::string s;
    std::string param;
    char code;
    std::cout << "> ";
    std::cin >> s;
    code = s[0];
    if (OpInt.find(code) >= 0)
    {
        std::string param;
        event.what = evMessage;
        switch (code) {
            case 'm': {
                std::cout << "Size? ";
                std::cin >> param;
                event.a = atoi(param.c_str());
                event.command = cmMake;
                break;
            }
            case '+': {
                std::cout << "Type? Magazine (m) Print (p) ";
                std::cin >> param;
                if (param[0] != typeMagazine && param[0] != typePrint) {
                    std::cout << "Unknown type\n";
                    event.what = evNothing;
                    break;
                }
                event.command = cmAdd;
                event.a = param[0];
                break;
            }
            case '-': {
                std::cout << "Number? ";
                std::cin >> param;
                event.a = atoi(param.c_str());
                event.a--;
                event.command = cmDel;
                break;
            }
            case 's':
                event.command = cmShow;
                break;
            case'q':
                event.command = cmQuit;
                break;
            case 'z':
                event.command = cmShowNames;
                break;
        }
    } else {
        event.what = evNothing;
        std::cout << "Unknown command\n";
    }
}

int Dialog::Execute() {
    Event event;
    do {
        EndState = 0;
        GetEvent(event);
        handleEvent(event);
    } while (!Valid());
    return EndState;
}

int Dialog::Valid() {
    if (EndState == 0) return 0;
    return 1;
}

void Dialog::ClearEvent(Event &event) {
    event.what = evNothing;
}

void Dialog::EndExec() {
    EndState = 1;
}

void Dialog::handleEvent(Event &event) {
    if (event.what == evMessage) {
        switch (event.command) {
            case cmMake:
                size = event.a;
                beg = new Object *[size];
                cur = 0;
                ClearEvent(event);
                break;
            case cmAdd:
            {
                switch (event.a) {
                    case typePrint: {
                        Print *p = new Print;
                        std::cin >> *p;
                        add(p);
                        break;
                    }
                    case typeMagazine:{
                        Magazine *p = new Magazine;
                        std::cin >> *p;
                        add(p);
                        break;
                    }
                }
                ClearEvent(event);
                break;
            }
            case cmDel:
                remove(event.a);
                ClearEvent(event);
                break;
            case cmShow:
                std::cout << *this;
                ClearEvent(event);
                break;
            case cmQuit: EndExec();
                ClearEvent(event);
                break;
            case cmShowNames: {
                for (int i = 0; i < cur; i++) {
                    std::cout << i + 1 << ' ' << beg[i]->getName() << '\n';
                }
            }
            default: Vector::handleEvent(event);
        };
    };
}
