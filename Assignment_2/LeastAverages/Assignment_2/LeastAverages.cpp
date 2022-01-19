#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Point
{
public:
	int x;
	double y;

	Point(int i = 0, int j = 0) : x(i), y(j) {}
};

void findSegmentedLeastAverage(vector<Point>& points, int penalty, vector<pair<int, int>>& segments)
{
	int n = points.size();
	vector<int> ySum(n + 1, 0);
	vector<int> ySquareSum(n + 1, 0);
	vector<vector<double>> error(n + 1, vector<double>(n + 1, 0));
	vector<pair<double, int>> optimal(n + 1, { 0, 0 });

	for (int j = 1; j <= n; j++)
	{
		ySum[j] = points[j - 1].y + ySum[j - 1];
		ySquareSum[j] = points[j - 1].y * points[j - 1].y + ySquareSum[j - 1];

		for (int i = 1; i <= j; i++)
		{
			double y_sq_sum_cur = ySquareSum[j] - ySquareSum[i - 1];
			double y_sum_cur = ySum[j] - ySum[i - 1];
			double mean_cur = y_sum_cur / (j - i + 1);
			error[i][j] = y_sq_sum_cur - (mean_cur * y_sum_cur);
		}
	}

	for (int j = 1; j <= n; j++)
	{
		double min_error = DBL_MAX;
		for (int i = 1; i <= j; i++)
		{
			double curVal = error[i][j] + optimal[i - 1].first + penalty;
			if (curVal < min_error)
			{
				min_error = curVal;
				optimal[j] = { curVal, i };
			}
		}
	}

	for (int i = n, j = optimal[n].second; i > 0; i = j - 1, j = optimal[i].second)
	{
		segments.push_back({ j , i});
	}

	for (auto i = segments.rbegin(); i != segments.rend(); i++)
	{
		cout << "\n The Segment Starts with " << points[i->first - 1].x << " and ends with " << points[i->second - 1].x << " ,has the cost " << error[i->first][i->second] << "\n";
	}
}

int main(void)
{
	vector<Point> points = { {1,6}, {2, 5}, {3,1}, {4,6}, {7, 3}, {8, 5}, {9,9} };
	//vector<Point> points = { {1,6}, {2, 6}, {3,6}, {4,2}, {7, 2}, {8, 9}, {9,9} };
	sort(points.begin(), points.end(), 
		[](const Point& p1, const Point& p2)
		{
			return p1.x < p2.x;
		});
	vector<pair<int, int>> segments;
	int penalty = 20;
	cout << "Penalty is " << penalty << endl;
	findSegmentedLeastAverage(points, penalty, segments);
	return 0;
}
