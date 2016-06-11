#include "../include/error.h"

Error::Error() {}

const std::string Error::ERROR_NUM_OF_ARGS = "wrong number of arguments.";

void Error::error_num_of_args() {
  std::cout << Error::ERROR_NUM_OF_ARGS << std::endl;
}
