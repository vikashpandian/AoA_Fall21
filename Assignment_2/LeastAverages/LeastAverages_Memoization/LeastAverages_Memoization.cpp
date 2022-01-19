#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Point
{
public:
	int x;
	double y;

	Point(int i = 0, int j = 0) : x(i), y(j) {}
};

double computeError(vector<Point>& points, int start, int end, unordered_map<int, pair<int,int>>& dpSum)
{
	double sum = 0, squaredSum = 0;
	for (int i = start; i <= end; i++)
	{
		sum += points[i].y;
		squaredSum += (points[i].y * points[i].y);
	}
	double error = squaredSum - (sum * sum / (end - start + 1));
	return error;
}

double findSegmentedLeastAverage(vector<Point>& points, int start, int end, int penalty, vector<pair<int, int>>& optimal, unordered_map<int, pair<int, int>>& dpSum, unordered_map<int, double>& memo)
{
	double minError = DBL_MAX;
	int bestSegment = end;
	for (int i = start; i <= end; i++)
	{
		double curError = computeError(points, i, end, dpSum);
		if (i > start)
		{
			if (!memo.count(i - 1))
			{
				memo.insert({ i - 1, findSegmentedLeastAverage(points, start, i - 1, penalty, optimal, dpSum, memo) });
			}
			curError += memo[i - 1];
		}
		if (curError <= minError)
		{
			minError = curError;
			bestSegment = i;
		}
	}
	optimal.push_back({ bestSegment, end });
	double finalError = minError + penalty;
	return finalError;
}

int main(void)
{
	//vector<Point> points = { {1,6}, {2, 5}, {3,1}, {4,6}, {7, 3}, {8, 5}, {9,9} };
	vector<Point> points = { {1,6}, {2, 6}, {3,6}, {4,2}, {7, 2}, {8, 9}, {9,9} };
	sort(points.begin(), points.end(),
		[](const Point& p1, const Point& p2)
		{
			return p1.x < p2.x;
		});
	vector<pair<int, int>> optimal;
	vector<pair<int, int>> segments;
	unordered_map<int, pair<int, int>> dpSum;
	unordered_map<int, double> memo;
	findSegmentedLeastAverage(points, 0, points.size() - 1, 5, optimal, dpSum, memo);

	for (int i = optimal.size() - 1; i >= 0; i = optimal[i].first - 1)
	{
		segments.push_back({ points[optimal[i].first].x , points[optimal[i].second].x });
	}

	for (auto i = segments.rbegin(); i != segments.rend(); i++)
	{
		cout << "\n" << i->first << "\t" << i->second << "\n";
	}

	return 0;
}

