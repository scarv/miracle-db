
# Target Platforms

*A list of candidate devices and platforms on which to perform these
experiments*

**FPGA + Xilinx Microblaze:**
- Use the Sasebo FPGA platform
- Use Xilinx own Microblaze configurable CPU.
- The CPU has a *configurable* pipeline depth, and it's micro-architecture
  is documented in 
  [Xilinx UG984](https://www.xilinx.com/support/documentation/sw_manuals/xilinx2018_3/ug984-vivado-microblaze-ref.pdf).
  - Pipeline length: 3/5/8
- We can configure the surrounding AXI interconnect as well to add register
  stages to the memory busess.

**SCALE Boards:**

- ARM M0/3/4 core support.
- Possibly RISC-V support?
- Represent real world systems.
- Mostly un-documented internals of the CPUs themselves, some clues
  about pipeline information.


Note:
- According to [1], the M3 NOP instruction is actually killed in the
  decode stage, and does not affect later pipeline registers.
  This sort of effect is *extremely* important to identify.

**SiFive HiFive board:**

- Rocket chip based microcontroller
- Would need to mod it to get a scope onto the power trace.

**FPGA + PicoRV32:**

- A multi-cycle micro-architecture CPU.
- Interesting to run the same benchmarks on a multi-cycle machine and
  see what the differences are.

**FPGA + SCARV in house CPU:**

- 5 Stage pipeline
- Total control over internal micro-architecture.
- Very useful for logic gating experiments.
- Will eventually be used as host for pipeline XCrypto implementation,
  so useful to profile as a baseline anyway.

---

**References:**
1. Microarchitectural power simulator for leakage assessment of cryptographic
   software on ARM Cortex-M3 Processors. Yan Le Corre, Johann Gro\Bschadl and
   Daniel Dinu.