#include "readData.h"

void readPressEnth(std::vector<double>& p, std::vector<double>& h) {

    double x;
    std::ifstream inFile;

    inFile.open("C:/Users/katja/source/repos/VaporCompressionSystemTest/VaporCompressionSystem/coarseMesh/pressures.txt");
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    while (inFile >> x) {
        p.push_back(x);
    }
    inFile.close();

    inFile.open("C:/Users/katja/source/repos/VaporCompressionSystemTest/VaporCompressionSystem/coarseMesh/enthalpies.txt");
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    while (inFile >> x) {
        h.push_back(x);
    }
    inFile.close();

}


void readData(std::vector<double>& p, std::vector<double>& h, std::vector<double>& fvals, std::vector<std::vector<double>>& matrix, std::string txtName) {

    double x;
    std::ifstream inFile;

    std::string path = "C:/Users/katja/source/repos/VaporCompressionSystemTest/VaporCompressionSystem/coarseMesh/" + txtName;

    std::ifstream fin(path);

    size_t n_rows, n_cols;
    n_rows = p.size();
    n_cols = h.size();

    matrix.resize(n_rows);

    //std::cout << n_rows << "  " << n_cols;

    fvals.resize(n_rows * n_cols);
    fvals.assign(std::istream_iterator<double>(fin), std::istream_iterator<double>());

    fin.close();

    for (size_t i = 0; i < n_rows; i++)
    {
        matrix[i].resize(n_cols);
        for (size_t j = 0; j < n_cols; j++)
        {
            matrix[i][j] = fvals[i * n_cols + j];
        }
    }


}