#pragma once
#include<string>
#include<iostream>



template <size_t N>
class My_bitset {
public:
	My_bitset(const char*);
	constexpr My_bitset(unsigned long long val);
	constexpr My_bitset() = default;
	My_bitset& operator=(My_bitset& rhs);
	bool all() const;
	bool any() const;
	size_t count() const;
	My_bitset<N>& flip();
	My_bitset<N>& flip(size_t pos);
	bool none() const;
	bool operator!=(const My_bitset<N>& right) const;
	My_bitset<N>& operator&=(const My_bitset<N>& right);
	My_bitset<N> operator&(const My_bitset<N>& right);
	My_bitset<N> operator<<(size_t pos) const;
	My_bitset<N>& operator<<=(size_t pos);
	bool operator==(const My_bitset<N>& right) const;
	My_bitset<N> operator>>(size_t pos) const;
	My_bitset<N>& operator>>=(size_t pos);
	constexpr bool operator[](size_t pos) const;
	My_bitset<N>& operator^=(const My_bitset<N>& right);
	My_bitset<N>& operator|=(const My_bitset<N>& right);
	My_bitset<N> operator~() const;
	My_bitset<N> operator^(const My_bitset<N>& right);
	My_bitset<N> operator|(const My_bitset<N>& right);
	My_bitset<N>& reset();
	My_bitset<N>& reset(size_t pos);
	My_bitset<N>& set();
	My_bitset<N>& set( size_t pos, bool val = true);
	template <size_t N>
	friend void operator<<(std::ostream& os, const My_bitset<N>& x);
	size_t bit_size() const;
	bool test(size_t pos) const;
	unsigned long long to_ullong() ;
	std::string to_string() ;


private:
	const int size = sizeof(long long) * 8;
	long long data[(N % (sizeof(long long) * 8) == 0) ? N / (sizeof(long long) * 8): N / (sizeof(long long) * 8) + 1 ]{0};

	void shift_unshift();
	void convert_in_bits(unsigned long long&);
};

template <size_t N>
void operator<<(std::ostream& os, const My_bitset<N>& x)
{
	for (int i = N - 1; i >= 0; i--) {
		os << x[i];
	}
}

template<size_t N>
My_bitset<N>::My_bitset(const char* bits)
{
	for (int i = strlen(bits) - 1; i >= 0; i++)
	{
		if (bits[i] == 1 || bits[i] == 0) {
			data[i / size] | (bits[i] - '0' << i) ;
		}
	}
}

template<size_t N>
constexpr My_bitset<N>::My_bitset(unsigned long long val)
{
	convert_in_bits(val);
}

template<size_t N>
My_bitset<N>& My_bitset<N>:: operator= (My_bitset& rhs)
{
	for (int i = 0; i <= N/size; i++)
	{
		this->data[i] = rhs.data[i];
	}
}

template<size_t N>
bool My_bitset<N>::all() const
{
	for (int i = 0; i <= N / size; i++) {
		if (data[i] + 1 == 0) {
			continue;
		}
		else if ((data[i] + (long long)1 & data[i]) == 0) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

template<size_t N>
bool My_bitset<N>::none() const

{

	for (int i = 0; i <= N / size ; i++) {
		if ((data[i] ^ (long long)0 )== 0) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

template<size_t N>
bool My_bitset<N>::operator!=(const My_bitset<N>& right) const
{	
	if (count() == right.count()) {
		for (int i = 0; i < N; i++) {
			if (right[i] != *this[i]) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

template<size_t N>
My_bitset<N>& My_bitset<N>::operator&=(const My_bitset<N>& right)
{
	for (int i = 0; i <= N / size; i++) {
		data[i] &= right.data[i];
	}
	return *this;
}

template<size_t N>
My_bitset<N> My_bitset<N>::operator<<(size_t pos) const
{
	
	My_bitset<N> tmp=*this;
	int res = 0;
	for (int i = 0; i <= N / size; i++) {

		int res1 = tmp.data[i] >> size - pos;
		tmp.data[i] <<=  pos;
		tmp.data[i] |= res;
		res = res1;
	}
	tmp.shift_unshift();
	return tmp;
}

template<size_t N>
My_bitset<N>& My_bitset<N>::operator<<=(size_t pos)
{
	int res = 0;
	for (int i = 0; i <= N / size; i++) {

		int res1 = data[i] >> size - pos;
		data[i] <<= pos;
		data[i] |= res;
		res = res1;
	}
	shift_unshift();
	return *this;
}

template<size_t N>
My_bitset<N> My_bitset<N>::operator>>(size_t pos) const
{

	My_bitset<N> tmp = *this;
	int res = 0;
	for (int i = 0; i <= N / size; i++) {

		int res1 = tmp.data[i] << size - pos;
		tmp.data[i] >>= pos;
		tmp.data[i] |= res;
		res = res1;
	}
	tmp.shift_unshift();
	return tmp;
}

template<size_t N>
My_bitset<N>& My_bitset<N>::operator>>=(size_t pos)
{
	int res = 0;
	for (int i = 0; i <= N / size; i++) {

		int res1 = data[i] << size - pos;
		data[i] >>= pos;
		data[i] |= res;
		res = res1;
	}
	shift_unshift();
	return *this;
}

template<size_t N>
bool My_bitset<N>::any() const
{
	return !none();
}

template<size_t N>
size_t My_bitset<N>::count() const
{
	if (any()) {
		int count = 0;
		for (int i = 0; i < N; i++) {
			if (this->operator[](i) == true) {
				count++;
			}
		}
		return count;
	}
	else {
		return 0;
	}

}

template<size_t N>
My_bitset<N>& My_bitset<N>::flip()
{
	for (int i = 0; i <= N / size; i++) {
		data[i] = data[i] ^ ~((long long)0);
	}
	shift_unshift();
	return *this;
}

template<size_t N>
My_bitset<N>& My_bitset<N>::flip(size_t pos)
{
	data[pos / size] ^= (1 << pos % size);
	return *this;
}

template<size_t N>
bool My_bitset<N>::operator==(const My_bitset<N>& right) const
{
	return !(*this != right);
}

template<size_t N>
constexpr bool My_bitset<N>::operator[](size_t pos) const
{
	bool tmp = data[pos / size] & (1 << pos % size);
	return tmp;
}

template<size_t N>
My_bitset<N>& My_bitset<N>::operator^=(const My_bitset<N>& right)
{
	for (int i = 0; i <= N/size; i++)
	{
		data[i] = data[i] ^ right.data[i];
	}
	return *this;
}

//template<size_t N>
//My_bitset<N>& My_bitset<N>::operator&=(const My_bitset<N>& right)
//{
//	for (int i = 0; i < N / size; i++)
//	{
//		data[i] = data[i] & right.data[i];
//	}
//	return *this;
//}

template<size_t N>
My_bitset<N>& My_bitset<N>::operator|=(const My_bitset<N>& right)
{
	for (int i = 0; i <= N / size; i++)
	{
		data[i] = data[i] | right.data[i];
	}
	return *this;
}

template<size_t N>
My_bitset<N> My_bitset<N>::operator^(const My_bitset<N>& right)
{
	My_bitset<N> tmp;
	for (int i = 0; i <= N / size; i++)
	{
		tmp.data[i] = data[i] ^ right.data[i];
	}
	return tmp;
}

template<size_t N>
My_bitset<N> My_bitset<N>::operator&(const My_bitset<N>& right)
{
	My_bitset<N> tmp;
	for (int i = 0; i <= N / size; i++)
	{
		tmp.data[i] = data[i] & right.data[i];
	}
	return tmp;
}

template<size_t N>
 My_bitset<N> My_bitset<N>::operator|(const My_bitset<N>& right)
{
	 My_bitset<N> tmp;
	for (int i = 0; i <= N / size; i++)
	{
		tmp.data[i] = data[i] | right.data[i];
	}
	return tmp;
}

template<size_t N>
My_bitset<N> My_bitset<N>::operator~() const
{
	return this->flip();
}

template<size_t N>
void My_bitset<N>::convert_in_bits(unsigned long long& val)
{
	for (int i = 0; i < N && val != 0; i++) {
		data[i / size] |= ((val % 2) << i % size);
		val /= 2;
	}
}

template<size_t N>
size_t My_bitset<N>::bit_size() const
{
	return N;
}

template<size_t N>
bool My_bitset<N>::test(size_t pos) const
{
	return data[pos / size] >> pos % size & 1;
}

template<size_t N>
unsigned long long My_bitset<N>::to_ullong()
{
	return data[0];
}

template<size_t N>
std::string My_bitset<N>::to_string()
{
	std::string str;
	for (int i = N-1; i >= 0; i--)
	{
		str += (int)this->operator[](i) + '0';
	}
	return str;
}

template<size_t N>
My_bitset<N>& My_bitset<N>::reset()
{
	for (int i = 0; i <= N / size; i++) {
		data[i] = data[i] & (long long)0;
	}
	return *this;
}

template<size_t N>
My_bitset<N>& My_bitset<N>::reset(size_t pos)
{
	data[pos / size] &= ~(1 << pos % size);
	return *this;
}

template<size_t N>

void My_bitset<N>::shift_unshift() {
	data[N / size - 1] << size - N % size;
	data[N / size - 1] >> size - N % size;
}

template<size_t N>
My_bitset<N>& My_bitset<N>::set()
{
	for (int i = 0; i <= N / size; i++) {
		data[i] = data[i] | (long long)-1;
	}
	shift_unshift();
	return *this;
}

template<size_t N>
My_bitset<N>& My_bitset<N>::set(size_t pos, bool val)
{
	data[pos / size] |= val << pos % size;
	return *this;
}



