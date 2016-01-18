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
                default:
                    other();
                    break;
            }
        }
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

    void Parser::condition()
    {
        output.emitLine("<condition>");
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
int main(int argc, char *argv[])
{
    compiler::Parser parser{};
    parser.program();
    return EXIT_SUCCESS;
}
