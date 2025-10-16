#pragma once
#include <functional>

namespace NumericalMethods
{
	namespace EigenvalueComputations
	{
		double PowerMethod(int n, double** A, double* eigenvector, double* eigenvalue, int maxIter, double tol);
		double QRAlgorithm(int n, double** A, double* eigenvalues, double** eigenvectors, int maxIter, double tol);
	}
}