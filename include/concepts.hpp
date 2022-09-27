#pragma once

namespace wg::impl
{
    // An expression is any type with a result type, which includes multivectors.
    template <typename E>
    concept expression = requires(E)
    {
        typename E::result_type;
    };

    // Blade restricted to include only a specific set of bases.
    template <unsigned P, unsigned Q, unsigned R, typename B>
    concept restricted_blade = B::pos <= P && B::neg <= Q && B::zer <= R;

    // Expression where each blade in the result type is restricted.
    template <unsigned P, unsigned Q, unsigned R, typename E>
    concept restricted_expression =
        [] <std::size_t... I>
        (std::index_sequence<I...>)
        {
            return (restricted_blade<P, Q, R, get_t<I, typename E::result_type>> && ...);
        }
        (std::make_index_sequence<E::result_type::size>{});
}