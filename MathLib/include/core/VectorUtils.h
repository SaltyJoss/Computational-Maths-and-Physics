// PxM/MathLib VectorUtils.h
#pragma once

#include "core/ScalarScaling.h"
#include "core/DualNumbers.h"
#include <Eigen/Dense>

namespace mathlib {
	// WARNING: Currently does not work with dual numbers when in safeNormalised(), will fix later.
	template<typename Derived>
	inline auto safeNorm(const Eigen::MatrixBase<Derived>& v) { return mathlib::sqrt((v.array() * v.array()).sum()); }

	template<typename Derived>
	inline typename Derived::PlainObject safeNormalised(const Eigen::MatrixBase<Derived>& v) {
		using Scalar = typename Derived::Scalar;
		using Plain = typename Derived::PlainObject;
		Scalar n = safeNorm(v);
		if (n > Scalar(0)) { return (v / n).eval(); }
		return Plain::Zero(v.rows(), v.cols());
	}

	template<class Derived>
	inline Eigen::Quaternion<typename Derived::Scalar> safeNormalised(const Eigen::QuaternionBase<Derived>& q) {
		using Scalar = typename Derived::Scalar;
		using Quat = Eigen::Quaternion<Scalar>;
		Scalar n = safeNorm(q.coeffs());
		if (n > Scalar(0)) {
			auto c = (q.coeffs() / n).eval();
			return Eigen::Quaternion<Scalar>(c.w(), c.x(), c.y(), c.z());
		}
		return Quat(Scalar(1), Scalar(0), Scalar(0), Scalar(0));
	}
}