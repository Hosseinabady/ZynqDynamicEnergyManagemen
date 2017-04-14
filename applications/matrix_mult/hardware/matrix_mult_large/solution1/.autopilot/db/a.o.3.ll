; ModuleID = 'C:/ws/paper-01/matrix_mult/matrix_mult_large_vhls/solution1/.autopilot/db/a.o.3.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-w64-mingw32"

@matrix_mult_large_str = internal unnamed_addr constant [18 x i8] c"matrix_mult_large\00" ; [#uses=1 type=[18 x i8]*]
@c_offset_address_channel_str = internal unnamed_addr constant [25 x i8] c"c_offset_address_channel\00" ; [#uses=1 type=[25 x i8]*]
@c_fifo_OC_V_str = internal unnamed_addr constant [9 x i8] c"c_fifo.V\00" ; [#uses=1 type=[9 x i8]*]
@ap_fifo_str = internal unnamed_addr constant [8 x i8] c"ap_fifo\00" ; [#uses=9 type=[8 x i8]*]
@a_fifo_OC_V_str = internal unnamed_addr constant [9 x i8] c"a_fifo.V\00" ; [#uses=1 type=[9 x i8]*]
@p_str8 = private unnamed_addr constant [12 x i8] c"hls_label_1\00", align 1 ; [#uses=2 type=[12 x i8]*]
@p_str7 = private unnamed_addr constant [12 x i8] c"hls_label_3\00", align 1 ; [#uses=2 type=[12 x i8]*]
@p_str65 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=1 type=[1 x i8]*]
@p_str64 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=1 type=[1 x i8]*]
@p_str63 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=1 type=[1 x i8]*]
@p_str62 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=1 type=[1 x i8]*]
@p_str60 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=1 type=[1 x i8]*]
@p_str6 = private unnamed_addr constant [12 x i8] c"hls_label_2\00", align 1 ; [#uses=2 type=[12 x i8]*]
@p_str59 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=1 type=[1 x i8]*]
@p_str58 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=1 type=[1 x i8]*]
@p_str57 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=1 type=[1 x i8]*]
@p_str56 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=2 type=[1 x i8]*]
@p_str55 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=1 type=[1 x i8]*]
@p_str54 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=1 type=[1 x i8]*]
@p_str53 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=1 type=[1 x i8]*]
@p_str52 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=1 type=[1 x i8]*]
@p_str49 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=3 type=[1 x i8]*]
@p_str48 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=3 type=[1 x i8]*]
@p_str47 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=3 type=[1 x i8]*]
@p_str46 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=3 type=[1 x i8]*]
@p_str45 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=2 type=[1 x i8]*]
@p_str44 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=3 type=[1 x i8]*]
@p_str43 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=3 type=[1 x i8]*]
@p_str42 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=3 type=[1 x i8]*]
@p_str41 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=3 type=[1 x i8]*]
@p_str40 = internal unnamed_addr constant [1 x i8] zeroinitializer ; [#uses=2 type=[1 x i8]*]
@p_str4 = private unnamed_addr constant [12 x i8] c"hls_label_0\00", align 1 ; [#uses=2 type=[12 x i8]*]
@p_str3 = private unnamed_addr constant [6 x i8] c"m_axi\00", align 1 ; [#uses=21 type=[6 x i8]*]
@p_str2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1 ; [#uses=101 type=[1 x i8]*]
@p_str1 = private unnamed_addr constant [12 x i8] c"control_bus\00", align 1 ; [#uses=4 type=[12 x i8]*]
@p_str = private unnamed_addr constant [10 x i8] c"s_axilite\00", align 1 ; [#uses=4 type=[10 x i8]*]

; [#uses=1]
define internal fastcc void @matrix_mult_large_mxv_Loop_3_proc(i32* nocapture %c_offset_address, i32* %c_fifo_V, i32* %memory_3) {
entry:
  call void (...)* @_ssdm_op_SpecInterface(i32* %c_fifo_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str46, [1 x i8]* @p_str47, [1 x i8]* @p_str48, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str49)
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_3, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2)
  call void (...)* @_ssdm_op_SpecInterface(i32* %c_offset_address, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str62, [1 x i8]* @p_str63, [1 x i8]* @p_str64, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str65)
  %c_offset_address_read = call i32 @_ssdm_op_Read.ap_fifo.i32P(i32* %c_offset_address) ; [#uses=1 type=i32]
  %tmp_3 = zext i32 %c_offset_address_read to i64, !dbg !0 ; [#uses=1 type=i64] [debug line = 175:35]
  %memory_3_addr = getelementptr inbounds i32* %memory_3, i64 %tmp_3, !dbg !0 ; [#uses=3 type=i32*] [debug line = 175:35]
  %memory_3_addr_1_wr_req = call i1 @_ssdm_op_WriteReq.m_axi.i32P(i32* %memory_3_addr, i32 16), !dbg !0 ; [#uses=0 type=i1] [debug line = 175:35]
  br label %.preheader.i, !dbg !19                ; [debug line = 173:15]

.preheader.i:                                     ; preds = %0, %entry
  %j2_i = phi i5 [ %j, %0 ], [ 0, %entry ]        ; [#uses=2 type=i5]
  %exitcond_i = icmp eq i5 %j2_i, -16, !dbg !19   ; [#uses=1 type=i1] [debug line = 173:15]
  %j = add i5 %j2_i, 1, !dbg !20                  ; [#uses=1 type=i5] [debug line = 173:49]
  br i1 %exitcond_i, label %.exit, label %0, !dbg !19 ; [debug line = 173:15]

; <label>:0                                       ; preds = %.preheader.i
  %empty = call i32 (...)* @_ssdm_op_SpecLoopTripCount(i64 16, i64 16, i64 16) ; [#uses=0 type=i32]
  %tmp_10_i = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str8), !dbg !21 ; [#uses=1 type=i32] [debug line = 173:55]
  call void (...)* @_ssdm_op_SpecPipeline(i32 -1, i32 1, i32 1, i32 0, [1 x i8]* @p_str2) nounwind, !dbg !22 ; [debug line = 174:1]
  %c_fifo_V_read = call i32 @_ssdm_op_Read.ap_fifo.volatile.i32P(i32* %c_fifo_V), !dbg !23 ; [#uses=1 type=i32] [debug line = 131:9@175:35]
  call void @_ssdm_op_Write.m_axi.i32P(i32* %memory_3_addr, i32 %c_fifo_V_read, i4 -1), !dbg !0 ; [debug line = 175:35]
  %empty_6 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str8, i32 %tmp_10_i), !dbg !82 ; [#uses=0 type=i32] [debug line = 176:2]
  call void @llvm.dbg.value(metadata !{i5 %j}, i64 0, metadata !83), !dbg !20 ; [debug line = 173:49] [debug variable = j]
  br label %.preheader.i, !dbg !20                ; [debug line = 173:49]

.exit:                                            ; preds = %.preheader.i
  %memory_3_addr_1_wr_resp = call i1 @_ssdm_op_WriteResp.m_axi.i32P(i32* %memory_3_addr), !dbg !0 ; [#uses=0 type=i1] [debug line = 175:35]
  ret void
}

; [#uses=1]
define internal fastcc void @matrix_mult_large_mxv_Loop_2_proc(i32* %a_fifo_V, i32* %c_fifo_V, [8192 x i32]* nocapture %B) {
newFuncRoot:
  %tmp = alloca i32                               ; [#uses=2 type=i32*]
  call void @llvm.dbg.declare(metadata !{i32* %tmp}, metadata !84) ; [debug variable = tmp]
  call void (...)* @_ssdm_op_SpecInterface(i32* %c_fifo_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str46, [1 x i8]* @p_str47, [1 x i8]* @p_str48, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str49)
  call void (...)* @_ssdm_op_SpecInterface(i32* %a_fifo_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str41, [1 x i8]* @p_str42, [1 x i8]* @p_str43, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str44)
  %a_0 = alloca [16 x i32], align 4               ; [#uses=2 type=[16 x i32]*]
  %a_1 = alloca [16 x i32], align 4               ; [#uses=2 type=[16 x i32]*]
  %a_2 = alloca [16 x i32], align 4               ; [#uses=2 type=[16 x i32]*]
  %a_3 = alloca [16 x i32], align 4               ; [#uses=2 type=[16 x i32]*]
  %a_4 = alloca [16 x i32], align 4               ; [#uses=2 type=[16 x i32]*]
  %a_5 = alloca [16 x i32], align 4               ; [#uses=2 type=[16 x i32]*]
  %a_6 = alloca [16 x i32], align 4               ; [#uses=2 type=[16 x i32]*]
  %a_7 = alloca [16 x i32], align 4               ; [#uses=2 type=[16 x i32]*]
  %a_8 = alloca [16 x i32], align 4               ; [#uses=2 type=[16 x i32]*]
  %a_9 = alloca [16 x i32], align 4               ; [#uses=2 type=[16 x i32]*]
  %a_10 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_11 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_12 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_13 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_14 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_15 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_16 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_17 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_18 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_19 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_20 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_21 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_22 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_23 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_24 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_25 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_26 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_27 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_28 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_29 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_30 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  %a_31 = alloca [16 x i32], align 4              ; [#uses=2 type=[16 x i32]*]
  br label %.preheader17

.preheader.preheader.exitStub:                    ; preds = %.preheader17
  ret void

.preheader18:                                     ; preds = %.preheader17
  %p_011_1_load = load i32* %tmp, !dbg !87        ; [#uses=1 type=i32] [debug line = 161:2]
  %j = add i5 %j1, 1, !dbg !92                    ; [#uses=2 type=i5] [debug line = 158:49]
  call void @llvm.dbg.value(metadata !{i5 %j}, i64 0, metadata !93), !dbg !92 ; [debug line = 158:49] [debug variable = j]
  %empty = call i32 (...)* @_ssdm_op_SpecLoopTripCount(i64 8192, i64 8192, i64 8192) ; [#uses=0 type=i32]
  %exitcond = icmp eq i10 %k, -512, !dbg !94      ; [#uses=3 type=i1] [debug line = 159:16]
  %k_mid2 = select i1 %exitcond, i10 0, i10 %k    ; [#uses=8 type=i10]
  %tmp_6_mid1 = icmp eq i5 %j, 0, !dbg !95        ; [#uses=1 type=i1] [debug line = 162:4]
  %tmp_3 = icmp eq i5 %j1, 0, !dbg !95            ; [#uses=1 type=i1] [debug line = 162:4]
  %tmp_6_mid2 = select i1 %exitcond, i1 %tmp_6_mid1, i1 %tmp_3, !dbg !95 ; [#uses=1 type=i1] [debug line = 162:4]
  %tmp_7_mid2_v = select i1 %exitcond, i5 %j, i5 %j1, !dbg !96 ; [#uses=2 type=i5] [debug line = 165:4]
  %tmp_7_mid2_cast = zext i5 %tmp_7_mid2_v to i15, !dbg !97 ; [#uses=1 type=i15] [debug line = 159:33]
  %tmp_1 = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str7), !dbg !97 ; [#uses=1 type=i32] [debug line = 159:33]
  call void (...)* @_ssdm_op_SpecPipeline(i32 -1, i32 1, i32 1, i32 0, [1 x i8]* @p_str2) nounwind, !dbg !98 ; [debug line = 160:1]
  %tmp_s = icmp eq i10 %k_mid2, 0, !dbg !87       ; [#uses=1 type=i1] [debug line = 161:2]
  %p_011_1 = select i1 %tmp_s, i32 0, i32 %p_011_1_load, !dbg !87 ; [#uses=1 type=i32] [debug line = 161:2]
  br i1 %tmp_6_mid2, label %1, label %._crit_edge, !dbg !95 ; [debug line = 162:4]

.preheader17:                                     ; preds = %._crit_edge19, %newFuncRoot
  %indvar_flatten = phi i14 [ 0, %newFuncRoot ], [ %indvar_flatten_next, %._crit_edge19 ] ; [#uses=2 type=i14]
  %j1 = phi i5 [ 0, %newFuncRoot ], [ %tmp_7_mid2_v, %._crit_edge19 ] ; [#uses=3 type=i5]
  %k = phi i10 [ 0, %newFuncRoot ], [ %k_1, %._crit_edge19 ] ; [#uses=2 type=i10]
  call void @llvm.dbg.value(metadata !{i5 %j}, i64 0, metadata !93), !dbg !92 ; [debug line = 158:49] [debug variable = j]
  %exitcond_flatten = icmp eq i14 %indvar_flatten, -8192 ; [#uses=1 type=i1]
  %indvar_flatten_next = add i14 %indvar_flatten, 1 ; [#uses=1 type=i14]
  br i1 %exitcond_flatten, label %.preheader.preheader.exitStub, label %.preheader18

._crit_edge19:                                    ; preds = %2, %._crit_edge
  %empty_7 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str7, i32 %tmp_1), !dbg !99 ; [#uses=0 type=i32] [debug line = 168:3]
  %k_1 = add i10 %k_mid2, 1, !dbg !100            ; [#uses=1 type=i10] [debug line = 159:27]
  call void @llvm.dbg.value(metadata !{i10 %k_1}, i64 0, metadata !101), !dbg !100 ; [debug line = 159:27] [debug variable = k]
  br label %.preheader17, !dbg !100               ; [debug line = 159:27]

._crit_edge:                                      ; preds = %0, %.preheader18
  %newIndex = call i5 @_ssdm_op_PartSelect.i5.i10.i32.i32(i10 %k_mid2, i32 5, i32 9) ; [#uses=1 type=i5]
  %newIndex2 = zext i5 %newIndex to i64           ; [#uses=32 type=i64]
  %tmp_10 = trunc i10 %k_mid2 to i5               ; [#uses=1 type=i5]
  %a_0_addr_1 = getelementptr [16 x i32]* %a_0, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_0_load = load i32* %a_0_addr_1, align 4      ; [#uses=1 type=i32]
  %a_1_addr_1 = getelementptr [16 x i32]* %a_1, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_1_load = load i32* %a_1_addr_1, align 4      ; [#uses=1 type=i32]
  %a_2_addr_1 = getelementptr [16 x i32]* %a_2, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_2_load = load i32* %a_2_addr_1, align 4      ; [#uses=1 type=i32]
  %a_3_addr_1 = getelementptr [16 x i32]* %a_3, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_3_load = load i32* %a_3_addr_1, align 4      ; [#uses=1 type=i32]
  %a_4_addr_1 = getelementptr [16 x i32]* %a_4, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_4_load = load i32* %a_4_addr_1, align 4      ; [#uses=1 type=i32]
  %a_5_addr_1 = getelementptr [16 x i32]* %a_5, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_5_load = load i32* %a_5_addr_1, align 4      ; [#uses=1 type=i32]
  %a_6_addr_1 = getelementptr [16 x i32]* %a_6, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_6_load = load i32* %a_6_addr_1, align 4      ; [#uses=1 type=i32]
  %a_7_addr_1 = getelementptr [16 x i32]* %a_7, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_7_load = load i32* %a_7_addr_1, align 4      ; [#uses=1 type=i32]
  %a_8_addr_1 = getelementptr [16 x i32]* %a_8, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_8_load = load i32* %a_8_addr_1, align 4      ; [#uses=1 type=i32]
  %a_9_addr_1 = getelementptr [16 x i32]* %a_9, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_9_load = load i32* %a_9_addr_1, align 4      ; [#uses=1 type=i32]
  %a_10_addr_1 = getelementptr [16 x i32]* %a_10, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_10_load = load i32* %a_10_addr_1, align 4    ; [#uses=1 type=i32]
  %a_11_addr_1 = getelementptr [16 x i32]* %a_11, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_11_load = load i32* %a_11_addr_1, align 4    ; [#uses=1 type=i32]
  %a_12_addr_1 = getelementptr [16 x i32]* %a_12, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_12_load = load i32* %a_12_addr_1, align 4    ; [#uses=1 type=i32]
  %a_13_addr_1 = getelementptr [16 x i32]* %a_13, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_13_load = load i32* %a_13_addr_1, align 4    ; [#uses=1 type=i32]
  %a_14_addr_1 = getelementptr [16 x i32]* %a_14, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_14_load = load i32* %a_14_addr_1, align 4    ; [#uses=1 type=i32]
  %a_15_addr_1 = getelementptr [16 x i32]* %a_15, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_15_load = load i32* %a_15_addr_1, align 4    ; [#uses=1 type=i32]
  %a_16_addr_1 = getelementptr [16 x i32]* %a_16, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_16_load = load i32* %a_16_addr_1, align 4    ; [#uses=1 type=i32]
  %a_17_addr_1 = getelementptr [16 x i32]* %a_17, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_17_load = load i32* %a_17_addr_1, align 4    ; [#uses=1 type=i32]
  %a_18_addr_1 = getelementptr [16 x i32]* %a_18, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_18_load = load i32* %a_18_addr_1, align 4    ; [#uses=1 type=i32]
  %a_19_addr_1 = getelementptr [16 x i32]* %a_19, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_19_load = load i32* %a_19_addr_1, align 4    ; [#uses=1 type=i32]
  %a_20_addr_1 = getelementptr [16 x i32]* %a_20, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_20_load = load i32* %a_20_addr_1, align 4    ; [#uses=1 type=i32]
  %a_21_addr_1 = getelementptr [16 x i32]* %a_21, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_21_load = load i32* %a_21_addr_1, align 4    ; [#uses=1 type=i32]
  %a_22_addr_1 = getelementptr [16 x i32]* %a_22, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_22_load = load i32* %a_22_addr_1, align 4    ; [#uses=1 type=i32]
  %a_23_addr_1 = getelementptr [16 x i32]* %a_23, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_23_load = load i32* %a_23_addr_1, align 4    ; [#uses=1 type=i32]
  %a_24_addr_1 = getelementptr [16 x i32]* %a_24, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_24_load = load i32* %a_24_addr_1, align 4    ; [#uses=1 type=i32]
  %a_25_addr_1 = getelementptr [16 x i32]* %a_25, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_25_load = load i32* %a_25_addr_1, align 4    ; [#uses=1 type=i32]
  %a_26_addr_1 = getelementptr [16 x i32]* %a_26, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_26_load = load i32* %a_26_addr_1, align 4    ; [#uses=1 type=i32]
  %a_27_addr_1 = getelementptr [16 x i32]* %a_27, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_27_load = load i32* %a_27_addr_1, align 4    ; [#uses=1 type=i32]
  %a_28_addr_1 = getelementptr [16 x i32]* %a_28, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_28_load = load i32* %a_28_addr_1, align 4    ; [#uses=1 type=i32]
  %a_29_addr_1 = getelementptr [16 x i32]* %a_29, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_29_load = load i32* %a_29_addr_1, align 4    ; [#uses=1 type=i32]
  %a_30_addr_1 = getelementptr [16 x i32]* %a_30, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_30_load = load i32* %a_30_addr_1, align 4    ; [#uses=1 type=i32]
  %a_31_addr_1 = getelementptr [16 x i32]* %a_31, i64 0, i64 %newIndex2 ; [#uses=1 type=i32*]
  %a_31_load = load i32* %a_31_addr_1, align 4    ; [#uses=1 type=i32]
  %tmp_9 = call i32 @_ssdm_op_Mux.ap_auto.32i32.i5(i32 %a_0_load, i32 %a_1_load, i32 %a_2_load, i32 %a_3_load, i32 %a_4_load, i32 %a_5_load, i32 %a_6_load, i32 %a_7_load, i32 %a_8_load, i32 %a_9_load, i32 %a_10_load, i32 %a_11_load, i32 %a_12_load, i32 %a_13_load, i32 %a_14_load, i32 %a_15_load, i32 %a_16_load, i32 %a_17_load, i32 %a_18_load, i32 %a_19_load, i32 %a_20_load, i32 %a_21_load, i32 %a_22_load, i32 %a_23_load, i32 %a_24_load, i32 %a_25_load, i32 %a_26_load, i32 %a_27_load, i32 %a_28_load, i32 %a_29_load, i32 %a_30_load, i32 %a_31_load, i5 %tmp_10) ; [#uses=1 type=i32]
  %tmp_2 = call i14 @_ssdm_op_BitConcatenate.i14.i10.i4(i10 %k_mid2, i4 0) ; [#uses=1 type=i14]
  %tmp_3_cast = zext i14 %tmp_2 to i15, !dbg !96  ; [#uses=1 type=i15] [debug line = 165:4]
  %tmp_7 = add i15 %tmp_3_cast, %tmp_7_mid2_cast, !dbg !96 ; [#uses=1 type=i15] [debug line = 165:4]
  %tmp_7_cast = zext i15 %tmp_7 to i64, !dbg !96  ; [#uses=1 type=i64] [debug line = 165:4]
  %B_addr = getelementptr [8192 x i32]* %B, i64 0, i64 %tmp_7_cast, !dbg !96 ; [#uses=1 type=i32*] [debug line = 165:4]
  %B_load = load i32* %B_addr, align 4, !dbg !96  ; [#uses=1 type=i32] [debug line = 165:4]
  %tmp_4 = mul nsw i32 %tmp_9, %B_load, !dbg !96  ; [#uses=1 type=i32] [debug line = 165:4]
  %tmp_5 = add nsw i32 %tmp_4, %p_011_1, !dbg !96 ; [#uses=2 type=i32] [debug line = 165:4]
  call void @llvm.dbg.value(metadata !{i32 %tmp_5}, i64 0, metadata !102), !dbg !96 ; [debug line = 165:4] [debug variable = tmp]
  %tmp_8 = icmp eq i10 %k_mid2, 511, !dbg !103    ; [#uses=1 type=i1] [debug line = 167:4]
  store i32 %tmp_5, i32* %tmp
  br i1 %tmp_8, label %2, label %._crit_edge19, !dbg !103 ; [debug line = 167:4]

; <label>:0                                       ; preds = %branch31, %branch30, %branch29, %branch28, %branch27, %branch26, %branch25, %branch24, %branch23, %branch22, %branch21, %branch20, %branch19, %branch18, %branch17, %branch16, %branch15, %branch14, %branch13, %branch12, %branch11, %branch10, %branch9, %branch8, %branch7, %branch6, %branch5, %branch4, %branch3, %branch2, %branch1, %branch0
  br label %._crit_edge, !dbg !104                ; [debug line = 164:4]

branch0:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_0_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

; <label>:1                                       ; preds = %.preheader18
  %a_fifo_V_read = call i32 @_ssdm_op_Read.ap_fifo.volatile.i32P(i32* %a_fifo_V), !dbg !107 ; [#uses=32 type=i32] [debug line = 131:9@163:12]
  %newIndex1 = call i5 @_ssdm_op_PartSelect.i5.i10.i32.i32(i10 %k_mid2, i32 5, i32 9) ; [#uses=1 type=i5]
  %newIndex3 = zext i5 %newIndex1 to i64          ; [#uses=32 type=i64]
  %a_0_addr = getelementptr [16 x i32]* %a_0, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_1_addr = getelementptr [16 x i32]* %a_1, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_2_addr = getelementptr [16 x i32]* %a_2, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_3_addr = getelementptr [16 x i32]* %a_3, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_4_addr = getelementptr [16 x i32]* %a_4, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_5_addr = getelementptr [16 x i32]* %a_5, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_6_addr = getelementptr [16 x i32]* %a_6, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_7_addr = getelementptr [16 x i32]* %a_7, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_8_addr = getelementptr [16 x i32]* %a_8, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_9_addr = getelementptr [16 x i32]* %a_9, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_10_addr = getelementptr [16 x i32]* %a_10, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_11_addr = getelementptr [16 x i32]* %a_11, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_12_addr = getelementptr [16 x i32]* %a_12, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_13_addr = getelementptr [16 x i32]* %a_13, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_14_addr = getelementptr [16 x i32]* %a_14, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_15_addr = getelementptr [16 x i32]* %a_15, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_16_addr = getelementptr [16 x i32]* %a_16, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_17_addr = getelementptr [16 x i32]* %a_17, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_18_addr = getelementptr [16 x i32]* %a_18, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_19_addr = getelementptr [16 x i32]* %a_19, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_20_addr = getelementptr [16 x i32]* %a_20, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_21_addr = getelementptr [16 x i32]* %a_21, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_22_addr = getelementptr [16 x i32]* %a_22, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_23_addr = getelementptr [16 x i32]* %a_23, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_24_addr = getelementptr [16 x i32]* %a_24, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_25_addr = getelementptr [16 x i32]* %a_25, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_26_addr = getelementptr [16 x i32]* %a_26, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_27_addr = getelementptr [16 x i32]* %a_27, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_28_addr = getelementptr [16 x i32]* %a_28, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_29_addr = getelementptr [16 x i32]* %a_29, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_30_addr = getelementptr [16 x i32]* %a_30, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %a_31_addr = getelementptr [16 x i32]* %a_31, i64 0, i64 %newIndex3, !dbg !106 ; [#uses=1 type=i32*] [debug line = 163:12]
  %tmp_6 = trunc i10 %k_mid2 to i5                ; [#uses=1 type=i5]
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
  ], !dbg !106                                    ; [debug line = 163:12]

branch1:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_1_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch2:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_2_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch3:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_3_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch4:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_4_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch5:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_5_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch6:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_6_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch7:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_7_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch8:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_8_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch9:                                          ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_9_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch10:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_10_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch11:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_11_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch12:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_12_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch13:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_13_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch14:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_14_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch15:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_15_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch16:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_16_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch17:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_17_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch18:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_18_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch19:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_19_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch20:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_20_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch21:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_21_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch22:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_22_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch23:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_23_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch24:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_24_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch25:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_25_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch26:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_26_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch27:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_27_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch28:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_28_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch29:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_29_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch30:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_30_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

branch31:                                         ; preds = %1
  store i32 %a_fifo_V_read, i32* %a_31_addr, align 4, !dbg !106 ; [debug line = 163:12]
  br label %0, !dbg !106                          ; [debug line = 163:12]

; <label>:2                                       ; preds = %._crit_edge
  call void @llvm.dbg.value(metadata !{i32 %tmp_5}, i64 0, metadata !84), !dbg !108 ; [debug line = 145:31@106:9@167:21] [debug variable = tmp]
  call void @_ssdm_op_Write.ap_fifo.volatile.i32P(i32* %c_fifo_V, i32 %tmp_5), !dbg !113 ; [debug line = 146:9@106:9@167:21]
  br label %._crit_edge19, !dbg !112              ; [debug line = 167:21]
}

; [#uses=1]
define internal fastcc void @matrix_mult_large_mxv_Loop_1_proc50(i32 %a_offset_address, i32* %memory_0, i32* %a_fifo_V, i32 %c_offset_address, i32* %c_offset_address_out) {
entry:
  call void (...)* @_ssdm_op_SpecInterface(i32* %a_fifo_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str41, [1 x i8]* @p_str42, [1 x i8]* @p_str43, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str44)
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_0, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2)
  call void (...)* @_ssdm_op_SpecInterface(i32* %c_offset_address_out, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str52, [1 x i8]* @p_str53, [1 x i8]* @p_str54, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str55)
  %c_offset_address_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %c_offset_address) ; [#uses=1 type=i32]
  %a_offset_address_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %a_offset_address) ; [#uses=1 type=i32]
  call void @_ssdm_op_Write.ap_fifo.i32P(i32* %c_offset_address_out, i32 %c_offset_address_read)
  call void @llvm.dbg.declare(metadata !{i32* %a_fifo_V}, metadata !114), !dbg !118 ; [debug line = 149:25] [debug variable = a_fifo.V]
  %tmp_s = zext i32 %a_offset_address_read to i64, !dbg !119 ; [#uses=1 type=i64] [debug line = 153:2]
  %memory_0_addr = getelementptr inbounds i32* %memory_0, i64 %tmp_s, !dbg !119 ; [#uses=2 type=i32*] [debug line = 153:2]
  %memory_0_addr_rd_req = call i1 @_ssdm_op_ReadReq.m_axi.i32P(i32* %memory_0_addr, i32 512), !dbg !122 ; [#uses=0 type=i1] [debug line = 145:31@106:9@153:2]
  br label %0

; <label>:0                                       ; preds = %1, %entry
  %j_0_i_i_i_i = phi i10 [ 0, %entry ], [ %j, %1 ] ; [#uses=2 type=i10]
  %exitcond16_i_i_i_i = icmp eq i10 %j_0_i_i_i_i, -512, !dbg !124 ; [#uses=1 type=i1] [debug line = 151:15]
  %j = add i10 %j_0_i_i_i_i, 1, !dbg !125         ; [#uses=1 type=i10] [debug line = 151:26]
  br i1 %exitcond16_i_i_i_i, label %.exit, label %1, !dbg !124 ; [debug line = 151:15]

; <label>:1                                       ; preds = %0
  %empty = call i32 (...)* @_ssdm_op_SpecLoopTripCount(i64 512, i64 512, i64 512) ; [#uses=0 type=i32]
  %tmp_1_i_i = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str6), !dbg !126 ; [#uses=1 type=i32] [debug line = 151:32]
  call void (...)* @_ssdm_op_SpecPipeline(i32 1, i32 1, i32 1, i32 0, [1 x i8]* @p_str2) nounwind, !dbg !127 ; [debug line = 152:1]
  %tmp = call i32 @_ssdm_op_Read.m_axi.i32P(i32* %memory_0_addr), !dbg !122 ; [#uses=1 type=i32] [debug line = 145:31@106:9@153:2]
  call void @llvm.dbg.value(metadata !{i32 %tmp}, i64 0, metadata !84) nounwind, !dbg !122 ; [debug line = 145:31@106:9@153:2] [debug variable = tmp]
  call void @_ssdm_op_Write.ap_fifo.volatile.i32P(i32* %a_fifo_V, i32 %tmp), !dbg !128 ; [debug line = 146:9@106:9@153:2]
  %empty_8 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str6, i32 %tmp_1_i_i), !dbg !129 ; [#uses=0 type=i32] [debug line = 154:2]
  call void @llvm.dbg.value(metadata !{i10 %j}, i64 0, metadata !130) nounwind, !dbg !125 ; [debug line = 151:26] [debug variable = j]
  br label %0, !dbg !125                          ; [debug line = 151:26]

.exit:                                            ; preds = %0
  ret void
}

; [#uses=8]
define internal fastcc void @matrix_mult_large_mxv(i32* %memory_0, i32* %memory_3, i32 %a_offset_address, [8192 x i32]* nocapture %B, i32 %c_offset_address) {
codeRepl:
  %c_offset_address_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %c_offset_address) ; [#uses=1 type=i32]
  call void @llvm.dbg.value(metadata !{i32 %c_offset_address_read}, i64 0, metadata !131), !dbg !132 ; [debug line = 142:8] [debug variable = c_offset_address]
  %a_offset_address_read = call i32 @_ssdm_op_Read.ap_auto.i32(i32 %a_offset_address) ; [#uses=1 type=i32]
  call void @llvm.dbg.value(metadata !{i32 %a_offset_address_read}, i64 0, metadata !133), !dbg !134 ; [debug line = 140:8] [debug variable = a_offset_address]
  %c_offset_address_channel = alloca i32, align 4 ; [#uses=5 type=i32*]
  call void (...)* @_ssdm_op_SpecDataflowPipeline(i32 -1, [1 x i8]* @p_str2) nounwind, !dbg !135 ; [debug line = 144:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_3, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_0, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind
  %a_fifo_V = alloca i32, align 4                 ; [#uses=5 type=i32*]
  %empty = call i32 (...)* @_ssdm_op_SpecChannel([9 x i8]* @a_fifo_OC_V_str, i32 1, [1 x i8]* @p_str40, [1 x i8]* @p_str40, i32 1, i32 1, i32* %a_fifo_V, i32* %a_fifo_V) ; [#uses=0 type=i32]
  call void (...)* @_ssdm_op_SpecInterface(i32* %a_fifo_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str41, [1 x i8]* @p_str42, [1 x i8]* @p_str43, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str44)
  %c_fifo_V = alloca i32, align 4                 ; [#uses=5 type=i32*]
  %empty_9 = call i32 (...)* @_ssdm_op_SpecChannel([9 x i8]* @c_fifo_OC_V_str, i32 1, [1 x i8]* @p_str45, [1 x i8]* @p_str45, i32 1, i32 1, i32* %c_fifo_V, i32* %c_fifo_V) ; [#uses=0 type=i32]
  call void (...)* @_ssdm_op_SpecInterface(i32* %c_fifo_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str46, [1 x i8]* @p_str47, [1 x i8]* @p_str48, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str49)
  call void @llvm.dbg.value(metadata !{i32* %memory_0}, i64 0, metadata !136), !dbg !137 ; [debug line = 138:22] [debug variable = memory_0]
  call void @llvm.dbg.value(metadata !{i32* %memory_3}, i64 0, metadata !138), !dbg !139 ; [debug line = 139:17] [debug variable = memory_3]
  call void @llvm.dbg.value(metadata !{i32 %a_offset_address}, i64 0, metadata !133), !dbg !134 ; [debug line = 140:8] [debug variable = a_offset_address]
  call void @llvm.dbg.value(metadata !{[8192 x i32]* %B}, i64 0, metadata !140), !dbg !144 ; [debug line = 141:14] [debug variable = B]
  call void @llvm.dbg.value(metadata !{i32 %c_offset_address}, i64 0, metadata !131), !dbg !132 ; [debug line = 142:8] [debug variable = c_offset_address]
  call void @llvm.dbg.declare(metadata !{i32* %c_fifo_V}, metadata !145), !dbg !147 ; [debug line = 150:25] [debug variable = c_fifo.V]
  %empty_10 = call i32 (...)* @_ssdm_op_SpecChannel([25 x i8]* @c_offset_address_channel_str, i32 1, [1 x i8]* @p_str56, [1 x i8]* @p_str56, i32 2, i32 0, i32* %c_offset_address_channel, i32* %c_offset_address_channel) ; [#uses=0 type=i32]
  call void (...)* @_ssdm_op_SpecInterface(i32* %c_offset_address_channel, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str57, [1 x i8]* @p_str58, [1 x i8]* @p_str59, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str60)
  call fastcc void @matrix_mult_large_mxv_Loop_1_proc50(i32 %a_offset_address_read, i32* %memory_0, i32* %a_fifo_V, i32 %c_offset_address_read, i32* %c_offset_address_channel)
  call fastcc void @matrix_mult_large_mxv_Loop_2_proc(i32* %a_fifo_V, i32* %c_fifo_V, [8192 x i32]* %B)
  call fastcc void @matrix_mult_large_mxv_Loop_3_proc(i32* nocapture %c_offset_address_channel, i32* %c_fifo_V, i32* %memory_3)
  ret void, !dbg !148                             ; [debug line = 179:1]
}

; [#uses=0]
define void @matrix_mult_large(i32* %memory_0, i32* %memory_1_0, i32* %memory_2_0, i32* %memory_1_1, i32* %memory_2_1, i32* %memory_1_2, i32* %memory_2_2, i32* %memory_1_3, i32* %memory_2_3, i32* %memory_1_4, i32* %memory_2_4, i32* %memory_1_5, i32* %memory_2_5, i32* %memory_1_6, i32* %memory_2_6, i32* %memory_1_7, i32* %memory_2_7, i32 %a_offset_address, i32 %b_offset_address, i32 %c_offset_address) nounwind uwtable {
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_0) nounwind, !map !149
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_0) nounwind, !map !155
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_0) nounwind, !map !159
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_1) nounwind, !map !163
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_1) nounwind, !map !167
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_2) nounwind, !map !171
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_2) nounwind, !map !175
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_3) nounwind, !map !179
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_3) nounwind, !map !183
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_4) nounwind, !map !187
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_4) nounwind, !map !191
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_5) nounwind, !map !195
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_5) nounwind, !map !199
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_6) nounwind, !map !203
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_6) nounwind, !map !207
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_1_7) nounwind, !map !211
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %memory_2_7) nounwind, !map !215
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %a_offset_address) nounwind, !map !219
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %b_offset_address) nounwind, !map !225
  call void (...)* @_ssdm_op_SpecBitsMap(i32 %c_offset_address) nounwind, !map !229
  call void (...)* @_ssdm_op_SpecTopModule([18 x i8]* @matrix_mult_large_str) nounwind
  %c_offset_address_read = call i32 @_ssdm_op_Read.s_axilite.i32(i32 %c_offset_address) nounwind ; [#uses=2 type=i32]
  call void @llvm.dbg.value(metadata !{i32 %c_offset_address_read}, i64 0, metadata !233), !dbg !237 ; [debug line = 41:10] [debug variable = c_offset_address]
  %b_offset_address_read = call i32 @_ssdm_op_Read.s_axilite.i32(i32 %b_offset_address) nounwind ; [#uses=1 type=i32]
  call void @llvm.dbg.value(metadata !{i32 %b_offset_address_read}, i64 0, metadata !238), !dbg !239 ; [debug line = 40:10] [debug variable = b_offset_address]
  %a_offset_address_read = call i32 @_ssdm_op_Read.s_axilite.i32(i32 %a_offset_address) nounwind ; [#uses=1 type=i32]
  call void @llvm.dbg.value(metadata !{i32 %a_offset_address_read}, i64 0, metadata !240), !dbg !241 ; [debug line = 39:10] [debug variable = a_offset_address]
  %B_0 = alloca [8192 x i32], align 4             ; [#uses=2 type=[8192 x i32]*]
  %B_1 = alloca [8192 x i32], align 4             ; [#uses=2 type=[8192 x i32]*]
  %B_2 = alloca [8192 x i32], align 4             ; [#uses=2 type=[8192 x i32]*]
  %B_3 = alloca [8192 x i32], align 4             ; [#uses=2 type=[8192 x i32]*]
  %B_4 = alloca [8192 x i32], align 4             ; [#uses=2 type=[8192 x i32]*]
  %B_5 = alloca [8192 x i32], align 4             ; [#uses=2 type=[8192 x i32]*]
  %B_6 = alloca [8192 x i32], align 4             ; [#uses=2 type=[8192 x i32]*]
  %B_7 = alloca [8192 x i32], align 4             ; [#uses=2 type=[8192 x i32]*]
  call void @llvm.dbg.value(metadata !{i32* %memory_0}, i64 0, metadata !242), !dbg !243 ; [debug line = 20:36] [debug variable = memory_0]
  call void @llvm.dbg.value(metadata !{i32* %memory_1_0}, i64 0, metadata !244), !dbg !245 ; [debug line = 21:26] [debug variable = memory_1_0]
  call void @llvm.dbg.value(metadata !{i32* %memory_2_0}, i64 0, metadata !246), !dbg !247 ; [debug line = 22:17] [debug variable = memory_2_0]
  call void @llvm.dbg.value(metadata !{i32* %memory_1_1}, i64 0, metadata !248), !dbg !249 ; [debug line = 23:26] [debug variable = memory_1_1]
  call void @llvm.dbg.value(metadata !{i32* %memory_2_1}, i64 0, metadata !250), !dbg !251 ; [debug line = 24:17] [debug variable = memory_2_1]
  call void @llvm.dbg.value(metadata !{i32* %memory_1_2}, i64 0, metadata !252), !dbg !253 ; [debug line = 25:26] [debug variable = memory_1_2]
  call void @llvm.dbg.value(metadata !{i32* %memory_2_2}, i64 0, metadata !254), !dbg !255 ; [debug line = 26:17] [debug variable = memory_2_2]
  call void @llvm.dbg.value(metadata !{i32* %memory_1_3}, i64 0, metadata !256), !dbg !257 ; [debug line = 27:26] [debug variable = memory_1_3]
  call void @llvm.dbg.value(metadata !{i32* %memory_2_3}, i64 0, metadata !258), !dbg !259 ; [debug line = 28:17] [debug variable = memory_2_3]
  call void @llvm.dbg.value(metadata !{i32* %memory_1_4}, i64 0, metadata !260), !dbg !261 ; [debug line = 30:26] [debug variable = memory_1_4]
  call void @llvm.dbg.value(metadata !{i32* %memory_2_4}, i64 0, metadata !262), !dbg !263 ; [debug line = 31:17] [debug variable = memory_2_4]
  call void @llvm.dbg.value(metadata !{i32* %memory_1_5}, i64 0, metadata !264), !dbg !265 ; [debug line = 32:26] [debug variable = memory_1_5]
  call void @llvm.dbg.value(metadata !{i32* %memory_2_5}, i64 0, metadata !266), !dbg !267 ; [debug line = 33:17] [debug variable = memory_2_5]
  call void @llvm.dbg.value(metadata !{i32* %memory_1_6}, i64 0, metadata !268), !dbg !269 ; [debug line = 34:26] [debug variable = memory_1_6]
  call void @llvm.dbg.value(metadata !{i32* %memory_2_6}, i64 0, metadata !270), !dbg !271 ; [debug line = 35:17] [debug variable = memory_2_6]
  call void @llvm.dbg.value(metadata !{i32* %memory_1_7}, i64 0, metadata !272), !dbg !273 ; [debug line = 36:26] [debug variable = memory_1_7]
  call void @llvm.dbg.value(metadata !{i32* %memory_2_7}, i64 0, metadata !274), !dbg !275 ; [debug line = 37:17] [debug variable = memory_2_7]
  call void @llvm.dbg.value(metadata !{i32 %a_offset_address}, i64 0, metadata !240), !dbg !241 ; [debug line = 39:10] [debug variable = a_offset_address]
  call void @llvm.dbg.value(metadata !{i32 %b_offset_address}, i64 0, metadata !238), !dbg !239 ; [debug line = 40:10] [debug variable = b_offset_address]
  call void @llvm.dbg.value(metadata !{i32 %c_offset_address}, i64 0, metadata !233), !dbg !237 ; [debug line = 41:10] [debug variable = c_offset_address]
  call void (...)* @_ssdm_op_SpecInterface(i32 0, [10 x i8]* @p_str, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2) nounwind, !dbg !276 ; [debug line = 44:1]
  call void (...)* @_ssdm_op_SpecInterface(i32 %a_offset_address, [10 x i8]* @p_str, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2) nounwind, !dbg !278 ; [debug line = 46:1]
  call void (...)* @_ssdm_op_SpecInterface(i32 %b_offset_address, [10 x i8]* @p_str, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2) nounwind, !dbg !279 ; [debug line = 47:1]
  call void (...)* @_ssdm_op_SpecInterface(i32 %c_offset_address, [10 x i8]* @p_str, i32 0, i32 0, i32 0, i32 0, [12 x i8]* @p_str1, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2) nounwind, !dbg !280 ; [debug line = 48:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_0, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !281 ; [debug line = 49:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_0, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !282 ; [debug line = 51:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_0, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !283 ; [debug line = 52:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_1, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !284 ; [debug line = 53:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_1, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !285 ; [debug line = 54:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_2, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !286 ; [debug line = 56:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_2, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !287 ; [debug line = 57:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_3, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !288 ; [debug line = 58:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_3, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !289 ; [debug line = 59:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_4, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !290 ; [debug line = 62:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_4, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !291 ; [debug line = 63:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_5, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !292 ; [debug line = 64:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_5, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !293 ; [debug line = 65:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_6, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !294 ; [debug line = 67:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_6, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !295 ; [debug line = 68:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_1_7, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !296 ; [debug line = 69:1]
  call void (...)* @_ssdm_op_SpecInterface(i32* %memory_2_7, [6 x i8]* @p_str3, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str2, [1 x i8]* @p_str2, [1 x i8]* @p_str2, i32 16, i32 16, i32 16, i32 16, [1 x i8]* @p_str2) nounwind, !dbg !297 ; [debug line = 70:1]
  call void @llvm.dbg.declare(metadata !{[8192 x i32]* %B_0}, metadata !298), !dbg !299 ; [debug line = 75:12] [debug variable = B_0]
  call void @llvm.dbg.declare(metadata !{[8192 x i32]* %B_1}, metadata !300), !dbg !301 ; [debug line = 76:12] [debug variable = B_1]
  call void @llvm.dbg.declare(metadata !{[8192 x i32]* %B_2}, metadata !302), !dbg !303 ; [debug line = 77:12] [debug variable = B_2]
  call void @llvm.dbg.declare(metadata !{[8192 x i32]* %B_3}, metadata !304), !dbg !305 ; [debug line = 78:12] [debug variable = B_3]
  call void @llvm.dbg.declare(metadata !{[8192 x i32]* %B_4}, metadata !306), !dbg !307 ; [debug line = 79:12] [debug variable = B_4]
  call void @llvm.dbg.declare(metadata !{[8192 x i32]* %B_5}, metadata !308), !dbg !309 ; [debug line = 80:12] [debug variable = B_5]
  call void @llvm.dbg.declare(metadata !{[8192 x i32]* %B_6}, metadata !310), !dbg !311 ; [debug line = 81:12] [debug variable = B_6]
  call void @llvm.dbg.declare(metadata !{[8192 x i32]* %B_7}, metadata !312), !dbg !313 ; [debug line = 82:12] [debug variable = B_7]
  %tmp_9 = zext i32 %b_offset_address_read to i64, !dbg !314 ; [#uses=1 type=i64] [debug line = 92:2]
  %memory_0_addr = getelementptr inbounds i32* %memory_0, i64 %tmp_9, !dbg !314 ; [#uses=2 type=i32*] [debug line = 92:2]
  br label %.loopexit, !dbg !321                  ; [debug line = 87:16]

.loopexit:                                        ; preds = %.preheader, %0
  %p1 = phi i3 [ 0, %0 ], [ %p, %.preheader ]     ; [#uses=3 type=i3]
  %exitcond4 = icmp eq i3 %p1, -4, !dbg !321      ; [#uses=1 type=i1] [debug line = 87:16]
  %p = add i3 %p1, 1, !dbg !322                   ; [#uses=1 type=i3] [debug line = 87:82]
  call void @llvm.dbg.value(metadata !{i3 %p}, i64 0, metadata !323), !dbg !322 ; [debug line = 87:82] [debug variable = p]
  br i1 %exitcond4, label %24, label %.preheader6.preheader, !dbg !321 ; [debug line = 87:16]

.preheader6.preheader:                            ; preds = %.loopexit
  %empty = call i32 (...)* @_ssdm_op_SpecLoopTripCount(i64 4, i64 4, i64 4) nounwind ; [#uses=0 type=i32]
  %tmp_14 = trunc i3 %p1 to i2                    ; [#uses=2 type=i2]
  %tmp_s = call i9 @_ssdm_op_BitConcatenate.i9.i2.i7(i2 %tmp_14, i7 0), !dbg !324 ; [#uses=8 type=i9] [debug line = 94:5]
  %tmp_cast2 = zext i9 %tmp_s to i10, !dbg !324   ; [#uses=3 type=i10] [debug line = 94:5]
  %tmp_1 = or i9 %tmp_s, 16, !dbg !325            ; [#uses=2 type=i9] [debug line = 97:10]
  %tmp_15_cast1 = zext i9 %tmp_1 to i10, !dbg !325 ; [#uses=3 type=i10] [debug line = 97:10]
  %tmp_2 = or i9 %tmp_s, 32, !dbg !326            ; [#uses=2 type=i9] [debug line = 100:10]
  %tmp_16_cast1 = zext i9 %tmp_2 to i10, !dbg !326 ; [#uses=3 type=i10] [debug line = 100:10]
  %tmp_3 = or i9 %tmp_s, 48, !dbg !327            ; [#uses=2 type=i9] [debug line = 103:10]
  %tmp_17_cast9 = zext i9 %tmp_3 to i10, !dbg !327 ; [#uses=3 type=i10] [debug line = 103:10]
  %tmp_4 = or i9 %tmp_s, 64, !dbg !328            ; [#uses=2 type=i9] [debug line = 106:10]
  %tmp_18_cast8 = zext i9 %tmp_4 to i10, !dbg !328 ; [#uses=3 type=i10] [debug line = 106:10]
  %tmp_5 = or i9 %tmp_s, 80, !dbg !329            ; [#uses=2 type=i9] [debug line = 109:10]
  %tmp_19_cast7 = zext i9 %tmp_5 to i10, !dbg !329 ; [#uses=3 type=i10] [debug line = 109:10]
  %tmp_6 = or i9 %tmp_s, 96, !dbg !330            ; [#uses=2 type=i9] [debug line = 112:10]
  %tmp_20_cast6 = zext i9 %tmp_6 to i10, !dbg !330 ; [#uses=3 type=i10] [debug line = 112:10]
  %tmp_7 = or i9 %tmp_s, 112, !dbg !331           ; [#uses=2 type=i9] [debug line = 115:10]
  %tmp_21_cast5 = zext i9 %tmp_7 to i10, !dbg !331 ; [#uses=3 type=i10] [debug line = 115:10]
  %tmp_8 = add i10 128, %tmp_cast2, !dbg !331     ; [#uses=1 type=i10] [debug line = 115:10]
  %memory_0_addr_1_rd_req = call i1 @_ssdm_op_ReadReq.m_axi.i32P(i32* %memory_0_addr, i32 262144) nounwind, !dbg !314 ; [#uses=0 type=i1] [debug line = 92:2]
  br label %.preheader5, !dbg !332                ; [debug line = 89:16]

.preheader.preheader:                             ; preds = %.preheader5
  %tmp417_cast = zext i9 %tmp_1 to i32, !dbg !333 ; [#uses=1 type=i32] [debug line = 125:4]
  %tmp618_cast = zext i9 %tmp_2 to i32, !dbg !336 ; [#uses=1 type=i32] [debug line = 126:4]
  %tmp819_cast = zext i9 %tmp_3 to i32, !dbg !337 ; [#uses=1 type=i32] [debug line = 127:4]
  %tmp1020_cast = zext i9 %tmp_4 to i32, !dbg !338 ; [#uses=1 type=i32] [debug line = 129:4]
  %tmp1221_cast = zext i9 %tmp_5 to i32, !dbg !339 ; [#uses=1 type=i32] [debug line = 130:4]
  %tmp1422_cast = zext i9 %tmp_6 to i32, !dbg !340 ; [#uses=1 type=i32] [debug line = 131:4]
  %tmp1623_cast = zext i9 %tmp_7 to i32, !dbg !341 ; [#uses=1 type=i32] [debug line = 132:4]
  br label %.preheader, !dbg !342                 ; [debug line = 123:16]

.preheader5:                                      ; preds = %22, %.preheader6.preheader
  %indvar_flatten = phi i19 [ 0, %.preheader6.preheader ], [ %indvar_flatten_next, %22 ] ; [#uses=2 type=i19]
  %i = phi i10 [ 0, %.preheader6.preheader ], [ %tmp_24_cast_cast_mid2_v_v_v, %22 ] ; [#uses=2 type=i10]
  %j = phi i10 [ 0, %.preheader6.preheader ], [ %j_1, %22 ] ; [#uses=2 type=i10]
  call void @llvm.dbg.value(metadata !{i10 %i_2}, i64 0, metadata !343), !dbg !344 ; [debug line = 89:27] [debug variable = i]
  %exitcond_flatten = icmp eq i19 %indvar_flatten, -262144 ; [#uses=1 type=i1]
  %indvar_flatten_next = add i19 %indvar_flatten, 1 ; [#uses=1 type=i19]
  br i1 %exitcond_flatten, label %.preheader.preheader, label %.preheader6

; <label>:1                                       ; preds = %.preheader6
  %tmp_17 = sub i10 %j_mid2, %tmp_cast2, !dbg !345 ; [#uses=1 type=i10] [debug line = 95:6]
  %tmp_21_cast = sext i10 %tmp_17 to i15, !dbg !345 ; [#uses=1 type=i15] [debug line = 95:6]
  %tmp_18 = add i15 %tmp_16_cast, %tmp_21_cast, !dbg !345 ; [#uses=1 type=i15] [debug line = 95:6]
  %tmp_22_cast = sext i15 %tmp_18 to i64, !dbg !345 ; [#uses=1 type=i64] [debug line = 95:6]
  %B_0_addr = getelementptr [8192 x i32]* %B_0, i64 0, i64 %tmp_22_cast, !dbg !345 ; [#uses=1 type=i32*] [debug line = 95:6]
  store i32 %tmp, i32* %B_0_addr, align 4, !dbg !345 ; [debug line = 95:6]
  br label %22, !dbg !345                         ; [debug line = 95:6]

; <label>:2                                       ; preds = %.preheader6
  %ult = icmp ult i10 %j_mid2, %tmp_15_cast1, !dbg !325 ; [#uses=1 type=i1] [debug line = 97:10]
  %rev1 = xor i1 %ult, true, !dbg !325            ; [#uses=1 type=i1] [debug line = 97:10]
  %tmp_19 = icmp ult i10 %j_mid2, %tmp_16_cast1, !dbg !325 ; [#uses=1 type=i1] [debug line = 97:10]
  %or_cond7 = and i1 %rev1, %tmp_19, !dbg !325    ; [#uses=1 type=i1] [debug line = 97:10]
  br i1 %or_cond7, label %3, label %4, !dbg !325  ; [debug line = 97:10]

; <label>:3                                       ; preds = %2
  %tmp_28 = sub i10 %j_mid2, %tmp_15_cast1, !dbg !346 ; [#uses=1 type=i10] [debug line = 98:6]
  %tmp_35_cast = sext i10 %tmp_28 to i15, !dbg !346 ; [#uses=1 type=i15] [debug line = 98:6]
  %tmp_29 = add i15 %tmp_16_cast, %tmp_35_cast, !dbg !346 ; [#uses=1 type=i15] [debug line = 98:6]
  %tmp_36_cast = sext i15 %tmp_29 to i64, !dbg !346 ; [#uses=1 type=i64] [debug line = 98:6]
  %B_1_addr = getelementptr [8192 x i32]* %B_1, i64 0, i64 %tmp_36_cast, !dbg !346 ; [#uses=1 type=i32*] [debug line = 98:6]
  store i32 %tmp, i32* %B_1_addr, align 4, !dbg !346 ; [debug line = 98:6]
  br label %21, !dbg !346                         ; [debug line = 98:6]

; <label>:4                                       ; preds = %2
  %ult2 = icmp ult i10 %j_mid2, %tmp_16_cast1, !dbg !326 ; [#uses=1 type=i1] [debug line = 100:10]
  %rev2 = xor i1 %ult2, true, !dbg !326           ; [#uses=1 type=i1] [debug line = 100:10]
  %tmp_30 = icmp ult i10 %j_mid2, %tmp_17_cast9, !dbg !326 ; [#uses=1 type=i1] [debug line = 100:10]
  %or_cond8 = and i1 %rev2, %tmp_30, !dbg !326    ; [#uses=1 type=i1] [debug line = 100:10]
  br i1 %or_cond8, label %5, label %6, !dbg !326  ; [debug line = 100:10]

; <label>:5                                       ; preds = %4
  %tmp_31 = sub i10 %j_mid2, %tmp_16_cast1, !dbg !347 ; [#uses=1 type=i10] [debug line = 101:6]
  %tmp_40_cast = sext i10 %tmp_31 to i15, !dbg !347 ; [#uses=1 type=i15] [debug line = 101:6]
  %tmp_32 = add i15 %tmp_16_cast, %tmp_40_cast, !dbg !347 ; [#uses=1 type=i15] [debug line = 101:6]
  %tmp_41_cast = sext i15 %tmp_32 to i64, !dbg !347 ; [#uses=1 type=i64] [debug line = 101:6]
  %B_2_addr = getelementptr [8192 x i32]* %B_2, i64 0, i64 %tmp_41_cast, !dbg !347 ; [#uses=1 type=i32*] [debug line = 101:6]
  store i32 %tmp, i32* %B_2_addr, align 4, !dbg !347 ; [debug line = 101:6]
  br label %20, !dbg !347                         ; [debug line = 101:6]

; <label>:6                                       ; preds = %4
  %ult3 = icmp ult i10 %j_mid2, %tmp_17_cast9, !dbg !327 ; [#uses=1 type=i1] [debug line = 103:10]
  %rev3 = xor i1 %ult3, true, !dbg !327           ; [#uses=1 type=i1] [debug line = 103:10]
  %tmp_33 = icmp ult i10 %j_mid2, %tmp_18_cast8, !dbg !327 ; [#uses=1 type=i1] [debug line = 103:10]
  %or_cond9 = and i1 %rev3, %tmp_33, !dbg !327    ; [#uses=1 type=i1] [debug line = 103:10]
  br i1 %or_cond9, label %7, label %8, !dbg !327  ; [debug line = 103:10]

; <label>:7                                       ; preds = %6
  %tmp_34 = sub i10 %j_mid2, %tmp_17_cast9, !dbg !348 ; [#uses=1 type=i10] [debug line = 104:6]
  %tmp_45_cast = sext i10 %tmp_34 to i15, !dbg !348 ; [#uses=1 type=i15] [debug line = 104:6]
  %tmp_35 = add i15 %tmp_16_cast, %tmp_45_cast, !dbg !348 ; [#uses=1 type=i15] [debug line = 104:6]
  %tmp_46_cast = sext i15 %tmp_35 to i64, !dbg !348 ; [#uses=1 type=i64] [debug line = 104:6]
  %B_3_addr = getelementptr [8192 x i32]* %B_3, i64 0, i64 %tmp_46_cast, !dbg !348 ; [#uses=1 type=i32*] [debug line = 104:6]
  store i32 %tmp, i32* %B_3_addr, align 4, !dbg !348 ; [debug line = 104:6]
  br label %19, !dbg !348                         ; [debug line = 104:6]

; <label>:8                                       ; preds = %6
  %ult4 = icmp ult i10 %j_mid2, %tmp_18_cast8, !dbg !328 ; [#uses=1 type=i1] [debug line = 106:10]
  %rev4 = xor i1 %ult4, true, !dbg !328           ; [#uses=1 type=i1] [debug line = 106:10]
  %tmp_36 = icmp ult i10 %j_mid2, %tmp_19_cast7, !dbg !328 ; [#uses=1 type=i1] [debug line = 106:10]
  %or_cond1 = and i1 %rev4, %tmp_36, !dbg !328    ; [#uses=1 type=i1] [debug line = 106:10]
  br i1 %or_cond1, label %9, label %10, !dbg !328 ; [debug line = 106:10]

; <label>:9                                       ; preds = %8
  %tmp_37 = sub i10 %j_mid2, %tmp_18_cast8, !dbg !349 ; [#uses=1 type=i10] [debug line = 107:6]
  %tmp_50_cast = sext i10 %tmp_37 to i15, !dbg !349 ; [#uses=1 type=i15] [debug line = 107:6]
  %tmp_38 = add i15 %tmp_16_cast, %tmp_50_cast, !dbg !349 ; [#uses=1 type=i15] [debug line = 107:6]
  %tmp_51_cast = sext i15 %tmp_38 to i64, !dbg !349 ; [#uses=1 type=i64] [debug line = 107:6]
  %B_4_addr = getelementptr [8192 x i32]* %B_4, i64 0, i64 %tmp_51_cast, !dbg !349 ; [#uses=1 type=i32*] [debug line = 107:6]
  store i32 %tmp, i32* %B_4_addr, align 4, !dbg !349 ; [debug line = 107:6]
  br label %18, !dbg !349                         ; [debug line = 107:6]

; <label>:10                                      ; preds = %8
  %ult5 = icmp ult i10 %j_mid2, %tmp_19_cast7, !dbg !329 ; [#uses=1 type=i1] [debug line = 109:10]
  %rev5 = xor i1 %ult5, true, !dbg !329           ; [#uses=1 type=i1] [debug line = 109:10]
  %tmp_39 = icmp ult i10 %j_mid2, %tmp_20_cast6, !dbg !329 ; [#uses=1 type=i1] [debug line = 109:10]
  %or_cond2 = and i1 %rev5, %tmp_39, !dbg !329    ; [#uses=1 type=i1] [debug line = 109:10]
  br i1 %or_cond2, label %11, label %12, !dbg !329 ; [debug line = 109:10]

; <label>:11                                      ; preds = %10
  %tmp_40 = sub i10 %j_mid2, %tmp_19_cast7, !dbg !350 ; [#uses=1 type=i10] [debug line = 110:6]
  %tmp_55_cast = sext i10 %tmp_40 to i15, !dbg !350 ; [#uses=1 type=i15] [debug line = 110:6]
  %tmp_41 = add i15 %tmp_16_cast, %tmp_55_cast, !dbg !350 ; [#uses=1 type=i15] [debug line = 110:6]
  %tmp_56_cast = sext i15 %tmp_41 to i64, !dbg !350 ; [#uses=1 type=i64] [debug line = 110:6]
  %B_5_addr = getelementptr [8192 x i32]* %B_5, i64 0, i64 %tmp_56_cast, !dbg !350 ; [#uses=1 type=i32*] [debug line = 110:6]
  store i32 %tmp, i32* %B_5_addr, align 4, !dbg !350 ; [debug line = 110:6]
  br label %17, !dbg !350                         ; [debug line = 110:6]

; <label>:12                                      ; preds = %10
  %ult6 = icmp ult i10 %j_mid2, %tmp_20_cast6, !dbg !330 ; [#uses=1 type=i1] [debug line = 112:10]
  %rev6 = xor i1 %ult6, true, !dbg !330           ; [#uses=1 type=i1] [debug line = 112:10]
  %tmp_42 = icmp ult i10 %j_mid2, %tmp_21_cast5, !dbg !330 ; [#uses=1 type=i1] [debug line = 112:10]
  %or_cond3 = and i1 %rev6, %tmp_42, !dbg !330    ; [#uses=1 type=i1] [debug line = 112:10]
  br i1 %or_cond3, label %13, label %14, !dbg !330 ; [debug line = 112:10]

; <label>:13                                      ; preds = %12
  %tmp_43 = sub i10 %j_mid2, %tmp_20_cast6, !dbg !351 ; [#uses=1 type=i10] [debug line = 113:6]
  %tmp_60_cast = sext i10 %tmp_43 to i15, !dbg !351 ; [#uses=1 type=i15] [debug line = 113:6]
  %tmp_44 = add i15 %tmp_16_cast, %tmp_60_cast, !dbg !351 ; [#uses=1 type=i15] [debug line = 113:6]
  %tmp_61_cast = sext i15 %tmp_44 to i64, !dbg !351 ; [#uses=1 type=i64] [debug line = 113:6]
  %B_6_addr = getelementptr [8192 x i32]* %B_6, i64 0, i64 %tmp_61_cast, !dbg !351 ; [#uses=1 type=i32*] [debug line = 113:6]
  store i32 %tmp, i32* %B_6_addr, align 4, !dbg !351 ; [debug line = 113:6]
  br label %16, !dbg !351                         ; [debug line = 113:6]

; <label>:14                                      ; preds = %12
  %ult7 = icmp ult i10 %j_mid2, %tmp_21_cast5, !dbg !331 ; [#uses=1 type=i1] [debug line = 115:10]
  %rev7 = xor i1 %ult7, true, !dbg !331           ; [#uses=1 type=i1] [debug line = 115:10]
  %tmp_45 = icmp ult i10 %j_mid2, %tmp_8, !dbg !331 ; [#uses=1 type=i1] [debug line = 115:10]
  %or_cond4 = and i1 %rev7, %tmp_45, !dbg !331    ; [#uses=1 type=i1] [debug line = 115:10]
  br i1 %or_cond4, label %15, label %._crit_edge, !dbg !331 ; [debug line = 115:10]

; <label>:15                                      ; preds = %14
  %tmp_46 = sub i10 %j_mid2, %tmp_21_cast5, !dbg !352 ; [#uses=1 type=i10] [debug line = 116:6]
  %tmp_65_cast = sext i10 %tmp_46 to i15, !dbg !352 ; [#uses=1 type=i15] [debug line = 116:6]
  %tmp_47 = add i15 %tmp_16_cast, %tmp_65_cast, !dbg !352 ; [#uses=1 type=i15] [debug line = 116:6]
  %tmp_66_cast = sext i15 %tmp_47 to i64, !dbg !352 ; [#uses=1 type=i64] [debug line = 116:6]
  %B_7_addr = getelementptr [8192 x i32]* %B_7, i64 0, i64 %tmp_66_cast, !dbg !352 ; [#uses=1 type=i32*] [debug line = 116:6]
  store i32 %tmp, i32* %B_7_addr, align 4, !dbg !352 ; [debug line = 116:6]
  br label %._crit_edge, !dbg !352                ; [debug line = 116:6]

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
  %empty_11 = call i32 (...)* @_ssdm_op_SpecRegionEnd([12 x i8]* @p_str4, i32 %tmp_15) nounwind, !dbg !353 ; [#uses=0 type=i32] [debug line = 120:4]
  %j_1 = add i10 %j_mid2, 1, !dbg !354            ; [#uses=1 type=i10] [debug line = 90:28]
  call void @llvm.dbg.value(metadata !{i10 %j_1}, i64 0, metadata !355), !dbg !354 ; [debug line = 90:28] [debug variable = j]
  br label %.preheader5, !dbg !354                ; [debug line = 90:28]

.preheader6:                                      ; preds = %.preheader5
  %i_2 = add i10 %i, 1, !dbg !344                 ; [#uses=1 type=i10] [debug line = 89:27]
  call void @llvm.dbg.value(metadata !{i10 %i_2}, i64 0, metadata !343), !dbg !344 ; [debug line = 89:27] [debug variable = i]
  %empty_12 = call i32 (...)* @_ssdm_op_SpecLoopTripCount(i64 262144, i64 262144, i64 262144) nounwind ; [#uses=0 type=i32]
  %exitcond1 = icmp eq i10 %j, -512, !dbg !356    ; [#uses=2 type=i1] [debug line = 90:17]
  %j_mid2 = select i1 %exitcond1, i10 0, i10 %j   ; [#uses=25 type=i10]
  %tmp_24_cast_cast_mid2_v_v_v = select i1 %exitcond1, i10 %i_2, i10 %i, !dbg !352 ; [#uses=2 type=i10] [debug line = 116:6]
  %tmp_10 = call i14 @_ssdm_op_BitConcatenate.i14.i10.i4(i10 %tmp_24_cast_cast_mid2_v_v_v, i4 0) ; [#uses=1 type=i14]
  %tmp_16_cast = zext i14 %tmp_10 to i15, !dbg !357 ; [#uses=8 type=i15] [debug line = 90:34]
  %tmp_15 = call i32 (...)* @_ssdm_op_SpecRegionBegin([12 x i8]* @p_str4) nounwind, !dbg !357 ; [#uses=1 type=i32] [debug line = 90:34]
  call void (...)* @_ssdm_op_SpecPipeline(i32 -1, i32 1, i32 1, i32 0, [1 x i8]* @p_str2) nounwind, !dbg !358 ; [debug line = 91:1]
  %tmp = call i32 @_ssdm_op_Read.m_axi.i32P(i32* %memory_0_addr) nounwind, !dbg !314 ; [#uses=8 type=i32] [debug line = 92:2]
  call void @llvm.dbg.value(metadata !{i32 %tmp}, i64 0, metadata !359), !dbg !314 ; [debug line = 92:2] [debug variable = tmp]
  %ult1 = icmp ult i10 %j_mid2, %tmp_cast2, !dbg !324 ; [#uses=1 type=i1] [debug line = 94:5]
  %rev = xor i1 %ult1, true, !dbg !324            ; [#uses=1 type=i1] [debug line = 94:5]
  %tmp_16 = icmp ult i10 %j_mid2, %tmp_15_cast1, !dbg !324 ; [#uses=1 type=i1] [debug line = 94:5]
  %or_cond = and i1 %rev, %tmp_16, !dbg !324      ; [#uses=1 type=i1] [debug line = 94:5]
  br i1 %or_cond, label %1, label %2, !dbg !324   ; [debug line = 94:5]

.preheader:                                       ; preds = %23, %.preheader.preheader
  %i2 = phi i10 [ %i_1, %23 ], [ 0, %.preheader.preheader ] ; [#uses=3 type=i10]
  %exitcond = icmp eq i10 %i2, -512, !dbg !342    ; [#uses=1 type=i1] [debug line = 123:16]
  %empty_13 = call i32 (...)* @_ssdm_op_SpecLoopTripCount(i64 512, i64 512, i64 512) nounwind ; [#uses=0 type=i32]
  %i_1 = add i10 %i2, 1, !dbg !360                ; [#uses=1 type=i10] [debug line = 123:27]
  br i1 %exitcond, label %.loopexit, label %23, !dbg !342 ; [debug line = 123:16]

; <label>:23                                      ; preds = %.preheader
  %tmp_20 = trunc i10 %i2 to i9                   ; [#uses=2 type=i9]
  %tmp_11 = call i18 @_ssdm_op_BitConcatenate.i18.i9.i9(i9 %tmp_20, i9 0), !dbg !361 ; [#uses=1 type=i18] [debug line = 124:4]
  %tmp_26_cast = zext i18 %tmp_11 to i32, !dbg !361 ; [#uses=2 type=i32] [debug line = 124:4]
  %tmp_12 = add i32 %a_offset_address_read, %tmp_26_cast, !dbg !361 ; [#uses=8 type=i32] [debug line = 124:4]
  %tmp2 = call i18 @_ssdm_op_BitConcatenate.i18.i9.i2.i7(i9 %tmp_20, i2 %tmp_14, i7 0), !dbg !361 ; [#uses=1 type=i18] [debug line = 124:4]
  %tmp2_cast = zext i18 %tmp2 to i32, !dbg !361   ; [#uses=1 type=i32] [debug line = 124:4]
  %tmp_13 = add i32 %c_offset_address_read, %tmp2_cast, !dbg !361 ; [#uses=1 type=i32] [debug line = 124:4]
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_0, i32* %memory_2_0, i32 %tmp_12, [8192 x i32]* %B_0, i32 %tmp_13) nounwind, !dbg !361 ; [debug line = 124:4]
  %tmp3 = add i32 %c_offset_address_read, %tmp_26_cast, !dbg !333 ; [#uses=7 type=i32] [debug line = 125:4]
  %tmp_21 = add i32 %tmp417_cast, %tmp3, !dbg !333 ; [#uses=1 type=i32] [debug line = 125:4]
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_1, i32* %memory_2_1, i32 %tmp_12, [8192 x i32]* %B_1, i32 %tmp_21) nounwind, !dbg !333 ; [debug line = 125:4]
  %tmp_22 = add i32 %tmp618_cast, %tmp3, !dbg !336 ; [#uses=1 type=i32] [debug line = 126:4]
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_2, i32* %memory_2_2, i32 %tmp_12, [8192 x i32]* %B_2, i32 %tmp_22) nounwind, !dbg !336 ; [debug line = 126:4]
  %tmp_23 = add i32 %tmp819_cast, %tmp3, !dbg !337 ; [#uses=1 type=i32] [debug line = 127:4]
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_3, i32* %memory_2_3, i32 %tmp_12, [8192 x i32]* %B_3, i32 %tmp_23) nounwind, !dbg !337 ; [debug line = 127:4]
  %tmp_24 = add i32 %tmp1020_cast, %tmp3, !dbg !338 ; [#uses=1 type=i32] [debug line = 129:4]
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_4, i32* %memory_2_4, i32 %tmp_12, [8192 x i32]* %B_4, i32 %tmp_24) nounwind, !dbg !338 ; [debug line = 129:4]
  %tmp_25 = add i32 %tmp1221_cast, %tmp3, !dbg !339 ; [#uses=1 type=i32] [debug line = 130:4]
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_5, i32* %memory_2_5, i32 %tmp_12, [8192 x i32]* %B_5, i32 %tmp_25) nounwind, !dbg !339 ; [debug line = 130:4]
  %tmp_26 = add i32 %tmp1422_cast, %tmp3, !dbg !340 ; [#uses=1 type=i32] [debug line = 131:4]
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_6, i32* %memory_2_6, i32 %tmp_12, [8192 x i32]* %B_6, i32 %tmp_26) nounwind, !dbg !340 ; [debug line = 131:4]
  %tmp_27 = add i32 %tmp1623_cast, %tmp3, !dbg !341 ; [#uses=1 type=i32] [debug line = 132:4]
  call fastcc void @matrix_mult_large_mxv(i32* %memory_1_7, i32* %memory_2_7, i32 %tmp_12, [8192 x i32]* %B_7, i32 %tmp_27) nounwind, !dbg !341 ; [debug line = 132:4]
  call void @llvm.dbg.value(metadata !{i10 %i_1}, i64 0, metadata !362), !dbg !360 ; [debug line = 123:27] [debug variable = i]
  br label %.preheader, !dbg !360                 ; [debug line = 123:27]

; <label>:24                                      ; preds = %.loopexit
  ret void, !dbg !363                             ; [debug line = 136:1]
}

; [#uses=1]
declare i10 @llvm.part.select.i10(i10, i32, i32) nounwind readnone

; [#uses=44]
declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

; [#uses=11]
declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

; [#uses=1]
define weak i1 @_ssdm_op_WriteResp.m_axi.i32P(i32*) {
entry:
  ret i1 true
}

; [#uses=1]
define weak i1 @_ssdm_op_WriteReq.m_axi.i32P(i32*, i32) {
entry:
  ret i1 true
}

; [#uses=1]
define weak void @_ssdm_op_Write.m_axi.i32P(i32*, i32, i4) {
entry:
  ret void
}

; [#uses=2]
define weak void @_ssdm_op_Write.ap_fifo.volatile.i32P(i32*, i32) {
entry:
  %empty = call i32 @_autotb_FifoWrite_i32(i32* %0, i32 %1) ; [#uses=0 type=i32]
  ret void
}

; [#uses=1]
define weak void @_ssdm_op_Write.ap_fifo.i32P(i32*, i32) {
entry:
  %empty = call i32 @_autotb_FifoWrite_i32(i32* %0, i32 %1) ; [#uses=0 type=i32]
  ret void
}

; [#uses=1]
define weak void @_ssdm_op_SpecTopModule(...) {
entry:
  ret void
}

; [#uses=4]
define weak i32 @_ssdm_op_SpecRegionEnd(...) {
entry:
  ret i32 0
}

; [#uses=4]
define weak i32 @_ssdm_op_SpecRegionBegin(...) {
entry:
  ret i32 0
}

; [#uses=4]
define weak void @_ssdm_op_SpecPipeline(...) nounwind {
entry:
  ret void
}

; [#uses=6]
define weak i32 @_ssdm_op_SpecLoopTripCount(...) {
entry:
  ret i32 0
}

; [#uses=34]
define weak void @_ssdm_op_SpecInterface(...) nounwind {
entry:
  ret void
}

; [#uses=1]
define weak void @_ssdm_op_SpecDataflowPipeline(...) nounwind {
entry:
  ret void
}

; [#uses=3]
define weak i32 @_ssdm_op_SpecChannel(...) {
entry:
  ret i32 0
}

; [#uses=20]
define weak void @_ssdm_op_SpecBitsMap(...) {
entry:
  ret void
}

; [#uses=2]
define weak i1 @_ssdm_op_ReadReq.m_axi.i32P(i32*, i32) {
entry:
  ret i1 true
}

; [#uses=3]
define weak i32 @_ssdm_op_Read.s_axilite.i32(i32) {
entry:
  ret i32 %0
}

; [#uses=2]
define weak i32 @_ssdm_op_Read.m_axi.i32P(i32*) {
entry:
  %empty = load i32* %0                           ; [#uses=1 type=i32]
  ret i32 %empty
}

; [#uses=2]
define weak i32 @_ssdm_op_Read.ap_fifo.volatile.i32P(i32*) {
entry:
  %empty = call i32 @_autotb_FifoRead_i32(i32* %0) ; [#uses=1 type=i32]
  ret i32 %empty
}

; [#uses=1]
define weak i32 @_ssdm_op_Read.ap_fifo.i32P(i32*) {
entry:
  %empty = call i32 @_autotb_FifoRead_i32(i32* %0) ; [#uses=1 type=i32]
  ret i32 %empty
}

; [#uses=4]
define weak i32 @_ssdm_op_Read.ap_auto.i32(i32) {
entry:
  ret i32 %0
}

; [#uses=0]
declare i9 @_ssdm_op_PartSelect.i9.i10.i32.i32(i10, i32, i32) nounwind readnone

; [#uses=2]
define weak i5 @_ssdm_op_PartSelect.i5.i10.i32.i32(i10, i32, i32) nounwind readnone {
entry:
  %empty = call i10 @llvm.part.select.i10(i10 %0, i32 %1, i32 %2) ; [#uses=1 type=i10]
  %empty_14 = trunc i10 %empty to i5              ; [#uses=1 type=i5]
  ret i5 %empty_14
}

; [#uses=0]
declare i2 @_ssdm_op_PartSelect.i2.i3.i32.i32(i3, i32, i32) nounwind readnone

; [#uses=1]
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
  %merge = phi i32 [ %0, %entry ], [ %1, %case1 ], [ %2, %case2 ], [ %3, %case3 ], [ %4, %case4 ], [ %5, %case5 ], [ %6, %case6 ], [ %7, %case7 ], [ %8, %case8 ], [ %9, %case9 ], [ %10, %case10 ], [ %11, %case11 ], [ %12, %case12 ], [ %13, %case13 ], [ %14, %case14 ], [ %15, %case15 ], [ %16, %case16 ], [ %17, %case17 ], [ %18, %case18 ], [ %19, %case19 ], [ %20, %case20 ], [ %21, %case21 ], [ %22, %case22 ], [ %23, %case23 ], [ %24, %case24 ], [ %25, %case25 ], [ %26, %case26 ], [ %27, %case27 ], [ %28, %case28 ], [ %29, %case29 ], [ %30, %case30 ], [ %31, %case31 ] ; [#uses=1 type=i32]
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

; [#uses=1]
define weak i9 @_ssdm_op_BitConcatenate.i9.i2.i7(i2, i7) nounwind readnone {
entry:
  %empty = zext i2 %0 to i9                       ; [#uses=1 type=i9]
  %empty_15 = zext i7 %1 to i9                    ; [#uses=1 type=i9]
  %empty_16 = shl i9 %empty, 7                    ; [#uses=1 type=i9]
  %empty_17 = or i9 %empty_16, %empty_15          ; [#uses=1 type=i9]
  ret i9 %empty_17
}

; [#uses=1]
define weak i18 @_ssdm_op_BitConcatenate.i18.i9.i9(i9, i9) nounwind readnone {
entry:
  %empty = zext i9 %0 to i18                      ; [#uses=1 type=i18]
  %empty_18 = zext i9 %1 to i18                   ; [#uses=1 type=i18]
  %empty_19 = shl i18 %empty, 9                   ; [#uses=1 type=i18]
  %empty_20 = or i18 %empty_19, %empty_18         ; [#uses=1 type=i18]
  ret i18 %empty_20
}

; [#uses=1]
define weak i18 @_ssdm_op_BitConcatenate.i18.i9.i2.i7(i9, i2, i7) nounwind readnone {
entry:
  %empty = zext i2 %1 to i9                       ; [#uses=1 type=i9]
  %empty_21 = zext i7 %2 to i9                    ; [#uses=1 type=i9]
  %empty_22 = shl i9 %empty, 7                    ; [#uses=1 type=i9]
  %empty_23 = or i9 %empty_22, %empty_21          ; [#uses=1 type=i9]
  %empty_24 = zext i9 %0 to i18                   ; [#uses=1 type=i18]
  %empty_25 = zext i9 %empty_23 to i18            ; [#uses=1 type=i18]
  %empty_26 = shl i18 %empty_24, 9                ; [#uses=1 type=i18]
  %empty_27 = or i18 %empty_26, %empty_25         ; [#uses=1 type=i18]
  ret i18 %empty_27
}

; [#uses=2]
define weak i14 @_ssdm_op_BitConcatenate.i14.i10.i4(i10, i4) nounwind readnone {
entry:
  %empty = zext i10 %0 to i14                     ; [#uses=1 type=i14]
  %empty_28 = zext i4 %1 to i14                   ; [#uses=1 type=i14]
  %empty_29 = shl i14 %empty, 4                   ; [#uses=1 type=i14]
  %empty_30 = or i14 %empty_29, %empty_28         ; [#uses=1 type=i14]
  ret i14 %empty_30
}

; [#uses=2]
declare i32 @_autotb_FifoWrite_i32(i32*, i32)

; [#uses=2]
declare i32 @_autotb_FifoRead_i32(i32*)

!hls.encrypted.func = !{}
!llvm.map.gv = !{}

!0 = metadata !{i32 175, i32 35, metadata !1, null}
!1 = metadata !{i32 786443, metadata !2, i32 173, i32 54, metadata !5, i32 18} ; [ DW_TAG_lexical_block ]
!2 = metadata !{i32 786443, metadata !3, i32 173, i32 2, metadata !5, i32 17} ; [ DW_TAG_lexical_block ]
!3 = metadata !{i32 786443, metadata !4, i32 143, i32 6, metadata !5, i32 9} ; [ DW_TAG_lexical_block ]
!4 = metadata !{i32 786478, i32 0, metadata !5, metadata !"mxv", metadata !"mxv", metadata !"_Z3mxvPiS_mPA16_im", metadata !5, i32 138, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, null, null, null, metadata !17, i32 143} ; [ DW_TAG_subprogram ]
!5 = metadata !{i32 786473, metadata !"matrix_mult_large_vhls/matrix_mult.cpp", metadata !"C:\5Cws\5Cpaper-01\5Cmatrix_mult", null} ; [ DW_TAG_file_type ]
!6 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!7 = metadata !{null, metadata !8, metadata !8, metadata !11, metadata !13, metadata !11}
!8 = metadata !{i32 786447, null, metadata !"", null, i32 0, i64 64, i64 64, i64 0, i32 0, metadata !9} ; [ DW_TAG_pointer_type ]
!9 = metadata !{i32 786454, null, metadata !"DATA_TYPE", metadata !5, i32 10, i64 0, i64 0, i64 0, i32 0, metadata !10} ; [ DW_TAG_typedef ]
!10 = metadata !{i32 786468, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!11 = metadata !{i32 786454, null, metadata !"u32", metadata !5, i32 9, i64 0, i64 0, i64 0, i32 0, metadata !12} ; [ DW_TAG_typedef ]
!12 = metadata !{i32 786468, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!13 = metadata !{i32 786447, null, metadata !"", null, i32 0, i64 64, i64 64, i64 0, i32 0, metadata !14} ; [ DW_TAG_pointer_type ]
!14 = metadata !{i32 786433, null, metadata !"", null, i32 0, i64 512, i64 32, i32 0, i32 0, metadata !9, metadata !15, i32 0, i32 0} ; [ DW_TAG_array_type ]
!15 = metadata !{metadata !16}
!16 = metadata !{i32 786465, i64 0, i64 15}       ; [ DW_TAG_subrange_type ]
!17 = metadata !{metadata !18}
!18 = metadata !{i32 786468}                      ; [ DW_TAG_base_type ]
!19 = metadata !{i32 173, i32 15, metadata !2, null}
!20 = metadata !{i32 173, i32 49, metadata !2, null}
!21 = metadata !{i32 173, i32 55, metadata !1, null}
!22 = metadata !{i32 174, i32 1, metadata !1, null}
!23 = metadata !{i32 131, i32 9, metadata !24, metadata !0}
!24 = metadata !{i32 786443, metadata !25, i32 129, i32 63, metadata !27, i32 19} ; [ DW_TAG_lexical_block ]
!25 = metadata !{i32 786478, i32 0, metadata !26, metadata !"read", metadata !"read", metadata !"_ZN3hls6streamIiE4readEv", metadata !27, i32 129, metadata !28, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, null, null, metadata !68, metadata !17, i32 129} ; [ DW_TAG_subprogram ]
!26 = metadata !{i32 786489, null, metadata !"hls", metadata !27, i32 69} ; [ DW_TAG_namespace ]
!27 = metadata !{i32 786473, metadata !"C:/Xilinx/Vivado_HLS/2016.1/common/technology/autopilot\5Chls_stream.h", metadata !"C:\5Cws\5Cpaper-01\5Cmatrix_mult", null} ; [ DW_TAG_file_type ]
!28 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !29, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!29 = metadata !{metadata !10, metadata !30}
!30 = metadata !{i32 786447, i32 0, metadata !"", i32 0, i32 0, i64 64, i64 64, i64 0, i32 64, metadata !31} ; [ DW_TAG_pointer_type ]
!31 = metadata !{i32 786434, metadata !26, metadata !"stream<int>", metadata !27, i32 79, i64 32, i64 32, i32 0, i32 0, null, metadata !32, i32 0, null, metadata !80} ; [ DW_TAG_class_type ]
!32 = metadata !{metadata !33, metadata !34, metadata !37, metadata !43, metadata !48, metadata !52, metadata !56, metadata !61, metadata !66, metadata !67, metadata !68, metadata !69, metadata !72, metadata !73, metadata !76}
!33 = metadata !{i32 786445, metadata !31, metadata !"V", metadata !27, i32 163, i64 32, i64 32, i64 0, i32 0, metadata !10} ; [ DW_TAG_member ]
!34 = metadata !{i32 786478, i32 0, metadata !31, metadata !"stream", metadata !"stream", metadata !"", metadata !27, i32 83, metadata !35, i1 false, i1 false, i32 0, i32 0, null, i32 256, i1 false, null, null, i32 0, metadata !17, i32 83} ; [ DW_TAG_subprogram ]
!35 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !36, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!36 = metadata !{null, metadata !30}
!37 = metadata !{i32 786478, i32 0, metadata !31, metadata !"stream", metadata !"stream", metadata !"", metadata !27, i32 86, metadata !38, i1 false, i1 false, i32 0, i32 0, null, i32 256, i1 false, null, null, i32 0, metadata !17, i32 86} ; [ DW_TAG_subprogram ]
!38 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !39, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!39 = metadata !{null, metadata !30, metadata !40}
!40 = metadata !{i32 786447, null, metadata !"", null, i32 0, i64 64, i64 64, i64 0, i32 0, metadata !41} ; [ DW_TAG_pointer_type ]
!41 = metadata !{i32 786470, null, metadata !"", null, i32 0, i64 0, i64 0, i64 0, i32 0, metadata !42} ; [ DW_TAG_const_type ]
!42 = metadata !{i32 786468, null, metadata !"char", null, i32 0, i64 8, i64 8, i64 0, i32 0, i32 6} ; [ DW_TAG_base_type ]
!43 = metadata !{i32 786478, i32 0, metadata !31, metadata !"stream", metadata !"stream", metadata !"", metadata !27, i32 91, metadata !44, i1 false, i1 false, i32 0, i32 0, null, i32 257, i1 false, null, null, i32 0, metadata !17, i32 91} ; [ DW_TAG_subprogram ]
!44 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !45, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!45 = metadata !{null, metadata !30, metadata !46}
!46 = metadata !{i32 786448, null, null, null, i32 0, i64 0, i64 0, i64 0, i32 0, metadata !47} ; [ DW_TAG_reference_type ]
!47 = metadata !{i32 786470, null, metadata !"", null, i32 0, i64 0, i64 0, i64 0, i32 0, metadata !31} ; [ DW_TAG_const_type ]
!48 = metadata !{i32 786478, i32 0, metadata !31, metadata !"operator=", metadata !"operator=", metadata !"_ZN3hls6streamIiEaSERKS1_", metadata !27, i32 94, metadata !49, i1 false, i1 false, i32 0, i32 0, null, i32 257, i1 false, null, null, i32 0, metadata !17, i32 94} ; [ DW_TAG_subprogram ]
!49 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !50, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!50 = metadata !{metadata !51, metadata !30, metadata !46}
!51 = metadata !{i32 786448, null, null, null, i32 0, i64 0, i64 0, i64 0, i32 0, metadata !31} ; [ DW_TAG_reference_type ]
!52 = metadata !{i32 786478, i32 0, metadata !31, metadata !"operator>>", metadata !"operator>>", metadata !"_ZN3hls6streamIiErsERi", metadata !27, i32 101, metadata !53, i1 false, i1 false, i32 0, i32 0, null, i32 256, i1 false, null, null, i32 0, metadata !17, i32 101} ; [ DW_TAG_subprogram ]
!53 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !54, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!54 = metadata !{null, metadata !30, metadata !55}
!55 = metadata !{i32 786448, null, null, null, i32 0, i64 0, i64 0, i64 0, i32 0, metadata !10} ; [ DW_TAG_reference_type ]
!56 = metadata !{i32 786478, i32 0, metadata !31, metadata !"operator<<", metadata !"operator<<", metadata !"_ZN3hls6streamIiElsERKi", metadata !27, i32 105, metadata !57, i1 false, i1 false, i32 0, i32 0, null, i32 256, i1 false, null, null, i32 0, metadata !17, i32 105} ; [ DW_TAG_subprogram ]
!57 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !58, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!58 = metadata !{null, metadata !30, metadata !59}
!59 = metadata !{i32 786448, null, null, null, i32 0, i64 0, i64 0, i64 0, i32 0, metadata !60} ; [ DW_TAG_reference_type ]
!60 = metadata !{i32 786470, null, metadata !"", null, i32 0, i64 0, i64 0, i64 0, i32 0, metadata !10} ; [ DW_TAG_const_type ]
!61 = metadata !{i32 786478, i32 0, metadata !31, metadata !"empty", metadata !"empty", metadata !"_ZNK3hls6streamIiE5emptyEv", metadata !27, i32 112, metadata !62, i1 false, i1 false, i32 0, i32 0, null, i32 256, i1 false, null, null, i32 0, metadata !17, i32 112} ; [ DW_TAG_subprogram ]
!62 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !63, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!63 = metadata !{metadata !64, metadata !65}
!64 = metadata !{i32 786468, null, metadata !"bool", null, i32 0, i64 8, i64 8, i64 0, i32 0, i32 2} ; [ DW_TAG_base_type ]
!65 = metadata !{i32 786447, i32 0, metadata !"", i32 0, i32 0, i64 64, i64 64, i64 0, i32 64, metadata !47} ; [ DW_TAG_pointer_type ]
!66 = metadata !{i32 786478, i32 0, metadata !31, metadata !"full", metadata !"full", metadata !"_ZNK3hls6streamIiE4fullEv", metadata !27, i32 117, metadata !62, i1 false, i1 false, i32 0, i32 0, null, i32 256, i1 false, null, null, i32 0, metadata !17, i32 117} ; [ DW_TAG_subprogram ]
!67 = metadata !{i32 786478, i32 0, metadata !31, metadata !"read", metadata !"read", metadata !"_ZN3hls6streamIiE4readERi", metadata !27, i32 123, metadata !53, i1 false, i1 false, i32 0, i32 0, null, i32 256, i1 false, null, null, i32 0, metadata !17, i32 123} ; [ DW_TAG_subprogram ]
!68 = metadata !{i32 786478, i32 0, metadata !31, metadata !"read", metadata !"read", metadata !"_ZN3hls6streamIiE4readEv", metadata !27, i32 129, metadata !28, i1 false, i1 false, i32 0, i32 0, null, i32 256, i1 false, null, null, i32 0, metadata !17, i32 129} ; [ DW_TAG_subprogram ]
!69 = metadata !{i32 786478, i32 0, metadata !31, metadata !"read_nb", metadata !"read_nb", metadata !"_ZN3hls6streamIiE7read_nbERi", metadata !27, i32 136, metadata !70, i1 false, i1 false, i32 0, i32 0, null, i32 256, i1 false, null, null, i32 0, metadata !17, i32 136} ; [ DW_TAG_subprogram ]
!70 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !71, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!71 = metadata !{metadata !64, metadata !30, metadata !55}
!72 = metadata !{i32 786478, i32 0, metadata !31, metadata !"write", metadata !"write", metadata !"_ZN3hls6streamIiE5writeERKi", metadata !27, i32 144, metadata !57, i1 false, i1 false, i32 0, i32 0, null, i32 256, i1 false, null, null, i32 0, metadata !17, i32 144} ; [ DW_TAG_subprogram ]
!73 = metadata !{i32 786478, i32 0, metadata !31, metadata !"write_nb", metadata !"write_nb", metadata !"_ZN3hls6streamIiE8write_nbERKi", metadata !27, i32 150, metadata !74, i1 false, i1 false, i32 0, i32 0, null, i32 256, i1 false, null, null, i32 0, metadata !17, i32 150} ; [ DW_TAG_subprogram ]
!74 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !75, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!75 = metadata !{metadata !64, metadata !30, metadata !59}
!76 = metadata !{i32 786478, i32 0, metadata !31, metadata !"size", metadata !"size", metadata !"_ZN3hls6streamIiE4sizeEv", metadata !27, i32 157, metadata !77, i1 false, i1 false, i32 0, i32 0, null, i32 256, i1 false, null, null, i32 0, metadata !17, i32 157} ; [ DW_TAG_subprogram ]
!77 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !78, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!78 = metadata !{metadata !79, metadata !30}
!79 = metadata !{i32 786468, null, metadata !"unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!80 = metadata !{metadata !81}
!81 = metadata !{i32 786479, null, metadata !"__STREAM_T__", metadata !10, null, i32 0, i32 0} ; [ DW_TAG_template_type_parameter ]
!82 = metadata !{i32 176, i32 2, metadata !1, null}
!83 = metadata !{i32 786688, metadata !2, metadata !"j", metadata !5, i32 173, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!84 = metadata !{i32 786688, metadata !85, metadata !"tmp", metadata !27, i32 145, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!85 = metadata !{i32 786443, metadata !86, i32 144, i32 79, metadata !27, i32 21} ; [ DW_TAG_lexical_block ]
!86 = metadata !{i32 786478, i32 0, metadata !26, metadata !"write", metadata !"write", metadata !"_ZN3hls6streamIiE5writeERKi", metadata !27, i32 144, metadata !57, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, null, null, metadata !72, metadata !17, i32 144} ; [ DW_TAG_subprogram ]
!87 = metadata !{i32 161, i32 2, metadata !88, null}
!88 = metadata !{i32 786443, metadata !89, i32 159, i32 32, metadata !5, i32 15} ; [ DW_TAG_lexical_block ]
!89 = metadata !{i32 786443, metadata !90, i32 159, i32 3, metadata !5, i32 14} ; [ DW_TAG_lexical_block ]
!90 = metadata !{i32 786443, metadata !91, i32 158, i32 54, metadata !5, i32 13} ; [ DW_TAG_lexical_block ]
!91 = metadata !{i32 786443, metadata !3, i32 158, i32 2, metadata !5, i32 12} ; [ DW_TAG_lexical_block ]
!92 = metadata !{i32 158, i32 49, metadata !91, null}
!93 = metadata !{i32 786688, metadata !91, metadata !"j", metadata !5, i32 158, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!94 = metadata !{i32 159, i32 16, metadata !89, null}
!95 = metadata !{i32 162, i32 4, metadata !88, null}
!96 = metadata !{i32 165, i32 4, metadata !88, null}
!97 = metadata !{i32 159, i32 33, metadata !88, null}
!98 = metadata !{i32 160, i32 1, metadata !88, null}
!99 = metadata !{i32 168, i32 3, metadata !88, null}
!100 = metadata !{i32 159, i32 27, metadata !89, null}
!101 = metadata !{i32 786688, metadata !89, metadata !"k", metadata !5, i32 159, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!102 = metadata !{i32 786688, metadata !3, metadata !"tmp", metadata !5, i32 156, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!103 = metadata !{i32 167, i32 4, metadata !88, null}
!104 = metadata !{i32 164, i32 4, metadata !105, null}
!105 = metadata !{i32 786443, metadata !88, i32 162, i32 14, metadata !5, i32 16} ; [ DW_TAG_lexical_block ]
!106 = metadata !{i32 163, i32 12, metadata !105, null}
!107 = metadata !{i32 131, i32 9, metadata !24, metadata !106}
!108 = metadata !{i32 145, i32 31, metadata !85, metadata !109}
!109 = metadata !{i32 106, i32 9, metadata !110, metadata !112}
!110 = metadata !{i32 786443, metadata !111, i32 105, i32 88, metadata !27, i32 20} ; [ DW_TAG_lexical_block ]
!111 = metadata !{i32 786478, i32 0, metadata !26, metadata !"operator<<", metadata !"operator<<", metadata !"_ZN3hls6streamIiElsERKi", metadata !27, i32 105, metadata !57, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, null, null, metadata !56, metadata !17, i32 105} ; [ DW_TAG_subprogram ]
!112 = metadata !{i32 167, i32 21, metadata !88, null}
!113 = metadata !{i32 146, i32 9, metadata !85, metadata !109}
!114 = metadata !{i32 790529, metadata !115, metadata !"a_fifo.V", null, i32 149, metadata !116, i32 0, i32 0} ; [ DW_TAG_auto_variable_field ]
!115 = metadata !{i32 786688, metadata !3, metadata !"a_fifo", metadata !5, i32 149, metadata !31, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!116 = metadata !{i32 786438, metadata !26, metadata !"stream<int>", metadata !27, i32 79, i64 32, i64 32, i32 0, i32 0, null, metadata !117, i32 0, null, metadata !80} ; [ DW_TAG_class_field_type ]
!117 = metadata !{metadata !33}
!118 = metadata !{i32 149, i32 25, metadata !3, null}
!119 = metadata !{i32 153, i32 2, metadata !120, null}
!120 = metadata !{i32 786443, metadata !121, i32 151, i32 31, metadata !5, i32 11} ; [ DW_TAG_lexical_block ]
!121 = metadata !{i32 786443, metadata !3, i32 151, i32 2, metadata !5, i32 10} ; [ DW_TAG_lexical_block ]
!122 = metadata !{i32 145, i32 31, metadata !85, metadata !123}
!123 = metadata !{i32 106, i32 9, metadata !110, metadata !119}
!124 = metadata !{i32 151, i32 15, metadata !121, null}
!125 = metadata !{i32 151, i32 26, metadata !121, null}
!126 = metadata !{i32 151, i32 32, metadata !120, null}
!127 = metadata !{i32 152, i32 1, metadata !120, null}
!128 = metadata !{i32 146, i32 9, metadata !85, metadata !123}
!129 = metadata !{i32 154, i32 2, metadata !120, null}
!130 = metadata !{i32 786688, metadata !121, metadata !"j", metadata !5, i32 151, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!131 = metadata !{i32 786689, metadata !4, metadata !"c_offset_address", metadata !5, i32 83886222, metadata !11, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!132 = metadata !{i32 142, i32 8, metadata !4, null}
!133 = metadata !{i32 786689, metadata !4, metadata !"a_offset_address", metadata !5, i32 50331788, metadata !11, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!134 = metadata !{i32 140, i32 8, metadata !4, null}
!135 = metadata !{i32 144, i32 1, metadata !3, null}
!136 = metadata !{i32 786689, metadata !4, metadata !"memory_0", metadata !5, i32 16777354, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!137 = metadata !{i32 138, i32 22, metadata !4, null}
!138 = metadata !{i32 786689, metadata !4, metadata !"memory_3", metadata !5, i32 33554571, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!139 = metadata !{i32 139, i32 17, metadata !4, null}
!140 = metadata !{i32 786689, metadata !4, metadata !"B", null, i32 141, metadata !141, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!141 = metadata !{i32 786433, null, metadata !"", null, i32 0, i64 262144, i64 32, i32 0, i32 0, metadata !9, metadata !142, i32 0, i32 0} ; [ DW_TAG_array_type ]
!142 = metadata !{metadata !143, metadata !16}
!143 = metadata !{i32 786465, i64 0, i64 511}     ; [ DW_TAG_subrange_type ]
!144 = metadata !{i32 141, i32 14, metadata !4, null}
!145 = metadata !{i32 790529, metadata !146, metadata !"c_fifo.V", null, i32 150, metadata !116, i32 0, i32 0} ; [ DW_TAG_auto_variable_field ]
!146 = metadata !{i32 786688, metadata !3, metadata !"c_fifo", metadata !5, i32 150, metadata !31, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!147 = metadata !{i32 150, i32 25, metadata !3, null}
!148 = metadata !{i32 179, i32 1, metadata !3, null}
!149 = metadata !{metadata !150}
!150 = metadata !{i32 0, i32 31, metadata !151}
!151 = metadata !{metadata !152}
!152 = metadata !{metadata !"memory_0", metadata !153, metadata !"int", i32 0, i32 31}
!153 = metadata !{metadata !154}
!154 = metadata !{i32 0, i32 0, i32 1}
!155 = metadata !{metadata !156}
!156 = metadata !{i32 0, i32 31, metadata !157}
!157 = metadata !{metadata !158}
!158 = metadata !{metadata !"memory_1_0", metadata !153, metadata !"int", i32 0, i32 31}
!159 = metadata !{metadata !160}
!160 = metadata !{i32 0, i32 31, metadata !161}
!161 = metadata !{metadata !162}
!162 = metadata !{metadata !"memory_2_0", metadata !153, metadata !"int", i32 0, i32 31}
!163 = metadata !{metadata !164}
!164 = metadata !{i32 0, i32 31, metadata !165}
!165 = metadata !{metadata !166}
!166 = metadata !{metadata !"memory_1_1", metadata !153, metadata !"int", i32 0, i32 31}
!167 = metadata !{metadata !168}
!168 = metadata !{i32 0, i32 31, metadata !169}
!169 = metadata !{metadata !170}
!170 = metadata !{metadata !"memory_2_1", metadata !153, metadata !"int", i32 0, i32 31}
!171 = metadata !{metadata !172}
!172 = metadata !{i32 0, i32 31, metadata !173}
!173 = metadata !{metadata !174}
!174 = metadata !{metadata !"memory_1_2", metadata !153, metadata !"int", i32 0, i32 31}
!175 = metadata !{metadata !176}
!176 = metadata !{i32 0, i32 31, metadata !177}
!177 = metadata !{metadata !178}
!178 = metadata !{metadata !"memory_2_2", metadata !153, metadata !"int", i32 0, i32 31}
!179 = metadata !{metadata !180}
!180 = metadata !{i32 0, i32 31, metadata !181}
!181 = metadata !{metadata !182}
!182 = metadata !{metadata !"memory_1_3", metadata !153, metadata !"int", i32 0, i32 31}
!183 = metadata !{metadata !184}
!184 = metadata !{i32 0, i32 31, metadata !185}
!185 = metadata !{metadata !186}
!186 = metadata !{metadata !"memory_2_3", metadata !153, metadata !"int", i32 0, i32 31}
!187 = metadata !{metadata !188}
!188 = metadata !{i32 0, i32 31, metadata !189}
!189 = metadata !{metadata !190}
!190 = metadata !{metadata !"memory_1_4", metadata !153, metadata !"int", i32 0, i32 31}
!191 = metadata !{metadata !192}
!192 = metadata !{i32 0, i32 31, metadata !193}
!193 = metadata !{metadata !194}
!194 = metadata !{metadata !"memory_2_4", metadata !153, metadata !"int", i32 0, i32 31}
!195 = metadata !{metadata !196}
!196 = metadata !{i32 0, i32 31, metadata !197}
!197 = metadata !{metadata !198}
!198 = metadata !{metadata !"memory_1_5", metadata !153, metadata !"int", i32 0, i32 31}
!199 = metadata !{metadata !200}
!200 = metadata !{i32 0, i32 31, metadata !201}
!201 = metadata !{metadata !202}
!202 = metadata !{metadata !"memory_2_5", metadata !153, metadata !"int", i32 0, i32 31}
!203 = metadata !{metadata !204}
!204 = metadata !{i32 0, i32 31, metadata !205}
!205 = metadata !{metadata !206}
!206 = metadata !{metadata !"memory_1_6", metadata !153, metadata !"int", i32 0, i32 31}
!207 = metadata !{metadata !208}
!208 = metadata !{i32 0, i32 31, metadata !209}
!209 = metadata !{metadata !210}
!210 = metadata !{metadata !"memory_2_6", metadata !153, metadata !"int", i32 0, i32 31}
!211 = metadata !{metadata !212}
!212 = metadata !{i32 0, i32 31, metadata !213}
!213 = metadata !{metadata !214}
!214 = metadata !{metadata !"memory_1_7", metadata !153, metadata !"int", i32 0, i32 31}
!215 = metadata !{metadata !216}
!216 = metadata !{i32 0, i32 31, metadata !217}
!217 = metadata !{metadata !218}
!218 = metadata !{metadata !"memory_2_7", metadata !153, metadata !"int", i32 0, i32 31}
!219 = metadata !{metadata !220}
!220 = metadata !{i32 0, i32 31, metadata !221}
!221 = metadata !{metadata !222}
!222 = metadata !{metadata !"a_offset_address", metadata !223, metadata !"long unsigned int", i32 0, i32 31}
!223 = metadata !{metadata !224}
!224 = metadata !{i32 0, i32 0, i32 0}
!225 = metadata !{metadata !226}
!226 = metadata !{i32 0, i32 31, metadata !227}
!227 = metadata !{metadata !228}
!228 = metadata !{metadata !"b_offset_address", metadata !223, metadata !"long unsigned int", i32 0, i32 31}
!229 = metadata !{metadata !230}
!230 = metadata !{i32 0, i32 31, metadata !231}
!231 = metadata !{metadata !232}
!232 = metadata !{metadata !"c_offset_address", metadata !223, metadata !"long unsigned int", i32 0, i32 31}
!233 = metadata !{i32 786689, metadata !234, metadata !"c_offset_address", metadata !5, i32 335544361, metadata !11, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!234 = metadata !{i32 786478, i32 0, metadata !5, metadata !"matrix_mult_large", metadata !"matrix_mult_large", metadata !"_Z17matrix_mult_largePiS_S_S_S_S_S_S_S_S_S_S_S_S_S_S_S_mmm", metadata !5, i32 20, metadata !235, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, void (i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32, i32, i32)* @matrix_mult_large, null, null, metadata !17, i32 42} ; [ DW_TAG_subprogram ]
!235 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !236, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!236 = metadata !{null, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !8, metadata !11, metadata !11, metadata !11}
!237 = metadata !{i32 41, i32 10, metadata !234, null}
!238 = metadata !{i32 786689, metadata !234, metadata !"b_offset_address", metadata !5, i32 318767144, metadata !11, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!239 = metadata !{i32 40, i32 10, metadata !234, null}
!240 = metadata !{i32 786689, metadata !234, metadata !"a_offset_address", metadata !5, i32 301989927, metadata !11, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!241 = metadata !{i32 39, i32 10, metadata !234, null}
!242 = metadata !{i32 786689, metadata !234, metadata !"memory_0", metadata !5, i32 16777236, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!243 = metadata !{i32 20, i32 36, metadata !234, null}
!244 = metadata !{i32 786689, metadata !234, metadata !"memory_1_0", metadata !5, i32 33554453, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!245 = metadata !{i32 21, i32 26, metadata !234, null}
!246 = metadata !{i32 786689, metadata !234, metadata !"memory_2_0", metadata !5, i32 50331670, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!247 = metadata !{i32 22, i32 17, metadata !234, null}
!248 = metadata !{i32 786689, metadata !234, metadata !"memory_1_1", metadata !5, i32 67108887, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!249 = metadata !{i32 23, i32 26, metadata !234, null}
!250 = metadata !{i32 786689, metadata !234, metadata !"memory_2_1", metadata !5, i32 83886104, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!251 = metadata !{i32 24, i32 17, metadata !234, null}
!252 = metadata !{i32 786689, metadata !234, metadata !"memory_1_2", metadata !5, i32 100663321, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!253 = metadata !{i32 25, i32 26, metadata !234, null}
!254 = metadata !{i32 786689, metadata !234, metadata !"memory_2_2", metadata !5, i32 117440538, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!255 = metadata !{i32 26, i32 17, metadata !234, null}
!256 = metadata !{i32 786689, metadata !234, metadata !"memory_1_3", metadata !5, i32 134217755, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!257 = metadata !{i32 27, i32 26, metadata !234, null}
!258 = metadata !{i32 786689, metadata !234, metadata !"memory_2_3", metadata !5, i32 150994972, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!259 = metadata !{i32 28, i32 17, metadata !234, null}
!260 = metadata !{i32 786689, metadata !234, metadata !"memory_1_4", metadata !5, i32 167772190, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!261 = metadata !{i32 30, i32 26, metadata !234, null}
!262 = metadata !{i32 786689, metadata !234, metadata !"memory_2_4", metadata !5, i32 184549407, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!263 = metadata !{i32 31, i32 17, metadata !234, null}
!264 = metadata !{i32 786689, metadata !234, metadata !"memory_1_5", metadata !5, i32 201326624, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!265 = metadata !{i32 32, i32 26, metadata !234, null}
!266 = metadata !{i32 786689, metadata !234, metadata !"memory_2_5", metadata !5, i32 218103841, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!267 = metadata !{i32 33, i32 17, metadata !234, null}
!268 = metadata !{i32 786689, metadata !234, metadata !"memory_1_6", metadata !5, i32 234881058, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!269 = metadata !{i32 34, i32 26, metadata !234, null}
!270 = metadata !{i32 786689, metadata !234, metadata !"memory_2_6", metadata !5, i32 251658275, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!271 = metadata !{i32 35, i32 17, metadata !234, null}
!272 = metadata !{i32 786689, metadata !234, metadata !"memory_1_7", metadata !5, i32 268435492, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!273 = metadata !{i32 36, i32 26, metadata !234, null}
!274 = metadata !{i32 786689, metadata !234, metadata !"memory_2_7", metadata !5, i32 285212709, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!275 = metadata !{i32 37, i32 17, metadata !234, null}
!276 = metadata !{i32 44, i32 1, metadata !277, null}
!277 = metadata !{i32 786443, metadata !234, i32 42, i32 9, metadata !5, i32 0} ; [ DW_TAG_lexical_block ]
!278 = metadata !{i32 46, i32 1, metadata !277, null}
!279 = metadata !{i32 47, i32 1, metadata !277, null}
!280 = metadata !{i32 48, i32 1, metadata !277, null}
!281 = metadata !{i32 49, i32 1, metadata !277, null}
!282 = metadata !{i32 51, i32 1, metadata !277, null}
!283 = metadata !{i32 52, i32 1, metadata !277, null}
!284 = metadata !{i32 53, i32 1, metadata !277, null}
!285 = metadata !{i32 54, i32 1, metadata !277, null}
!286 = metadata !{i32 56, i32 1, metadata !277, null}
!287 = metadata !{i32 57, i32 1, metadata !277, null}
!288 = metadata !{i32 58, i32 1, metadata !277, null}
!289 = metadata !{i32 59, i32 1, metadata !277, null}
!290 = metadata !{i32 62, i32 1, metadata !277, null}
!291 = metadata !{i32 63, i32 1, metadata !277, null}
!292 = metadata !{i32 64, i32 1, metadata !277, null}
!293 = metadata !{i32 65, i32 1, metadata !277, null}
!294 = metadata !{i32 67, i32 1, metadata !277, null}
!295 = metadata !{i32 68, i32 1, metadata !277, null}
!296 = metadata !{i32 69, i32 1, metadata !277, null}
!297 = metadata !{i32 70, i32 1, metadata !277, null}
!298 = metadata !{i32 786688, metadata !277, metadata !"B_0", metadata !5, i32 75, metadata !141, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!299 = metadata !{i32 75, i32 12, metadata !277, null}
!300 = metadata !{i32 786688, metadata !277, metadata !"B_1", metadata !5, i32 76, metadata !141, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!301 = metadata !{i32 76, i32 12, metadata !277, null}
!302 = metadata !{i32 786688, metadata !277, metadata !"B_2", metadata !5, i32 77, metadata !141, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!303 = metadata !{i32 77, i32 12, metadata !277, null}
!304 = metadata !{i32 786688, metadata !277, metadata !"B_3", metadata !5, i32 78, metadata !141, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!305 = metadata !{i32 78, i32 12, metadata !277, null}
!306 = metadata !{i32 786688, metadata !277, metadata !"B_4", metadata !5, i32 79, metadata !141, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!307 = metadata !{i32 79, i32 12, metadata !277, null}
!308 = metadata !{i32 786688, metadata !277, metadata !"B_5", metadata !5, i32 80, metadata !141, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!309 = metadata !{i32 80, i32 12, metadata !277, null}
!310 = metadata !{i32 786688, metadata !277, metadata !"B_6", metadata !5, i32 81, metadata !141, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!311 = metadata !{i32 81, i32 12, metadata !277, null}
!312 = metadata !{i32 786688, metadata !277, metadata !"B_7", metadata !5, i32 82, metadata !141, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!313 = metadata !{i32 82, i32 12, metadata !277, null}
!314 = metadata !{i32 92, i32 2, metadata !315, null}
!315 = metadata !{i32 786443, metadata !316, i32 90, i32 33, metadata !5, i32 6} ; [ DW_TAG_lexical_block ]
!316 = metadata !{i32 786443, metadata !317, i32 90, i32 4, metadata !5, i32 5} ; [ DW_TAG_lexical_block ]
!317 = metadata !{i32 786443, metadata !318, i32 89, i32 32, metadata !5, i32 4} ; [ DW_TAG_lexical_block ]
!318 = metadata !{i32 786443, metadata !319, i32 89, i32 3, metadata !5, i32 3} ; [ DW_TAG_lexical_block ]
!319 = metadata !{i32 786443, metadata !320, i32 87, i32 87, metadata !5, i32 2} ; [ DW_TAG_lexical_block ]
!320 = metadata !{i32 786443, metadata !277, i32 87, i32 2, metadata !5, i32 1} ; [ DW_TAG_lexical_block ]
!321 = metadata !{i32 87, i32 16, metadata !320, null}
!322 = metadata !{i32 87, i32 82, metadata !320, null}
!323 = metadata !{i32 786688, metadata !320, metadata !"p", metadata !5, i32 87, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!324 = metadata !{i32 94, i32 5, metadata !315, null}
!325 = metadata !{i32 97, i32 10, metadata !315, null}
!326 = metadata !{i32 100, i32 10, metadata !315, null}
!327 = metadata !{i32 103, i32 10, metadata !315, null}
!328 = metadata !{i32 106, i32 10, metadata !315, null}
!329 = metadata !{i32 109, i32 10, metadata !315, null}
!330 = metadata !{i32 112, i32 10, metadata !315, null}
!331 = metadata !{i32 115, i32 10, metadata !315, null}
!332 = metadata !{i32 89, i32 16, metadata !318, null}
!333 = metadata !{i32 125, i32 4, metadata !334, null}
!334 = metadata !{i32 786443, metadata !335, i32 123, i32 34, metadata !5, i32 8} ; [ DW_TAG_lexical_block ]
!335 = metadata !{i32 786443, metadata !319, i32 123, i32 3, metadata !5, i32 7} ; [ DW_TAG_lexical_block ]
!336 = metadata !{i32 126, i32 4, metadata !334, null}
!337 = metadata !{i32 127, i32 4, metadata !334, null}
!338 = metadata !{i32 129, i32 4, metadata !334, null}
!339 = metadata !{i32 130, i32 4, metadata !334, null}
!340 = metadata !{i32 131, i32 4, metadata !334, null}
!341 = metadata !{i32 132, i32 4, metadata !334, null}
!342 = metadata !{i32 123, i32 16, metadata !335, null}
!343 = metadata !{i32 786688, metadata !318, metadata !"i", metadata !5, i32 89, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!344 = metadata !{i32 89, i32 27, metadata !318, null}
!345 = metadata !{i32 95, i32 6, metadata !315, null}
!346 = metadata !{i32 98, i32 6, metadata !315, null}
!347 = metadata !{i32 101, i32 6, metadata !315, null}
!348 = metadata !{i32 104, i32 6, metadata !315, null}
!349 = metadata !{i32 107, i32 6, metadata !315, null}
!350 = metadata !{i32 110, i32 6, metadata !315, null}
!351 = metadata !{i32 113, i32 6, metadata !315, null}
!352 = metadata !{i32 116, i32 6, metadata !315, null}
!353 = metadata !{i32 120, i32 4, metadata !315, null}
!354 = metadata !{i32 90, i32 28, metadata !316, null}
!355 = metadata !{i32 786688, metadata !316, metadata !"j", metadata !5, i32 90, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!356 = metadata !{i32 90, i32 17, metadata !316, null}
!357 = metadata !{i32 90, i32 34, metadata !315, null}
!358 = metadata !{i32 91, i32 1, metadata !315, null}
!359 = metadata !{i32 786688, metadata !277, metadata !"tmp", metadata !5, i32 84, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!360 = metadata !{i32 123, i32 27, metadata !335, null}
!361 = metadata !{i32 124, i32 4, metadata !334, null}
!362 = metadata !{i32 786688, metadata !335, metadata !"i", metadata !5, i32 123, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!363 = metadata !{i32 136, i32 1, metadata !277, null}
