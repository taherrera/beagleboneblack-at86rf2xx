#define SPI_BUS 0        // /dev/spidev0.x
#define SPI_CS 0         // /dev/spidev0.0
#define SPI_FREQ 4000000 // in Hz
#define CLOCKMODE 3      // ?


/**
 * @brief Called when Ctrl+C is pressed - triggers the program to stop.
 */
void stopHandler(int sig) {
  running = 0;
}

int main() {
	int spi_fd, value;
	// Open the SPI device file:
	spi_fd = SPI_open(SPI_BUS, SPI_CS);
	if (spi_fd < 0) {
		printf("*Could not open SPI bus %d\n", AD7390_BUS);
		exit(0);
	}
	// Configure the SPI bus:
	spi_init(spi_fd);

	// Loop until Ctrl+C pressed:
	running = 1;
	signal(SIGINT, stopHandler);
	while(running) {
		// Ramp up from 0V to full-scale:
		for (value=0; value<4095; value++) {
			AD7390_setValue(spi_fd, value);
	}
		// Ramp down from full-scale to 0V:
		for (value=4096; value>0; value--) {
			AD7390_setValue(spi_fd, value);
		}
	}
	// Set DAC output to 0 and close the SPI file descriptor:
	AD7390_setValue(spi_fd, 0);
	SPI_close(spi_fd);
	return 0;
}
