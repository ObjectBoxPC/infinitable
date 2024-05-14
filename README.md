# Infinitable

Infinitable is a simple library for introducing the notion of "infinity" and "negative infinity" to numeric types, such as integers, that do not have infinite values.

A representation of infinity is useful for graph algorithms such as Dijkstra's algorithm, as well as for representing a graph with an adjacency matrix.

## Usage

Simply copy `infinitable.h` and include it in your program:

```c++
#include <iostream>
#include <cassert>
#include "infinitable.h"

int main() {
	infinitable<int> finite = infinitable<int>(5);
	infinitable<int> infinity = infinitable<int>::inf();
	infinitable<int> negative_infinity = infinitable<int>::neginf();

	assert(finite < infinity);
	assert(finite > negative_infinity);
	assert(infinity == infinity - finite);
	assert(infinity == finite * infinity);

	return 0;
}
```

## Tests

Tests are in `InfinitableTest.cpp` and use CppUnit. In addition, the usage example in this README also serves as a fully executable test.

On a Unix-like system with the CppUnit library installed, simply run `make test` to run the tests.

## Arithmetic Operations

Arithmetic operations behave as described in the following tables.

### Addition

| LHS      | RHS      | Result                          |
|----------|----------|---------------------------------|
| Finite   | Finite   | Finite (add values)             |
| Finite   | `inf`    | `inf`                           |
| Finite   | `neginf` | `neginf`                        |
| `inf`    | Finite   | `inf`                           |
| `inf`    | `inf`    | `inf`                           |
| `inf`    | `neginf` | Undefined (`std::domain_error`) |
| `neginf` | Finite   | `neginf`                        |
| `neginf` | `inf`    | Undefined (`std::domain_error`) |
| `neginf` | `neginf` | `neginf`                        |

### Subtraction

| LHS      | RHS      | Result                          |
|----------|----------|---------------------------------|
| Finite   | Finite   | Finite (subtract values)        |
| Finite   | `inf`    | `neginf`                        |
| Finite   | `neginf` | `inf`                           |
| `inf`    | Finite   | `inf`                           |
| `inf`    | `inf`    | Undefined (`std::domain_error`) |
| `inf`    | `neginf` | `inf`                           |
| `neginf` | Finite   | `neginf`                        |
| `neginf` | `inf`    | `neginf`                        |
| `neginf` | `neginf` | Undefined (`std::domain_error`) |

### Multiplication

In the following table, "0" is the result of value-initializing the underlying type (`T()`), which generally represents zero for numeric types. The notation "~ 0" refers to a value that is neither less than nor greater than that value.

| LHS          | RHS          | Result                          |
|--------------|--------------|---------------------------------|
| Finite       | Finite       | Finite (multiply values)        |
| Finite (> 0) | `inf`        | `inf`                           |
| Finite (~ 0) | `inf`        | Undefined (`std::domain_error`) |
| Finite (< 0) | `inf`        | `neginf`                        |
| Finite (> 0) | `neginf`     | `neginf`                        |
| Finite (~ 0) | `neginf`     | Undefined (`std::domain_error`) |
| Finite (< 0) | `neginf`     | `inf`                           |
| `inf`        | Finite (> 0) | `inf`                           |
| `inf`        | Finite (~ 0) | Undefined (`std::domain_error`) |
| `inf`        | Finite (< 0) | `neginf`                        |
| `inf`        | `inf`        | `inf`                           |
| `inf`        | `neginf`     | `neginf`                        |
| `neginf`     | Finite (> 0) | `neginf`                        |
| `neginf`     | Finite (~ 0) | Undefined (`std::domain_error`) |
| `neginf`     | Finite (< 0) | `inf`                           |
| `neginf`     | `inf`        | `neginf`                        |
| `neginf`     | `neginf`     | `inf`                           |

### Division

In the following table, "0" is the result of value-initializing the underlying type (`T()`), which generally represents zero for numeric types. The notation "<> 0" refers to a value that is either less than or greater than that value, "~ 0" refers to a value that is neither.

| LHS          | RHS           | Result                          |
|--------------|---------------|---------------------------------|
| Finite (> 0) | Finite (~ 0)  | `inf`                           |
| Finite (~ 0) | Finite (~ 0)  | Undefined (`std::domain_error`) |
| Finite (< 0) | Finite (~ 0)  | `neginf`                        |
| Finite       | Finite (<> 0) | Finite (divide values)          |
| Finite       | `inf`         | 0                               |
| Finite       | `neginf`      | 0                               |
| `inf`        | Finite (> 0)  | `inf`                           |
| `inf`        | Finite (~ 0)  | `inf`                           |
| `inf`        | Finite (< 0)  | `neginf`                        |
| `inf`        | `inf`         | Undefined (`std::domain_error`) |
| `inf`        | `neginf`      | Undefined (`std::domain_error`) |
| `neginf`     | Finite (> 0)  | `neginf`                        |
| `neginf`     | Finite (~ 0)  | `neginf`                        |
| `neginf`     | Finite (< 0)  | `inf`                           |
| `neginf`     | `inf`         | Undefined (`std::domain_error`) |
| `neginf`     | `neginf`      | Undefined (`std::domain_error`) |

### Negation

| Operand  | Result                |
|----------|-----------------------|
| Finite   | Finite (negate value) |
| `inf`    | `neginf`              |
| `neginf` | `inf`                 |

## Note About Floating-Point Numbers

Infinitable does not account for existing infinite values in floating-point numeric types. The infinity provided by Infinitable compares greater than *all* existing values, and the negative infinity provided by Infinitable compares less than *all* existing values.

To illustrate, here are some values listed from least to greatest:

* Infinitable `neginf()`
* Floating-point negative infinity
* Floating-point zero
* Floating-point infinity
* Infinitable `inf()`

Similarly, any existing infinite values are treated as "finite" values for the purposes of arithmetic operations.

## License

Infinitable is available under the 2-clause BSD license. The header file includes the license text so simply preserving the text there will suffice for source distributions. For binary (non-source) distributions, a separate license text is provided in `LICENSE.txt` for convenience (although either text may be used).