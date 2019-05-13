#ifndef GAMMER_H_INCLUDED
#define GAMMER_H_INCLUDED

#include <iostream>


typedef int status_t;

namespace grammer{
    #define STATUS_SUCCEED 0
    #define STATUS_FAILED  1

    const int BUFF_SIZE = 2048;
    extern char buffer[BUFF_SIZE];

    extern char *cur;
    extern char *dest;
    extern std::istream __in;

    extern void initiation(std::basic_streambuf<char> *stream);
    extern void load(int len);
    extern void next();
    extern void error(char *message);
    extern void message(char *message);

    class grammer{
        public:
            status_t E();
            status_t T();
            status_t E_();
            status_t F();
            status_t T_();
            status_t F_();
            status_t P();
    };
}

#endif // GAMMER_H_INCLUDED
