#include "LinearRegression.h"
#include "stack"
#include <numeric>
#include <algorithm>
#include <vector>

void LR::getLinearRegression(vector<vector<int>>& data) {
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
	transform(X_deviance.begin(), X_deviance.end(), Y_deviance.begin(), back_inserter(Deviance_Product), std::multiplies<double>());

	// Calculate (X_i - X_MEAN)^2
	vector<double> X_deviance_sqr;
	for (auto& v : X_deviance) X_deviance_sqr.push_back(v*v);

	// Calculate Slope
	double B_1 = accumulate(Deviance_Product.begin(), Deviance_Product.end(), 0) / accumulate(X_deviance_sqr.begin(), X_deviance_sqr.end(), 0);

	// Calculate Intercept
	double B_0 = Y_MEAN - (B_1 * X_MEAN);

	cout << "Y = " << B_1 << "x + " << B_0 << endl;
}