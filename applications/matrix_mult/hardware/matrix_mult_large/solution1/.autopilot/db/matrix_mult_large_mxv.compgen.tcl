# This script segment is generated automatically by AutoPilot

# FIFO definition:
set ID 14
set FifoName FIFO_matrix_mult_large_mxv_a_fifo_V
set CoreName ap_simcore_fifo
set NumOfStage 2
set RegisteredInput 0
set DualClock 0
set Depth 1
set DataWd 32
set AddrWd 1
set impl_style auto
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_fifo] == "ap_gen_simcore_fifo"} {
eval "ap_gen_simcore_fifo { \
    id ${ID} \
    name ${FifoName} \
    corename ${CoreName} \
    op fifo \
    stage_num ${NumOfStage} \
    registered_input ${RegisteredInput} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    reset_level 1 \
    sync_rst true \
    dual_clk 0\
    depth ${Depth} \
}"
} else {
puts "@W \[IMPL-106\] Cannot find ap_gen_simcore_fifo, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $FifoName
}


if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_FIFO] == "::AESL_LIB_VIRTEX::xil_gen_FIFO"} {
eval "::AESL_LIB_VIRTEX::xil_gen_FIFO { \
    id ${ID} \
    name ${FifoName} \
    corename FIFO \
    op fifo \
    stage_num ${NumOfStage} \
    registered_input ${RegisteredInput} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    reset_level 1 \
    sync_rst true \
    dual_clk 0 \
    depth ${Depth} \
    style ${impl_style} \
}"
} else {
puts "@W \[IMPL-107\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_FIFO, check your platform lib"
}
}


# FIFO definition:
set ID 15
set FifoName FIFO_matrix_mult_large_mxv_c_offset_address_channel
set CoreName ap_simcore_fifo
set NumOfStage 2
set RegisteredInput 0
set DualClock 0
set Depth 2
set DataWd 32
set AddrWd 1
set impl_style auto
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_fifo] == "ap_gen_simcore_fifo"} {
eval "ap_gen_simcore_fifo { \
    id ${ID} \
    name ${FifoName} \
    corename ${CoreName} \
    op fifo \
    stage_num ${NumOfStage} \
    registered_input ${RegisteredInput} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    reset_level 1 \
    sync_rst true \
    dual_clk 0\
    depth ${Depth} \
}"
} else {
puts "@W \[IMPL-106\] Cannot find ap_gen_simcore_fifo, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $FifoName
}


if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_FIFO] == "::AESL_LIB_VIRTEX::xil_gen_FIFO"} {
eval "::AESL_LIB_VIRTEX::xil_gen_FIFO { \
    id ${ID} \
    name ${FifoName} \
    corename FIFO \
    op fifo \
    stage_num ${NumOfStage} \
    registered_input ${RegisteredInput} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    reset_level 1 \
    sync_rst true \
    dual_clk 0 \
    depth ${Depth} \
    style ${impl_style} \
}"
} else {
puts "@W \[IMPL-107\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_FIFO, check your platform lib"
}
}


# FIFO definition:
set ID 16
set FifoName FIFO_matrix_mult_large_mxv_c_fifo_V
set CoreName ap_simcore_fifo
set NumOfStage 2
set RegisteredInput 0
set DualClock 0
set Depth 1
set DataWd 32
set AddrWd 1
set impl_style auto
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_fifo] == "ap_gen_simcore_fifo"} {
eval "ap_gen_simcore_fifo { \
    id ${ID} \
    name ${FifoName} \
    corename ${CoreName} \
    op fifo \
    stage_num ${NumOfStage} \
    registered_input ${RegisteredInput} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    reset_level 1 \
    sync_rst true \
    dual_clk 0\
    depth ${Depth} \
}"
} else {
puts "@W \[IMPL-106\] Cannot find ap_gen_simcore_fifo, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $FifoName
}


if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_FIFO] == "::AESL_LIB_VIRTEX::xil_gen_FIFO"} {
eval "::AESL_LIB_VIRTEX::xil_gen_FIFO { \
    id ${ID} \
    name ${FifoName} \
    corename FIFO \
    op fifo \
    stage_num ${NumOfStage} \
    registered_input ${RegisteredInput} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    reset_level 1 \
    sync_rst true \
    dual_clk 0 \
    depth ${Depth} \
    style ${impl_style} \
}"
} else {
puts "@W \[IMPL-107\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_FIFO, check your platform lib"
}
}


# clear list
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_begin
    cg_default_interface_gen_bundle_begin
    AESL_LIB_XILADAPTER::native_axis_begin
}

# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 20 \
    name B \
    reset_level 1 \
    sync_rst true \
    dir I \
    corename B \
    op interface \
    ports { B_address0 { O 13 vector } B_ce0 { O 1 bit } B_d0 { O 32 vector } B_q0 { I 32 vector } B_we0 { O 1 bit } B_address1 { O 13 vector } B_ce1 { O 1 bit } B_d1 { O 32 vector } B_q1 { I 32 vector } B_we1 { O 1 bit } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'B'"
}
}


# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 17 \
    name memory_0 \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_memory_0 \
    op interface \
    ports { m_axi_memory_0_AWVALID { O 1 bit } m_axi_memory_0_AWREADY { I 1 bit } m_axi_memory_0_AWADDR { O 32 vector } m_axi_memory_0_AWID { O 1 vector } m_axi_memory_0_AWLEN { O 32 vector } m_axi_memory_0_AWSIZE { O 3 vector } m_axi_memory_0_AWBURST { O 2 vector } m_axi_memory_0_AWLOCK { O 2 vector } m_axi_memory_0_AWCACHE { O 4 vector } m_axi_memory_0_AWPROT { O 3 vector } m_axi_memory_0_AWQOS { O 4 vector } m_axi_memory_0_AWREGION { O 4 vector } m_axi_memory_0_AWUSER { O 1 vector } m_axi_memory_0_WVALID { O 1 bit } m_axi_memory_0_WREADY { I 1 bit } m_axi_memory_0_WDATA { O 32 vector } m_axi_memory_0_WSTRB { O 4 vector } m_axi_memory_0_WLAST { O 1 bit } m_axi_memory_0_WID { O 1 vector } m_axi_memory_0_WUSER { O 1 vector } m_axi_memory_0_ARVALID { O 1 bit } m_axi_memory_0_ARREADY { I 1 bit } m_axi_memory_0_ARADDR { O 32 vector } m_axi_memory_0_ARID { O 1 vector } m_axi_memory_0_ARLEN { O 32 vector } m_axi_memory_0_ARSIZE { O 3 vector } m_axi_memory_0_ARBURST { O 2 vector } m_axi_memory_0_ARLOCK { O 2 vector } m_axi_memory_0_ARCACHE { O 4 vector } m_axi_memory_0_ARPROT { O 3 vector } m_axi_memory_0_ARQOS { O 4 vector } m_axi_memory_0_ARREGION { O 4 vector } m_axi_memory_0_ARUSER { O 1 vector } m_axi_memory_0_RVALID { I 1 bit } m_axi_memory_0_RREADY { O 1 bit } m_axi_memory_0_RDATA { I 32 vector } m_axi_memory_0_RLAST { I 1 bit } m_axi_memory_0_RID { I 1 vector } m_axi_memory_0_RUSER { I 1 vector } m_axi_memory_0_RRESP { I 2 vector } m_axi_memory_0_BVALID { I 1 bit } m_axi_memory_0_BREADY { O 1 bit } m_axi_memory_0_BRESP { I 2 vector } m_axi_memory_0_BID { I 1 vector } m_axi_memory_0_BUSER { I 1 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 18 \
    name memory_3 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_memory_3 \
    op interface \
    ports { m_axi_memory_3_AWVALID { O 1 bit } m_axi_memory_3_AWREADY { I 1 bit } m_axi_memory_3_AWADDR { O 32 vector } m_axi_memory_3_AWID { O 1 vector } m_axi_memory_3_AWLEN { O 32 vector } m_axi_memory_3_AWSIZE { O 3 vector } m_axi_memory_3_AWBURST { O 2 vector } m_axi_memory_3_AWLOCK { O 2 vector } m_axi_memory_3_AWCACHE { O 4 vector } m_axi_memory_3_AWPROT { O 3 vector } m_axi_memory_3_AWQOS { O 4 vector } m_axi_memory_3_AWREGION { O 4 vector } m_axi_memory_3_AWUSER { O 1 vector } m_axi_memory_3_WVALID { O 1 bit } m_axi_memory_3_WREADY { I 1 bit } m_axi_memory_3_WDATA { O 32 vector } m_axi_memory_3_WSTRB { O 4 vector } m_axi_memory_3_WLAST { O 1 bit } m_axi_memory_3_WID { O 1 vector } m_axi_memory_3_WUSER { O 1 vector } m_axi_memory_3_ARVALID { O 1 bit } m_axi_memory_3_ARREADY { I 1 bit } m_axi_memory_3_ARADDR { O 32 vector } m_axi_memory_3_ARID { O 1 vector } m_axi_memory_3_ARLEN { O 32 vector } m_axi_memory_3_ARSIZE { O 3 vector } m_axi_memory_3_ARBURST { O 2 vector } m_axi_memory_3_ARLOCK { O 2 vector } m_axi_memory_3_ARCACHE { O 4 vector } m_axi_memory_3_ARPROT { O 3 vector } m_axi_memory_3_ARQOS { O 4 vector } m_axi_memory_3_ARREGION { O 4 vector } m_axi_memory_3_ARUSER { O 1 vector } m_axi_memory_3_RVALID { I 1 bit } m_axi_memory_3_RREADY { O 1 bit } m_axi_memory_3_RDATA { I 32 vector } m_axi_memory_3_RLAST { I 1 bit } m_axi_memory_3_RID { I 1 vector } m_axi_memory_3_RUSER { I 1 vector } m_axi_memory_3_RRESP { I 2 vector } m_axi_memory_3_BVALID { I 1 bit } m_axi_memory_3_BREADY { O 1 bit } m_axi_memory_3_BRESP { I 2 vector } m_axi_memory_3_BID { I 1 vector } m_axi_memory_3_BUSER { I 1 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 19 \
    name a_offset_address \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_a_offset_address \
    op interface \
    ports { a_offset_address { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 21 \
    name c_offset_address \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_c_offset_address \
    op interface \
    ports { c_offset_address { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id -1 \
    name ap_ctrl \
    type ap_ctrl \
    reset_level 1 \
    sync_rst true \
    corename ap_ctrl \
    op interface \
    ports { ap_start { I 1 bit } ap_ready { O 1 bit } ap_done { O 1 bit } ap_idle { O 1 bit } ap_continue { I 1 bit } } \
} "
}


# Adapter definition:
set PortName ap_clk
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_clock] == "cg_default_interface_gen_clock"} {
eval "cg_default_interface_gen_clock { \
    id -2 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_clk \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-113\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}


# Adapter definition:
set PortName ap_rst
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_reset] == "cg_default_interface_gen_reset"} {
eval "cg_default_interface_gen_reset { \
    id -3 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_rst \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-114\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}



# merge
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_end
    cg_default_interface_gen_bundle_end
    AESL_LIB_XILADAPTER::native_axis_end
}


