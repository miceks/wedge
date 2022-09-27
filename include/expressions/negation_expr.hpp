#pragma once 

namespace wg::impl
{
    // Expression produced by negating an expression
    template <typename E>
    class negation_expr
    {
        E const& m_expr;
        
      public:
        using result_type = E::result_type;

        constexpr negation_expr(E const& expr)
            : m_expr(expr)
        {
        }

        // Produce the blade at index I
        template <std::size_t I>
        friend constexpr auto get_blade(negation_expr<E> const& expr)
        {
            return -get_blade<I>(expr.m_expr);
        }
    };

} // namespace wg::impl


namespace wg
{
    // Negation of expression
    template <impl::expression E>
    constexpr auto operator - (E const& expr)
    {
        return impl::negation_expr<E>(expr);
    }

} // namespace wg