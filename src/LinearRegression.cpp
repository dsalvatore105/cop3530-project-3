#include "LinearRegression.h"
#include <algorithm>
#include <vector>

double LR::getLinearRegression(vector<vector<int>> data, int dp, double X) {
	// Truncate to dp
	if (data.size() > dp) {
		data.resize(dp);
	}

	// where X = Sqr Ftg and Y = Price
	vector<double> X_i;
	vector<double> Y_i;

	for (auto& row : data) {
		X_i.push_back(row[1]);
		Y_i.push_back(row[2]);
	}

	int SIZE = X_i.size();

	// Calculate means
	double X_MEAN = 0;
	double Y_MEAN = 0;
	for (auto& v : X_i) {
		X_MEAN += v;
	}
	X_MEAN /= X_i.size();
	for (auto& v : Y_i) {
		Y_MEAN += v;
	}
	Y_MEAN /= Y_i.size();

	// Calculate X_i - X_MEAN
	vector<double> X_deviance;
	for (auto& v : X_i) {
		X_deviance.push_back(v - X_MEAN);
	}

	// Calculate Y_i - Y_MEAN
	vector<double> Y_deviance;
	for (auto& v : Y_i) {
		Y_deviance.push_back(v - Y_MEAN);
	}

	// Calculate (X_i - X_MEAN)(Y_i - Y_MEAN)
	vector<double> Deviance_Product;
	for (int i = 0; i < SIZE; i++) {
		Deviance_Product.push_back(X_deviance[i] * Y_deviance[i]);
	}

	// Calculate (X_i - X_MEAN)^2
	vector<double> X_deviance_sqr;
	for (auto& v : X_deviance) {
		X_deviance_sqr.push_back(v * v);
	}

	// Calculate Slope
	double B_1 = 0;
	for (int i = 0; i < SIZE; i++) {
		B_1 += Deviance_Product[i];
	}
	double sum = 0;
	for (auto& v : X_deviance_sqr) {
		sum += v;
	}
	B_1 /= sum;

	// Calculate Intercept
	double B_0 = Y_MEAN - (B_1 * X_MEAN);

	//cout << "Y = " << B_1 << "x + " << B_0 << endl;
	return B_0 + B_1 * X;
}

double LR::getMultLinearRegression(vector<vector<int>> data, int dp, double X1, double X2) {
	if (data.size() > dp) {
		data.resize(dp);
	}

	// where X1 = Year, X2 = Sqr Ftg, Y = Price
	vector<double> X1_i;
	vector<double> X2_i;
	vector<double> Y_i;

	for (auto& row : data) {
		X1_i.push_back(row[0]);
		X2_i.push_back(row[1]);
		Y_i.push_back(row[2]);
	}

	// Calculate Sums and Means
	double X1_SUM = 0;
	double X2_SUM = 0;
	double Y_SUM = 0;
	for (auto& v : X1_i) {
		X1_SUM += v;
	}
	for (auto& v : X2_i) {
		X2_SUM += v;
	}
	for (auto& v : Y_i) {
		Y_SUM += v;
	}
	double X1_MEAN = X1_SUM / X1_i.size();
	double X2_MEAN = X2_SUM / X2_i.size();
	double Y_MEAN = Y_SUM / Y_i.size();

	// Deviances
	for (auto& v : X1_i) {
		v -= X1_MEAN;
	}
	for (auto& v : X2_i) {
		v -= X2_MEAN;
	}
	for (auto& v : Y_i) {
		v -= Y_MEAN;
	}

	// Squares
	vector<double> X1_sqr;
	for (auto& v : X1_i) {
		X1_sqr.push_back(v * v);
	}
	vector<double> X2_sqr;
	for (auto& v : X2_i) {
		X2_sqr.push_back(v * v);
	}
	vector<double> Y_sqr;
	for (auto& v : Y_i) {
		Y_sqr.push_back(v * v);
	}

	// Products
	vector<double> X1Y;
	for (int i = 0; i < X1_i.size(); i++) {
		X1Y.push_back(X1_i[i] * Y_i[i]);
	}
	vector<double> X2Y;
	for (int i = 0; i < X2_i.size(); i++) {
		X2Y.push_back(X2_i[i] * Y_i[i]);
	}
	vector<double> X1X2;
	for (int i = 0; i < X1_i.size(); i++) {
		X1X2.push_back(X1_i[i] * X2_i[i]);
	}

	// Sums
	double X1_sqr_SUM = 0;
	double X2_sqr_SUM = 0;
	double Y_sqr_SUM = 0;
	double X1Y_SUM = 0;
	double X2Y_SUM = 0;
	double X1X2_SUM = 0;
	for (auto& v : X1_sqr) {
		X1_sqr_SUM += v;
	}
	for (auto& v : X2_sqr) {
		X2_sqr_SUM += v;
	}
	for (auto& v : Y_sqr) {
		Y_sqr_SUM += v;
	}
	for (auto& v : X1Y) {
		X1Y_SUM += v;
	}
	for (auto& v : X2Y) {
		X2Y_SUM += v;
	}
	for (auto& v : X1X2) {
		X1X2_SUM += v;
	}

	// Slopes/Intercepts
	double B_1 = (X2_sqr_SUM * X1Y_SUM - X2Y_SUM * X1X2_SUM) / (X1_sqr_SUM * X2_sqr_SUM - X1X2_SUM * X1X2_SUM);
	double B_2 = (X1_sqr_SUM * X2Y_SUM - X1X2_SUM * X1Y_SUM) / (X1_sqr_SUM * X2_sqr_SUM - X1X2_SUM * X1X2_SUM);
	double B_0 = Y_MEAN - B_1 * X1_MEAN - B_2 * X2_MEAN;

	//cout << endl << B_0 << " + " << B_1 << "x1 + " << B_2 << "x2" << endl << "=";

	return B_0 + B_1 * X1 + B_2 * X2;
}