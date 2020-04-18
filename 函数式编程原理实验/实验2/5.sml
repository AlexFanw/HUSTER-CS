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
val l1 = [1,2,3,4,5,6,7,8,9];
val t1 = listToTree(l1);
fun binarySearch (None, x) = false
    | binarySearch(Node(L, v, R), x) = case Int.compare(x, v) of
                                            GREATER => binarySearch(R, x)
                                            |LESS => binarySearch(L, x)
                                            |EQUAL => true
val b1 = binarySearch(t1,6);