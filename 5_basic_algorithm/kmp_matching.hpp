void get_next(const char* p, int* next) {
	    int n_len = strlen(p);
	    if(n_len <= 0)    return ;
	    next[0] = -1;
    
	    int k = -1;    // 'next[]' array's value and index for 
	    int j = 0;     // Pattern string's index

	    while(j < n_len - 1) {
	    	if(k == -1 || p[k] == p[j]) {
		    	++j;
		    	++k;
		    	if(p[j] != p[k])    next[j] = k;
		    	else next[j] = next[k];
		    } else {
			    k = next[k];
		    }
	    }
    }

    int kmp_searching(const char* s, const char* p) {
    	if(s == NULL || p == NULL)    return -1;

	    int n_len_s = strlen(s);
	    int n_len_p = strlen(p);
        
        if(n_len_p == 0)    return 0;
	    if(n_len_p == 0 || n_len_s == 0)    return -1;

	    int* p_next = new int[n_len_p];
	    get_next(p, p_next);
	    int i = 0, j = 0;
	    while(i < n_len_s && j < n_len_p) {
		    if(j == -1 || s[i] == p[j]) {
		     	++i;
		    	++j;
		    }
		    else {
			    j = p_next[j];
		    }
	    }

	    delete[] p_next;
	    p_next = NULL;
	
	    if(j == n_len_p)    return i - j;
	    else return -1;
    }