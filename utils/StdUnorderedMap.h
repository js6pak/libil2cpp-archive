#pragma once

#ifdef __clang__
# if __has_include(<tr1/unordered_map>)
#  include <tr1/unordered_map>
using namespace std::tr1;
# else
#  include <unordered_map>
using namespace std;
# endif
#elif defined(__GNUC__)
#  include <tr1/unordered_map>
using namespace std::tr1;
#else
# include <unordered_map>
using namespace std;
#endif

