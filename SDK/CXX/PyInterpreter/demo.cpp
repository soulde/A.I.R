// Created by lyjly on 2022/12/28.
//
#include "PyInterpreter.h"
int main(int argc, char** argv){
    PyInterpreter interpreter;
    char* cmd = "import pandas as pd\n";
    interpreter.runCommand(cmd);
    interpreter.import("pandas");

    return 0;

}