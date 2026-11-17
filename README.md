# 🌱 Sistema de Irrigação Automática

Projeto Integrador Extensionista II — IFTM Campus Ituiutaba

Sistema com **Arduino Uno** que irriga plantas de pequeno porte automaticamente: quando o solo fica seco, o Arduino liga uma bomba de aquário por meio de um módulo relé e mostra a umidade em tempo real em um display LCD.

## 🎯 Objetivo

Desenvolver um sistema capaz de irrigar plantas de pequeno porte, reduzindo o tempo e o esforço gastos na manutenção. A aplicação pensada é em viveiros, jardins e orquidários.

## ⚙️ Como funciona

1. **Sensor:** o sensor de umidade fica enfiado no solo. A cada 1 segundo, o Arduino o liga, faz a leitura analógica e o desliga em seguida. Isso reduz o desgaste do sensor por corrosão.
2. **Arduino:** converte a leitura para uma escala de 0 a 100% e compara com o limite de **45%**.
3. **Bomba e LCD:** se a umidade for **menor ou igual a 45%**, o relé liga a bomba de 12 V. Acima disso, a bomba desliga. O LCD mostra a umidade atual.

O sistema também pode ser ligado e desligado pelo **Monitor Serial** (9600 baud):

| Comando | Ação |
|---------|------|
| `l` / `L` | Liga o sistema |
| `d` / `D` | Desliga o sistema e a bomba |

## 🔗 Simulação no Tinkercad

Veja o circuito montado e simulado no Tinkercad: [Projeto de Irrigação](https://www.tinkercad.com/things/8vUm1nGzg5Q-projeto-de-irrigacao?sharecode=YPrd8r14oKsaqlGNIwxwXYobVvecnq3m_QtaYiVM230)

## 🧰 Materiais

| Componente | Função |
|------------|--------|
| Arduino Uno R3 | Controle do sistema |
| Módulo relé de 5 V | Recebe o comando do Arduino e liga a bomba |
| Bomba de aquário 12 V | Leva a água até a planta |
| Fonte 12 V e tubos | Alimentação da bomba e condução da água |
| Sensor de umidade do solo | Mede a umidade da terra |
| Display LCD 16x2 com módulo I2C | Mostra a leitura |

## 🔌 Ligações

| Componente | Pino do Arduino |
|------------|-----------------|
| Relé (IN) | D8 |
| Alimentação do sensor de umidade | D7 |
| Sinal do sensor de umidade | A0 |
| LCD I2C (SDA / SCL) | A4 / A5 |

O LCD usa o endereço I2C `0x27`. Se o display não acender, teste `0x3F`.

## 💻 Como usar

1. Instale a [Arduino IDE](https://www.arduino.cc/en/software).
2. Instale a biblioteca **LiquidCrystal I2C** pelo Gerenciador de Bibliotecas.
3. Monte o circuito conforme a tabela de ligações.
4. Abra `projeto_de_irriga_o1.ino`, selecione a placa **Arduino Uno** e faça o upload.
5. Abra o Monitor Serial em 9600 baud para usar os comandos `L` e `D`.

## 🔧 Calibração

Os parâmetros ficam no início do código:

```cpp
#define SOLO_SECO 200          // leitura do sensor com solo seco
#define SOLO_UMIDO 1023        // leitura do sensor com solo úmido
#define LIMITE_UMIDADE 45      // % abaixo da qual a bomba liga
#define INTERVALO_LEITURA 1000 // tempo entre leituras (ms)
```

Cada sensor responde de um jeito. Para calibrar, leia o valor bruto com o sensor no ar ou em solo seco e depois em água, e ajuste `SOLO_SECO` e `SOLO_UMIDO`.

## ✅ Resultados

O sistema irriga plantas de pequeno porte automaticamente quando a umidade chega a 45% ou menos e mostra a leitura no display.

## 👤 Autor

**Luis Fernando dos Santos Faria**
Ciência da Computação — IFTM Campus Ituiutaba
Orientador: Prof. Rodrigo Grassi Martins
