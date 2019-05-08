module EXT(imm,sel,Ext_imm);
  input           [15:0]      imm;
  input                       sel;
  output          [31:0]      Ext_imm;
  
  assign Ext_imm= sel==0? {16'H0000,imm} : {{16{imm[15]}},imm};
        
endmodule