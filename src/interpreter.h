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

#include <string>
#include <map>
#include "cradle.h"
#include "input.h"
#include "output.h"

namespace compiler {
class Interpreter
{
    public:
        Interpreter() {};
        void nextLine();
        void assignment();
        int expression();
        int term();
        int factor();
        void userInput();
        void screenOutput();
        bool isNewLine();
        void newLine();
    private:
        typedef std::map<std::string, int> var_t;
        const int CHAR_OFFSET = static_cast<int>('0');
        var_t variables;
        Input input{stdin};
        Output output{};
};
}
#endif
