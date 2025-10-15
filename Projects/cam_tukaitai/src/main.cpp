//#include <M5Core2.h>
#include "uart_frame.h"

typedef struct _JpegFrame_t
{
  uint8_t *buf;
  uint32_t size;
} JpegFrame_t;

static QueueHandle_t jpeg_fream_queue = NULL;

// UART
const int UART_RX_PIN = 33; 
const int UART_TX_PIN = 32;
const int UART_BAUD_RATE = 1500000;

void frame_recv_callback(int cmd, const uint8_t *buf, int len)
{
  JpegFrame_t frame;
  frame.buf = (uint8_t *)malloc(sizeof(uint8_t) * len);
  memcpy(frame.buf, buf, len);
  frame.size = len;

  if (xQueueSend(jpeg_fream_queue, &frame, 0) != pdTRUE)
  {
    free(frame.buf);
  }
}

void setup()
{
  M5.begin();
  Serial.begin(1500000);
   uart_frame_init(UART_RX_PIN, UART_TX_PIN, UART_BAUD_RATE);
}


void loop()
{
  JpegFrame_t frame;
  int time_last = 0;
  time_last = millis();
  xQueueReceive(jpeg_fream_queue, &frame, portMAX_DELAY);
  M5.Lcd.drawJpg(frame.buf, frame.size, 0, 0);
  Serial.printf("--%ld--size--%d--\r\n", millis() - time_last, frame.size);
  free(frame.buf);
}


