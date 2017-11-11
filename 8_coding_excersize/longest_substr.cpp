/**
 * Given a string, find the length of the longest substring without repeating characters.
 * Examples:
 * Given "abcabcbb", the answer is "abc", which the length is 3.
 * Given "bbbbb", the answer is "b", with the length of 1.
 * Given "pwwkew", the answer is "wke", with the length of 3. 
 * Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 */

int lengthOfLongestSubstring(string s) {
        std::vector<int> hash_map(256, -1);
        int n_length = 0, n_left_pos = -1;
        for(int i = 0; i < s.size(); ++i) {
            n_left_pos = std::max(n_left_pos, hash_map[s[i]]);
            hash_map[s[i]] = i;
            
            n_length = std::max(n_length, i - n_left_pos);
        }
        
        return n_length;
}
