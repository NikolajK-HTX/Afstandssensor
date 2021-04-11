import serial
import csv

# COM3 skal ændres efter hvilken port Arduino Unoen sidder i
ser = serial.Serial('COM3', 57600, timeout=1) 

print('Tryk på enter for at starte indsamlingen af data :-)')
input()
ser.write(b'Start\n')

print('Programmet er nu i gang med at indsamle data. Vent venligst.\n')
with open('outputfile.txt', 'w', newline='', encoding='utf-8') as csvfile:
    outputWriter = csv.writer(csvfile, delimiter=';')
    for i in range(0, 510):
        outputValue = str(ser.readline(), 'utf-8')[:-1]
        if (outputValue == 'Done'):
            print("Sensoren siger den er færdig med at indsamle data.")
            break
        outputValue = outputValue.split(';')
        timeValue = float(outputValue[0])/1000
        distanceValue = outputValue[1]
        
        outputWriter.writerow([timeValue, distanceValue])

print('Programmet er færdigt med at indsamle data og den indsamlede data')
print('kan findes i "outputfile.csv"')
