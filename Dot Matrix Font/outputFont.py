# Open the file with read only permit
filename = "/home/matt/Development/python/Dot Matrix Font/Font Input"
f = open(filename, "r")
# use readlines to read all lines in the file
# The variable "lines" is a list containing all lines in the file
lines = f.readlines()
# close the file after reading the lines.
f.close()


lineStart = "constexpr character "
spacer1 = " = {0x00, 0x"
hexSpacer = " ,0x00, 0x"
lineEnd = " ,0x00,0x00,0x00,0x00,0x00,0x00,0x00};"

processLimit = 6

for line in lines:
	vals = line.split()
	valstr = lineStart + vals[0] + spacer1 + vals[1] + hexSpacer + vals[2] + hexSpacer + vals[3] + hexSpacer + vals[4] + hexSpacer + vals[5] + lineEnd
	print valstr

print "done"
