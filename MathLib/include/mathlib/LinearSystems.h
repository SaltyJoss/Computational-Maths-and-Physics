#pragma once
#include <functional>

namespace NumericalMethods
{
	namespace LinearSystems
	{
		double JacobiMethod(int n, double** A, double* b, double* x, int maxIter, double tol);
	}
}