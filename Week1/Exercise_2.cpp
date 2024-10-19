#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
using namespace std;

bool readMatrix(const char *filename, int **&matrix, int &rows, int &cols)
{
    fstream inputFile(filename, ios::in);

    if (!inputFile.is_open()){
        return false;
    }

    string buff;
    cols = 0, rows = 0;
    while(!inputFile.eof() && getline(inputFile, buff) && buff[0] != '\0'){
        rows = rows + 1;
        if (cols == 0){
            istringstream iss(buff);
            int tmp;
            while(iss >> tmp) cols = cols + 1;
        }
    }
    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    matrix = (int **)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)calloc(cols, sizeof(int));
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            inputFile >> matrix[i][j];
        }
    }
    inputFile.close();
    return true;
}

void printMatrix(const char *filename, int **matrix, int rows, int cols)
{
    fstream outputFile(filename, ios::out);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            outputFile << matrix[i][j] << " ";
        }
        outputFile << '\n';
    }
    outputFile.close();
}

bool multiplyMatrices(int **a, int aRows, int aCols, int **b, int bRows, int bCols, int **&res, int &resRows, int &resCols)
{
    if (aCols != bRows)
        return false;

    resRows = aRows;
    resCols = bCols;

    res = (int **)calloc(resRows, sizeof(int *));
    for (int i = 0; i < resRows; i++)
        res[i] = (int *)calloc(resCols, sizeof(int));
    
    for (int i = 0; i < aRows; i++)
        for (int j = 0; j < bCols; ++j)
            for (int k = 0; k < aCols; ++k)
                res[i][j] += a[i][k] * b[k][j];

    return true;
}

void transposeMatrix(int **matrix, int rows, int cols, int **&res, int &resRows, int &resCols)
{
    resRows = cols;
    resCols = rows;
    res = (int**)calloc(resRows, sizeof(int*));
    for (int i = 0; i < resRows; i++){
        res[i] = (int*)calloc(resCols, sizeof(int));
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            res[j][i] = matrix[i][j];
        }
    }
}

void freeMatrix(int **&matrix, int rows, int cols){
    if (matrix == NULL) return;
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}

int main()
{
    int **a = nullptr, aRows, aCols;
    readMatrix("matrix_a.txt", a, aRows, aCols);
   
    int **b = nullptr, bRows, bCols;
    readMatrix("matrix_b.txt", b, bRows, bCols);
    
    int **c = nullptr, cRows, cCols;
    int **cT = nullptr, cTRows, cTCols; 

    if (multiplyMatrices(a, aRows, aCols, b, bRows, bCols, c, cRows, cCols)){
        cout << "Multiplication is successful!!! \n";
        printMatrix("matrix_c.txt", c, cRows, cCols);
        transposeMatrix(c, cRows, cCols, cT, cTRows, cTCols);
        printMatrix("matrix_c_transposed.txt", cT, cTRows, cTCols);
    }
    else
        cout << "Multiplication is unsuccessful!!! \n";
    
    freeMatrix(a, aRows, aCols);
    freeMatrix(b, bRows, bCols);
    freeMatrix(c, cRows, cCols);
    freeMatrix(cT, cTRows, cTCols);
    
    return 0;
}
