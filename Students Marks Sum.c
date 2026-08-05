#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int marks_summation(int* marks, int number_of_students, char gender) {
    int sum = 0;
    
    // If gender is 'b', start at index 0 (boys) and increment by 2
    // If gender is 'g', start at index 1 (girls) and increment by 2
    int start_index = (gender == 'b') ? 0 : 1;
    
    for (int i = start_index; i < number_of_students; i += 2) {
        sum += marks[i];
    }
    
    return sum;
}
