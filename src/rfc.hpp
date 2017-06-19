/*
    +-------------------------------------+
    |Regex Function Collection ( or: RFC )|
    |-------------------------------------|
    |Written by Shakiba (=k-five) in 2017,|
    |shared on Git-Hub .../k-five/RFC,    |
    |All things that is used, is from std,|
    |there is no nonstandard library, but,|
    |you can use boost in place of std.   |
    +-------------------------------------+
    |Any bug, suggestion, critic, opinion,|
    |would be appreciated. Feel free if y-|
    |ou need a special function that you c|
    |ould not find it here.               |
    +-------------------------------------+
    | contact me: vhsu30@yahoo.com        |
    | github: k-five                      |
    | stackoverflow: k-five               |
    | twitter: k__five                    |
    +-------------------------------------+

    =======================================

    content:

    valid family:
        regex_is_valid (1)
        regex_is_valid (2)

*/

#ifndef REGEX_FUNCTION_COLLECTION_HPP
#define REGEX_FUNCTION_COLLECTION_HPP

#include <regex>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

namespace k5 {

/***********************************************************************/
/*                                                                     */
/*                            valid family                             */
/*                                                                     */
/***********************************************************************/

bool        regex_is_valid( const std::string& user_pattern );

const char* regex_is_valid( const char* user_pattern );

} // end of namespace k5

#endif // REGEX_FUNCTION_COLLECTION_HPP

