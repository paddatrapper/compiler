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

#include "cradle.h"
#include "input.h"
#include "output.h"

namespace compiler {
class Translator
{
    public:
        Translator() {};
        void expression();
        void assignment();
        void term();
        void factor();
        void indent();
        void add();
        void subtract();
        void multiply();
        void divide();
    protected:
    private:
        Input input{stdin};
        Output output{};
};
}
#endif
