#include <iostream>
#include <thread>
#include <stack>
#include <cstdlib>
#include <chrono>
#include <random>
#include <semaphore>

using namespace std;

const int MAX = 10000;

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> num(1, 10);
uniform_int_distribution<int> slp(1, 100);
binary_semaphore producer_s(0), consumer_s(0), main_s(0); 
long int tracker = 0;
long int globalSum = 0;


void producer(stack<int> &s) // Producer
{
    int inputStack = 0;
    producer_s.acquire(); 
    cout << "Inside Producer" << this_thread::get_id() << endl; 

    for (int i = 0; i < MAX; i++)
    {
        inputStack = num(gen); 
        tracker += inputStack; 
        s.push(inputStack); 
        cout << "Producer Working" << this_thread::get_id() << endl; 
        this_thread::sleep_for(chrono::milliseconds(slp(gen))); 
    }

    cout << "Stack Full - Producer Waiting " << this_thread::get_id() << endl; 
    main_s.release();
}

void consumer(stack<int> &s) // Consumer 
{
    int localSum = 0;

    consumer_s.acquire(); 
    cout << "Inside Consumer" << endl;

    for (int i = 0; i < MAX; i++)
    {
        localSum += s.top();
        s.pop();
        cout << "Consumer Working" << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::milliseconds(slp(gen)));
    }

    globalSum += localSum;
    cout << "Stack Empty - Consumer Waiting " << this_thread::get_id() << endl;
    main_s.release(); 
}

int main()
{
    stack<int> s; 

    thread p1(producer, ref(s));
    thread c1(consumer, ref(s));
    thread p2(producer, ref(s));
    thread c2(consumer, ref(s));

    cout << "Executing p1" << endl;
    producer_s.release();
    p1.join();

    cout << "Executing c1" << endl;
    main_s.acquire();
    consumer_s.release();
    c1.join();

    cout << "Executing p2" << endl;
    main_s.acquire();
    producer_s.release();
    p2.join();

    cout << "Executing c2" << endl;
    main_s.acquire();
    consumer_s.release();
    c2.join();

    main_s.acquire();

    cout << "\n==================================" << endl;
    cout << "Total  : " << globalSum << endl;
    cout << "Tracker : " << tracker << endl; 

    return 0;
}