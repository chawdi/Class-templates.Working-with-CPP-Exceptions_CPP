#ifndef RATIONAL_H
#define RATIONAL_H

#include <ostream>
#include <experimental/numeric> // std::gcd
#include <stdexcept>            // std::invalid_argument

namespace lab {
// three constructors: default constructor, constructor with parameters, copy constructor.
// For classes where a constructor allocates memory, a destructor must be provided.
// Classes used for storage must provide accessor methods.
//
// Rational numbers are a set of quotients of the form P / Q, where P and Q are integers
// numbers, and Q != 0. The number P is called the numerator, and Q is called the denominator.
// This representation of numbers is not unique. For example,
// 2 / 5 == 4 / 10 == 12 / 30.
// Usually, the result of calculations with rational numbers leads to the so-called
// reduced form, when the numerator and denominator do not have a common
// denominator. To convert a rational number to
// reduced form, the numerator and denominator must be divided by their
// greatest common denominator(GCD, greatest common denominator).
//
// The developed class (Rational) should provide the following operations:
// default constructor. check
// constructor with parameters. check
// addition, check
// subtraction, check
// multiplication, check
// division, check
// comparisons for equality and inequality. check
// relationship. check
// output a rational number to the display screen. check
// Note. After performing arithmetic operations, the result should be
// converted to reduced form.

template <typename IntT = int>
class rational_t {
private:
	static_assert(std::is_integral<IntT>::value, "Integral required.");

	// N = num / denom; denom != 0.
	IntT num_, denom_;

	void check() noexcept
	{
		if (denom_ < 0) {
			denom_ = -denom_;
			num_ = -num_;
		}
		int const gcd_ = gcd(num_, denom_);
		denom_ /= gcd_;
		num_ /= gcd_;
	}
public:
	rational_t() noexcept : num_(0), denom_(1) {}
	rational_t(IntT num, IntT denom) noexcept(false) : num_(num), denom_(denom)
	{
		if (!denom)
			throw std::invalid_argument("Denominator can't be 0.");
		check();
	}
	// assign operator
	rational_t& operator=(rational_t const& number) noexcept
	{
		if (this == &number)
			return *this;
		num_ = number.num_;
		denom_ = number.denom_;
		return *this;
	}
	operator double() const noexcept
	{
		return static_cast<double>(num_) / denom_;
	}

	friend inline std::ostream& operator<<(std::ostream& os,
					       rational_t const& number)
	{
		os << +number.num_ << " / " << +number.denom_;
		return os;
	}

	//unary +
	friend rational_t const& operator+(rational_t const& number) noexcept
	{
		return number;
	}

	//unary -
	friend rational_t const operator-(rational_t const& number) noexcept
	{
		return rational_t(-number.num_, number.denom_);
	}

	//prefix increment
	friend rational_t const& operator++(rational_t& number) noexcept
	{
		number = number + rational_t(1, 1);
		return number;
	}

	//postfix increment
	friend rational_t const operator++(rational_t& number, int) noexcept
	{
		rational_t old(number);

		number = number + rational_t(1, 1);
		return old;
	}

	//prefix decrement
	friend rational_t const& operator--(rational_t& number) noexcept
	{
		number = number - rational_t(1, 1);
		return number;
	}

	//postfix decrement
	friend rational_t const operator--(rational_t& number, int) noexcept
	{
		rational_t old(number);

		number = number - rational_t(1, 1);
		return old;
	}

	// +=
	friend rational_t& operator+=(rational_t& lhs,
				    rational_t const& rhs) noexcept
	{
		lhs = lhs + rhs;
		return lhs;
	}

	// ==
	friend bool operator==(rational_t const& lhs,
			       rational_t const& rhs) noexcept
	{
		return (lhs.denom_ == rhs.denom_) && (lhs.num_ == rhs.num_);
	}

	// !=
	friend bool operator!=(rational_t const& lhs,
			       rational_t const& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	// binary plus
	friend rational_t const operator+(rational_t const& lhs,
					rational_t const& rhs) noexcept
	{
		int const temp_denom = lhs.denom_ * rhs.denom_
				       / gcd(lhs.denom_, rhs.denom_);
		int const temp_num = temp_denom / lhs.denom_ * lhs.num_
				     + temp_denom / rhs.denom_ * rhs.num_;

		return rational_t(temp_num, temp_denom);
	}

	// binary -
	friend rational_t const operator-(rational_t const& lhs,
					rational_t const& rhs) noexcept
	{
		return operator+(lhs, -rhs);
	}

	// binary -=
	friend rational_t& operator-=(rational_t& lhs,
				    rational_t const& rhs) noexcept
	{
		lhs = lhs - rhs;
		return lhs;
	}

	// binary multiply
	friend rational_t const operator*(rational_t const& lhs,
					rational_t const& rhs) noexcept
	{
		return rational_t(lhs.num_ * rhs.num_, lhs.denom_ * rhs.denom_);
	}

	// binary *=
	friend rational_t const operator*=(rational_t& lhs,
					rational_t const& rhs) noexcept
	{
		lhs = lhs * rhs;
		return lhs;
	}

	// binary divide
	friend rational_t const operator/(rational_t const& lhs,
					rational_t const& rhs) noexcept
	{
		return rational_t(lhs.num_ * rhs.denom_, lhs.denom_ * rhs.num_);
	}

	// binary /=
	friend rational_t const operator/=(rational_t& lhs,
					rational_t const& rhs) noexcept
	{
		lhs = lhs / rhs;
		return lhs;
	}

	friend bool operator<(rational_t const& lhs,
			      rational_t const& rhs) noexcept
	{
		return rational_t(lhs - rhs).num_ < 0;
	}

	friend bool operator>(rational_t const& lhs,
			      rational_t const& rhs) noexcept
	{
		return rhs < lhs;
	}

	friend bool operator<=(rational_t const& lhs,
			       rational_t const& rhs) noexcept
	{
		return !(lhs > rhs);
	}

	friend bool operator>=(rational_t const& lhs,
			       rational_t const& rhs) noexcept
	{
		return !(lhs < rhs);
	}


	// GCD, greatest common denominator
	static inline int gcd(IntT a, IntT b) noexcept
	{
		return std::experimental::gcd(a, b);
		a = std::abs(a);
		b = std::abs(b);
		return b ? gcd(b, a % b) : a;
	}
};

typedef rational_t<int> rational;

} // namespace lab

#endif // RATIONAL_H
