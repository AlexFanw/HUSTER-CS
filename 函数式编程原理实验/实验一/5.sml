fun double(0:int):int=0
    | double n = 2+ double(n-1);

fun square(0:int ) = 0
    | square(1:int) = 1
    | square n = square(n-1) + double(n) -1;

square(5);