#ifndef IENUMERATOR_HPP
#define IENUMERATOR_HPP

template<typename T>
class IEnumerator {
public:
    virtual bool HasNext() const = 0;
    virtual const T& Next() = 0;

    virtual ~IEnumerator() = default;
};

#endif /* IENUMERATOR_HPP */
