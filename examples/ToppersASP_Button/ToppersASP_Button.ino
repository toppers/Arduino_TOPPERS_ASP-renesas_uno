#include <ToppersASP-renesas_uno.h>

#define BUTTON_PIN  2

// the setup function runs once when you press reset or power the board
void setup() {
  SerialUSB.begin(115200);
  while (!SerialUSB)
    ;

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_handler, RISING);

  // Start TOPPERS/ASP kernel
  StartToppersASP();
}

void button_handler(void) {    
    iwup_tsk(TASK2);
}

void task1(intptr_t exinf) {
  int count = 0;
  while (1) {
    SerialUSB.print("task1 is running. ");
    SerialUSB.println(count++);
    delay(1000);  // wait for a second
  }
}

void task2(intptr_t exinf) {
  int count = 0;
  while (1) {
    SerialUSB.print("task2 is running. ");
    SerialUSB.println(count++);
    slp_tsk();
  }
}

void user_inirtn(void) {
  T_CTSK ctsk;
  ER ercd;

  ctsk.tskatr = TA_ACT;
  ctsk.exinf = 1;
  ctsk.task = task1;
  ctsk.itskpri = 10;
  ctsk.stksz = 1024;
  ctsk.stk = NULL;
  ercd = cre_tsk(TASK1, &ctsk);
  if (ercd != E_OK) {
    SerialUSB.print("cre_tsk(TASK1) error! ercd = ");
    SerialUSB.println(ercd);
  }

  ctsk.task = task2;
  ercd = cre_tsk(TASK2, &ctsk);
  if (ercd != E_OK) {
    SerialUSB.print("cre_tsk(TASK2) error! ercd = ");
    SerialUSB.println(ercd);
  }
}

int loop_count;

// the loop function runs over and over again forever
void loop() {
  slp_tsk();
  SerialUSB.print("loop: ");
  SerialUSB.println(loop_count++);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}