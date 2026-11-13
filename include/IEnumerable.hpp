#ifndef IENUMERABLE_HPP
#define IENUMERABLE_HPP

#include "IEnumerator.hpp"

template<typename T>
class IEnumerable {
public:
    virtual IEnumerator<T> *GetEnumerator() const = 0;
    virtual ~IEnumerable() = default;
};

#endif /* IENUMERABLE_HPP */
