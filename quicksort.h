#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_
#include <iostream>
#include <algorithm> //partition
#include <iterator> //distance, advance

extern bool verbose;

template<typename Iterator>
void inspect(Iterator first, Iterator last, Iterator pivot, int pass) {
    int inc = std::distance(first,pivot);
    std::vector<int> digits(inc);
    std::transform(first, pivot, digits.begin(), [](const int val) { return std::to_string(val).size()+2; } );
    int digit_count=std::accumulate(digits.begin(), digits.end(), 0);
    std::cerr.width(11+digit_count);
    std::cerr << std::right << "^" << std::endl;
}

template<typename BidirectionalIterator>
int quicksort(BidirectionalIterator first, BidirectionalIterator last, int pass=0) {
    typedef typename BidirectionalIterator::value_type value_type;
    if (first == last)
	return pass;

    if (verbose)
	std::cerr << "Pass " << pass << "-: " << streamifier(first, last) << std::endl;

    //Actual algorithm. Since the pivot value is somewhat arbitrary, we'll just use whatever value is at first
    BidirectionalIterator pivot = std::stable_partition(first, last, std::bind2nd(std::less<value_type>(), *first));

    if (verbose) {
	std::cerr << "Pass " << pass << "+: " << streamifier(first, last) << std::endl;
	inspect(first,last,pivot,pass);
    }
    int pass1 = quicksort(first, pivot, pass+1);
    int pass2 = 0;
    if (pivot != last)
	pass2 = quicksort(pivot+1, last, pass+1);
    return std::max(pass1,pass2);
}

template<typename BidirectionalIterator>
int quicksort2(BidirectionalIterator first, BidirectionalIterator last, int pass=0) {
    typedef typename BidirectionalIterator::value_type value_type;
    if (first == last)
	return pass;

    if (verbose)
	std::cerr << "Pass " << pass << "-: " << streamifier(first, last) << std::endl;
    value_type pivot_value = *first;

    //Actual algorithm. Since the pivot value is somewhat arbitrary, we'll just use whatever value is at first
    BidirectionalIterator pivot = std::partition(first, last, std::bind2nd(std::less<value_type>(), pivot_value));
    //Since we are not using stable_partition we need to make sure the pivot value is at the pivot point
    BidirectionalIterator it = std::find(pivot,last,pivot_value);
    std::iter_swap(it, pivot);

    if (verbose) {
	std::cerr << "Pass " << pass << "+: " << streamifier(first, last) << std::endl;
	inspect(first,last,pivot,pass);
    }
    int pass1 = quicksort(first, pivot, pass+1);
    int pass2 = 0;
    if (pivot != last)
	pass2 = quicksort(pivot+1, last, pass+1);
    return std::max(pass1,pass2);
}


#endif
