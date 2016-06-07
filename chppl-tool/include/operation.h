#ifndef OPERATION_H_
#define OPERATION_H_

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include "common_pg.h"

class Operation {
  private:
    PGresult* res;
    int n;
    int rows;
  public:
    Operation(PGresult* res);
    int get_n();
    int get_rows();
    void search_all();
    void install_lib();
};

#endif
