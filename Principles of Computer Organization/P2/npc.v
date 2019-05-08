module npc(PC,overflow,j,beq,zero,nonneg,jr,RA,IMM,NPC,PC_4);
  input       [31:2]      PC;
  input       [31:0]      RA;
  input                   overflow,j,jr,beq,zero,nonneg;
  input       [25:0]      IMM;
  
  
  output      [31:2]      NPC;
  output      [31:2]      PC_4;
  
  
  assign NPC= overflow ? PC : (j ? {PC_4[31:28],IMM}:(jr ? RA[31:2]:(((beq&&nonneg)||(beq&&zero)) ? (PC_4+IMM[15:0]):PC_4)));
  
  assign PC_4=PC+1;
  
endmodule