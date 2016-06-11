#ifndef INCLUDE_ERROR_H_
#define INCLUDE_ERROR_H_

#include <iostream>
#include <string>

class Error {
  public:
    Error();
    static const std::string ERROR_NUM_OF_ARGS;
    void error_num_of_args();
};

#endif
