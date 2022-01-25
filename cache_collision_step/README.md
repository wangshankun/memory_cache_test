#  跨界距离测试

```
由于 L2 cache 有 16,384 slots (LEVEL2_CACHE_SIZE除以LEVEL2_CACHE_LINESIZE)，而 each memory set 需要 16 cache slot ,
所以 memory 可以划分为 1024 sets。因此，chunk index 的低10 bit（2^10 == 1024）可以用于标定当前 memory chunk 属于哪个 memory set。
因此造成的后果是，以 65535 bytes（1024 * 64）为倍数差的 memory chunk 将会竞争同一个 cache slot。
为了直观的了解 Cache associativity 的影响，需要在同样的 memory set 中重复访问超过 16 个元素

```
