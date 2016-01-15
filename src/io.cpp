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

    std::string Input::getName()
    {
        if (!Cradle::isAlpha(getChar()))
            Reporter::expected("Name", getChar());
        std::string token = "";
        while (Cradle::isAlpha(getChar())) {
            token += Cradle::toString(getChar());
            getNextChar();
        }
        skipWhite();
        return token;
    }

    int Input::getNum()
    {
        int value = 0;
        if (!Cradle::isDigit(getChar())) {
            Reporter::expected("Integer", getChar());
        }
        while (Cradle::isDigit(getChar())) {
            value = 10 * value + (getChar() - OFFSET);
            getNextChar();
        }
        skipWhite();
        return value;
    }

    void Input::match(char c)
    {
        if (getChar() == c) {
            getNextChar();
            skipWhite();
        } else {
            Reporter::expected("'" + Cradle::toString(c) + "'", getChar());
        }
    }

    void Input::skipWhite()
    {
        while (Cradle::isWhite(getChar()))
            getNextChar();
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

    void Reporter::expected(std::string message, char c)
    {
        abort(message + " Expected, but found " + Cradle::toString(c));
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
