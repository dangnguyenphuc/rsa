byte_list = ['0'+hex(i)[2:] if len(hex(i)[2:]) == 1 else hex(i)[2:] for i in range(1,256)]

print(len(byte_list))