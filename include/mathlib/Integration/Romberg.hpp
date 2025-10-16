#pragma once
#include <functional>

namespace mathlib {
namespace Integration {
		double RombergIntegration(double a, double b, int maxIter, double tol, std::function<double(double)> f);
}
}
