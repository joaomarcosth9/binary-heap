# binary-heap
A binary heap (min heap) implementation in C. I've implemented some C++ like structures like `std::pair` and `std::vector` to help me.

Heap operations time complexity:
- Push: O(log(n))
- Top: O(1)
- Pop: O(log(n))

I used it in a Dijkstra algorithm to solve this simple problem on codeforces:
- https://codeforces.com/problemset/problem/20/C

Obs: It worked, but way slower than with a C++ `std::priority_queue`:

<img width="1066" alt="Screenshot 2023-03-01 at 00 56 16" src="https://user-images.githubusercontent.com/70975757/222041230-31d90e3b-970e-4367-b136-8afce4fd80a3.png">
