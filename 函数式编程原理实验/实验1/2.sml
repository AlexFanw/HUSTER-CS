fun sum []=0
    | sum(x::L) = x+(sum L);

val a = [1,2,3,4];
val b = sum(a);

fun mult[] = 0
    | mult(x::L) = if L=[] then x else x *(mult L);

val c = [1,2,3,4]
val d = mult(c);