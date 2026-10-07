#include <stdio.h>
#include <stdint.h>

//entrada
typedef struct PureInstruction{
    char Command;
    int Reg1_Imm;
    int Destiny;
    int Reg2_Imm;
    unsigned char FlagTipo: 1; 
} PureInstruction;

typedef union PCInstruction{

    unsigned int m;
    
    //tipo 0
    struct{
        unsigned int opcode : 8;
        unsigned int Reg1 : 5;
        unsigned int Reg2 : 5;
        unsigned int destino : 5;
        unsigned int unused : 9;

    }TipoR;

    //tipo 1
    struct{
        unsigned int opcode : 8;
        unsigned int Reg1 : 5;
        unsigned int destino : 5;
        int imediato : 14;
        
    }TipoI;
    
    

}PCInstruction;


PCInstruction codificar(PureInstruction* dados){

    PCInstruction info;
    info.m = 0;

    if(dados->FlagTipo == 0){

        info.TipoR.opcode = (unsigned)dados->Command;
        info.TipoR.Reg1 = dados->Reg1_Imm;
        info.TipoR.Reg2 = dados->Reg2_Imm;
        info.TipoR.destino = dados->Destiny;
        info.TipoR.unused = 0;
    }
    else{

        info.TipoI.opcode = (unsigned)dados->Command;
        info.TipoI.Reg1 = dados->Reg1_Imm;
        info.TipoI.destino = dados->Destiny;
        info.TipoI.imediato = dados->Reg2_Imm;
        
    }

    return info;
}
void PrintInstruction(PCInstruction *Inst) 

{ printf("0x%08X\n", Inst->m); }


int main(){

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        PureInstruction dados;
        int tipo;

        scanf("%d %c %d %d %d", &tipo, &dados.Command, &dados.Reg1_Imm, &dados.Reg2_Imm, &dados.Destiny);
        dados.FlagTipo = tipo;

        PCInstruction j = codificar(&dados);
        PrintInstruction(&j);

    }
    

}