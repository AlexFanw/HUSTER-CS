fun double(x) = 2*x;
fun square(x) = x*x;
fun frac(0,x) = x
    |frac(y,x) = frac(y-1,x*y);
val double = (fn x=>double(x));
val square = (fn x=>square(x));
val frac = (fn x=>frac(x,1));
(*
     fun maplist
*)
fun maplist(func,s) = 
    case s of
        [] => []
        |(x::L) => (func x)::maplist(func,L);
val l = [1,2,3,4,5,6,7,8,9];
val d = maplist(double,l);
val s = maplist(square,l);
val f = maplist(frac,l);