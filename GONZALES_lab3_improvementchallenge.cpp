//including thread and mutex libraries
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <mutex>

using namespace std;

//declaring global variables
const long MAX = 500000000;
const int RANGE = 6;
vector<int> num(MAX);
unsigned long long int sum = 0;
int h1=0, h2=0, h3=0, h4=0, h5=0;
mutex mtx;

//count hg by switch case, repeat till max val
void count_histogram(long START, long END)
{
	lock_guard<mutex>lck(mtx);
    for(int i=START; i < END; i++)
    {
        switch(num[i])
        {
            case 1: h1++;
            break;

            case 2: h2++;
            break;

            case 3: h3++;
            break;

            case 4: h4++;
            break;

            case 5: h5++;
            break;
        }
    }
}

//get sum using for loop, and implement mutex + lockguard
void get_sum(long START, long END)
{
	lock_guard<mutex> lck(mtx);
    for (int i = START; i < END; i++)
    {
        sum = sum + num[i];
    }
}


//create threads, call functions, join threads
int main() {
    for (int i = 0; i < MAX; i++) {
        num[i] = rand() % RANGE;
    }

    auto start = chrono::high_resolution_clock::now();

    thread t1(count_histogram, 0, 166666667);
    thread t2(count_histogram, 166666667, 333333334);
    thread t3(count_histogram, 333333334, 500000000);

    thread t4(get_sum, 0, 166666667);
    thread t5(get_sum, 166666667, 333333334);
    thread t6(get_sum, 333333334, 500000000);

    t1.join();
    t2.join();
    t3.join();

    t4.join();
    t5.join();
    t6.join();


    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    //print sums, total, output of running time, and percentage enhancement
    cout << "Histogram Result is : " << endl;
    cout << "1  ----> " << h1 << " SUM : " << h1 << endl;
    cout << "2  ----> " << h1 << " SUM : " << h2*2 << endl;
    cout << "3  ----> " << h1 << " SUM : " << h3*3 << endl;
    cout << "4  ----> " << h1 << " SUM : " << h4*4 << endl;
    cout << "5  ----> " << h1 << " SUM : " << h5*5 << endl;

    unsigned long long int histogramsum = h1 + (h2*2) + (h3*3) + (h4*4) + (h5*5);

    cout << "The sum of the vector is : " << sum << " and the sum of the histogram is " << histogramsum << endl;
    cout << "TOTAL RUNNING TIME IS : " << duration.count() << " milliseconds...."<<endl;

    double cent = (1-(3378.75/7344))*100;
    cout << "Percentage enchancement is : " <<cent <<"%";

    return 0;
}
