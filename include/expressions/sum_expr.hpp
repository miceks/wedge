#pragma once

namespace wg::impl
{
    // Expression produced by the + operator
    template <typename LHS, typename RHS>
    class sum_expr
    {
        LHS const& m_lhs;
        RHS const& m_rhs;

      public:
        using result_type 
            = wg::impl::sum<typename LHS::result_type,
                            typename RHS::result_type>::type;

        constexpr sum_expr(LHS const& lhs, RHS const& rhs)
            : m_lhs(lhs), m_rhs(rhs)
        {
        }

        // Produce the blade at index I
        template <std::size_t I>
        friend constexpr auto get_blade(sum_expr<LHS, RHS> const& expr)
        {
            // Find which indices in sub expressions result in index I
            using index_map 
                = impl::sum_sub_indices<I, result_type, 
                                           typename LHS::result_type,
                                           typename RHS::result_type>;

            // Only rhs contributes a term.
            if constexpr(index_map::I1 == LHS::result_type::size)
            {
                return get_blade<index_map::I2>(expr.m_rhs);
            }

            // Only lhs contributes a term.
            else if constexpr(index_map::I2 == RHS::result_type::size)
            {
                return get_blade<index_map::I1>(expr.m_lhs);
            }
            
            // Both rhs and lhs contribute a term each.
            else
            {
                return get_blade<index_map::I1>(expr.m_lhs)
                     + get_blade<index_map::I2>(expr.m_rhs);
            }
        }
    };

} // namespace wg::impl


namespace wg
{
    // Sum of two expressions
    template <impl::expression LHS, impl::expression RHS>
    constexpr auto operator + (LHS const& lhs, RHS const& rhs)
    {
        return impl::sum_expr<LHS, RHS>(lhs, rhs);
    }

    // Sum of scalar and expression
    template <impl::expression RHS>
    constexpr auto operator + (mvec<blade<0,0,0>> const& lhs, RHS const& rhs)
    {
        return impl::sum_expr(lhs, rhs);
    }

    // Sum of expression and scalar
    template <impl::expression LHS>
    constexpr auto operator + (LHS const& lhs, mvec<blade<0,0,0>> const& rhs)
    {
        return impl::sum_expr(lhs, rhs);
    }

} // namespace wg