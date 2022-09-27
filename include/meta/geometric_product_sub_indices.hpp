#pragma once

namespace wg::impl
{
    namespace geometric_product_sub_indices_impl
    {
        template <typename B, typename M1, typename M2,
                  std::size_t I1, std::size_t I2, 
                  std::size_t S1, std::size_t S2,
                  bool Done1, bool Done2,
                  typename Seq1, typename Seq2>
        struct compare_step;

        template <typename B, typename M1, typename M2,
                  std::size_t I1, std::size_t I2,
                  std::size_t S1, std::size_t S2,
                  typename Seq1, typename Seq2, int O>
        struct advance_step;


        // General compare step
        template <typename B, typename M1, typename M2, 
                  std::size_t I1, std::size_t I2,
                  std::size_t S1, std::size_t S2,
                  typename Seq1, typename Seq2>
        struct compare_step<B, M1, M2, I1, I2, S1, S2, false, false, Seq1, Seq2>
            : public advance_step<B, M1, M2, I1, I2, S1, S2, Seq1, Seq2,
                                  cmp<B, typename impl::geometric_product<get_t<I1, M1>, 
                                                                          get_t<I2, M2>>::type>::value>
        {
        };

        // I2 reached end sentinel S2. Increment I1, reset I2 and instantiate new compare step.
        template <typename B, typename M1, typename M2, 
                  std::size_t I1, std::size_t I2,
                  std::size_t S1, std::size_t S2,
                  typename Seq1, typename Seq2>
        struct compare_step<B, M1, M2, I1, I2, S1, S2, false, true, Seq1, Seq2>
            : public compare_step<B, M1, M2, I1 + 1, 0, S1, S2, I1 + 1 == S1, false, Seq1, Seq2>
        {
        };

        // Terminating specialization: I2 reached end sentinel S2.
        template <typename B, typename M1, typename M2, 
                  std::size_t I1, std::size_t I2,
                  std::size_t S1, std::size_t S2,
                  bool Done2,
                  typename Seq1, typename Seq2>
        struct compare_step<B, M1, M2, I1, I2, S1, S2, true, Done2, Seq1, Seq2>
        {
            using Is1 = Seq1;
            using Is2 = Seq2;
        };

        // General advance step.
        template <typename B, typename M1, typename M2, 
                  std::size_t I1, std::size_t I2,
                  std::size_t S1, std::size_t S2,
                  std::size_t... Ix1, std::size_t... Ix2, int O>
        struct advance_step<B, M1, M2, I1, I2, S1, S2, std::index_sequence<Ix1...>, std::index_sequence<Ix2...>, O>
            : public compare_step<B, M1, M2, I1, I2 + 1, S1, S2, 
                                  I1 == S1, I2 + 1  == S2,
                                  typename std::index_sequence<Ix1...>, 
                                  typename std::index_sequence<Ix2...>>
        {
        };

        // Valid product found at index I1 and I2, append to index sequences and continue.
        template <typename B, typename M1, typename M2, 
                  std::size_t I1, std::size_t I2, 
                  std::size_t S1, std::size_t S2,
                  std::size_t... Ix1, std::size_t... Ix2>
        struct advance_step<B, M1, M2, I1, I2, S1, S2, std::index_sequence<Ix1...>, std::index_sequence<Ix2...>, 0>
            : public compare_step<B, M1, M2, I1, I2 + 1, S1, S2,
                                  I1 == S1, I2 + 1  == S2,
                                  typename std::index_sequence<I1, Ix1...>,
                                  typename std::index_sequence<I2, Ix2...>>
        {
        };

    } // namespace geometric_product_sub_indices_impl


    // Recover the indices of M1 and M2 whose blades, when multiplied, yield
    // the blade at index I in M0. Result represented by two index sequences.
    template <std::size_t I, typename M0, typename M1, typename M2>
    struct geometric_product_sub_indices
        : public geometric_product_sub_indices_impl::compare_step<get_t<I, M0>, M1, M2,
                                                                  0, 0, M1::size, M2::size,
                                                                  M1::size == 0, M2::size == 0,
                                                                  std::index_sequence<>, 
                                                                  std::index_sequence<>>
    {
    };
 
} // namespace wg::impl