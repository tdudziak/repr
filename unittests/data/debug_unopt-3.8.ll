; ModuleID = 'debug.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @test(i32 %arg) #0 !dbg !4 {
bb:
  %arg.addr = alloca i32, align 4
  %y = alloca i32, align 4
  store i32 %arg, i32* %arg.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %arg.addr, metadata !11, metadata !12), !dbg !13
  call void @llvm.dbg.declare(metadata i32* %y, metadata !14, metadata !12), !dbg !15
  store i32 0, i32* %y, align 4, !dbg !15
  %tmp = load i32, i32* %arg.addr, align 4, !dbg !16
  %cmp = icmp sgt i32 %tmp, 0, !dbg !18
  br i1 %cmp, label %bb3, label %bb5, !dbg !19

bb3:                                          ; preds = %bb
  %tmp1 = load i32, i32* %arg.addr, align 4, !dbg !20
  store i32 %tmp1, i32* %y, align 4, !dbg !21
  br label %bb8, !dbg !22

bb5:                                          ; preds = %bb
  %tmp2 = load i32, i32* %arg.addr, align 4, !dbg !23
  %sub = sub nsw i32 0, %tmp2, !dbg !24
  store i32 %sub, i32* %y, align 4, !dbg !25
  br label %bb8

bb8:                                           ; preds = %bb5, %bb3
  %tmp3 = load i32, i32* %y, align 4, !dbg !26
  ret i32 %tmp3, !dbg !27
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!8, !9}
!llvm.ident = !{!10}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "debug.c", directory: "/home/tdudziak/src/repr/unittests/data")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "test", scope: !1, file: !1, line: 1, type: !5, isLocal: false, isDefinition: true, scopeLine: 2, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !7}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !{i32 2, !"Dwarf Version", i32 4}
!9 = !{i32 2, !"Debug Info Version", i32 3}
!10 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!11 = !DILocalVariable(name: "arg", arg: 1, scope: !4, file: !1, line: 1, type: !7)
!12 = !DIExpression()
!13 = !DILocation(line: 1, column: 14, scope: !4)
!14 = !DILocalVariable(name: "y", scope: !4, file: !1, line: 3, type: !7)
!15 = !DILocation(line: 3, column: 6, scope: !4)
!16 = !DILocation(line: 5, column: 6, scope: !17)
!17 = distinct !DILexicalBlock(scope: !4, file: !1, line: 5, column: 6)
!18 = !DILocation(line: 5, column: 10, scope: !17)
!19 = !DILocation(line: 5, column: 6, scope: !4)
!20 = !DILocation(line: 6, column: 7, scope: !17)
!21 = !DILocation(line: 6, column: 5, scope: !17)
!22 = !DILocation(line: 6, column: 3, scope: !17)
!23 = !DILocation(line: 8, column: 8, scope: !17)
!24 = !DILocation(line: 8, column: 7, scope: !17)
!25 = !DILocation(line: 8, column: 5, scope: !17)
!26 = !DILocation(line: 10, column: 9, scope: !4)
!27 = !DILocation(line: 10, column: 2, scope: !4)
