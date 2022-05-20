#include <iostream>
using namespace std;
class matrix3d
{
    int n, m, p;
    int ***matrix;
    bool checkBound(int &i, int &j, int &k)
    {
        if (i >= n || i < 0 || j >= m || j < 0 || k >= p || k < 0)
            return false;
        return true;
    }

public:
    matrix3d(int N, int M, int P)
    {
        n = N;
        m = M;
        p = P;
        matrix = new int **[n];
        for (int i = 0; i < n; i++)
        {
            matrix[i] = new int *[m];
            for (int j = 0; j < m; j++)
                matrix[i][j] = new int[p];
        }
    }
    void insertIn3D(int i, int j, int k, int value)
    {
        if (!checkBound(i, j, k))
        {
            throw exception();
            return;
        }
        matrix[i][j][k] = value;
    }
    int *get1DArray()
    {
        int *flattenedMatrix = new int[n * m * p];
        return flattenedMatrix;
    }
    int convert_3d_index_to_1d_index(int i, int j, int k)
    {
        if (!checkBound(i, j, k))
            throw exception();
        return i + j * n + k * n * m;
    }
    ~matrix3d()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                delete[] matrix[i][j];
            delete[] matrix[i];
        }
    }
};
int main()
{
    try
    {
        matrix3d testing(2, 2, 3);
        int i, j, k;

        // get 1D array from 3d array
        int *flattenedMatrix = testing.get1DArray();

        // initialize position bounded in the range
        i = 1;
        j = 0;
        k = 2;

        // get position bounded in 3d array and then initialize it
        flattenedMatrix[testing.convert_3d_index_to_1d_index(i, j, k)] = 20;
        cout << "initiaizing position " << testing.convert_3d_index_to_1d_index(i, j, k) << " in the 1D array\n";
        // print the same position we have initialized
        cout << "with value = " << flattenedMatrix[testing.convert_3d_index_to_1d_index(i, j, k)] << endl;

        // initialize position unbounded in the range
        i = 6;
        j = 0;
        k = 2;
        // get position unbounded in 3d array => error excepted
        cout << "tring to access position [" << i << "][" << j << "][" << k << "] which is\n";
        testing.convert_3d_index_to_1d_index(i, j, k);
    }
    catch (exception &)
    {
        cout << "ERROR => out of range access\n";
    }
    return 0;
}