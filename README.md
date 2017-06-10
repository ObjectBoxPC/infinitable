# Infinitable

Infinitable is a simple library for introducing the notion of "infinity" and "negative infinity" to numeric types, such as integers, that do not have infinite values.

A representation of infinity is useful for graph algorithms such as Dijkstra's algorithm, as well as for representing a graph with an adjacency matrix.

## Usage

Simply copy `infinitable.h` and include it in your program:

```c++
#include <iostream>
#include "infinitable.h"

int main() {
	infinitable<int> finite = infinitable<int>(5);
	infinitable<int> infinity = infinitable<int>::inf();
	infinitable<int> negative_infinity = infinitable<int>::neginf();
	if(finite < infinity && finite > negative_infinity) {
		std::cout << "It works!" << std::endl;
	}

	return 0;
}
```

## Tests

Tests are in `InfinitableTest.cpp` and use CppUnit.

On a Unix-like system with the CppUnit library installed, simply run `make test` to run the tests.

## Note About Floating-Point Numbers

Infinitable does not account for existing infinite values in floating-point numeric types. The infinity provided by Infinitable compares greater than *all* existing values, and the negative infinity provided by Infinitable compares less than *all* existing values.

To illustrate, here are some values listed from least to greatest:

* Infinitable `neginf()`
* Floating-point negative infinity
* Floating-point zero
* Floating-point infinity
* Infinitable `inf()`

## License

Infinitable is available under the 2-clause BSD license. Refer to `LICENSE.txt` for details.