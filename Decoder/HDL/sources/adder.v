module adder(a, b, c);
input [6:0] a;
input [6:0] b;
output [6:0] sum;

reg cout;

assign (cout, sum) = a + b + cin;
if(cout == 1'b1)
	assign sum = 7'b1111111;
endmodule
