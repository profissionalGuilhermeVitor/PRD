#ifndef __VARSET_H__
#define __VARSET_H__
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <new>
#include <unordered_set>
//-------------------------------------------------------------------------------------
namespace std {
	using namespace std::tr1;
};
//-------------------------------------------------------------------------------------
namespace planners {
	//-------------------------------------------------------------------------------------
	class varlist
	{
	protected:
		//mutable std::unordered_set<std::string> vec;
		mutable std::vector<std::string> vec;
		mutable std::vector<std::size_t> hval;
		std::hash<std::string> hfunc;
		mutable bool needsort;
	public:
		varlist(int reserve = 0):needsort(false) { vec.reserve(reserve); };
		//--
		varlist& add(std::string var);
		varlist& add(const std::vector<std::string>& var);
		int get(const std::string& var) const;
		int size() const;
		const std::vector<std::string>& getvector() const { return vec; };
		//--
		friend bool operator==(const varlist&a, const varlist&b) { return a.vec == b.vec; };
		friend bool operator!=(const varlist&a, const varlist&b) { return a.vec != b.vec; };
	};
	//-------------------------------------------------------------------------------------
	class varset
	{
	protected:
		unsigned long* data;
		std::size_t dsize;
		varlist* vlist;
	public:
		explicit varset(varlist& vlist);
		varset(const varset& other);
		~varset();
		//--
		varset& operator= (varset other);
		//--
		bool isempty() const;
		bool isset(size_t idx) const;
		varset&set(size_t idx);
		varset&unset(size_t idx);
		bool isset(const std::string& var) const;
		varset&set(const std::string& var);
		varset&unset(const std::string& var);
		varset&set(const std::vector<std::string>& var);
		varset&unset(const std::vector<std::string>& var);
		//--
		void sanitize();
		//--
		void swap(varset&b);
		//--
		varset& operator|=(const varset&b);
		varset& operator&=(const varset&b);
		varset& operator^=(const varset&b);
		friend varset operator~(varset a);
		//--
		friend std::ostream& operator<<(std::ostream&out, const varset&a);
		//--
		friend bool operator==(const varset&a, const varset&b);
	};
	//-------------------------------------------------------------------------------------
	inline varset operator|(varset a, const varset&b) { return a |= b; }
	inline varset operator&(varset a, const varset&b) { return a &= b; }
	inline varset operator^(varset a, const varset&b) { return a ^= b; }
	inline bool operator!=(const varset&a, const varset&b) { return !(a == b); };
	//-------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------
namespace std
{
	template <> inline void swap(planners::varset& a, planners::varset& b)
	{
		a.swap(b);
	}
}
//-------------------------------------------------------------------------------------
#endif