#pragma once

namespace wg::impl
{
    // Expression produced by the * operator of two expressions
    template <typename LHS, typename RHS>
    class geometric_prod_expr
    {
        LHS const& m_lhs;
        RHS const& m_rhs;

      public:
        using result_type = geometric_product<typename LHS::result_type,
                                              typename RHS::result_type>::type;

        constexpr geometric_prod_expr(LHS const& lhs, RHS const& rhs)
            : m_lhs(lhs), m_rhs(rhs)
        {
        }

        // Produce the blade at index I in result type
        template <std::size_t I>
        friend constexpr auto get_blade(geometric_prod_expr<LHS, RHS> const& expr)
        {
            // Find which index pairs in sub expressions multiply to index I in result type
            using index_map = geometric_product_sub_indices<I, result_type,
                                                            typename LHS::result_type,
                                                            typename RHS::result_type>;

            // Return sum of relevant blade products
            return [&]<std::size_t... Ix1, std::size_t... Ix2>
                   (std::index_sequence<Ix1...>, std::index_sequence<Ix2...>)
                   {
                       return ((get_blade<Ix1>(expr.m_lhs) 
                              * get_blade<Ix2>(expr.m_rhs)) + ...); 
                   }
                   (typename index_map::Is1{}, typename index_map::Is2{});
        }
    };

} // namespace wg::impl


namespace wg
{
    // Geometric product of two expressions
    template <impl::expression LHS, impl::expression RHS>
    constexpr auto operator * (LHS const& lhs, RHS const& rhs)
    {
        return impl::geometric_prod_expr<LHS, RHS>(lhs, rhs);
    }

} // namespace wg