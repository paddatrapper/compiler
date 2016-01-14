/**
 *    Description:  Handles output of compile
 *        Version:  1.0
 *        Created:  14/01/2016 14:57:32
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), paddatrapper@gmail.com
 */
#ifndef _OUTPUT_H
#define _OUTPUT_H
namespace compiler {
class Output
{
    public:
        Output() {};
        void emit(std::string message);
        void emitLine(std::string message);
    private:
        char look;
        FILE *stream;
};
}
#endif
