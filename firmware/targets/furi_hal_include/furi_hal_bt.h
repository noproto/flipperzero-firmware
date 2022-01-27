/**
 * @file furi_hal_bt.h
 * BT/BLE HAL API
 */

#pragma once

#include <m-string.h>
#include <stdbool.h>
#include <gap.h>
#include <serial_service.h>
#include <ble_glue.h>
#include <ble_app.h>

#include "furi_hal_bt_serial.h"

#define FURI_HAL_BT_STACK_VERSION_MAJOR (1)
#define FURI_HAL_BT_STACK_VERSION_MINOR (13)

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FuriHalBtStackUnknown,
    FuriHalBtStackHciLayer,
    FuriHalBtStackLight,
} FuriHalBtStack;

typedef enum {
    FuriHalBtProfileSerial,
    FuriHalBtProfileHidKeyboard,

    // Keep last for Profiles number calculation
    FuriHalBtProfileNumber,
} FuriHalBtProfile;

/** Initialize
 */
void furi_hal_bt_init();

/** Lock core2 state transition */
void furi_hal_bt_lock_core2();

/** Lock core2 state transition */
void furi_hal_bt_unlock_core2();

/** Start radio stack
 *
 * @return  true on successfull radio stack start
 */
bool furi_hal_bt_start_radio_stack();

/** Get radio stack type
 *
 * @return  FuriHalBtStack instance
 */
FuriHalBtStack furi_hal_bt_get_radio_stack();

/** Start BLE app
 *
 * @param profile   FuriHalBtProfile instance
 * @param event_cb  GapEventCallback instance
 * @param context   pointer to context
 *
 * @return          true on success
*/
bool furi_hal_bt_start_app(FuriHalBtProfile profile, GapEventCallback event_cb, void* context);

/** Change BLE app
 * Restarts 2nd core
 *
 * @param profile   FuriHalBtProfile instance
 * @param event_cb  GapEventCallback instance
 * @param context   pointer to context
 *
 * @return          true on success
*/
bool furi_hal_bt_change_app(FuriHalBtProfile profile, GapEventCallback event_cb, void* context);

/** Update battery level
 *
 * @param battery_level battery level
 */
void furi_hal_bt_update_battery_level(uint8_t battery_level);

/** Start advertising
 */
void furi_hal_bt_start_advertising();

/** Stop advertising
 */
void furi_hal_bt_stop_advertising();

/** Get BT/BLE system component state
 *
 * @param[in]  buffer  string_t buffer to write to
 */
void furi_hal_bt_dump_state(string_t buffer);

/** Get BT/BLE system component state
 *
 * @return     true if core2 is alive
 */
bool furi_hal_bt_is_alive();

/** Get key storage buffer address and size
 *
 * @param      key_buff_addr  pointer to store buffer address
 * @param      key_buff_size  pointer to store buffer size
 */
void furi_hal_bt_get_key_storage_buff(uint8_t** key_buff_addr, uint16_t* key_buff_size);

/** Get SRAM2 hardware semaphore
 * @note Must be called before SRAM2 read/write operations
 */
void furi_hal_bt_nvm_sram_sem_acquire();

/** Release SRAM2 hardware semaphore
 * @note Must be called after SRAM2 read/write operations
 */
void furi_hal_bt_nvm_sram_sem_release();

/** Clear key storage
 *
 * @return      true on success
*/
bool furi_hal_bt_clear_white_list();

/** Set key storage change callback
 *
 * @param       callback    BleGlueKeyStorageChangedCallback instance
 * @param       context     pointer to context
 */
void furi_hal_bt_set_key_storage_change_callback(
    BleGlueKeyStorageChangedCallback callback,
    void* context);

/** Start ble tone tx at given channel and power
 *
 * @param[in]  channel  The channel
 * @param[in]  power    The power
 */
void furi_hal_bt_start_tone_tx(uint8_t channel, uint8_t power);

/** Stop ble tone tx
 */
void furi_hal_bt_stop_tone_tx();

/** Start sending ble packets at a given frequency and datarate
 *
 * @param[in]  channel   The channel
 * @param[in]  pattern   The pattern
 * @param[in]  datarate  The datarate
 */
void furi_hal_bt_start_packet_tx(uint8_t channel, uint8_t pattern, uint8_t datarate);

/** Stop sending ble packets
 *
 * @return     sent packet count
 */
uint16_t furi_hal_bt_stop_packet_test();

/** Start receiving packets
 *
 * @param[in]  channel   RX channel
 * @param[in]  datarate  Datarate
 */
void furi_hal_bt_start_packet_rx(uint8_t channel, uint8_t datarate);

/** Set up the RF to listen to a given RF channel
 *
 * @param[in]  channel  RX channel
 */
void furi_hal_bt_start_rx(uint8_t channel);

/** Stop RF listenning
 */
void furi_hal_bt_stop_rx();

/** Get RSSI
 *
 * @return     RSSI in dBm
 */
float furi_hal_bt_get_rssi();

/** Get number of transmitted packets
 *
 * @return     packet count
 */
uint32_t furi_hal_bt_get_transmitted_packets();

/** Start MAC addresses scan
 * @note Works only with HciLayer 2nd core firmware
 *
 * @param callback  GapScanCallback instance
 * @param context   pointer to context
 */
bool furi_hal_bt_start_scan(GapScanCallback callback, void* context);

/** Stop MAC addresses scan */
void furi_hal_bt_stop_scan();

#ifdef __cplusplus
}
#endif