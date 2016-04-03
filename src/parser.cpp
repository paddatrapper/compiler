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
    void Parser::program()
    {
        input.match('{');
        block("");
        if (input.getChar() != '}')
            Reporter::expected("End", input.getChar());
        output.emitLine("END");
    }

    void Parser::block(std::string l)
    {
        while (input.getChar() != '}') {
            switch (input.getChar()) {
                case 'i':
                    doIf(l);
                    break;
                case 'w':
                    doWhile();
                    break;
                case 'l':
                    doLoop();
                    break;
                case 'r':
                    doDoWhile();
                    break;
                case 'f':
                    doFor();
                    break;
                case 'd':
                    doDo();
                    break;
                case 'b':
                    doBreak(l);
                    break;
                default:
                    other();
                    break;
            }
        }
    }

    void Parser::condition()
    {
        output.emitLine("<condition>");
    }

    void Parser::expression()
    {
        output.emitLine("<expression>");
        input.getNextChar();
    }

    void Parser::relation() 
    {
        expression();
        if (Cradle::isRelOp(input.getChar())) {
            output.emitLine("MOVE D0,(SP)-");
            switch (input.getChar()) {
                case '=':
                    equals();
                    break;
                case '#':
                    notEquals();
                    break;
                case '<':
                    lessThan();
                    break;
                case '>':
                    greaterThan();
                    break;
            }
            output.emitLine("TST D0");
        }
    }

    void Parser::equals()
    {
        input.match('=');
        expression();
        output.emitLine("CMP (SP)+,D0");
        output.emitLine("SEQ D0");
    }

    void Parser::notEquals()
    {
        input.match('#');
        expression();
        output.emitLine("CMP (SP)+,D0");
        output.emitLine("SNE D0");
    }

    void Parser::lessThan()
    {
        input.match('<');
        expression();
        output.emitLine("CMP (SP)+,S0");
        output.emitLine("SGE D0");
    }

    void Parser::greaterThan()
    {
        input.match('>');
        expression();
        output.emitLine("CMP (SP)+,S0");
        output.emitLine("SLE D0");
    }

    void Parser::boolExpression()
    {
        boolTerm();
        while (Cradle::isOrOp(input.getChar())) {
            output.emitLine("MOVE D0,-(SP)");
            switch (input.getChar()) {
                case '|':
                    boolOr();
                    break;
                case '~':
                    boolXor();
                    break;
            }
        }
    }

    void Parser::boolOr()
    {
        input.match('|');
        boolTerm();
        output.emitLine("OR (SP)+,D0");
    }

    void Parser::boolXor()
    {
        input.match('~');
        boolTerm();
        output.emitLine("EOR (SP)+,D0");
    }

    void Parser::boolTerm()
    {
        boolNotFactor();
        while (input.getChar() == '&') {
            output.emitLine("MOVE D0,-(SP)");
            input.match('&');
            boolNotFactor();
            output.emitLine("AND (SP)+,D0");
        }
    }

    void Parser::boolFactor()
    {
        if (Cradle::isBoolean(input.getChar())) {
            if (input.getBoolean()) {
                output.emitLine("MOVE #-1,D0");
            } else {
                output.emitLine("CLR D0");
            }
        } else {
            relation();
        }
    }

    void Parser::boolNotFactor()
    {
        if (input.getChar() == '!') {
            input.match('!');
            boolFactor();
            output.emitLine("EOR #-1,D0");
        } else {
            boolFactor();
        }
    }

    void Parser::doIf(std::string l)
    {
        input.match('i');
        std::string l1 = newLabel();
        std::string l2 = l1;
        condition();
        output.emitLine("BEQ " + l1);
        input.match('{');
        block(l);
        input.match('}');
        if (input.getChar() == 'e') {
            input.match('e');
            l2 = newLabel();
            output.emitLine("BRA " + l2);
            output.postLabel(l1);
            input.match('{');
            block(l);
            input.match('}');
        }
        output.postLabel(l2);
    }

    void Parser::doLoop()
    {
        input.match('l');
        std::string l1 = newLabel();
        std::string l2 = newLabel();
        output.postLabel(l1);
        input.match('{');
        block(l2);
        input.match('}');
        output.emitLine("BRA " + l1);
        output.postLabel(l2);
    }

    void Parser::doWhile()
    {
        input.match('w');
        std::string l1 = newLabel();
        std::string l2 = newLabel();
        output.postLabel(l1);
        condition();
        output.emitLine("BEQ " + l2);
        input.match('{');
        block(l2);
        input.match('}');
        output.emitLine("BRA " + l1);
        output.postLabel(l2);
    }

    void Parser::doDoWhile()
    {
        input.match('r');
        std::string l1 = newLabel();
        std::string l2 = newLabel();
        input.match('{');
        output.postLabel(l1);
        block(l2);
        input.match('}');
        input.match('w');
        condition();
        output.emitLine("BEQ " + l1);
        output.postLabel(l2);
    }

    void Parser::doFor()
    {
        input.match('f');
        std::string l1 = newLabel();
        std::string l2 = newLabel();
        input.match('(');
        char name = input.getName();
        input.match('=');
        expression();
        output.emitLine("SUBQ #1,D0");
        output.emitLine("LEA " + Cradle::toString(name) + "(PC),A0");
        output.emitLine("MOVE D0,-(SP)");
        output.postLabel(l1);
        output.emitLine("LEA " + Cradle::toString(name) + "(PC),A0");
        output.emitLine("MOVE (A0),D0");
        output.emitLine("ADDQ #1,D0");
        output.emitLine("MOVE D0,(A0)");
        output.emitLine("CMP (SP),D0");
        output.emitLine("BGT " + l2);
        input.match(')');
        input.match('{');
        block(l2);
        output.emitLine("BRA " + l1);
        output.postLabel(l2);
        output.emitLine("ADDQ #2,SP");
        input.match('}');
    }

    void Parser::doDo()
    {
        input.match('d');
        std::string l1 = newLabel();
        std::string l2 = newLabel();
        expression();
        output.emitLine("SUBQ #1,D0");
        output.postLabel(l1);
        output.emitLine("MOVE D0,-(SP)");
        block(l2);
        output.emitLine("MOVE (SP)+,D0");
        output.emitLine("DBRA D0," + l1);
        output.emitLine("SUBQ #2,SP");
        output.postLabel(l2);
        output.emitLine("ADDQ #2,SP");
    }

    void Parser::doBreak(std::string l)
    {
        input.match('b');
        if (l != "") {
            output.emitLine("BRA " + l);
        } else {
            Reporter::abort("No loop to break from");
        }
    }

    void Parser::other()
    {
        output.emitLine(Cradle::toString(input.getName()));
    }

    std::string Parser::newLabel()
    {
        return "L" + Cradle::toString(labelCount++);
    }
}
/**
 * Main
 */
int main()
{
    compiler::Parser parser{};
    parser.boolExpression();
    return EXIT_SUCCESS;
}
