#include "libspi-pipe-ng.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

int spipipeng_transfer(int fd, const void *tx_buf, uint32_t tx_len, void *rx_buf, uint32_t rx_len, uint32_t speed_hz)
{
    if (!speed_hz) speed_hz = 12500000;
    if (!tx_len || !tx_buf || (rx_len && !rx_buf)) { errno = EINVAL; return -1; }

    struct spi_ioc_transfer spi_msg[2] =
    {
        {
            .tx_buf = (__u64)tx_buf,
            .rx_buf = (__u64)NULL,
            .len = tx_len,
            .speed_hz = speed_hz,
            .delay_usecs = 0,
            .bits_per_word = 8,
            .cs_change = 0
        },
        {
            .tx_buf = (__u64)NULL,
            .rx_buf = (__u64)rx_buf,
            .len = rx_len,
            .speed_hz = speed_hz,
            .delay_usecs = 0,
            .bits_per_word = 8,
            .cs_change = 0
        }
    };

    return (ioctl(fd, SPI_IOC_MESSAGE(rx_len ? 2 : 1), spi_msg) >= 0) ? 0 : -1;
}
