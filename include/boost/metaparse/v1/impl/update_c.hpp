#ifndef BOOST_METAPARSE_V1_IMPL_UPDATE_C_HPP
#define BOOST_METAPARSE_V1_IMPL_UPDATE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/config.hpp>
#include <boost/metaparse/v1/fwd/string.hpp>
#include <boost/metaparse/v1/impl/split_at_c.hpp>
#include <boost/metaparse/v1/impl/concat.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, int N, char C>
        struct update_c;

#ifndef BOOST_VARIADIC_STRING
        #ifdef BOOST_ARGN
        #  error BOOST_ARGN already defined
        #endif
        #define BOOST_ARGN(z, n, unused) , BOOST_PP_CAT(C, n)

        #ifdef BOOST_UPDATE
        #  error BOOST_UPDATE already defined
        #endif
        #define BOOST_UPDATE(z, n, unused) \
          template < \
            BOOST_PP_ENUM_PARAMS(BOOST_LIMIT_STRING_SIZE, int C), \
            char Ch \
          > \
          struct update_c< \
            string<BOOST_PP_ENUM_PARAMS(BOOST_LIMIT_STRING_SIZE, C)>, \
            n, \
            Ch \
          > : \
            string< \
              BOOST_PP_ENUM_PARAMS(n, C) BOOST_PP_COMMA_IF(n) \
              Ch \
              BOOST_PP_REPEAT_FROM_TO( \
                BOOST_PP_INC(n), \
                BOOST_PP_DEC(BOOST_LIMIT_STRING_SIZE), \
                BOOST_ARGN, \
                ~ \
              ) \
            > \
          {};

        BOOST_PP_REPEAT(BOOST_LIMIT_STRING_SIZE, BOOST_UPDATE, ~)

        #undef BOOST_UPDATE
        #undef BOOST_ARGN
#else
        template <class S, int N, char C>
        struct update_c :
          concat<
            typename split_at_c<N, S>::type::first,
            typename
              update_c<typename split_at_c<N, S>::type::second, 0, C>::type
          >
        {};
  
        template <char... Cs, char C, char NewChar>
        struct update_c<string<C, Cs...>, 0, NewChar> :
          string<NewChar, Cs...>
        {};
#endif
      }
    }
  }
}

#endif

