import serial
import time

def main():

    # Abre o arquivo de texto.
    with open("dataaaa.txt", "w") as f:

        # Abre a porta COM9.
        ser = serial.Serial("COM9", 9600)

        # Inicia o laço.
        for i in range(10):

            # Lê o valor da porta.
            value = ser.read()

            # Grava o valor no arquivo de texto.
            f.write(f"{value}\n")

            # Aguarda 1 segundo.
            time.sleep(5)

    # Fecha a porta COM9.
    ser.close()

if __name__ == "__main__":
    main()
