def funcSquare(x:real) : real {
    return x*x;
}

def funcGreaterThan(x:real, y:real) : bool {
    var ans : bool = true; //YA
    if (y>x) {
        set ans = false;
    }
    return ans;
}

var x : real = 2.4;
//var y : real = funcSquare(2.5);
print y;
//print funcGreaterThan(x,2.3);
//print funcGreaterThan(x,funcSquare(1.555));