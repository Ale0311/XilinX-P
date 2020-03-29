program main;
int a;
int b;
int c;
import "DPI-C" function int add(int a, int b);

initial begin
a=$random;
b=$random;
c=add(a,b);
$display("a=%0d,b=%0d,c=%0d",a,b,c);
end
endprogram
