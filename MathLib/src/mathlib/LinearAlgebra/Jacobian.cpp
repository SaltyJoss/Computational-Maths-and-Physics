#pragma once
#include <functional>

namespace mathlib {
	namespace LinearAlgebra {
		double JacobiMethod(int n, double** A, double* b, double* x, int maxIter, double tol);
}
}