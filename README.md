# Projeto: **Dosador Automático para Animais de Estimação**

## **Descrição Geral**
O projeto consiste em um sistema automatizado que dosa porções de ração para animais de estimação em horários previamente configurados. Utilizando tecnologias acessíveis e componentes eletrônicos, como **Arduino Uno**, **LCD 16x2** e um **servo motor**, o sistema proporciona uma alimentação equilibrada, mesmo na ausência do dono. É uma solução prática e eficiente para donos que seguem dietas rigorosas para seus pets.

---

## **Componentes Utilizados**
### **Hardware**
1. **Arduino Uno**  
   - Controlador central do sistema.
   - Responsável por processar os horários, acionar o servo motor e atualizar o display LCD.

2. **Display LCD 16x2**  
   - Exibe informações como horário atual, número de alimentações realizadas e status do dispensador.

3. **Servo Motor**  
   - Controla o movimento do mecanismo de liberação da ração.
   - Configurado para abrir e fechar o compartimento de ração.

4. **Fonte de Alimentação**  
   - Alimenta o Arduino e os periféricos do sistema.

### **Software**
- **Biblioteca `LiquidCrystal`**  
   Utilizada para controlar o display LCD, permitindo exibir mensagens e informações em tempo real.
- **Biblioteca `Servo`**  
   Controla o posicionamento do servo motor, ajustando o mecanismo de dosagem.

---

## **Funcionamento do Sistema**
O sistema opera em um ciclo contínuo (*loop*) onde:
1. O **relógio interno** simula o tempo em segundos, minutos e horas.
2. O **usuário predefine três horários de alimentação**. Para simplificação, no código, foram configurados os tempos 15s, 25s e 35s após o início.
3. Quando o relógio coincide com um horário programado:
   - O servo motor é acionado para dispensar a ração.
   - O LCD exibe a mensagem correspondente.
4. A cada alimentação, o sistema registra o evento, garantindo que o mesmo horário não seja repetido no mesmo dia.

---

## **Estrutura do Código**
### **Setup Inicial**
- Configuração dos pinos do Arduino para o LCD e o servo motor.
- Inicialização do display LCD com mensagens de boas-vindas e status inicial.
- Configuração da posição inicial do servo motor.

### **Relógio Simulado**
- O tempo é simulado incrementando segundos a partir da função `millis()`.  
- A cada 60 segundos, os minutos são incrementados; a cada 60 minutos, as horas são incrementadas.

### **Controle das Alimentações**
- Um array `feedingTimes` armazena os horários programados e o status de alimentação do dia.
- A função `checkFeedingTimes()` verifica continuamente se o horário atual coincide com algum dos horários programados.
- Se coincidir:
  - A função `dispenseFood()` é chamada para acionar o servo motor e dispensar a ração.

### **Exibição no LCD**
- A função `displayCurrentTime()` atualiza o display com:
  - Hora atual no formato **HH:MM:SS**.
  - Quantidade de alimentações realizadas no dia.

### **Reset Diário**
- Quando o relógio atinge 24 horas, as bandeiras de alimentação são reiniciadas, permitindo que o ciclo recomece no dia seguinte.
