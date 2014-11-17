#ifndef EBI_SETUP_H_
#define EBI_SETUP_H_

#define FPGA_BASE_ADDR 0x80000000
#define SRAM_BASE_ADDR 0x84000000

#define OFFSET_INSTRUCTION_MEMORY (FPGA_BASE_ADDR + (1 << 17))
#define OFFSET_CONSTANT_MEMORY (FPGA_BASE_ADDR)
#define OFFSET_KERNEL_START (FPGA_BASE_ADDR + (1 << 18))

void ebi_setup();

#endif /* EBI_SETUP_H_ */
