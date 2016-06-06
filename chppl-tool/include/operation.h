#ifndef OPERATION_H_
#define OPERATION_H_

#include <iostream>
#include <vector>
#include "common_pg.h"

class Operation {
  private:
    PGresult* res;
    int n;
    int rows;
  public:
    Operation(PGresult* res);
    void search_all();
    void install_lib();
};

#endif
