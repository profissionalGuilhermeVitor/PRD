#include "varset.h"
#include <new>
#include <cstring>
#include <algorithm>
namespace planners {
	//-------------------------------------------------------------------------------------
	// varlist
	//-------------------------------------------------------------------------------------
	template <typename Iter>
	Iter SelectPivot(Iter begin, Iter end)
	{
		// Current implementation just returns the middle element,
		// but we are free to choose the pivot in any other way.
		std::advance(begin, std::distance(begin, end) / 2);
		return begin;
	}
	
	// Implements the quick sort algorithm.
	template <typename Iter, typename Iter2, typename Cmp>
	void QuickSort(Iter begin, Iter end, Iter2 begin2, Iter2 end2, Cmp less)
	{
		// No need to sort an empty or a single-element sequence.
		if (std::distance(begin, end) < 2)
		{
			return;
		}

		// Select the pivot element and store
		// its value in 'val' variable.
		Iter pivot = SelectPivot(begin, end);
		Iter2 pivot2 = SelectPivot(begin2, end2);
		std::iterator_traits<Iter>::value_type val = *pivot;

		// Introduce new iterators to operate on,
		// begin and end will be needed for recursive
		// calls, so we do not modify them.
		Iter left = begin;
		Iter right = end;
		Iter2 left2 = begin2;
		Iter2 right2 = end2;

		// Like all the similar algorithms in STL, our function accepts
		// a pair of iterators, pointing to the first and one beyond
		// the last elements respectively. That's why we should not
		// consider the value pointed to by 'end'.
		std::advance(right, -1);
		std::advance(right2, -1);
		
		// Move the pivot element to the end of the sequence.
		std::swap(*pivot, *right);
		std::swap(*pivot2, *right2);

		// The following piece of code partitions the whole into
		// two sub-sequences so that all the elemets less than the
		// pivot appear to the left from pivot and all the greater
		// elements appear to the right. This means that the chosen
		// pivot element will be in its final place.
		Iter pivot_position = left;
		Iter2 pivot_position2 = left2;

		while (left != right)
		{
			if (less(*left, val))
			{
				std::swap(*left, *pivot_position);
				std::swap(*left2, *pivot_position2);
				std::advance(pivot_position, 1);
				std::advance(pivot_position2, 1);
			}
			std::advance(left, 1);
			std::advance(left2, 1);
		}
				
		// The pivot_position now points to the first
		// element which is not 'less' than the pivot. So we
		// need to swap the pivot stored in the rightmost
		// element with that stored in pivot_position.
		std::swap(*pivot_position, *right);
		std::swap(*pivot_position2, *right2);

		// Calling the function recursively to
		// sort the sub-sequences to the left
		// and right from the pivot. The latter
		// is already in its final position.
		right = pivot_position;
		right2 = pivot_position2;
		std::advance(right, 1);
		std::advance(right2, 1);

		QuickSort(begin, pivot_position, begin2, pivot_position2, less);
		QuickSort(right, end, right2, end2, less);
	}
	template <typename Iter, typename Iter2>
	void QuickSort(Iter begin, Iter end, Iter2 begin2, Iter2 end2)
	{
		QuickSort(begin, end, begin2, end2, [](const std::iterator_traits<Iter>::value_type&a, const std::iterator_traits<Iter>::value_type&b){return a < b; });
	}
	//-------------------------------------------------------------------------------------
	template<class Iter, class T>
	Iter binary_find(Iter begin, Iter end, T val)
	{
		// Finds the lower bound in at most log(last - first) + 1 comparisons
		Iter i = std::lower_bound(begin, end, val);

		if (i != end && !(val < *i))
			return i; // found
		else
			return end; // not found
	}
	//-------------------------------------------------------------------------------------
	varlist& varlist::add(std::string var)
	{
		if (!var.empty() && var[0] != '!')
		{
			vec.push_back(var); // adiciona fato à lista
			vec.push_back('!' + var); // adiciona fato complementar à lista
			needsort = true; // ajusta flag para ordenamento futuro
		}
		return *this;
	}
	//-------------------------------------------------------------------------------------
	varlist& varlist::add(const std::vector<std::string>& var)
	{
		if (!var.empty())
		{
			std::vector<std::string> vec2;
			vec2.resize(var.size());
			std::transform(var.begin(), var.end(), vec2.begin(), [](const std::string& s){return '!' + s; });
			needsort = true;
			vec.insert(vec.end(), var.begin(), var.end());
			vec.insert(vec.end(), vec2.begin(), vec2.end());
		}
		return *this;
	}
	//-------------------------------------------------------------------------------------
	int varlist::get(const std::string& var) const
	{
		if (needsort)
		{
			hval.clear();
			hval.reserve(vec.size());
			// calcula o hash dos nomes dos fatos
			for (auto& s : vec) hval.push_back(hfunc(s));
			// ordena a lista dos fatos e dos valores hash simultaneamente
			QuickSort(hval.begin(), hval.end(), vec.begin(), vec.end());
			needsort = false;
		}
		std::size_t h = hfunc(var);
		auto it = hval.begin();
		auto it2 = vec.begin();
		// realiza busca pelo valor hash
		it = binary_find(it, hval.end(), h);
		it2 = (vec.begin() + std::distance(hval.begin(), it));
		// o laço abaixo previne que colisões de valores hash
		// permitam que o código retorne um elemento errado
		while (it != hval.end() && var != *it2)
		{
			it++;
			if (*it != h)
				it = hval.end();
			else
				it2 = (vec.begin() + std::distance(hval.begin(), it));
		}
		if (it != hval.end())
		{
			int idx = std::distance(hval.begin(), it) + 1;
			return idx;
		}
		return 0; // retorna 0 caso o fato não seja encontrado
	}
	//-------------------------------------------------------------------------------------
	int varlist::size() const
	{
		return vec.size();
	}
	//-------------------------------------------------------------------------------------
	// varset
	//-------------------------------------------------------------------------------------
	varset::varset(varlist& vlist)
	{
		this->vlist = &vlist;
		data = NULL;
		dsize = (vlist.size() / (8 * sizeof(unsigned long))) + ((vlist.size() % (8 * sizeof(unsigned long)) > 0) ? 1 : 0);
		if (dsize > 0)
		{
			data = new unsigned long[dsize];
			std::memset(data, 0, dsize*sizeof(unsigned long));
		}
	}
	//-------------------------------------------------------------------------------------
	varset::varset(const varset& other)
	{
		vlist = other.vlist;
		data = NULL;
		dsize = other.dsize;
		if (dsize > 0)
		{
			data = new unsigned long[dsize];
			std::memcpy(data, other.data, dsize*sizeof(unsigned long));
		}
	}
	//-------------------------------------------------------------------------------------
	varset::~varset()
	{
		vlist = NULL;
		dsize = 0;
		if (data /*&& dsize*/) delete[] data;
	}
	//-------------------------------------------------------------------------------------
	varset& varset::operator= (varset other)
	{
		swap(other);
		return *this;
	}
	//-------------------------------------------------------------------------------------
	void varset::swap(varset&b)
	{
		using std::swap;
		swap(b.data, data);
		swap(b.vlist, vlist);
		swap(b.dsize, dsize);
	}
	//-------------------------------------------------------------------------------------
	bool varset::isempty() const
	{
		if (!vlist || !data) return true;
		for (unsigned i = 0; i<dsize; i++)
		{
			if (data[i] != 0) return false;
		}
		return true;
	}
	//-------------------------------------------------------------------------------------
	bool varset::isset(size_t idx) const
	{
		if (idx == 0 || !vlist || idx>(size_t)vlist->size()) return false;
		size_t i = (idx - 1) / (8 * sizeof(unsigned long));
		size_t shift = (idx - 1) % (8 * sizeof(unsigned long));
		return (data[i] >> shift) & 1;
	}
	//-------------------------------------------------------------------------------------
	varset&varset::set(size_t idx)
	{
		if (idx == 0 || !vlist || idx > (size_t)vlist->size()) return *this;
		size_t i = (idx - 1) / (8 * sizeof(unsigned long));
		size_t shift = (idx - 1) % (8 * sizeof(unsigned long));
		data[i] |= 1ul << shift;
		return *this;
	}
	//-------------------------------------------------------------------------------------
	varset&varset::unset(size_t idx)
	{
		if (idx == 0 || !vlist || idx > (size_t)vlist->size()) return *this;
		size_t i = (idx - 1) / (8 * sizeof(unsigned long));
		size_t shift = (idx - 1) % (8 * sizeof(unsigned long));
		data[i] &= ~(1ul << shift);
		return *this;
	}
	//-------------------------------------------------------------------------------------
	bool varset::isset(const std::string& var) const
	{
		if (!vlist) return false;
		size_t idx = vlist->get(var);
		return isset(idx);
	}
	//-------------------------------------------------------------------------------------
	varset&varset::set(const std::string& var)
	{
		if (!vlist) return *this;
		size_t idx = vlist->get(var);
		return set(idx);
	}
	//-------------------------------------------------------------------------------------
	varset&varset::unset(const std::string& var)
	{
		if (!vlist) return *this;
		size_t idx = vlist->get(var);
		return unset(idx);
	}
	//-------------------------------------------------------------------------------------
	varset&varset::set(const std::vector<std::string>& var)
	{
		if (!vlist) return *this;
		for (std::vector<std::string>::const_iterator it = var.begin(); it != var.end(); it++)
		{
			set(*it);
		}
		return *this;
	}
	//-------------------------------------------------------------------------------------
	varset&varset::unset(const std::vector<std::string>& var)
	{
		if (!vlist) return *this;
		for (std::vector<std::string>::const_iterator it = var.begin(); it != var.end(); it++)
		{
			unset(*it);
		}
		return *this;
	}
	//-------------------------------------------------------------------------------------
	void varset::sanitize()
	{
		if (!vlist) return;
		auto& vec = vlist->getvector();
		int idx = 0;
		for (auto it = vec.begin(); it != vec.end(); it++)
		{
			idx++;
			if ((*it)[0] != '!')
			{
				if (isset(idx))
					unset('!' + (*it));
				else
					set('!' + (*it));
			}
		}
	}
	//-------------------------------------------------------------------------------------
	varset& varset::operator|=(const varset&b) // OU
	{
		if ((dsize != b.dsize) || (vlist != b.vlist && *vlist != *b.vlist)) {
			return *this;
		}
		for (size_t i = 0; i < dsize; i++) {
			data[i] |= b.data[i];
		}
		return *this;
	}
	//-------------------------------------------------------------------------------------
	varset& varset::operator&=(const varset&b) // E
	{
		if ((dsize != b.dsize) || (vlist != b.vlist && *vlist != *b.vlist)) {
			return *this;
		}
		for (size_t i = 0; i < dsize; i++) {
			data[i] &= b.data[i];
		}
		return *this;
	}
	//-------------------------------------------------------------------------------------
	varset& varset::operator^=(const varset&b) // OU EXCLUSIVO
	{
		if ((dsize != b.dsize) || (vlist != b.vlist && *vlist != *b.vlist)) {
			return *this;
		}
		for (size_t i = 0; i<dsize; i++) {
			data[i] ^= b.data[i];
		}
		return *this;
	}
	//-------------------------------------------------------------------------------------
	varset operator~(varset a) // Porta inversora
	{
		if (a.dsize == 0) return a;
		if (a.vlist->size() % (8 * sizeof(unsigned long))>0)
		{
			for (size_t i = 0; i < a.dsize - 1; i++) {
				a.data[i] = ~a.data[i];
			}
			// cria uma máscara para impedir que bits não utilizados sejam alterados
			// (importante para que funções de comparação)
			unsigned long mask = ~0ul << (a.vlist->size() % (8 * sizeof(unsigned long)));
			a.data[a.dsize - 1] = (~a.data[a.dsize - 1]) & (~mask);
		}
		else
		{
			for (size_t i = 0; i < a.dsize; i++) {
				a.data[i] = ~a.data[i];
			}
		}
		return a;
	}
	//-------------------------------------------------------------------------------------
	std::ostream& operator<<(std::ostream&out, const varset&a)
	{
		if (!a.vlist || !a.data) {
			return out << "NULL";
		}
		for (size_t i = a.vlist->size(); i > 0; i--) {
			size_t idx = (i - 1) / (8 * sizeof(unsigned long));
			size_t shift = (i - 1) % (8 * sizeof(unsigned long));
			out << ((a.data[idx] >> shift) & 1) ? '1' : '0';
		}
		return out;
	}
	//-------------------------------------------------------------------------------------
	bool operator==(const varset&a, const varset&b)
	{
		if ((a.dsize != b.dsize) || (a.vlist != b.vlist && *a.vlist != *b.vlist)) {
			return false;
		}
		return memcmp(a.data, b.data, a.dsize*sizeof(unsigned long)) == 0;
		/*for(size_t i=0;i<a.dsize;i++) {
			if(a.data[i]!=b.data[i]) return false;
			}
			return true;*/
	}
	//-------------------------------------------------------------------------------------
}