#pragma once

namespace wg::impl
{
    namespace is_ordered_impl
    {
        template <typename M>
        struct compare_step;

        template <typename M, int O>
        struct advance_step;

        // General compare step.
        template <typename H1, typename H2, typename... T>
        struct compare_step<mvec<H1, H2, T...>>
            : public advance_step<mvec<H1, H2, T...>, cmp<H1, H2>::value>
        {
        };

        // General Advance step.
        template <typename H1, typename H2, typename... T, int O>
        struct advance_step<mvec<H1, H2, T...>, O>
            : public compare_step<mvec<H2, T...>>
        {
        };

        // Terminating specialization: not ordered.
        template <typename H1, typename H2, typename... T>
        struct advance_step<mvec<H1, H2, T...>, 1> : std::false_type
        {
        };

        // Terminating specialization: multivector exhausted
        template <typename H1>
        struct compare_step<mvec<H1>> : std::true_type
        {
        };

    } // namespace is_ordered_impl


    // Holds true value if multivector M is ordered, false otherwise.
    template <typename M>
    struct is_ordered : public is_ordered_impl::compare_step<M>
    {
    };

} // namespace wg::impl