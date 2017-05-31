define i32 @main(i32 %argc, i8** %argv) {
  call void @main.string(i32 %argc, i8** %argv)
  ret i32 0
}

define void @main.string(i32 %argc, i8** %argv) {
  %1 = alloca i32
  %2 = alloca i8**
  ret void
}


@.str.true = private unnamed_addr constant [6 x i8] c"true\0A\00"
@.str.false = private unnamed_addr constant [7 x i8] c"false\0A\00"
@.str.int = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@.str.double = private unnamed_addr constant [7 x i8] c"%.16E\0A\00"

declare i32 @printf(i8*, ...)

declare i32 @atoi(...)

