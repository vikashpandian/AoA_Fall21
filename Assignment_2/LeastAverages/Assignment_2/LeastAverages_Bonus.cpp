#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Point
{
public:
	int x;
	int y;
	double z;

	Point(int i = 0, int j = 0, int k = 0) : x(i), y(j), z(k) {}
};

void findSegmentedLeastAverage(vector<Point>& points, int penalty, vector<pair<int, int>>& segments)
{
	int n = points.size();
	vector<int> y_sum(n + 1, 0);
	vector<int> y_square_sum(n + 1, 0);
	vector<vector<double>> error(n + 1, vector<double>(n + 1, 0));
	vector<pair<int, int>> optimal(n + 1, { 0, 0 });

	for (int j = 1; j <= n; j++)
	{
		y_sum[j] = points[j - 1].y + y_sum[j - 1];
		y_square_sum[j] = points[j - 1].y * points[j - 1].y + y_square_sum[j - 1];

		for (int i = 1; i <= j; i++)
		{
			int y_sq_sum_cur = y_square_sum[j] - y_square_sum[i - 1];
			int y_sum_cur = y_sum[j] - y_sum[i - 1];
			double mean_cur = y_sum_cur / (j - i + 1);
			error[i][j] = y_sq_sum_cur - (mean_cur * y_sum_cur);
		}
	}

	for (int j = 1; j <= n; j++)
	{
		double min_error = DBL_MAX;
		for (int i = 1; i <= j; i++)
		{
			auto curVal = error[i][j] + optimal[i - 1].first;
			if (curVal < min_error)
			{
				min_error = curVal;
				optimal[j].first = curVal + penalty;
				optimal[j].second = i;
			}
		}
	}

	for (int i = n, j = optimal[n].second; i > 0; i = j - 1, j = optimal[i].second) {
		segments.push_back({ j , i });
	}

	for (auto i = segments.rbegin(); i != segments.rend(); i++)
	{
		cout << "\n" << i->first << "\t" << i->second << "\t" << error[i->first][i->second] << "\n";
	}
}

int main(void)
{
	vector<Point> points = { {1,6}, {2, 5}, {3,1}, {4,6}, {7, 3}, {8, 5}, {9,9} };
	//vector<Point> points = { {1,6}, {2, 6}, {3,6}, {4,2}, {7, 2}, {8, 9}, {9,9} };
	sort(points.begin(), points.end(), [](const Point& p1, const Point& p2)
		{
			return p1.x < p2.x;
		});
	vector<pair<int, int>> segments;
	findSegmentedLeastAverage(points, 5, segments);
	return 0;
}
