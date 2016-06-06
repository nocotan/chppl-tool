#include "../include/operation.h"

std::vector<std::string> split(const std::string&, const std::string&);


Operation::Operation(PGresult* res) {
  this->res = res;
  this->n = PQnfields(res);
  this->rows = PQntuples(res);
}

void Operation::search_all() {
  res = this->res;
  rows = this->rows;

  for (int i=0; i<rows; ++i) {
    std::cout << PQgetvalue(res, i, PQfnumber(res, "name")) << std::endl;
  }

  PQclear(res);
}

void Operation::install_lib() {
  res = this->res;
  std::string url = PQgetvalue(res,0,PQfnumber(res,"url"));
  std::vector<std::string> splited_url = split(url, "/blob/");
  std::string cmd = "svn export " + splited_url[0] + "/branches/" + splited_url[1];
  system(cmd.c_str());
  PQclear(res);
}

std::vector<std::string> split(const std::string &str, const std::string &delim) {
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
