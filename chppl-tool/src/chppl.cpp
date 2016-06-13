// chppl.cpp
#include "../include/chppl.h"

Cpgsql connect_psql();
static std::string query(const std::string&, int&, char* argv[], int);

enum QUERY_FLAG{
  QUERY_FLAG_UNKNOWN  = 0,
  QUERY_FLAG_SEARCH   = 1,
  QUERY_FLAG_INSTALL  = 2,
  QUERY_FLAG_DOWNLOAD = 3,
  QUERY_FLAG_SHOW     = 4,
};

int main(int argc, char *argv[]) {
  // main block
  // raise error if argc < 2
  Error error;
  if (argc < 2) {
    error.error_num_of_args();
    exit(1);
  }

  Validate v;
  if (v.validate_input(argv[1]) != true) {
    error.error_invalid_args();
    exit(1);
  }

  int query_flag = QUERY_FLAG_UNKNOWN;

  std::string argument = argv[1];
  std::string q = query(argument, query_flag, argv, argc);

  std::cerr << "chppl: connecting..." << std::flush;
  Cpgsql con = connect_psql();
  PGresult* res = con.m_ExecSql(q.c_str());
  std::cerr << std::endl;

  if (NULL == res) {
    error.error_invalid_args();
    exit(1);
  }

  Operation op;
  op.set_result(res);

  int rows = op.get_rows();
  if (rows <= 0) {
    error.error_invalid_args();
    exit(1);
  }

  if (QUERY_FLAG_SEARCH == query_flag) {
    if(argc >= 3)
      op.search_string(const_cast<const char**>(argv+2), argc-2);
    else
      op.search_all();
  }
  else if (QUERY_FLAG_INSTALL == query_flag) {
    op.install_lib();
  }
  else if (QUERY_FLAG_DOWNLOAD == query_flag) {
    op.download_lib();
  }
  else if (QUERY_FLAG_SHOW == query_flag) {
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

static std::string query(const std::string& argument, int &query_flag, char* argv[], int argc) {
  // return sql query
  std::string q = "invalid";
  Error error;
  Validate v;

  if (argument == "search") {
    q = "SELECT * FROM libraries;";
    query_flag = QUERY_FLAG_SEARCH;
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
    query_flag = QUERY_FLAG_INSTALL;
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
    query_flag = QUERY_FLAG_DOWNLOAD;
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
    query_flag = QUERY_FLAG_SHOW;
  }
  else if (argument == "list") {
    Operation op;
    op.show_list();
    exit(0);
  }
  else if (argument == "help") {
    Operation op;
    op.help();
    exit(0);
  }
  else {
    error.error_not_found_command();
    exit(1);
  }

  return q;
}
