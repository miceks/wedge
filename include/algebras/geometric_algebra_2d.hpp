#pragma once

// 2D geometric algebra
namespace wg::algebras::ga2d
{
    // Blades used as template parameters of multivector in algebra
    using scalar  = blade<0b00, 0, 0, float>;
    using e1      = blade<0b01, 0, 0, float>;
    using e2      = blade<0b10, 0, 0, float>;
    using e12     = blade<0b11, 0, 0, float>;
    

    // Named constant values
    inline constexpr mvec<e12> I = 1.0f;
    

    // Multivector aliases
    using vec = mvec<e1, e2>;

    // Literals
    constexpr auto operator "" _e1 (long double val)        { return mvec<e1 >{val}; }
    constexpr auto operator "" _e1 (unsigned long long val) { return mvec<e1 >{val}; }

    constexpr auto operator "" _e2 (long double val)        { return mvec<e2 >{val}; }
    constexpr auto operator "" _e2 (unsigned long long val) { return mvec<e2 >{val}; }

    constexpr auto operator "" _e12(long double val)        { return mvec<e12>{val}; }
    constexpr auto operator "" _e12(unsigned long long val) { return mvec<e12>{val}; }

    template <typename E>
    concept ga2d = impl::restricted_expression<0b11, 0, 0, E>;
}