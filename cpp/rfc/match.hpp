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

#ifndef RFC_MATCH_HPP
#define RFC_MATCH_HPP

#include <regex>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>


namespace k5{

/*********************************************************************/
/*                                                                   */
/*                            match family                           */
/*                                                                   */
/*********************************************************************/

std::vector< std::string > match( std::string user_string, const std::string& user_pattern, const std::string& flags = "o" ){

    const bool flags_has_i = flags.find( "i" ) < flags.size();
    const bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;
    std::regex rx( user_pattern, regex_flag );
    std::regex_token_iterator< std::string::const_iterator > first( user_string.begin(),
                                                                    user_string.end(),
                                                                    rx ), last;

    if( flags_has_g ){
        return std::vector< std::string >( first, last );
    } else {
        if( std::distance( first, last ) >= 1 ){
            return std::vector< std::string >( 1, *first );
        } else {
            return std::vector< std::string >();
        }
    }
}

template< typename Container >
void match_to( std::string user_string, std::vector< std::string >& vec_str, const std::string& user_pattern, const std::string& flags = "o" ){

    const bool flags_has_i = flags.find( "i" ) < flags.size();
    const bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;
    std::regex rx( user_pattern, regex_flag );
    std::regex_token_iterator< std::string::const_iterator > first( user_string.begin(),
                                                                    user_string.end(),
                                                                    rx ), last;

    if( flags_has_g ){
        vec_str.assign( first, last );
    } else {
        if( std::distance( first, last ) >= 1 ){
            vec_str.assign( 1, *first );
        } else {
            // nothing
        }
    }
}

template< typename Container >
void match_to( std::string user_string, Container& object, const std::string& user_pattern, const std::string& flags = "o" ){

    const bool flags_has_i = flags.find( "i" ) < flags.size();
    const bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;
    std::regex rx( user_pattern, regex_flag );
    std::regex_token_iterator< std::string::const_iterator > first( user_string.begin(),
                                                                    user_string.end(),
                                                                    rx ), last;

    if( flags_has_g ){
        std::copy( first, last, std::back_insert_iterator< Container >( object ) );
    } else {
        if( std::distance( first, last ) >= 1 ){
            object.push_back( 1, *first );
        } else {
            // nothing
        }
    }
}

std::string match_at_index( const std::string& user_string, const std::string& user_pattern, int position ){

    const std::regex rx( user_pattern );

    std::regex_token_iterator< std::string::const_iterator > first( user_string.begin(), user_string.end(), rx ), last;
    const std::ptrdiff_t distance = std::distance( first, last );

    if( position >= distance )      return user_string;
    if( position + distance < 0 )   return user_string;

    if( position < 0 ){
        position = position + distance;
        while( position-- ) first++;
        //std::advance( first, position );
        return *first;
    } else {
        while( position-- ) first++;
        //std::advance( first, position );
        return *first;
    }

    return user_string;
}

void match_at_index_to( const std::string& user_string, std::string& user_index, const std::string& user_pattern, int position ){

    const std::regex rx( user_pattern );

    std::regex_token_iterator< std::string::const_iterator > first( user_string.begin(), user_string.end(), rx ), last;
    const std::ptrdiff_t distance = std::distance( first, last );

    if( position >= distance )      user_index = user_string;
    if( position + distance < 0 )   user_index = user_string;

    if( position < 0 ){
        position = position + distance;
        while( position-- ) first++;
        //std::advance( first, position );
        user_index = *first;
    } else {
        while( position-- ) first++;
        //std::advance( first, position );
        user_index = *first;
    }

    user_index = user_string;
}

std::vector< std::string > match_all( std::string user_string, const std::string& user_pattern ){

    std::regex::flag_type regex_flag                  = std::regex_constants::icase;
//    std::regex_constants::match_flag_type search_flag = std::regex_constants::match_default;
    std::regex rx( user_pattern, regex_flag );

    std::regex_token_iterator< std::string::const_iterator > first( user_string.begin(), user_string.end(), rx ), last;

    return std::vector< std::string >( first, last );
}

void match_all_to( const std::string& user_string, std::vector< std::string >& vec_str, const std::string& user_pattern ){

    std::regex::flag_type regex_flag                  = std::regex_constants::icase;
//    std::regex_constants::match_flag_type search_flag = std::regex_constants::match_default;
    std::regex rx( user_pattern, regex_flag );

    std::regex_token_iterator< std::string::const_iterator > first( user_string.begin(), user_string.end(), rx ), last;

    vec_str.assign( first, last );
}

template< typename Container >
void match_all_to( const std::string& user_string, Container& object, const std::string& user_pattern ){

    std::regex::flag_type regex_flag                  = std::regex_constants::icase;
//    std::regex_constants::match_flag_type search_flag = std::regex_constants::match_default;
    std::regex rx( user_pattern, regex_flag );

    std::regex_token_iterator< std::string::const_iterator > first( user_string.begin(), user_string.end(), rx ), last;

    std::copy( object.begin(), object.end(), std::back_insert_iterator< Container >( object ) );
}

bool has_match( const std::string& user_string, const std::string& user_pattern, const std::string& flags = "o"  ){

    const bool flags_has_i = flags.find( "i" ) < flags.size();
//    const bool flags_has_g = flags.find( "g" ) < flags.size();
    std::vector< std::string > vec_str;

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;
    std::regex rx( user_pattern, regex_flag );

    return std::regex_search( user_string, rx );
}

} // end of namespace k5



#endif // RFC_MATCH_HPP

