/**
 *    Description:  Translates expressions into assembly
 *        Version:  1.0
 *        Created:  14/01/2016 10:25:20
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), paddatrapper@gmail.com
 */
#ifndef _TRANSLATOR_H
#define _TRANSLATOR_H

#include <string>
#include "input.h"
#include "output.h"

namespace compiler {
class Parser
{
    public:
        Parser() {};
        void program();
        void block(std::string l);
        void condition();
        void expression();
        void relation();
        void variable();

        void equals();
        void notEquals();
        void lessThan();
        void greaterThan();

        void multiply();
        void divide();
        void add();
        void subtract();
        void term();
        void factor();
        void signedFactor();

        void boolExpression();
        void boolOr();
        void boolXor();
        void boolTerm();
        void boolFactor();
        void boolNotFactor();

        void doIf(std::string l);
        void doLoop();
        void doWhile();
        void doDoWhile();
        void doFor();
        void doDo();
        void doBreak(std::string l);

        void other();
    private:
        std::string newLabel();

        Input input{stdin};
        Output output;
        int labelCount{0};
};
}
#endif
