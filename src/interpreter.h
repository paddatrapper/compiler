/**
 *    Description:  Translates expressions into assembly
 *        Version:  1.0
 *        Created:  14/01/2016 10:25:20
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), paddatrapper@gmail.com
 */
#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "cradle.h"
#include "input.h"
#include "output.h"

namespace compiler {
class Interpreter
{
    public:
        Interpreter() {};
        int expression();
        //void assignment();
        //void term();
        //void factor();
        //void indent();
        void add();
        void subtract();
        //void multiply();
        //void divide();
    private:
        const int OFFSET = 48;
        Input input{stdin};
        Output output{};
};
}
#endif
