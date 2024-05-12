#ifndef INFINITABLE_H
#define INFINITABLE_H

/*
 * This file is part of Infinitable <https://github.com/ObjectBoxPC/infinitable>
 *
 * Copyright (c) 2017-2024 Philip Chung. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdexcept>

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
		return (comp == COMP_LESS || comp == COMP_EQUAL)
			|| (comp == COMP_FINITE && m_value <= other.m_value);
	}

	template<class U>
	bool operator >=(const infinitable<U>& other) const {
		comparison comp = compare(other);
		return (comp == COMP_GREATER || comp == COMP_EQUAL)
			|| (comp == COMP_FINITE && m_value >= other.m_value);
	}

	infinitable operator -() const {
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

	infinitable operator +(const infinitable& other) const {
		if((m_tag == IT_INF && other.m_tag == IT_NEGINF)
			|| (m_tag == IT_NEGINF && other.m_tag == IT_INF)) {
			throw std::domain_error(
				"Cannot add infinity and negative infinity"
			);
		} else if(m_tag == IT_FINITE && other.m_tag == IT_FINITE) {
			return infinitable(m_value + other.m_value);
		} else if(m_tag == IT_INF || other.m_tag == IT_INF) {
			return infinitable(IT_INF);
		} else {
			return infinitable(IT_NEGINF);
		}
	}

	infinitable operator -(const infinitable& other) const {
		if((m_tag == IT_INF && other.m_tag == IT_INF)
			|| (m_tag == IT_NEGINF && other.m_tag == IT_NEGINF)) {
			throw std::domain_error(
				"Cannot subtract infinite value from itself"
			);
		} else if(m_tag == IT_FINITE && other.m_tag == IT_FINITE) {
			return infinitable(m_value - other.m_value);
		} else if(m_tag == IT_INF || other.m_tag == IT_NEGINF) {
			return infinitable(IT_INF);
		} else {
			return infinitable(IT_NEGINF);
		}
	}

	infinitable operator *(const infinitable& other) const {
		if((m_tag == IT_INF && other.m_tag == IT_INF)
			|| (m_tag == IT_NEGINF && other.m_tag == IT_NEGINF)) {
			return infinitable(IT_INF);
		} else if((m_tag == IT_INF && other.m_tag == IT_NEGINF)
			|| (m_tag == IT_NEGINF && other.m_tag == IT_INF)) {
			return infinitable(IT_NEGINF);
		} else if(m_tag == IT_INF) {
			if(other.m_value > T()) {
				return infinitable(IT_INF);
			} else if(other.m_value < T()) {
				return infinitable(IT_NEGINF);
			} else {
				throw std::domain_error(
					"Cannot multiply infinite value and zero or unordered value"
				);
			}
		} else if(other.m_tag == IT_INF) {
			if(m_value > T()) {
				return infinitable(IT_INF);
			} else if(m_value < T()) {
				return infinitable(IT_NEGINF);
			} else {
				throw std::domain_error(
					"Cannot multiply infinite value and zero or unordered value"
				);
			}
		} else if(m_tag == IT_NEGINF) {
			if(other.m_value > T()) {
				return infinitable(IT_NEGINF);
			} else if(other.m_value < T()) {
				return infinitable(IT_INF);
			} else {
				throw std::domain_error(
					"Cannot multiply infinite value and zero or unordered value"
				);
			}
		} else if(other.m_tag == IT_NEGINF) {
			if(m_value > T()) {
				return infinitable(IT_NEGINF);
			} else if(m_value < T()) {
				return infinitable(IT_INF);
			} else {
				throw std::domain_error(
					"Cannot multiply infinite value and zero or unordered value"
				);
			}
		} else {
			return infinitable(m_value * other.m_value);
		}
	}

	infinitable operator /(const infinitable& other) const {
		if(m_tag != IT_FINITE && other.m_tag != IT_FINITE) {
			throw std::domain_error("Cannot divide two infinite values");
		} else if(m_tag == IT_INF) {
			return other.m_value < T()
				? infinitable(IT_NEGINF)
				: infinitable(IT_INF);
		} else if(m_tag == IT_NEGINF) {
			return other.m_value < T()
				? infinitable(IT_INF)
				: infinitable(IT_NEGINF);
		} else if(m_tag == IT_FINITE && other.m_tag != IT_FINITE) {
			return infinitable(T());
		} else {
			if(other.m_value < T() || other.m_value > T()) {
				return infinitable(m_value / other.m_value);
			} else {
				if(m_value > T()) {
					return infinitable(IT_INF);
				} else if(m_value < T()) {
					return infinitable(IT_NEGINF);
				} else {
					throw std::domain_error(
						"Cannot divide two zeros or unordered values"
					);
				}
			}
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
		if((m_tag == IT_INF && other.m_tag == IT_INF)
			|| (m_tag == IT_NEGINF && other.m_tag == IT_NEGINF)) {
			return COMP_EQUAL;
		} else if(m_tag == IT_INF || other.m_tag == IT_NEGINF) {
			return COMP_GREATER;
		} else if(m_tag == IT_NEGINF || other.m_tag == IT_INF){
			return COMP_LESS;
		} else {
			return COMP_FINITE;
		}
	}
};
#endif