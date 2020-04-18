fun findOdd [] = NONE
                |findOdd (x::L) = 
                if x mod 2 = 0  
                then findOdd(L)
                else SOME x;  
val l = [2,4,6,8,10];
val t = findOdd(l);