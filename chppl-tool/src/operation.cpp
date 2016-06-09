// operation.cpp
#include "../include/operation.h"

std::vector<std::string> split(const std::string&, const std::string&);


Operation::Operation() {
  // constructor
  this->res;
  this->n;
  this->rows;
}

int Operation::get_n() {
  // PQfields getter
  return this->n;
}

int Operation::get_rows() {
  // PQntuples getter
  return this->rows;
}

void Operation::set_result(PGresult* res) {
  this->res = res;
  this->n = PQnfields(res);
  this->rows = PQntuples(res);
}

void Operation::search_all() {
  // search all libraries
  res = this->res;
  rows = this->rows;

  for (int i=0; i<rows; ++i) {
    std::cout << PQgetvalue(res, i, PQfnumber(res, "name")) << std::endl;
  }

  PQclear(res);
}

void Operation::install_lib() {
  // install libraries
  res = this->res;

  std::string url = PQgetvalue(res,0,PQfnumber(res,"url"));

  std::vector<std::string> splited_url = split(url, "/blob/");
  std::vector<std::string> splited_url2 = split(url, "/");

  std::string filename = splited_url2.back();

  std::string cmd = "svn export " + splited_url[0] + "/branches/" + splited_url[1];
  cmd += " ~/.chppl/libs/";
  cmd += filename;

  system("mkdir ~/.chppl -p");
  system("mkdir ~/.chppl/libs -p");

  system(cmd.c_str());
  PQclear(res);
}

void Operation::download_lib() {
  // download libraries
  res = this->res;

  std::string url = PQgetvalue(res,0,PQfnumber(res,"url"));

  std::vector<std::string> splited_url = split(url, "/blob/");
  std::vector<std::string> splited_url2 = split(url, "/");

  std::string filename = splited_url2.back();

  std::string cmd = "svn export " + splited_url[0] + "/branches/" + splited_url[1];

  system("mkdir ~/.chppl -p");
  system("mkdir ~/.chppl/libs -p");

  system(cmd.c_str());
  PQclear(res);
}

void Operation::uninstall_lib(std::string target) {
  // uninstall libraries
  std::string cmd = "rm ~/.chppl/libs/" + target;

  system(cmd.c_str());
}

void Operation::show_list() {
  // show installed libraries
  std::string cmd = "ls ~/.chppl/libs/";
  system(cmd.c_str());
}

void Operation::help() {
  // display help
  std::cout << std::endl;
  std::cout << "Usage:" << std::endl;
  std::cout << "chppl <command> [options]" << std::endl;
  std::cout << std::endl;
  std::cout << "Commands:" << std::endl;
  std::cout << "  install    Install packages." << std::endl;
  std::cout << "  download   Download packages." << std::endl;
  std::cout << "  uninstall  Uninstall packages." << std::endl;
  std::cout << "  list       List installed packages." << std::endl;
  std::cout << "  search     Search packages." << std::endl;
  std::cout << "  help       Show help for commands." << std::endl;
  std::cout << std::endl;
}

std::vector<std::string> split(const std::string &str, const std::string &delim) {
  // split string
  std::vector<std::string> result;
  size_t current = 0;
  size_t found;
  size_t delimlen = delim.size();

  while ((found = str.find(delim, current)) != std::string::npos) {
    result.push_back(std::string(str, current, found - current));
    current = found + delimlen;
  }

  result.push_back(std::string(str, current, str.size() - current));

  return result;
}
