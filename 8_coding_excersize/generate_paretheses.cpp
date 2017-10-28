class Solution {
public:
    vector<string> generateParenthesis(int n) {
        std::vector<std::string> vec_res;
        searchSolution(n, n, "", vec_res);
        return vec_res;
    }
    
    /* Using DFS */
    void searchSolution(int left, int right, std::string str_res, std::vector<std::string>& vec_res){
        /******************************************************************************************************
         * Becuase left parethese has to be placed first, so for the left amount of parentheses, left's number
         * must less than the right's.
         ******************************************************************************************************/
        if(left > right)  return;
        if(left == 0 && right == 0)  vec_res.push_back(str_res);
        else {
            if(left > 0) searchSolution(left - 1, right, str_res + "(", vec_res);
            if(right > 0)  searchSolution(left, right - 1, str_res + ")", vec_res);
        }
    }
};