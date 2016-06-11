#ifndef INCLUDE_ERROR_H_
#define INCLUDE_ERROR_H_

#include <iostream>
#include <string>

class Error {
  public:
    Error();
    static const std::string ERROR_NUM_OF_ARGS;
    static const std::string ERROR_INVALID_ARGS;
    static const std::string ERROR_NOT_FOUND_COMMAND;
    void error_num_of_args();
    void error_invalid_args();
    void error_not_found_command();
};

#endif
