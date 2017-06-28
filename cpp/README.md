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

 - `parse_index_all`
 - `parse_index_all_to`

 ```C++
#include <iostream>
#include "rfc/parse.hpp"

int main( int argc, const char** argv ){

    /// parse_index_all     parse a specific argument, but returns a vector of string of all its options
    for( const std::string& s : k5::parse_index_all( argv, 2 ) ){
        std::cout << s << '\n';
    }

    /// parse_index_all_to  like above, but it is void
    // std::vector< std::string > vs;
    // k5::parse_index_all_to( argv, vs, 2 );

return 0;}

/* the output:

 ideas $  ./temp -one a --two a b ---three a b c ----four a b c d
--three
a
b
c
 ideas $  ./temp -one a --two a b ---three aaa bbb ccc ----four a b c d
--three
aaa
bbb
ccc
 ideas $  ./temp -one a --two a b -three aaa bbb ccc ----four a b c d
-three
aaa
bbb
ccc
 ideas $  ./temp -one a --two a b three aaa bbb ccc ----four a b c d
--four
a
b
c
d
 ideas $


*/

 ```
 - `parse_option`
 - `parse_option_to`
 - `parse_option_all`
 - `parse_option_all_to`

 ```C++
#include <iostream>
#include "rfc/parse.hpp"

int main( int argc, const char** argv ){

    /// parse_option        acts like parse_index, except looking for an argument by getting a string, and return a single string
    const std::string s = k5::parse_option( argv, "--three" );
    std::cout << s << '\n';

    /// parse_option_to     like above, but is is void

    std::puts( "----------------------" );
    /// parse_option_all    like above, but return a vector of string for all part of that option
    std::vector< std::string > vs = k5::parse_option_all( argv, "--three" );
    for( const auto& s : vs ){
        std::cout << s << '\n';
    }

    /// parse_option_all_to like above, but it is void

return 0;}

/* the output:

 ideas $  # there is not --three, so there would not be any output
 ideas $  ./temp -one a --two a b three aaa bbb ccc ----four a b c d

----------------------

 ideas $
 ideas $  ./temp -one a --two a b --three aaa bbb ccc ----four a b c d
--three aaa bbb ccc
----------------------
--three
aaa
bbb
ccc
 ideas $  ./temp -one a --two a b --three 1 2 3 ----four a b c d
--three 1 2 3
----------------------
--three
1
2
3
 ideas $

*/
```
