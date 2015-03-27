#pragma once

#include "util/value_ref.hpp"
#include <algorithm>
#include <stdexcept>

namespace math { namespace detail
{
    
struct sequence_iterator
{

public:
    
    sequence_iterator(int const n, int const upper) 
        : n{n}, upper{upper}
    { 
    }
    
    int operator * ()
    { 
        return this->n; 
    }    
    
    sequence_iterator& operator ++ ()
    { 
        this->n = std::min(this->upper, this->n + 1); 

        return *this; 
    }

    bool operator != (util::value_ref<sequence_iterator> rhs) const 
    { 
        return (this->n != rhs.n);
    }

private:
    
    int n;
    
    int upper;

};
    
struct sequence
{

public:
    
    sequence(int from, int to) : from{from}, to{to}
    { 
    }    
    
    sequence_iterator begin() const
    { 
        return {this->from, this->to}; 
    }
    
    sequence_iterator end() const
    { 
        return {this->to, this->to}; 
    }

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

detail::sequence sequence(int const from, int const to)
{
    if (to < from) 
    { 
        throw bad_interval_exception{};
    }
    
    return {from, to};
}

}