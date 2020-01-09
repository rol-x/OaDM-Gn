/// Made by Karol Latos for Optimization and Decision Making laboratories, non-zero sum games (Nash Equilibrium and Minimax Method)

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main()
{
	double A[3][3] = { 3, -2, -1, 0, 3, -2, -1, 20, -1 };
	double B[3][3] = { -1, -2, 15, 4, 4, 2, -2, 1, 0 };
	int size = 3;

	cout << "A (D1):\t\t\t\t\tB (D2):" << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cout << A[i][j] << "  ";
		cout << "\t\t\t\t";
		for (int j = 0; j < size; j++)
			cout << B[i][j] << "  ";
		cout << endl;
	}
	cout << endl;

	double * maxInRow = new double [size];
	double * maxInCol = new double [size];
	for (int i = 0; i < size; i++)
	{
		maxInRow[i] = A[i][0];
		for (int j = 0; j < size; j++)
			if (maxInRow[i] < A[i][j])
				maxInRow[i] = A[i][j];
	}
	for (int j = 0; j < size; j++)
	{
		maxInCol[j] = B[0][j];
		for (int i = 0; i < size; i++)
			if (maxInCol[j] < B[i][j])
				maxInCol[j] = B[i][j];
	}

	vector<int> minMaxRows;
	auto best = maxInRow[0];
	for (int i = 1; i < size; i++)
		if (best > maxInRow[i])
			best = maxInRow[i];
	for (int i = 0; i < size; i++)
		if (best == maxInRow[i])
			minMaxRows.push_back(i);

	vector<int> minMaxCols;
	best = maxInCol[0];
	for (int i = 1; i < size; i++)
		if (best > maxInCol[i])
			best = maxInCol[i];
	for (int i = 0; i < size; i++)
		if (best == maxInCol[i])
			minMaxCols.push_back(i);

	vector<pair<int, int>> minimaxPoints;
	for (auto row : minMaxRows)
		for (auto col : minMaxCols)
			minimaxPoints.push_back(pair<int, int>(row, col));

	auto bestPoint = minimaxPoints[0];
	for (auto point : minimaxPoints)
		if (A[point.first][point.second] <= A[bestPoint.first][bestPoint.second] && B[point.first][point.second] <= B[bestPoint.first][bestPoint.second])
			bestPoint = point;
	for (auto point : minimaxPoints)
		cout << "Minimax strategy (" << point.first + 1 << ", " << point.second + 1 << ") resulting in (" << A[point.first][point.second] << ", " << B[point.first][point.second] << ")" << endl;
	cout << "Best proposition: (" << bestPoint.first + 1 << ", " << bestPoint.second + 1 << ")" << endl;
	cout << endl;
	double minInCol;
	double minInRow;
	vector<pair<int, int>> pointsD1;
	vector<pair<int, int>> pointsD2;
	pair<int, int> point;
	for (int j = 0; j < size; j++)
	{
		minInCol = A[0][j];
		point = pair<int, int>(0, j);
		for (int i = 1; i < size; i++)
			if (minInCol > A[i][j])
			{
				minInCol = A[i][j];
				point = pair<int, int>(i, j);
			}
		for (int i = 0; i < size; i++)
			if (minInCol == A[i][j])
				pointsD1.push_back(pair<int, int>(i, j));
	}
	for (int i = 0; i < size; i++)
	{
		minInRow = B[i][0];
		point = pair<int, int>(i, 0);
		for (int j = 1; j < size; j++)
			if (minInRow > B[i][j])
			{
				minInRow = B[i][j];
				point = pair<int, int>(i, j);
			}
		for (int j = 0; j < size; j++)
				if (minInRow == B[i][j])
					pointsD2.push_back(pair<int, int>(i, j));
	}

	vector<pair<int, int>> nashEqPoints;

	for (auto pointA : pointsD1)
		for (auto pointB : pointsD2)
			if (pointA == pointB)
				nashEqPoints.push_back(pointA);
	if (!nashEqPoints.empty())
	{
		auto bestPoint = nashEqPoints[0];
		for (auto point : nashEqPoints)
			if (A[point.first][point.second] <= A[bestPoint.first][bestPoint.second] && B[point.first][point.second] <= B[bestPoint.first][bestPoint.second])
				bestPoint = point;
		for (auto point : nashEqPoints)
			cout << "Nash equilibrium at (" << point.first + 1 << ", " << point.second + 1 << ") resulting in (" << A[point.first][point.second] << ", " << B[point.first][point.second] << ")" << endl;
		if (nashEqPoints.size() > 1)
			cout << "Best proposition: (" << bestPoint.first + 1 << ", " << bestPoint.second + 1 << ")" << endl;
	}
	else
		cout << "No pure Nash equlibrium found" << endl;


	system("pause");
	return 0;
}
