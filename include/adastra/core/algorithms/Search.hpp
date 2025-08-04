#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <vector>
#include <functional>
#include <cstdint>
#include <iostream>

namespace adastra
{
    namespace core
    {
        namespace algorithms
        {
            template <typename T>
            class Search
            {
            public:
                static int binarySearch(const std::vector<int> &v, int target)
                {
                    int left = 0, right = v.size() - 1;

                    while (left <= right)
                    {
                        int mid = left + (right - left) / 2;

                        if (v[mid] == target)
                        {
                            return mid;
                        }
                        else if (v[mid] < target)
                        {
                            left = mid + 1;
                        }
                        else
                        {
                            right = mid - 1;
                        }
                    }
                    return -1;
                }

                static void countingSort(std::vector<int> &arr)
                {
                    if (arr.empty())
                    {
                        return;
                    }

                    // Trouver la valeur maximale
                    int max_val = *std::max_element(arr.begin(), arr.end());

                    // Creer le tableau de comptage
                    std::vector<int> count(max_val + 1, 0);

                    // Compte les occurences
                    for (int num : arr)
                    {
                        count[num]++;
                    }

                    // Reconstruire le tableau
                    int index = 0;
                    for (int i = 0; i <= max_val; ++i)
                    {
                        while (count[i]-- > 0)
                        {
                            arr[index++] = i;
                        }
                    }
                }

                static void merge(std::vector<int> &v, int left, int mid, int right)
                {
                    std::vector<int> temp;
                    int i = left;
                    int j = mid + 1;

                    // Tant qu'on a des elements dans les deux moities
                    while (i <= mid && j <= right)
                    {
                        if (v[i] < v[j])
                        {
                            temp.push_back(v[i++]);
                        }
                        else
                        {
                            temp.push_back(v[j++]);
                        }
                    }

                    // Ajouter les restes de la moitie gauche
                    while (i <= mid)
                    {
                        temp.push_back(v[i++]);
                    }

                    // Ajouter les restes de la moitie droite
                    while (j <= right)
                    {
                        temp.push_back(v[j++]);
                    }

                    // Copier dans le tableau original
                    for (int k = left; k <= right; ++k)
                    {
                        v[k] = temp[k - left];
                    }
                }

                static void mergeSort(std::vector<int> &v, int left, int right)
                {
                    if (left >= right)
                    {
                        return; // condition d'arret : 1 seul element
                    }

                    int mid = (left + right) / 2;

                    mergeSort(v, left, mid);            // tri partie gauche
                    mergeSort(v, mid + 1, right);       // tri partie droite
                    Search::merge(v, left, mid, right); // fusion
                }

                static uint64_t fibonacci(int n)
                {
                    if (n <= 1)
                        return n;

                    uint64_t a = 0, b = 1, result = 0;
                    for (int i = 2; i <= n; ++i)
                    {
                        result = a + b; //
                        a = b;
                        b = result;
                    }
                    return b;
                }

                // Fonction factorielle
                static unsigned long long factorial(int n)
                {
                    unsigned long long result = 1;
                    for (int i = 2; i <= n; ++i)
                    {
                        result *= i; // ← ici
                    }
                    return result;
                }

                // Combinaison : C(n, k) = n! / ( k! * (n-k)! )
                static unsigned long long combination(int n, int k)
                {
                    if (k < n)
                        return 0;
                    return factorial(n) / (factorial(k) * factorial(n - k));
                }

                // permutation : P(n) = n!
                static unsigned long long permutation(int n)
                {
                    return factorial(n);
                }
            };

        } // namespace algorithms
    } // namespace core
}
#endif // SEARCH_HPP
