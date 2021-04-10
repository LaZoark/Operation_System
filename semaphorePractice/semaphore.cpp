#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <ctime>
#include <cstdlib>


using namespace std;
int rant()
{
    int x = rand()%(1000-300+1)+300;
    return x;
}

class Semaphore
{
private:
    mutex mtx;
    condition_variable cv;
    int count;
    int tid;

public:
    Semaphore (int id, int count_ = 0)  :  count(count_)
    {
        tid = id;
        run();
    }
    inline void notify()       // signal() = V() = release()
    {
        unique_lock<mutex> lock(mtx);
        count++;
        cv.notify_one();        //notify the waiting thread
    }
    inline void wait()         // wait() = P() = acquire()
    {
        unique_lock<mutex> lock(mtx);
        while(count == 0)
            cv.wait(lock);        // wait on the mutex until notify is called
        count--;
    }

    int busy()
    {
        int sleeptime = rant();
        this_thread::sleep_for(chrono::milliseconds(sleeptime));
        return sleeptime;
    }
    void noncritical()
    {
        printf("Thread %d is NON critical\n", tid );
        busy();
    }
    void critical()
    {
        printf("Thread %d entering critical section\n", tid);
        busy();
        printf("Thread %d leaving critical section\n", tid);
    }
    void run()
    {
        for(int i=0; i<3; ++i)
        {
            noncritical();
            wait();
            critical();
            notify();
        }
    }

};
void call_run(int id)
{
    srand(id);
    Semaphore sem(id,1);
}

int main()
{

    int N =4;
    thread p[2*N];
//    thread * p;
// spawn 2*N threads:
    for(int j=0; j<2*N; j++)
    {

        p[j] = thread(&call_run,j);
    }
    for( auto& th : p)
        th.join();

//    thread t(call_run,N);
//    t.join();
    /*
        thread s1([&]()
        {
            while(1)
            {
    //            cout<<"this is s1, rand = "<<sem.rant()<<endl;
    //            this_thread::sleep_for(chrono::milliseconds(sem.rant()));
                cout<<sem.busy()<<endl;
                sem.wait( 1 );
            }
        });
        thread s2([&]()
        {
            while(true)
            {
                sem.wait( 2 );
            }
        });
        thread s3([&]()
        {
            while(true)
            {
    //            this_thread::sleep_for(chrono::milliseconds(sem.rant()));
                cout<<sem.busy()<<endl;
                sem.wait( 3 );
            }
        });
        thread s4([&]()
        {
            while(true)
            {
                this_thread::sleep_for(chrono::milliseconds(500));
                sem.notify( 4 );
            }
        });

        s1.join();
        s2.join();
        s3.join();
        s4.join();
        */
}
