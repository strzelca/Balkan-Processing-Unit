# enumerate every instruction with a unique number as defined in the ISA spec ../lib/isa.h
from enum import Enum

# hex values are the same as in ../lib/isa.h 16-bit instruction format
class ISA(Enum):
    ADD = 0x0001      # ADD A, B
    SUB = 0x0002      # SUB A, B
    MUL = 0x0003      # MUL A, B
    DIV = 0x0004      # DIV A, B

    MOV = 0x0005      # MOV A, B
    LDR = 0x0006      # LDR A

    SHF = 0x0007      # SHF A, B
    ROT = 0x0008      # ROT A, B

    AND = 0x0009      # AND A, B
    OR  = 0x000A      # OR  A, B
    XOR = 0x000B      # XOR A, B
    NOT = 0x000C      # NOT A

    CMP = 0x000F      # CMP A, B
    JMP = 0x0010      # JMP A
    JZ  = 0x0011      # JZ  A
    JNZ = 0x0012      # JNZ A
    JG  = 0x0013      # JG  A
    JL  = 0x0014      # JL  A
    JGE = 0x0015      # JGE A
    JLE = 0x0016      # JLE A
    JE  = 0x0017      # JEQ A
    JNE = 0x0018      # JNE A