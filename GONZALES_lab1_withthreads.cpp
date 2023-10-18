#include <iostream>

#include <thread>


using namespace std;


void f_firstw() {

    for (int i = 0; i < 1000; i++) {

        cout << "I ";

    }

}


void f_secw() {

    for (int i = 0; i < 1000; i++) {

        cout << "GOT ";

    }

}


void f_thirdw() {

    for (int i = 0; i < 1000; i++) {

        cout << "NOBODY ";

    }

}


void f_fourthw() {

    for (int i = 0; i < 1000; i++) {

        cout << "BUT ";

    }

}


void f_fifthw() {

    for (int i = 0; i < 1000; i++) {

        cout << "YOU ";

    }

}



int main()

{

    thread t1(f_firstw);
    thread t2(f_secw);
    thread t3(f_thirdw);
    thread t4(f_fourthw);
    thread t5(f_fifthw);



    t1.join();

    t2.join();

    t3.join();

    t4.join();

    t5.join();


    return 0;

}