#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsUtiil.h"
#include "clsMainScreen.h"
#include "clsLoginScreen.h"
#include "clsDate.h"
using namespace std;

int main(){
    while (true) {
        if (!clsLoginScreen::ShowLoginScreen()) {
            break;
        }
    }
     
    //clsMainScreen::ShowMainMenue();
}

