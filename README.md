# Wedge

Wedge is a header-only, constexpr-enabled, geometric algebra library for C++20 that uses template 
metaprogramming and expression templates. It is a personal experiment intended to explore 
computer representations of generic geometric algebras which allow for efficient operations 
on their elements.


## Overview

The central component used to model the elements of an algebra is the multivector ('mvec') 
class template, which is a tuple-like container storing instances of blades, which are in 
turn the outer (wedge) product of arbitrary basis vectors, the signature of which are specified 
through template bitflags.

```cpp
#include <iostream>
#include "wedge.hpp"

using namespace wg;

int main()
{
    // Blades represent the outer (wedge) product of basis vectors
    using e1 = blade<0b01, 0, 0>;
    using e2 = blade<0b10, 0, 0>;

    // Multivectors house instances of blades
    mvec<e1, e2> v = { 1.0f, 2.0f };

    std::cout << eval(v * v);     // Prints: { 5 ,  0 e1e2 }
}
```

In the above example, a multivector consisting of grade 1 blades (vectors) is squared using the
geometric product, yielding a new multivector with a scalar and a bivector component. The basis
vectors in a blade have the signature +1 (hyperbolic), -1 (complex) or 0 (dual) based on which
template bitflag marks their presence. 

Several common algebras are included in the form of namespaces with useful aliases, constants 
and literals for that algebra, all using the same template classes under the hood:

```cpp
// 3D geometric algebra
using namespace wg;
using namespace algebras::ga3d;

vec v1 = 1_e1 + 2_e2 + 1_e3;
vec v2 = 1_e1 - 1_e2 + 0_e3;

// Lazily calculates the components requested
mvec<e12, e23> v3 = (v1 - v2) * (v2 + 1);

std::cout << v3;    // prints: { -3 e1e2,  1 e2e3 }
```

```cpp
// Complex numbers
using namespace wg;
using namespace algebras::complex;

complex z1 = 1.0 + i;
complex z2 = 1.0 - i;

complex z3 = z1 * z2;

std::cout << z3;    // Prints: { 2 ,  0 i1 }
```

The use of expression templates turned out to be particularly beneficial in the library
since, in addition to eliminating temporaries, it allows expressions to be lazily 
evaluated only for the components of interest (e.g. only the scalar part of a squared
vector). The downside is that using auto to get the result of an expression can be 
perilous:

```cpp
using namespace wg;
using namespace algebras::ga2d;

vec v1 = 1_e1 + 2_e2;
vec v2 = 3_e1 - 1_e2;

auto v3 = v1 * v2; // v3 now contains an expression, not a multivector

// Can trigger evaluation of expression by several means:

mvec<e12> v4 = v3;              // (1) Specifying type
auto v5 = eval(v3);             // (2) Forcing evaluation (gets all components as multivector)
auto v6 = grade<2>(v3);         // (3) Using grade projection (returns multivector)
auto v7 = get<e12>(v3);         // (4) Using get (returns float if only one component is specified)
auto [scalar, bivector] = v3;   // (5) Using structured bindings (returns floats)

mvec<e1> v8 = v3;               // Compile error: no e1 component available in expression
```

## How it works

Since all information is represented through template parameters (barring the single float 
value of each blade), the implementation of operations can be wired up at compile time using 
metaprogramming techniques. This is accomplished in two steps:

1. The result type (mvec) of the expression is determined using the result types of the 
   operands (the result type of an mvec is itself).
2. The component blades (indices) of each operand participating in producing a given blade
   in the result type is determined.

When a blade in the result type is requested from the expression (be it from the user or 
a parent expression), the relevant blades of the operands are produced and then combined.
The process is illustrated by the implementation of the geometric product expression below
(credit to 
[FluentC++](https://www.fluentcpp.com/2021/03/05/stdindex_sequence-and-its-improvement-in-c20/)
for the idea of std::index_sequence deduction in a C++20 immediately invoked lambda):

```cpp
// Expression produced by the * operator of two expressions
template <typename LHS, typename RHS>
class geometric_prod_expr
{
    LHS const& m_lhs;
    RHS const& m_rhs;

  public:
    using result_type = geometric_product<typename LHS::result_type,
                                          typename RHS::result_type>::type;

    constexpr geometric_prod_expr(LHS const& lhs, RHS const& rhs)
        : m_lhs(lhs), m_rhs(rhs)
    {
    }

    // Produce the blade at index I in result type
    template <std::size_t I>
    friend constexpr auto get_blade(geometric_prod_expr<LHS, RHS> const& expr)
    {
        // Find which index pairs in sub expressions multiply to index I in result type
        using index_map = geometric_product_sub_indices<I, result_type,
                                                        typename LHS::result_type,
                                                        typename RHS::result_type>;

        // Return sum of relevant blade products
        return [&]<std::size_t... Ix1, std::size_t... Ix2>
               (std::index_sequence<Ix1...>, std::index_sequence<Ix2...>)
               {
                   return ((get_blade<Ix1>(expr.m_lhs) 
                          * get_blade<Ix2>(expr.m_rhs)) + ...); 
               }
               (typename index_map::Is1{}, typename index_map::Is2{});
    }
};
```

## Installation

The library provides a CMake target which can be linked to. Simply clone the project into 
your own and add

```CMake
add_subdirectory(wedge)
target_link_libraries(your_project PRIVATE wedge)
```

to your CMakeLists.txt file. Alternatively, since the library is header-only, you could also 
just drop the include files into your project directly.


## Requirements

Requires C++20. Tested on GCC 10.3 - 12.2 (Mingw-w64).

## Features

Wedge is very lightweight in the sense that many features are not implemented :). Notably, 
the outer and the inner products are missing, as is the exponential function and the 
different algebras in the "algebras" folder are sporadically implemented.

 - [x] Basic multivector operations (add/sub/scale/negate/reverse)
 - [x] Geometric product
 - [ ] Outer product
 - [ ] Inner product
 - [ ] Compound multivector operations
 - [x] Grade projection
 - [x] 2D vectorspace geometric algebra
 - [x] 3D vectorspace geometric algebra
 - [x] 2D projective geometric algebra
 - [ ] 3D projective geometric algebra
 - [ ] Spacetime (Minkowski) algebra
 - [ ] 2D conformal geometric algebra
 - [ ] 3D conformal geometric algebra
 - [ ] Symbolic values
 - [ ] exp function
 - [x] Unit tests

Planned future efforts are focused on adding basic compile time symbolic values to automate 
algorithm selection, which is expected to be useful in implementing the exponential function.
The library is experimental and many things are subject to change.

## License

Distributed under the MIT license.
