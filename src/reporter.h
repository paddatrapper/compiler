/**
 *    Description:  Prints out messages on screen
 *        Version:  1.0
 *        Created:  14/01/2016 13:27:07
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), paddatrapper@gmail.com
 */
#ifndef REPORTER_H
#define REPORTER_H

#include <string>

namespace compiler {
class Reporter
{
    public:
        Reporter();
        static void error(std::string message);
        static void abort(std::string message);
        static void expected(std::string message, char expected);
};
}
#endif
