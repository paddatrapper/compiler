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
#include <utility>

#include "cradle.h"
#include "input.h"
#include "output.h"
#include "reporter.h"

namespace compiler {
    Input::Input(FILE *stream)
    {
        this->stream = stream;
        initKeywords();
        getNextChar();
    }

    void Input::initKeywords()
    {
        keywords.push_back("if");
        keywords.push_back("else");
        keywords.push_back("endif");
        keywords.push_back("end");
    }

    void Input::getNextChar()
    {
        look = getc(stream);
    }

    char Input::getChar()
    {
        return look;
    }

    Input::symbol_t Input::scan()
    {
        while (getChar() == '\n') {
            skipWhite();
        }
        Symbol token;
        std::string value;
        if (Cradle::isAlpha(getChar())) {
            value = getName();
            int k = getKeywordCode(value);
            if (k == -1) {
                token = Symbol::VARIABLE;
            } else {
                token = static_cast<Symbol>(k);
            }
        } else if (Cradle::isDigit(getChar())) {
            token = Symbol::NUMBER;
            value = getNum();
        } else if (Cradle::isOp(getChar())) {
            token = Symbol::OPERATOR;
            value = getOp();
        } else {
            token = Symbol::OPERATOR;
            char c = getChar();
            getNextChar();
            value = Cradle::toString(c);
        }
        skipWhite();
        return std::make_pair (token, value);
    }

    std::string Input::getName()
    {
        if (!Cradle::isAlpha(getChar())) {
            Reporter::expected("Name", getChar());
        }
        std::string name = "";
        while (Cradle::isAlNum(getChar())) {
            name += getChar();
            getNextChar();
        }
        skipWhite();
        return name;
    }

    std::string Input::getNum()
    {
        if (!Cradle::isDigit(getChar())) {
            Reporter::expected("Integer", getChar());
        }
        std::string num = "";
        while (Cradle::isDigit(getChar())) {
            num += getChar();
            getNextChar();
        }
        skipWhite();
        return num;
    }

    bool Input::getBoolean()
    {
        if (!Cradle::isBoolean(getChar())) {
            Reporter::expected("Boolean literal", getChar());
        }
        bool b = toupper(getChar()) == 'T';
        getNextChar();
        return b;
    }

    std::string Input::getKeyword(int code)
    {
        return keywords[code];
    }

    int Input::getKeywordCode(std::string keyword)
    {
        for (unsigned int i = 0; i < keywords.size(); i++) {
            if (keywords[i] == keyword) {
                return (signed int) i;
            }
        }
        return -1;
    }

    std::string Input::getOp()
    {
        if (!Cradle::isOp(getChar())) {
            Reporter::expected("Operator", getChar());
        }
        std::string op = "";
        while (Cradle::isOp(getChar())) {
            op += getChar();
            getNextChar(); 
        }
        skipWhite();
        return op;
    }

    void Input::skipWhite()
    {
        while (Cradle::isWhite(getChar())) {
            getNextChar();
        }
    }

    void Input::skipComma()
    {
        if (getChar() == ',') {
            getNextChar();
            skipWhite();
        }
    }

    void Input::match(char c)
    {
        if (getChar() != c)
            Reporter::expected("'" + Cradle::toString(c) + "'", getChar());
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

    void Output::postLabel(std::string label)
    {
        emitLine(label + ":");
    }
}
/**
 * Main
 */
int main()
{
    compiler::Input input{stdin};
    while(input.getChar() != compiler::Input::Symbol::END_SYM) {
        compiler::Input::symbol_t token = input.scan();
        switch (token.first) {
            case compiler::Input::Symbol::VARIABLE:
                std::cout << "Variable\n";
                break;
            case compiler::Input::Symbol::NUMBER:
                std::cout << "Number\n";
                break;
            default:
                std::cout << "Keyword\n";
                break;
        }
    }
    return EXIT_SUCCESS;
}
