import serial
import time

# Configuração da porta serial.
arduino = serial.Serial('COMX', 9600)
time.sleep(2)  # Tempo para estabilizar a conexão

# Função do comando da lampada
def controlar_lampada(lampada, estado):
    #ligar as lampadas
    comando = f"{lampada}{estado}\n"
    arduino.write(comando.encode())

# Função de leitura dados dos sensores no Arduino
def ler_sensores():
    if arduino.in_waiting > 0:
        dados = arduino.readline().decode().strip()
        # imprimir os dados dos sensores
        print("Dados dos sensores:", dados)
        return dados
    return None

try:
    while True:
        dados = ler_sensores()
        
        # Processamento os dados dos sensores
        if dados:
            partes = dados.split(',')
            pir = int(partes[0].split(':')[1])
            temp = float(partes[1].split(':')[1])

            #ligar todas ás lampadas verificando a presença e temperatura alta.
            if pir == 1 and temp > 32:
                for i in range(8):
                    controlar_lampada(i, "ON") # Ligar a lampada
            else:
                for i in range(8):
                    controlar_lampada(i, "OFF") # desligar a lampada
        
        time.sleep(1)

except KeyboardInterrupt: #exeção
    print("Finalizando o programa...") # finalizar o processo
finally:
    arduino.close() # fechar a conecção