bool isMatch_v1(string s, string p) {
    if(p.empty())    
        return s.empty();
    if(p.size() > 1 && p[1] == '*') {
        /* If 's' is empty, matching fails. */
        bool is_s_empty = !s.empty();
        /* If the first char in 's' match pattern 'p'(equal or p[0] is wildcard) */
        bool is_1st_match = (s[0] == p[0] || p[0] == '.');
        /* If 1st char in 's' match pattern 'p', is the left part of 's' still matching? */
        /* Becuase the second char in 'p' is a wildcard which mean can repeat any times. */
        bool is_sub_match = isMatch(s.substr(1), p);
        /* If the case, in which the first char in 'p' repeat no time, 's' match 'p'?    */
        bool is_skip_head_match = isMatch(s, p.substr(2));
        return (is_s_empty && is_1st_match && is_sub_match) || is_skip_head_match;
    }
    else {
        return !s.empty() 
            && (s[0] == p[0] || p[0] == '.') 
            && isMatch(s.substr(1), p.substr(1));
    }
}

bool isMatch_v2(string s, string p) {
    if( p.empty() )  return s.empty();
    if( p.size() == 1){
        return ( s.size() == 1 && (s[0] == p[0] || p[0] = '.') );
    }
    if( p[1] != '*' ) {
        if( s.empty() )  return false;
        return ( s[0] == p[0] || p[0] == '.' ) && isMatch(s.substr(1), p.substr(1));
    }

    while( !s.empty() && ( s[0] == p[0] || p[0] == '.' ) ) {
        if( isMatch(s, p.substr(2)) )  return true;
        s = s.substr(1);
    }

    return isMatch(s, p.substr(2));
}