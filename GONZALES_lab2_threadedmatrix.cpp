#include <bits/stdc++.h>
using namespace std;

#define MAX 1
#define MAX_THREAD 1

    int m1[5][5] = {{1, 2, 3, 4, 5}, //given for matrix 1

                    {6, 7, 8, 9, 10},

                    {11, 12, 13, 14, 15},

                    {16, 17, 18, 19, 20},

                    {21, 22, 23, 24, 25}};

    int m2[5][3] = {{26, 27, 28}, //given for matrix 2

                    {29, 30, 31},

                    {32, 33, 34},

                    {35, 36, 37},

                    {38, 39, 40}};
    
    
    int result[5][3] = {{0}}; // initializing matrix for result

    void* multi(void* arg)
    {
        
        for (int i = 0; i < 5; i++)
        {
            for (int j=0; j < 3; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    result[i][j] += m1[i][k] * m2[k][j];
                }
            }
        }
    }

//DRIVER
int main()

{
    
    //Print m1
    cout << "\n" << "Matrix A" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            cout << m1[i][j] << " ";
        cout << endl;
    }
    
    //Print m2
    cout << "\n" << "Matrix B" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++)
            cout << m2[i][j] << " ";
        cout << endl;
    }
    
    //declare 5 threads
    pthread_t threads[MAX_THREAD]; 
    
    //create threads
    for (int i = 0; i < MAX_THREAD; i++) 
    {
        int* p;
        pthread_create(&threads[i], NULL, multi, (void*)(p));
    }
 
    // join and wait
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], NULL);   
 
    // Result
    cout << "\n";
    cout << "Multiplication of A and B" << endl;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++)
            cout << result[i][j] << " ";       
        cout << endl;
    }

    return 0;

}
