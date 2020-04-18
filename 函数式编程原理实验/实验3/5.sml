(*
    subsetSumOption:int list*int->int list option
*)
fun subsetSumOption([],sum) = NONE
    | subsetSumOption([x],sum) = if x = sum
                                 then SOME[x]
                                 else NONE
    | subsetSumOption(x::L,sum) = let val addx = subsetSumOption(L,sum-x)
                                      val notaddx = subsetSumOption(L,sum)
                                  in
                                      if x=sum
                                      then SOME(x::(fn SOME (x) => x| NONE =>[])addx)
                                      else if addx = NONE
                                      then notaddx
                                      else SOME(x::(fn SOME (x) => x| NONE =>[])addx)
                                  end;
val l1 = [1,2,3,4,5,6,7,8,9]
val t1 = subsetSumOption(l1,5);