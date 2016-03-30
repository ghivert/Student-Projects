#ifndef _Enum_type_H
#define _Enum_type_H


#define NB_REG 32
#define NB_MAX_BB 32
/**	\brief	Type enum which take the type of the operand			
*/
	enum t_OpType {Imm,Exp,Lab,Reg,};

/**	\brief	Type enum which take the format of the instructions			
*/
	enum  t_Format {J, I, R, O, B};

/**	\brief	Type enum which take the type of the instructions			
*/
	enum t_Inst {ALU, MEM, BR, OTHER, BAD};

/**	\brief	Type enum which take the Operator of the instructions			
*/
	// !!WARNING!! :If you add new Operators, dont forget to report their caracteristics in op_profile with the same order !!
	enum t_Operator{
	b,	beqz,	bnez,	beq,	bgez,	bgezal,
	bgtz,	blez,	bltz,	bltzal,	bne,	j,
	jal,	jalr,	jr,	la,	li,	loadi,	
	sb,	sh,	lb,	lbu,	lh,	lhu,	
	lui,	lw,	lwl,	lwr,	ll,	pref,
	sw,	add,
	addu,	addi,	addiu,	and_,	andi,	mul,
	mult,	multu,	nor,	or_,	ori,	srl,
	srlv,	sub,	subu,	sll,	sllv,	slt,
	slti,	sltiu,	sltu,	xor_,	xori,	sra,
	srav,	div_,	divu,	mfhi,	mflo,	mthi,
	mtlo,	move,	neg,	negu,	nop,	break_,
	syscallu,mfc0,	mtc0,	clo,	clz,	ebase,
	eepc,	eret,	madd,	maddu,	mfc2,
	movn,	movz,	msub,	msubu,	mtc2,	
	sc,		sync_,	tccontext,teq,	teqi,	tge,
	tgei,	tgeiu,	tgeu,	tlt,	 tlti,	tltiu,
	tltu,	tne,	tnei,	waitn,	rfe,	maxop};

/**	\brief	Type enum which take the type of dependance			
*/
enum t_Dep {NONE, RAW, WAR, WAW, MEMDEP, CONTROL};

/**	\brief	Structure allowing to add caracteristics to an operator*/
	struct s_Profile {
	   t_Operator	op ;
	   std::string  nom;
	   t_Format	format ;
	   t_Inst	type ;
	   int          nb_oper;
	} ;

	static s_Profile op_profile[maxop] = {
	   {b,	        "b",            B,              BAD},
	   {beqz,       "beqz",		I,		BR},
	   {bnez,       "bnez",		I,		BR},
	   {beq,        "beq",		I,		BR},
	   {bgez,       "bgez",		I,		BR},
	   {bgezal,     "bgezal",	I,		BR},
	   {bgtz,       "bgtz",		I,		BR},
	   {blez,       "blez",		I,		BR},
	   {bltz,       "bltz",		I,		BR},
	   {bltzal,     "bltzal",	I,		BR},
	   {bne,        "bne",		I,		BR},
	   {j,  	"j",            J,		BR},
	   {jal,        "jal",		J,		BR},
	   {jalr,       "jalr",		R,		BR},
	   {jr, 	"jr",   	R,		BR},
	   {la, 	"la",   	O,		OTHER},
	   {li,	        "li",   	O,		OTHER},
	   {loadi,      "loadi",	O,		OTHER},
	   {sb,	        "sb",   	I,		MEM},
	   {sh,	        "sh",   	I,		MEM},
	   {lb,	        "lb",   	I,		MEM},
	   {lbu,        "lbu",		I,		MEM},
	   {lh,	        "lh",	        I,		MEM},
	   {lhu,        "lhu",		I,		MEM},
	   {lui,        "lui",		I,		ALU},
	   {lw,	        "lw",    	I,		MEM},
	   {lwl,        "lwl",		B,		BAD},
	   {lwr,        "lwr",		B,		BAD},
	   {ll,	        "ll",   	B,		BAD},
	   {pref,       "pref",		O,		MEM},
	   {sw,	        "sw",   	I,		MEM},
	   {add,        "add",		R,		ALU},
	   {addu,       "addu",		R,		ALU},
	   {addi,       "addi",		I,		ALU},
	   {addiu,      "addiu",	I,		ALU},
	   {and_,       "and",		R,		ALU},
	   {andi,       "andi",		I,		ALU},
	   {mul,        "mul",		B,		BAD},
	   {mult,       "mult",		R,		ALU},
	   {multu,      "multu",	R,		ALU},
	   {nor,        "nor",		R,		ALU},
	   {or_,        "or",		R,		ALU},
	   {ori,        "ori",		I,		ALU},
	   {srl,        "srl",		R,		ALU},
	   {srlv,       "srlv",		R,		ALU},
	   {sub,        "sub",		R,		ALU},
	   {subu,       "subu",		R,		ALU},
	   {sll,        "sll",		R,		ALU},
	   {sllv,       "sllv",		R,		ALU},
	   {slt,        "slt",		R,		ALU},
	   {slti,       "slti",		I,		ALU},
	   {sltiu,      "sltiu",	I,		ALU},
	   {sltu,       "sltu",		R,		ALU},
	   {xor_,       "xor",		R,		ALU},
	   {xori,       "xori",		I,		ALU},
	   {sra,        "sra",		R,		ALU},
	   {srav,       "srav",		R,		ALU},
	   {div_,       "div",		R,		ALU},
	   {divu,       "divu",		R,		ALU},
	   {mfhi,       "mhfi",		R,		OTHER},
	   {mflo,       "mflo",		R,		OTHER},
	   {mthi,       "mthi",		R,		OTHER},
	   {mtlo,       "mtlo",		R,		OTHER},
	   {move,       "move",		B,		BAD},
	   {neg,        "neg",		B,		BAD},
	   {negu,       "negu",		B,		BAD},
	   {nop,        "nop",		B,		BAD},
	   {break_,     "break",	B,		BAD},
	   {syscallu,   "syscall",	B,		BAD},
	   {mfc0,       "mfc0",		B,		BAD},
	   {mtc0,       "mtc0",		B,		BAD},
	   {clo,        "clo",		B,		BAD},
	   {clz,        "clz",		B,		BAD},
	   {ebase,      "ebase",	B,		BAD},
	   {eepc,       "eepc",		B,		BAD},
	   {eret,       "eret",		B,		BAD},
	   {madd,       "madd",		B,		BAD},
	   {maddu,      "maddu",	B,		BAD},
	   {mfc2,       "mfc2",		B,		BAD},
	   {movn,       "movn",		B,		BAD},
	   {movz,       "movz",		B,		BAD},
	   {msub,       "msub",		B,		BAD},
	   {msubu,      "msubu",	B,		BAD},
	   {mtc2,       "mtc2",		B,		BAD},
	   {sc,	        "sc",	        B,		BAD},
	   {sync_,      "sync",		B,		BAD},
	   {tccontext,  "tccontext",	B,		BAD},
	   {teq,        "teq",		B,		BAD},
	   {teqi,       "teqi",		B,		BAD},
	   {tge,        "tge",		B,		BAD},
	   {tgei,       "tgei",		B,		BAD},
	   {tgeiu,      "tgeiu",	B,		BAD},
	   {tgeu,       "tgeu",		B,		BAD},
	   {tlt,        "tlt",		B,		BAD},
	   {tlti,       "tlti",		B,		BAD},
	   {tltiu,      "tltiu",	B,		BAD},
	   {tltu,       "tltu",		B,		BAD},
	   {tne,        "tne",		B,		BAD},
	   {tnei,       "tnei",		B,		BAD},
	   {waitn,      "wait",		B,		BAD},
	   {rfe,        "rfe",		B,		BAD}
	};


/**	\brief	Type enum which take the type of the line			
*/
	enum t_Line {line_Instru,line_Lab,line_Direct};

/**	\brief	Type enum which takes the type of the register			
*/
	enum t_Src_Dst {Src,Dst,CopSrc,CopDst} ;


#define WAW_DELAY 0
#define WAR_DELAY 0
#define MEMDEP_DELAY 1
 
/** 	\brief	Gives the delay between two instructions, in case of RAW dependance , according to their type -- ALU, MEM or BR 			
*/

static int t_delay[5][5]={
   {1,1,2,-1,-1},
   {2,2,3,-1,-1},
   {1,1,2,-1,-1},
   {-1,-1,-1,-1,-1},
   {-1,-1,-1,-1,-1}
};

#endif

 
  

