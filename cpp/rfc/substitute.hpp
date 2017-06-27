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

#ifndef RFC_SUBSTITUTE_HPP
#define RFC_SUBSTITUTE_HPP

#include <regex>
#include <string>

namespace k5{

/***********************************************************************/
/*                                                                     */
/*                       substitute family                             */
/*                                                                     */
/***********************************************************************/

std::string substitute( const std::string& user_string, const std::string& user_pattern, const std::string& substitution, const std::string& flags ){

    bool flags_has_i = flags.find( "i" ) < flags.size();
    bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;

    std::regex rx( user_pattern, regex_flag );

    return std::regex_replace( user_string, rx, substitution, search_flag );
}

void substitute_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, const std::string& substitution, const std::string& flags){

    bool flags_has_i = flags.find( "i" ) < flags.size();
    bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;

    std::regex rx( user_pattern, regex_flag );

    new_user_string = std::regex_replace( user_string, rx, substitution, search_flag );
}

std::string substitute_at_index( const std::string& user_string, const std::string& user_pattern, const std::string& substitution, int position ){

    const std::regex rx( user_pattern );
    std::match_results< std::string::const_iterator > mr;


    if( position < 0 ){
        std::string temp = user_string;
        unsigned int counter = 0;

        while( std::regex_search( temp, mr, rx ) ){
            temp = mr.suffix().str();
            ++counter;
        }
        position = counter + position;
    }

    std::string temp = user_string;
    std::string new_string;

    while( std::regex_search( temp, mr, rx ) ){
        if( !position-- ){
            new_string += std::regex_replace( temp, rx, substitution, std::regex_constants::format_first_only );
            break;
        }

        new_string += mr.prefix().str() + mr.str();
        temp = mr.suffix().str();
    }

    if( mr.str() != "" )    return new_string;
    else                    return user_string;
}

void substitute_at_index_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, const std::string& substitution, int position ){

    const std::regex rx( user_pattern );
    std::match_results< std::string::const_iterator > mr;


    if( position < 0 ){
        std::string temp = user_string;
        unsigned int counter = 0;

        while( std::regex_search( temp, mr, rx ) ){
            temp = mr.suffix().str();
            ++counter;
        }
        position = counter + position;
    }

    std::string temp = user_string;
    std::string new_string;

    while( std::regex_search( temp, mr, rx ) ){
        if( !position-- ){
            new_string += std::regex_replace( temp, rx, substitution, std::regex_constants::format_first_only );
            break;
        }

        new_string += mr.prefix().str() + mr.str();
        temp = mr.suffix().str();
    }

    if( mr.str() != "" )    new_user_string = new_string;
    else                    new_user_string = new_string;
}

std::string substitute_all( const std::string& user_string, const std::string& user_pattern, const std::string& substitution ){

    std::regex::flag_type regex_flag                  = std::regex_constants::icase;
    std::regex_constants::match_flag_type search_flag = std::regex_constants::match_default;

    std::regex rx( user_pattern, regex_flag );

    return std::regex_replace( user_string, rx, substitution, search_flag );

}

void substitute_all_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, const std::string& substitution ){

    std::regex::flag_type regex_flag                  = std::regex_constants::icase;
    std::regex_constants::match_flag_type search_flag = std::regex_constants::match_default;

    std::regex rx( user_pattern, regex_flag );

    new_user_string = std::regex_replace( user_string, rx, substitution, search_flag );
}


} // end of namespace k5

#endif // RFC_SUBSTITUTE_HPP

