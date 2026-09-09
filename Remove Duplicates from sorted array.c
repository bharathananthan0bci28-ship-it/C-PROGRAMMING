int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }
    
    int k = 1; // Initializes the count of unique elements
    
    for (int i = 1; i < numsSize; i++) {
        // If the current element is different from the previous one, it's unique
        if (nums[i] != nums[i - 1]) {
            nums[k] = nums[i]; // Move it to the next available unique position
            k++;
        }
    }
    
    return k;
}
