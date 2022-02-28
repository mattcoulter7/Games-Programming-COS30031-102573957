#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <chrono>
#include <ctime>
#include <random>
#include <fstream>
#include "StopWatch.h"
using namespace std;



int main()
{
    srand(time(NULL));
    fstream output;
    output.open("output.csv", ios::out);
    StopWatch *s = new StopWatch();
    array<int, 6> sizes{100, 1000, 10000, 100000, 1000000, 10000000};
    int const NUM_INSERTIONS = 100;
    output << "iterations,insertions,type,initialisation,looping,inserts\n";
    for (int SIZE : sizes)
    {
        cout << "# VECTOR vs LIST TEST (" << SIZE << ")" << endl;
        cout << "## INITIALISATION TEST" << endl;
        // initialising list
        s->Start();
        list<int> l;
        for (int i = 1; i <= SIZE; ++i)
            l.push_back(i);
        s->Stop();
        int listInitDuration = s->GetDuration();
        cout << "Created list in " << listInitDuration << "microseconds" << endl;
        // initialising vector
        s->Start();
        vector<int> v;
        for (int i = 1; i <= SIZE; ++i)
            v.push_back(i);
        s->Stop();
        int vectorInitDuration = s->GetDuration();
        cout << "Created vector in " << vectorInitDuration << "microseconds" << endl;
        cout << endl;

        cout << "## ITERATOR TEST" << endl;
        // looping through list
        s->Start();
        for (auto it = l.begin(); it != l.end(); ++it)
        {
            (*it);
            //cout << *it;
        }
        s->Stop();
        int listIteratorDuration = s->GetDuration();
        cout << "Looped through list in " << listIteratorDuration << "microseconds" << endl;

        // looping through vector
        s->Start();
        for (auto val : v)
        {
            val;
            //cout << val;
        }
        s->Stop();
        int vectorIteratorDuration = s->GetDuration();
        cout << "Looped through vector in " << vectorIteratorDuration << "microseconds" << endl;
        cout << endl;

        cout << "## " << NUM_INSERTIONS << " INSERTION TEST" << endl;
        array<int, NUM_INSERTIONS> random_insert_indices;
        for (int i = 0; i < NUM_INSERTIONS; i++)
        {
            random_insert_indices[i] = rand() % (NUM_INSERTIONS + i + 1);
        }

        // inserting into list
        s->Start();
        list<int>::iterator list_it;
        for (int i : random_insert_indices)
        {
            list_it = next(l.begin(), i);
            l.insert(list_it, i);
        }
        s->Stop();
        int listInsertionDuration = s->GetDuration();
        cout << "Inserted " << NUM_INSERTIONS << " values into list in " << listInsertionDuration << "microseconds" << endl;

        // inserting into vector
        vector<int>::iterator vector_it;
        s->Start();
        for (int i : random_insert_indices)
        {
            vector_it = next(v.begin(), i);
            v.insert(vector_it, i);
        }
        s->Stop();
        int vectorInsertionDuration = s->GetDuration();
        cout << "Inserted " << NUM_INSERTIONS << " values into vector in " << vectorInsertionDuration << "microseconds" << endl;

        cout << "Finished " << SIZE << " Test" << endl
             << endl;
        output << SIZE << "," << NUM_INSERTIONS << ",LIST," << listInitDuration << "," << listIteratorDuration << "," << listInsertionDuration << "\n";
        output << SIZE << "," << NUM_INSERTIONS << ",VECTOR," << vectorInitDuration << "," << vectorIteratorDuration << "," << vectorInsertionDuration << "\n";
    }
    output.close();

    delete s;
    return 0;
}