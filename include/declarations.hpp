#pragma once


/* ------------ Forward declarations ------------ */

namespace wg
{
    template <typename...>
    class mvec;

    template <unsigned, unsigned, unsigned, typename>
    class blade;

    template <std::size_t, typename E>
    constexpr auto get_blade(E const&);
}

namespace wg::impl
{
    template <std::size_t, typename E>
    constexpr auto get_blade(E const&);
}