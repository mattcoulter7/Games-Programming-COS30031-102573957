#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class StopWatch
{
public:
    StopWatch(){
        task = "";
    }
    void Start()
    {
        start = high_resolution_clock::now();
    };
    void Start(string message)
    {
        Start();
        task = message;
        cout << "* Starting " << task << "," << endl;
    };
    void Stop()
    {
        end = high_resolution_clock::now();
        if (task.length() > 0){
            cout << "* Completed " << task << " in " << GetDuration() << " SI" << endl << endl;
            task = "";
        }
    };
    long GetDuration()
    {
        auto duration = duration_cast<microseconds>(end - start);
        return duration.count();
    }

private:
    string task;
    time_point<high_resolution_clock> start;
    // Some computation here
    time_point<high_resolution_clock> end;
};