/*
 * This file is part of Infinitable <https://github.com/ObjectBoxPC/infinitable>
 * Copyright (c) 2017-2020 Philip Chung. All rights reserved.
 * Available under the 2-clause BSD license (refer to `LICENSE.txt` for details)
 */

#include "../infinitable.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cmath>

class InfinitableTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(InfinitableTest);
		CPPUNIT_TEST(testCanExtractFiniteValue);
		CPPUNIT_TEST(testCanCheckFiniteness);
		CPPUNIT_TEST(testFiniteValuesCompareNormally);
		CPPUNIT_TEST(testInfinitiesEquality);
		CPPUNIT_TEST(testInfinityGreaterThanAll);
		CPPUNIT_TEST(testNegativeInfinityLessThanAll);
		CPPUNIT_TEST(testNanIsIncomparable);
		CPPUNIT_TEST(testCanNegate);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp() {
		neginf = infinitable<int>::neginf();
		inf = infinitable<int>::inf();
		zero = 0;
		one = 1;
		nan = NAN;
	}

	void testCanExtractFiniteValue() {
		CPPUNIT_ASSERT(zero.value() == 0);
		CPPUNIT_ASSERT(one.value() == 1);
	}

	void testCanCheckFiniteness() {
		CPPUNIT_ASSERT(zero.is_finite());
		CPPUNIT_ASSERT(one.is_finite());
		CPPUNIT_ASSERT(!inf.is_finite());
		CPPUNIT_ASSERT(!neginf.is_finite());
	}

	void testFiniteValuesCompareNormally() {
		CPPUNIT_ASSERT(zero < one);
		CPPUNIT_ASSERT(zero <= one);
		CPPUNIT_ASSERT(one > zero);
		CPPUNIT_ASSERT(one >= zero);
		CPPUNIT_ASSERT(one == one);
		CPPUNIT_ASSERT(one <= one);
		CPPUNIT_ASSERT(one >= one);

		CPPUNIT_ASSERT(!(zero > one));
		CPPUNIT_ASSERT(!(zero >= one));
		CPPUNIT_ASSERT(!(one < zero));
		CPPUNIT_ASSERT(!(one <= zero));
	}

	void testInfinitiesEquality() {
		CPPUNIT_ASSERT(inf == inf);
		CPPUNIT_ASSERT(neginf == neginf);
		CPPUNIT_ASSERT(inf <= inf);
		CPPUNIT_ASSERT(neginf <= neginf);
		CPPUNIT_ASSERT(inf >= inf);
		CPPUNIT_ASSERT(neginf >= neginf);
		CPPUNIT_ASSERT(!(inf != inf));
		CPPUNIT_ASSERT(!(neginf != neginf));

		CPPUNIT_ASSERT(!(inf == neginf));
		CPPUNIT_ASSERT(inf != neginf);
		CPPUNIT_ASSERT(!(neginf == inf));
		CPPUNIT_ASSERT(neginf != inf);

		CPPUNIT_ASSERT(!(inf == zero));
		CPPUNIT_ASSERT(inf != zero);
		CPPUNIT_ASSERT(!(zero == inf));
		CPPUNIT_ASSERT(zero != inf);
	}

	void testInfinityGreaterThanAll() {
		CPPUNIT_ASSERT(inf > one);
		CPPUNIT_ASSERT(inf >= one);
		CPPUNIT_ASSERT(inf > neginf);
		CPPUNIT_ASSERT(inf >= neginf);
		CPPUNIT_ASSERT(one < inf);
		CPPUNIT_ASSERT(one <= inf);
		CPPUNIT_ASSERT(neginf < inf);
		CPPUNIT_ASSERT(neginf <= inf);

		CPPUNIT_ASSERT(!(inf < one));
		CPPUNIT_ASSERT(!(inf <= one));
		CPPUNIT_ASSERT(!(inf < neginf));
		CPPUNIT_ASSERT(!(inf <= neginf));
		CPPUNIT_ASSERT(!(one > inf));
		CPPUNIT_ASSERT(!(one >= inf));
		CPPUNIT_ASSERT(!(neginf > inf));
		CPPUNIT_ASSERT(!(neginf >= inf));
	}
	
	void testNegativeInfinityLessThanAll() {
		CPPUNIT_ASSERT(neginf < zero);
		CPPUNIT_ASSERT(neginf <= zero);
		CPPUNIT_ASSERT(neginf < inf);
		CPPUNIT_ASSERT(neginf <= inf);
		CPPUNIT_ASSERT(zero > neginf);
		CPPUNIT_ASSERT(zero >= neginf);
		CPPUNIT_ASSERT(inf > neginf);
		CPPUNIT_ASSERT(inf >= neginf);

		CPPUNIT_ASSERT(!(neginf > zero));
		CPPUNIT_ASSERT(!(neginf >= zero));
		CPPUNIT_ASSERT(!(neginf > inf));
		CPPUNIT_ASSERT(!(neginf >= inf));
		CPPUNIT_ASSERT(!(zero < neginf));
		CPPUNIT_ASSERT(!(zero <= neginf));
		CPPUNIT_ASSERT(!(inf < neginf));
		CPPUNIT_ASSERT(!(inf <= neginf));
	}

	void testNanIsIncomparable() {
		CPPUNIT_ASSERT(!(nan == nan));
		CPPUNIT_ASSERT(!(nan < nan));
		CPPUNIT_ASSERT(!(nan <= nan));
		CPPUNIT_ASSERT(!(nan > nan));
		CPPUNIT_ASSERT(!(nan >= nan));
		CPPUNIT_ASSERT(nan != nan);
	}

	void testCanNegate() {
		CPPUNIT_ASSERT(-zero == zero);
		CPPUNIT_ASSERT(-one == infinitable<int>(-1));
		CPPUNIT_ASSERT(-inf == neginf);
		CPPUNIT_ASSERT(-neginf == inf);
	}
private:
	infinitable<int> neginf, inf, zero, one;
	infinitable<float> nan;
};

CPPUNIT_TEST_SUITE_REGISTRATION(InfinitableTest);