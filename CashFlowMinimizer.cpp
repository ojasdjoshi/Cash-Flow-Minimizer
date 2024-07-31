#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

struct minHeapCmp
{
    bool operator()(pair<int, int> &p1, pair<int, int> &p2)
    {
        return p1.second < p2.second;
    }
};

struct maxHeapCmp
{
    bool operator()(pair<int, int> &p1, pair<int, int> &p2)
    {
        return p1.second > p2.second;
    }
};

class Solution
{
private:
    priority_queue<pair<int, int>, vector<pair<int, int>>, minHeapCmp> minHeap;
    priority_queue<pair<int, int>, vector<pair<int, int>>, maxHeapCmp> maxHeap;

    void constructHeaps(vector<int> &netAmount)
    {
        for (int i = 0; i < netAmount.size(); i++)
        {
            if (netAmount[i] > 0)
                maxHeap.emplace(i, netAmount[i]);
            else if (netAmount[i] < 0)
                minHeap.emplace(i, netAmount[i]);
        }
    }

    void solveTransaction()
    {
        while (!minHeap.empty() && !maxHeap.empty())
        {
            pair<int, int> maxCredit = maxHeap.top();
            maxHeap.pop();

            pair<int, int> maxDebit = minHeap.top();
            minHeap.pop();

            int transactionVal = maxCredit.second + maxDebit.second;
            int amntOwed = 0;

            if (transactionVal == 0)
                amntOwed = maxCredit.second;

            else if (transactionVal > 0)
            {
                amntOwed = -maxDebit.second;
                maxHeap.emplace(maxCredit.first, transactionVal);
            }

            else
            {
                amntOwed = maxCredit.second;
                minHeap.emplace(maxDebit.first, transactionVal);
            }

            cout << "Person " << maxDebit.first << " has to pay " << amntOwed << " to person " << maxCredit.first << endl;
        }
    }

public:
    void minCashFlow(vector<vector<int>> &graph)
    {
        vector<int> netAmount(graph.size(), 0);
        for (int i = 0; i < graph.size(); i++)
        {
            for (int j = 0; j < graph.size(); j++)
            {
                netAmount[i] += graph[j][i] - graph[i][j];
            }
        }

        constructHeaps(netAmount);
        solveTransaction();
    }
};

int main()
{
    vector<vector<int>> graph = {{0, 1000, 2000},
                                 {0, 0, 5000},
                                 {0, 0, 0}};
    cout << "Solution 1 : " << endl;
    Solution S;
    S.minCashFlow(graph);
}
