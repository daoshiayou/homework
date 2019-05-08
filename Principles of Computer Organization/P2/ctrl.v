module ctrl(instr,rs,rt,rd,imm,RegDst,ALUSel,BSel,RegWr,ExtOp,MemWr,RegWSel,isJ,isBeq,isJr);
  input            [31:0]     instr;
  output           [4:0]      rs;
  output           [4:0]      rt;
  output           [4:0]      rd;
  output           [25:0]     imm;
  output reg       [1:0]      RegDst,RegWSel;
  output reg       [2:0]      ALUSel;
  output reg                  BSel,RegWr,ExtOp,MemWr,isJ,isJr,isBeq;
  
  always@(instr)
  begin
    if(instr[31:26]==6'b000000)
      begin
        case(instr[5:0])
         6'b100001: begin RegDst=2'b01; RegWSel=2'b00;  ALUSel=3'b000;  BSel=0;  RegWr=1;  MemWr=0;  isJ=0;  isJr=0;  isBeq=0; end //ADDU
         6'b100011: begin RegDst=2'b01; RegWSel=2'b00;  ALUSel=3'b001;  BSel=0;  RegWr=1;  MemWr=0;  isJ=0;  isJr=0;  isBeq=0; end //SUBU
         6'b101010: begin RegDst=2'b01; RegWSel=2'b00;  ALUSel=3'b101;  BSel=0;  RegWr=1;  MemWr=0;  isJ=0;  isJr=0;  isBeq=0; end //SLT
         6'b001000: begin RegDst=2'b01; RegWSel=2'b00;  RegWr=0;  MemWr=0;  isJ=0;  isJr=1;  isBeq=0; end //JR
        endcase
      end
    else
      begin
        case(instr[31:26])
          6'b001000: begin RegDst=2'b00; RegWSel=2'b00;  ALUSel=3'b110;  BSel=1;  ExtOp=1;  RegWr=1;  MemWr=0;  isJ=0;  isJr=0;  isBeq=0; end //ADDI
          6'b001001: begin RegDst=2'b00; RegWSel=2'b00;  ALUSel=3'b000;  BSel=1;  ExtOp=0;  RegWr=1;  MemWr=0;  isJ=0;  isJr=0;  isBeq=0; end //ADDIU
          6'b001101: begin RegDst=2'b00; RegWSel=2'b00;  ALUSel=3'b010;  BSel=1;  ExtOp=0;  RegWr=1;  MemWr=0;  isJ=0;  isJr=0;  isBeq=0; end //ORI
          6'b100011: begin RegDst=2'b00; RegWSel=2'b01;  ALUSel=3'b000;  BSel=1;  ExtOp=1;  RegWr=1;  MemWr=0;  isJ=0;  isJr=0;  isBeq=0; end //LW
          6'b101011: begin RegDst=2'b00; ALUSel=3'b000;  BSel=1;  ExtOp=1;  RegWr=0;  MemWr=1;  isJ=0;  isJr=0;  isBeq=0; end //SW
          6'b000100: begin RegDst=2'b00; ALUSel=3'b100;  BSel=0;  RegWr=0;  MemWr=0;  isJ=0;  isJr=0;  isBeq=1; end //BEQ
          6'b001111: begin RegDst=2'b00; RegWSel=2'b00;  ALUSel=3'b011;  BSel=1;  ExtOp=0;  RegWr=1;  MemWr=0;  isJ=0;  isJr=0;  isBeq=0; end //LUI
          6'b000010: begin RegWr=0;  MemWr=0;  isJ=1;  isJr=0;  isBeq=0; end //J
          6'b000011: begin RegDst=2'b10; RegWSel=2'b10;  RegWr=1;  MemWr=0;  isJ=1;  isJr=0;  isBeq=0; end //JAL
          6'b000001: begin RegDst=2'b00; ALUSel=3'b111;  BSel=0;  RegWr=0;  MemWr=0;  isJ=0;  isJr=0;  isBeq=1; end //BGEZ
        endcase
      end
  end
  
  assign rs=instr[25:21];
  assign rt=instr[20:16];
  assign rd=instr[15:11];
  assign imm=instr[25:0];
  
endmodule