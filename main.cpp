/* ========================================================================
   $File: main.cpp $
   $Date: Apr 04 2020 $
   $Revision: $
   $Creator: Creative GP $
   $Notice: (C) Copyright 2020 by Creative GP. All Rights Reserved. $
   ======================================================================== */

#include <iostream>
#include <unistd.h>

#include <vector>

#include "greatpanel.h"

using namespace std;

int main() {
    GreatPanel::Panel panel;
    panel.init(600, 400, "hello");

    GreatPanel::Canvas cvs(100,100,10, 10);

    panel.open();
    sleep(2);
        for (int i = 0; i < 10 * 10; ++i) {
        cvs.pixels()[i] = 0xffffffff;
    }
    cvs.blit(panel.surface);
    sleep(2);
    panel.close();
    
    return 0;
}
