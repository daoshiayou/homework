module pc(NPC,clk,Reset,PC);
  input        [31:2]      NPC;
  input                    clk;
  input                    Reset;
  output reg   [31:2]      PC;

  always@(posedge clk)
  if(Reset)
    PC<=32'H0000_3000;
  else
    PC<=NPC;
    
  endmodule