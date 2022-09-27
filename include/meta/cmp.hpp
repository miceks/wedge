#pragma once

namespace wg::impl
{
    // Get relative order of two blades (1 if B2 > B1, 0 if B2 == B1, -1 if B2 < B1)
    template <typename B1, typename B2>
    struct cmp
    {
      private:
        static constexpr auto c1 = std::tie(B1::grade, B1::zer, B1::neg, B1::pos);
        static constexpr auto c2 = std::tie(B2::grade, B2::zer, B2::neg, B2::pos);

      public:
        static constexpr int value = (c1 > c2) ?  1 :
                                     (c1 < c2) ? -1 : 0;
    };

} // namespace wg::impl