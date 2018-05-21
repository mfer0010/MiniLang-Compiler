def funcPow( x : real, n: int) : real {
    var y : real = 1.0; //Declare y and set it to 1.0
    if (n > 0) {
       while (n>0) {
            set y = y * x; //Assignment y = y * x
            set n = n - 1; //Assignment n = -1
        }
    }
    else {
        while (n<0) {
            /*Assignment
            for y and n: */
            set y = y / x;
            set n = n+1;
        }
    }
    return y;
}

var x : real = 2.4;
var x : bool = false;
var z : string = "The answer is: ";
var y : real = -funcPow(x,2);
print z;
print y;