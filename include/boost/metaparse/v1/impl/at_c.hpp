#ifndef BOOST_METAPARSE_V1_IMPL_AT_C_HPP
#define BOOST_METAPARSE_V1_IMPL_AT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/config.hpp>
#include <boost/metaparse/v1/fwd/string.hpp>

#include <boost/mpl/char.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, int N>
        struct at_c;

#ifdef BOOST_VARIADIC_STRING
        template <char C, char... Cs, int N>
        struct at_c<string<C, Cs...>, N> : at_c<string<Cs...>, N - 1> {};

        template <char C, char... Cs>
        struct at_c<string<C, Cs...>, 0> : boost::mpl::char_<C> {};
#else
        #ifdef BOOST_STRING_CASE
        #  error BOOST_STRING_CASE is already defined
        #endif
        #define BOOST_STRING_CASE(z, n, unused) \
          template <BOOST_PP_ENUM_PARAMS(BOOST_LIMIT_STRING_SIZE, int C)> \
          struct \
            at_c< \
              string<BOOST_PP_ENUM_PARAMS(BOOST_LIMIT_STRING_SIZE,C)>, \
              n \
            > : \
            boost::mpl::char_<BOOST_PP_CAT(C, n)> \
          {};
      
        BOOST_PP_REPEAT(BOOST_LIMIT_STRING_SIZE, BOOST_STRING_CASE, ~)

        #undef BOOST_STRING_CASE
#endif
      }
    }
  }
}

#endif

