#include <ToppersASP-renesas_uno.h>

#ifdef ARDUINO_UNOR4_MINIMA
#define Serial SerialUSB 
#endif /* ARDUINO_UNOWIFIR4 */

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // Start TOPPERS/ASP kernel
  StartToppersASP();
}

void task1(intptr_t exinf) {
  int count = 0;
  while (1) {
    Serial.print("task1 is running. ");
    Serial.println(count++);
    delay(1000);  // wait for a second
  }
}

void task2(intptr_t exinf) {
  int count = 0;
  while (1) {
    Serial.print("task2 is running. ");
    Serial.println(count++);
    delay(1000);  // wait for a second
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
    Serial.print("cre_tsk(TASK1) error! ercd = ");
    Serial.println(ercd);
  }

  ctsk.task = task2;
  ercd = cre_tsk(TASK2, &ctsk);
  if (ercd != E_OK) {
    Serial.print("cre_tsk(TASK2) error! ercd = ");
    Serial.println(ercd);
  }
}

int loop_count;

// the loop function runs over and over again forever
void loop() {
  Serial.print("loop: ");
  Serial.println(loop_count++);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}
