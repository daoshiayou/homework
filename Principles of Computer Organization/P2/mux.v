module mux32_2(a,b,sel,out);
  input   [31:0]    a;
  input   [31:0]    b;
  input             sel;
  output  [31:0]    out;
  
  assign out=sel?b:a;
  
endmodule


module mux32_3(a,b,c,sel,out);
  input   [31:0]    a;
  input   [31:0]    b;
  input   [31:0]    c;
  input   [1:0]     sel;
  output  [31:0]    out;
  
  assign out= sel==2'b00 ? a:sel==2'b01 ? b:c;
  
endmodule


module mux5_3(a,b,c,sel,out);
  input   [4:0]    a;
  input   [4:0]    b;
  input   [4:0]    c;
  input   [1:0]    sel;
  output  [4:0]    out;
  
  assign out= sel==2'b00 ? a:sel==2'b01 ? b:c;
  
endmodule
