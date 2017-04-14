; ModuleID = 'C:/ws/paper-01/matrix_mult/matrix_mult_large_vhls/solution1/.autopilot/db/a.o.2.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-w64-mingw32"

@matrix_mult_large_str = internal unnamed_addr constant [18 x i8] c"matrix_mult_large\00"
@c_offset_address_channel_str = internal unnamed_addr constant [25 x i8] c"c_offset_address_channel\00"
@c_fifo_OC_V_str = internal unnamed_addr constant [9 x i8] c"c_fifo.V\00"
@ap_fifo_str = internal unnamed_addr constant [8 x i8] c"ap_fifo\00"
@a_fifo_OC_V_str = internal unnamed_addr constant [9 x i8] c"a_fifo.V\00"
@p_str8 = private unnamed_addr constant [12 x i8] c"hls_label_1\00", align 1
@p_str7 = private unnamed_addr constant [12 x i8] c"hls_label_3\00", align 1
@p_str65 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str64 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str63 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str62 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str60 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str6 = private unnamed_addr constant [12 x i8] c"hls_label_2\00", align 1
@p_str59 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str58 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str57 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str56 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str55 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str54 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str53 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str52 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str49 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str48 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str47 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str46 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str45 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str44 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str43 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str42 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str41 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str40 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str4 = private unnamed_addr constant [12 x i8] c"hls_label_0\00", align 1
@p_str3 = private unnamed_addr constant [6 x i8] c"m_axi\00", align 1
@p_str2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@p_str1 = private unnamed_addr constant [12 x i8] c"control_bus\00", align 1
@p_str = private unnamed_addr constant [10 x i8] c"s_axilite\00", align 1

define internal fastcc void @matrix_mult_large_mxv_Loop_3_proc(i32* nocapture %c_offset_address, i32* %c_fifo_V, i32* %memory_3) {
entry:
  call void (...)* @_ssdm_op_SpecInterface(i32* %c_fifo_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str46, [1 x i8]* @p_str47, [1 x i8]* @p_str48, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str49)
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_3, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2)
  call void (...)* @_ssdm_op_SpecInterface(i32* %c_offset_address, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str62, [1 x i8]* @p_str63, [1 x i8]* @p_str64, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str65)
  %c_offset_address_read = call i32 @_ssdm_op_Read.ap_fifo.i32P(i32* %c_offset_address)
  %tmp_3 = zext i32 %c_offset_address_read to i64
  %memory_3_addr = getelementptr inbounds i32* %memory_3, i64 %tmp_3
  %memory_3_addr_1_wr_req = call i1 @_ssdm_op_WriteReq.m_axi.i32P(i32* %memory_3_addr, i32 16)
  br label %.preheader.i

.preheader.i:                                     ; preds = %0, %entry
  %j2_i = phi i5 [ %j, %0 ], [ 0, %entry ]
  %exitcond_i = icmp eq i5 %j2_i, -16
  %j = add i5 %j2_i, 1
  br i1 %exitcond_i, label %.exit, label %0

; <label>:0                                       ; preds = %.preheader.i
  %empty = call i32 (...)* @_ssdm_op_SpecLoopTripCount(i64 16, i64 16, i64 16)
  %tmp_10_i = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str8)
  call void (...)* @_ssdm_op_SpecPipeline(i32 -1, i32 1, i32 1, i32 0, [1 x i8]* @p_str2) nounwind
  %c_fifo_V_read = call i32 @_ssdm_op_Read.ap_fifo.volatile.i32P(i32* %c_fifo_V)
  call void @_ssdm_op_Write.m_axi.i32P(i32* %memory_3_addr, i32 %c_fifo_V_read, i4 -1)
  %empty_6 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str8, i32 %tmp_10_i)
  br label %.preheader.i

.exit:                                            ; preds = %.preheader.i
  %memory_3_addr_1_wr_resp = call i1 @_ssdm_op_WriteResp.m_axi.i32P(i32* %memory_3_addr)
  ret void
}

define internal fastcc void @matrix_mult_large_mxv_Loop_2_proc(i32* %a_fifo_V, i32* %c_fifo_V, [8192 x i32]* nocapture %B) {
newFuncRoot:
  %tmp = alloca i32
  call void (...)* @_ssdm_op_SpecInterface(i32* %c_fifo_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str46, [1 x i8]* @p_str47, [1 x i8]* @p_str48, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str49)
  call void (...)* @_ssdm_op_SpecInterface(i32* %a_fifo_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str41, [1 x i8]* @p_str42, [1 x i8]* @p_str43, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str44)
  %a_0 = alloca [16 x i32], align 4
  %a_1 = alloca [16 x i32], align 4
  %a_2 = alloca [16 x i32], align 4
  %a_3 = alloca [16 x i32], align 4
  %a_4 = alloca [16 x i32], align 4
  %a_5 = alloca [16 x i32], align 4
  %a_6 = alloca [16 x i32], align 4
  %a_7 = alloca [16 x i32], align 4
  %a_8 = alloca [16 x i32], align 4
  %a_9 = alloca [16 x i32], align 4
  %a_10 = alloca [16 x i32], align 4
  %a_11 = alloca [16 x i32], align 4
  %a_12 = alloca [16 x i32], align 4
  %a_13 = alloca [16 x i32], align 4
  %a_14 = alloca [16 x i32], align 4
  %a_15 = alloca [16 x i32], align 4
  %a_16 = alloca [16 x i32], align 4
  %a_17 = alloca [16 x i32], align 4
  %a_18 = alloca [16 x i32], align 4
  %a_19 = alloca [16 x i32], align 4
  %a_20 = alloca [16 x i32], align 4
  %a_21 = alloca [16 x i32], align 4
  %a_22 = alloca [16 x i32], align 4
  %a_23 = alloca [16 x i32], align 4
  %a_24 = alloca [16 x i32], align 4
  %a_25 = alloca [16 x i32], align 4
  %a_26 = alloca [16 x i32], align 4
  %a_27 = alloca [16 x i32], align 4
  %a_28 = alloca [16 x i32], align 4
  %a_29 = alloca [16 x i32], align 4
  %a_30 = alloca [16 x i32], align 4
  %a_31 = alloca [16 x i32], align 4
  br label %.preheader17

.preheader.preheader.exitStub:                    ; preds = %.preheader17
  ret void

.preheader18:                                     ; preds = %.preheader17
  %p_011_1_load = load i32* %tmp
  %j = add i5 %j1, 1
  %empty = call i32 (...)* @_ssdm_op_SpecLoopTripCount(i64 8192, i64 8192, i64 8192)
  %exitcond = icmp eq i10 %k, -512
  %k_mid2 = select i1 %exitcond, i10 0, i10 %k
  %tmp_6_mid1 = icmp eq i5 %j, 0
  %tmp_3 = icmp eq i5 %j1, 0
  %tmp_6_mid2 = select i1 %exitcond, i1 %tmp_6_mid1, i1 %tmp_3
  %tmp_7_mid2_v = select i1 %exitcond, i5 %j, i5 %j1
  %tmp_7_mid2_cast = zext i5 %tmp_7_mid2_v to i15
  %tmp_1 = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str7)
  call void (...)* @_ssdm_op_SpecPipeline(i32 -1, i32 1, i32 1, i32 0, [1 x i8]* @p_str2) nounwind
  %tmp_s = icmp eq i10 %k_mid2, 0
  %p_011_1 = select i1 %tmp_s, i32 0, i32 %p_011_1_load
  br i1 %tmp_6_mid2, label %1, label %._crit_edge

.preheader17:                                     ; preds = %._crit_edge19, %newFuncRoot
  %indvar_flatten = phi i14 [ 0, %newFuncRoot ], [ %indvar_flatten_next, %._crit_edge19 ]
  %j1 = phi i5 [ 0, %newFuncRoot ], [ %tmp_7_mid2_v, %._crit_edge19 ]
  %k = phi i10 [ 0, %newFuncRoot ], [ %k_1, %._crit_edge19 ]
  %exitcond_flatten = icmp eq i14 %indvar_flatten, -8192
  %indvar_flatten_next = add i14 %indvar_flatten, 1
  br i1 %exitcond_flatten, label %.preheader.preheader.exitStub, label %.preheader18

._crit_edge19:                                    ; preds = %2, %._crit_edge
  %empty_7 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str7, i32 %tmp_1)
  %k_1 = add i10 %k_mid2, 1
  br label %.preheader17

._crit_edge:                                      ; preds = %0, %.preheader18
  %newIndex = call i5 @_ssdm_op_PartSelect.i5.i10.i32.i32(i10 %k_mid2, i32 5, i32 9)
  %newIndex2 = zext i5 %newIndex to i64
  %tmp_10 = trunc i10 %k_mid2 to i5
  %a_0_addr_1 = getelementptr [16 x i32]* %a_0, i64 0, i64 %newIndex2
  %a_0_load = load i32* %a_0_addr_1, align 4
  %a_1_addr_1 = getelementptr [16 x i32]* %a_1, i64 0, i64 %newIndex2
  %a_1_load = load i32* %a_1_addr_1, align 4
  %a_2_addr_1 = getelementptr [16 x i32]* %a_2, i64 0, i64 %newIndex2
  %a_2_load = load i32* %a_2_addr_1, align 4
  %a_3_addr_1 = getelementptr [16 x i32]* %a_3, i64 0, i64 %newIndex2
  %a_3_load = load i32* %a_3_addr_1, align 4
  %a_4_addr_1 = getelementptr [16 x i32]* %a_4, i64 0, i64 %newIndex2
  %a_4_load = load i32* %a_4_addr_1, align 4
  %a_5_addr_1 = getelementptr [16 x i32]* %a_5, i64 0, i64 %newIndex2
  %a_5_load = load i32* %a_5_addr_1, align 4
  %a_6_addr_1 = getelementptr [16 x i32]* %a_6, i64 0, i64 %newIndex2
  %a_6_load = load i32* %a_6_addr_1, align 4
  %a_7_addr_1 = getelementptr [16 x i32]* %a_7, i64 0, i64 %newIndex2
  %a_7_load = load i32* %a_7_addr_1, align 4
  %a_8_addr_1 = getelementptr [16 x i32]* %a_8, i64 0, i64 %newIndex2
  %a_8_load = load i32* %a_8_addr_1, align 4
  %a_9_addr_1 = getelementptr [16 x i32]* %a_9, i64 0, i64 %newIndex2
  %a_9_load = load i32* %a_9_addr_1, align 4
  %a_10_addr_1 = getelementptr [16 x i32]* %a_10, i64 0, i64 %newIndex2
  %a_10_load = load i32* %a_10_addr_1, align 4
  %a_11_addr_1 = getelementptr [16 x i32]* %a_11, i64 0, i64 %newIndex2
  %a_11_load = load i32* %a_11_addr_1, align 4
  %a_12_addr_1 = getelementptr [16 x i32]* %a_12, i64 0, i64 %newIndex2
  %a_12_load = load i32* %a_12_addr_1, align 4
  %a_13_addr_1 = getelementptr [16 x i32]* %a_13, i64 0, i64 %newIndex2
  %a_13_load = load i32* %a_13_addr_1, align 4
  %a_14_addr_1 = getelementptr [16 x i32]* %a_14, i64 0, i64 %newIndex2
  %a_14_load = load i32* %a_14_addr_1, align 4
  %a_15_addr_1 = getelementptr [16 x i32]* %a_15, i64 0, i64 %newIndex2
  %a_15_load = load i32* %a_15_addr_1, align 4
  %a_16_addr_1 = getelementptr [16 x i32]* %a_16, i64 0, i64 %newIndex2
  %a_16_load = load i32* %a_16_addr_1, align 4
  %a_17_addr_1 = getelementptr [16 x i32]* %a_17, i64 0, i64 %newIndex2
  %a_17_load = load i32* %a_17_addr_1, align 4
  %a_18_addr_1 = getelementptr [16 x i32]* %a_18, i64 0, i64 %newIndex2
  %a_18_load = load i32* %a_18_addr_1, align 4
  %a_19_addr_1 = getelementptr [16 x i32]* %a_19, i64 0, i64 %newIndex2
  %a_19_load = load i32* %a_19_addr_1, align 4
  %a_20_addr_1 = getelementptr [16 x i32]* %a_20, i64 0, i64 %newIndex2
  %a_20_load = load i32* %a_20_addr_1, align 4
  %a_21_addr_1 = getelementptr [16 x i32]* %a_21, i64 0, i64 %newIndex2
  %a_21_load = load i32* %a_21_addr_1, align 4
  %a_22_addr_1 = getelementptr [16 x i32]* %a_22, i64 0, i64 %newIndex2
  %a_22_load = load i32* %a_22_addr_1, align 4
  %a_23_addr_1 = getelementptr [16 x i32]* %a_23, i64 0, i64 %newIndex2
  %a_23_load = load i32* %a_23_addr_1, align 4
  %a_24_addr_1 = getelementptr [16 x i32]* %a_24, i64 0, i64 %newIndex2
  %a_24_load = load i32* %a_24_addr_1, align 4
  %a_25_addr_1 = getelementptr [16 x i32]* %a_25, i64 0, i64 %newIndex2
  %a_25_load = load i32* %a_25_addr_1, align 4
  %a_26_addr_1 = getelementptr [16 x i32]* %a_26, i64 0, i64 %newIndex2
  %a_26_load = load i32* %a_26_addr_1, align 4
  %a_27_addr_1 = getelementptr [16 x i32]* %a_27, i64 0, i64 %newIndex2
  %a_27_load = load i32* %a_27_addr_1, align 4
  %a_28_addr_1 = getelementptr [16 x i32]* %a_28, i64 0, i64 %newIndex2
  %a_28_load = load i32* %a_28_addr_1, align 4
  %a_29_addr_1 = getelementptr [16 x i32]* %a_29, i64 0, i64 %newIndex2
  %a_29_load = load i32* %a_29_addr_1, align 4
  %a_30_addr_1 = getelementptr [16 x i32]* %a_30, i64 0, i64 %newIndex2
  %a_30_load = load i32* %a_30_addr_1, align 4
  %a_31_addr_1 = getelementptr [16 x i32]* %a_31, i64 0, i64 %newIndex2
  %a_31_load = load i32* %a_31_addr_1, align 4
  %tmp_9 = call i32 @_ssdm_op_Mux.ap_auto.32i32.i5(i32 %a_0_load, i32 %a_1_load, i32 %a_2_load, i32 %a_3_load, i32 %a_4_load, i32 %a_5_load, i32 %a_6_load, i32 %a_7_load, i32 %a_8_load, i32 %a_9_load, i32 %a_10_load, i32 %a_11_load, i32 %a_12_load, i32 %a_13_load, i32 %a_14_load, i32 %a_15_load, i32 %a_16_load, i32 %a_17_load, i32 %a_18_load, i32 %a_19_load, i32 %a_20_load, i32 %a_21_load, i32 %a_22_load, i32 %a_23_load, i32 %a_24_load, i32 %a_25_load, i32 %a_26_load, i32 %a_27_load, i32 %a_28_load, i32 %a_29_load, i32 %a_30_load, i32 %a_31_load, i5 %tmp_10)
  %tmp_2 = call i14 @_ssdm_op_BitConcatenate.i14.i10.i4(i10 %k_mid2, i4 0)
  %tmp_3_cast = zext i14 %tmp_2 to i15
  %tmp_7 = add i15 %tmp_3_cast, %tmp_7_mid2_cast
  %tmp_7_cast = zext i15 %tmp_7 to i64
  %B_addr = getelementptr [8192 x i32]* %B, i64 0, i64 %tmp_7_cast
  %B_load = load i32* %B_addr, align 4
  %tmp_4 = mul nsw i32 %tmp_9, %B_load
  %tmp_5 = add nsw i32 %tmp_4, %p_011_1
  %tmp_8 = icmp eq i10 %k_mid2, 511
  store i32 %tmp_5, i32* %tmp
  br i1 %tmp_8, label %2, label %._crit_edge19

; <label>:0                                       ; preds = %branch31, %branch30, %branch29, %branch28, %branch27, %branch26, %branch25, %branch24, %branch23, %branch22, %branch21, %branch20, %branch19, %branch18, %branch17, %branch16, %branch15, %branch14, %branch13, %branch12, %branch11, %branch10, %branch9, %branch8, %branch7, %branch6, %branch5, %branch4, %branch3, %branch2, %branch1, %branch0
  br label %._crit_edge

branch0:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_0_addr, align 4
  br label %0

; <label>:1                                       ; preds = %.preheader18
  %a_fifo_V_read = call i32 @_ssdm_op_Read.ap_fifo.volatile.i32P(i32* %a_fifo_V)
  %newIndex1 = call i5 @_ssdm_op_PartSelect.i5.i10.i32.i32(i10 %k_mid2, i32 5, i32 9)
  %newIndex3 = zext i5 %newIndex1 to i64
  %a_0_addr = getelementptr [16 x i32]* %a_0, i64 0, i64 %newIndex3
  %a_1_addr = getelementptr [16 x i32]* %a_1, i64 0, i64 %newIndex3
  %a_2_addr = getelementptr [16 x i32]* %a_2, i64 0, i64 %newIndex3
  %a_3_addr = getelementptr [16 x i32]* %a_3, i64 0, i64 %newIndex3
  %a_4_addr = getelementptr [16 x i32]* %a_4, i64 0, i64 %newIndex3
  %a_5_addr = getelementptr [16 x i32]* %a_5, i64 0, i64 %newIndex3
  %a_6_addr = getelementptr [16 x i32]* %a_6, i64 0, i64 %newIndex3
  %a_7_addr = getelementptr [16 x i32]* %a_7, i64 0, i64 %newIndex3
  %a_8_addr = getelementptr [16 x i32]* %a_8, i64 0, i64 %newIndex3
  %a_9_addr = getelementptr [16 x i32]* %a_9, i64 0, i64 %newIndex3
  %a_10_addr = getelementptr [16 x i32]* %a_10, i64 0, i64 %newIndex3
  %a_11_addr = getelementptr [16 x i32]* %a_11, i64 0, i64 %newIndex3
  %a_12_addr = getelementptr [16 x i32]* %a_12, i64 0, i64 %newIndex3
  %a_13_addr = getelementptr [16 x i32]* %a_13, i64 0, i64 %newIndex3
  %a_14_addr = getelementptr [16 x i32]* %a_14, i64 0, i64 %newIndex3
  %a_15_addr = getelementptr [16 x i32]* %a_15, i64 0, i64 %newIndex3
  %a_16_addr = getelementptr [16 x i32]* %a_16, i64 0, i64 %newIndex3
  %a_17_addr = getelementptr [16 x i32]* %a_17, i64 0, i64 %newIndex3
  %a_18_addr = getelementptr [16 x i32]* %a_18, i64 0, i64 %newIndex3
  %a_19_addr = getelementptr [16 x i32]* %a_19, i64 0, i64 %newIndex3
  %a_20_addr = getelementptr [16 x i32]* %a_20, i64 0, i64 %newIndex3
  %a_21_addr = getelementptr [16 x i32]* %a_21, i64 0, i64 %newIndex3
  %a_22_addr = getelementptr [16 x i32]* %a_22, i64 0, i64 %newIndex3
  %a_23_addr = getelementptr [16 x i32]* %a_23, i64 0, i64 %newIndex3
  %a_24_addr = getelementptr [16 x i32]* %a_24, i64 0, i64 %newIndex3
  %a_25_addr = getelementptr [16 x i32]* %a_25, i64 0, i64 %newIndex3
  %a_26_addr = getelementptr [16 x i32]* %a_26, i64 0, i64 %newIndex3
  %a_27_addr = getelementptr [16 x i32]* %a_27, i64 0, i64 %newIndex3
  %a_28_addr = getelementptr [16 x i32]* %a_28, i64 0, i64 %newIndex3
  %a_29_addr = getelementptr [16 x i32]* %a_29, i64 0, i64 %newIndex3
  %a_30_addr = getelementptr [16 x i32]* %a_30, i64 0, i64 %newIndex3
  %a_31_addr = getelementptr [16 x i32]* %a_31, i64 0, i64 %newIndex3
  %tmp_6 = trunc i10 %k_mid2 to i5
  switch i5 %tmp_6, label %branch31 [
    i5 0, label %branch0
    i5 1, label %branch1
    i5 2, label %branch2
    i5 3, label %branch3
    i5 4, label %branch4
    i5 5, label %branch5
    i5 6, label %branch6
    i5 7, label %branch7
    i5 8, label %branch8
    i5 9, label %branch9
    i5 10, label %branch10
    i5 11, label %branch11
    i5 12, label %branch12
    i5 13, label %branch13
    i5 14, label %branch14
    i5 15, label %branch15
    i5 -16, label %branch16
    i5 -15, label %branch17
    i5 -14, label %branch18
    i5 -13, label %branch19
    i5 -12, label %branch20
    i5 -11, label %branch21
    i5 -10, label %branch22
    i5 -9, label %branch23
    i5 -8, label %branch24
    i5 -7, label %branch25
    i5 -6, label %branch26
    i5 -5, label %branch27
    i5 -4, label %branch28
    i5 -3, label %branch29
    i5 -2, label %branch30
  ]

branch1:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_1_addr, align 4
  br label %0

branch2:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_2_addr, align 4
  br label %0

branch3:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_3_addr, align 4
  br label %0

branch4:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_4_addr, align 4
  br label %0

branch5:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_5_addr, align 4
  br label %0

branch6:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_6_addr, align 4
  br label %0

branch7:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_7_addr, align 4
  br label %0

branch8:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_8_addr, align 4
  br label %0

branch9:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_9_addr, align 4
  br label %0

branch10:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_10_addr, align 4
  br label %0

branch11:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_11_addr, align 4
  br label %0

branch12:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_12_addr, align 4
  br label %0

branch13:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_13_addr, align 4
  br label %0

branch14:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_14_addr, align 4
  br label %0

branch15:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_15_addr, align 4
  br label %0

branch16:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_16_addr, align 4
  br label %0

branch17:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_17_addr, align 4
  br label %0

branch18:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_18_addr, align 4
  br label %0

branch19:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_19_addr, align 4
  br label %0

branch20:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_20_addr, align 4
  br label %0

branch21:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_21_addr, align 4
  br label %0

branch22:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_22_addr, align 4
  br label %0

branch23:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_23_addr, align 4
  br label %0

branch24:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_24_addr, align 4
  br label %0

branch25:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_25_addr, align 4
  br label %0

branch26:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_26_addr, align 4
  br label %0

branch27:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_27_addr, align 4
  br label %0

branch28:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_28_addr, align 4
  br label %0

branch29:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_29_addr, align 4
  br label %0

branch30:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_30_addr, align 4
  br label %0

branch31:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_31_addr, align 4
  br label %0

; <label>:2                                       ; preds = %._crit_edge
  call void @_ssdm_op_Write.ap_fifo.volatile.i32P(i32* %c_fifo_V, i32 %tmp_5)
  br label %._crit_edge19
}

define internal fastcc void @matrix_mult_large_mxv_Loop_1_proc50(i32 %a_offset_address, i32* %memory_0, i32* %a_fifo_V, i32 %c_offset_address, i32* %c_offset_address_out) {
entry:
  call void (...)* @_ssdm_op_SpecInterface(i32* %a_fifo_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str41, [1 x i8]* @p_str42, [1 x i8]* @p_str43, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str44)
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_0, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2)
  call void (...)* @_ssdm_op_SpecInterface(i32* %c_offset_address_out, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str52, [1 x i8]* @p_str53, [1 x i8]* @p_str54, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str55)
  %c_offset_address_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %c_offset_address)
  %a_offset_address_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %a_offset_address)
  call void @_ssdm_op_Write.ap_fifo.i32P(i32* %c_offset_address_out, i32 %c_offset_address_read)
  %tmp_s = zext i32 %a_offset_address_read to i64
  %memory_0_addr = getelementptr inbounds i32* %memory_0, i64 %tmp_s
  %memory_0_addr_rd_req = call i1 @_ssdm_op_ReadReq.m_axi.i32P(i32* %memory_0_addr, i32 512)
  br label %0

; <label>:0                                       ; preds = %1, %entry
  %j_0_i_i_i_i = phi i10 [ 0, %entry ], [ %j, %1 ]
  %exitcond16_i_i_i_i = icmp eq i10 %j_0_i_i_i_i, -512
  %j = add i10 %j_0_i_i_i_i, 1
  br i1 %exitcond16_i_i_i_i, label %.exit, label %1

; <label>:1                                       ; preds = %0
  %empty = call i32 (...)* @_ssdm_op_SpecLoopTripCount(i64 512, i64 512, i64 512)
  %tmp_1_i_i = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str6)
  call void (...)* @_ssdm_op_SpecPipeline(i32 1, i32 1, i32 1, i32 0, [1 x i8]* @p_str2) nounwind
  %tmp = call i32 @_ssdm_op_Read.m_axi.i32P(i32* %memory_0_addr)
  call void @_ssdm_op_Write.ap_fifo.volatile.i32P(i32* %a_fifo_V, i32 %tmp)
  %empty_8 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str6, i32 %tmp_1_i_i)
  br label %0

.exit:                                            ; preds = %0
  ret void
}

define internal fastcc void @matrix_mult_large_mxv(i32* %memory_0, i32* %memory_3, i32 %a_offset_address, [8192 x i32]* nocapture %B, i32 %c_offset_address) {
codeRepl:
  %c_offset_address_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %c_offset_address)
  %a_offset_address_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %a_offset_address)
  %c_offset_address_channel = alloca i32, align 4
  call void (...)* @_ssdm_op_SpecDataflowPipeline(i32 -1, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_3, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_0, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  %a_fifo_V = alloca i32, align 4
  %empty = call i32 (...)* @_ssdm_op_SpecChannel([9 x i8]* @a_fifo_OC_V_str, i32 1, [1 x i8]* @p_str40, [1 x i8]* @p_str40, i32 1, i32 1, i32* %a_fifo_V, i32* %a_fifo_V)
  call void (...)* @_ssdm_op_SpecInterface(i32* %a_fifo_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str41, [1 x i8]* @p_str42, [1 x i8]* @p_str43, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str44)
  %c_fifo_V = alloca i32, align 4
  %empty_9 = call i32 (...)* @_ssdm_op_SpecChannel([9 x i8]* @c_fifo_OC_V_str, i32 1, [1 x i8]* @p_str45, [1 x i8]* @p_str45, i32 1, i32 1, i32* %c_fifo_V, i32* %c_fifo_V)
  call void (...)* @_ssdm_op_SpecInterface(i32* %c_fifo_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str46, [1 x i8]* @p_str47, [1 x i8]* @p_str48, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str49)
  %empty_10 = call i32 (...)* @_ssdm_op_SpecChannel([25 x i8]* @c_offset_address_channel_str, i32 1, [1 x i8]* @p_str56, [1 x i8]* @p_str56, i32 2, i32 0, i32* %c_offset_address_channel, i32* %c_offset_address_channel)
  call void (...)* @_ssdm_op_SpecInterface(i32* %c_offset_address_channel, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str57, [1 x i8]* @p_str58, [1 x i8]* @p_str59, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str60)
  call fastcc void @matrix_mult_large_mxv_Loop_1_proc50(i32 %a_offset_address_read, i32* %memory_0, i32* %a_fifo_V, i32 %c_offset_address_read, i32* %c_offset_address_channel)
  call fastcc void @matrix_mult_large_mxv_Loop_2_proc(i32* %a_fifo_V, i32* %c_fifo_V, [8192 x i32]* %B)
  call fastcc void @matrix_mult_large_mxv_Loop_3_proc(i32* nocapture %c_offset_address_channel, i32* %c_fifo_V, i32* %memory_3)
  ret void
}

define void @matrix_mult_large(i32* %memory_0, i32* %memory_1_0, i32* %memory_2_0, i32* %memory_1_1, i32* %memory_2_1, i32* %memory_1_2, i32* %memory_2_2, i32* %memory_1_3, i32* %memory_2_3, i32* %memory_1_4, i32* %memory_2_4, i32* %memory_1_5, i32* %memory_2_5, i32* %memory_1_6, i32* %memory_2_6, i32* %memory_1_7, i32* %memory_2_7, i32 %a_offset_address, i32 %b_offset_address, i32 %c_offset_address) nounwind uwtable {
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_0) nounwind, !map !0
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_0) nounwind, !map !6
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_0) nounwind, !map !10
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_1) nounwind, !map !14
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_1) nounwind, !map !18
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_2) nounwind, !map !22
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_2) nounwind, !map !26
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_3) nounwind, !map !30
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_3) nounwind, !map !34
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_4) nounwind, !map !38
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_4) nounwind, !map !42
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_5) nounwind, !map !46
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_5) nounwind, !map !50
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_6) nounwind, !map !54
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_6) nounwind, !map !58
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_7) nounwind, !map !62
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_7) nounwind, !map !66
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %a_offset_address) nounwind, !map !70
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %b_offset_address) nounwind, !map !76
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %c_offset_address) nounwind, !map !80
  call void (...)* @_ssdm_op_SpecTopModule([18 x i8]* @matrix_mult_large_str) nounwind
  %c_offset_address_read = call i32 @_ssdm_op_Read.s_axilite.i32(i32 %c_offset_address) nounwind
  %b_offset_address_read = call i32 @_ssdm_op_Read.s_axilite.i32(i32 %b_offset_address) nounwind
  %a_offset_address_read = call i32 @_ssdm_op_Read.s_axilite.i32(i32 %a_offset_address) nounwind
  %B_0 = alloca [8192 x i32], align 4
  %B_1 = alloca [8192 x i32], align 4
  %B_2 = alloca [8192 x i32], align 4
  %B_3 = alloca [8192 x i32], align 4
  %B_4 = alloca [8192 x i32], align 4
  %B_5 = alloca [8192 x i32], align 4
  %B_6 = alloca [8192 x i32], align 4
  %B_7 = alloca [8192 x i32], align 4
  call void (...)* @_ssdm_op_SpecInterface(i32 0, [10 x i8]* @p_str, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32 %a_offset_address, [10 x i8]* @p_str, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32 %b_offset_address, [10 x i8]* @p_str, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32 %c_offset_address, [10 x i8]* @p_str, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_0, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_0, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_0, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_1, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_1, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_2, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_2, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_3, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_3, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_4, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_4, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_5, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_5, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_6, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_6, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_7, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_7, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  %tmp_9 = zext i32 %b_offset_address_read to i64
  %memory_0_addr = getelementptr inbounds i32* %memory_0, i64 %tmp_9
  br label %.loopexit

.loopexit:                                        ; preds = %.preheader, %0
  %p1 = phi i3 [ 0, %0 ], [ %p, %.preheader ]
  %exitcond4 = icmp eq i3 %p1, -4
  %p = add i3 %p1, 1
  br i1 %exitcond4, label %24, label %.preheader6.preheader

.preheader6.preheader:                            ; preds = %.loopexit
  %empty = call i32 (...)* @_ssdm_op_SpecLoopTripCount(i64 4, i64 4, i64 4) nounwind
  %tmp_14 = trunc i3 %p1 to i2
  %tmp_s = call i9 @_ssdm_op_BitConcatenate.i9.i2.i7(i2 %tmp_14, i7 0)
  %tmp_cast2 = zext i9 %tmp_s to i10
  %tmp_1 = or i9 %tmp_s, 16
  %tmp_15_cast1 = zext i9 %tmp_1 to i10
  %tmp_2 = or i9 %tmp_s, 32
  %tmp_16_cast1 = zext i9 %tmp_2 to i10
  %tmp_3 = or i9 %tmp_s, 48
  %tmp_17_cast9 = zext i9 %tmp_3 to i10
  %tmp_4 = or i9 %tmp_s, 64
  %tmp_18_cast8 = zext i9 %tmp_4 to i10
  %tmp_5 = or i9 %tmp_s, 80
  %tmp_19_cast7 = zext i9 %tmp_5 to i10
  %tmp_6 = or i9 %tmp_s, 96
  %tmp_20_cast6 = zext i9 %tmp_6 to i10
  %tmp_7 = or i9 %tmp_s, 112
  %tmp_21_cast5 = zext i9 %tmp_7 to i10
  %tmp_8 = add i10 128, %tmp_cast2
  %memory_0_addr_1_rd_req = call i1 @_ssdm_op_ReadReq.m_axi.i32P(i32* %memory_0_addr, i32 262144) nounwind
  br label %.preheader5

.preheader.preheader:                             ; preds = %.preheader5
  %tmp417_cast = zext i9 %tmp_1 to i32
  %tmp618_cast = zext i9 %tmp_2 to i32
  %tmp819_cast = zext i9 %tmp_3 to i32
  %tmp1020_cast = zext i9 %tmp_4 to i32
  %tmp1221_cast = zext i9 %tmp_5 to i32
  %tmp1422_cast = zext i9 %tmp_6 to i32
  %tmp1623_cast = zext i9 %tmp_7 to i32
  br label %.preheader

.preheader5:                                      ; preds = %.preheader6.preheader, %22
  %indvar_flatten = phi i19 [ 0, %.preheader6.preheader ], [ %indvar_flatten_next, %22 ]
  %i = phi i10 [ 0, %.preheader6.preheader ], [ %tmp_24_cast_cast_mid2_v_v_v, %22 ]
  %j = phi i10 [ 0, %.preheader6.preheader ], [ %j_1, %22 ]
  %exitcond_flatten = icmp eq i19 %indvar_flatten, -262144
  %indvar_flatten_next = add i19 %indvar_flatten, 1
  br i1 %exitcond_flatten, label %.preheader.preheader, label %.preheader6

; <label>:1                                       ; preds = %.preheader6
  %tmp_17 = sub i10 %j_mid2, %tmp_cast2
  %tmp_21_cast = sext i10 %tmp_17 to i15
  %tmp_18 = add i15 %tmp_16_cast, %tmp_21_cast
  %tmp_22_cast = sext i15 %tmp_18 to i64
  %B_0_addr = getelementptr [8192 x i32]* %B_0, i64 0, i64 %tmp_22_cast
  store i32 %tmp, i32* %B_0_addr, align 4
  br label %22

; <label>:2                                       ; preds = %.preheader6
  %ult = icmp ult i10 %j_mid2, %tmp_15_cast1
  %rev1 = xor i1 %ult, true
  %tmp_19 = icmp ult i10 %j_mid2, %tmp_16_cast1
  %or_cond7 = and i1 %rev1, %tmp_19
  br i1 %or_cond7, label %3, label %4

; <label>:3                                       ; preds = %2
  %tmp_28 = sub i10 %j_mid2, %tmp_15_cast1
  %tmp_35_cast = sext i10 %tmp_28 to i15
  %tmp_29 = add i15 %tmp_16_cast, %tmp_35_cast
  %tmp_36_cast = sext i15 %tmp_29 to i64
  %B_1_addr = getelementptr [8192 x i32]* %B_1, i64 0, i64 %tmp_36_cast
  store i32 %tmp, i32* %B_1_addr, align 4
  br label %21

; <label>:4                                       ; preds = %2
  %ult2 = icmp ult i10 %j_mid2, %tmp_16_cast1
  %rev2 = xor i1 %ult2, true
  %tmp_30 = icmp ult i10 %j_mid2, %tmp_17_cast9
  %or_cond8 = and i1 %rev2, %tmp_30
  br i1 %or_cond8, label %5, label %6

; <label>:5                                       ; preds = %4
  %tmp_31 = sub i10 %j_mid2, %tmp_16_cast1
  %tmp_40_cast = sext i10 %tmp_31 to i15
  %tmp_32 = add i15 %tmp_16_cast, %tmp_40_cast
  %tmp_41_cast = sext i15 %tmp_32 to i64
  %B_2_addr = getelementptr [8192 x i32]* %B_2, i64 0, i64 %tmp_41_cast
  store i32 %tmp, i32* %B_2_addr, align 4
  br label %20

; <label>:6                                       ; preds = %4
  %ult3 = icmp ult i10 %j_mid2, %tmp_17_cast9
  %rev3 = xor i1 %ult3, true
  %tmp_33 = icmp ult i10 %j_mid2, %tmp_18_cast8
  %or_cond9 = and i1 %rev3, %tmp_33
  br i1 %or_cond9, label %7, label %8

; <label>:7                                       ; preds = %6
  %tmp_34 = sub i10 %j_mid2, %tmp_17_cast9
  %tmp_45_cast = sext i10 %tmp_34 to i15
  %tmp_35 = add i15 %tmp_16_cast, %tmp_45_cast
  %tmp_46_cast = sext i15 %tmp_35 to i64
  %B_3_addr = getelementptr [8192 x i32]* %B_3, i64 0, i64 %tmp_46_cast
  store i32 %tmp, i32* %B_3_addr, align 4
  br label %19

; <label>:8                                       ; preds = %6
  %ult4 = icmp ult i10 %j_mid2, %tmp_18_cast8
  %rev4 = xor i1 %ult4, true
  %tmp_36 = icmp ult i10 %j_mid2, %tmp_19_cast7
  %or_cond1 = and i1 %rev4, %tmp_36
  br i1 %or_cond1, label %9, label %10

; <label>:9                                       ; preds = %8
  %tmp_37 = sub i10 %j_mid2, %tmp_18_cast8
  %tmp_50_cast = sext i10 %tmp_37 to i15
  %tmp_38 = add i15 %tmp_16_cast, %tmp_50_cast
  %tmp_51_cast = sext i15 %tmp_38 to i64
  %B_4_addr = getelementptr [8192 x i32]* %B_4, i64 0, i64 %tmp_51_cast
  store i32 %tmp, i32* %B_4_addr, align 4
  br label %18

; <label>:10                                      ; preds = %8
  %ult5 = icmp ult i10 %j_mid2, %tmp_19_cast7
  %rev5 = xor i1 %ult5, true
  %tmp_39 = icmp ult i10 %j_mid2, %tmp_20_cast6
  %or_cond2 = and i1 %rev5, %tmp_39
  br i1 %or_cond2, label %11, label %12

; <label>:11                                      ; preds = %10
  %tmp_40 = sub i10 %j_mid2, %tmp_19_cast7
  %tmp_55_cast = sext i10 %tmp_40 to i15
  %tmp_41 = add i15 %tmp_16_cast, %tmp_55_cast
  %tmp_56_cast = sext i15 %tmp_41 to i64
  %B_5_addr = getelementptr [8192 x i32]* %B_5, i64 0, i64 %tmp_56_cast
  store i32 %tmp, i32* %B_5_addr, align 4
  br label %17

; <label>:12                                      ; preds = %10
  %ult6 = icmp ult i10 %j_mid2, %tmp_20_cast6
  %rev6 = xor i1 %ult6, true
  %tmp_42 = icmp ult i10 %j_mid2, %tmp_21_cast5
  %or_cond3 = and i1 %rev6, %tmp_42
  br i1 %or_cond3, label %13, label %14

; <label>:13                                      ; preds = %12
  %tmp_43 = sub i10 %j_mid2, %tmp_20_cast6
  %tmp_60_cast = sext i10 %tmp_43 to i15
  %tmp_44 = add i15 %tmp_16_cast, %tmp_60_cast
  %tmp_61_cast = sext i15 %tmp_44 to i64
  %B_6_addr = getelementptr [8192 x i32]* %B_6, i64 0, i64 %tmp_61_cast
  store i32 %tmp, i32* %B_6_addr, align 4
  br label %16

; <label>:14                                      ; preds = %12
  %ult7 = icmp ult i10 %j_mid2, %tmp_21_cast5
  %rev7 = xor i1 %ult7, true
  %tmp_45 = icmp ult i10 %j_mid2, %tmp_8
  %or_cond4 = and i1 %rev7, %tmp_45
  br i1 %or_cond4, label %15, label %._crit_edge

; <label>:15                                      ; preds = %14
  %tmp_46 = sub i10 %j_mid2, %tmp_21_cast5
  %tmp_65_cast = sext i10 %tmp_46 to i15
  %tmp_47 = add i15 %tmp_16_cast, %tmp_65_cast
  %tmp_66_cast = sext i15 %tmp_47 to i64
  %B_7_addr = getelementptr [8192 x i32]* %B_7, i64 0, i64 %tmp_66_cast
  store i32 %tmp, i32* %B_7_addr, align 4
  br label %._crit_edge

._crit_edge:                                      ; preds = %15, %14
  br label %16

; <label>:16                                      ; preds = %._crit_edge, %13
  br label %17

; <label>:17                                      ; preds = %16, %11
  br label %18

; <label>:18                                      ; preds = %17, %9
  br label %19

; <label>:19                                      ; preds = %18, %7
  br label %20

; <label>:20                                      ; preds = %19, %5
  br label %21

; <label>:21                                      ; preds = %20, %3
  br label %22

; <label>:22                                      ; preds = %21, %1
  %empty_11 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str4, i32 %tmp_15) nounwind
  %j_1 = add i10 %j_mid2, 1
  br label %.preheader5

.preheader6:                                      ; preds = %.preheader5
  %i_2 = add i10 %i, 1
  %empty_12 = call i32 (...)* @_ssdm_op_SpecLoopTripCount(i64 262144, i64 262144, i64 262144) nounwind
  %exitcond1 = icmp eq i10 %j, -512
  %j_mid2 = select i1 %exitcond1, i10 0, i10 %j
  %tmp_24_cast_cast_mid2_v_v_v = select i1 %exitcond1, i10 %i_2, i10 %i
  %tmp_10 = call i14 @_ssdm_op_BitConcatenate.i14.i10.i4(i10 %tmp_24_cast_cast_mid2_v_v_v, i4 0)
  %tmp_16_cast = zext i14 %tmp_10 to i15
  %tmp_15 = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str4) nounwind
  call void (...)* @_ssdm_op_SpecPipeline(i32 -1, i32 1, i32 1, i32 0, [1 x i8]* @p_str2) nounwind
  %tmp = call i32 @_ssdm_op_Read.m_axi.i32P(i32* %memory_0_addr) nounwind
  %ult1 = icmp ult i10 %j_mid2, %tmp_cast2
  %rev = xor i1 %ult1, true
  %tmp_16 = icmp ult i10 %j_mid2, %tmp_15_cast1
  %or_cond = and i1 %rev, %tmp_16
  br i1 %or_cond, label %1, label %2

.preheader:                                       ; preds = %23, %.preheader.preheader
  %i2 = phi i10 [ %i_1, %23 ], [ 0, %.preheader.preheader ]
  %exitcond = icmp eq i10 %i2, -512
  %empty_13 = call i32 (...)* @_ssdm_op_SpecLoopTripCount(i64 512, i64 512, i64 512) nounwind
  %i_1 = add i10 %i2, 1
  br i1 %exitcond, label %.loopexit, label %23

; <label>:23                                      ; preds = %.preheader
  %tmp_20 = trunc i10 %i2 to i9
  %tmp_11 = call i18 @_ssdm_op_BitConcatenate.i18.i9.i9(i9 %tmp_20, i9 0)
  %tmp_26_cast = zext i18 %tmp_11 to i32
  %tmp_12 = add i32 %a_offset_address_read, %tmp_26_cast
  %tmp2 = call i18 @_ssdm_op_BitConcatenate.i18.i9.i2.i7(i9 %tmp_20, i2 %tmp_14, i7 0)
  %tmp2_cast = zext i18 %tmp2 to i32
  %tmp_13 = add i32 %c_offset_address_read, %tmp2_cast
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_0, i32* %memory_2_0, i32 %tmp_12, [8192 x i32]* %B_0, i32 %tmp_13) nounwind
  %tmp3 = add i32 %c_offset_address_read, %tmp_26_cast
  %tmp_21 = add i32 %tmp417_cast, %tmp3
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_1, i32* %memory_2_1, i32 %tmp_12, [8192 x i32]* %B_1, i32 %tmp_21) nounwind
  %tmp_22 = add i32 %tmp618_cast, %tmp3
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_2, i32* %memory_2_2, i32 %tmp_12, [8192 x i32]* %B_2, i32 %tmp_22) nounwind
  %tmp_23 = add i32 %tmp819_cast, %tmp3
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_3, i32* %memory_2_3, i32 %tmp_12, [8192 x i32]* %B_3, i32 %tmp_23) nounwind
  %tmp_24 = add i32 %tmp1020_cast, %tmp3
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_4, i32* %memory_2_4, i32 %tmp_12, [8192 x i32]* %B_4, i32 %tmp_24) nounwind
  %tmp_25 = add i32 %tmp1221_cast, %tmp3
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_5, i32* %memory_2_5, i32 %tmp_12, [8192 x i32]* %B_5, i32 %tmp_25) nounwind
  %tmp_26 = add i32 %tmp1422_cast, %tmp3
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_6, i32* %memory_2_6, i32 %tmp_12, [8192 x i32]* %B_6, i32 %tmp_26) nounwind
  %tmp_27 = add i32 %tmp1623_cast, %tmp3
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_7, i32* %memory_2_7, i32 %tmp_12, [8192 x i32]* %B_7, i32 %tmp_27) nounwind
  br label %.preheader

; <label>:24                                      ; preds = %.loopexit
  ret void
}

declare i10 @llvm.part.select.i10(i10, i32, i32) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define weak i1 @_ssdm_op_WriteResp.m_axi.i32P(i32*) {
entry:
  ret i1 true
}

define weak i1 @_ssdm_op_WriteReq.m_axi.i32P(i32*, i32) {
entry:
  ret i1 true
}

define weak void @_ssdm_op_Write.m_axi.i32P(i32*, i32, i4) {
entry:
  ret void
}

define weak void @_ssdm_op_Write.ap_fifo.volatile.i32P(i32*, i32) {
entry:
  %empty = call i32 @_autotb_FifoWrite_i32(i32* %0, i32 %1)
  ret void
}

define weak void @_ssdm_op_Write.ap_fifo.i32P(i32*, i32) {
entry:
  %empty = call i32 @_autotb_FifoWrite_i32(i32* %0, i32 %1)
  ret void
}

define weak void @_ssdm_op_SpecTopModule(...) {
entry:
  ret void
}

define weak i32 @_ssdm_op_SpecRegionEnd(...) {
entry:
  ret i32 0
}

define weak i32 @_ssdm_op_SpecRegionBegin(...) {
entry:
  ret i32 0
}

define weak void @_ssdm_op_SpecPipeline(...) nounwind {
entry:
  ret void
}

define weak i32 @_ssdm_op_SpecLoopTripCount(...) {
entry:
  ret i32 0
}

define weak void @_ssdm_op_SpecInterface(...) nounwind {
entry:
  ret void
}

define weak void @_ssdm_op_SpecDataflowPipeline(...) nounwind {
entry:
  ret void
}

define weak i32 @_ssdm_op_SpecChannel(...) {
entry:
  ret i32 0
}

define weak void @_ssdm_op_SpecBitsMap(...) {
entry:
  ret void
}

define weak i1 @_ssdm_op_ReadReq.m_axi.i32P(i32*, i32) {
entry:
  ret i1 true
}

define weak i32 @_ssdm_op_Read.s_axilite.i32(i32) {
entry:
  ret i32 %0
}

define weak i32 @_ssdm_op_Read.m_axi.i32P(i32*) {
entry:
  %empty = load i32* %0
  ret i32 %empty
}

define weak i32 @_ssdm_op_Read.ap_fifo.volatile.i32P(i32*) {
entry:
  %empty = call i32 @_autotb_FifoRead_i32(i32* %0)
  ret i32 %empty
}

define weak i32 @_ssdm_op_Read.ap_fifo.i32P(i32*) {
entry:
  %empty = call i32 @_autotb_FifoRead_i32(i32* %0)
  ret i32 %empty
}

define weak i32 @_ssdm_op_Read.ap_auto.i32(i32) {
entry:
  ret i32 %0
}

declare i9 @_ssdm_op_PartSelect.i9.i10.i32.i32(i10, i32, i32) nounwind readnone

define weak i5 @_ssdm_op_PartSelect.i5.i10.i32.i32(i10, i32, i32) nounwind readnone {
entry:
  %empty = call i10 @llvm.part.select.i10(i10 %0, i32 %1, i32 %2)
  %empty_14 = trunc i10 %empty to i5
  ret i5 %empty_14
}

declare i2 @_ssdm_op_PartSelect.i2.i3.i32.i32(i3, i32, i32) nounwind readnone

define weak i32 @_ssdm_op_Mux.ap_auto.32i32.i5(i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i5) {
entry:
  switch i5 %32, label %case31 [
    i5 0, label %case0
    i5 1, label %case1
    i5 2, label %case2
    i5 3, label %case3
    i5 4, label %case4
    i5 5, label %case5
    i5 6, label %case6
    i5 7, label %case7
    i5 8, label %case8
    i5 9, label %case9
    i5 10, label %case10
    i5 11, label %case11
    i5 12, label %case12
    i5 13, label %case13
    i5 14, label %case14
    i5 15, label %case15
    i5 -16, label %case16
    i5 -15, label %case17
    i5 -14, label %case18
    i5 -13, label %case19
    i5 -12, label %case20
    i5 -11, label %case21
    i5 -10, label %case22
    i5 -9, label %case23
    i5 -8, label %case24
    i5 -7, label %case25
    i5 -6, label %case26
    i5 -5, label %case27
    i5 -4, label %case28
    i5 -3, label %case29
    i5 -2, label %case30
  ]

case0:                                            ; preds = %case31, %case30, %case29, %case28, %case27, %case26, %case25, %case24, %case23, %case22, %case21, %case20, %case19, %case18, %case17, %case16, %case15, %case14, %case13, %case12, %case11, %case10, %case9, %case8, %case7, %case6, %case5, %case4, %case3, %case2, %case1, %entry
  %merge = phi i32 [ %0, %entry ], [ %1, %case1 ], [ %2, %case2 ], [ %3, %case3 ], [ %4, %case4 ], [ %5, %case5 ], [ %6, %case6 ], [ %7, %case7 ], [ %8, %case8 ], [ %9, %case9 ], [ %10, %case10 ], [ %11, %case11 ], [ %12, %case12 ], [ %13, %case13 ], [ %14, %case14 ], [ %15, %case15 ], [ %16, %case16 ], [ %17, %case17 ], [ %18, %case18 ], [ %19, %case19 ], [ %20, %case20 ], [ %21, %case21 ], [ %22, %case22 ], [ %23, %case23 ], [ %24, %case24 ], [ %25, %case25 ], [ %26, %case26 ], [ %27, %case27 ], [ %28, %case28 ], [ %29, %case29 ], [ %30, %case30 ], [ %31, %case31 ]
  ret i32 %merge

case1:                                            ; preds = %entry
  br label %case0

case2:                                            ; preds = %entry
  br label %case0

case3:                                            ; preds = %entry
  br label %case0

case4:                                            ; preds = %entry
  br label %case0

case5:                                            ; preds = %entry
  br label %case0

case6:                                            ; preds = %entry
  br label %case0

case7:                                            ; preds = %entry
  br label %case0

case8:                                            ; preds = %entry
  br label %case0

case9:                                            ; preds = %entry
  br label %case0

case10:                                           ; preds = %entry
  br label %case0

case11:                                           ; preds = %entry
  br label %case0

case12:                                           ; preds = %entry
  br label %case0

case13:                                           ; preds = %entry
  br label %case0

case14:                                           ; preds = %entry
  br label %case0

case15:                                           ; preds = %entry
  br label %case0

case16:                                           ; preds = %entry
  br label %case0

case17:                                           ; preds = %entry
  br label %case0

case18:                                           ; preds = %entry
  br label %case0

case19:                                           ; preds = %entry
  br label %case0

case20:                                           ; preds = %entry
  br label %case0

case21:                                           ; preds = %entry
  br label %case0

case22:                                           ; preds = %entry
  br label %case0

case23:                                           ; preds = %entry
  br label %case0

case24:                                           ; preds = %entry
  br label %case0

case25:                                           ; preds = %entry
  br label %case0

case26:                                           ; preds = %entry
  br label %case0

case27:                                           ; preds = %entry
  br label %case0

case28:                                           ; preds = %entry
  br label %case0

case29:                                           ; preds = %entry
  br label %case0

case30:                                           ; preds = %entry
  br label %case0

case31:                                           ; preds = %entry
  br label %case0
}

define weak i9 @_ssdm_op_BitConcatenate.i9.i2.i7(i2, i7) nounwind readnone {
entry:
  %empty = zext i2 %0 to i9
  %empty_15 = zext i7 %1 to i9
  %empty_16 = shl i9 %empty, 7
  %empty_17 = or i9 %empty_16, %empty_15
  ret i9 %empty_17
}

define weak i18 @_ssdm_op_BitConcatenate.i18.i9.i9(i9, i9) nounwind readnone {
entry:
  %empty = zext i9 %0 to i18
  %empty_18 = zext i9 %1 to i18
  %empty_19 = shl i18 %empty, 9
  %empty_20 = or i18 %empty_19, %empty_18
  ret i18 %empty_20
}

define weak i18 @_ssdm_op_BitConcatenate.i18.i9.i2.i7(i9, i2, i7) nounwind readnone {
entry:
  %empty = zext i2 %1 to i9
  %empty_21 = zext i7 %2 to i9
  %empty_22 = shl i9 %empty, 7
  %empty_23 = or i9 %empty_22, %empty_21
  %empty_24 = zext i9 %0 to i18
  %empty_25 = zext i9 %empty_23 to i18
  %empty_26 = shl i18 %empty_24, 9
  %empty_27 = or i18 %empty_26, %empty_25
  ret i18 %empty_27
}

define weak i14 @_ssdm_op_BitConcatenate.i14.i10.i4(i10, i4) nounwind readnone {
entry:
  %empty = zext i10 %0 to i14
  %empty_28 = zext i4 %1 to i14
  %empty_29 = shl i14 %empty, 4
  %empty_30 = or i14 %empty_29, %empty_28
  ret i14 %empty_30
}

declare i32 @_autotb_FifoWrite_i32(i32*, i32)

declare i32 @_autotb_FifoRead_i32(i32*)

!hls.encrypted.func = !{}
!llvm.map.gv = !{}

!0 = metadata !{metadata !1}
!1 = metadata !{i32 0, i32 31, metadata !2}
!2 = metadata !{metadata !3}
!3 = metadata !{metadata !"memory_0", metadata !4, metadata !"int", i32 0, i32 31}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 0, i32 0, i32 1}
!6 = metadata !{metadata !7}
!7 = metadata !{i32 0, i32 31, metadata !8}
!8 = metadata !{metadata !9}
!9 = metadata !{metadata !"memory_1_0", metadata !4, metadata !"int", i32 0, i32 31}
!10 = metadata !{metadata !11}
!11 = metadata !{i32 0, i32 31, metadata !12}
!12 = metadata !{metadata !13}
!13 = metadata !{metadata !"memory_2_0", metadata !4, metadata !"int", i32 0, i32 31}
!14 = metadata !{metadata !15}
!15 = metadata !{i32 0, i32 31, metadata !16}
!16 = metadata !{metadata !17}
!17 = metadata !{metadata !"memory_1_1", metadata !4, metadata !"int", i32 0, i32 31}
!18 = metadata !{metadata !19}
!19 = metadata !{i32 0, i32 31, metadata !20}
!20 = metadata !{metadata !21}
!21 = metadata !{metadata !"memory_2_1", metadata !4, metadata !"int", i32 0, i32 31}
!22 = metadata !{metadata !23}
!23 = metadata !{i32 0, i32 31, metadata !24}
!24 = metadata !{metadata !25}
!25 = metadata !{metadata !"memory_1_2", metadata !4, metadata !"int", i32 0, i32 31}
!26 = metadata !{metadata !27}
!27 = metadata !{i32 0, i32 31, metadata !28}
!28 = metadata !{metadata !29}
!29 = metadata !{metadata !"memory_2_2", metadata !4, metadata !"int", i32 0, i32 31}
!30 = metadata !{metadata !31}
!31 = metadata !{i32 0, i32 31, metadata !32}
!32 = metadata !{metadata !33}
!33 = metadata !{metadata !"memory_1_3", metadata !4, metadata !"int", i32 0, i32 31}
!34 = metadata !{metadata !35}
!35 = metadata !{i32 0, i32 31, metadata !36}
!36 = metadata !{metadata !37}
!37 = metadata !{metadata !"memory_2_3", metadata !4, metadata !"int", i32 0, i32 31}
!38 = metadata !{metadata !39}
!39 = metadata !{i32 0, i32 31, metadata !40}
!40 = metadata !{metadata !41}
!41 = metadata !{metadata !"memory_1_4", metadata !4, metadata !"int", i32 0, i32 31}
!42 = metadata !{metadata !43}
!43 = metadata !{i32 0, i32 31, metadata !44}
!44 = metadata !{metadata !45}
!45 = metadata !{metadata !"memory_2_4", metadata !4, metadata !"int", i32 0, i32 31}
!46 = metadata !{metadata !47}
!47 = metadata !{i32 0, i32 31, metadata !48}
!48 = metadata !{metadata !49}
!49 = metadata !{metadata !"memory_1_5", metadata !4, metadata !"int", i32 0, i32 31}
!50 = metadata !{metadata !51}
!51 = metadata !{i32 0, i32 31, metadata !52}
!52 = metadata !{metadata !53}
!53 = metadata !{metadata !"memory_2_5", metadata !4, metadata !"int", i32 0, i32 31}
!54 = metadata !{metadata !55}
!55 = metadata !{i32 0, i32 31, metadata !56}
!56 = metadata !{metadata !57}
!57 = metadata !{metadata !"memory_1_6", metadata !4, metadata !"int", i32 0, i32 31}
!58 = metadata !{metadata !59}
!59 = metadata !{i32 0, i32 31, metadata !60}
!60 = metadata !{metadata !61}
!61 = metadata !{metadata !"memory_2_6", metadata !4, metadata !"int", i32 0, i32 31}
!62 = metadata !{metadata !63}
!63 = metadata !{i32 0, i32 31, metadata !64}
!64 = metadata !{metadata !65}
!65 = metadata !{metadata !"memory_1_7", metadata !4, metadata !"int", i32 0, i32 31}
!66 = metadata !{metadata !67}
!67 = metadata !{i32 0, i32 31, metadata !68}
!68 = metadata !{metadata !69}
!69 = metadata !{metadata !"memory_2_7", metadata !4, metadata !"int", i32 0, i32 31}
!70 = metadata !{metadata !71}
!71 = metadata !{i32 0, i32 31, metadata !72}
!72 = metadata !{metadata !73}
!73 = metadata !{metadata !"a_offset_address", metadata !74, metadata !"long unsigned int", i32 0, i32 31}
!74 = metadata !{metadata !75}
!75 = metadata !{i32 0, i32 0, i32 0}
!76 = metadata !{metadata !77}
!77 = metadata !{i32 0, i32 31, metadata !78}
!78 = metadata !{metadata !79}
!79 = metadata !{metadata !"b_offset_address", metadata !74, metadata !"long unsigned int", i32 0, i32 31}
!80 = metadata !{metadata !81}
!81 = metadata !{i32 0, i32 31, metadata !82}
!82 = metadata !{metadata !83}
!83 = metadata !{metadata !"c_offset_address", metadata !74, metadata !"long unsigned int", i32 0, i32 31}
