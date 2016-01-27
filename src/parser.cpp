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
        block();
        if (input.getChar() != '}')
            Reporter::expected("End", input.getChar());
        output.emitLine("END");
    }

    void Parser::block()
    {
        while (input.getChar() != '}') {
            switch (input.getChar()) {
                case 'i':
                    doIf();
                    break;
                case 'w':
                    doWhile();
                    break;
                case 'l':
                    doLoop();
                    break;
                case 'd':
                    doDoWhile();
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

    void Parser::doIf()
    {
        input.match('i');
        std::string l1 = newLabel();
        std::string l2 = l1;
        condition();
        output.emitLine("BEQ " + l1);
        input.match('{');
        block();
        input.match('}');
        if (input.getChar() == 'e') {
            input.match('e');
            l2 = newLabel();
            output.emitLine("BRA " + l2);
            output.postLabel(l1);
            input.match('{');
            block();
            input.match('}');
        }
        output.postLabel(l2);
    }

    void Parser::doLoop()
    {
        input.match('l');
        std::string l = newLabel();
        output.postLabel(l);
        input.match('{');
        block();
        input.match('}');
        output.emitLine("BRA " + l);
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
        block();
        input.match('}');
        output.emitLine("BRA " + l1);
        output.postLabel(l2);
    }

    void Parser::doDoWhile()
    {
        input.match('d');
        std::string l = newLabel();
        input.match('{');
        output.postLabel(l);
        block();
        input.match('}');
        input.match('w');
        condition();
        output.emitLine("BEQ " + l);
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
    parser.program();
    return EXIT_SUCCESS;
}
