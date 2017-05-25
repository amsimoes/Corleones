@.str = private unnamed_addr constant [13 x i8] c"hello world\0A\00"

declare i32 @puts(i8* nocapture) nounwind

define i32 @main() {
  %1 = getelementptr [13 x i8], [13 x i8]* @.str, i64 0, i64 0
  call i32 @puts(i8* %1)
  ret i32 0
}
