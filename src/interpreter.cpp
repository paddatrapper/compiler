/**
 *    Description:  Interpreter version of the compiler
 *        Version:  1.0
 *        Created:  14/01/2016 19:46:16
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), paddatrapper@gmail.com
 */

#include <stdlib.h>
#include "cradle.h"
#include "input.h"
#include "interpreter.h"
#include "output.h"
#include "reporter.h"

namespace compiler {
    int Interpreter::expression()
    {
        int value;
        if (Cradle::isAddOp(input.getChar()))
            value = 0;
        else 
            value = term();
        while (Cradle::isAddOp(input.getChar())) {
            switch (input.getChar()) {
                case '+': 
                    input.match('+');
                    value += term();
                    break;
                case '-':
                    input.match('-');
                    value -= term();
                    break;
            }
        }
        return value;
    } 

    int Interpreter::term()
    {
        int value;
        if (Cradle::isMulOp(input.getChar()))
            value = 0;
        else 
            value = factor();
        while (Cradle::isMulOp(input.getChar())) {
            switch (input.getChar()) {
                case '*': 
                    input.match('*');
                    value *= factor();
                    break;
                case '/':
                    input.match('/');
                    value /= factor();
                    break;
            }
        }
        return value;
    } 

    int Interpreter::factor()
    {
        if (input.getChar() == '(') {
            input.match('(');
            int value = expression();
            input.match(')');
            return value;
        } else {
            return input.getNum();
        }
    }
}
