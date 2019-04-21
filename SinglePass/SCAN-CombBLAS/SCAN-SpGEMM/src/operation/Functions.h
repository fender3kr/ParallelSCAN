/*
 * Functions.h
 *
 *  Created on: Oct 16, 2017
 *  Author: Seokyong Hong
 */

#ifndef SRC_OPERATION_FUNCTIONS_H_
#define SRC_OPERATION_FUNCTIONS_H_

template <typename T>
void symmetricize(T &matrix) {
	T temp = matrix;
	temp.Transpose();
	matrix += temp;
}

template <typename T, typename R>
struct one : public unary_function<T, R> {
	double operator()(const T e) const {
		return (R)1;
	}
};

template <typename T>
struct get_first_4 : public std::binary_function<T, T, T> {
	T operator()(const T &x, const T &y, const bool &a, const bool &b) const {
		return x + (T)2;
	}
};

template <typename T>
struct add_multiple_sqaure_root : public std::binary_function<T, T, T> {
	T operator()(const T &x, const T &y) const {
		return sqrt(x * (y + 1));
	}
};

template <typename T1, typename T2, typename R>
struct divide_by_second : public std::binary_function<T1, T2, R> {
	R operator()(const T1 &x, const T2 &y, const bool &a, const bool &b) const {
		return (R)((double)x / (double)y);
	}
};

template <typename T>
struct select_first : public std::binary_function<T, T, T> {
	T operator()(const T &x, const T &y) const {
		return x;
	}
};

template <typename T>
struct select_second : public std::binary_function<T, T, T> {
	T operator()(const T &x, const T &y) const {
		return y;
	}
};

template <typename T, typename R>
struct sum : public std::binary_function<T, T, R> {
	R operator()(const T &x, const T &y) const {
		return (x > 0UL) ? (R)(y + (T)1) : (R)y;
	}
};

template <typename T, typename R>
struct count_non_zeros : public std::binary_function<T, T, R> {
	R operator()(const T &x, const T &y) const {
		return (x > (T)0) ? y + 1 : y;
	}
};

template <typename T, typename R>
struct set_one_2 : public std::binary_function<T, T, R> {
	R operator()(const T &x, const T &y) const {
		return (R)1;
	}
};

template <typename T1, typename T2, typename R>
struct set_one_4 : public std::binary_function<T1, T2, R> {
	R operator()(const T1 &x, const T2 &y, const bool &a, const bool &b) const {
		return (R)1;
	}
};

template <typename T1, typename T2>
struct set_minus_one : public std::binary_function<T1, T2, T1> {
	T1 operator()(const T1 &x, const T2 &y) const {
		return (T1)-1;
	}
};

template <typename T1, typename T2>
struct set_solitary : public std::binary_function<T1, T2, T1> {
	double operator()(const T1 &x, const T2 &y) const {
		return (y > (T2)0) ? x : (T1)0;
	}
};

template <typename T1, typename T2>
struct set_label : public std::binary_function<T1, T2, T1> {
	T1 operator()(const T1 &x, const T2 &y) const {
		return (x > (T1)0) ? (T1)y : (T1)0;
	}
};

template <typename T>
struct select_max : public std::binary_function<T, T, T> {
	T operator()(const T &x, const T &y) const {
		return max(x, y);
	}
};

template <typename T>
struct check_cluster : public std::binary_function<T, T, T> {
  	T operator()(const T &x, const T &y) const {
		if(y == (T)-2)
			return x;
		else if(y == (T)-1)
			return y;
		else {
			if(x == (T)-2)
				return y;
			else {
				if(y != x)
					return (T)-1;
				else
					return x;
			}
		}
	}
};

template <typename T1, typename T2>
struct mark_as_hub : public std::binary_function<T1, T2, T1> {
	T1 operator()(const T1 &x, const T2 &y, const bool &a, const bool &b) const {
		return (T1)-3;
	}
};

template <typename T>
struct always_true : public std::binary_function<T, T, bool> {
  	bool operator()(const T &x, const T &y, const bool &a, const bool &b) const {
		return true;
	}
};

template <typename T>
struct is_second_not_equal_to_one : public std::binary_function<T, T, bool> {
  	bool operator()(const T &x, const T &y) const {
		return (y != (T)1);
	}
};

template <typename T>
struct is_second_greater_than_zero : public std::binary_function<T, T, bool> {
	bool operator()(const T &x, const T &y) const {
		return y > (T)0;
	}
};

template <typename T1, typename T2>
struct is_second_less_than_zero : public std::binary_function<T1, T2, bool> {
	bool operator()(const T1 &x, const T2 &y, const bool &a, const bool &b) const {
		return y < (T2)0;
	}
};

template <typename T>
struct is_solitary : public std::binary_function<T, T, bool> {
  	bool operator()(const T &x, const T &y) const {
		return (x == (T)1 and y != (T)1);
	}
};

template <typename T1, typename T2>
struct is_hub : public std::binary_function<T1, T2, bool> {
  	bool operator()(const T1 &x, const T2 &y, const bool &a, const bool &b) const {
		return (y == (T2)-1);
	}
};

template <typename T>
struct is_zero : public unary_function<T, bool> {
	bool operator()(const T &e) const {
		return (e == (T)0);
	}
};

template <typename T>
struct is_less_than_zero : public unary_function<T, bool> {
	bool operator()(const T &e) const {
		return (e < (T)0);
	}
};

template <typename T>
struct is_lt_or_eq_zero : public unary_function<T, bool> {
	bool operator()(const T &e) const {
		return (e <= (T)0);
	}
};

template <typename T>
struct is_greater_than_zero : public unary_function<T, bool> {
	bool operator()(const T &e) const {
		return e > (T)0;
	}
};

template <typename T>
class less_than_epsilon : public unary_function<T, bool> {
private:
	const T &epsilon;
public:
	less_than_epsilon(const T &epsilon) : epsilon(epsilon) {}
	bool operator()(const T &e) const {
		return (e < epsilon);
	}
};

template <typename T>
class set_core : public unary_function<T, T> {
private:
	const uint32_t &mu;
public:
	set_core(const uint32_t &mu) : mu(mu) {}
	T operator()(const T &e) const {
		return (e >= (T)mu) ? (T)1 : (T)0;
	}
};

struct select_max_sr {
	typedef uint64_t T_promote;
	static T_promote id() { return -1; }
	static bool returnedSAID() { return false; }

	static T_promote add(const T_promote &e1, const T_promote &e2) {
		return max(e1, e2);
	}
	static T_promote multiply(const bool &e1, const T_promote &e2) {
		return e2;
	}
	static void axpy(bool a, const T_promote &e1, T_promote &e2) {
		e2 = max(e1, e2);
	}
};

#endif /* SRC_OPERATION_FUNCTIONS_H_ */
