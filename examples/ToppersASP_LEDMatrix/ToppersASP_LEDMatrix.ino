#include <ToppersASP-renesas_uno.h>

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

#ifdef ARDUINO_UNOR4_MINIMA
#error Arduino UNO R4 Minima is not supported!
#endif /* ARDUINO_UNOWIFIR4 */

ArduinoLEDMatrix matrix;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  matrix.begin();

  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  // add some static text
  // will only show "UNO" (not enough space on the display)
  const char text[] = "UNO r4";
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText();

  matrix.endDraw();
  
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
    SerialUSB.print("cre_tsk(TASK1) error! ercd = ");
    SerialUSB.println(ercd);
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
  // Make it scroll!
  matrix.beginDraw();

  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(50);

  // add the text
  const char text[] = "    TOPPERS/ASP Kernel for Arduino UNO R4!    ";
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText(SCROLL_LEFT);

  matrix.endDraw();
}