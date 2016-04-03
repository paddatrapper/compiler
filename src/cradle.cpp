/**
 *    Description:  Compiler boiler plate.
 *        Version:  1.0
 *        Created:  14/01/2016 08:05:04
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), paddatrapper@gmail.com
 */

#include <ctype.h>
#include <iostream>
#include <sstream>
#include "cradle.h"

namespace compiler {
    bool Cradle::isAlpha(char c)
    {
        return (bool) isalpha(c);
    }

    bool Cradle::isDigit(char c)
    {
        return (bool) isdigit(c);
    }

    bool Cradle::isAlNum(char c)
    {
        return isAlpha(c) || isDigit(c);
    }

    bool Cradle::isBoolean(char c)
    {
        return toupper(c) == 'T' || toupper(c) == 'F';
    }

    bool Cradle::isWhite(char c)
    {
        return isspace(c);
    }

    bool Cradle::isOp(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/' ||
            c == '<' || c == '>' || c == '=';
    }

    std::string Cradle::toString(char c)
    {
        std::stringstream ss;
        std::string string;
        ss << c;
        ss >> string;
        return string;
    }

    std::string Cradle::toString(bool b)
    {
        std::stringstream ss;
        std::string string;
        ss << b;
        ss >> string;
        return string;
    }

    std::string Cradle::toString(int n)
    {
        std::stringstream ss;
        std::string string;
        ss << n;
        ss >> string;
        return string;
    }

    bool Cradle::isAddOp(char c)
    {
        return c == '+' ||
            c == '-';
    }

    bool Cradle::isMulOp(char c)
    {
        return c == '*' ||
            c == '/';
    }

    bool Cradle::isParentheses(char c)
    {
        return c == '(' ||
            c == ')';
    }

    bool Cradle::isOrOp(char c)
    {
        return c == '|' ||
            c == '~';
    }

    bool Cradle::isRelOp(char c)
    {
        return c == '=' ||
            c == '#' ||
            c == '<' ||
            c == '>';
    }
}
