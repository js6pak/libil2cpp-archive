#pragma once

#ifdef __clang__
# if __has_include(<tr1/unordered_set>)
#  include <tr1/unordered_set>
using std::tr1::unordered_set;
# else
#  include <unordered_set>
using std::unordered_set;
# endif
#elif defined(__GNUC__)
#  include <tr1/unordered_set>
using std::tr1::unordered_set;
#else
# include <unordered_set>
using std::unordered_set;
#endif

