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

    parse family:
        parse
        parse_to
        parse_count
        parse_index
        parse_index_to
        parse_index_all
        parse_index_all_to
        parse_option
        parse_option_to
        parse_option_all
        parse_option_all_to

    split family:
        split
        split_to

    join family:
        join
        join_to

    substitute family:
        substitute
        substitute_to
        substitute_all
        substitute_all_to
        substitute_at_index
        substitute_at_index_to

    match family:
        match
        match_to
        match_all
        match_all_to
        match_at_index
        match_at_index_to
        has_match

    get family:
        get_prefix
        get_prefix_to
        get_suffix
        get_suffix_to
        get_prefix_of_index
        get_prefix_of_index_to
        get_suffix_of_index
        get_suffix_of_index_to

    count family
        count_match
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

