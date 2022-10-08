f= open("Sammy.KB.txt","w+")

stepCounter = 1


boxNum = 3
color = ["Y", "W", "B"]
# white = "W"
# both = "B"
# yellow ="Y"
orSymbol = "v"
andSymbol = "^"

containArray = []
labelArray = []


# a) Every box contains one (and only) of the 3 colors.
for i in range(boxNum):
    stepMessage = str(stepCounter) + ". "
    for j in range(len(color)):
        if j == 2: 
            stepMessage += "C" + str(i+1) + color[j]
            containArray.append("C" + str(i+1) + color[j]) 
        else:
            stepMessage += "C" + str(i+1) + color[j] + " " + orSymbol + " "
            containArray.append("C" + str(i+1) + color[j]) 
    f.write(stepMessage)
    f.write("\n")
    stepCounter += 1


#b) Each box is a different color.

#f.write("\n")
for i in range(1,4):
    for j in range(len(color)):
        stepMessage = str(stepCounter) + ". "
        stepMessage += "C%d%s -> -C%d%s ^ -C%d%s\n" % (i if i <= 3 else i % 3, color[j], i+1 if i+1 <= 3 else (i+1) % 3, color[j], i+2 if i+2 <= 3 else (i+2) % 3, color[j])
        f.write(stepMessage)
        stepCounter += 1
# for i in range(len(containArray)):
#     stepMessage = str(stepCounter) + ". " + containArray[i] + " -> "
#     for j in range(boxNum): #len(color)
#         if 
#         stepMessage += "(-"




#c) For each box and each color...if the box is labelled with that color, then it does not actually contain that color.

#f.write("\n")

for j in range(len(color)):
    stepMessage = ""
    for k in range(boxNum):
        #if k == 0: 
        stepMessage = str(stepCounter) + ". "
        stepMessage += "L" + str(k+1) + color[j] + " -> "
         #else:
        stepMessage += "-" + "C" + str(k+1) + color[j] + "\n" 
        f.write(stepMessage)
        
        stepCounter += 1
    #f.write("\n")



#d) For each box and each color...if you observe a ball of that color drawn from that box, then it actually contains either that color alone, or both.

#f.write("\n")

for i in range(1,4):
    for color in ['W', 'Y']:
        stepMessage = str(stepCounter) + ". "
        stepMessage += "O%d%s -> C%d%s v C%dB\n" % (i, color, i, color, i)
        f.write(stepMessage)
        stepCounter += 1

#e) Include the 6 initial facts at the end.
facts = ["O1Y", "L1W", "O2W", "L2Y", "O3Y", "L3B"]

for i in range(len(facts)):
    stepMessage = str(stepCounter) + ". "
    stepMessage += facts[i] + "\n"
    f.write(stepMessage)
    stepCounter += 1





#print(containArray)
# for i in range(boxNum*boxNum):
#     stepMessage = str(stepCounter) + ". "
#     for j in range(len(color)):
#         for k in range(boxNum):
#             if j == 0: 
#             stepMessage += "C" + str(i+1) + color[j]
#         else:
#             stepMessage += "C" + str(i+1) + color[j] + " " + orSymbol + " "
#     f.write(stepMessage)
#     f.write("\n")
#     stepCounter += 1


f.close()