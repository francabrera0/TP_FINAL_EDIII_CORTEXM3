# TP_FINAL_LPC1769_CORTEXM3

## Electrónica Digital III 2022

- Ivo Gay Caramuti

- Francisco Cabrera

---

## Descripción general del proyecto

    El presente proyecto pretende modelar un sistema automático de carga de camiones cerealeros desde un silo. 

### Funcionalidades implementadas

- Pesaje de camiones

- Control de nivel de silo

- Sistema de gillotina para controlar el flujo de salida del silo

- Comunicación serial a PC

- Interfaz gráfica de visualización de variables

---

## Pin Out LPC 1769

     j2-1  --> GND
     j2-2  --> V3.3
     j2-5  --> Sensor100
     j2-6  --> Sensor75
     j2-7  --> Sensor50
     j2-8  --> Sensor25
     j2-9  --> LedVerde
     j2-10 --> LedRojo
     j2-15 --> LoadCellOut 
     j2-21 --> LedAzul
     j2-42 --> UartTx
     j2-45 --> ServoOut
     j2-51 --> ExtInt0
     j2-52 --> ExtInt1
     j2-53 --> ExtInt2
     j2-54 --> GND

![image](https://user-images.githubusercontent.com/101826494/199761125-24eeb974-a407-4741-8224-fcbaa961079f.png)


-----

## Circuitos particulares

### Celda de carga

     La celda de carga está compuesta por un puente wheastone que es alimentado con una tensión (en nuestro caso) de 5[v]. La salida del puente tiene una sensibilidad de 1[mV/V], lo que quiere decir que a fondo de escala (10[Kg]) obtendremos una salída de 5[mV]. 

    Para adaptar esta señal y poder procesarla con el ADC de la LPC1769, fue necesario un circuito de amplificación utilizando un amplificador de instrumentación AD620. La etapa de amplificación está referenciada a un voltaje máximo de 3.3[V] para poder conectarlo a la entrada analógica de la placa.
    
![image](https://user-images.githubusercontent.com/101826494/199758005-981e9a3d-98f1-411a-91dd-c34e9467dafc.png)


### Servo

    El servomotor utilizado para controlar la gillotina de apertura y cierre del silo se controla a través de una señal PWM de 5[V] de amplitud y 50[Hz] de frecuencia.

    Para controlar el grado de apertura se debe modificar el DuttyCycle de la señal, teniendo como referencia la siguiente imágen se implementó el código necesario para los ángulos necesarios. 

![image](https://user-images.githubusercontent.com/101826494/199758079-aac13648-5dcd-4b38-ba68-329ef7f1b971.png)

   La salida digital de la LPC1769 tiene un valor de tensión de 3.3[V], por lo tanto es necesario una etapa de amplificación para lograr la amplitud de 5[V]. Al contar sólo con transistores BC548 (NPN), se genera una configuración inversora y por lo tanto la señal generada en el software también es negada para lograr el PWM deseado.
    
![image](https://user-images.githubusercontent.com/101826494/199758147-59cdeb58-2fe2-4ab3-ab3d-2a6047aaf5fc.png)


### Sensores de nivel

    Los sensores de nivel del silo son de tipo infrarojos, compuestos por un led emisor y un fotoreceptor. Para variar la sensibilidad de detección de presencia se varía el valor de las resistencias que se conecta entre VCC y la señal de salida.

![image](https://user-images.githubusercontent.com/101826494/199758207-49ef3074-a699-47c0-bd84-33afd41ca574.png)


### Uart

    La señal de salida de la uart de la LPC1769, tiene un valor de amplitud de 3.3[V].

    Para la conversión de RS-232 a USB, se realiza con un conversor TTL, que requiere que la señal tenga 5[V] de amplitud para poder recibirla correctamente. Por lo tanto se realizó una etápa de amplificación con transistores BC548 (NPN). Para evitar la inversión de la señal, se conecto los transistores en una configuración Darlington (en corte- saturación).

![image](https://user-images.githubusercontent.com/101826494/199758294-25320cc6-abb4-46f2-944d-fa44fda58cd8.png)


----

## Posibles mejoras

- Control de lazo cerrado de la apertura del silo en función del peso actual y el peso final.

- Almacenar datos de la cantidad de camiones (y [Kg]) que se cargaron en un tiempo determinado.
