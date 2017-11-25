/**
 *  LeetCode 29:
 *    Divide two integers without using multiplication, division and mod operator. 
 *    If it is overflow, return MAX_INT. 
 *
 *  The thought is that if 'x/y = a', then there must exists 'k' that makes:
 *  x / (y * 2^k) = 1. So 'a' is '2^k'.
 */

int divide(int dividend, int divisor) {
        if(divisor == 0 || (dividend == INT_MIN && divisor == -1))    return INT_MAX;
        int n_sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
        
        long long int n_dividend = abs(static_cast<long long int>(dividend));
        long long int n_divisor  = abs(static_cast<long long int>(divisor));
        
        if(n_divisor == 1)    return n_sign == 1 ? n_dividend : -n_dividend;
        long long int n_res = 0;
        
        while(n_dividend >= n_divisor) {
            long long int n_temp_divisor = n_divisor, n_temp_res = 1;
            while(n_dividend > (n_temp_divisor << 1)) {
                n_temp_divisor <<= 1;
                n_temp_res <<= 1;
            }
            
            n_res += n_temp_res;
            n_dividend -= n_temp_divisor;
        }
        
        return n_sign == 1 ? n_res : -n_res;
    }
