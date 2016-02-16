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
        void block();
        void condition();
        void expression();
        void doIf();
        void doLoop();
        void doWhile();
        void doDoWhile();
        void doFor();
        void doDo();
        void other();
        std::string newLabel();
    private:
        Input input{stdin};
        Output output;
        int labelCount{0};
};
}
#endif
