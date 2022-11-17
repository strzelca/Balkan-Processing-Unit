from isa import ISA
from sys import argv

# create and open binary destination file
def open_bin_file(filename):
    return open(filename, "wb")

# open source file
def open_src_file(filename):
    return open(filename, "r")

# create help message
def help_message():
    print("Usage: python3 main.py <source file> <destination file>")

# check if there are enough arguments
def check_args():
    if len(argv) < 3 or len(argv) > 3:
        help_message()
        exit(1)

# read source file, decode opcodes based on ISA name, find arguments divided by comma until new line, convert arguments to hexadecimal, write to binary file

def main():
    check_args()
    src_file = open_src_file(argv[1])
    bin_file = open_bin_file(argv[2])
    for line in src_file:
        opcode = line.split(" ")[0]
        args = line.split(" ")[1].split(",")
        # 2 bytes for opcode, 2 bytes for each argument, 0x04X
        bin_file.write(bytes([ISA[opcode].value]))
        for arg in args:
            print(bytes([int(arg, 16)]))
            bin_file.write(bytes([int(arg, 16)]))
    bin_file.close()
    src_file.close()
    

    
main()