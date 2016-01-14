/**
 *    Description:  Handles all IO of the compiler
 *        Version:  1.0
 *        Created:  14/01/2016 13:31:56
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), paddatrapper@gmail.com
 */
#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include "cradle.h"
#include "input.h"
#include "output.h"
#include "reporter.h"

namespace compiler {
    Input::Input(FILE *stream)
    {
        this->stream = stream;
        getNextChar();
    }

    void Input::getNextChar()
    {
        look = getc(stream);
    }

    char Input::getChar()
    {
        return look;
    }

    std::string Input::getName()
    {
        if (!Cradle::isAlpha(look)) {
            Reporter::expected("Name");
        }
        std::string token {""};
        while (Cradle::isAlNum(look)) {
            token += Cradle::toString(toupper(look));
            getNextChar();
        }
        return token;
    }

    std::string Input::getNum()
    {
        if (!Cradle::isDigit(look)) {
            Reporter::expected("Integer");
        }
        std::string token {""};
        while (Cradle::isDigit(look)) {
            token += Cradle::toString(look);
            getNextChar();
        }
        return token;
    }

    void Input::match(char c)
    {
        if (getChar() == c)
            getNextChar();
        else {
            Reporter::expected("'" + Cradle::toString(c) + "'");
        }
    }

    void Reporter::error(std::string message)
    {
        std::cerr << "Error: " << message << '\n';
    }

    void Reporter::abort(std::string message)
    {
        error(message);
        exit(EXIT_FAILURE);
    }

    void Reporter::expected(std::string message)
    {
        abort(message + " Expected");
    }

    
    void Output::emit(std::string message)
    {
        std::cout << '\t' << message;
    }

    void Output::emitLine(std::string message)
    {
        emit(message);
        std::cout << '\n';
    }
}
