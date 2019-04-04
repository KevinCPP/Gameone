#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <vector>
#include <string>

namespace Util{

    //pass a string, and it will fill the vector passed to result
    //with the ints that were parsed from the string:
    void parseIntsFromString(const std::string& str, std::vector<int>& result);

}

#endif // UTILITY_H_INCLUDED
