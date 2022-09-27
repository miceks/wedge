#pragma once

namespace wg::impl
{
    // Recover the indices of M1 and M2 that resulted in index I in M0, where M0
    // is the sum (or difference) of M1 and M2. If M1 or M2 did not contribute
    // to the relevant index, their sub index equal their size.
    template <std::size_t I, typename M0, typename M1, typename M2>
    struct sum_sub_indices
    {
        static constexpr auto I1 
            = index<std::tuple_element_t<I, typename M0::blades>, M1>::value;
        static constexpr auto I2 
            = index<std::tuple_element_t<I, typename M0::blades>, M2>::value;
    };

} // namespace wg::impl