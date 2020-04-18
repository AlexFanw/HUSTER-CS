fun double(x) = 2*x;
fun square(x) = x*x;
fun frac(0,x) = x
    |frac(y,x) = frac(y-1,x*y);
val double = (fn x=>double(x));
val square = (fn x=>square(x));
val frac = (fn x=>frac(x,1));
fun thenAddOne(func,x)=func x+1;
(*
    test fun theAddOne
*)
val d = thenAddOne(double,4)
val s = thenAddOne(square,4)
val f = thenAddOne(frac,4)