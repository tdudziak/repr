; ModuleID = 'debug.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @test(i32 %arg) #0 {
bb:
  %tmp = alloca i32, align 4
  %y = alloca i32, align 4
  store i32 %arg, i32* %tmp, align 4
  call void @llvm.dbg.declare(metadata i32* %tmp, metadata !12, metadata !13), !dbg !14
  call void @llvm.dbg.declare(metadata i32* %y, metadata !15, metadata !13), !dbg !16
  store i32 0, i32* %y, align 4, !dbg !16
  %tmp1 = load i32* %tmp, align 4, !dbg !17
  %tmp2 = icmp sgt i32 %tmp1, 0, !dbg !17
  br i1 %tmp2, label %bb3, label %bb5, !dbg !19

bb3:                                              ; preds = %bb
  %tmp4 = load i32* %tmp, align 4, !dbg !20
  store i32 %tmp4, i32* %y, align 4, !dbg !21
  br label %bb8, !dbg !21

bb5:                                              ; preds = %bb
  %tmp6 = load i32* %tmp, align 4, !dbg !22
  %tmp7 = sub nsw i32 0, %tmp6, !dbg !23
  store i32 %tmp7, i32* %y, align 4, !dbg !24
  br label %bb8

bb8:                                              ; preds = %bb5, %bb3
  %tmp9 = load i32* %y, align 4, !dbg !25
  ret i32 %tmp9, !dbg !26
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!9, !10}
!llvm.ident = !{!11}

!0 = !{!"0x11\0012\00clang version 3.6.0 (tags/RELEASE_360/final)\000\00\000\00\001", !1, !2, !2, !3, !2, !2} ; [ DW_TAG_compile_unit ] [/home/tdudziak/src/repr/unittests/data/debug.c] [DW_LANG_C99]
!1 = !{!"debug.c", !"/home/tdudziak/src/repr/unittests/data"}
!2 = !{}
!3 = !{!4}
!4 = !{!"0x2e\00test\00test\00\001\000\001\000\000\00256\000\002", !1, !5, !6, null, i32 (i32)* @test, null, null, !2} ; [ DW_TAG_subprogram ] [line 1] [def] [scope 2] [test]
!5 = !{!"0x29", !1}                               ; [ DW_TAG_file_type ] [/home/tdudziak/src/repr/unittests/data/debug.c]
!6 = !{!"0x15\00\000\000\000\000\000\000", null, null, null, !7, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = !{!8, !8}
!8 = !{!"0x24\00int\000\0032\0032\000\000\005", null, null} ; [ DW_TAG_base_type ] [int] [line 0, size 32, align 32, offset 0, enc DW_ATE_signed]
!9 = !{i32 2, !"Dwarf Version", i32 4}
!10 = !{i32 2, !"Debug Info Version", i32 2}
!11 = !{!"clang version 3.6.0 (tags/RELEASE_360/final)"}
!12 = !{!"0x101\00arg\0016777217\000", !4, !5, !8} ; [ DW_TAG_arg_variable ] [arg] [line 1]
!13 = !{!"0x102"}                                 ; [ DW_TAG_expression ]
!14 = !MDLocation(line: 1, column: 14, scope: !4)
!15 = !{!"0x100\00y\003\000", !4, !5, !8}         ; [ DW_TAG_auto_variable ] [y] [line 3]
!16 = !MDLocation(line: 3, column: 6, scope: !4)
!17 = !MDLocation(line: 5, column: 6, scope: !18)
!18 = !{!"0xb\005\006\000", !1, !4}               ; [ DW_TAG_lexical_block ] [/home/tdudziak/src/repr/unittests/data/debug.c]
!19 = !MDLocation(line: 5, column: 6, scope: !4)
!20 = !MDLocation(line: 6, column: 7, scope: !18)
!21 = !MDLocation(line: 6, column: 3, scope: !18)
!22 = !MDLocation(line: 8, column: 8, scope: !18)
!23 = !MDLocation(line: 8, column: 7, scope: !18)
!24 = !MDLocation(line: 8, column: 3, scope: !18)
!25 = !MDLocation(line: 10, column: 9, scope: !4)
!26 = !MDLocation(line: 10, column: 2, scope: !4)
