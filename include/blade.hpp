#pragma once

namespace wg
{
    // A blade has three bitflags (P, Q, R) as part of its type signature which encode
    // what bases it is comprised of. These bitmasks correspond, respectively, to positive bases
    // (square to 1), negative bases (square to -1) and zero bases (square to 0).
    template <unsigned P, unsigned Q, unsigned R, typename T = float>
    class blade
    {
        T m_value; 
        
        template <typename...> 
        friend class mvec;

        template <unsigned, unsigned, unsigned, typename> 
        friend class blade;

        // Only multivectors (and other blades) can instantiate blades.
        constexpr blade(T const value)
            : m_value(value)
        {
        };

      public:
        using value_type = T;

        static constexpr unsigned pos = P, neg = Q, zer = R;
        static constexpr int grade = std::popcount(pos)
                                   + std::popcount(neg)
                                   + std::popcount(zer);

        constexpr auto value() const
            -> value_type
        {
            return m_value;
        }
        
        // Negation
        [[nodiscard]]
        constexpr auto operator - () const
            -> blade<P, Q, R, T>
        {
            return { -m_value };
        }

        // Homogeneous addition
        constexpr auto operator + (blade<P, Q, R, T> const other) const
            -> blade<P, Q, R, T>
        {
            return { m_value + other.value() };
        }

        // Homogeneous subtraction
        constexpr auto operator - (blade<P, Q, R, T> const other) const
            -> blade<P, Q, R, T>
        {
            return { m_value - other.value() };
        }

        // Scalar multiplication
        constexpr auto operator * (T const scalar) const
            -> blade<P, Q, R, T>
        {
            return { scalar * m_value };
        }

        // Reverse order of bases (amounts to possible sign flip)
        [[nodiscard]]
        constexpr auto operator ~ () const
            -> blade<P, Q, R, T>
        {
            constexpr T sign = (reverse_flips() % 2)
                                    ? T{-1} : T{1};

            return { sign * m_value };
        }

        // Geometric product
        template <unsigned p, unsigned q, unsigned r, typename t>
        constexpr auto operator * (blade<p, q, r, t> const other) const
            -> impl::geometric_product<blade<P, Q, R, T>, blade<p, q, r, t>>::type
        {
            constexpr T sign = ((commute_flips(p, q, r) + std::popcount(Q & q)) % 2)
                                    ? T{-1} : T{1};

            constexpr T zero = (R & r) ? T{0} : T{1};

            return { sign * zero * m_value * other.value() };
        }


      private:
        // Get the number of commutations (sign flips) needed to put the
        // product of two blades in standard order (pos neg zer)
        [[nodiscard]]
        static consteval auto commute_flips(unsigned p, unsigned q, unsigned r) -> int
        {
            int flips = 0;

            flips += (std::popcount(p) * std::popcount(R));   // (P Q R) (p q r) -> (P Q p R) (q r)   Commute all p bases through R
            flips += (std::popcount(p) * std::popcount(Q));   //                 -> (P p Q R) (q r)   Commute all p bases through Q
            for(auto mask = ~0u; p; )                         //                 -> (p Q R) (q r)     Commute individual p bases through P
            {
                mask <<= (std::countr_zero(p) + 1);           // Cover all bases of higher order than the current base in 2
                flips += std::popcount(P & mask);             // Flip for every base in 1 of higher order than the current base in 2
                p    >>= (std::countr_zero(p) + 1);           // Advance to next base in 2
            }

            flips += (std::popcount(q) * std::popcount(R));   // (p Q R) (q r) -> (p Q q R) (r)   Commute all q bases through R
            for(auto mask = ~0u; q; )                         //               -> (p n R) (r)     Commute individual q bases through Q
            {
                mask <<= (std::countr_zero(q) + 1);
                flips += std::popcount(Q & mask);
                q    >>= (std::countr_zero(q) + 1);
            }

            for(auto mask = ~0u; r; )                         // (p q R) (r) -> (p q r)   Commute individual r bases through R
            {
                mask <<= (std::countr_zero(r) + 1);
                flips += std::popcount(R & mask);
                r    >>= (std::countr_zero(r) + 1);
            }

            return flips;
        }

        // Get the number of commutations (sign flips) needed
        // to reverse the order of the bases
        [[nodiscard]]
        static consteval auto reverse_flips() -> int
        {
            return (grade - 1) * grade / 2;
        }

    };


} // namespace wg