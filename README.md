# Simulação de Robô com SDL2

## Visão Geral

Este projeto implementa uma simulação de um robô navegando em um ambiente bidimensional com obstáculos. A simulação utiliza a biblioteca SDL2 para renderizar graficamente o ambiente e representar o robô e os obstáculos em tempo real. O projeto é composto por vários arquivos de cabeçalho e um programa principal (`main.cpp`).

## Estrutura do Projeto

### Arquivos

1. **`Sensor.hpp`**:
   - Define a classe `Sensor`, que representa os sensores instalados no robô. 
   - Cada sensor tem um alcance e uma orientação (ângulo).

2. **`Robot.hpp`**:
   - Define a classe `Robot`, que modela o robô.
   - O robô possui uma posição inicial e pode conter múltiplos sensores.
   - Inclui métodos para adicionar sensores e manipular o movimento do robô.

3. **`Obstacle.hpp`**:
   - Define a classe `Obstacle`, representando obstáculos estáticos no ambiente.
   - Cada obstáculo tem uma posição fixa.

4. **`Environment.hpp`**:
   - Define a classe `Environment`, que organiza os obstáculos e interage com o robô.
   - Contém métodos para simular o comportamento do ambiente e verificar colisões.

5. **`main.cpp`**:
   - Implementa a lógica principal da simulação, incluindo:
     - Inicialização do robô, ambiente e obstáculos.
     - Representação gráfica do ambiente utilizando SDL2.
     - Atualizações contínuas na posição do robô e renderização do estado.

## Lógica da Simulação

1. **Inicialização**:
   - O robô é criado na posição `(0, 0)` com uma orientação inicial de `90°`.
   - Quatro sensores são adicionados ao robô, cobrindo ângulos de 0°, 90°, 180° e 270°.
   - Seis obstáculos são gerados aleatoriamente no ambiente com posições e tamanhos definidos.

2. **Ambiente**:
   - Representado como uma grade 10x10.
   - Obstáculos são distribuídos na grade, ocupando posições específicas marcadas com 'O'.
   - O robô é representado como 'R' na visualização textual.

3. **Renderização**:
   - O SDL2 é usado para desenhar o robô e os obstáculos em um canvas de 640x640 pixels.
   - Cada célula da grade tem tamanho proporcional para uma exibição clara.

4. **Simulação**:
   - O ambiente é atualizado em cada iteração do loop principal.
   - A posição do robô é alterada, e suas interações com obstáculos são verificadas.
   - Se o robô alcança uma área específica (destino), a simulação termina.

5. **Saída**:
   - O estado do ambiente é exibido tanto no console (visualização textual) quanto na janela SDL2 (visualização gráfica).
   - Mensagens são exibidas no console indicando eventos como a posição do robô e o sucesso da simulação.

## Como Compilar e Executar

1. **Pré-requisitos**:
   - [SDL2](https://www.libsdl.org/) instalado no sistema.
   - Compilador C++ compatível com C++11 ou superior.

2. **Compilação**:
   ```bash
   g++ -o simulacao main.cpp -lSDL2 -std=c++11
   ```

3. **Execução**:
   ```bash
   ./simulacao
   ```

## Funcionalidades

- **Robô com Sensores**:
  - Os sensores detectam o ambiente ao redor do robô, permitindo navegação inteligente.

- **Obstáculos Dinâmicos**:
  - Posições dos obstáculos são geradas aleatoriamente em cada execução, garantindo simulações variadas.

- **Renderização em Tempo Real**:
  - Representação visual do ambiente atualizada a cada iteração, criando uma experiência interativa.

## Licença
Este projeto é livre para uso e modificação. Sinta-se à vontade para contribuir e melhorar a simulação.
