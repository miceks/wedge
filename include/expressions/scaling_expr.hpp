#pragma once 

namespace wg::impl
{
    // Expression produced by the * operator of a scalar and an expression.
    template <typename E>
    class scaling_expr
    {
        E::result_type::value_type const m_scalar;
        E const& m_expr;

      public:
        using result_type = E::result_type;

        template <typename S>
        constexpr scaling_expr(S const scalar, E const& expr)
            : m_scalar(static_cast<result_type::value_type>(scalar)),
              m_expr(expr)
        {
        }

        // Produce the blade at index I
        template <std::size_t I>
        friend constexpr auto get_blade(scaling_expr<E> const& expr)
        {
            return get_blade<I>(expr.m_expr) * expr.m_scalar;
        }
    };

} // namespace wg::impl


namespace wg
{
    // Product of scalar and expression
    template <typename S, impl::expression E>
        requires(std::integral<S> || std::floating_point<S>)
    constexpr auto operator * (S const scalar, E const& expr)
    {
        return impl::scaling_expr<E>(scalar, expr);
    }

    // Product of expression and scalar
    template <impl::expression E, typename S>
        requires(std::integral<S> || std::floating_point<S>)
    constexpr auto operator * (E const& expr, S const scalar)
    {
        return impl::scaling_expr<E>(scalar, expr);
    }

} // namespace wg