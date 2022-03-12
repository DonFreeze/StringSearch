#include "TestClient.h"
#include <algorithm> // for shuffle // and sort
#include <random>   // for shuffle
#include <chrono>     // measure execution time


using namespace std;


void TestClient::runTest1()
{
    WordList expecterResultList;
    expecterResultList.push_back("AAAA");

    if (runTest("AAAA", expecterResultList))
    {
        cout << "Test1 succeeded!" << endl;
    }
    else
    {
        cout << "Test1 failed!" << endl;
    }
}

void TestClient::runTest2()
{
    string testString{ "AB" };
    WordList expecterResultList;
    string letters{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    for (char third : letters)
    {
        for (char fourth : letters)
        {
            expecterResultList.push_back(testString + third + fourth);
            //cout << wordList.words[index] << endl;
        }
    }

    if (runTest(testString, expecterResultList))
    {
        cout << "Test2 succeeded!" << endl;
    }
    else
    {
        cout << "Test2 failed!" << endl;
    }
}


void TestClient::runTest3()
{
    string testString{ "D" };
    WordList expecterResultList;
    string letters{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    for (char second : letters)
    {
        for (char third : letters)
        {
            for (char fourth : letters)
            {
                expecterResultList.push_back(testString + second + third + fourth);
                //cout << wordList.words[index] << endl;
            }
        }
    }

    if (runTest(testString, expecterResultList))
    {
        cout << "Test3 succeeded!" << endl;
    }
    else
    {
        cout << "Test2 failed!" << endl;
    }

}


bool TestClient::runTest(string testString, WordList& expectedResultList)
{
    cout << "Run Test to find all words with prefix:" << testString << endl;

    auto time1 = chrono::high_resolution_clock::now();
    WordList resultList = stringSearch.search(testString, wordList);
    auto time2 = chrono::high_resolution_clock::now();
    auto durationInMs = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "Search lasted " << durationInMs.count() << " ms" << endl;
    cout << "Expect " << expectedResultList.size() << ", found " << resultList.size() << endl;

    return compareWordLists(resultList, expectedResultList);
}

/*
* Checks if list1 contains same strings as list2, independent of the order
*/
bool TestClient::compareWordLists(WordList& list1, WordList& list2)
{
    // sort lists to ease compare
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    return list1 == list2 ? true : false;
}

void TestClient::generateWordList()
{
    string letters{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    uint32_t index = 0;

    for (char first : letters)
    {
        for (char second : letters)
        {
            for (char third : letters)
            {
                for (char fourth : letters)
                {
                    wordList.push_back(string() + first + second + third + fourth);
                    index++;
                }
            }
        }
    }
    auto randomEngine = std::default_random_engine{};
    std::shuffle(std::begin(wordList), std::end(wordList), randomEngine);
}

void TestClient::printWordList(WordList& list)
{
    for (string word : wordList)
    {
        cout << word << endl;
    }
}