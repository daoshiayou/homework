;按以下规律编码：字母A变为E，a变为e，即变成其后的第4个字母，W变为A，Y变为C，Z变为D，非字母不变。如输入“China”变为“Glmre”。
;要求：提示输入一字符串（字符个数至少为8个）
;键盘输入，Enter键结束输入，并换行显示结果
DATAS SEGMENT
    inputMsg DB 'Please enter a string of length greater than 7$'
    outputMsg DB 'The converted string is:$'
    BUF DB 50H
    	DB ? 
    	DB 50H DUP(0)
    
DATAS ENDS

STACKS SEGMENT
    DW 20H DUP(0);此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;输出输入提示信息
ERROR:
    LEA DX,inputMsg
    MOV AH,09H
    INT 21H
    ;输出回车
    CALL NEWLINE
	;接收输入的字符串
	LEA DX,BUF
	MOV AH,0AH
	INT 21H
	;输出回车
	CALL NEWLINE
	;检测字符串长度
	MOV AL,[BUF+1]
	CMP AL,08H
	JB ERROR
	;字符加工
	CALL TRANSFORM
    ;输出输出提示信息
    LEA DX,outputMsg
    MOV AH,09H
    INT 21H
    ;输出回车
    CALL NEWLINE
    ;输出加工后的字符串
    LEA DX,BUF+2
    MOV AH,09H
    INT 21H
    MOV AH,4CH
    INT 21H    
    
TRANSFORM PROC
	MOV AL,[BUF+1]
	INC AL
	MOV [BUF+1],AL
	CBW
	MOV SI,AX
	DEC SI
	MOV BUF+2[SI],'$'
	MOV CX,AX
	XOR SI,SI
LOP:
	MOV AL,BUF+2[SI]
	CMP AL,'A'
	JB CONT
	CMP AL,'z'
	JG CONT
	CMP AL,'Z'
	JBE ALPH
	CMP AL,'a'
	JGE ALPH
	JMP CONT
ALPH:
	ADD AL,04H
	CMP AL,'Z'
	JBE CONT
	CMP AL,'Z'+4
	JBE TOA
	CMP AL,'z'
	JBE CONT
TOA:
	SUB AL,1AH
CONT:
	MOV BUF+2[SI],AL
	ADD SI,TYPE BUF
	LOOP LOP
	RET
TRANSFORM ENDP

NEWLINE PROC
	MOV DL,0DH
	MOV AH,02H
	INT 21H
	MOV DL,0AH
	INT 21H
	RET
NEWLINE ENDP

CODES ENDS
    END START










