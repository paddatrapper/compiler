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

namespace compiler {
class Input
{
    public:
        Input(FILE *stream);
        void getNextChar();
        char getChar();
        std::string getName();
        std::string getNum();
        void skipWhite();
        void match(char c);
    private:
        char look;
        FILE *stream;
};
}
#endif
