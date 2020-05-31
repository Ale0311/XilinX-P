program main(adder adder_if);
int a;
int b;
int c;
import "DPI-C" function int add(int a, int b);

initial begin
a=adder_if.a;
b=adder_if.b;
c=add(a,b);
adder_if.c=c;
$display("a=%0d,b=%0d,c=%0d",a,b,c);
end
endprogram
