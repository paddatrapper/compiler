/**
 *    Description:  Compiler boiler plate
 *        Version:  1.0
 *        Created:  14/01/2016 08:05:37
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), paddatrapper@gmail.com
 */

#ifndef _CRADLE_H
#define _CRADLE_H

#include <string>
#include <stdio.h>
#include "input.h"
#include "output.h"


namespace compiler {
class Cradle
{
    public:
        Cradle() {};
        static bool isAlpha(char c);
        static bool isDigit(char c);
        static bool isAlNum(char c);
        static bool isWhite(char c);
        static std::string toString(char c);
        static std::string toString(int x);
        static bool isAddOp(char c);
        static bool isMulOp(char c);
        static bool isParentheses(char c);
    private:
        Output output{};
};
}
#endif
