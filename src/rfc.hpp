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

bool regex_is_valid( const std::string& user_pattern );

const char* regex_is_valid( const char* user_pattern );


/***********************************************************************/
/*                                                                     */
/*                            parse family                             */
/*                                                                     */
/***********************************************************************/

std::string parse( const char** argv, const char* glue = " " );

void parse_to( const char** argv, std::string& user_string, const char* glue = " " );

std::ptrdiff_t parse_count( const char** argv );

std::vector< std::string > parse_all( const char** argv, const char* glue = " "  );

void parse_all_to( const char** argv, std::vector< std::string >& vec_str, const char* glue = " "  );

template< typename Container >
Container parse_all( const char** argv, const char* glue = " "  );

template< typename Container >
void parse_all_to( const char** argv, Container& object, const char* glue = " "  );

std::string parse_index( const char** argv, int position );

void parse_index_to( const char** argv, std::string& user_string, int position );

std::vector< std::string > parse_index_all( const char** argv, int position );

template< typename Container >
Container parse_index_all( const char** argv, int position );

void parse_index_all_to( const char** argv, std::vector< std::string >& vec_str, int position );

template< typename Container >
void parse_index_all_to( const char** argv, Container& object, int position );

std::string parse_option( const char** argv, const std::string& argument );

void parse_option_to( const char** argv, std::string& user_string, const std::string& argument );

std::vector< std::string > parse_option_all( const char** argv, const std::string& argument );

template< typename Container >
Container parse_option_all( const char** argv, const std::string& argument );

void parse_option_all_to( const char** argv, std::vector< std::string >& vec_str, const std::string& argument );

template< typename Container >
void parse_option_all_to( const char** argv, Container& object, const std::string& argument );

/***********************************************************************/
/*                                                                     */
/*                            split family                             */
/*                                                                     */
/***********************************************************************/

std::vector< std::string > split( const std::string& user_string, const std::string& delimiter = "\\s+" );

template< typename Container >
Container split( const std::string& user_string, const std::string& delimiter = "\\s+" );

template< typename Container >
void split_to( const std::string& user_string, Container& object, const std::string& delimiter = "\\s+" );

/***********************************************************************/
/*                                                                     */
/*                            join family                              */
/*                                                                     */
/***********************************************************************/

template< typename Container >
std::string join( Container con, const std::string& glue = " " );

template< typename Container >
void join_to( Container con, std::string& user_string, const std::string& glue = " " );

template< typename Container >
std::string join( Container first, Container last,const std::string& glue = " " );

template< typename Container >
void join_to( Container first, Container last, std::string& user_string, const std::string& glue = " " );


/***********************************************************************/
/*                                                                     */
/*                       substitute family                             */
/*                                                                     */
/***********************************************************************/

std::string substitute( const std::string& user_string, const std::string user_pattern, const std::string& substitution, const std::string& flags = "o" );

void substitute_to( const std::string& user_string, std::string& new_user_string, const std::string user_pattern, const std::string& substitution, const std::string& flags = "o" );

std::string substitute_at_index( const std::string& user_string, const std::string& user_pattern, const std::string& substitution, int position );

void substitute_at_index_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, const std::string& substitution, int position );

std::string substitute_all( const std::string& user_string, const std::string user_pattern, const std::string& substitution );

void substitute_all_to( const std::string& user_string, std::string& new_user_string, const std::string user_pattern, const std::string& substitution );

/*********************************************************************/
/*                                                                   */
/*                            match family                           */
/*                                                                   */
/*********************************************************************/

std::vector< std::string > match( std::string user_string, const std::string& user_pattern, const std::string& flags = "o" );

template< typename Container >
void match_to( std::string user_string, std::vector< std::string >& vec_str, const std::string& user_pattern, const std::string& flags = "o" );

template< typename Container >
void match_to( std::string user_string, Container& object, const std::string& user_pattern, const std::string& flags = "o" );

std::string match_at_index( const std::string& user_string, const std::string& user_pattern, int position );

void match_at_index_to( const std::string& user_string, std::string& user_index, const std::string& user_pattern, int position );

std::vector< std::string > match_all( std::string user_string, const std::string& user_pattern );

void match_all_to( const std::string& user_string, std::vector< std::string >& vec_str, const std::string& user_pattern );

template< typename Container >
void match_all_to( const std::string& user_string, Container& object, const std::string& user_pattern );

bool has_match( const std::string& user_string, const std::string& user_pattern, const std::string& flags = "o"  );

/***********************************************************************/
/*                                                                     */
/*                            get family                               */
/*                                                                     */
/***********************************************************************/

std::string get_prefix( const std::string& user_string, const std::string& user_pattern, const std::string& flags = "o" );

void get_prefix_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, const std::string& flags = "o" );

std::string get_suffix( const std::string& user_string, const std::string& user_pattern, const std::string& flags = "o" );

void get_suffix_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, const std::string& flags = "o" );

std::string get_prefix_of_index( const std::string& user_string, const std::string& user_pattern, int position );

void get_prefix_of_index_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, int position );

std::string get_suffix_of_index( const std::string& user_string, const std::string& user_pattern, int position );

void get_suffix_of_index( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, int position );

} // end of namespace k5

#endif // REGEX_FUNCTION_COLLECTION_HPP

