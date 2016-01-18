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

#include <iostream>

namespace compiler {
    void Parser::program()
    {
        block();
        if (input.getChar() != 'e')
            Reporter::expected("End", input.getChar());
        output.emitLine("END");
    }

    void Parser::block()
    {
        while (input.getChar() != 'e')
            other();
    }

    void Parser::other()
    {
        output.emitLine(Cradle::toString(input.getName()));
        input.getNextChar();
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
