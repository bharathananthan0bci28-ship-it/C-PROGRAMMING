unsigned char is_prime[50001];


void sieve_of_eratosthenes() 
{
    static int need_init = 1;
    if (!need_init) 
        return;

    memset(is_prime, 1, sizeof(is_prime));
    need_init = 0;
    
    is_prime[0] = is_prime[1] = 0;
    
    for (int p = 2; p * p < 50001; ++p) 
    {
        if (is_prime[p]) 
            for (int i = p * p; i < 50001; i += p) 
                is_prime[i] = 0;
    }
}


int primeSubarray(int *nums, int n, int k) 
{
    sieve_of_eratosthenes();

    int max_queue[n];
    int max_front = 0, max_rear = 0;

    int min_queue[n];
    int min_front = 0, min_rear = 0;
    

    int ret = 0;

    int left = 0,
        count = 0,
        prev_prime = -1,
        last_prime;
    for (int i = 0; i < n; ++i) 
    {
        if (is_prime[nums[i]]) 
        {
            if (prev_prime == -1)
                prev_prime = i;
            else
                prev_prime = last_prime;
            last_prime = i;

            ++count;
            while (max_front < max_rear && nums[max_queue[max_rear - 1]] < nums[i]) 
                --max_rear;

            while (min_front < min_rear && nums[min_queue[min_rear - 1]] > nums[i]) 
                --min_rear;

            max_queue[max_rear++] = i;
            min_queue[min_rear++] = i;
        }

        if (!count)
            continue;

        while(nums[max_queue[max_front]] - nums[min_queue[min_front]] > k)
        {
            ++left;
            if (max_queue[max_front] < left)
            {
                ++max_front;
                --count;
            }
            if (min_queue[min_front] < left)
            {
                ++min_front;
                --count;
            }
        }

        if (count < 2)
            continue;
        
        ret += prev_prime - left + 1;
    }


    return ret;
}
