(*
    exists:('a -> bool) -> 'a list -> bool
*)
fun exists(_,[]) = false
   |exists(p,x::L) = if p x = true
                     then true
                     else exists(p,L);
fun above3(x) = x>3;
fun above5(x) = x>5;
val t1 = exists(above3,[1,2]);
val t2 = exists(above5,[2,4,6]);
(*
  forall:('a->bool)->'a list ->bool
*)
fun forall(_,[]) = false
   |forall(p,[x]) = p x
   |forall(p,x::L) = p x andalso forall(p,L);
fun lessthan20(x) = x<20;
val t1 = forall(above3,[4,5,6]);
val t2 = forall(above5,[2,3,5,6]);