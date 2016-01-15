/**
 *    Description:  main entry point for the compiler or interpreter.
 *        Version:  1.0
 *        Created:  14/01/2016 19:56:54
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), paddatrapper@gmail.com
 */

#include <stdlib.h>
#include <iostream>
#include "parser.h"
#include "interpreter.h"

/**
 * Main
 */
int main(int argc, char *argv[])
{
    //compiler::Parser parser{};
    //parser.assignment();
    compiler::Interpreter interpreter{};
    while (interpreter.isNewLine()) {
        interpreter.nextLine();
    }
    return EXIT_SUCCESS;
}
