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



} // end of namespace k5

#endif // REGEX_FUNCTION_COLLECTION_HPP

