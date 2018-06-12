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
		return infinitable(IT_INF);
	}

	static infinitable neginf() {
		return infinitable(IT_NEGINF);
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

	infinitable(inf_tag tag) : m_value(T()), m_tag(tag) {}
};

template <class A, class B>
bool operator ==(const infinitable<A>& a, const infinitable<B>& b) {
	if(a.m_tag == b.m_tag && a.m_tag == a.IT_FINITE) {
		return a.m_value == b.m_value;
	} else {
		return a.m_tag == b.m_tag;
	}
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

template <class T>
infinitable<T> operator -(infinitable<T> i) {
	if(i == infinitable<T>::inf()) {
		return infinitable<T>::neginf();
	} else if(i == infinitable<T>::neginf()) {
		return infinitable<T>::inf();
	} else {
		return infinitable<T>(-i.value());
	}
}
#endif