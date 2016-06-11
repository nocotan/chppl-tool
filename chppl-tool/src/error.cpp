#include "../include/error.h"

Error::Error() {}

const std::string Error::ERROR_NUM_OF_ARGS = "wrong number of arguments.";
const std::string Error::ERROR_INVALID_ARGS = "invalid arguments.";
const std::string Error::ERROR_NOT_FOUND_COMMAND = "not found such a command.";

void Error::error_num_of_args() {
  std::cout << Error::ERROR_NUM_OF_ARGS << std::endl;
}

void Error::error_invalid_args() {
  std::cout << Error::ERROR_INVALID_ARGS << std::endl;
}

void Error::error_not_found_command() {
  std::cout << Error::ERROR_NOT_FOUND_COMMAND << std::endl;
}
