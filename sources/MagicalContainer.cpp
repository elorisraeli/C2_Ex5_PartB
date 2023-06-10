#include "MagicalContainer.hpp"

namespace ariel
{
    /************* MagicalContainer ************/

    bool MagicalContainer::isPrime(int num) const
    {
        if (num <= 1)
        {
            return false;
        }
        for (int i = 2; i <= sqrt(num); ++i)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    /* Updating all the element in all the vectors */
    void MagicalContainer::updateAll()
    {
        /* Update the Ascending iterator vector*/
        ascendingElements.clear();
        for (auto it = defaultElements.begin(); it != defaultElements.end(); ++it)
        {
            ascendingElements.push_back(&(*it));
        }
        sort(ascendingElements.begin(), ascendingElements.end(), [](int *a, int *b)
             { return (*a) < (*b); });

        /* Update the Side Cross iterator vector*/
        sideCrossElements.clear();
        auto start_it = ascendingElements.begin();
        auto end_it = ascendingElements.rbegin();

        bool is_start_addition = true;
        for (int i = 0; i < ascendingElements.size(); ++i)
        {
            if (is_start_addition)
            {
                sideCrossElements.push_back(*start_it);
                ++start_it;
            }
            else
            {
                sideCrossElements.push_back(*end_it);
                ++end_it;
            }
            is_start_addition = !is_start_addition;
        }

        /* Update the Prime iterator vector*/
        primeElements.clear();
        for (auto it = defaultElements.begin(); it != defaultElements.end(); ++it)
        {
            if (isPrime(*it))
            {
                primeElements.push_back(&(*it));
            }
        }
    }

    MagicalContainer::MagicalContainer()
    {
    }

    MagicalContainer::~MagicalContainer()
    {
    }

    MagicalContainer::MagicalContainer(const MagicalContainer &other)
    {
        defaultElements = other.defaultElements;
        ascendingElements = other.ascendingElements;
        sideCrossElements = other.sideCrossElements;
        primeElements = other.primeElements;
    }

    void MagicalContainer::addElement(int element)
    {
        defaultElements.push_back(element);
        updateAll();
    }

    void MagicalContainer::removeElement(int element)
    {
        auto it = find(defaultElements.begin(), defaultElements.end(), element);
        if (it == defaultElements.end())
        {
            throw runtime_error("Element not found");
        }

        if (defaultElements.size() == 0)
        {
            return;
        }
        defaultElements.erase(remove(defaultElements.begin(), defaultElements.end(), element), defaultElements.end());
        updateAll();
    }

    size_t MagicalContainer::size() const
    {
        return defaultElements.size();
    }

    bool MagicalContainer::operator==(const MagicalContainer &other) const
    {
        return defaultElements == other.defaultElements;
    }

    bool MagicalContainer::operator!=(const MagicalContainer &other) const
    {
        return defaultElements != other.defaultElements;
    }

    MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other)
    {
        if (this == &other)
        {
            return *this;
        }
        defaultElements = other.defaultElements;
        return *this;
    }

    /************ BaseIterator ***********/

    MagicalContainer::BaseIterator::BaseIterator(MagicalContainer &magicalContainer) : magicalContainer(&magicalContainer), pos(0)
    {
    }

    MagicalContainer::BaseIterator::~BaseIterator()
    {
    }

    MagicalContainer::BaseIterator::BaseIterator(const BaseIterator &other) : magicalContainer(other.magicalContainer), pos(other.pos)
    {
    }

    MagicalContainer::BaseIterator &MagicalContainer::BaseIterator::operator=(const BaseIterator &other)
    {
        if (this->magicalContainer != other.magicalContainer)
        {
            throw runtime_error("Copy allow only from same container");
        }
        magicalContainer = other.magicalContainer;
        it = other.it;
        pos = other.pos;
        return *this;
    }

    bool MagicalContainer::BaseIterator::operator==(const BaseIterator &other) const
    {
        if (this->magicalContainer != other.magicalContainer)
        {
            throw invalid_argument("Comparation of iterators allow only from same MagicalContainers");
        }
        return pos == other.pos;
    }

    bool MagicalContainer::BaseIterator::operator!=(const BaseIterator &other) const
    {
        if (this->magicalContainer != other.magicalContainer)
        {
            throw invalid_argument("Comparation of iterators allow only from same MagicalContainers");
        }
        return pos != other.pos;
    }

    bool MagicalContainer::BaseIterator::operator>(const BaseIterator &other) const
    {
        if (this->magicalContainer != other.magicalContainer)
        {
            throw invalid_argument("Comparation of iterators allow only from same MagicalContainers");
        }
        return pos > other.pos;
    }

    bool MagicalContainer::BaseIterator::operator<(const BaseIterator &other) const
    {
        if (this->magicalContainer != other.magicalContainer)
        {
            throw invalid_argument("Comparation of iterators allow only from same MagicalContainers");
        }
        return pos < other.pos;
    }

    /************ AscendingIterator ***********/

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &magicalContainer) : BaseIterator(magicalContainer)
    {
        it = magicalContainer.ascendingElements.begin();
    }

    MagicalContainer::AscendingIterator::~AscendingIterator()
    {
    }

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : BaseIterator(other)
    {
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (this->magicalContainer != other.magicalContainer)
        {
            throw runtime_error("Copy allow only from same container");
        }
        magicalContainer = other.magicalContainer;
        it = other.it;
        pos = other.pos;
        return *this;
    }

    int MagicalContainer::AscendingIterator::operator*() const
    {
        if (it == magicalContainer->ascendingElements.end())
        {
            throw runtime_error("AscendingIterator out of range");
        }
        return **it;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        if (it == magicalContainer->ascendingElements.end())
        {
            throw runtime_error("AscendingIterator out of range");
            return *this;
        }
        ++it;
        ++pos;
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++(int)
    {
        if (it == magicalContainer->ascendingElements.end())
        {
            throw runtime_error("AscendingIterator out of range");
            return *this;
        }
        AscendingIterator &beforeRaising(*this);
        ++it;
        ++pos;
        return beforeRaising;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        AscendingIterator it_copy(*this);
        it_copy.it = magicalContainer->ascendingElements.begin();
        it_copy.pos = 0;
        return it_copy;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
    {
        AscendingIterator it_copy(*this);
        it_copy.it = magicalContainer->ascendingElements.end();
        it_copy.pos = magicalContainer->ascendingElements.size();
        return it_copy;
    }

    /************ SideCrossIterator ***********/

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &magicalContainer) : BaseIterator(magicalContainer)
    {
        it = magicalContainer.sideCrossElements.begin();
    }

    MagicalContainer::SideCrossIterator::~SideCrossIterator()
    {
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : BaseIterator(other)
    {
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (this->magicalContainer != other.magicalContainer)
        {
            throw runtime_error("Copy allow only from same container");
        }
        magicalContainer = other.magicalContainer;
        it = other.it;
        pos = other.pos;
        return *this;
    }

    int MagicalContainer::SideCrossIterator::operator*() const
    {
        if (it == magicalContainer->sideCrossElements.end())
        {
            throw runtime_error("SideCrossIterator out of range");
        }
        return **it;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {
        if (it == magicalContainer->sideCrossElements.end())
        {
            throw runtime_error("SideCrossIterator out of range");
            return *this;
        }
        ++it;
        ++pos;
        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++(int)
    {
        if (it == magicalContainer->sideCrossElements.end())
        {
            throw runtime_error("SideCrossIterator out of range");
            return *this;
        }
        SideCrossIterator &beforeRaising(*this);
        ++it;
        ++pos;
        return beforeRaising;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {
        SideCrossIterator it_copy(*this);
        it_copy.it = magicalContainer->sideCrossElements.begin();
        it_copy.pos = 0;
        return it_copy;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        SideCrossIterator it_copy(*this);
        it_copy.it = magicalContainer->sideCrossElements.end();
        it_copy.pos = magicalContainer->sideCrossElements.size();
        return it_copy;
    }

    // /************* PrimeIterator ***************/

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &magicalContainer) : BaseIterator(magicalContainer)
    {
        it = magicalContainer.primeElements.begin();
    }

    MagicalContainer::PrimeIterator::~PrimeIterator()
    {
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : BaseIterator(other)
    {
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (this->magicalContainer != other.magicalContainer)
        {
            throw runtime_error("Copy allow only from same container");
        }
        magicalContainer = other.magicalContainer;
        it = other.it;
        pos = other.pos;
        return *this;
    }

    int MagicalContainer::PrimeIterator::operator*() const
    {
        if (it == magicalContainer->primeElements.end())
        {
            throw runtime_error("PrimeIterator out of range");
        }
        return **it;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        if (it == magicalContainer->primeElements.end())
        {
            throw runtime_error("PrimeIterator out of range");
            return *this;
        }
        ++it;
        ++pos;
        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++(int)
    {
        if (it == magicalContainer->primeElements.end())
        {
            throw runtime_error("PrimeIterator out of range");
            return *this;
        }
        PrimeIterator &beforeRaising(*this);
        ++it;
        ++pos;
        return beforeRaising;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    {
        PrimeIterator it_copy(*this);
        it_copy.it = magicalContainer->primeElements.begin();
        it_copy.pos = 0;
        return it_copy;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
    {
        PrimeIterator it_copy(*this);
        it_copy.it = magicalContainer->primeElements.end();
        it_copy.pos = magicalContainer->primeElements.size();
        return it_copy;
    }

}