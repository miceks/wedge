#pragma once

 // Complex numbers
namespace wg::algebras::complex
{
    // Blades used as template parameters of multivector in algebra
    using re = blade<0, 0,   0, float>;
    using im = blade<0, 0b1, 0, float>;
    

    // Named constant values
    inline constexpr mvec<im> i = 1.0f;


    // Multivector aliases
    using complex = mvec<re, im>;


    // Literals
    constexpr auto operator "" _i(long double val)        { return mvec<im>{val}; }
    constexpr auto operator "" _i(unsigned long long val) { return mvec<im>{val}; }
}