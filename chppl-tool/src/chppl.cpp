#include "../include/chppl.h"

Cpgsql connect_psql();
std::string query(std::string);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "argument error" << std::endl;
    exit(1);
  }

  Cpgsql con = connect_psql();

  std::string op = argv[1];
  std::string q = query(op);

  PGresult* res = con.m_ExecSql(q.c_str());

  if (NULL == res) {
    exit(1);
  }

  int n = PQnfields(res);
  int rows = PQntuples(res);

  std::cout << PQgetvalue(res, 1, PQfnumber(res, "name")) << std::endl;


  PQclear(res);
  return 0;
}

Cpgsql connect_psql() {
  Cpgsql con(
      "ec2-50-19-239-232.compute-1.amazonaws.com",
      "agcdhswzpdwrbp",
      "gurQBp9jT2t1eNMHI3P7Ew5g_0",
      "d8rjp9952jhohi");
  return con;
}

std::string query(std::string op) {
  std::string q = "invalid";

  if (op == "search") {
    q = "SELECT * FROM libraries;";
  } else {
    std::cout << "argument error" << std::endl;
    exit(1);
  }

  return q;
}
