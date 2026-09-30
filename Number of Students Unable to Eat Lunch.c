int countStudents(int* students, int studentsSize, int* sandwiches, int sandwichesSize) {
    int counts[2] = {0, 0}; // counts[0] for circular, counts[1] for square
    
    // Count preferences of all students
    for (int i = 0; i < studentsSize; i++) {
        counts[students[i]]++;
    }
    
    // Process each sandwich in the stack
    for (int i = 0; i < sandwichesSize; i++) {
        // If no students want the current sandwich type, stop
        if (counts[sandwiches[i]] > 0) {
            counts[sandwiches[i]]--;
        } else {
            return sandwichesSize - i; // Remaining sandwiches/students who cannot eat
        }
    }
    
    return 0; // All students ate
}
