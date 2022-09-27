#pragma once

namespace wg::impl
{
    // Get the type of the geometric product of blade B and multivector M.
    template <typename, typename>
    struct geometric_product;

    namespace geometric_product_blade_mvec_impl
    {
        template <typename B, typename M, typename R>
        struct mult_step;

        // General multiplication step.
        template <typename B,
                  typename H, typename... T,
                  typename R>
        struct mult_step<B, mvec<H, T...>, R>
            : public mult_step<B, mvec<T...>, 
                typename impl::inserted<typename geometric_product<B, H>::type, R>::type>
        {
        };

        // Terminating specialization: multivector exhausted.
        template <typename B, typename R>
        struct mult_step<B, mvec<>, R>
        {
            using type = R;
        };

    } // namespace geometric_product_blade_mvec_impl

    
    template <unsigned P, unsigned Q, unsigned R, typename T, typename... Bx>
    struct geometric_product<blade<P, Q, R, T>, mvec<Bx...>>
        : public geometric_product_blade_mvec_impl::mult_step<blade<P, Q, R, T>, mvec<Bx...>, mvec<>>
    {
    };

}