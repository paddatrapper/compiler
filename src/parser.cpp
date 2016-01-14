/**
 *    Description:  Translates expressions into assembly
 *        Version:  1.0
 *        Created:  14/01/2016 10:30:17
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), paddatrapper@gmail.com
 */
#include <stdlib.h>
#include "cradle.h"
#include "input.h"
#include "output.h"
#include "reporter.h"
#include "parser.h"

namespace compiler {
    void Parser::expression()
    {
        if (Cradle::isAddOp(input.getChar()))
            output.emitLine("CLR D0");
        else
            term();
        while (Cradle::isAddOp(input.getChar())) {
            output.emitLine("MOVE D0,-(SP)");
            switch (input.getChar()) {
                case '+':
                    add();
                    break;
                case '-':
                    subtract();
                    break;
            }
        }

        if (input.getChar() != '\n')
            Reporter::expected("New line");
    }

    void Parser::assignment()
    {
        char name = input.getName();
        input.match('=');
        expression();
        output.emitLine("LEA " + Cradle::toString(name) + "(PC),A0");
        output.emitLine("MOVE D0,(A0)");
    }

    void Parser::term()
    {
        factor();
        while (Cradle::isMulOp(input.getChar())) {
            output.emitLine("MOVE D0,-(SP)");
            switch (input.getChar()) {
                case '*':
                    multiply();
                    break;
                case '/':
                    divide();
                    break;
            }
        }
    }

    void Parser::factor()
    {
        if (Cradle::isParentheses(input.getChar())) {
            input.match('(');
            expression();
            input.match(')');
        } else if (Cradle::isAlpha(input.getChar())) {
            indent();
        } else {
            output.emitLine("MOVE #" + Cradle::toString(input.getNum())
                    + ",D0");
        }
    }

    void Parser::indent()
    {
        char name = input.getName();
        if (input.getChar() == '(') {
            input.match('(');
            input.match(')');
            output.emitLine("BSR " + Cradle::toString(name));
        } else {
            output.emitLine("MOVE " + Cradle::toString(name) 
                   + "(PC),D0");
        }
    }

    void Parser::add()
    {
        input.match('+');
        term();
        output.emitLine("ADD (SP)+,D0");
    }

    void Parser::subtract()
    {
        input.match('-');
        term();
        output.emitLine("SUB (SP)+,D0");
        output.emitLine("NEG D0");
    }

    void Parser::multiply()
    {
        input.match('*');
        factor();
        output.emitLine("MULS (SP)+,D0");
    }

    void Parser::divide()
    {
        input.match('/');
        term();
        output.emitLine("MOVE (SP)+,D1");
        output.emitLine("DIVS (SP)+,D1");
    }
}
/**
 * Main
 */
int main(int argc, char *argv[])
{
    compiler::Parser parser{};
    parser.assignment();
    return EXIT_SUCCESS;
}
