//https://codility.com/demo/results/training4M2QEN-3PD/
#include <cassert>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;

/*
 * Naive solution
 *
 * Since we deal with average here, at least a pair of elements should be examined each step
 * From the example it gives, it's an easy observation that the ith and (i+1)th should be checked
 * on each step. In [4,2,2], [2,2] has a smaller avg than [4,2]; However, it's also possible that
 * 3 continuous elements could have an even lower avg, say [-8,-4,-10]. I don't have an example on top
 * of my head to qualify tree elements min avg with all positive numbers.
 *
 * So, based upon the observation above, we will loop the array start from 1 (assuming we take A[0] and A[1]
 * as the starting value already) and end at len-2. On each step, both i and i+1 th elements will be checked:
 *
 * 1. If (A[i]+A[i+1])/2.0 is smaller than the previous avg min; If yes, reset startidx to i and update avg min.
 * 2. If current sum plus A[i] and then divided by the number of elements is smaller than previous avg min;
 *    if yes, update avg min.
 * 3  If neither of above is satisfied, we have found the min avg end at index i-1, reset current sum to max value
 *    and then move i backward 1 to i-1, also reset number count to 1;
 * 4. According to the above 3 steps, we now can update the avg min so far and start index of current avg-min sequence 
 */
int solutionMinAvgTwoSlice(vector<int> &A)
{
    int len = A.size() - 1;
    assert(len>0);
    double avgminsofar = (A[0] + A[1])/2.0;
    double minendhere = (A[0] + A[1]);
    double tmp, tmp1;
    int sidx = 0, minidx = 0, cnt = 2;
    for (int i = 1; i<len; ++i)
    {
	tmp = (A[i] + A[i + 1]) / 2.0;
	tmp1 = (minendhere + A[i + 1]) / (cnt + 1);
	if (tmp < tmp1 && tmp < minendhere / cnt)
	{
	    minendhere = (A[i] + A[i + 1]);
	    sidx = i;
	    cnt = 2;
	}
	else if (tmp1 < tmp && tmp1 < minendhere / cnt)
	{
	    minendhere += A[i + 1];
	    ++cnt;
	}
	else
	{
	    minendhere = std::numeric_limits<double>::max();
	    cnt = 1;
	    --i;
	}
	if (avgminsofar>minendhere / cnt)
	{
		minidx = sidx;
		avgminsofar = minendhere / cnt;
	}
    }
    return minidx;
}
void testMinAvgTwoSlice()
{
    cout << "Expect 1: " << solutionMinAvgTwoSlice(vector<int>({ 4, 2, 2, 5, 1, 5, 8 })) << endl;
    cout << "Expect 1: " << solutionMinAvgTwoSlice(vector<int>({ 4, -2, 2, 5, 1, 5, 8 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ 4, 2 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ -4, -2, -1, -3 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ -1, -1, -1, -1 })) << endl;
    cout << "Expect 2: " << solutionMinAvgTwoSlice(vector<int>({ -1, -2, -3, -4 })) << endl;
    cout << "Expect 2: " << solutionMinAvgTwoSlice(vector<int>({ -3, -5, -8, -4, -10 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ -8, -4, -10 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ 4, -10, 5, 10, -5, 8 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ -1, -1, 0, 0, -1, -1, -1 })) << endl;
}	 