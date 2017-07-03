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

    count family
        count_match
*/

#ifndef RFC_COUNT_HPP
#define RFC_COUNT_HPP

#include <regex>
#include <string>

namespace k5{

/***********************************************************************/
/*                                                                     */
/*                           count family                              */
/*                                                                     */
/***********************************************************************/

std::size_t count_match( const std::string& user_string, const std::string& user_pattern, const std::string& flags = "o" ){

    const bool flags_has_i = flags.find( "i" ) < flags.size();
    const bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;
    std::regex rx( user_pattern, regex_flag );
    std::match_results< std::string::const_iterator > mr;

    std::size_t counter = 0;
    std::string temp = user_string;
    while( std::regex_search( temp, mr, rx ) ){
        temp = mr.suffix().str();
        ++counter;
    }

    if( flags_has_g ){
        return counter;
    } else {
        if( counter >= 1 ) return 1;
        else               return 0;
    }

}


} // end of namespace k5


#endif // RFC_COUNT_HPP

