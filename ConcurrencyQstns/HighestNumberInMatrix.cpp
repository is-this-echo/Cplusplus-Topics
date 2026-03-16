#include <iostream>
#include <vector>
#include <thread>
#include <limits>
#include <algorithm>
#include <future>

using namespace std;


/*
Multithreading – scenario: find highest number in a random matrix[N][M] using threads.
- how you divide work
- how you avoid data races
- whether you understand false sharing / contention
- clean C++ thread usage

Bad approach
-------------
All threads update a shared global max:
globalMax = max(globalMax, value); // needs mutex every iteration
This causes:
- heavy locking
- terrible performance
- race conditions if no mutex


Correct approach (Two-phase reduction)
--------------------------------------
Each thread computes local maximum
Store in thread-local result array
Main thread reduces to final maximum

This is the standard parallel reduction pattern : 
- lock-free during scanning
- minimal synchronization
- cache-friendly

Thought process:
I divide the matrix rows among threads, each computes a local maximum without synchronization,
then the main thread reduces them. This avoids contention and follows the standard parallel reduction pattern.

Time complexity
----------------
Work per thread	  O(N*M / T)
Thread creation	  O(T)
Reduction	      O(T)
Total           O(N*M / T + T)

*/

int findMaxInRange(
const vector<vector<int>>& mat,
    int startRow,
    int endRow)
{
    int localMax = numeric_limits<int>::min();

    for (int i = startRow; i < endRow; ++i)
        for (int v : mat[i])
            localMax = max(localMax, v);

    return localMax;
}

// Version using std::thread
int parallelMatrixMax(const vector<vector<int>>& mat, int numThreads)
{
    int rows = mat.size();
    vector<thread> threads;
    vector<int> localMax(numThreads, numeric_limits<int>::min());

    // This is just ceil(rows / numThreads). If rows aren’t divisible, we still need to cover all rows
    int chunk = (rows + numThreads - 1) / numThreads;

    for (int t = 0; t < numThreads; ++t)
    {
        int start = t * chunk;
        int end   = min(start + chunk, rows);

        if (start >= rows) break;

        threads.emplace_back([&, t, start, end]()
        {
            localMax[t] = findMaxInRange(mat, start, end);
        });
    }

    for (auto& th : threads)
        th.join();

    return *max_element(localMax.begin(), localMax.end());
}


/*
Even Better (Avoid False Sharing)

The previous solution might suffer false sharing because:
localMax[0], localMax[1], localMax[2] may lie in same cache line.

Fix:
struct alignas(64) PaddedInt
{
    int value;
};

Use:
vector<PaddedInt> localMax(numThreads);
*/


// Using std::async
int parallelMatrixMaxAsync(const vector<vector<int>>& mat, int numThreads)
{
    int rows = mat.size();
    int chunk = (rows + numThreads - 1) / numThreads;

    vector<future<int>> futures;
    for (int t = 0; t < numThreads; ++t)
    {
        int start = t * chunk;
        int end   = min(start + chunk, rows);

        if (start >= rows) break;

        futures.push_back(std::async(std::launch::async, [&, start, end]
        {
            return findMaxInRange(mat, start, end);
        }));
    }

    int globalMax = std::numeric_limits<int>::min();

    for (auto& f : futures)
        globalMax = max(globalMax, f.get());

    return globalMax;
}


/*
Follow-up qstsn
---------------
What if matrix is HUGE?
-> use thread pool

What if streaming data?
-> use atomic max with compare_exchange

How to choose thread count?
-> std::thread::hardware_concurrency()

Why not mutex global max?
-> contention + poor scaling

*/


int main()
{
    
    return 0;
}