// Alunos: Maria Eduarda Cardoso Aciole, Rafael Ramos Pimentel Santana, Matheus Macário dos Santos 
// Período 2024.1

// DosadorAutomaticoPet.ino

// Importações de biblioteca
#include <LiquidCrystal.h> // Biblioteca para controle do display LCD
#include <Servo.h>         // Biblioteca para controle do servo motor

// Definições dos pinos para o LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

// Definições do Servo Motor
Servo servoMotor;
const int servoPin = 9; // Pino conectado ao sinal do servo motor

// Estrutura para armazenar horários de alimentação
struct FeedingTime {
  int hour;       // Hora da alimentação
  int minute;     // Minuto da alimentação
  int second;     // Segundo da alimentação
  bool fedToday;  // Indica se já foi alimentado hoje nesse horário
};

// Definição dos horários de alimentação e número de alimentações diárias
// Para testes, as alimentações ocorrem aos 15s, 25s e 35s após o início
const int numberOfMeals = 3;
FeedingTime feedingTimes[numberOfMeals] = {
  {0, 0, 15, false},
  {0, 0, 25, false},
  {0, 0, 35, false}
};

// Variáveis para simular o tempo
unsigned long previousMillis = 0;      // Marca o último tempo verificado
const unsigned long interval = 1000;   // Intervalo de 1 segundo

// Variáveis para o relógio simulado
unsigned long totalSeconds = 0;        // Total de segundos desde o início
int currentHour = 0;                   // Hora atual
int currentMinute = 0;                 // Minuto atual
int currentSecond = 0;                 // Segundo atual

// Variável para contar o número de alimentações realizadas no dia
int feedingsToday = 0;

void setup() {
  // Inicialização do LCD
  lcd.begin(16, 2);                    // Configura o LCD com 16 colunas e 2 linhas
  lcd.setCursor(0, 0);                 // Move o cursor para a coluna 0, linha 0
  lcd.print("Dosador Pet");            // Exibe "Dosador Pet" na tela
  lcd.setCursor(0, 1);                 // Move o cursor para a coluna 0, linha 1
  lcd.print("Inicializando...");       // Exibe "Inicializando..."

  // Inicialização do Servo
  servoMotor.attach(servoPin);         // Anexa o servo ao pino designado
  servoMotor.write(0);                 // Define a posição inicial do servo

  delay(2000);                         // Aguarda 2 segundos
  lcd.clear();                         // Limpa o display LCD
}

void loop() {
  unsigned long currentMillis = millis(); // Obtém o tempo atual em milissegundos

  // Atualizar o relógio a cada segundo
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;    // Atualiza o último tempo verificado
    totalSeconds++;                    // Incrementa o total de segundos
    updateClock();                     // Atualiza a hora, minuto e segundo atuais

    // Verificar se passou um dia (24 horas)
    if (totalSeconds >= 86400) {       // Se total de segundos for 24 horas
      totalSeconds = 0;                // Reinicia o total de segundos
      resetDailyFlags();               // Reinicia as alimentações diárias
    }
  }

  // Mostrar o tempo atual no LCD
  displayCurrentTime();                // Exibe a hora e alimentações no LCD

  // Verificar se é hora de alimentar
  checkFeedingTimes();                 // Verifica se é o horário de alimentação

  delay(10);                           // Pequena pausa para estabilidade
}

void updateClock() {
  currentSecond++;                     // Incrementa o segundo atual
  if (currentSecond >= 60) {           // Se segundos alcançam 60
    currentSecond = 0;                 // Reinicia segundos
    currentMinute++;                   // Incrementa o minuto atual
    if (currentMinute >= 60) {         // Se minutos alcançam 60
      currentMinute = 0;               // Reinicia minutos
      currentHour++;                   // Incrementa a hora atual
      if (currentHour >= 24) {         // Se horas alcançam 24
        currentHour = 0;               // Reinicia horas
      }
    }
  }
}

void resetDailyFlags() {
  for (int i = 0; i < numberOfMeals; i++) {
    feedingTimes[i].fedToday = false;  // Reinicia o status de alimentação para cada horário
  }
  feedingsToday = 0;                   // Reinicia o contador de alimentações diárias
}

void displayCurrentTime() {
  lcd.setCursor(0, 0);
  lcd.print("Hora: ");
  if (currentHour < 10) lcd.print("0");
  lcd.print(currentHour);
  lcd.print(":");
  if (currentMinute < 10) lcd.print("0");
  lcd.print(currentMinute);
  lcd.print(":");
  if (currentSecond < 10) lcd.print("0");
  lcd.print(currentSecond);

  // Mostrar o número de alimentações realizadas no dia
  lcd.setCursor(0, 1);
  lcd.print("Alimentacoes: ");
  lcd.print(feedingsToday);
}

void checkFeedingTimes() {
  for (int i = 0; i < numberOfMeals; i++) {
    if (!feedingTimes[i].fedToday &&                   // Se ainda não alimentou nesse horário
        currentHour == feedingTimes[i].hour &&         // Verifica hora
        currentMinute == feedingTimes[i].minute &&     // Verifica minuto
        currentSecond == feedingTimes[i].second) {     // Verifica segundo
      dispenseFood(i + 1);                             // Dispensar alimento
      feedingTimes[i].fedToday = true;                 // Marca como alimentado
      feedingsToday++;                                 // Incrementa o contador diário
    }
  }
}

void dispenseFood(int mealNumber) {
  lcd.setCursor(0, 1);
  lcd.print("Dispensando " + String(mealNumber) + "...");

  // Acionar o servo para dispensar a ração
  servoMotor.write(90);    // Abre o dispensador
  delay(1000);             // Aguarda 1 segundo
  servoMotor.write(0);     // Fecha o dispensador

  lcd.setCursor(0, 1);
  lcd.print("Pronto!          "); // Limpa o restante da linha
}