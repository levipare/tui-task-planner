#ifndef CSV_H
#define CSV_H

#include <fstream>
#include <string>
#include <vector>

class Csv {
private:
  std::string file_path;

public:
  /**
   * Constructor.
   * @param file_path the file path of the csv to write/read to/from
   */
  Csv(std::string file_path);

  /**
   * Write out data to csv file.
   * @param lines a vector of vectors that contain strings which represent each
   * value.
   */
  void write(const std::vector<std::vector<std::string>> &lines);

  /**
   * Reads a csv file and assumes that each field is a string type.
   * It is up to the user to convert types.
   * @return a vector of vectors that contain strings which represent each
   * value.
   */
  std::vector<std::vector<std::string>> read();
};

#endif
