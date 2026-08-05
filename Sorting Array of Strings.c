#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Sorts the strings in lexicographically non-decreasing order
int lexicographic_sort(const char* a, const char* b) {
    return strcmp(a, b);
}

// 2. Sorts the strings in lexicographically non-increasing order
int lexicographic_sort_reverse(const char* a, const char* b) {
    return strcmp(b, a);
}

// Helper function to count distinct characters in a string
int count_distinct(const char* str) {
    int distinct_count = 0;
    int hash[26] = {0}; // Track lowercase English letters
    
    for (int i = 0; str[i] != '\0'; i++) {
        int index = str[i] - 'a';
        if (index >= 0 && index < 26 && hash[index] == 0) {
            hash[index] = 1;
            distinct_count++;
        }
    }
    return distinct_count;
}

// 3. Sorts by number of distinct characters, breaks ties lexicographically
int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int count_a = count_distinct(a);
    int count_b = count_distinct(b);
    
    if (count_a != count_b) {
        return count_a - count_b;
    }
    return strcmp(a, b);
}

// 4. Sorts by length, breaks ties lexicographically
int sort_by_length(const char* a, const char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    
    if (len_a != len_b) {
        return len_a - len_b;
    }
    return strcmp(a, b);
}

// Generic sorting function using standard Selection/Bubble Sort logic
void string_sort(const char **arr, const int cnt, int (*cmp_func)(const char* a, const char* b)) {
    for (int i = 0; i < cnt - 1; i++) {
        for (int j = i + 1; j < cnt; j++) {
            // If the comparison function returns a value greater than 0, swap the pointers
            if (cmp_func(arr[i], arr[j]) > 0) {
                const char* temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}
