#pragma once

namespace wg::impl
{
    namespace inserted_impl
    {
        template <typename M1, typename M2, typename B>
        struct compare_step;

        template <typename M1, typename M2, typename B, int O>
        struct append_step;

        // General compare step, decide if blade ranks higher than (+1),
        // lower than (-1) or equal to (0) current head.
        template <typename H, typename... T,
                  typename M2, typename B>
        struct compare_step<mvec<H, T...>, M2, B>
            : public append_step<mvec<H, T...>, M2, B, cmp<B, H>::value>
        {
        };

        // General append step, blade belongs further up. Append current head.
        template <typename H, typename... T,
                  typename... R, typename B>
        struct append_step<mvec<H, T...>, mvec<R...>, B, 1>
            : public compare_step<mvec<T...>, mvec<R..., H>, B>
        {
        };

        // Terminating specialization: blade ranked lower than current head.
        template <typename H, typename... T,
                  typename... R, typename B>
        struct append_step<mvec<H, T...>, mvec<R...>, B, -1>
        {
            using type = mvec<R..., B, H, T...>;
        };

        // Terminating specialization: blade ranked equal to current head.
        template <typename H, typename... T,
                  typename... R, typename B>
        struct append_step<mvec<H, T...>, mvec<R...>, B, 0>
        {
            using type = mvec<R..., B, T...>;
        };

        // Terminating specialization: reached end of multivector.
        template <typename... R, typename B>
        struct compare_step<mvec<>, mvec<R...>, B>
        {
            using type = mvec<R..., B>;
        };

    } // namespace inserted_impl


    // Blade B inserted in multivector M.
    template <typename B, typename M>
    struct inserted : public inserted_impl::compare_step<M, mvec<>, B>
    {
    };


} // namespace wg::impl