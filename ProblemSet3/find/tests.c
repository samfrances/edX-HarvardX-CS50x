#include <stdio.h>

#include "helpers.h"

void test_search();
void print_array(int list[], int size);
void test_sort();

int main (int argc, string argv[])
{
    test_search();
    test_sort();
}

void print_array(int list[], int size)
{
    if (size == 0) {
        printf("{}\n");
        return;
    }
    
    printf("{");
    for (int i = 0; i < size-1; i++) {
        printf("%i, ", list[i]);
    }
    printf("%i}\n", list[size-1]);
}

void test_search()
{
    int list0[] = {};
    int list1[] = {327, 44, 7, 1000, 33, 3, 99};
    int list2[] = {571, 464, 140, 639, 605, 556, 293, 650, 235, 17, 347, 304, 680, 389, 132};
    int list3[] = {554, 525};
    int list4[] = {708, 2, 957, 765, 17, 463, 268, 130, 291, 762, 649, 523, 39};
    
    printf("Testing search function\n");
    
    // test 0
    sort(list0, 0);
    if (search(5, list0, 0)) {
        printf("Failed test 0\n");
    }
    else {
        printf("Passed test 0\n");
    }    

    // test 1
    sort(list1, 7);
    if (search(5, list1, 7)) {
        printf("Failed test 1\n");
    }
    else {
        printf("Passed test 1\n");
    }
    
    // test 2
    if (search(44, list1, 7)) {
        printf("Passed test 2\n");
    }
    else {
        printf("Failed test 2\n");
    }
    
    // test3
    sort(list2, 15);
    if (search(132, list2, 15)) {
        printf("Passed test 3\n");
    }
    else {
        printf("Failed test 3\n");
    }

    // test4
    if (search(13, list2, 15)) {
        printf("Failed test 4\n");
    }
    else {
        printf("Passed test 4\n");
    }
    
    // test4
    sort(list3, 2);
    if (search(554, list3, 2)) {
        printf("Passed test 4\n");
    }
    else {
        printf("Failed test 4\n");
    }
    
    // test5
    if (search(525, list3, 2)) {
        printf("Passed test 5\n");
    }
    else {
        printf("Failed test 5\n");
    }

    // test6
    if (search(25, list3, 2)) {
        printf("Failed test 6\n");
    }
    else {
        printf("Passed test 6\n");
    }

    // test7
    sort(list4, 13);
    if (search(17, list4, 13)) {
        printf("Passed test 7\n");
    }
    else {
        printf("Failed test 7\n");
    }

    // test8
    if (search(7, list4, 13)) {
        printf("Failed test 8\n");
    }
    else {
        printf("Passed test 8\n");
    }
    printf("\n");
}

void test_sort()
{
    int len;
    
    printf("Testing sort function\n");
    
    // test1
    printf("\nTest 1\n");
    int list1[] = {313, 37, 494, 814, 348, 402, 12, 313, 823, 151, 678};
    len = 11;
    print_array(list1, len);
    sort(list1, len);
    print_array(list1, len);
    
    // test2
    printf("\nTest 2\n");
    int list2[] = {491, 301, 746, 604, 608};
    len = 5;
    print_array(list2, len);
    sort(list2, len);
    print_array(list2, len);
    
    // test3
    printf("\nTest 3\n");
    int list3[] = {};
    len = 0;
    print_array(list3, len);
    sort(list3, len);
    print_array(list3, len);
    
    // test4
    printf("\nTest 4\n");
    int list4[] = {47};
    len = 1;
    print_array(list4, len);
    sort(list4, len);
    print_array(list4, len);
    
    // test5
    printf("\nTest 5\n");
    int list5[] = {1,2,3};
    len = 3;
    print_array(list5, len);
    sort(list5, len);
    print_array(list5, len);
    
    // test6
    printf("\nTest 6\n");
    int list6[] = {3,2,1};
    len = 3;
    print_array(list6, len);
    sort(list6, len);
    print_array(list6, len);
}