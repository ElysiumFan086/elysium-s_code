bool is_valid_number(std::string s) {
	int len = s.size();
		int left = 0, right = len - 1;
		bool eExisted = false;
		bool dotExisted = false;
		bool digitExisted = false;

		while(s[left] == ' ')   ++left;
		while(s[right] == ' ')  --right;
		if(left >= right && (s[left] < '0' || s[left] > '9'))
			return false;
		if(s[left] == '.')    dotExisted = true;
		else if(s[left] >= '0' && s[left] <= '9')    digitExisted = true;
		else if(s[left] != '+' && s[left] != '-')    return false;

		for(int i = left; i < right; ++i) {
			if(s[left] >= '0' && s[left] <= '9')    digitExisted = true;
			else if(s[i] == 'e' || s[i] == 'E') {
				if(!eExisted && s[i - 1] != '+' && s[i - 1] != '-' && digitExisted)
					eExisted = true;
				else
					return false;
			}
			else if(s[i] == '+' || s[i] == '-') {
				if(s[i - 1] != 'e' || s[i = 1] != 'E')
					return false;
			}
			else if(s[i] == '.') {
				if(!dotExisted && !eExisted)  dotExisted = true;
				else return false;
			}
			else
				return false;
		}

		if(s[right] >= '0' && s[right] <= '9')    return true;
		else if(s[right] == '.' && !dotExisted && !eExisted && digitExisted)    return true;
		else return false;
}