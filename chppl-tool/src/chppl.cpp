#include "../include/chppl.h"

Cpgsql connect_psql();
std::string query(std::string, int&, char* argv[]);

int main(int argc, char *argv[]) {
  // raise error if argc < 2
  if (argc < 2) {
    std::cout << "argument error" << std::endl;
    exit(1);
  }

  Cpgsql con = connect_psql();

  int query_flag = 0;

  std::string argument = argv[1];
  std::string q = query(argument, query_flag, argv);

  PGresult*  res = con.m_ExecSql(q.c_str());

  if (NULL == res) {
    exit(1);
  }

  Operation op(res);

  if (1 == query_flag) {
    op.search_all();
  } else if (2 == query_flag) {
    op.install_lib();
  }

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

std::string query(std::string argument, int &query_flag, char* argv[]) {
  std::string q = "invalid";

  if (argument == "search") {
    q = "SELECT * FROM libraries;";
    query_flag = 1;
  } else if (argument == "install") {
      if (sizeof(argv) < 3) {
        std::cout << "argument error" << std::endl;
        exit(1);
      }
      std::string target = argv[2];
      q = "SELECT * FROM libraries WHERE name = '" + target + "';";
      query_flag = 2;
  } else {
    std::cout << "argument error" << std::endl;
    exit(1);
  }

  return q;
}
