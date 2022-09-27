#pragma once

namespace wg::impl
{
    // Get the type of the geometric product of two multivectors M1 and M2.
    template <typename, typename>
    struct geometric_product;

    namespace geometric_product_mvec_mvec_impl
    {
        template <typename M1, typename M2, typename R>
        struct mult_step;

        // General multiplication step. Multiply current head of M1 with M2 and add to running total.
        template <typename H, typename...T,
                  typename M2, typename... Bx>
        struct mult_step<mvec<H, T...>, M2, mvec<Bx...>>
            : public mult_step<mvec<T...>, M2, 
                typename impl::sum<typename impl::geometric_product<H, M2>::type, mvec<Bx...>>::type>
        {
        };

        // Terminating specialization: all blades of M1 multiplied with M2.
        template <typename M2, typename R>
        struct mult_step<mvec<>, M2, R>
        {
            using type = R;
        };

    } // namespace geometric_product_mvec_mvec_impl


    template <typename... Bx1, typename... Bx2>
    struct geometric_product<mvec<Bx1...>, mvec<Bx2...>>
        : public geometric_product_mvec_mvec_impl::mult_step<mvec<Bx1...>, mvec<Bx2...>, mvec<>>
    {
    };


} // namespace wg::impl