#ifndef INFINITABLE_H
#define INFINITABLE_H

/*
 * This file is part of Infinitable <https://github.com/philipchungtech/infinitable>
 * Copyright (c) 2016-2017 Philip Chung. All rights reserved.
 * Available under the 2-clause BSD license (refer to `LICENSE.txt` for details)
 */

template <class T>
class infinitable {
public:
	infinitable(T value = T()) : m_value(value), m_tag(IT_FINITE) {}

	static infinitable inf() {
		return make_from_tag(IT_INF);
	}

	static infinitable neginf() {
		return make_from_tag(IT_NEGINF);
	}

	T& value() {
		return m_value;
	}

	const T& value() const {
		return m_value;
	}

	bool is_finite() const {
		return m_tag == IT_FINITE;
	}

	template <class FA, class FB>
	friend bool operator ==(const infinitable<FA>& a, const infinitable<FB>& b);
private:
	enum inf_tag { IT_FINITE, IT_INF, IT_NEGINF };

	T m_value;
	inf_tag m_tag;

	static infinitable make_from_tag(inf_tag tag) {
		infinitable result;

		result.m_value = T();
		result.m_tag = tag;
		return result;
	}
};

template <class A, class B>
bool operator ==(const infinitable<A>& a, const infinitable<B>& b) {
	typedef infinitable<A> ia;
	typedef infinitable<B> ib;

	if(a.m_tag == ia::IT_INF && b.m_tag == ib::IT_INF) {
		return true;
	}
	if(a.m_tag == ia::IT_NEGINF && b.m_tag == ib::IT_NEGINF) {
		return true;
	}
	if(a.m_tag == ia::IT_FINITE && b.m_tag != ib::IT_FINITE) {
		return false;
	}
	if(a.m_tag != ia::IT_FINITE && b.m_tag == ib::IT_FINITE) {
		return false;
	}
	if(a.m_tag == ia::IT_INF && b.m_tag == ib::IT_NEGINF) {
		return false;
	}
	if(a.m_tag == ia::IT_NEGINF && b.m_tag == ib::IT_INF) {
		return false;
	}
	return a.value() == b.value();
}

template <class A, class B>
bool operator !=(const infinitable<A>& a, const infinitable<B>& b) {
	return !(a == b);
}

template <class A, class B>
bool operator <(infinitable<A> a, infinitable<B> b) {
	infinitable<A> a_inf = infinitable<A>::inf();
	infinitable<B> b_inf = infinitable<B>::inf();
	infinitable<A> a_neginf = infinitable<A>::neginf();
	infinitable<B> b_neginf = infinitable<B>::neginf();

	if(a == a_inf && b == b_inf) {
		return false;
	} else if(a == a_neginf && b == b_neginf) {
		return false;
	} else if(a == a_inf) {
		return false;
	} else if(b == b_inf){
		return true;
	} else if(a == a_neginf) {
		return true;
	} else if(b == b_neginf) {
		return false;
	} else {
		return a.value() < b.value();
	}
}

template <class A, class B>
bool operator >(infinitable<A> a, infinitable<B> b) {
	return !((a < b) || (a == b));
}

template <class A, class B>
bool operator <=(infinitable<A> a, infinitable<B> b) {
	return (a < b) || (a == b);
}

template <class A, class B>
bool operator >=(infinitable<A> a, infinitable<B> b) {
	return !(a < b);
}
#endif