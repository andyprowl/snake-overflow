#pragma once

#include "util/value_ref.hpp"
#include <stdexcept>

namespace math { namespace detail
{

struct sequence_iterator
{

public:
    
    sequence_iterator(int const n, int const upper);
    
    int operator * () const;
    
    sequence_iterator& operator ++ ();

    bool operator != (util::value_ref<sequence_iterator> rhs) const;

private:
    
    int n;
    
    int upper;

};
    
struct sequence
{

public:
    
    sequence(int from, int to);

    sequence_iterator begin() const;    
    
    sequence_iterator end() const;

private:
    
    int from;
    
    int to;

};

} }

namespace math
{

class bad_interval_exception : public virtual std::exception
{
};

detail::sequence sequence(int const from, int const to);

}