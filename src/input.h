/**
 *    Description:  Manages the input
 *        Version:  1.0
 *        Created:  14/01/2016 13:53:04
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), paddatrapper@gmail.com
 */
#ifndef _INPUT_H
#define _INPUT_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

namespace compiler {

class Input
{
    public:
        enum Symbol {
            IF_SYM,
            ELSE_SYM,
            ENDIF_SYM,
            END_SYM,
            VARIABLE,
            NUMBER,
            OPERATOR
        };

        typedef std::pair<Input::Symbol, std::string> symbol_t;

        Input(FILE *stream);
        void getNextChar();
        char getChar();
        std::pair<Input::Symbol, std::string> scan();
        std::string getName();
        std::string getNum();
        std::string getOp();
        bool getBoolean();
        std::string getKeyword(int code);
        int getKeywordCode(std::string keyword);

        void skipWhite();
        void skipComma();

        void match(char c);
    private:
        std::vector<std::string> keywords;
        char look;
        FILE *stream;

        void initKeywords();
};
}
#endif
