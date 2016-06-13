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
    Operation();
    int get_n() const;
    int get_rows() const;
    void get_result() const;
    void set_result(PGresult*);
    void search_string(const std::string&) const;
    void search_all() const;
    void install_lib() const;
    void download_lib() const;
    void uninstall_lib(const std::string&) const;
    void show_list() const;
    void show_description() const;
    void help() const;
};

#endif
