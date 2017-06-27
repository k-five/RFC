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

#ifndef RFC_PARSE_HPP
#define RFC_PARSE_HPP

#include <regex>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

namespace k5{

/***********************************************************************/
/*                                                                     */
/*                            parse family                             */
/*                                                                     */
/***********************************************************************/

std::string parse( const char** argv, const char* glue = " " ){

    std::string result;
    while( *argv ){
        result += *argv;
        result += glue;
        argv++;
    }

    return result;
}

void parse_to( const char** argv, std::string& user_string, const char* glue = " " ){

    while( *argv ){
        user_string += *argv;
        user_string += glue;
        argv++;
    }
}


std::ptrdiff_t parse_count( const char** argv ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( "[-]{1,2}(?!-).+?(?= -)" );
    std::regex_token_iterator< std::string::const_iterator > first( command_line.begin(),
                                                                    command_line.end(),
                                                                    rx), last;
    return std::distance( first, last );
}


std::vector< std::string > parse_all( const char** argv, const char* glue = " "  ){

    std::string command_line = parse( argv, glue );
    command_line += "-";

    std::regex rx( "[-]{1,2}(?!-).+?(?= -)" );
    std::regex_token_iterator< std::string::const_iterator > first( command_line.begin(),
                                                                    command_line.end(),
                                                                    rx), last;

    return std::vector< std::string >( first, last );
}

void parse_all_to( const char** argv, std::vector< std::string >& vec_str, const char* glue = " "  ){

    std::string command_line = parse( argv, glue );
    command_line += "-";

    std::regex rx( "[-]{1,2}(?!-).+?(?= -)" );
    std::regex_token_iterator< std::string::const_iterator > first( command_line.begin(),
                                                                    command_line.end(),
                                                                    rx), last;

    vec_str.assign( first, last );
}

template< typename Container >
Container parse_all( const char** argv, const char* glue = " "  ){

    std::string command_line = parse( argv, glue );
    command_line += "-";

    std::regex rx( "[-]{1,2}(?!-).+?(?= -)" );
    std::regex_token_iterator< std::string::const_iterator > first( command_line.begin(),
                                                                    command_line.end(),
                                                                    rx), last;

    return Container( first, last );
}

template< typename Container >
void parse_all_to( const char** argv, Container& object, const char* glue = " "  ){

    std::string command_line = parse( argv, glue );
    command_line += "-";

    std::regex rx( "[-]{1,2}(?!-).+?(?= -)" );
    std::regex_token_iterator< std::string::const_iterator > first( command_line.begin(),
                                                                    command_line.end(),
                                                                    rx), last;

    std::copy( first, last, std::back_insert_iterator< Container >( object ) );
}


std::string parse_index( const char** argv, int position ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( "[-]{1,2}(?!-).+?(?= -)" );
    std::regex_token_iterator< std::string::const_iterator > first( command_line.begin(),
                                                                    command_line.end(),
                                                                    rx), last;
    const std::ptrdiff_t distance = std::distance( first, last );

    if( position >= distance )      return *argv;
    if( position + distance < 0 )   return *argv;

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

    return *argv;
}

void parse_index_to( const char** argv, std::string& user_string, int position ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( "[-]{1,2}(?!-).+?(?= -)" );
    std::regex_token_iterator< std::string::const_iterator > first( command_line.begin(),
                                                                    command_line.end(),
                                                                    rx), last;
    const std::ptrdiff_t distance = std::distance( first, last );

    if( position >= distance )      user_string = "";
    if( position + distance < 0 )   user_string = "";

    if( position < 0 ){
        position = position + distance;
        while( position-- ) first++;
        //std::advance( first, position );
        user_string = *first;
    } else {
        while( position-- ) first++;
        //std::advance( first, position );
        user_string = *first;
    }

}


std::vector< std::string > parse_index_all( const char** argv, int position ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( "[-]{1,2}(?!-).+?(?= -)" );
    std::regex_token_iterator< std::string::const_iterator > first( command_line.begin(),
                                                                    command_line.end(),
                                                                    rx), last;
    const std::ptrdiff_t distance = std::distance( first, last );

    if( position >= distance )      return  std::vector< std::string >();
    if( position + distance < 0 )   return  std::vector< std::string >();

    if( position < 0 ){
        position = position + distance;
        while( position-- ) first++;

        std::regex rx2( " " );
        const std::string temp = *first;
        std::regex_token_iterator< std::string::const_iterator > first2( temp.begin(),
                                                                         temp.end(),
                                                                         rx2,
                                                                         -1 ), last2;
        return std::vector< std::string >( first2, last2 );

    } else {
        while( position-- ) first++;

        std::regex rx2( " " );
        const std::string temp = *first;
        std::regex_token_iterator< std::string::const_iterator > first2( temp.begin(),
                                                                         temp.end(),
                                                                         rx2,
                                                                         -1 ), last2;
        return std::vector< std::string >( first2, last2 );
    }

    return std::vector< std::string >();
}
template< typename Container >
Container parse_index_all( const char** argv, int position ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( "[-]{1,2}(?!-).+?(?= -)" );
    std::regex_token_iterator< std::string::const_iterator > first( command_line.begin(),
                                                                    command_line.end(),
                                                                    rx), last;
    const std::ptrdiff_t distance = std::distance( first, last );

    if( position >= distance )      return  Container();
    if( position + distance < 0 )   return  Container();

    if( position < 0 ){
        position = position + distance;
        while( position-- ) first++;

        std::regex rx2( " " );
        const std::string temp = *first;
        std::regex_token_iterator< std::string::const_iterator > first2( temp.begin(),
                                                                         temp.end(),
                                                                         rx2,
                                                                         -1 ), last2;
        return Container( first2, last2 );

    } else {
        while( position-- ) first++;

        std::regex rx2( " " );
        const std::string temp = *first;
        std::regex_token_iterator< std::string::const_iterator > first2( temp.begin(),
                                                                         temp.end(),
                                                                         rx2,
                                                                         -1 ), last2;
        return Container( first2, last2 );
    }

    return Container();
}

void parse_index_all_to( const char** argv, std::vector< std::string >& vec_str, int position ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( "[-]{1,2}(?!-).+?(?= -)" );
    std::regex_token_iterator< std::string::const_iterator > first( command_line.begin(),
                                                                    command_line.end(),
                                                                    rx), last;
    const std::ptrdiff_t distance = std::distance( first, last );

    if( position >= distance )      vec_str = std::vector< std::string >();
    if( position + distance < 0 )   vec_str = std::vector< std::string >();

    if( position < 0 ){
        position = position + distance;
        while( position-- ) first++;

        std::regex rx2( " " );
        const std::string temp = *first;
        std::regex_token_iterator< std::string::const_iterator > first2( temp.begin(),
                                                                         temp.end(),
                                                                         rx2,
                                                                         -1 ), last2;
        vec_str.assign( first2, last2 );

    } else {
        while( position-- ) first++;

        std::regex rx2( " " );
        const std::string temp = *first;
        std::regex_token_iterator< std::string::const_iterator > first2( temp.begin(),
                                                                         temp.end(),
                                                                         rx2,
                                                                         -1 ), last2;
        vec_str.assign( first2, last2 );
    }

}

template< typename Container >
void parse_index_all_to( const char** argv, Container& object, int position ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( "[-]{1,2}(?!-).+?(?= -)" );
    std::regex_token_iterator< std::string::const_iterator > first( command_line.begin(),
                                                                    command_line.end(),
                                                                    rx), last;
    const std::ptrdiff_t distance = std::distance( first, last );

    if( position >= distance )      object = Container();
    if( position + distance < 0 )   object = Container();

    if( position < 0 ){
        position = position + distance;
        while( position-- ) first++;

        std::regex rx2( " " );
        const std::string temp = *first;
        std::regex_token_iterator< std::string::const_iterator > first2( temp.begin(),
                                                                         temp.end(),
                                                                         rx2,
                                                                         -1 ), last2;
        std::copy( first2, last2, std::back_insert_iterator< Container >( object ) );

    } else {
        while( position-- ) first++;

        std::regex rx2( " " );
        const std::string temp = *first;
        std::regex_token_iterator< std::string::const_iterator > first2( temp.begin(),
                                                                         temp.end(),
                                                                         rx2,
                                                                         -1 ), last2;
        std::copy( first2, last2, std::back_insert_iterator< Container >( object ) );
    }

}


std::string parse_option( const char** argv, const std::string& argument ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( argument + ".+?(?= -)" );
    std::match_results< std::string::const_iterator > mr;

    std::regex_search( command_line, mr, rx );

    return mr.str();
}

void parse_option_to( const char** argv, std::string& user_string, const std::string& argument ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( argument + ".+?(?= -)" );
    std::match_results< std::string::const_iterator > mr;

    std::regex_search( command_line, mr, rx );

    user_string = mr.str();
}

std::vector< std::string > parse_option_all( const char** argv, const std::string& argument ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( argument + ".+?(?= -)" );
    std::match_results< std::string::const_iterator > mr;

    std::regex_search( command_line, mr, rx );

    const std::string& temp = mr.str();
    std::regex rx2( " " );
    std::regex_token_iterator< std::string::const_iterator > first( temp.begin(),
                                                                    temp.end(),
                                                                    rx2,
                                                                    -1 ), last;
    return std::vector< std::string >( first, last );

}

template< typename Container >
Container parse_option_all( const char** argv, const std::string& argument ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( argument + ".+?(?= -)" );
    std::match_results< std::string::const_iterator > mr;

    std::regex_search( command_line, mr, rx );

    const std::string& temp = mr.str();
    std::regex rx2( " " );
    std::regex_token_iterator< std::string::const_iterator > first( temp.begin(),
                                                                    temp.end(),
                                                                    rx2,
                                                                    -1 ), last;
    return Container( first, last );

}


void parse_option_all_to( const char** argv, std::vector< std::string >& vec_str, const std::string& argument ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( argument + ".+?(?= -)" );
    std::match_results< std::string::const_iterator > mr;

    std::regex_search( command_line, mr, rx );

    const std::string& temp = mr.str();
    std::regex rx2( " " );
    std::regex_token_iterator< std::string::const_iterator > first( temp.begin(),
                                                                    temp.end(),
                                                                    rx2,
                                                                    -1 ), last;
    vec_str.assign( first, last );

}

template< typename Container >
void parse_option_all_to( const char** argv, Container& object, const std::string& argument ){

    std::string command_line = parse( argv );
    command_line += "-";

    std::regex rx( argument + ".+?(?= -)" );
    std::match_results< std::string::const_iterator > mr;

    std::regex_search( command_line, mr, rx );

    const std::string& temp = mr.str();
    std::regex rx2( " " );
    std::regex_token_iterator< std::string::const_iterator > first( temp.begin(),
                                                                    temp.end(),
                                                                    rx2,
                                                                    -1 ), last;
    std::copy( first, last, std::back_insert_iterator< Container >( object ) );

}

} // end of namespace k5


#endif // RFC_PARSE_HPP
