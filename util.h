#ifndef _UTIL_H_
#define _UTIL_H_
#include <cassert>
#include <ostream>

template<typename T>
struct Enumerator {
    T value;
    Enumerator(T start=T()) : value(start) {};
    int operator()() {
	return value++;
    }
};

template<typename ForwardIterator>
std::ostream& print_range(std::ostream& out, ForwardIterator first, ForwardIterator last) {
    out << "[";
    assert(first<last);
    while(first!=last)
    {
	out << *first++;
	if(first != last)
	    out << ", ";
    }
    out << "]";
    return out;
}

template<typename Iterator>
struct Streamifier {
    Iterator first;
    Iterator last;
    Streamifier(Iterator f, Iterator l) : first(f), last(l) {};
};

template<typename Container>
Streamifier<typename Container::const_iterator> streamifier(const Container& c) { return Streamifier<typename Container::const_iterator>(c.begin(), c.end()); };

template<typename Iterator>
Streamifier<Iterator> streamifier(Iterator first, Iterator last) { return Streamifier<Iterator>(first, last); };

template<typename Container>
std::ostream& operator<<(std::ostream& out, const Streamifier<Container>& s) {
    print_range(out, s.first, s.last);
    return out;
}

#endif
