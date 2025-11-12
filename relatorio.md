# Relatório Técnico — Sensor de Cor GY-33 (TCS34725)

**Dupla:** Ana Beatriz Barbosa Yoshida (RA: 245609 / @beatrizbarbosay), Julio Nunes Avelar (RA: 241163 / @JN513)

**Turma:** EA701 — 2025S2

**Data:** 11 de Novembro de 2025

**Repositório:** [github.com/JN513/sensor_tcs34725_yoshida_avelar](https://github.com/JN513/sensor_tcs34725_yoshida_avelar)

---

## 1. Escopo e Objetivos

O presente experimento teve como objetivo desenvolver um **sistema embarcado capaz de detectar e identificar cores** utilizando o **sensor óptico GY-33 (TCS34725)** acoplado à placa **BitDogLab**.
O projeto foi implementado em **C/C++**, utilizando o **Pico SDK** e explorando os recursos de comunicação **I2C** e **PWM por hardware** do microcontrolador **RP2040**.

Os principais objetivos técnicos foram:

* Implementar comunicação I2C com o sensor TCS34725;
* Calibrar e ler os canais de cor (**R**, **G**, **B** e **C** — clear);
* Converter os valores normalizados para o formato RGB (0–255) e HSV;
* Controlar o LED RGB da BitDogLab via PWM;
* Classificar a cor dominante de acordo com faixas de matiz (Hue);
* Reproduzir a cor detectada no LED RGB, garantindo coerência visual.

O sistema foi considerado funcional quando a cor reproduzida pelo LED correspondia visualmente à cor observada no objeto e a classificação textual coincidiu com o esperado.

---

## 2. Metodologia e Implementação

### 2.1 Arquitetura do Sistema

O sistema é composto por dois módulos principais:

1. **Sensor de cor (GY-33 / TCS34725)** — realiza a leitura das intensidades de luz refletida nos canais vermelho, verde, azul e claro, comunicando-se com o microcontrolador via I2C.
2. **LED RGB da BitDogLab** — reproduz a cor detectada por meio de três canais PWM independentes (R, G e B).

**Diagrama de blocos:**

```
+------------------+       +----------------+       +-----------------+
|    TCS34725      | <---> |   BitDogLab    | --->  | LED RGB PWM     |
|  Sensor de cor   |  I2C  |  RP2040 MCU    |  RGB  | Saídas R,G,B    |
+------------------+       +----------------+       +-----------------+
```

---

### 2.2 Ligações Elétricas

| Pino Sensor | GPIO (BitDogLab) | Função      | Observação         |
| ----------- | ---------------- | ----------- | ------------------ |
| VCC         | 3.3V             | Alimentação | Compatível 3.3V–5V |
| GND         | GND              | Terra comum | —                  |
| SDA         | GPIO0            | I2C0 SDA    | Dados              |
| SCL         | GPIO1            | I2C0 SCL    | Clock              |

O LED RGB integrado à BitDogLab utiliza os pinos:

```
R = GPIO13   G = GPIO11   B = GPIO12
```

Foram feitos ajustes no brilho para evitar mistura excessiva de branco.

---

### 2.3 Desenvolvimento de Software

O firmware foi desenvolvido em **C** utilizando o **Pico SDK (v2.2.0)**, com as seguintes bibliotecas:

* `hardware_i2c.h` — comunicação I2C com o sensor;
* `hardware_pwm.h` — controle de brilho do LED RGB;
* `pico/stdlib.h` e `stdio.h` — temporização e depuração via terminal serial.

**Fluxo lógico do programa:**

1. Inicialização dos periféricos (UART, I2C e PWM);
2. Leitura dos valores brutos dos canais R, G, B e C;
3. Normalização dos valores com base no canal “clear”;
4. Conversão de RGB para HSV;
5. Classificação da cor dominante com base no matiz (Hue);
6. Atualização do LED RGB com os valores de PWM correspondentes;
7. Impressão da cor detectada no terminal serial.

---

### 2.4 Conversão RGB-->HSV e Classificação de Cores

Foi implementado um algoritmo de conversão RGB-->HSV para análise perceptiva das cores.
A classificação é feita com base no valor do **matiz (Hue)**, conforme faixas abaixo:

| Faixa de Hue (°) | Cor Dominante |
| ---------------: | ------------- |
|     0–15 ou >345 | Vermelho      |
|            15–45 | Laranja       |
|            45–70 | Amarelo       |
|           70–160 | Verde         |
|          160–200 | Ciano         |
|          200–260 | Azul          |
|          260–320 | Roxo          |
|          320–345 | Magenta       |

A expansão das faixas foi feita empiricamente, de modo a melhorar a diferenciação entre tons intermediários (como laranja e amarelo).

---

### 2.5 Controle PWM do LED RGB

Cada canal do LED foi configurado com frequência de **1 kHz** e resolução de **16 bits**.
A intensidade de cada cor é proporcional ao valor normalizado (0–255), invertendo o duty cycle devido à natureza de ânodo comum.

Foi observada a necessidade de calibração manual para equilibrar os canais, compensando a maior luminosidade do verde.

---

## 3. Resultados e Análise

Os testes foram realizados sob iluminação branca ambiente. O sistema foi capaz de identificar e reproduzir cores básicas com boa correspondência entre leitura e exibição.

| Cor Observada  | Hue (°) | Cor Detectada | RGB Reproduzido |
| -------------- | ------- | ------------- | --------------- |
| Tampa vermelha | ~5      | Vermelho      | (255, 0, 0)     |
| Tampa verde    | ~130    | Verde         | (0, 255, 0)     |
| Tampa azul     | ~230    | Azul          | (0, 0, 255)     |
| Papel amarelo  | ~55     | Amarelo       | (255, 255, 0)   |
| Objeto branco  | —       | Branco/Cinza  | (255, 255, 255) |

**Observações:**

* Em tons claros, o LED tende ao branco ou cinza.
* A detecção do preto exigiu ajuste de limiar no valor do canal “clear”.

**Registro experimental:**

* **Montagem:** ![Montagem](/imgs/montagem.png)
* **Saída no terminal:** ![Saída](/imgs/saida.png)

---

## 4. Dificuldades e Soluções

| Desafio                                 | Solução Implementada                                                    |
| --------------------------------------- | ----------------------------------------------------------------------- |
| Brilho excessivo no LED RGB             | Calibração de brilho para evitar saturação branca.    |
| Limites imprecisos entre cores próximas | Refinamento manual das faixas de matiz (Hue) e inclusão de subdivisões. |
| Influência da iluminação ambiente       | Padronização do ambiente com luz branca direta e constante.             |
| Sensibilidade desigual dos canais RGB   | Ajuste empírico de ganho, com atenuação no canal verde.                 |

---

## 5. Conclusões e Trabalhos Futuros

O projeto alcançou os objetivos propostos, demonstrando o funcionamento adequado do sensor TCS34725 na detecção de cores.
A integração entre **leitura I2C**, **conversão HSV** e **controle PWM** resultou em um sistema eficiente, didático e de boa responsividade.

**Trabalhos futuros sugeridos:**

* Implementar calibração automática baseada em referência branca;
* Adicionar compensação de luminosidade ambiente (auto gain);
* Exibir a cor detectada em um display OLED;
* Expandir a lógica para reconhecimento de padrões multicoloridos;

---

## 6. Referências

1. ams AG. *TCS34725 Color Light-to-Digital Converter with IR Filter — Datasheet.*
   Disponível em: [https://cdn-shop.adafruit.com/datasheets/TCS34725.pdf](https://cdn-shop.adafruit.com/datasheets/TCS34725.pdf)
2. Raspberry Pi Foundation. *Pico SDK — C/C++ Development Guide.*
   Disponível em: [https://www.raspberrypi.com/documentation/microcontrollers/](https://www.raspberrypi.com/documentation/microcontrollers/)
3. BitDogLab. *Documentação de Hardware — Mapeamento de GPIOs e periféricos.*
4. Adafruit Industries. *TCS34725 Color Sensor Guide.*
   [https://learn.adafruit.com/adafruit-color-sensors](https://learn.adafruit.com/adafruit-color-sensors)
5. Repositório do projeto:
   [https://github.com/JN513/sensor_tcs34725_yoshida_avelar](https://github.com/JN513/sensor_tcs34725_yoshida_avelar)
