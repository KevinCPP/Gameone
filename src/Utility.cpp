#include "Utility.h"
#include <sstream>

namespace Util{

    /**
    * takes a string param, and a reference to an std::vector<int> param,
    * this method will parse all integers from the string parameter and
    * push_back the results into the vector that the result param refers
    * to:
    **/
    void parseIntsFromString(const std::string& str, std::vector<int>& result){
        std::stringstream ss;
        ss << str;

        std::string temp;

        int found;
        while(!ss.eof()){
            ss >> temp;

            if(std::stringstream(temp) >> found)
                result.push_back(found);

            temp = "";
        }
    }
}
