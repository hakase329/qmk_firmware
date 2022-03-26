/*
 * ROWをpro microのIO、COLをPCF8574のIOエキスパンダで使うためのカスタムマトリクス
 *
 * - パクリ元は2箇所
 * [https://github.com/qmk/qmk_firmware/tree/master/keyboards/yiancardesigns/seigaiha]
 * [https://github.com/FREEWING-JP/qmk_firmware/tree/freewing/test_expand_io_i2c/keyboards/handwired/freewing/test_expand_io_i2c]
 * - 公式マニュアルも見たほうがいい
 * [https://github.com/qmk/qmk_firmware/blob/master/docs/ja/custom_matrix.md]
 */
#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "quantum.h"
#include "i2c_master.h"

#define PCF8574_I2C_TIMEOUT 50

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

/* Row全部OFF */
static void unselect_rows(void) {
    for(uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
    }
}

/* Row指定箇所だけON */
static void select_row(uint8_t row) {
    setPinOutput(row_pins[row]);
    writePinLow(row_pins[row]);
}

/* Row指定箇所だけOFF */
static void unselect_row(uint8_t row) {
    setPinInputHigh(row_pins[row]);
}

/*
 * PCF8574の初期化
 * 全部INPUT用に設定
 */
static void init_pins(void) {
    unselect_rows();

    // Col Input PCF8574 8bit
    // All Input Pull Up
    // Row 0 - 7 Input 'L' active
    uint8_t buf[] = { 0b11111111 };
    i2c_transmit((PORT_EXPANDER_ADDRESS << 1), buf, sizeof(buf), PCF8574_I2C_TIMEOUT);
}

/*
 * カスタムマトリックス実装部
 * ハードウェアの初期化
 */
void matrix_init_custom(void) {
    // Initialize I2C
    i2c_init();

    // Initialize key pins
    init_pins();
    wait_ms(50); // 50msってなんの値だろう…
}

/* matrix_scan_customから呼ばれる実際の処理部分 */
static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    matrix_io_delay();

    // Read Col Data
    uint8_t port_expander_col_buffer;
    i2c_receive((PORT_EXPANDER_ADDRESS << 1), &port_expander_col_buffer, sizeof(port_expander_col_buffer), PCF8574_I2C_TIMEOUT);

    // For each Cols
    for(uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        uint8_t pin_state;
        pin_state = port_expander_col_buffer & (1 << col_index);

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |=  pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    return (last_row_value != current_matrix[current_row]);
}

/*
 * カスタムマトリックス実装部
 * ここでマトリックススキャンを行なう
 */
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // Set row, Read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        matrix_has_changed |= read_cols_on_row(current_matrix, current_row);
    }

    return matrix_has_changed;
}
