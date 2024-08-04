#include "LinearRegression.h"
#include "stack"
#include <numeric>
#include <algorithm>
#include <vector>

double LR::getLinearRegression(vector<vector<int>>& data, int dp, double X) {
	// truncate to dp
	if (data.size() > dp){
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
	double X_MEAN = accumulate(X_i.begin(), X_i.end(), 0);
	double Y_MEAN = accumulate(Y_i.begin(), Y_i.end(), 0);
	X_MEAN /= X_i.size();
	Y_MEAN /= Y_i.size();

	// Calculate X_i - X_MEAN
	vector<double> X_deviance;
	for (auto& v : X_i) X_deviance.push_back(v - X_MEAN);

	// Calculate Y_i - Y_MEAN
	vector<double> Y_deviance;
	for (auto& v : Y_i) Y_deviance.push_back(v - Y_MEAN);

	// Calculate (X_i - X_MEAN)(Y_i - Y_MEAN)
	vector<double> Deviance_Product;
	std::transform(X_deviance.begin(), X_deviance.end(), Y_deviance.begin(), back_inserter(Deviance_Product), std::multiplies<double>());

	// Calculate (X_i - X_MEAN)^2
	vector<double> X_deviance_sqr;
	for (auto& v : X_deviance) X_deviance_sqr.push_back(v*v);

	// Calculate Slope
	double B_1 = accumulate(Deviance_Product.begin(), Deviance_Product.end(), 0) / accumulate(X_deviance_sqr.begin(), X_deviance_sqr.end(), 0);

	// Calculate Intercept
	double B_0 = Y_MEAN - (B_1 * X_MEAN);

	//cout << "Y = " << B_1 << "x + " << B_0 << endl;
	return B_0 + B_1 * X;
}

double LR::getMultLinearRegression(vector<vector<int>>& data, int dp, double X1, double X2) {
	if (data.size() > dp){
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
	double X1_SUM = accumulate(X1_i.begin(), X1_i.end(), 0);
	double X2_SUM = accumulate(X2_i.begin(), X2_i.end(), 0);
	double Y_SUM = accumulate(Y_i.begin(), Y_i.end(), 0);
	double X1_MEAN = X1_SUM / X1_i.size();
	double X2_MEAN = X2_SUM / X2_i.size();
	double Y_MEAN = Y_SUM / Y_i.size();

	// Deviances
	for (auto& v : X1_i) v -= X1_MEAN;
	for (auto& v : X2_i) v -= X2_MEAN;
	for (auto& v : Y_i) v -= Y_MEAN;
	
	// Squares
	vector<double> X1_sqr;
	for (auto& v : X1_i) X1_sqr.push_back(v * v);
	vector<double> X2_sqr;
	for (auto& v : X2_i) X2_sqr.push_back(v * v);
	vector<double> Y_sqr;
	for (auto& v : Y_i) Y_sqr.push_back(v * v);

	// Products
	vector<double> X1Y;
	std::transform(X1_i.begin(), X1_i.end(), Y_i.begin(), back_inserter(X1Y), std::multiplies<double>());
	vector<double> X2Y;
	std::transform(X2_i.begin(), X2_i.end(), Y_i.begin(), back_inserter(X2Y), std::multiplies<double>());
	vector<double> X1X2;
	std::transform(X1_i.begin(), X1_i.end(), X2_i.begin(), back_inserter(X1X2), std::multiplies<double>());

	// Sums
	double X1_sqr_SUM = accumulate(X1_sqr.begin(), X1_sqr.end(), 0);
	double X2_sqr_SUM = accumulate(X2_sqr.begin(), X2_sqr.end(), 0);
	double Y_sqr_SUM = accumulate(Y_sqr.begin(), Y_sqr.end(), 0);
	double X1Y_SUM = accumulate(X1Y.begin(), X1Y.end(), 0);
	double X2Y_SUM = accumulate(X2Y.begin(), X2Y.end(), 0);
	double X1X2_SUM = accumulate(X1X2.begin(), X1X2.end(), 0);

	// Slopes/Intercepts
	double B_1 = (X2_sqr_SUM * X1Y_SUM - X2Y_SUM * X1X2_SUM) / (X1_sqr_SUM * X2_sqr_SUM - X1X2_SUM * X1X2_SUM);
	double B_2 = (X1_sqr_SUM * X2Y_SUM - X1X2_SUM * X1Y_SUM) / (X1_sqr_SUM * X2_sqr_SUM - X1X2_SUM * X1X2_SUM);
	double B_0 = Y_MEAN - B_1 * X1_MEAN - B_2 * X2_MEAN;

	//cout << endl << B_0 << " + " << B_1 << "x1 + " << B_2 << "x2" << endl << "=";
	
	return B_0 + B_1 * X1 + B_2 * X2;
}