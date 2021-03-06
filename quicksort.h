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
    std::cerr.width(12+digit_count);
    std::cerr << std::right << "^" << std::endl;
}

//Algorithm 1: uses std::stable_partition
template<typename BidirectionalIterator>
int quicksort(BidirectionalIterator first, BidirectionalIterator last, int pass=0) {
    typedef typename BidirectionalIterator::value_type value_type;

    //a collection of one item is already sorted!
    if (first == last)
	return pass;

    if (verbose)
	std::cerr << "Depth " << pass << "-: " << streamifier(first, last) << std::endl;

    //Since the pivot value is somewhat arbitrary, we'll just use whatever value is at first
    BidirectionalIterator pivot = std::stable_partition(first, last, std::bind2nd(std::less<value_type>(), *first));

    if (verbose) {
	std::cerr << "Depth " << pass << "+: " << streamifier(first, last) << std::endl;
	inspect(first,last,pivot,pass);
    }

    int pass1 = quicksort(first, pivot, pass+1);
    int pass2 = 0;
    if (pivot != last)
	pass2 = quicksort(pivot+1, last, pass+1);
    return std::max(pass1,pass2);
}

//Algorithm 2: uses std::partition
template<typename BidirectionalIterator>
int quicksort2(BidirectionalIterator first, BidirectionalIterator last, int pass=0) {
    typedef typename BidirectionalIterator::value_type value_type;

    //a collection of one item is already sorted!
    if (first == last)
	return pass;

    if (verbose)
	std::cerr << "Depth " << pass << "-: " << streamifier(first, last) << std::endl;

    //Actual algorithm starts here.
    value_type pivot_value = *first;

    //Since the pivot value is somewhat arbitrary, we'll just use whatever value is at first
    BidirectionalIterator pivot = std::partition(first, last, std::bind2nd(std::less<value_type>(), pivot_value));
    //Since we are not using stable_partition we need to make sure the pivot value is at the pivot point
    BidirectionalIterator it = std::find(pivot,last,pivot_value);
    std::iter_swap(it, pivot);

    if (verbose) {
	std::cerr << "Depth " << pass << "+: " << streamifier(first, last) << std::endl;
	inspect(first,last,pivot,pass);
    }
    int pass1 = quicksort2(first, pivot, pass+1);
    int pass2 = 0;
    if (pivot != last)
	pass2 = quicksort2(pivot+1, last, pass+1);
    return std::max(pass1,pass2);
}

//Algorithm 3: uses std::partition and lambda
template<typename BidirectionalIterator>
int quicksort3(BidirectionalIterator first, BidirectionalIterator last, int pass=0) {
    typedef typename BidirectionalIterator::value_type value_type;

    if (first == last)
	return pass;

    if (verbose)
	std::cerr << "Depth " << pass << "-: " << streamifier(first, last) << std::endl;

    value_type pivot_value = *first;

    //Since the pivot value is somewhat arbitrary, we'll just use whatever value is at first
    BidirectionalIterator pivot = std::partition(first, last, [pivot_value](value_type a) { return (a < pivot_value); } );
    //Since we are not using stable_partition we need to make sure the pivot value is at the pivot point
    BidirectionalIterator it = std::find(pivot,last,pivot_value);
    std::iter_swap(it, pivot);

    if (verbose) {
	std::cerr << "Depth " << pass << "+: " << streamifier(first, last) << std::endl;
	inspect(first,last,pivot,pass);
    }
    int pass1 = quicksort3(first, pivot, pass+1);
    int pass2 = 0;
    if (pivot != last)
	pass2 = quicksort3(pivot+1, last, pass+1);
    return std::max(pass1,pass2);
}


//Algorithm 4: clean and simple
template<typename BidirectionalIterator>
int quicksort4(BidirectionalIterator first, BidirectionalIterator last, int pass=0) {
    typedef typename BidirectionalIterator::value_type value_type;

    //a collection of one item is already sorted!
    if (first == last)
	return pass;

    //Since the pivot value is somewhat arbitrary, we'll just use whatever value is at first
    value_type pivot_value = *first;

    BidirectionalIterator pivot = std::partition(first, last, std::bind2nd(std::less<value_type>(), pivot_value));
    //Make sure the pivot value is at the pivot point
    BidirectionalIterator it = std::find(pivot,last,pivot_value);
    std::iter_swap(it, pivot);

    quicksort4(first, pivot, pass+1);
    if (pivot != last)
	quicksort4(pivot+1, last, pass+1);

    return 0;
}

#endif
