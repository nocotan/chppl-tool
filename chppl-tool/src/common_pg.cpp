#include "../include/common_pg.h"

Cpgsql::Cpgsql(const char* host, const char* user,
    const char* pw, const char* dbn) {
  con = PQsetdbLogin(host, "5432", "", "", dbn, user, pw);

  if (PQstatus(con) == CONNECTION_BAD) {
    std::cout << stderr << std::flush;
    std::cout << PQerrorMessage(con) << std::endl;
  }
}

Cpgsql::~Cpgsql() {
  PQfinish(con);
}

PGresult* Cpgsql::m_ExecSql(const char* sql) {
  res = PQexec(con, sql);
  if(PQresultStatus(res) != PGRES_TUPLES_OK) {
    std::cout << stderr << std::flush;
    std::cout << PQerrorMessage(con) << std::flush;
    PQclear(res);
    return NULL;
  }
  return res;
}
