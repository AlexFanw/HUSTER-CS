(*
reverse:int list -> int list
requires:int list
ensures:ecaluate the reverse of the input list
*)
fun reverse[] = []
    | reverse [a] = [a]
    | reverse (a::L) = reverse L @ [a];
val  l1 = [1,2,3,4,5,6,7,8,9];
val reverse_l1 = reverse l1;
(*
reverse':int list ->int list
require:int list,init y[]
ensures:ecaluate the reverse of the input list
*)
fun reverse'([],y) = y
    | reverse'(x::L,y) = reverse'(L,x::y);
val reverse'_l2 = reverse' (l1,[]);
