#pragma once

namespace wg::impl
{
    // Expression produced by basis reversal operator ~ of expression
    template <typename E>
    class reverse_expr
    {
        E const& m_expr;
        
      public:
        using result_type = E::result_type;

        constexpr reverse_expr(E const& expr)
            : m_expr(expr)
        {
        }

        // Produce the blade at index I
        template <std::size_t I>
        friend constexpr auto get_blade(reverse_expr<E> const& expr)
        {
            return ~get_blade<I>(expr.m_expr);
        }
    };

} // namespace wg::impl


namespace wg
{
    // Base order reversal of expression
    template <impl::expression E>
    constexpr auto operator ~ (E const& expr)
    {
        return impl::reverse_expr<E>(expr);
    }

} // namespace wg