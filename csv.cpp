#include "csv.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>

Csv::Csv(std::string file_path) { this->file_path = file_path; }

void Csv::write(const std::vector<std::vector<std::string>> &lines) {
  std::ofstream fs;
  fs.open(this->file_path);

  for (std::vector line : lines) {
    for (int col = 0; col < line.size(); col++) {
      if (line[col].find(",") != std::string::npos ||
          line[col].find('"') != std::string::npos) {
        std::string escaped;
        for (char c : line[col]) {
          if (c == '"')
            escaped += '"';
          escaped += c;
        }

        fs << '"' << escaped << '"';
      } else {
        fs << line[col];
      }

      if (col < line.size() - 1) {
        fs << ',';
      } else {
        fs << std::endl;
      }
    }
  }

  fs.close();
}

// name, day, month, year, completed
std::vector<std::vector<std::string>> Csv::read() {
  std::fstream fs;
  fs.open(this->file_path);
  std::vector<std::vector<std::string>> lines;

  std::string line_str;
  while (getline(fs, line_str)) {
    std::stringstream ss(line_str);
    std::vector<std::string> columns;

    while (ss.peek() != EOF) {
      std::string col;
      if (ss.peek() == '"') {
        ss.get();
        char c = ss.get();
        while (true) {
          if (c == '"' && ss.peek() == ',') {
            ss.get();
            break;
          } else if (c == '"' && ss.peek() == '"') {
            ss.get();
          }
          col += c;
          c = ss.get();
        }
      } else {
        getline(ss, col, ',');
      }
      columns.push_back(col);
    }
    if (!columns.empty()) {
      lines.push_back(columns);
    }
  }

  fs.close();
  return lines;
}
