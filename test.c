typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef typeof(sizeof(0)) size_t;
typedef unsigned long long int uint64_t;

void memset_given(uint8_t *dest, uint8_t value, size_t len);
void memset_mod(uint8_t *dest, uint8_t value, size_t len);
void memset_bonus(uint8_t *dest, uint8_t value, size_t len);

#define TEST_BUFFER_SIZE 256
uint8_t aligned_test_buffer[TEST_BUFFER_SIZE] __attribute__((aligned(4)));
uint8_t *misaligned_test_buffer = aligned_test_buffer + 2;

// macro to start tracking the number of clock cycles
#define START_CYCLE_COUNTER(var)                                               \
  uint64_t var = 0;                                                            \
  asm volatile("rdcycle %0" : "=r"(var))

// macro to stop tracking the number of clock cycles, and dump in the `result`
// var
#define STOP_CYCLE_COUNTER(var, result)                                        \
  uint64_t var##_end = 0;                                                      \
  asm volatile("rdcycle %0" : "=r"(var##_end));                                \
  result = var##_end - var

// Memory address where the results for aligned buffer pointer tests must be
// dumped
volatile uint32_t *cycle_count_aligned = (uint32_t *)0x80040000;
volatile uint8_t *verify_status_aligned = (uint8_t *)0x80050000;

// Memory address where the results for misaligned buffer pointer tests must be
// dumped
volatile uint32_t *cycle_count_misaligned = (uint32_t *)0x80041000;
volatile uint8_t *verify_status_misaligned = (uint8_t *)0x80051000;

/*!
 * \breif function to verify if memset implementation dumps values appropriately
 *
 * \param `buffer` pointer to the write location
 * \param `expected` expected write value
 * \param `len` number of bytes expected to be written
 *
 * \return `0` if the write matches the expected values for the input number of
 *    bytes, `1` if not
 */
int verify_memory(uint8_t *buffer, uint8_t expected, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (buffer[i] != expected)
      return 1;
  }
  return 0;
}

/*!
 * \brief function to functionally test the memset implementations for a defined
 *    set of number of bytes and a write value, and calculate the number of
 *    clock cycles consumed respectively.
 *
 * \param `test_buffer` pointer to the write location
 * \param `cycle_count` pointer to dump the cycle count for each implementation
 * \param `verify_status` pointer to dump the verufy status for each
 *    implementation
 */
void test_function(uint8_t *test_buffer, volatile uint32_t *cycle_count,
                   volatile uint8_t *verify_status) {
  size_t test_sizes[4] = {0, 3, 15, 32};
  uint8_t test_value = 0x55;

  uint32_t cycles_count[3];

  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < TEST_BUFFER_SIZE; i++)
      test_buffer[i] = 0;

    for (int i = 0; i < 4; i++) {
      if (k == 0) {
        START_CYCLE_COUNTER(start_counter);
        memset_given(test_buffer, test_value, test_sizes[i]);
        STOP_CYCLE_COUNTER(start_counter, cycles_count[k]);
      } else if (k == 1) {
        START_CYCLE_COUNTER(start_counter);
        memset_mod(test_buffer, test_value, test_sizes[i]);
        STOP_CYCLE_COUNTER(start_counter, cycles_count[k]);
      } else {
        START_CYCLE_COUNTER(start_counter);
        memset_bonus(test_buffer, test_value, test_sizes[i]);
        STOP_CYCLE_COUNTER(start_counter, cycles_count[k]);
      }
      if (verify_memory(test_buffer, test_value, test_sizes[i]) == 0)
        *verify_status = (uint8_t)1;

      else
        while (1)
          ;

      *cycle_count = cycles_count[k];
      verify_status++;
      cycle_count++;
    }
  }
}

int main() {
  // Trigger test function for word-aligned buffer pointer
  test_function(aligned_test_buffer, cycle_count_aligned,
                verify_status_aligned);

  // Trigger test function for non-word-aligned buffer pointer
  test_function(misaligned_test_buffer, cycle_count_misaligned,
                verify_status_misaligned);

  return 0;
}
