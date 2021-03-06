// ==============================================================
// File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2016.1
// Copyright (C) 1986-2016 Xilinx, Inc. All Rights Reserved.
// 
// ==============================================================

// control_bus
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of a_offset_address
//        bit 31~0 - a_offset_address[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of b_offset_address
//        bit 31~0 - b_offset_address[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of c_offset_address
//        bit 31~0 - c_offset_address[31:0] (Read/Write)
// 0x24 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMXV_STREAM_CONTROL_BUS_ADDR_AP_CTRL               0x00
#define XMXV_STREAM_CONTROL_BUS_ADDR_GIE                   0x04
#define XMXV_STREAM_CONTROL_BUS_ADDR_IER                   0x08
#define XMXV_STREAM_CONTROL_BUS_ADDR_ISR                   0x0c
#define XMXV_STREAM_CONTROL_BUS_ADDR_A_OFFSET_ADDRESS_DATA 0x10
#define XMXV_STREAM_CONTROL_BUS_BITS_A_OFFSET_ADDRESS_DATA 32
#define XMXV_STREAM_CONTROL_BUS_ADDR_B_OFFSET_ADDRESS_DATA 0x18
#define XMXV_STREAM_CONTROL_BUS_BITS_B_OFFSET_ADDRESS_DATA 32
#define XMXV_STREAM_CONTROL_BUS_ADDR_C_OFFSET_ADDRESS_DATA 0x20
#define XMXV_STREAM_CONTROL_BUS_BITS_C_OFFSET_ADDRESS_DATA 32

