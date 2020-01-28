#ifndef _MSG_H_
#define _MSG_H_

#include "all.hpp"

namespace report {
    extern int num_errors;

    void error(const std::string& msg, const std::string& note = "");

    void summary();
}

#endif /* _MSG_H_ */