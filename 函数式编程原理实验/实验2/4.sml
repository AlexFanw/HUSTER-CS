datatype tree = None
                |Node of tree*int*tree;
fun listToTree [] = None 
    |listToTree (x::L) = let 
                            val index = List.length L div 2
                            val ltree = List.take(L,index)
                            val rtree = List.drop(L,index)
                          in 
                            Node(listToTree(ltree),x,listToTree(rtree))
                          end;
(*
span = log_2 n
work = n/2
*)
fun revT(T) = case T of None => None
              |Node(ltree,x,rtree) => Node(revT(rtree),x,revT(ltree));
val l1 = [1,2,3,4,5,6,7,8,9];
val test = revT(listToTree(l1));