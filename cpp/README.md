## Regex Function Collection

### Cplusplus version

There are more than one header file. You can use them all, one by one
or just `include "rfc/rfc.hpp"` if you have the whole directory, or if
not, you just need `rfc.hpp`. If you just want to use **split family**
you can: `include "rfc/split.hpp"`. Header files have been separated by
family.

Families:
 - valid
 - parse
 - split
 - join
 - substitute
 - match
 - get
 - count

 ## Examples:

 #### [valid family](https://github.com/k-five/RFC/blob/master/cpp/rfc/valid.hpp): for validation a pattern.

 ```C++
#include <iostream>
#include "rfc/valid.hpp"

int main(){

    /// regex_is_valid

    const char* r = k5::regex_is_valid( "/\/\\" ); // returns regex_error.what() or nullptr
    if( !r ){
        std::cout << "okay valid\n";
    } else {
        std::cout << "not valid: " << r << '\n';
    }

    std::cout << std::string( 20, '-' ) << '\n';

    std::string s_pat( "/\/\\" );
    if( k5::regex_is_valid( s_pat ) ){              // returns true or false
        std::cout << "okay valid\n";
    } else {
        std::cout << "not valid\n";
    }

return 0;}

/* the output:

not valid: Unexpected end of regex when escaping.
--------------------
not valid

*/
 ```

 #### [parse](https://github.com/k-five/RFC/blob/master/cpp/rfc/parse.hpp) family:

 - `parse`
 - `parse_to`

 ```C++
 #include <iostream>
#include "rfc/parse.hpp"

int main( int argc,const char** argv ){

    /// parse
    std::cout << k5::parse( argv ) << '\n'; // returns a single string of all main argument

    /// parse_to
    std::string main_arg;
    k5::parse_to( argv, main_arg );         // void
    std::cout << main_arg << '\n';

return 0;}

/* the output:

 ideas   ./temp one two three
./temp one two three
./temp one two three

*/
 ```

 - `parse_count`
 - `parse_all`
 - `parse_all_to`

 ```C++
 #include <iostream>
#include "rfc/parse.hpp"

int main( int argc,const char** argv ){

    /// parse_count: counts the number argument with - or -- (= single dash or double dash)
    std::cout << k5::parse_count( argv ) << '\n';

    std::puts( "----------------\n" );
    /// parse_all:   returns a vector of string of all main argument that have - or --
    for( const std::string& s : k5::parse_all( argv ) ){
        std::cout << s << '\n';
    }

    std::puts( "----------------\n" );
    /// parse_all_to: acts like parse_all but it is void
    std::vector< std::string > vs;
    k5::parse_all_to( argv, vs );
    for( const std::string& s : vs ){
        std::cout << s << '\n';
    }

return 0;}

/* the output:

 ideas   ./temp one two three
0
----------------

----------------

 ideas   ./temp -one --two ---three
3
----------------

-one
--two
--three
----------------

-one
--two
--three
 ideas   ./temp -one a --two a b ---three a b c
3
----------------

-one a
--two a b
--three a b c
----------------

-one a
--two a b
--three a b c


*/
 ```
 - `parse_index`
 - `parse_index_to`

 ```C++
 #include <iostream>
#include "rfc/parse.hpp"

int main( int argc, const char** argv ){

    /// parse_index:        parse a specific argument, returns a single string
    std::cout << k5::parse_index( argv, 2 ) << '\n';

    std::puts( "---------------------------" );
    /// parse_index_to      like above,but is is void
    std::string main_arg_index_2;
    k5::parse_index_to( argv, main_arg_index_2, 2 );
    std::cout << main_arg_index_2 << '\n';

    // note:
    // index 0: -one a
    // index 1: --two a b
    // index 2: --three a b c
    // index 3: --three a b c d

return 0;}

/* the output:

 ideas $  ./temp -one a --two a b ---three a b c
--three a b c
---------------------------
--three a b c
 ideas $  ./temp -one a --two a b ---three a b c ----four a b c d
--three a b c
---------------------------
--three a b c

*/
 ```
