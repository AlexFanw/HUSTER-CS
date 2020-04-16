val a=[[1,2],[3,4]];

fun mult[] = 0
    | mult(x::L) = if L=[] then x else x *(mult L);

fun Mult[] = 0
    | Mult(x::L) = if L=[] then mult(x) else mult(x) *(Mult L);

val b = Mult(a);