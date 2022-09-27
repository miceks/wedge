#pragma once

namespace wg::impl
{
    namespace index_impl
    {
        template <typename B, typename M, 
                  std::size_t I>
        struct compare_step;

        template <typename B, typename M, 
                  std::size_t I, int O>
        struct advance_step;

        // General compare step.
        template <typename B, typename H, typename... T, 
                  std::size_t I>
        struct compare_step<B, mvec<H, T...>, I>
            : public advance_step<B, mvec<H, T...>, I, cmp<B, H>::value>
        {
        };

        // General advance step.
        template <typename B, typename H, typename... T, 
                  std::size_t I, int O>
        struct advance_step<B, mvec<H, T...>, I, O>
            : public compare_step<B, mvec<T...>, I + 1>
        {
        };

        // Terminating specialization: type matched at index I.
        template <typename B, typename H, typename... T, 
                  std::size_t I>
        struct advance_step<B, mvec<H, T...>, I, 0>
        {
            static constexpr auto value = I;
        };

        // Terminating specialization: multivector exhausted.
        template <typename B,std::size_t I>
        struct compare_step<B, mvec<>, I>
        {
            static constexpr auto value = I;
        };

    } // namespace index_impl


    // Get index of blade B in M, or size of M if B is not contained.
    template <typename B, typename M>
    struct index : public index_impl::compare_step<B, M, 0>
    {
    };

} // namespace wg::impl