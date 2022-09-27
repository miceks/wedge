#pragma once

// 2D projective geometric algebra (aka plane based geometric algebra)
namespace wg::algebras::pga2d
{
    // Blades used as template parameters of multivector in algebra
    using scalar = blade<0   , 0, 0  , float>;
    using e0     = blade<0   , 0, 0b1, float>;
    using e1     = blade<0b01, 0, 0  , float>;
    using e2     = blade<0b10, 0, 0  , float>;
    using e10    = blade<0b01, 0, 0b1, float>;
    using e20    = blade<0b10, 0, 0b1, float>;
    using e12    = blade<0b11, 0, 0  , float>;
    using e120   = blade<0b11, 0, 0b1, float>;
    

    // Named constant values
    inline constexpr mvec<e120> I = 1.0f;
    

    // Multivector aliases
    using vec2 = mvec<e1, e2>;
    using vec3 = mvec<e1, e2, e0>;


    // Literals
    constexpr auto operator "" _e0  (long double val)        { return mvec<e0  >{val}; }
    constexpr auto operator "" _e0  (unsigned long long val) { return mvec<e0  >{val}; }

    constexpr auto operator "" _e1  (long double val)        { return mvec<e1  >{val}; }
    constexpr auto operator "" _e1  (unsigned long long val) { return mvec<e1  >{val}; }

    constexpr auto operator "" _e2  (long double val)        { return mvec<e2  >{val}; }
    constexpr auto operator "" _e2  (unsigned long long val) { return mvec<e2  >{val}; }

    constexpr auto operator "" _e10 (long double val)        { return mvec<e10 >{val}; }
    constexpr auto operator "" _e10 (unsigned long long val) { return mvec<e10 >{val}; }

    constexpr auto operator "" _e20 (long double val)        { return mvec<e20 >{val}; }
    constexpr auto operator "" _e20 (unsigned long long val) { return mvec<e20 >{val}; }

    constexpr auto operator "" _e12 (long double val)        { return mvec<e12 >{val}; }
    constexpr auto operator "" _e12 (unsigned long long val) { return mvec<e12 >{val}; }

    constexpr auto operator "" _e120(long double val)        { return mvec<e120>{val}; }
    constexpr auto operator "" _e120(unsigned long long val) { return mvec<e120>{val}; }
}