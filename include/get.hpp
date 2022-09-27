#pragma once

// Support for structured bindings
namespace std
{
    using wg::impl::expression;

    template <expression E>
    struct tuple_size<E>
    {
        static constexpr auto value = E::result_type::size;
    };

    template<std::size_t I, expression E>
    struct tuple_element<I, E>
    {
        using type = std::tuple_element_t<I, typename E::result_type::blades>::value_type;
    };

} // namespace std


namespace wg
{
    using impl::expression;

    // Get element value by index
    template <std::size_t I, expression E>
    constexpr auto get(E const& expr) 
        -> E::result_type::value_type
    {
        return get_blade<I>(expr).value();
    }

    // Get element value by type (won't compile if absent)
    template <typename B, expression E>
    constexpr auto get(E const& expr) 
        -> E::result_type::value_type
    {
        return get<impl::index<B, typename E::result_type>::value>(expr);
    }

    // Get several elements by type and return by multivector
    template <typename... Bx, expression E>
        requires(sizeof...(Bx) > 1)
    constexpr auto get(E const& expr) 
        -> mvec<Bx...>
    {
        return { get<Bx>(expr)... };
    }

    // Evaluate entire expression and return result by multivector
    template <expression E>
    constexpr auto eval(E const& expr)
        -> E::result_type
    {
        return { expr };
    }

    // Get all elements of a certain grade by multivector
    template <std::size_t I, expression E>
    constexpr auto grade(E const& expr)
        -> impl::grade<I, typename E::result_type>::type
    {
        return { expr };
    }

} // namespace wg
