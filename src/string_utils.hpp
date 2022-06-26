// Code judiciously copied from
// https://stackoverflow.com/questions/44973435/stdptr-fun-replacement-for-c17/44973498#44973498

#include <algorithm>
#include <cctype>
#include <locale>
#include <string>

// trim from start (in place)
inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

// trim from start (copying)
inline std::string ltrim_copy(std::string s) {
  ltrim(s);
  return s;
}

// trim from end (copying)
inline std::string rtrim_copy(std::string s) {
  rtrim(s);
  return s;
}

// trim from both ends (copying)
inline std::string trim_copy(std::string s) {
  trim(s);
  return s;
}

// trim from both ends (copying)
inline std::string trim_remove_leading_zeros_copy(std::string s) {
  trim(s);
  auto found = s.find_first_not_of('0');
  if (found != std::string::npos) {
    if (found < s.length()) {
      return s.erase(0, found);
    }
    return "0";
  }
  return s;
}
