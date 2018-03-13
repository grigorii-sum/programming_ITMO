#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

class Matrix
{
    private:
        int rows, cols;
        int **table;
    public:
        //constructor
        Matrix(int rows, int cols)
        {
            this->rows = rows;
            this->cols = cols;
            this->table = new int*[rows];
            for(int i = 0; i < this->rows; i++)
            {
                this->table[i] = new int[this->cols];
            }
        }

        //destructor
        ~Matrix()
        {
            for(int i = 0; i < rows; i++)
            {
                delete [] table[i];
            }
            delete [] table;
        }

        //operator >>
        friend istream &operator>>(istream& put, Matrix& other)
        {
            cout << "Reading elements of matrix from file..." << endl;
            for(int i = 0; i < other.rows; i++)
            {
                for(int j = 0; j < other.cols; j++)
                {
                    put >> other[i][j];
                }
            }
            return put;
        }

        //operator <<
        friend ostream &operator<<(ostream& put, Matrix& other)
        {
            for(int i = 0; i < other.rows; i++)
            {
                for(int j = 0; j < other.cols; j++)
                {
                    put << other[i][j] << " ";
                }
                put << endl;
            }
            return put;
        }

        //operator + with matrix
        Matrix operator+(Matrix &other)
        {
            if ((this->rows == other.rows) && (this->cols == other.cols))
            {
                Matrix answer(rows, cols);
                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < cols; j++)
                    {
                        answer.table[i][j] = this->table[i][j] + other.table[i][j];
                    }
                }
                return answer;
            }
            else
            {
                cout << ("ERROR: THE NUMBER OF ROWS OR COLUMNS IN MATRICES DOES NOT MATCH") << endl;
                exit(1);
            }
        }

        //operator + with constant
        Matrix operator+(int number)
        {
            Matrix answer(rows, cols);
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    answer.table[i][j] = this->table[i][j] + number;
                }
            }
            return answer;
        }

        //operator - with matrix
        Matrix operator-(Matrix &other)
        {
            if ((this->rows == other.rows) && (this->cols == other.cols))
            {
                Matrix answer(rows, cols);
                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < cols; j++)
                    {
                        answer.table[i][j] = this->table[i][j] - other.table[i][j];
                    }
                }
                return answer;
            }
            else
            {
                cout << ("ERROR: THE NUMBER OF ROWS OR COLUMNS IN MATRICES DOES NOT MATCH") << endl;
                exit(1);
            }
        }

        //operator - with constant
        Matrix operator-(int number)
        {
            Matrix answer(rows, cols);
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    answer.table[i][j] = this->table[i][j] - number;
                }
            }
            return answer;
        }

        //operator * with matrix
        Matrix operator*(Matrix &other)
        {
            if ((this->rows == other.rows) && (this->cols == other.cols))
            {
                Matrix answer(rows, cols);
                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < cols; j++)
                    {
                        answer.table[i][j] = this->table[i][j] * other.table[i][j];
                    }
                }
                return answer;
            }
            else
            {
                cout << ("ERROR: THE NUMBER OF ROWS OR COLUMNS IN MATRICES DOES NOT MATCH") << endl;
                exit(1);
            }
        }

        //operator * with constant
        Matrix operator*(int number)
        {
            Matrix answer(rows, cols);
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    answer.table[i][j] = this->table[i][j] * number;
                }
            }
            return answer;
        }

        //operator += with matrix
        Matrix& operator+=(Matrix &other)
        {
            if ((this->rows == other.rows) && (this->cols == other.cols))
            {
                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < cols; j++)
                    {
                        this->table[i][j] += other.table[i][j];
                    }
                }
                return *this;
            }
            else
            {
                cout << ("ERROR: THE NUMBER OF ROWS OR COLUMNS IN MATRICES DOES NOT MATCH") << endl;
                exit(1);
            }
        }

        //operator += with constant
        Matrix& operator+=(int number)
        {
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    this->table[i][j] += number;
                }
            }
            return *this;
        }

        //operator -= with matrix
        Matrix& operator-=(Matrix &other)
        {
            if ((this->rows == other.rows) && (this->cols == other.cols))
            {
                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < cols; j++)
                    {
                        this->table[i][j] -= other.table[i][j];
                    }
                }
                return *this;
            }
            else
            {
                cout << ("ERROR: THE NUMBER OF ROWS OR COLUMNS IN MATRICES DOES NOT MATCH") << endl;
                exit(1);
            }
        }

        //operator -= with constant
        Matrix& operator-=(int number)
        {
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    this->table[i][j] -= number;
                }
            }
            return *this;
        }

        //operator *= with matrix
        Matrix& operator*=(Matrix &other)
        {
            if ((this->rows == other.rows) && (this->cols == other.cols))
            {
                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < cols; j++)
                    {
                        this->table[i][j] *= other.table[i][j];
                    }
                }
                return *this;
            }
            else
            {
                cout << ("ERROR: THE NUMBER OF ROWS OR COLUMNS IN MATRICES DOES NOT MATCH") << endl;
                exit(1);
            }
        }

        //operator *= with constant
        Matrix& operator*=(int number)
        {
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    this->table[i][j] *= number;
                }
            }
            return *this;
        }

        //operator[]
        int *operator[](int i)
        {
            return this->table[i];
        }

        //transpose
        Matrix tran()
        {
            Matrix answer(this->cols, this->rows);
            for(int i = 0; i < this->rows; i++)
            {
                for(int j = 0; j < this->cols; j++)
                {
                    answer.table[j][i] = this->table[i][j];
                }
            }
            return answer;
        }

        //dot
        Matrix dot(Matrix &other)
        {
            if (this->cols == other.rows)
            {
                Matrix answer(this->rows, other.cols);
                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < other.cols; j++)
                    {
                        answer.table[i][j] = 0;
                        for(int k = 0; k < cols; k++)
                        {
                            answer.table[i][j] += this->table[i][k] * other.table[k][j];
                        }
                    }
                }
                return answer;
            }
            else
            {
                cout << ("ERROR: THE NUMBER OF ROWS OR COLUMNS IN MATRICES DOES NOT SATISFY CONDITION") << endl;
                exit(1);
            }
        }
};

int main()
{
    ifstream input("data-in.txt");
    int rows1, cols1, rows2, cols2, number;

    cout << "Enter the number of rows and columns of the first matrix:" << endl;
    cin >> rows1 >> cols1;
    cout << "Enter the number of rows and columns of the second matrix:" << endl;
    cin >> rows2 >> cols2;
    cout << "Enter an integer:" << endl;
    cin >> number;
    cout << endl;

    Matrix A(rows1, cols1);
    Matrix B(rows2, cols2);

    cout << "//OPERATOR + WITH MATRIX:" << endl;
    input >> A;
    input >> B;
    Matrix C = A + B;
    cout << C << endl << endl;

    cout << "//OPERATOR + WITH CONSTANT:" << endl;
    input >> A;
    C = A + number;
    cout << C << endl << endl;

    cout << "//OPERATOR - WITH MATRIX:" << endl;
    input >> A;
    input >> B;
    C = A - B;
    cout << C << endl << endl;

    cout << "//OPERATOR - WITH CONSTANT:" << endl;
    input >> A;
    C = A - number;
    cout << C << endl << endl;

    cout << "//OPERATOR * WITH MATRIX:" << endl;
    input >> A;
    input >> B;
    C = A * B;
    cout << C << endl << endl;

    cout << "//OPERATOR * WITH CONSTANT:" << endl;
    input >> A;
    C = A * number;
    cout << C << endl << endl;

    cout << "//OPERATOR += WITH MATRIX:" << endl;
    input >> A;
    input >> B;
    A += B;
    cout << A << endl << endl;

    cout << "//OPERATOR += WITH CONSTANT:" << endl;
    input >> A;
    A += number;
    cout << A << endl << endl;

    cout << "//OPERATOR -= WITH MATRIX:" << endl;
    input >> A;
    input >> B;
    A -= B;
    cout << A << endl << endl;

    cout << "//OPERATOR -= WITH CONSTANT:" << endl;
    input >> A;
    A -= number;
    cout << A << endl << endl;

    cout << "//OPERATOR *= WITH MATRIX:" << endl;
    input >> A;
    input >> B;
    A *= B;
    cout << A << endl << endl;

    cout << "//OPERATOR *= WITH CONSTANT:" << endl;
    input >> A;
    A *= number;
    cout << A << endl << endl;

    cout << "//TRANSPOSE:" << endl;
    input >> A;
    Matrix T = A.tran();
    cout << T << endl << endl;

    cout << "//DOT:" << endl;
    input >> A;
    Matrix D = A.dot(T);
    cout << D << endl << endl;

    return 0;
}
