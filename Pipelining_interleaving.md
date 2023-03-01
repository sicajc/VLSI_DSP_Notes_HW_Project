# Interleaving, self-timed circuit
1. Interleaving actually increases throughput just like pipeline, by replicating the HW of your critical components circuit we can further reduce the critical bottleneck.
2. The effect of N-way interleaving just works like N-stage pipelining, however, additional HW for arithmetic units and selector is needed to implement such design
3. Asynchronous, locally-timed system can be used using transition signaling.
4. However, the self-timed circuit is not reliable.
5. We usually use local handshaking instead of controllly all blocks using main control units.
6. Whenever you want to further increase your throughput using pipelining, pipelined version of arithmetic units IP can be found on designware library.