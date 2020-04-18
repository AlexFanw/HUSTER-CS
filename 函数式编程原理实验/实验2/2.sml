fun interleave(A,[],l) = l @ A
  |interleave([],A,l)  = l @ A
  |interleave(x1::L1,x2::L2,l) = interleave(L1,L2,l@[x1,x2]);
val  l1 = [1,2,3,4,5,6,7,8,9];
val  l2 = [0,0,0];
val interleaves = interleave(l1,l2,[]);