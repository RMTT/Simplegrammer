#include "gammer.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

namespace grammer {
    std::istream __in(0);
    char buffer[BUFF_SIZE];

    char *cur = buffer;
    char *dest = buffer;

    void initiation(std::basic_streambuf<char> *stream) {
        cur = buffer;
        dest = buffer;
        __in.rdbuf(stream);
        load(BUFF_SIZE);
    }

    void load(int len) {
        for (unsigned int i = 0; i < len; i++) {
            char c = (char) __in.get();
            *dest++ = c;
            if (c == EOF)
                break;
        }
    }

    void next() {
        if (cur == (buffer + BUFF_SIZE)) {
            cur = buffer;
            dest = buffer;
            load(BUFF_SIZE);
        }
        cur++;
    }

    void error(char *message) {
        cout << message << "\n";
    }

    void message(char *message) {
        cout << message << '\n';
    }

    status_t grammer::E() {
        status_t res = STATUS_SUCCEED;

        res |= T();
        if (res == STATUS_FAILED){
            error("Something error in T of E=TE'");
            return res;
        }
        res |= E_();
        if (res == STATUS_FAILED){
            error("Something error in E' of E=TE'");
            return res;
        }
        return res;
    }

    status_t grammer::T() {
        status_t res = STATUS_SUCCEED;
        res |= F();

        if (res == STATUS_FAILED){
            error("Something error in F of T=FT'");
            return res;
        }

        res |= T_();
        if (res == STATUS_FAILED){
            error("Something error in T' of T=FT'");
            return res;
        }
        return res;
    }

    status_t grammer::E_() {
        status_t res = STATUS_SUCCEED;
        if (*cur == '+') {
            next();
            res |= E();
            if (res == STATUS_FAILED){
                error("Something error in E of E'=+E|Epsilon");
                return res;
            }
        }
        return res;
    }

    status_t grammer::F() {
        status_t res = STATUS_SUCCEED;

        res |= P();
        if (res == STATUS_FAILED) {
            error("Something error in P of F=PF'");
            return res;
        }
        res |= F_();
        if (res == STATUS_FAILED) {
            error("Something error in F' of F=PF'");
            return res;
        }
        return res;
    }

    status_t grammer::T_() {
        char *tmp = cur;
        status_t t = T();
        if (t == STATUS_FAILED) {
            message("if some error info print above,you can ignore it.");
            cur = tmp;
        }

        return STATUS_SUCCEED;
    }

    status_t grammer::F_() {
        status_t res = STATUS_SUCCEED;
        if (*cur == '*') {
            next();
            res |= F_();
            if (res == STATUS_FAILED)
                error("Something error in *F' of F'=*F'|Epsilon");
        }
        return res;
    }

    status_t grammer::P() {
        status_t res = STATUS_SUCCEED;
        if (*cur == '(') {
            res |= E();
            next();
            if (*cur == ')')
                res |= STATUS_SUCCEED;
            else {
                error("Lacking corresponding character ')' in P");
                res |= STATUS_FAILED;
            }
        } else if (*cur == 'a')
            res |= STATUS_SUCCEED;
        else if (*cur == 'b')
            res |= STATUS_SUCCEED;
        else if (*cur == '^')
            res |= STATUS_SUCCEED;
        else {
            error("Lacking corresponding character 'a | b | ^' in P");
            return STATUS_FAILED;
        }
        next();
        return res;
    }
}
