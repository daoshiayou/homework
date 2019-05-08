module mips(clk, rst);
  input       clk;    //clock
  input       rst;    //reset
  //ctrl(clk,instr,rs,rt,rd,imm,RegDst,ALUSel,BSel,RegWr,ExtOp,MemWr,RegWSel,isJ,isBeq,isJr)
  //im_4k(addr,dout)
  //EXT(clk,imm,sel,Ext_imm)
  //dm(clk,addr,din,we,dout)
  //npc(clk,PC,j,beq,zero,jr,RA,IMM,NPC,PC_4)
  //mux32_2(a,b,sel,out) mux32_3(a,b,c,sel,out) mux5_3(a,b,c,sel,out)
  //ALU(clk,A,B,sel,out,zero,overflow)
  //pc(NPC,clk,Reset,PC)
  //rf(clk,rd1,rd2,WrEN,wd,Wbus,ra,rb)
  
    
  wire    [31:0]   instr,ALU_data,dm_data,Wbus,ra,rb,Ext_imm,ALU_b;//rd1,rd2,sign_ext,zero_ext,GPRw_data,opcode,pcout,Aluresult,DMreg_data,alub,sign,npc,pcp4;
  wire    [31:2]   NPC,PC,PC_4;
  wire    [25:0]   IMM;
  wire    [4:0]    rs,rt,rd,wd;//GPRw_addr;
  wire    [2:0]    ALUSel;//bes;
  wire    [1:0]    RegDst,RegWSel;//WDSel,GPRSel,BSel;
  wire             BSel,RegWr,ExtOp,MemWr,isJ,isBeq,isJr,overflow,nonneg;//GPRWr,Branch,DMWr,Jump,Jal,Jr,zero,PCWr,IRWr,sb,sh,sw,lb,lh;
  parameter dra=5'H1f;
  
  im_4k im_4k(PC,instr);
  
  ctrl ctrl(instr,rs,rt,rd,IMM,RegDst,ALUSel,BSel,RegWr,ExtOp,MemWr,RegWSel,isJ,isBeq,isJr);
  
  mux5_3 mux5_3(rt,rd,dra,RegDst,wd);
  
  mux32_3 mux32_3(ALU_data,dm_data,{PC_4,2'b00},RegWSel,Wbus);
  
  rf rf(clk,overflow,rs,rt,RegWr,wd,Wbus,ra,rb);
  
  EXT EXT(IMM[15:0],ExtOp,Ext_imm);
  
  mux32_2 mux32_2(rb,Ext_imm,BSel,ALU_b);
  
  ALU ALU(ra,ALU_b,ALUSel,ALU_data,zero,nonneg,overflow);
  
  dm dm(clk,ALU_data,rb,MemWr,dm_data);
  
  npc npc(PC,overflow,isJ,isBeq,zero,nonneg,isJr,ra,IMM,NPC,PC_4);
  
  pc pc(NPC,clk,rst,PC);
  
  
endmodule