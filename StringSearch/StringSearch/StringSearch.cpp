#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <windows.h>


#include "StringSearch.h"


using namespace std;

StringSearch::StringSearch()
{
    
}

void StringSearch::executeSearch( std::promise<WordList>&& promise, string searchString, string* searchBeginPtr, size_t length)
{
    WordList resultList;
    mutex mtx;
    mtx.lock();
    if (searchBeginPtr != nullptr)
    {
        for (int i = 0; i < length; i++)
        {
            if (searchBeginPtr[i].rfind(searchString, 0) == 0) // pos=0 limits the search to the prefix
            {
                resultList.push_back(searchBeginPtr[i]);
            }
        }
        promise.set_value(resultList);
    }
    mtx.unlock();
}

void someFunction( std::promise<WordList>&& promise, string searchString, string* searchBeginPtr, size_t length )
{
    WordList resultList;
    mutex mtx;
    mtx.lock();
    if( searchBeginPtr != nullptr )
    {
        for( int i = 0; i < length; i++ )
        {
            if( searchBeginPtr[i].rfind(searchString, 0) == 0 ) // pos=0 limits the search to the prefix
            {
                resultList.push_back(searchBeginPtr[i]);
            }
        }
        promise.set_value(resultList);
    }
    mtx.unlock();
}

WordList StringSearch::search( string searchString, WordList& wordList )
{
    const int numberCpuCores = std::thread::hardware_concurrency();
    static constexpr int threadNum = 4;
    thread threads[threadNum];
    WordList listParts[threadNum];
    WordList resultLists[threadNum];

    std::promise<WordList> promises[threadNum];
    std::future<WordList> futures[threadNum];

    size_t partSize = wordList.size() / threadNum;
    size_t leftover = wordList.size() % threadNum;
    cout << "WordList Begin : " << &wordList.front() << endl;
    cout << "WordList End :   " << &wordList.back() << endl;
    for (int index = 0; index < threadNum; index++)
    {
        futures[index] = promises[index].get_future();
        
        if (index == threadNum-1)
        {
            partSize += leftover;
        }       
        threads[index] = thread( &StringSearch::executeSearch, this, std::move( promises[index] ), searchString, wordList.data() + partSize * index, partSize );
        cout << "PartList Begin : " << wordList.data() + partSize * index << endl;
        cout << "PartList End :   " << wordList.data() +  (partSize * index) + partSize - 1 << endl;

        //threads[index] = thread(executeSearch, searchString, listParts[index], resultLists[index]);
    }

    // Get results from threads and combine them
    WordList resultList;
    for( int i = 0; i < threadNum; i++ )
    {
        resultLists[i] = futures[i].get();
        resultList.insert( resultList.end(), resultLists[i].begin(), resultLists[i].end() );
        threads[i].join();
    }

    /*for (string word : resultList)
    {
        cout << word << endl;
    }*/
 

     return resultList;


}
