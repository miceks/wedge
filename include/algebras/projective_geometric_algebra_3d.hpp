#pragma once

// 3D projective geometric algebra (aka plane based geometric algebra)
namespace wg::algebras::pga3d
{
    // Blades used as template parameters of multivector in algebra
    using scalar = blade<0    , 0, 0  , float>;
    using e0     = blade<0    , 0, 0b1, float>;
    using e1     = blade<0b001, 0, 0  , float>;
    using e2     = blade<0b010, 0, 0  , float>;
    using e3     = blade<0b100, 0, 0  , float>;
    using e10    = blade<0b001, 0, 0b1, float>;
    using e20    = blade<0b010, 0, 0b1, float>;
    using e30    = blade<0b100, 0, 0b1, float>;
    using e12    = blade<0b011, 0, 0  , float>;
    using e13    = blade<0b101, 0, 0  , float>;
    using e23    = blade<0b110, 0, 0  , float>;
    using e120   = blade<0b011, 0, 0b1, float>;
    using e130   = blade<0b101, 0, 0b1, float>;
    using e230   = blade<0b110, 0, 0b1, float>;
    using e123   = blade<0b111, 0, 0  , float>;
    using e1230  = blade<0b111, 0, 0b1, float>;
    

    // Named constant values
    inline constexpr mvec<e1230> I = 1.0f;
    
    
    // Multivector aliases
    using vec3 = mvec<e1, e2, e3>;
    using vec4 = mvec<e1, e2, e3, e0>;


    // Literals
    constexpr auto operator "" _e0   (long double val)        { return mvec<e0   >{val}; }
    constexpr auto operator "" _e0   (unsigned long long val) { return mvec<e0   >{val}; }

    constexpr auto operator "" _e1   (long double val)        { return mvec<e1   >{val}; }
    constexpr auto operator "" _e1   (unsigned long long val) { return mvec<e1   >{val}; }

    constexpr auto operator "" _e2   (long double val)        { return mvec<e2   >{val}; }
    constexpr auto operator "" _e2   (unsigned long long val) { return mvec<e2   >{val}; }

    constexpr auto operator "" _e3   (long double val)        { return mvec<e3   >{val}; }
    constexpr auto operator "" _e3   (unsigned long long val) { return mvec<e3   >{val}; }

    constexpr auto operator "" _e10  (long double val)        { return mvec<e10  >{val}; }
    constexpr auto operator "" _e10  (unsigned long long val) { return mvec<e10  >{val}; }

    constexpr auto operator "" _e20  (long double val)        { return mvec<e20  >{val}; }
    constexpr auto operator "" _e20  (unsigned long long val) { return mvec<e20  >{val}; }

    constexpr auto operator "" _e30  (long double val)        { return mvec<e30  >{val}; }
    constexpr auto operator "" _e30  (unsigned long long val) { return mvec<e30  >{val}; }

    constexpr auto operator "" _e12  (long double val)        { return mvec<e12  >{val}; }
    constexpr auto operator "" _e12  (unsigned long long val) { return mvec<e12  >{val}; }

    constexpr auto operator "" _e13  (long double val)        { return mvec<e13  >{val}; }
    constexpr auto operator "" _e13  (unsigned long long val) { return mvec<e13  >{val}; }

    constexpr auto operator "" _e23  (long double val)        { return mvec<e23  >{val}; }
    constexpr auto operator "" _e23  (unsigned long long val) { return mvec<e23  >{val}; }

    constexpr auto operator "" _e120 (long double val)        { return mvec<e120 >{val}; }
    constexpr auto operator "" _e120 (unsigned long long val) { return mvec<e120 >{val}; }

    constexpr auto operator "" _e130 (long double val)        { return mvec<e130 >{val}; }
    constexpr auto operator "" _e130 (unsigned long long val) { return mvec<e130 >{val}; }

    constexpr auto operator "" _e230 (long double val)        { return mvec<e230 >{val}; }
    constexpr auto operator "" _e230 (unsigned long long val) { return mvec<e230 >{val}; }

    constexpr auto operator "" _e123 (long double val)        { return mvec<e123 >{val}; }
    constexpr auto operator "" _e123 (unsigned long long val) { return mvec<e123 >{val}; }

    constexpr auto operator "" _e1230(long double val)        { return mvec<e1230>{val}; }
    constexpr auto operator "" _e1230(unsigned long long val) { return mvec<e1230>{val}; }
}