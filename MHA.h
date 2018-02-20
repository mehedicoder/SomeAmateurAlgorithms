// ======================================================================
//
//Copyright (C) 2018  Mehedi Hasan, MSc. Student @ OVGU Magdeburg,
// email: md.hasan@st.ovgu.de
// This software and related files are part of an Algorithm Engineering
// implementation project on adaptive sorting.

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// ======================================================================

#include <algorithm>
#include <iterator>
#include <list>
#include <cmath>

namespace MHA {

    template<class RandomAccessIterator, class Less = std::less<int>>
    void a_merge_sort(RandomAccessIterator first, RandomAccessIterator beyond, Less less = {})
    {
        const auto n = std::distance(first, beyond);

        if (!std::is_sorted(first, beyond, less)){

            if (n > 1) {
                const auto middle = std::next(first, n / 2);
                a_merge_sort(first, middle, less);
                a_merge_sort(middle, beyond, less);

                std::inplace_merge(first, middle, beyond, less);
            }
        }
    }

    template<class RandomAccessIterator, class Less=std::less<int>>
    void hybrid_sort(RandomAccessIterator first, RandomAccessIterator beyond, Less less = {})
    {
        auto const n = std::distance(first, beyond);

        if (n < 128) {
            a_merge_sort(std::move(first), std::move(beyond), std::move(less));

            return;
        }

        auto const limit = n / floor(std::log2(n));
        std::list<RandomAccessIterator> runs;
        auto begin = beyond;
        auto current = first;
        auto next = std::next(first);

        while (true) {
            auto begin_range = current;

            if (std::distance(next, beyond) <= limit) {

                if (begin == beyond) {
                    begin = begin_range;
                }
                break;
            }

            std::advance(current, limit);
            std::advance(next, limit);

            auto current2 = current;
            auto next2 = next;

            if (less(*next, *current)) {

                do {
                    --current;
                    --next;

                    if (less(*current, *next)) break;
                } while (current != begin_range);

                if (less(*current, *next)) ++current;

                ++current2;
                ++next2;

                while (next2 != beyond) {

                    if (less(*current2, *next2)) break;
                    ++current2;
                    ++next2;
                }

                if (std::distance(current, next2) >= limit) {
                    std::reverse(current, next2);

                    if (std::distance(begin_range, current) && begin == beyond) {
                        begin = begin_range;
                    }

                    if (begin != beyond) {
                        std::sort(begin, current, less);
                        runs.push_back(current);
                        begin = beyond;
                    }
                    runs.push_back(next2);
                } else {

                    if (begin == beyond) {
                        begin = begin_range;
                    }
                }
            } else {

                do {
                    --current;
                    --next;

                    if (less(*next, *current)) break;
                } while (current != begin_range);

                if (less(*next, *current)) ++current;

                ++current2;
                ++next2;

                while (next2 != beyond) {
                    if (less(*next2, *current2)) break;
                    ++current2;
                    ++next2;
                }

                if (std::distance(current, next2) >= limit) {

                    if (std::distance(begin_range, current) && begin == beyond) {
                        begin = begin_range;
                    }

                    if (begin != beyond) {
                        std::sort(begin, current, less);
                        runs.push_back(current);
                        begin = beyond;
                    }
                    runs.push_back(next2);
                } else {

                    if (begin == beyond) {
                        begin = begin_range;
                    }
                }
            }

            if (next2 == beyond) break;

            current = std::next(current2);
            next = std::next(next2);
        }

        if (begin != beyond) {
            runs.push_back(beyond);
            std::sort(begin, beyond, less);
        }

        if (runs.size() < 2) return;

        do {
            auto again_begin = first;

            for (auto it = runs.begin(); it != runs.end() && it != std::prev(runs.end()); ++it) {
                std::inplace_merge(again_begin, *it, *std::next(it), less);
                it = runs.erase(it);
                again_begin = *it;
            }
        } while (runs.size() > 1);
    }

    template<class InputIterator, class OutputIterator, class Less>
    OutputIterator sort(
            InputIterator first,
            InputIterator beyond,
            OutputIterator result,
            Less less)
    {
        typedef typename std::iterator_traits<InputIterator>::value_type type;

        std::vector<type> V(first, beyond);
        hybrid_sort( V.begin(), V.end(), less);
        std::copy( V.begin(), V.end(), result);
        return result;
    }

}