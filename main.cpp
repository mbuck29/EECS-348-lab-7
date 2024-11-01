#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void read_matrix_from_file(
    const char *file_name,
    vector<vector<double>> &matrix_1,
    vector<vector<double>> &matrix_2) {
    ifstream file(file_name);
    int matrix_size;
    file >> matrix_size;
    file.ignore();

    matrix_1 = vector<vector<double>>(matrix_size, vector<double>(matrix_size));
    matrix_2 = vector<vector<double>>(matrix_size, vector<double>(matrix_size));

    int line_number = 0;
    string line;
    
    while (getline(file, line)) {
        istringstream iss(line);
        vector<double> curr_line;
        double curr_element;
        
        while (iss >> curr_element){
            curr_line.push_back(curr_element);
        }
        if (line_number < matrix_size){
            matrix_1[line_number] = curr_line;
        }else if (line_number < matrix_size * 2){
            matrix_2[line_number - matrix_size] = curr_line; 
        }
        line_number++;
    }
    return;
}

void print_matrix(const vector<vector<double>> &matrix) {
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
    return;
}

void print_matrix(const vector<vector<double>> &matrix_1, const vector<vector<double>> &matrix_2) {
    print_matrix(matrix_1);
    print_matrix(matrix_2);
}

vector<vector<double>> operator+(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2) {
    if (matrix_1.size() != matrix_2.size() || matrix_1[0].size() != matrix_2[0].size()){
        cout << "The dimensions of the Matricies do not match" << endl;
        return {};
    }
    int rows = matrix_1.size();
    int cols = matrix_1[1].size();
    vector<vector<double>> new_matrix = vector<vector<double>>(rows, vector<double>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            new_matrix[i][j] = matrix_1[i][j] + matrix_2[i][j];
        }
    }
    return new_matrix;    
}

vector<vector<double>> operator*(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2) {
    if (matrix_1[0].size() != matrix_2.size()) {
        cout << "The given matricies have incompatible dimensions" << endl;
        return {};
    }
    int rows = matrix_1.size();
    int cols = matrix_2[0].size();
    vector<vector<double>> new_matrix = vector<vector<double>>(rows, vector<double>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < matrix_1.size(); k++) {
                new_matrix[i][j] += matrix_1[i][k] * matrix_2[k][j];
            }
        }
    }
    return new_matrix; 
}

void get_diagonal_sum(const vector<vector<double>> &matrix) {
    if (matrix.size() != matrix[0].size()){
        cout << "The given matrix is not square" << endl;
        return;
    }
    int main_diagonal = 0;
    int secondary_diagonal = 0;
    int secondary_offset = matrix.size() - 1;
    for (int i = 0; i < matrix.size(); i++) {
        main_diagonal += matrix[i][i];
        secondary_diagonal += matrix[secondary_offset][i];
        secondary_offset--;
    }
    cout << "The sum of the main diagonal is " << main_diagonal << endl;
    cout << "The sum of the secondary diagonal is " << secondary_diagonal << endl;
}

void swap_matrix_row(vector<vector<double>> matrix, int row1, int row2) {
    if (row1 < 0 || row1 >= matrix.size() || row2 < 0 || row2 >= matrix.size()){
        cout << "One of the given rows is a invalid index" << endl;
        return;
    }
    vector<double> temp_row1 = matrix[row1];
    vector<double> temp_row2 = matrix[row2];
    matrix[row1] = temp_row2;
    matrix[row2] = temp_row1;
    
    print_matrix(matrix);
    return;
}

int main(int argc, char *argv[]) {
    vector<vector<double>> matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);
    cout << "print_matrix" << endl;
    print_matrix(matrix_1, matrix_2);

    auto add_matrix = matrix_1 + matrix_2;
    cout << "operator+ overloading" << endl;
    print_matrix(add_matrix);

    auto multiply_matrix = matrix_1 * matrix_2;
    cout << "operator* overloading" << endl;
    print_matrix(multiply_matrix);

    cout << "get matrix diagonal sum" << endl;
    get_diagonal_sum(matrix_1);

    cout << "swap matrix rows" << endl;
    swap_matrix_row(matrix_1, 0, 1);
    swap_matrix_row(matrix_1, 0, 100);
}