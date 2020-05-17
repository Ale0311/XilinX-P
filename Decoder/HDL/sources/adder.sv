program main;
int a;
int b;
int c;
import "DPI-C" function int add(int a, int b);
virtual interface adder adder_if;

initial begin
a=$random;
b=$random;
c=add(a,b);
$display("a=%0d,b=%0d,c=%0d",a,b,c);
adder_if.a <= a;
adder_if.b <= b;
adder_tb inst1(adder_if);
end
endprogram
