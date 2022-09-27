#pragma once

namespace wg::impl
{

    template <std::unsigned_integral B>
    constexpr auto bit_and(B const b1, B const b2) -> B
    {
        return b1 & b2;
    }

    template <std::unsigned_integral B>
    constexpr auto bit_or(B const b1, B const b2) -> B
    {
        return b1 | b2;
    }

    template <std::unsigned_integral B>
    constexpr auto bit_xor(B const b1, B const b2) -> B
    {
        return b1 ^ b2;
    }

    // Helper alias
    template <std::size_t I, typename M>
    using get_t = typename std::tuple_element<I, typename M::blades>::type;

} // namespace wg::impl