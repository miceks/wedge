#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <array>

namespace wg
{
    // Pretty print blade.
    template <unsigned P, unsigned Q, unsigned R>
    std::ostream& operator << (std::ostream& os, blade<P, Q, R> const& blade)
    {
        os << std::setprecision(3) << blade.value() << ' ';

        auto print_bases = [&os](unsigned signature, std::array<std::string, 8> bases)
        {
            auto mask = 1u;
            for(int i = 0; i < 8; ++i, mask <<= 1)
                if(signature & mask) os << bases[i];
        };

        // Check if blade is marked as discarded (squared zero base)
        if(R == ~0u) return os << "--";

        print_bases(P, {"e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8"});
        print_bases(Q, {"i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8"});
        print_bases(R, {"o1", "o2", "o3", "o4", "o5", "o6", "o7", "o8"});

        return os;
    }

    // Pretty print multivector.
    template <typename... Bx>
    std::ostream& operator << (std::ostream& os, mvec<Bx...> const& mv)
    {
        os << "{ ";

        [&] <std::size_t... I>
        (std::index_sequence<I...>)
        {
            ((os << (I == 0 ? "" : ",  ") << get_blade<I>(mv)), ...);
        }
        (std::make_index_sequence<sizeof...(Bx)>{});

        return os << " }";
    }
}