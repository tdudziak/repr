; ModuleID = 'debug_unopt-3.5.ll'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @test(i32 %arg) #0 {
bb:
  call void @llvm.dbg.value(metadata !{i32 %arg}, i64 0, metadata !12), !dbg !13
  call void @llvm.dbg.value(metadata !14, i64 0, metadata !15), !dbg !16
  %tmp2 = icmp sgt i32 %arg, 0, !dbg !17
  br i1 %tmp2, label %bb3, label %bb5, !dbg !17

bb3:                                              ; preds = %bb
  call void @llvm.dbg.value(metadata !{i32 %arg}, i64 0, metadata !15), !dbg !16
  br label %bb8, !dbg !19

bb5:                                              ; preds = %bb
  %tmp7 = sub nsw i32 0, %arg, !dbg !20
  call void @llvm.dbg.value(metadata !{i32 %tmp7}, i64 0, metadata !15), !dbg !16
  br label %bb8

bb8:                                              ; preds = %bb5, %bb3
  %y.0 = phi i32 [ %arg, %bb3 ], [ %tmp7, %bb5 ]
  ret i32 %y.0, !dbg !21
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata) #1

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata) #1

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!9, !10}
!llvm.ident = !{!11}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 (tags/RELEASE_350/final)", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 1} ; [ DW_TAG_compile_unit ] [/home/tdudziak/src/repr/unittests/data/debug.c] [DW_LANG_C99]
!1 = metadata !{metadata !"debug.c", metadata !"/home/tdudziak/src/repr/unittests/data"}
!2 = metadata !{}
!3 = metadata !{metadata !4}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"test", metadata !"test", metadata !"", i32 1, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, i32 (i32)* @test, null, null, metadata !2, i32 2} ; [ DW_TAG_subprogram ] [line 1] [def] [scope 2] [test]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/home/tdudziak/src/repr/unittests/data/debug.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{metadata !8, metadata !8}
!8 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 32, align 32, offset 0, enc DW_ATE_signed]
!9 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!10 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!11 = metadata !{metadata !"clang version 3.5.0 (tags/RELEASE_350/final)"}
!12 = metadata !{i32 786689, metadata !4, metadata !"arg", metadata !5, i32 16777217, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [arg] [line 1]
!13 = metadata !{i32 1, i32 14, metadata !4, null}
!14 = metadata !{i32 0}
!15 = metadata !{i32 786688, metadata !4, metadata !"y", metadata !5, i32 3, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [y] [line 3]
!16 = metadata !{i32 3, i32 6, metadata !4, null}
!17 = metadata !{i32 5, i32 6, metadata !18, null}
!18 = metadata !{i32 786443, metadata !1, metadata !4, i32 5, i32 6, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/tdudziak/src/repr/unittests/data/debug.c]
!19 = metadata !{i32 6, i32 3, metadata !18, null}
!20 = metadata !{i32 8, i32 3, metadata !18, null} ; [ DW_TAG_imported_declaration ]
!21 = metadata !{i32 10, i32 2, metadata !4, null}
