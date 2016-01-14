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
        skipWhite();
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
        if (!Cradle::isAlpha(getChar())) {
            Reporter::expected("Name", getChar());
        }
        std::string token {""};
        while (Cradle::isAlNum(getChar())) {
            token += Cradle::toString(toupper(getChar()));
            getNextChar();
            skipWhite();
        }
        return token;
    }

    std::string Input::getNum()
    {
        if (!Cradle::isDigit(getChar())) {
            Reporter::expected("Integer", getChar());
        }
        std::string token {""};
        while (Cradle::isDigit(getChar())) {
            token += Cradle::toString(getChar());
            getNextChar();
            skipWhite();
        }
        return token;
    }

    void Input::skipWhite()
    {
        while (Cradle::isWhite(getChar()))
        {
            getNextChar();
        }
    }

    void Input::match(char c)
    {
        if (getChar() != c)
            Reporter::expected("'" + Cradle::toString(c) + "'", getChar());
        getNextChar();
        skipWhite();
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

    void Reporter::expected(std::string message, char expected)
    {
        abort(message + " Expected, but " + Cradle::toString(expected) + " found.");
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
