define i32 @main(i32 %argc, i8** %argv) {
  call void @main.string(i32 %argc, i8** %argv)
  ret i32 0
}


@.str.true = private unnamed_addr constant [6 x i8] c"true\0A\00"
@.str.false = private unnamed_addr constant [7 x i8] c"false\0A\00"
@.str.int = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@.str.double = private unnamed_addr constant [7 x i8] c"%.16E\0A\00"

declare i32 @printf(i8*, ...)

declare i32 @atoi(...)

define void @print_boolean(i1 %a) {
  %1 = alloca i1
  store i1 %a, i1* %1
  %2 = load i1, i1* %1
  %3 = icmp eq i1 %2, 0
  br i1 %3, label %false, label %true
  false:
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.false, i32 0, i32 0))
  br label %ret
  true:
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.true, i32 0, i32 0))
  br label %ret
  ret:
  ret void
}

@a = common global i32 0
@d = common global double 0.0000000000000000
@b = common global i1 0
define void @main.string(i32 %argc, i8** %argv) {
  %1 = alloca i32
  %2 = alloca i8**
  %3 = load i32, i32* @a
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.int, i32 0, i32 0), i32 %3)
  %a = alloca double
  store double 3.5000000000000000, double* %a
  %5 = add i32 0, 33333
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.int, i32 0, i32 0), i32 %5)
  %7 = fadd double 0.0, 2.5000000000000000
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.double, i32 0, i32 0), double %7)
  ret void
}

