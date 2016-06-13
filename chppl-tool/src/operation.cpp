// operation.cpp
#include "../include/operation.h"
#include <cstddef>

static std::vector<std::string> split(const std::string&, const std::string&);


Operation::Operation() {
  // constructor
  this->res;
  this->n;
  this->rows;
}

int Operation::get_n() const{
  // PQfields getter
  return this->n;
}

int Operation::get_rows() const{
  // PQntuples getter
  return this->rows;
}

void Operation::set_result(PGresult* res) {
  this->res = res;
  this->n = PQnfields(res);
  this->rows = PQntuples(res);
}

void Operation::search_all() const{
  // search all libraries
  PGresult* res = this->res;
  int rows = this->rows;

  for (int i=0; i<rows; ++i) {
    std::cout << PQgetvalue(res, i, PQfnumber(res, "name")) << std::endl;
  }

  PQclear(res);
}

void Operation::search_string(const char** needles, int count) const{
  // search libraries containing the specified string
  PGresult* res = this->res;
  int rows = this->rows;

  int fnumberOfName = PQfnumber(res, "name");
  std::string name;
  int numberOfMatches = 0;
  for (int i=0; i<rows; ++i) {
    name = PQgetvalue(res, i, fnumberOfName);

    bool flagFound = false;
    for (int j = 0; j<count; ++j) {
      if (name.find(needles[j]) != std::string::npos) {
        flagFound = true;
        break;
      }
    }

    if (flagFound) {
      std::cout << name << "\n";
      numberOfMatches++;
    }
  }

  if(numberOfMatches > 0) {
    std::cout << std::flush;
  } else {
    std::cerr << "no libraries matching with '";
    for (int j = 0; j<count; ++j) {
      if(j > 0) std::cerr << ", ";
      std::cerr << needles[j];
    }
    std::cerr << "' found." << std::endl;
  }

  PQclear(res);
}

void Operation::install_lib() const{
  // install libraries
  PGresult* res = this->res;

  std::string url = PQgetvalue(res,0,PQfnumber(res,"url"));

  std::vector<std::string> splitted_url = split(url, "/blob/");
  std::vector<std::string> splitted_url2 = split(url, "/");

  std::string filename = splitted_url2.back();

  std::string cmd = "svn export " + splitted_url[0] + "/branches/" + splitted_url[1];
  cmd += " ~/.chppl/libs/";
  cmd += filename;

  system("mkdir ~/.chppl -p");
  system("mkdir ~/.chppl/libs -p");

  system(cmd.c_str());
  PQclear(res);
}

void Operation::download_lib() const{
  // download libraries
  PGresult* res = this->res;

  std::string url = PQgetvalue(res,0,PQfnumber(res,"url"));

  std::vector<std::string> splitted_url = split(url, "/blob/");
  std::vector<std::string> splitted_url2 = split(url, "/");

  std::string filename = splitted_url2.back();

  std::string cmd = "svn export " + splitted_url[0] + "/branches/" + splitted_url[1];

  system("mkdir ~/.chppl -p");
  system("mkdir ~/.chppl/libs -p");

  system(cmd.c_str());
  PQclear(res);
}

void Operation::uninstall_lib(const std::string& target) const{
  // uninstall libraries
  std::string cmd = "rm ~/.chppl/libs/" + target;

  system(cmd.c_str());
}

void Operation::show_list() const{
  // show installed libraries
  std::string cmd = "ls ~/.chppl/libs/";
  system(cmd.c_str());
}

void Operation::show_description() const{
  // show description
  PGresult* res = this->res;
  int rows = this->rows;

  for (int i=0; i<rows; ++i) {
    std::cout << PQgetvalue(res, i, PQfnumber(res, "description")) << std::endl;
  }

  PQclear(res);
}

void Operation::help() const{
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

static std::vector<std::string> split(const std::string &str, const std::string &delim) {
  // split string
  std::vector<std::string> result;
  std::size_t current = 0;
  std::size_t found;
  std::size_t delimlen = delim.size();

  while ((found = str.find(delim, current)) != std::string::npos) {
    result.emplace_back(str, current, found - current);
    current = found + delimlen;
  }

  result.emplace_back(str, current, str.size() - current);

  return result;
}
