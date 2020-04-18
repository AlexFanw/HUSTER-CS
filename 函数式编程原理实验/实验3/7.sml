datatype 'a tree = None|Node of 'a tree * 'a *'a tree;
(*
构造树
*)
fun listToTree [] = None 
    |listToTree (x::L) = let 
                            val index = List.length L div 2
                            val ltree = List.take(L,index)
                            val rtree = List.drop(L,index)
                          in 
                            Node(listToTree(ltree),x,listToTree(rtree))
                          end;
(*
    treeFilter:('a->bool)->'a tree->'a option tree
*)
fun treeFilter(_,None) = None
    |treeFilter(p,Node(t1,v,t2)) = if  p v = true 
                                  then 
                                  Node(treeFilter(p,t1),SOME(v),treeFilter(p,t2))
                                  else
                                  Node(treeFilter(p,t1),NONE,treeFilter(p,t2));
fun mod3(x) = (x mod 3 = 0);
val testtreefilter = treeFilter(mod3,listToTree([2,3,4,5]))(*测试正确性*)