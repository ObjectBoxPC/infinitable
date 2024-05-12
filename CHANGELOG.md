# Changelog

## 3.0.0

Breaking changes:

* The negation operator is now `const`. This should only make a difference if the underlying "finite" type has const and non-const negation operators that behave differently:
	```
	class weird_negation {
	public:
		// ...
		weird_negation operator -() { /* ...non-const overload... */ }
		weird_negation operator -() const { /* ...const overload... */ }
	};

	// ...

	infinitable<weird_negation> x = /* ...finite value... */;

	// Calls non-const overload before 3.x, calls const overload in 3.x
	infinitable<weird_negation> neg_x = -x;
	```

Other changes:

* Arithmetic operators are now supported. (Refer to the README for how infinite values are handled.)

## 2.0.1

* A bug in the less-than-or-equal operator (`<=`) introduced in 2.0.0 is fixed.
* Makefile is fixed so that tests are recompiled when the main header file is changed.
* License text is added to the header file to facilitate compliance.

## 2.0.0

Breaking changes:

* Equality and comparison operators now use the corresponding operators of the underlying "finite" type. This ensures that comparisons between infinitable values are consistent with the underlying "finite" comparisons. Previously, all of the operators were based on the less-than (`<`) and equal (`==`) operators (for example, unequal [`!=`] was implemented as `!(x == y)` and greater-than [`>`] was implemented as `!(x < y || x == y)`), which could lead to inconsistencies with some orderings. For example:
	```
	// Assuming NAN behaves as specified by IEEE 754
	NAN < NAN; // false
	NAN == NAN; // false
	NAN > NAN; // false
	infinitable(NAN) > infinitable(NAN) // true in 1.x, false in 2.x
	```
* Operators are now defined as member functions instead of free functions. This should only make a difference if you are using explicit syntax to call them (for example, `operator <(x, y)` needs to be changed to `x.operator <(y)`).

Other changes:

* Implementations are simplified.
* Makefile is improved.

## 1.1.0

* Negation operator is now supported.

## 1.0.0

* Initial version supports equality and comparison operators.