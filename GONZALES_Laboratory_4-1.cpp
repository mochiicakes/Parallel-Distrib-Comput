#include <iostream>
#include <stack>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include <cstdlib>
#include <condition_variable>

using namespace std;

static stack<int> pc_stack;
int SUM = 0;
int temp_sum = 0;
int consumed_count = 0;
int produced_count = 0;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> random_number(1, 10);
uniform_int_distribution<int> random_sleep(1, 100);
mutex mtx;
condition_variable cv;

void producer(stack<int> &pc_stack)
{
        int buffer = 0;
        
        for (int i = 0; i < 10000; i++)
        {
            buffer = random_number(rng);
            temp_sum += buffer;

            unique_lock<mutex> lock(mtx);
            while (!pc_stack.empty() || pc_stack.size() >= 10000) 
            {
		        if (!pc_stack.empty()) 
                {
		            cout << "Stack Full Producer Waiting [" << this_thread::get_id() << "]" << endl;
		            this_thread::sleep_for(chrono::milliseconds(random_sleep(rng)));
		            break;
		        }		
		        cv.wait(lock);
		    }	
            pc_stack.push(buffer);
            lock.unlock();
            cv.notify_one();
        }
}

void consumer(stack<int> &pc_stack)
{
    for (int i = 0; i < 10000; i++)
    {
        unique_lock<mutex> lock(mtx);
        while (pc_stack.empty())
        {
            cout << "Stack Empty Consumer Waiting [" << this_thread::get_id() << "]" << endl;
            this_thread::sleep_for(chrono::milliseconds(random_sleep(rng)));
            cv.wait(lock);
        }

        SUM += pc_stack.top();
        pc_stack.pop();
        lock.unlock();
        cv.notify_one();
    }
}

int main()
{
    thread t1(producer, ref(pc_stack));
    thread t2(producer, ref(pc_stack));
    thread t3(consumer, ref(pc_stack));
    thread t4(consumer, ref(pc_stack));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    cout << "SUM: " << SUM << endl;
    cout << "Temp SUM: " << temp_sum << endl;
    cout << "Produced Count: " << produced_count << endl;
    cout << "Consumed Count: " << consumed_count << endl;
    if (temp_sum == SUM && produced_count == consumed_count)
    {
        cout << "Producer and Consumer completed their job and the sum is correct." << endl;
    }
    return 0;
}