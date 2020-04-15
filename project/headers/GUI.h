//
// Created by mihail on 15.04.2020.
//

#ifndef CODESHARE_GUI_H
#define CODESHARE_GUI_H


#include "ClientTextManager.h"

class GUI {
public:
    GUI();
    bool displayContentToTextBox();
private:
    ClientTextManager textManager;
};


#endif //CODESHARE_GUI_H
