/* Практичне завдання
 * Відстеження потоку людей у ТЦ
 * студентки ПІ-18-1
 * Кондратюк Наталії
 * Візуалізація графіку потоку людей
 * на OLED дисплеї
**************************************************************/

void printOled ( int *m, int sizeM ){

    u8g2.clearBuffer();
     for ( int i = 1; i < sizeM; i++ ){
        u8g2.drawLine ( (i-1)/6, hDisp - ((m[i-1])/5), i/6, hDisp - ((m[i])/5) );
      } // for i
    u8g2.sendBuffer();

    delay(1);
} // printOled
