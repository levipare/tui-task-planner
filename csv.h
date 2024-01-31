#ifndef CSV_H
#define CSV_H

#include <fstream>
#include <string>
#include <vector>

class Csv {
private:
  std::string file_path;

public:
  Csv(std::string file_path);

  void write(const std::vector<std::vector<std::string>> &lines);

  std::vector<std::vector<std::string>> read();
};

#endif
