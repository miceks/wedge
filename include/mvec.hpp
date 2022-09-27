#pragma once

namespace wg
{
    // A multivector contains instances of blades which are part of its template
    // arguments, and can be constructed from an expression (if the expression 
    // have all required blades in its result type) or from values.
    template<typename... Bx>
    class mvec
    {
        std::tuple<Bx...> m_blades;

      public:
        using blades      = std::tuple<Bx...>;
        using result_type = mvec<Bx...>;
        using value_type  = std::common_type<typename Bx::value_type...>::type;

        static constexpr auto size = sizeof...(Bx);

        // Construct from values
        template <typename... Ts>
        constexpr mvec(Ts... values)
            : m_blades(static_cast<value_type>(values)...)
        {
            static_assert(impl::is_ordered<mvec<Bx...>>::value);
        }
        
        // Construct from expression
        template <impl::expression E>
        constexpr mvec(E const& expr) 
            : mvec{ get<Bx>(expr)... }
        {
            static_assert(impl::is_ordered<mvec<Bx...>>::value);
        }

        template <std::size_t I>
        friend constexpr auto get_blade(mvec<Bx...> const& mv)
        {
            return std::get<I>(mv.m_blades);
        }
    };


} // namespace wg