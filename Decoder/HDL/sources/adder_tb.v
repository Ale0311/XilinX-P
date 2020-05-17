module adder_tb(adder adder_if)
reg [6:0] a;
reg [6:0] b;
wire [6:0] c;

adder inst1 (.a(adder_if.a), .b(adder_if.b), .c(adder_if.c));

endmodule
