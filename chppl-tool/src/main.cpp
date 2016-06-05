#include "../include/main.h"

int main(int argc, char **argv) {
  Cpgsql con(
      "ec2-50-19-239-232.compute-1.amazonaws.com",
      "agcdhswzpdwrbp",
      "gurQBp9jT2t1eNMHI3P7Ew5g_0",
      "d8rjp9952jhohi");

  std::cout << "connect" << std::endl;
  PGresult* res = con.m_ExecSql("SELECT * FROM libraries;");

  if (NULL == res) {
    return 1;
  }

  int n = PQnfields(res);
  int rows = PQntuples(res);

  std::cout << PQgetvalue(res, 0, PQfnumber(res, "name")) << std::endl;


  PQclear(res);
  return 0;
}
