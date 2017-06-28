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

#ifndef RFC_JOIN_HPP
#define RFC_JOIN_HPP

#include <regex>
#include <string>
#include <sstream>

namespace k5{

/***********************************************************************/
/*                                                                     */
/*                            join family                              */
/*                                                                     */
/***********************************************************************/

template< typename Container >
std::string join( const Container& object, const std::string& glue = " " ){

    std::ostringstream oss;
    for( const auto& item : object ){
        oss << item << glue;
    }

    //return oss.str();
    return oss.str().substr( 0, oss.str().size() - glue.size() );
}

template< typename Container >
void join_to( const Container& object, std::string& user_string, const std::string& glue = " " ){

    std::ostringstream oss;
    for( const auto& item : object ){
        oss << item << glue;
    }

    user_string = oss.str().substr( 0, oss.str().size() - glue.size() );
}

template< typename Container >
std::string join( Container first, Container last,const std::string& glue = " " ){

    std::ostringstream oss;
    while( first != last ){
        // ( ( first + 1 ) != last ) ? ( oss << *first << glue ) : ( oss << *first );
        oss << *first << glue;
        ++first;
    }

    //return oss.str();
    return oss.str().substr( 0, oss.str().size() - glue.size() );
}

template< typename Container >
void join_to( Container first, Container last, std::string& user_string, const std::string& glue  = " " ){

    std::ostringstream oss;
    while( first != last ){
        // ( ( first + 1 ) != last ) ? ( oss << *first << glue ) : ( oss << *first );
        oss << *first << glue;
        ++first;
    }

    user_string = oss.str().substr( 0, oss.str().size() - glue.size() );
}

} // end of namespace k5

#endif // RFC_JOIN_HPP

