#pragma once

namespace wg::impl
{
    // Get type signature of blade-blade geometric product.
    template <typename, typename>
    struct geometric_product;

    namespace geometric_product_blade_blade_impl
    {
        template <unsigned P, unsigned Q, unsigned R, bool zero, typename T>
        struct signature;

        // Zero bases squared, mark as discarded.
        template <unsigned P, unsigned Q, unsigned R, typename T>
        struct signature<P, Q, R, true, T>
        {
            using type = blade<0u, 0u, ~0u, T>;
        };

        // General case, squared positive and negative bases removed.
        template <unsigned P, unsigned Q, unsigned R, typename T>
        struct signature<P, Q, R, false, T>
        {
            using type = blade<P, Q, R, T>;
        };

    } // namespace geometric_product_blade_blade_impl

 
    template <unsigned P1, unsigned Q1, unsigned R1, typename T1,
              unsigned P2, unsigned Q2, unsigned R2, typename T2>
    struct geometric_product<blade<P1, Q1, R1, T1>, blade<P2, Q2, R2, T2>>
        : public geometric_product_blade_blade_impl::signature<bit_xor(P1, P2),
                                                               bit_xor(Q1, Q2),
                                                               bit_or(R1, R2),
                                                               bit_and(R1, R2),
                                                               std::common_type_t<T1, T2>>
    {
    };

} // namespace wg::impl