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

#include <iostream>

namespace compiler {
    int Interpreter::expression()
    {
        int value;
        if (Cradle::isAddOp(input.getChar()))
            value = 0;
        else 
            value = input.getNum() - OFFSET;
        while (Cradle::isAddOp(input.getChar())) {
            switch (input.getChar()) {
                case '+': 
                    input.match('+');
                    value += input.getNum() - OFFSET;
                    break;
                case '-':
                    input.match('-');
                    value -= input.getNum() - OFFSET;
                    break;
            }
        }
        return value;
    } 
}
