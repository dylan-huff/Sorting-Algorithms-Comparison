# Sorting-Algorithms-Comparison
This program implements various sorting algorithms for the purpose of comparing their performance against each other.
The algorithms used are bubble sort, merge sort, and radix sort. These algorithms are used to represent three categories of run time:
O(n^2), O(n log n), and O(n). To test the algorithms, an array of size 5000 will be populated with random integers and then that array
will be copied to use for each algorithm to make sure they are using the exact same array. While making the program, I used an array of
size 20 to make sure the algorithms were working properly. Inside of the algorithms a counter was implemented to keep track of the number
of comparisons each algorithm had to make. A clock was also implemented to compare actual run times as well, but this cannot be taken for
truth all the time because of all the variables involving the system and hardware that could effect the time, this is why the counters were
also implemented. The algorithms are ran 20 times, with each run having a new set of numbers to populate the array so we can see how the
algorithms perform over multiple runs.

