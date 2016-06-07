#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include <iostream>
#include <string>
#include "libpq-fe.h"
#include "postgres.h"

class Cpgsql {
  private:
    PGconn *con;
    PGresult *res;
  public:
    Cpgsql(const char* host, const char* user, const char* pw, const char* dbn);
    ~Cpgsql();
    PGresult* m_ExecSql(const char* sql);
};

#endif
