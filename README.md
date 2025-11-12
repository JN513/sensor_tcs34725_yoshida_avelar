# GY-33 TCS34725 — Sensores na BitDogLab

**Dupla:** Ana Beatriz Barbosa Yoshida (245609 / @beatrizbarbosay), Julio Nunes Avelar (241163 / @JN513)  
**Turma:** EA701 — 2025S2  
**Repositório:** [https://github.com/JN513/sensor_tcs34725_yoshida_avelar](https://github.com/JN513/sensor_tcs34725_yoshida_avelar)

## 1. Descrição do sensor

- **Fabricante / modelo:**  
  ams AG — Sensor TCS34725  
  Módulo: GY-33 TCS34725 (placa breakout com regulador e interface I²C)

- **Princípio de funcionamento:**  
  Sensor óptico RGB com conversor analógico-digital (ADC) de 16 bits.  
  Possui fotodiodos com filtros para vermelho, verde, azul e claro (clear), além de filtro de bloqueio de infravermelho (IR).  
  Mede a intensidade de luz refletida/incidente e envia os valores digitais via comunicação I²C.

- **Tensão / consumo típicos:**  
  - Alimentação: 3,3 V a 5 V (compatível com ambas as tensões)  
  - Corrente típica: ~330 µA @ 3 V (sem LED ativo)  
  - Interface: I²C (endereçamento padrão 0x29)

- **Faixa de medição / resolução:**  
  - Resolução: 16 bits por canal (R, G, B e Clear)  
  - Tempo de integração ajustável: 2,4 ms a 700 ms  
  - Faixa dinâmica: até aproximadamente 3.800.000:1 (dependendo do ganho e tempo de integração)

- **Datasheet (URL):**  
  [https://cdn-shop.adafruit.com/datasheets/TCS34725.pdf](https://cdn-shop.adafruit.com/datasheets/TCS34725.pdf)


## 2. Conexões de hardware
- Tabela indicando as conexões entre BitDogLab e sensor:
- Observações (resistores, alimentação externa, níveis lógicos):

| Pino Sensor | GPIO  | Função      | Observação         |
| ----------- | ----- | ----------- | ------------------ |
| GND         | GND   | Terra Comum |      ---           |
| VCC         | 3.3V  | Alimentação | Compatível 3.3V–5V |
| SDA         | GPIO0 | I2C0 SDA    | Pino de dados      |
| SDL         | GPIO1 | I2C0 SDL    | Pino de clock      |

## 3. Dependências

- Pico SDK: v2.2.0
- Micropython: a467762
- Picotool: v2.2.0
- Bibliotecas utilizadas: hardware_i2c e hardware_pwm 
- Como instalar: Disponivel em [INSTALL.md](INSTALL.md)

## 4. Como executar

Disponivel em [docs/run.md](docs/run.md)

## 5. Exemplos de uso
- `src/exemplo_basico.py` — leitura bruta  
- `src/exemplo_filtrado.py` — leitura com média móvel  
- `test/` — códigos de teste com instruções  

## 6. Resultados e validação
- Prints/plots, fotos do setup, limitações, ruídos, dicas.

## 7. Licença
- Ver arquivo `LICENSE`.

---

> **Checklist de entrega**
> - [x] README preenchido  
> - [x] Foto/diagrama em `docs/`  
> - [x] Código comentado em `src/`  
> - [x] Testes em `test/` com instruções  
> - [x] `relatorio.md` com lições aprendidas

##  8. Estrutura do Repositório

O projeto segue o padrão definido pela disciplina EA801 — Sistemas Embarcados, 
visando padronizar as entregas e facilitar o reuso dos códigos e documentação.

Todos os arquivos de código devem estar em src/.
Diagramas, fotos, gráficos e documentos vão em docs/.
Scripts ou logs de teste ficam em test/.
O relatório técnico (relatorio.md) documenta todo o processo de engenharia.

Mantenha os nomes dos arquivos em minúsculas, sem acentos ou espaços, usando _ ou -.

```text
template_sensor/
├── README.md          → Descrição completa do projeto (sensor, ligações, execução e checklist)
├── relatorio.md       → Relatório técnico da dupla (resultados, análise e conclusões)
├── LICENSE            → Licença MIT de uso e distribuição
├── .gitignore         → Regras para ignorar arquivos temporários e binários
│
├── docs/              → Documentação e mídias
│   ├── ligacao.jpg    → Diagrama ou foto da ligação na BitDogLab
│   ├── esquema.pdf    → Esquemático opcional
│   └── outros arquivos de apoio
│
├── src/               → Códigos-fonte principais
│   ├── main.py        → Código principal (MicroPython)
│   ├── main.c         → Versão alternativa (C / Pico SDK)
│   ├── exemplos/      → Códigos ilustrativos adicionais
│   └── bibliotecas/   → Drivers, módulos auxiliares
│
└── test/              → Testes e validações
    ├── test_basico.py → Teste de leitura e resposta do sensor
    ├── test_ruido.py  → Avaliação de ruído ou estabilidade
    └── logs/          → Registros experimentais, dados e gráficos

```
