
## Cataract

### Cataract is a software that uses Image processing to diagnose cataract.

This project uses: C++.

The software basically process an input image or multiple input images and uses a hough implementation to create a circumference that matches the pupil and then analyze and diagnose cataract from that. 

### Optimizations :

    - It is multithreaded;
    - It uses heavy compiler optimizations;
    - Custom Hough Space modelation to improve cpu usage and reduce random access memory, aka. RAM, usage;
    - Cropping the image is a way to reduce the processing itself and aslo reduces both the volatile and 
    non-volatile memory usage;

### To compile use :

    $ make

### Basic usage:

    $ ./bin/Cataract -i <PATH1>

or

    $ ./bin/Cataract -i <PATH1> <PATH2> <PATH3>

### Cataract é um software que usa processamento de imagem para diagnosticar a catarata.

Esse projeto usa: C++.

O software basicamente processa uma ou mais imagens de entrada e usa uma implementação hough para criar uma circunferência que corresponda a pupila para analisar e diagnosticar catarata a partir disso. 

### Otimizações :

    - Foi modelado com multithreading;
    - Usa otimizações pesadas do compilador;
    - Implementação de Hough personalizada para melhorar o uso da cpu e reduzir o uso da 
    memoria de acesso randômico, RAM.
    - O corte da image é um método de reduzir o processamento por si só e também reduz o uso de 
    memória volátil e não volátil.

### Para compilar use :

    $ make

### Uso básico:

    $ ./bin/Cataract -i <PATH1>

or
	
    $ ./bin/Cataract -i <PATH1> <PATH2> <PATH3>

### Processing Example / Exemplo de processamento:

![Crop()][crop]
![Grayscale()][grayscale]
![Gaussian()][gaussian]
![Binary()][binary]
![Sobel()][sobel]
![Hough()][hough]
![Final Image][final]

[crop]: docs/readme/Cataract-01.png "Crop();"
[grayscale]: docs/readme/Cataract-02.png "Grayscale();"
[gaussian]: docs/readme/Cataract-03.png "Gaussian();"
[binary]: docs/readme/Cataract-04.png "Binary();"
[sobel]: docs/readme/Cataract-05.png "Sobel();"
[hough]: docs/readme/Cataract-06.png "Hough();"
[final]: docs/readme/Cataract-07.png "Final Image."
