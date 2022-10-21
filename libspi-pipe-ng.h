#include <stdint.h>

int spipipeng_transfer(int fd, const void *tx_buf, uint32_t tx_len, void *rx_buf, uint32_t rx_len, uint32_t speed_hz);
