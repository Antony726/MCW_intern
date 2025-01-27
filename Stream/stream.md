# Streaming Engine
<P>A Streaming Engine is a feature of the C7000 CPU core that aids in high-speed loading of data from memory (L2 or higher) to the functional units in the CPU. </p>
<h3> It increases </h2>
<li> Thrughput
<li> Performance
<p>They prefetch data from memory to a location near the CPU so the data can be accessed faster.</p>
<p>The streaming engine doesn’t use the L1 cache, instead accessing memory directly, freeing up cache space and reducing cache misses for other data the CPU needs.</p>
<h3>The best way to use the Streaming Engines is with data that has been placed into <mark>L2 memory</mark>.</h3>
<h3>The Streaming Engine feature supports up to a 6D address access pattern.</h3>

<p>Using one or both of the Streaming Engines may also limit the number of instructions required to calculate an address used for a load instruction. This may allow the compiler to perform loop transformation optimizations called loop coalescing and loop collapsing, which may lead to a larger portion of the loop nest getting software pipelined, which can lead to improved performance.</p>