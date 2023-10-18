# Parallel-Distrib-Comput
Parallel and distributed computing revolutionize data processing. Multiple processors collaborate (parallel) or work independently (distributed), enhancing speed, efficiency, and scalability in handling complex computations and big data tasks.


##LAB 1:
Create a C++ program named nothreads.cpp that prints the word

"I " 1000 times "GOT " 1000 times "NOBODY" 1000 times "BUT" 1000 times "YOU" 1000 times sequentially no new lines in between using any loop

Submit the source file and screenshot of your output.

Create a C++ program named withthreads.cpp that does the same but each word is on a separate thread.

Submit the source file and screenshot of your output. 

##LAB 2:

Matrix Multiplication is one operation that would benefit if were designed in a concurrent way because of its independent operation. Consider the program below.

Output:

510 525 540 
1310 1350 1390
2110 2175 2240
2910 3000 3090
3710 3825 3940

Design your own program that implements the matrix multiplication achieving the same output using threads. Save it as threadedmatrix.cpp
Submit a screenshot of the output.

```cpp
#include <iostream>

using namespace std;

int main()

{

    int m1[5][5] = {{1, 2, 3, 4, 5},

                    {6, 7, 8, 9, 10},

                    {11, 12, 13, 14, 15},

                    {16, 17, 18, 19, 20},

                    {21, 22, 23, 24, 25}};

    int m2[5][3] = {{26, 27, 28},

                    {29, 30, 31},

                    {32, 33, 34},

                    {35, 36, 37},

                    {38, 39, 40}};

    int result[5][3] = {{0}};

    for (int i = 0; i < 5; i++)

    {

        for (int j = 0; j < 3; j++)

        {

            for (int k = 0; k < 5; k++)
            {
                result[i][j] += m1[i][k] * m2[k][j];
            }

        }

    }

    for (int i = 0; i < 5; ++i) {

      for (int j = 0; j < 3; ++j) {

         cout << result[i][j] << " ";

         if (j == 2)

            cout << "\n";

      }

    }

    return 0;

}

##LAB #3:

The program initializes a vector with an assigned capacity and a random number for each element. The program counts the histogram of all of the contents of the vector ranging from 1 to 5 and displays it on the screen. The program is also getting the sum of all of the vectors and displays it afterwards. I just displayed the equivalent sum of the histogram and as well as the sum that i was able to get from the vectors for double checking if they match so as to know the program is correct.
Your task is to improve the performance of the program, as we can see that there are things that we can do in concurrent here namely (counting of histogram and getting the sum of the vector). Convert the program to support multithreading in counting the histogram and getting the sum of the vector.
Run the original program and get the screenshot
Run your threaded program and get the screenshot
Determine the percentage of enhancement you were able to achieve using the threaded version and display it on your threaded program. Save the value of the total run on the original program and have it encoded on your threaded program to get the percentage.
You can make variables global
Use code sharing technique for your thread
Be aware of race condition when histogram counting is being implemented as thread thus there is a need to use for locks
Submit your CPP file and as well as the 2 screenshot of the output (original and threaded)

```cpp

#include <iostream>

#include <vector>

#include <chrono>

#include <cstdlib>

using namespace std;

int main()

{

    const long MAX = 500000000;

    const int RANGE = 6;

    vector<int> num(MAX);

    unsigned long long int sum = 0;

    int h1=0;

    int h2=0;

    int h3=0;

    int h4=0;

    int h5=0;

    for (int i = 0; i < MAX; i++)

    {

        num[i] = rand() % RANGE;

        //cout << num[i] << endl; //generates random numbers 1 to 5

    }

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < MAX; i++)

    {

        sum = sum + num[i];

    }

    for(int i=0; i < MAX; i++){

        switch(num[i]){

            case 1: h1++; break;

            case 2: h2++; break;

            case 3: h3++; break;

            case 4: h4++; break;

            case 5: h5++; break;

        }

    }

    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Histogram Result is : " << endl;

    cout << "1  ----> " << h1 << " SUM : " << h1 << endl;

    cout << "2  ----> " << h1 << " SUM : " << h2*2 << endl;

    cout << "3  ----> " << h1 << " SUM : " << h3*3 << endl;

    cout << "4  ----> " << h1 << " SUM : " << h4*4 << endl;

    cout << "5  ----> " << h1 << " SUM : " << h5*5 << endl;

    unsigned long long int histogramsum = h1 + (h2*2) + (h3*3) + (h4*4) + (h5*5); 

    cout << "The sum of the vector is : " << sum << " and the sum of the histogram is " << histogramsum << endl;

    cout << "TOTAL RUNNING TIME IS : " << duration.count() << " milliseconds....";

    return 0;

}

##LAB #4:

In this laboratory, you will be implementing the Producer-Consumer Pattern in a bounded-buffer. Our bounded-buffer of choice is a stack (std::stack - cppreference.comLinks to an external site.). Make the buffer size (stack’s maximum capacity) to not to exceed having 10000 elements inside. This is your shared data.

 

Create a method called producer() this method will generate a random number from 1 to 10 and whatever number it generated it will be pushed into the stack buffer. Sleep for a random time between (1 to 100ms) before adding another number again to the buffer do this for 10000 times. 

 

Create a method called consumer() this method will remove an item in the stack buffer and accumulate the removed(popped) value on a certain variable called SUM.  Sleep for a random time between (1 to 100ms) before removing another number again from the buffer

Please submit the source code and the screenshot of your output

Create your main method to produce four threads (2) Producers and (2) Consumer and take note of the following additional tasks.

Since there are 2 producer() threads that produces 10000 random number each for total of 20000 random numbers, there would come to a point (may or may not) that it would reach the maximum limit of our stack buffer which is 10000. Therefore a producer thread has to wait() before generating again a random number and placing it into the stack. Print “Stack Full Producer Waiting [thread-id]” when producer is waiting
 

The 2 consumer threads will continuously remove an item from the stack, there (may or may not) come to a point where the stack buffer is empty thus the consumer thread has to wait until such time that the stack buffer has content. Print “Stack Empty Consumer Waiting [thread-id]”
 

The program terminates when both producer finishes its job of adding random numbers into the stack and consumer fully consumes all of the numbers from the stack. You have to think of your own mechanism for detecting this one.
 

Display the total sum of all of the numbers before the program ends. (To determine if the sum is correct, create a temporary variable that accumulates too everytime the producer generates a number both of them should match at the end of the program, much like our previous laboratory). Display both values to check if the sum is correct.

##LAB #5:

IMPLEMENT USING SEMAPHORES.

In this laboratory, you will be implementing the Producer-Consumer Pattern in a bounded-buffer using Semaphores. Our bounded-buffer of choice is a stack (std::stack - cppreference.comLinks to an external site.). Make the buffer size (stack’s maximum capacity) to not to exceed having 10000 elements inside. This is your shared data. 

Create a method called producer() this method will generate a random number from 1 to 10 and whatever number it generated it will be pushed into the stack buffer. Sleep for a random time between (1 to 100ms) before adding another number again to the buffer do this for 10000 times. 

Create a method called consumer() this method will remove an item in the stack buffer and accumulate the removed(popped) value on a certain variable called SUM.  Sleep for a random time between (1 to 100ms) before removing another number again from the buffer

Please submit the source code and the screenshot of your output

Create your main method to produce four threads (2) Producers and (2) Consumer and take note of the following additional tasks.

Since there are 2 producer() threads that produces 10000 random number each for total of 20000 random numbers, there would come to a point (may or may not) that it would reach the maximum limit of our stack buffer which is 10000. Therefore a producer thread has to wait() before generating again a random number and placing it into the stack. Print “Stack Full Producer Waiting [thread-id]” when producer is waiting
 
The 2 consumer threads will continuously remove an item from the stack, there (may or may not) come to a point where the stack buffer is empty thus the consumer thread has to wait until such time that the stack buffer has content. Print “Stack Empty Consumer Waiting [thread-id]”

The program terminates when both producer finishes its job of adding random numbers into the stack and consumer fully consumes all of the numbers from the stack. You have to think of your own mechanism for detecting this one.

Display the total sum of all of the numbers before the program ends. (To determine if the sum is correct, create a temporary variable that accumulates too everytime the producer generates a number both of them should match at the end of the program, much like our previous laboratory). Display both values to check if the sum is correct.

##LAB #6:

In this laboratory, you will be converting our single client-server example into a multi client-server setup. By default your server is a C++, The two clients should be of different platform, Use a Java environment and a Python environment. What the program will do is to accept two numbers from the client, pass it on the server, the server will compute for the sum, and sends it back to the client. The client prints the sum

There is a need to convert our server lecture code example to accept multiple clients (as shown on the video example I modified our server lecture example to accept multiple clients, however I specifically ran two Java instances) of course I will not share the code :D because you have to do it yourselves. But ill be giving you tips on how you will do it.
