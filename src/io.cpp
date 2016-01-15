/**
 *    Description:  Handles all IO of the compiler
 *        Version:  1.0
 *        Created:  14/01/2016 13:31:56
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), paddatrapper@gmail.com
 */
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

    char Input::getName()
    {
        if (!Cradle::isAlpha(look)) {
            Reporter::expected("Name", getChar());
        }
        char currentChar = getChar();
        getNextChar();
        return currentChar;
    }

    char Input::getNum()
    {
        if (!Cradle::isDigit(look)) {
            Reporter::expected("Integer", getChar());
        }
        char currentChar = getChar();
        getNextChar();
        return currentChar;
    }

    void Input::match(char c)
    {
        if (getChar() == c)
            getNextChar();
        else {
            Reporter::expected("'" + Cradle::toString(c) + "'", getChar());
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

    void Reporter::expected(std::string message, char found)
    {
        abort(message + " Expected, but " + Cradle::toString(found) + " found");
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
