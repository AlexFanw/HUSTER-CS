fun double(x) = 2*x;
fun square(x) = x*x;
fun frac(0,x) = x
    |frac(y,x) = frac(y-1,x*y);
val double = (fn x=>double(x));
val square = (fn x=>square(x));
val frac = (fn x=>frac(x,1));
(*
    fun maplist'
    mapList 是常规的 map 函数,即将一个函数应用在一个 list 中的每一个元素并将结果作为新的 list
    返回, 目标函数和目标list都作为参数传入 mapList.
    mapList' 是柯里化的 mapList ，接收一个函数 f 并返回一个新的函数，可作用于某一个 list.
*)
fun maplist'(func) = 
    let 
        fun f[] = []
        |f(x::L) = func x::f(L)
    in f
    end
val l = [1,2,3,4,5,6,7,8,9];
val d = maplist'(double)l;
val s = maplist'(square)l;
val f = maplist'(frac)l;