#pragma once

namespace wg::impl
{
    // The union of two ordered multivectors
    template <typename M1, typename M2>
    struct sum;

    // Insert head of M1 in M2
    template <typename H, typename... T,
              typename M2>
    struct sum<mvec<H, T...>, M2>
        : public sum<mvec<T...>, typename inserted<H, M2>::type>
    {
    };

    // Terminating specialization: M1 exhausted
    template <typename M2>
    struct sum<mvec<>, M2>
    {
        using type = M2;
    };

} // namespace wg::impl