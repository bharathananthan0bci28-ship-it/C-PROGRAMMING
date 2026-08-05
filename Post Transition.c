#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 6

struct package {
    char* id;
    int weight;
};

typedef struct package package;

struct post_office {
    int min_weight;
    int max_weight;
    package* packages;
    int packages_count;
};

typedef struct post_office post_office;

struct town {
    char* name;
    post_office* offices;
    int offices_count;
};

typedef struct town town;

// 1. Prints all packages inside a given town with correct tab formatting
void print_all_packages(town t) {
    printf("%s:\n", t.name);
    for (int i = 0; i < t.offices_count; i++) {
        printf("\t%d:\n", i);
        for (int j = 0; j < t.offices[i].packages_count; j++) {
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
    }
}

// 2. Ships all packages meeting target weight conditions while retaining rejections safely
void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
    post_office* src = &source->offices[source_office_index];
    post_office* tgt = &target->offices[target_office_index];
    
    int accepted_count = 0;
    int rejected_count = 0;
    
    for (int i = 0; i < src->packages_count; i++) {
        int w = src->packages[i].weight;
        if (w >= tgt->min_weight && w <= tgt->max_weight) {
            accepted_count++;
        } else {
            rejected_count++;
        }
    }
    
    package* accepted = accepted_count > 0 ? malloc(accepted_count * sizeof(package)) : NULL;
    package* rejected = rejected_count > 0 ? malloc(rejected_count * sizeof(package)) : NULL;
    
    int a_idx = 0, r_idx = 0;
    for (int i = 0; i < src->packages_count; i++) {
        int w = src->packages[i].weight;
        if (w >= tgt->min_weight && w <= tgt->max_weight) {
            accepted[a_idx++] = src->packages[i];
        } else {
            rejected[r_idx++] = src->packages[i];
        }
    }
    
    if (accepted_count > 0) {
        tgt->packages = realloc(tgt->packages, (tgt->packages_count + accepted_count) * sizeof(package));
        for (int i = 0; i < accepted_count; i++) {
            tgt->packages[tgt->packages_count + i] = accepted[i];
        }
        tgt->packages_count += accepted_count;
    }
    
    free(src->packages);
    src->packages = rejected;
    src->packages_count = rejected_count;
    
    free(accepted);
}

// 3. Traverses towns to identify the one containing the highest absolute number of packages
town town_with_most_packages(town* towns, int towns_count) {
    int max_packages = -1;
    int max_idx = 0;
    
    for (int i = 0; i < towns_count; i++) {
        int current_packages = 0;
        for (int j = 0; j < towns[i].offices_count; j++) {
            current_packages += towns[i].offices[j].packages_count;
        }
        if (current_packages > max_packages) {
            max_packages = current_packages;
            max_idx = i;
        }
    }
    return towns[max_idx];
}

// 4. Returns a pointer reference to a town structure by scanning for a name match
town* find_town(town* towns, int towns_count, char* name) {
    for (int i = 0; i < towns_count; i++) {
        if (strcmp(towns[i].name, name) == 0) {
            return &towns[i];
        }
    }
    return NULL;
}

int main() {
    int towns_count;
    if (scanf("%d", &towns_count) != 1) return 0;
    
    town* towns = malloc(towns_count * sizeof(town));
    for (int i = 0; i < towns_count; i++) {
        towns[i].name = malloc(MAX_STRING_LENGTH * sizeof(char));
        scanf("%s", towns[i].name);
        scanf("%d", &towns[i].offices_count);
        towns[i].offices = malloc(towns[i].offices_count * sizeof(post_office));
        for (int j = 0; j < towns[i].offices_count; j++) {
            scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
            if (towns[i].offices[j].packages_count > 0) {
                towns[i].offices[j].packages = malloc(towns[i].offices[j].packages_count * sizeof(package));
                for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
                    towns[i].offices[j].packages[k].id = malloc(MAX_STRING_LENGTH * sizeof(char));
                    scanf("%s", towns[i].offices[j].packages[k].id);
                    scanf("%d", &towns[i].offices[j].packages[k].weight);
                }
            } else {
                towns[i].offices[j].packages = NULL;
            }
        }
    }
    
    int queries;
    if (scanf("%d", &queries) != 1) return 0;
    
    while (queries--) {
        int type;
        if (scanf("%d", &type) != 1) break;
        
        if (type == 1) {
            char town_name[MAX_STRING_LENGTH];
            scanf("%s", town_name);
            town* t = find_town(towns, towns_count, town_name);
            if (t != NULL) {
                print_all_packages(*t);
            }
        } else if (type == 2) {
            char source_name[MAX_STRING_LENGTH], target_name[MAX_STRING_LENGTH];
            int source_office_index, target_office_index;
            scanf("%s %d %s %d", source_name, &source_office_index, target_name, &target_office_index);
            
            town* source = find_town(towns, towns_count, source_name);
            town* target = find_town(towns, towns_count, target_name);
            
            send_all_acceptable_packages(source, source_office_index, target, target_office_index);
        } else if (type == 3) {
            town max_town = town_with_most_packages(towns, towns_count);
            printf("Town with the most number of packages is %s\n", max_town.name);
        }
    }
    
    // Deallocate heap arrays and strings cleanly
    for (int i = 0; i < towns_count; i++) {
        for (int j = 0; j < towns[i].offices_count; j++) {
            for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
                free(towns[i].offices[j].packages[k].id);
            }
            if (towns[i].offices[j].packages != NULL) {
                free(towns[i].offices[j].packages);
            }
        }
        free(towns[i].offices);
        free(towns[i].name);
    }
    free(towns);
    
    return 0;
}

