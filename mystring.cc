//#include"stringfwd.h"
#include"Base_string.h"
#include"Char_traits.h"
#include"Base_string.cc"
#include<iostream>
#include<utility>

using namespace String;
int main(){
    using std::cout; 
    using std::endl;
    const char book[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmn";
    String::Basic_string<char,Char_traits<char>,std::allocator<char>> S(book);
    const String::Basic_string<char,Char_traits<char>,std::allocator<char>> T("ghijk");
    String::Basic_string<char,Char_traits<char>,std::allocator<char>> TT;

    auto one = T.rbegin();
    auto two = T.rend();
    cout << std::distance(S.begin(), S.end()) << endl;
    using namespace std::rel_ops;
    //if(iitr == T.begin()) cout << "hello\n";
    //if(S.begin()!=S.end()) cout << "world\n";
    //auto itr_end = S.end();
    //cout << itr_end - T.begin() << endl;
    //cout << itr.base() << endl;
    //cout << itr_end.base() << endl;
    return 0;
}