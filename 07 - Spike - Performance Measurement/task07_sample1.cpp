#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include "../06 - Lab - Data Structure Basics/StopWatch.h"
#pragma optimize( "", off )

using namespace std;
using namespace std::chrono;

// - count char using slow repeated string::find_first_of
int count_char_using_find_first_of(string s, char delim)
{
    int count = 0;
    // note: string::size_type pos = s.find_first_of(delim);
    auto pos = s.find_first_of(delim);
    while ((pos = s.find_first_of(delim, pos)) != string::npos)
    {
        count++;
        pos++;
    }
    return count;
}

// - count char using fast std::count
int count_char_using_count(string s, char delim)
{
    return count(s.begin(), s.end(), delim);
}
// generate random string of length (https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c)
string gen_random(const int len) {
    
    std::string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    srand( (unsigned) time(NULL) * getpid());

    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) 
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    
    
    return tmp_s;
}

void function_comparison_test()
{
    cout << "# Function Comparison Test " << endl;
    StopWatch s = StopWatch();

    for (int i = 0; i < 5; i++){
        int string_length = i * 1000000;
        string s1 = gen_random(string_length);

        cout << "## " << string_length << endl;
        s.Start("count_char_using_find_first_of");
        count_char_using_find_first_of(s1, 's');
        s.Stop();
        int duration1 = s.GetDuration();

        s.Start("count_char_using_count");
        count_char_using_count(s1, 's');
        s.Stop();
        int duration2 = s.GetDuration();
    }
}

void sort_vector(){
    vector<int> v{ 1, 5, 8, 9, 6, 7, 3, 4, 2, 0 };

    sort(v.begin(), v.end());
}

void create_fill_sum_vector(unsigned long long int size){
    vector<int> v(size, 42);
    accumulate(v.begin(), v.end(), 0u);
}

void single_function_test()
{
    cout << "# Single Function Test " << endl;
    StopWatch s = StopWatch();
    s.Start("sort_vector");
    sort_vector();
    s.Stop();
}
void multiple_function_test()
{
    cout << "# Multiple Function Test " << endl;
    StopWatch s = StopWatch();
    s.Start("sort_vector 1000000 times");
    // run the sort 1000000 times
    for (int i = 0; i < 1000000; i++){
        sort_vector();
    }
    s.Stop();
}

void exponential_rampup_test()
{
    cout << "# Exponential Ramp-up Test " << endl;
    StopWatch s = StopWatch();

    for (auto size = 1ull; size < 1000000000ull; size *= 100)
    {
        s.Start(to_string(size));
        create_fill_sum_vector(size);
        s.Stop();
    }
}

void linear_rampup_test()
{
    cout << "# Linear Ramp-up Test " << endl;
    StopWatch s = StopWatch();

    for (auto size = 1; size <= 5; size += 1)
    {
        int vec_size = size * 10000;
        s.Start(to_string(vec_size));
        create_fill_sum_vector(vec_size);
        s.Stop();
    }
}

void exponential_rampdown_test()
{
    cout << "# Exponential Ramp-down Test " << endl;
    StopWatch s = StopWatch();

    for (auto size = 100000000ull; size > 0; size /= 100)
    {
        s.Start(to_string(size));
        create_fill_sum_vector(size);
        s.Stop();
    }
}

void linear_rampdown_test()
{
    cout << "# Linear Ramp-down Test " << endl;
    StopWatch s = StopWatch();

    for (auto size = 5; size > 0; size--)
    {
        int vec_size = size * 10000;
        s.Start(to_string(vec_size));
        create_fill_sum_vector(vec_size);
        s.Stop();
    }
}

int main()
{
    /* 
        1. Single Tests: Demonstrate how to measure both single and multiple function execution time. 
    */
    single_function_test();
    multiple_function_test();

    /*
        2. Ramp-up Test: Execute and show, with numbers and a chart, both linear and exponential ramp-up testing of
        function execution time. Is there a difference to ramp-down tests? 
    */
    linear_rampup_test();
    linear_rampdown_test();
    exponential_rampup_test();
    exponential_rampdown_test();

    /* 
        3. Repeatability: Show, with numbers and a chart, how repeatability will vary depending on test conditions. 
    */
    // run the solution multiple times to see how the results can change.

    /* 
        4. Function Comparison: There are two "char in string” counting functions provided (code sample 1). Clearly
        show the difference in performance (if any), and check if the execution time difference is linear with respect
        to string length (size).
        (Note, you will probably want to create random strings of the various size to test with.) 
    */
    function_comparison_test();

    /* 
        5. IDE Settings: Show what, if any, is the difference in execution time between debug settings and release
        settings. (Remember to have a task that runs for long enough that it matters.)
    */
    // run the solution through a script as opposed to IDE Debugger and analyuse the differences

    /*
        6. Compiler Settings: Turn down/off compiler optimisation and demonstrate a difference. (Make a note of how
        to do this so that a team member would be able to reproduce your result.)
    */
    // add #pragma optimize( "", off ) to headers

    string wait;
    cin >> wait;
    return 0;
}
