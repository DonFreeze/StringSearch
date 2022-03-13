#include "TestClient.h"
#include <algorithm> // for shuffle // and sort
#include <random>   // for shuffle
#include <chrono>     // measure execution time


using namespace std;


void TestClient::runTest1()
{
    cout << "---------------------------------------- " << endl;
    cout << "Run Test 1 " << endl;
    WordList expecterResultList;
    expecterResultList.push_back( "AAAA" );

    if( runTest("AAAA", expecterResultList ) )
    {
        cout << "Test succeeded!" << endl;
    }
    else
    {
        cout << "Test failed!" << endl;
    }
    cout << endl;
}

void TestClient::runTest2()
{
    cout << "---------------------------------------- " << endl;
    cout << "Run Test 2 " << endl;
    string testString{ "AB" };
    WordList expecterResultList;
    string letters{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    for( char third : letters )
    {
        for( char fourth : letters )
        {
            expecterResultList.push_back( testString + third + fourth );
            //cout << wordList.words[index] << endl;
        }
    }

    if( runTest( testString, expecterResultList ) )
    {
        cout << "Test succeeded!" << endl;
    }
    else
    {
        cout << "Test failed!" << endl;
    }
    cout << endl;
}


void TestClient::runTest3()
{
    cout << "---------------------------------------- " << endl;
    cout << "Run Test 3 " << endl;
    string testString{ "D" };
    WordList expecterResultList;
    string letters{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    for( char second : letters )
    {
        for( char third : letters )
        {
            for( char fourth : letters )
            {
                expecterResultList.push_back( testString + second + third + fourth );
                //cout << wordList.words[index] << endl;
            }
        }
    }

    if( runTest( testString, expecterResultList ) )
    {
        cout << "Test succeeded!" << endl;
    }
    else
    {
        cout << "Test failed!" << endl;
    }
    cout << endl;
}

/*
void TestClient::runTest4()
{
    string testString{ "34l" };
    WordList expecterResultList;
    string letters{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890" };

    for( char fourth : letters )
    {
        expecterResultList.push_back( testString + fourth );
        //cout << wordList.words[index] << endl;
    }

    if( runTest2( testString, expecterResultList ) )
    {
        cout << "Test succeeded!" << endl;
    }
    else
    {
        cout << "Test failed!" << endl;
    }
}*/

void TestClient::runTest5()
{
    cout << "---------------------------------------- " << endl;
    cout << "Run Test 5 " << endl;
    string testString{ "3e" };
    WordList expecterResultList;

    if( runTest( testString, expecterResultList ) )
    {
        cout << "Test succeeded!" << endl;
    }
    else
    {
        cout << "Test failed!" << endl;
    }
    cout << endl;
}

void TestClient::runTest6()
{
    cout << "---------------------------------------- " << endl;
    cout << "Run Test 6 " << endl;
    string testString{ "AAAAA" };
    WordList expecterResultList;

    if( runTest( testString, expecterResultList ) )
    {
        cout << "Test succeeded!" << endl;
    }
    else
    {
        cout << "Test failed!" << endl;
    }
    cout << endl;
}

bool TestClient::runTest( string testString, WordList& expectedResultList )
{
    cout << "Run Test to find all words with prefix:" << testString << endl;

    auto time1 = chrono::high_resolution_clock::now();
    WordList resultList = stringSearch.search(testString, wordList);
    auto time2 = chrono::high_resolution_clock::now();
    auto durationInMs = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "Search lasted " << durationInMs.count() << " ms" << endl;
    cout << "Expect " << expectedResultList.size() << ", found " << resultList.size() << endl;

    return compareWordLists( resultList, expectedResultList );
}

/*
bool TestClient::runTest2( string testString, WordList& expectedResultList )
{
    cout << "Run Test to find all words with prefix:" << testString << endl;

    auto time1 = chrono::high_resolution_clock::now();
    WordList resultList = stringSearch.search(testString, complexList);
    auto time2 = chrono::high_resolution_clock::now();
    auto durationInMs = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "Search lasted " << durationInMs.count() << " ms" << endl;
    cout << "Expect " << expectedResultList.size() << ", found " << resultList.size() << endl;

    return compareWordLists( resultList, expectedResultList );
}
*/

/*
* Checks if list1 contains same strings as list2, independent of the order
*/
bool TestClient::compareWordLists( WordList& list1, WordList& list2 )
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

    for( char first : letters )
    {
        for( char second : letters )
        {
            for( char third : letters )
            {
                for( char fourth : letters )
                {
                    wordList.push_back( string() + first + second + third + fourth );
                    index++;
                }
            }
        }
    }
    auto randomEngine = std::default_random_engine{};
    std::shuffle( std::begin(wordList), std::end(wordList), randomEngine );
}
/*
void TestClient::generateComplexWordList()
{
    string letters{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890" };
    uint32_t index = 0;

    for( char first : letters )
    {
        for( char second : letters )
        {
            for( char third : letters )
            {
                for( char fourth : letters )
                {
                    complexList.push_back( string() + first + second + third + fourth );
                    index++;

                }
            }
        }
    }
    auto randomEngine = std::default_random_engine{};
    std::shuffle( std::begin(complexList), std::end(complexList), randomEngine );
}
*/
void TestClient::printWordList( WordList& list )
{
    for( string word : wordList )
    {
        cout << word << endl;
    }
}