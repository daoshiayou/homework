module rf(clk,overflow,rd1,rd2,WrEN,wd,Wbus,ra,rb);
  input                  clk,overflow;
  input        [4:0]     rd1;
  input        [4:0]     rd2;
  input        [4:0]     wd;
  input                  WrEN;
  input        [31:0]    Wbus;
  output       [31:0]    ra;
  output       [31:0]    rb;
  
  reg          [31:0]    rf[31:0];
  
  initial
     begin
        $readmemh("0.txt",rf);
     end
    
  always@(posedge clk)
    if((!overflow)&&WrEN&&wd!=0)
      rf[wd]<=Wbus;

  assign ra=rf[rd1];
  assign rb=rf[rd2];
  
endmodule