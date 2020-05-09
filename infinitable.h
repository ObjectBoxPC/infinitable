#ifndef INFINITABLE_H
#define INFINITABLE_H

/*
 * This file is part of Infinitable <https://github.com/ObjectBoxPC/infinitable>
 * Copyright (c) 2017-2020 Philip Chung. All rights reserved.
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

	template<class U>
	bool operator ==(const infinitable<U>& other) const {
		comparison comp = compare(other);
		return comp == COMP_EQUAL
			|| (comp == COMP_FINITE && m_value == other.m_value);
	}

	template<class U>
	bool operator !=(const infinitable<U>& other) const {
		comparison comp = compare(other);
		return comp != COMP_EQUAL
			|| (comp == COMP_FINITE && m_value != other.m_value);
	}

	template<class U>
	bool operator <(const infinitable<U>& other) const {
		comparison comp = compare(other);
		return comp == COMP_LESS
			|| (comp == COMP_FINITE && m_value < other.m_value);
	}

	template<class U>
	bool operator >(const infinitable<U>& other) const {
		comparison comp = compare(other);
		return comp == COMP_GREATER
			|| (comp == COMP_FINITE && m_value > other.m_value);
	}

	template<class U>
	bool operator <=(const infinitable<U>& other) const {
		comparison comp = compare(other);
		return (comp == COMP_LESS || comp == COMP_GREATER)
			|| (comp == COMP_FINITE && m_value <= other.m_value);
	}

	template<class U>
	bool operator >=(const infinitable<U>& other) const {
		comparison comp = compare(other);
		return (comp == COMP_GREATER || comp == COMP_EQUAL)
			|| (comp == COMP_FINITE && m_value >= other.m_value);
	}

	infinitable operator -() {
		switch(m_tag) {
		case IT_INF:
			return infinitable(IT_NEGINF);
		case IT_NEGINF:
			return infinitable(IT_INF);
		case IT_FINITE:
		default: //Not needed, only here to silence compiler warnings
			return infinitable(-m_value);
		}
	}
private:
	enum inf_tag { IT_FINITE, IT_INF, IT_NEGINF };

	T m_value;
	inf_tag m_tag;

	infinitable(inf_tag tag) : m_value(T()), m_tag(tag) {}

	enum comparison { COMP_LESS, COMP_EQUAL, COMP_GREATER, COMP_FINITE };

	template<class U>
	comparison compare(const infinitable<U>& other) const {
		if(m_tag == IT_INF && other.m_tag == IT_INF) {
			return COMP_EQUAL;
		} else if(m_tag == IT_NEGINF && other.m_tag == IT_NEGINF) {
			return COMP_EQUAL;
		} else if(m_tag == IT_INF) {
			return COMP_GREATER;
		} else if(other.m_tag == IT_INF){
			return COMP_LESS;
		} else if(m_tag == IT_NEGINF) {
			return COMP_LESS;
		} else if(other.m_tag == IT_NEGINF) {
			return COMP_GREATER;
		} else {
			return COMP_FINITE;
		}
	}
};
#endif