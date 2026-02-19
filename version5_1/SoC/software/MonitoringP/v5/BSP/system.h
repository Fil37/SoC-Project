/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_qsys_0' in SOPC Builder design 'nios_sys'
 * SOPC Builder design path: C:/Users/fessome/Desktop/SoCTP/version5_1/SoC/nios_sys.sopcinfo
 *
 * Generated: Tue Feb 03 12:17:08 CET 2026
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * ADC_Core_0 configuration
 *
 */

#define ADC_CORE_0_BASE 0x300
#define ADC_CORE_0_IRQ -1
#define ADC_CORE_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ADC_CORE_0_NAME "/dev/ADC_Core_0"
#define ADC_CORE_0_SPAN 4
#define ADC_CORE_0_TYPE "ADC_Core"
#define ALT_MODULE_CLASS_ADC_Core_0 ADC_Core


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_qsys"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x2820
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1b
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x4000020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x1b
#define ALT_CPU_NAME "nios2_qsys_0"
#define ALT_CPU_RESET_ADDR 0x4000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x2820
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x1b
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x4000020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x1b
#define NIOS2_RESET_ADDR 0x4000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ADC_CORE
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_NIOS2_QSYS
#define __PWM_COMPONENT
#define __REG16_COMPONENT


/*
 * LEDS configuration
 *
 */

#define ALT_MODULE_CLASS_LEDS altera_avalon_pio
#define LEDS_BASE 0x3000
#define LEDS_BIT_CLEARING_EDGE_REGISTER 0
#define LEDS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LEDS_CAPTURE 0
#define LEDS_DATA_WIDTH 8
#define LEDS_DO_TEST_BENCH_WIRING 0
#define LEDS_DRIVEN_SIM_VALUE 0
#define LEDS_EDGE_TYPE "NONE"
#define LEDS_FREQ 50000000
#define LEDS_HAS_IN 0
#define LEDS_HAS_OUT 1
#define LEDS_HAS_TRI 0
#define LEDS_IRQ -1
#define LEDS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LEDS_IRQ_TYPE "NONE"
#define LEDS_NAME "/dev/LEDS"
#define LEDS_RESET_VALUE 0
#define LEDS_SPAN 16
#define LEDS_TYPE "altera_avalon_pio"


/*
 * SD_RAM configuration
 *
 */

#define ALT_MODULE_CLASS_SD_RAM altera_avalon_new_sdram_controller
#define SD_RAM_BASE 0x4000000
#define SD_RAM_CAS_LATENCY 3
#define SD_RAM_CONTENTS_INFO
#define SD_RAM_INIT_NOP_DELAY 0.0
#define SD_RAM_INIT_REFRESH_COMMANDS 2
#define SD_RAM_IRQ -1
#define SD_RAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SD_RAM_IS_INITIALIZED 1
#define SD_RAM_NAME "/dev/SD_RAM"
#define SD_RAM_POWERUP_DELAY 100.0
#define SD_RAM_REFRESH_PERIOD 15.625
#define SD_RAM_REGISTER_DATA_IN 1
#define SD_RAM_SDRAM_ADDR_WIDTH 0x18
#define SD_RAM_SDRAM_BANK_WIDTH 2
#define SD_RAM_SDRAM_COL_WIDTH 9
#define SD_RAM_SDRAM_DATA_WIDTH 16
#define SD_RAM_SDRAM_NUM_BANKS 4
#define SD_RAM_SDRAM_NUM_CHIPSELECTS 1
#define SD_RAM_SDRAM_ROW_WIDTH 13
#define SD_RAM_SHARED_DATA 0
#define SD_RAM_SIM_MODEL_BASE 0
#define SD_RAM_SPAN 33554432
#define SD_RAM_STARVATION_INDICATOR 0
#define SD_RAM_TRISTATE_BRIDGE_SLAVE ""
#define SD_RAM_TYPE "altera_avalon_new_sdram_controller"
#define SD_RAM_T_AC 5.5
#define SD_RAM_T_MRD 3
#define SD_RAM_T_RCD 20.0
#define SD_RAM_T_RFC 70.0
#define SD_RAM_T_RP 20.0
#define SD_RAM_T_WR 14.0


/*
 * SWs configuration
 *
 */

#define ALT_MODULE_CLASS_SWs altera_avalon_pio
#define SWS_BASE 0x3010
#define SWS_BIT_CLEARING_EDGE_REGISTER 0
#define SWS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SWS_CAPTURE 0
#define SWS_DATA_WIDTH 4
#define SWS_DO_TEST_BENCH_WIRING 0
#define SWS_DRIVEN_SIM_VALUE 0
#define SWS_EDGE_TYPE "NONE"
#define SWS_FREQ 50000000
#define SWS_HAS_IN 1
#define SWS_HAS_OUT 0
#define SWS_HAS_TRI 0
#define SWS_IRQ -1
#define SWS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SWS_IRQ_TYPE "NONE"
#define SWS_NAME "/dev/SWs"
#define SWS_RESET_VALUE 0
#define SWS_SPAN 16
#define SWS_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x3020
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x3020
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x3020
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "nios_sys"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x3020
#define JTAG_UART_IRQ 5
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * onchip_memory configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory altera_avalon_onchip_memory2
#define ONCHIP_MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY_BASE 0x1000
#define ONCHIP_MEMORY_CONTENTS_INFO ""
#define ONCHIP_MEMORY_DUAL_PORT 0
#define ONCHIP_MEMORY_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY_INIT_CONTENTS_FILE "nios_sys_onchip_memory"
#define ONCHIP_MEMORY_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY_IRQ -1
#define ONCHIP_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY_NAME "/dev/onchip_memory"
#define ONCHIP_MEMORY_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY_SIZE_VALUE 4096
#define ONCHIP_MEMORY_SPAN 4096
#define ONCHIP_MEMORY_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY_WRITABLE 1


/*
 * pwm_component_0 configuration
 *
 */

#define ALT_MODULE_CLASS_pwm_component_0 pwm_component
#define PWM_COMPONENT_0_BASE 0x100
#define PWM_COMPONENT_0_IRQ -1
#define PWM_COMPONENT_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PWM_COMPONENT_0_NAME "/dev/pwm_component_0"
#define PWM_COMPONENT_0_SPAN 4
#define PWM_COMPONENT_0_TYPE "pwm_component"


/*
 * reg16_component_0 configuration
 *
 */

#define ALT_MODULE_CLASS_reg16_component_0 reg16_component
#define REG16_COMPONENT_0_BASE 0x0
#define REG16_COMPONENT_0_IRQ -1
#define REG16_COMPONENT_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define REG16_COMPONENT_0_NAME "/dev/reg16_component_0"
#define REG16_COMPONENT_0_SPAN 2
#define REG16_COMPONENT_0_TYPE "reg16_component"

#endif /* __SYSTEM_H_ */
