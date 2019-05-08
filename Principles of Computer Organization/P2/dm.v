module dm(clk,addr,din,we,dout);
  input      [11:2]        addr;   //address bus
  input      [31:0]        din;    //32-bit memory output
  input                    we;     //memory write enable      
  input                    clk;    //clock
  output     [31:0]        dout;   //32-bit memory output
  
  reg        [31:0]        dm[1023:0];
  
  always@(posedge clk)
  begin
    if(we)
      dm[addr]=din;
  end
  
  assign dout=dm[addr];
  
endmodule