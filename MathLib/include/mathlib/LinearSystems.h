#pragma once
#include <functional>

namespace mathlib
{
	namespace LinearSystems
	{
		double JacobiMethod(int n, double** A, double* b, double* x, int maxIter, double tol);
	}
}