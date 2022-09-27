#pragma once

// 3D geometric algebra
namespace wg::algebras::ga3d
{
    // Blades used as template parameters of multivector in algebra
    using scalar = blade<0b000, 0, 0, float>;
    using e1     = blade<0b001, 0, 0, float>;
    using e2     = blade<0b010, 0, 0, float>;
    using e3     = blade<0b100, 0, 0, float>;
    using e12    = blade<0b011, 0, 0, float>;
    using e13    = blade<0b101, 0, 0, float>;
    using e23    = blade<0b110, 0, 0, float>;
    using e123   = blade<0b111, 0, 0, float>;
    

    // Named constant values
    inline constexpr mvec<e123> I = 1.0f; 
    

    // Multivector aliases
    using vec   = mvec<e1, e2, e3>;
    using rotor = mvec<e12, e13, e23>;

    
    // Literals
    constexpr auto operator "" _e1  (long double val)        { return mvec<e1  >{val}; }
    constexpr auto operator "" _e1  (unsigned long long val) { return mvec<e1  >{val}; }

    constexpr auto operator "" _e2  (long double val)        { return mvec<e2  >{val}; }
    constexpr auto operator "" _e2  (unsigned long long val) { return mvec<e2  >{val}; }

    constexpr auto operator "" _e3  (long double val)        { return mvec<e3  >{val}; }
    constexpr auto operator "" _e3  (unsigned long long val) { return mvec<e3  >{val}; }

    constexpr auto operator "" _e12 (long double val)        { return mvec<e12 >{val}; }
    constexpr auto operator "" _e12 (unsigned long long val) { return mvec<e12 >{val}; }

    constexpr auto operator "" _e13 (long double val)        { return mvec<e13 >{val}; }
    constexpr auto operator "" _e13 (unsigned long long val) { return mvec<e13 >{val}; }

    constexpr auto operator "" _e23 (long double val)        { return mvec<e23 >{val}; }
    constexpr auto operator "" _e23 (unsigned long long val) { return mvec<e23 >{val}; }

    constexpr auto operator "" _e123(long double val)        { return mvec<e123>{val}; }
    constexpr auto operator "" _e123(unsigned long long val) { return mvec<e123>{val}; }
}