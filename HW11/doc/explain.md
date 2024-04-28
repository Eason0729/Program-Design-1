# Chart with suffix -1.png

In those three chart, we know that they all have similar instruction, the distribution wasn't similar to linklist, but the average time is.

It's because two reason, one cause high baseline time, another is the data structure I use.

The first reason which cause high baseline time is bad IO optimization, It read from file for every prefix, even worse, I open file to write the chart before calling `usize end=rdtsc_64bits();`, which block.

The second reason is the addition of HashMap, rather than placing linklist(xor linklist) in vector(slice), I placed linklist in a custom hashmap, moreover, when the key is missing in the hashmap, the `hash_get()` function iterating all elements in hashmap, and hash collusion was discovered in one of the bucket, so there are several operation took significantly more time.

# Chart with suffix -2.png

After optimize some IO, I get correct result for combination of hashmap and linklist.

