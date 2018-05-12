def funcPow( x : real, n: int) : real {
    var y : real = 1.0;
    if(n > 0) {
        while (n > 0) {
            set y = y * x;
            set n = n-1;
        }
    }
    else {
        while (n<0) {
            set y = y/x;
            set n = n+1;
        }
    }
    return y;
}

var x : real = 2;
var z : int = 100;
var y : real = funcPow(x,z);
print y;