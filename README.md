# Quiz 2
## Subset Sum Problem
Given a set of non-negative integers, and a value sum, determine if there is a subset of the given set with sum equal to given sum.

My solution involves creating an array of precomputed solutions that encompasses which takes O(N*LEN) time to create and O(N) space where N is the sum of the entire array and LEN is the # of elements in the array.

A query for this problem asks whether a given sum L is possible given the current array. After precomputing the array of length LEN, all queries take O(1) time. 