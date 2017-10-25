#ifndef _FIND_PRIME_H_
#define _FIND_PRIME_H_

#include <vector>

/* Finding all prime numbers less than 'n_upper_bound' */
std::vector<int> find_primes(int n_upper_bound) {
   std::vector<int> vec_prime_nb;
   if(n_upper_bound < 0 || n_upper_bound == 1) {
      return vec_prime_nb;
   }
   if(n_upper_bound == 3) {
      vec_prime_nb.push_back(2);
      return vec_prime_nb;
   }

   char* p_prime_nb = new char[n_upper_bound];
   memset(p_prime_nb, 1, sizeof(char) * n_upper_bound);

   for(int i = 2; i * i < n_upper_bound; ++i) {
      if(!p_prime_nb[i])  continue;

      for(int j = i * i; j < n_upper_bound; j += i) {
         p_prime_nb[j] = 0;
      }
   }

   for(int i = 2; i < n_upper_bound; ++i) {
      if(p_prime_nb[i])
         vec_prime_nb.push_back(i);
   }

   delete[] p_prime_nb;
   p_prime_nb = NULL;

   return vec_prime_nb;
}

#endif