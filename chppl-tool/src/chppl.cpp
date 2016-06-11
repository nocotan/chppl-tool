// chppl.cpp
#include "../include/chppl.h"

Cpgsql connect_psql();
std::string query(std::string, int&, char* argv[], int);

int main(int argc, char *argv[]) {
  // main block
  // raise error if argc < 2
  Error error = Error();
  if (argc < 2) {
    error.error_num_of_args();
    exit(1);
  }
  Validate v = Validate();

  if (v.validate_input(argv[1]) != true) {
    error.error_invalid_args();
    exit(1);
  }

  Cpgsql con = connect_psql();

  int query_flag = 0;

  std::string argument = argv[1];
  std::string q = query(argument, query_flag, argv, argc);

  PGresult*  res = con.m_ExecSql(q.c_str());

  if (NULL == res) {
    error.error_invalid_args();
    exit(1);
  }

  Operation op = Operation();
  op.set_result(res);

  int rows = op.get_rows();
  if (rows <= 0) {
    error.error_invalid_args();
    exit(1);
  }

  if (1 == query_flag) {
    op.search_all();
  }
  else if (2 == query_flag) {
    op.install_lib();
  }
  else if (3 == query_flag) {
    op.download_lib();
  }
  else if (4 == query_flag) {
    op.show_description();
  }

  return 0;
}

Cpgsql connect_psql() {
  // connect db
  Cpgsql con(
      "ec2-50-19-239-232.compute-1.amazonaws.com",
      "agcdhswzpdwrbp",
      "gurQBp9jT2t1eNMHI3P7Ew5g_0",
      "d8rjp9952jhohi");
  return con;
}

std::string query(std::string argument, int &query_flag, char* argv[], int argc) {
  // return sql query
  std::string q = "invalid";
  Error error = Error();
  Validate v = Validate();

  if (argument == "search") {
    q = "SELECT * FROM libraries;";
    query_flag = 1;
  }
  else if (argument == "install") {
    if (argc < 3) {
      error.error_num_of_args();
      exit(1);
    }

    if (v.validate_input(argv[2]) != true) {
      error.error_invalid_args();
      exit(1);
    }

    std::string target = argv[2];
    q = "SELECT * FROM libraries WHERE name = '" + target + "';";
    query_flag = 2;
  }
  else if (argument == "download") {
    if (argc < 3) {
      error.error_num_of_args();
      exit(1);
    }

    if (v.validate_input(argv[2]) != true) {
      error.error_invalid_args();
      exit(1);
    }

    std::string target = argv[2];
    q = "SELECT * FROM libraries WHERE name = '" + target + "';";
    query_flag = 3;
  }
  else if (argument == "uninstall") {
    if (argc < 3) {
      error.error_num_of_args();
      exit(1);
    }

    if (v.validate_input(argv[2]) != true) {
      error.error_invalid_args();
      exit(1);
    }

    std::string target = argv[2];
    Operation op = Operation();
    op.uninstall_lib(target);
    exit(0);
  }
  else if (argument == "show") {
    if (argc < 3) {
      error.error_num_of_args();
      exit(1);
    }

    if (v.validate_input(argv[2]) != true) {
      error.error_invalid_args();
      exit(1);
    }

    std::string target = argv[2];
    q = "SELECT * FROM libraries WHERE name = '" + target + "';";
    query_flag = 4;
  }
  else if (argument == "list") {
    Operation op = Operation();
    op.show_list();
    exit(0);
  }
  else if (argument == "help") {
    Operation op = Operation();
    op.help();
    exit(0);
  }
  else {
    error.error_not_found_command();
    exit(1);
  }

  return q;
}
