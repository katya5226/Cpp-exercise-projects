#ifndef READDATA_H
#define READDATA_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <vector>

void readPressEnth(std::vector<double>&, std::vector<double>&);
void readData(std::vector<double>&, std::vector<double>&, std::vector<double>&, std::vector<std::vector<double>>&, std::string);

#endif //READDATA_H
