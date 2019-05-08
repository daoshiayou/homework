module ALU(A,B,sel,out,zero,nonneg,overflow);
  input         [31:0]      A;
  input         [31:0]      B;
  input         [2:0]       sel;
  output        [31:0]      out;
  output                    zero,nonneg;
  output                    overflow;
  
  assign out= (sel==3'b000||sel==3'b110) ? (A+B):sel==3'b001 ? (A-B):sel==3'b010 ? (A|B):sel==3'b011 ? ({B,16'H0000}):sel==3'b101 ? ($signed(A)<$signed(B)?1:0):32'bz;
  assign zero= ((sel==3'b100)&&(A==B))? 1:0;
  assign nonneg= (sel==3'b111)&&($signed(A)>=0)?1:0;
  assign overflow= ((sel==3'b110)&&((A[31]&&B[31]&&!out[31])||((!A[31]&&!B[31])&&out[31])))?  1:0;
  
endmodule