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

namespace k5 {

/***********************************************************************/
/*                                                                     */
/*                            valid family                             */
/*                                                                     */
/***********************************************************************/

bool regex_is_valid( const std::string& user_pattern ){
    bool result = false;

    try{
        std::regex regex( user_pattern );
        result = true;
    } catch( const std::regex_error& ){
        result = false;
    }

    return result;
}

const char* regex_is_valid( const char* user_pattern ){
    const char* result = nullptr;
    try{
        std::regex regex( user_pattern );
    } catch( const std::regex_error& re ){
        result = re.what();
    }

    return result;
}

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

/***********************************************************************/
/*                                                                     */
/*                            join family                              */
/*                                                                     */
/***********************************************************************/


template< typename Container >
std::string join( Container con, const std::string& glue = " " ){

    std::ostringstream oss;
    for( const auto& item : con ){
        oss << item << glue;
    }

    //return oss.str();
    return oss.str().substr( 0, oss.str().size() - glue.size() );
}

template< typename Container >
void join_to( Container con, std::string& user_string, const std::string& glue = " " ){

    std::ostringstream oss;
    for( const auto& item : con ){
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
void join_to( Container first, Container last, std::string& user_string, const std::string& glue = " " ){

    std::ostringstream oss;
    while( first != last ){
        // ( ( first + 1 ) != last ) ? ( oss << *first << glue ) : ( oss << *first );
        oss << *first << glue;
        ++first;
    }

    user_string = oss.str().substr( 0, oss.str().size() - glue.size() );
}

/***********************************************************************/
/*                                                                     */
/*                       substitute family                             */
/*                                                                     */
/***********************************************************************/

std::string substitute( const std::string& user_string, const std::string user_pattern, const std::string& substitution, const std::string& flags = "o" ){

    bool flags_has_i = flags.find( "i" ) < flags.size();
    bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;

    std::regex rx( user_pattern, regex_flag );

    return std::regex_replace( user_string, rx, substitution, search_flag );
}

void substitute_to( const std::string& user_string, std::string& new_user_string, const std::string user_pattern, const std::string& substitution, const std::string& flags = "o" ){

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


std::string substitute_all( const std::string& user_string, const std::string user_pattern, const std::string& substitution ){

    std::regex::flag_type regex_flag                  = std::regex_constants::icase;
    std::regex_constants::match_flag_type search_flag = std::regex_constants::match_default;

    std::regex rx( user_pattern, regex_flag );

    return std::regex_replace( user_string, rx, substitution, search_flag );

}

void substitute_all_to( const std::string& user_string, std::string& new_user_string, const std::string user_pattern, const std::string& substitution ){

    std::regex::flag_type regex_flag                  = std::regex_constants::icase;
    std::regex_constants::match_flag_type search_flag = std::regex_constants::match_default;

    std::regex rx( user_pattern, regex_flag );

    new_user_string = std::regex_replace( user_string, rx, substitution, search_flag );
}

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
    const bool flags_has_g = flags.find( "g" ) < flags.size();
    std::vector< std::string > vec_str;

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;
    std::regex rx( user_pattern, regex_flag );

    return std::regex_search( user_string, rx, search_flag );
}

/***********************************************************************/
/*                                                                     */
/*                            get family                               */
/*                                                                     */
/***********************************************************************/

std::string get_prefix( const std::string& user_string, const std::string& user_pattern, const std::string& flags = "o" ){

    bool flags_has_i = flags.find( "i" ) < flags.size();
//    bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;

    std::regex rx( user_pattern, regex_flag );
    std::match_results< std::string::const_iterator > mr;

//    std::regex_search( user_string, mr, rx, search_flag );
    std::regex_search( user_string, mr, rx );

    return mr.prefix().str();
}

void get_prefix_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, const std::string& flags = "o" ){

    bool flags_has_i = flags.find( "i" ) < flags.size();
//    bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;

    std::regex rx( user_pattern, regex_flag );
    std::match_results< std::string::const_iterator > mr;

//    std::regex_search( user_string, mr, rx, search_flag );
    std::regex_search( user_string, mr, rx );

    new_user_string = mr.prefix().str();
}



std::string get_suffix( const std::string& user_string, const std::string& user_pattern, const std::string& flags = "o" ){

    bool flags_has_i = flags.find( "i" ) < flags.size();
//    bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;

    std::regex rx( user_pattern, regex_flag );
    std::match_results< std::string::const_iterator > mr;

//    std::regex_search( user_string, mr, rx, search_flag );
    std::regex_search( user_string, mr, rx );

    return mr.suffix().str();
}

void get_suffix_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, const std::string& flags = "o" ){

    bool flags_has_i = flags.find( "i" ) < flags.size();
//    bool flags_has_g = flags.find( "g" ) < flags.size();

    std::regex::flag_type regex_flag                  = flags_has_i ? std::regex_constants::icase         : std::regex_constants::ECMAScript;
//    std::regex_constants::match_flag_type search_flag = flags_has_g ? std::regex_constants::match_default : std::regex_constants::format_first_only;

    std::regex rx( user_pattern, regex_flag );
    std::match_results< std::string::const_iterator > mr;

//    std::regex_search( user_string, mr, rx, search_flag );
    std::regex_search( user_string, mr, rx );

    new_user_string = mr.suffix().str();
}

std::string get_prefix_of_index( const std::string& user_string, const std::string& user_pattern, int position ){

    std::regex rx( user_pattern, std::regex_constants::icase );
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
    std::string the_prefix;
    while( std::regex_search( temp, mr, rx ) ){
        if( !position-- ){
            if( mr.str() != "" ){
                return the_prefix;
            }
            //break;
        }

        the_prefix += mr.prefix().str() + mr.str();
        temp = mr.suffix().str();
    }

    return user_string;
}

void get_prefix_of_index_to( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, int position ){

    std::regex rx( user_pattern, std::regex_constants::icase );
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
    std::string the_prefix;
    while( std::regex_search( temp, mr, rx ) ){
        if( !position-- ){
            if( mr.str() != "" ){
                new_user_string = the_prefix;
            }
            //break;
        }

        the_prefix += mr.prefix().str() + mr.str();
        temp = mr.suffix().str();
    }
}

std::string get_suffix_of_index( const std::string& user_string, const std::string& user_pattern, int position ){

    std::regex rx( user_pattern, std::regex_constants::icase );
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
    while( std::regex_search( temp, mr, rx ) ){
        if( !position-- ){
            if( mr.str() != "" ){
                return mr.suffix().str();
            }
            //break;
        }
        temp = mr.suffix().str();
    }

    return user_string;
}

void get_suffix_of_index( const std::string& user_string, std::string& new_user_string, const std::string& user_pattern, int position ){

    std::regex rx( user_pattern, std::regex_constants::icase );
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
    while( std::regex_search( temp, mr, rx ) ){
        if( !position-- ){
            if( mr.str() != "" ){
                new_user_string = mr.suffix().str();
            }
            //break;
        }
        temp = mr.suffix().str();
    }

}

} // end of namespace k5
