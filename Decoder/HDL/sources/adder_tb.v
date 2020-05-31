module adder_tb();
reg [6:0] a;
reg [6:0] b;
wire [6:0] c;

initial begin
adder adder_if;
adder_if.a = 7'b0101000;
adder_if.b = 7'b1000001;

adder inst1 (.a(adder_if.a), .b(adder_if.b), .c(adder_if.c));
main adder_program(adder_if);
end
endmodule
