#pragma once 

namespace wg::impl
{
    namespace grade_impl
    {
        template <std::size_t G, typename M, typename R>
        struct compare_step;

        template <std::size_t G, bool Inc, typename M, typename R>
        struct advance_step;

        template <std::size_t G, typename H, typename... T, typename R>
        struct compare_step<G, mvec<H, T...>, R>
            : public advance_step<G, H::grade == G, mvec<H, T...>, R>
        {
        };

        template <std::size_t G, typename H, typename... T1, typename... T2>
        struct advance_step<G, true, mvec<H, T1...>, mvec<T2...>>
            : public compare_step<G, mvec<T1...>, mvec<T2..., H>>
        {
        };

        template <std::size_t G, typename H, typename... T1, typename... T2>
        struct advance_step<G, false, mvec<H, T1...>, mvec<T2...>>
            : public compare_step<G, mvec<T1...>, mvec<T2...>>
        {
        };

        template <std::size_t G, typename R>
        struct compare_step<G, mvec<>, R>
        {
            using type = R;
        };

    } // namespace grade_impl


    // Get all elements in M of grade G
    template <std::size_t G, typename M>
    struct grade : public grade_impl::compare_step<G, M, mvec<>>
    {
    };
    
} // namespace wg::impl