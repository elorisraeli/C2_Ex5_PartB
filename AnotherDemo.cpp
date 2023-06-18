#include <iostream>
#include "sources/MagicalContainer.hpp"

using namespace ariel;

void printMagicalContainer(MagicalContainer &container, std::string containerName);

int main()
{
    // Create two MagicalContainers and add some elements
    MagicalContainer container1, container2;
    for (int i = 2; i <= 20; i += 2)
    {
        container1.addElement(i);
    }
    for (int i = 3; i <= 30; i += 3)
    {
        container2.addElement(i);
    }

    printMagicalContainer(container1, "container1");
    printMagicalContainer(container2, "container2");

    // Compare AscendingIterators
    MagicalContainer::AscendingIterator ascIter1(container1);
    MagicalContainer::AscendingIterator end1 = ascIter1.end();
    MagicalContainer::AscendingIterator ascIter2(container2);
    MagicalContainer::AscendingIterator end2 = ascIter2.end();

    try
    {
        if (ascIter1.begin() != ascIter2.begin())
        {
            std::cout << "Begin iterators for container1 and container2 are not equal.\n";
        }
        else
        {
            std::cout << "Begin iterators for container1 and container2 are equal.\n";
        }
        
        if (ascIter2.begin() > ascIter2.end())
        {
            std::cout << "Begin iterator is greater than end iterator for container2.\n";
        }
        else
        {
            std::cout << "Begin iterator is not greater than end iterator for container2.\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Execption:" << e.what() << '\n';
    }
    // end compare AscendingIterators

    // Check if containers are equal
    if (container1 == container2)
    {
        std::cout << "The containers are equal.\n";
    }
    else
    {
        std::cout << "The containers are not equal.\n";
    }

    // Assign container2 to container1 and check equality again
    container1 = container2;
    if (container1 == container2)
    {
        std::cout << "After assignment, the containers are equal.\n";
    }
    else
    {
        std::cout << "After assignment, the containers are not equal.\n";
    }

    // Check if an element is present in the container before and after removing
    int elementToRemove = 9;
    try
    {
        container1.removeElement(elementToRemove);
        std::cout << "Element " << elementToRemove << " removed from container1.\n";
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Exception caught while trying to remove element: " << e.what() << '\n';
    }

    try
    {
        container1.removeElement(elementToRemove);
        std::cout << "Element " << elementToRemove << " removed from container1.\n";
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Exception caught while trying to remove element: " << e.what() << '\n';
    }

    return 0;
}

void printMagicalContainer(MagicalContainer &container, std::string containerName)
{
    // Print container size
    std::cout << "Size of " << containerName << ": " << container.size() << std::endl;

    // Use AscendingIterator to display elements in ascending order
    std::cout << "Elements in ascending order for " << containerName << ":\n";
    MagicalContainer::AscendingIterator ascIter(container);
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    // Use SideCrossIterator to display elements in side-cross order
    std::cout << "Elements in side-cross order for " << containerName << ":\n";
    MagicalContainer::SideCrossIterator sideCrossIter(container);
    for (auto it = sideCrossIter.begin(); it != sideCrossIter.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    // Use PrimeIterator to display prime numbers only
    std::cout << "Prime numbers in " << containerName << ":\n";
    MagicalContainer::PrimeIterator primeIter(container);
    for (auto it = primeIter.begin(); it != primeIter.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}