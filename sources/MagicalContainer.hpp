#ifndef MAGICAL_CONTAINER_H
#define MAGICAL_CONTAINER_H

// all the necessary includes for the hpp and cpp
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <iostream>
using namespace std;

namespace ariel
{

    class MagicalContainer
    {
        vector<int> defaultElements;
        vector<int *> ascendingElements;
        vector<int *> sideCrossElements;
        vector<int *> primeElements;

        bool isPrime(int number) const;
        class BaseIterator;
        void updateAll();

    public:
        MagicalContainer();
        ~MagicalContainer();
        MagicalContainer(const MagicalContainer &other);
        MagicalContainer &operator=(const MagicalContainer &other);

        void addElement(int element);
        void removeElement(int element);
        size_t size() const;

        bool operator==(const MagicalContainer &other) const;
        bool operator!=(const MagicalContainer &other) const;

        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;
    };

    class MagicalContainer::BaseIterator
    {
    protected:
        MagicalContainer *magicalContainer;
        vector<int *>::iterator it;
        size_t pos;

    public:
        BaseIterator(MagicalContainer &magicalContainer);
        ~BaseIterator();
        BaseIterator(const BaseIterator &other);

        BaseIterator &operator=(const BaseIterator &other);
        bool operator==(const BaseIterator &other) const;
        bool operator!=(const BaseIterator &other) const;
        bool operator>(const BaseIterator &other) const;
        bool operator<(const BaseIterator &other) const;
    };

    class MagicalContainer::AscendingIterator : public MagicalContainer::BaseIterator
    {

    public:
        AscendingIterator(MagicalContainer &magicalContainer);
        ~AscendingIterator();
        AscendingIterator(const AscendingIterator &other);

        AscendingIterator &operator=(const AscendingIterator &other);
        int operator*() const;
        AscendingIterator &operator++();
        AscendingIterator &operator++(int);
        AscendingIterator begin();
        AscendingIterator end();
    };

    class MagicalContainer::SideCrossIterator : public MagicalContainer::BaseIterator
    {

    public:
        SideCrossIterator(MagicalContainer &magicalContainer);
        ~SideCrossIterator();
        SideCrossIterator(const SideCrossIterator &other);

        SideCrossIterator &operator=(const SideCrossIterator &other);
        int operator*() const;
        SideCrossIterator &operator++();
        SideCrossIterator &operator++(int);
        SideCrossIterator begin();
        SideCrossIterator end();
    };

    class MagicalContainer::PrimeIterator : public MagicalContainer::BaseIterator
    {

    public:
        PrimeIterator(MagicalContainer &magicalContainer);
        ~PrimeIterator();
        PrimeIterator(const PrimeIterator &other);

        PrimeIterator &operator=(const PrimeIterator &other);
        int operator*() const;
        PrimeIterator &operator++();
        PrimeIterator &operator++(int);
        PrimeIterator begin();
        PrimeIterator end();
    };
} // namespace ariel

#endif // MAGICAL_CONTAINER_H
