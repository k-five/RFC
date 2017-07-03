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

    split family:
        split
        split_to
*/

#ifndef RFC_SPLIT_HPP
#define RFC_SPLIT_HPP

#include <regex>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

namespace k5{

/***********************************************************************/
/*                                                                     */
/*                            split family                             */
/*                                                                     */
/***********************************************************************/

std::vector< std::string > split( const std::string& user_string, const std::string& delimiter = "\\s+" ){

    std::regex rx( delimiter );
    std::regex_token_iterator< std::string::const_iterator > first( user_string.begin(), user_string.end(), rx, -1 ), last;
    //return std::vector< std::string >( first, {} );
    return std::vector< std::string >( first, last );

}

template< typename Container >
Container split( const std::string& user_string, const std::string& delimiter = "\\s+" ){

    std::regex rx( delimiter );
    std::regex_token_iterator< std::string::const_iterator > first( user_string.begin(), user_string.end(), rx, -1 ), last;
    //return Container( first, {} );
    return Container( first, last );

}

template< typename Container >
void split_to( const std::string& user_string, Container& object, const std::string& delimiter = "\\s+" ){

    std::regex rx( delimiter );
    std::regex_token_iterator< std::string::const_iterator > first( user_string.begin(), user_string.end(), rx, -1 ), last;
    std::copy( first, last, std::back_insert_iterator< Container >( object ) );
}

} // end of namespace k5


#endif // RFC_SPLIT_HPP

