# lab1
更改后的代码如下
```
(*以下是更改后正确的代码*)
3+4;
3.0+2.0;(*类型不一样*)
it+6.0;(*类型不一样*)
val it = "hello";
it ^ "world"; (*需要用^连接*)
(*it + 5;(*类型不匹配*)*)
val a = 5;(**)
val a = 6;(**)
a+8;(**)
val twice = (fn x=> 2*x);(**)
twice a;(**)
let val x = 1 in x end;(*需要在x前面加上val*)
(*foo;无意义的语句*)
(*[1,"foo"];这里的整数类型和string类型不能放在一个lists里面*)
```

# lab2
```
fun sum []=0
    | sum(x::L) = x+(sum L);

val a = [1,2,3,4];
val b = sum(a);

fun mult[] = 0
    | mult(x::L) = if L=[] then x else x *(mult L);

val c = [1,2,3,4]
val d = mult(c);
```

# lab3
```
val a=[[1,2],[3,4]];

fun mult[] = 0
    | mult(x::L) = if L=[] then x else x *(mult L);

fun Mult[] = 0
    | Mult(x::L) = if L=[] then mult(x) else mult(x) *(Mult L);

val b = Mult(a);
```
# lab4
```
(* mult' : int list * int -> int  *)
(* REQUIRES: true *)
(* ENSURES: mult'(L, a) a与列表L中元素的乘积 *)
fun mult' ([], a) = a
    | mult' (x::L, a) = mult'(L, x*a);
fun Mult'([], a) = a
    | Mult'(r::R, a) = mult'(r, a) * Mult'(R, 1);
```
# lab5
```
fun double(0:int):int=0
    | double n = 2+ double(n-1);

fun square(0:int ) = 0
    | square(1:int) = 1
    | square n = square(n-1) + double(n) -1;

square(5);
```
# lab6
```
fun divisibleByThree(0: int) : bool = true
    | divisibleByThree 1 = false
    | divisibleByThree 2 = false
    | divisibleByThree n = divisibleByThree(n-3);
```
# lab7
```
fun oddP (0:int):bool = false
    | oddP 1 = true
    | oddP n = oddP(n-2);

oddP(100);
```