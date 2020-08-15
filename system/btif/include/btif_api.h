/******************************************************************************
 *
 *  Copyright 2009-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/*******************************************************************************
 *
 *  Filename:      btif_api.h
 *
 *  Description:   Main API header file for all BTIF functions accessed
 *                 from main bluetooth HAL. All HAL extensions will not
 *                 require headerfiles as they would be accessed through
 *                 callout/callins.
 *
 ******************************************************************************/

#ifndef BTIF_API_H
#define BTIF_API_H

#include <hardware/bluetooth.h>

#include "btif_common.h"
#include "btif_dm.h"

/*******************************************************************************
 *  BTIF CORE API
 ******************************************************************************/

/*******************************************************************************
 *
 * Function         btif_init_bluetooth
 *
 * Description      Creates BTIF task and prepares BT scheduler for startup
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_init_bluetooth(void);

/*******************************************************************************
 *
 * Function         btif_enable_bluetooth
 *
 * Description      Performs chip power on and kickstarts OS scheduler
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_enable_bluetooth(void);

/*******************************************************************************
 *
 * Function         btif_cleanup_bluetooth
 *
 * Description      Cleanup BTIF state.
 *
 *
 * Returns          void
 *
 ******************************************************************************/
bt_status_t btif_cleanup_bluetooth(void);

/*******************************************************************************
 *
 * Function         is_restricted_mode
 *
 * Description      Checks if BT was enabled in restriced mode. In restricted
 *                  mode, bonds that are created are marked as temporary.
 *                  These bonds persist until we leave restricted mode, at
 *                  which point they will be deleted from the config. Also
 *                  while in restricted mode, the user can access devices
 *                  that are already paired before entering restricted mode,
 *                  but they cannot remove any of these devices.
 *
 * Returns          bool
 *
 ******************************************************************************/
bool is_restricted_mode(void);

/*******************************************************************************
 *
 * Function         is_niap_mode_
 *
 * Description      Checks if BT was enabled in single user mode. In this
 *                  mode, use of keystore for key attestation of LTK is limitee
 *                  to this mode defined by UserManager.
 *
 * Returns          bool
 *
 ******************************************************************************/
bool is_niap_mode(void);

/*******************************************************************************
 *
 * Function         get_niap_config_compare_result
 *
 * Description      Get the niap config compare result for confirming the config
 *                  checksum compare result. When the niap mode doesn't enable,
 *                  it should be all pass (0b11).
 *                  Bit define:
 *                    CONFIG_FILE_COMPARE_PASS = 0b01
 *                    CONFIG_BACKUP_COMPARE_PASS = 0b10
 *
 * Returns          int
 *
 ******************************************************************************/
int get_niap_config_compare_result(void);

/*******************************************************************************
 *
 * Function         is_atv_device
 *
 * Description      Returns true if the local device is an Android TV
 *                  device, false if it is not.
 *
 * Returns          bool
 *
 ******************************************************************************/
bool is_atv_device(void);

/*******************************************************************************
 *
 * Function         btif_get_adapter_properties
 *
 * Description      Fetches all local adapter properties
 *
 ******************************************************************************/
void btif_get_adapter_properties(void);

bt_property_t* property_deep_copy(const bt_property_t* prop);

/*******************************************************************************
 *
 * Function         btif_get_adapter_property
 *
 * Description      Fetches property value from local cache
 *
 ******************************************************************************/
void btif_get_adapter_property(bt_property_type_t type);

/*******************************************************************************
 *
 * Function         btif_set_adapter_property
 *
 * Description      Updates core stack with property value and stores it in
 *                  local cache
 *
 ******************************************************************************/
void btif_set_adapter_property(bt_property_t* property);

/*******************************************************************************
 *
 * Function         btif_get_remote_device_property
 *
 * Description      Fetches the remote device property from the NVRAM
 *
 ******************************************************************************/
void btif_get_remote_device_property(RawAddress remote_addr,
                                     bt_property_type_t type);

/*******************************************************************************
 *
 * Function         btif_get_remote_device_properties
 *
 * Description      Fetches all the remote device properties from NVRAM
 *
 ******************************************************************************/
void btif_get_remote_device_properties(RawAddress remote_addr);

/*******************************************************************************
 *
 * Function         btif_set_remote_device_property
 *
 * Description      Writes the remote device property to NVRAM.
 *                  Currently, BT_PROPERTY_REMOTE_FRIENDLY_NAME is the only
 *                  remote device property that can be set
 *
 ******************************************************************************/
void btif_set_remote_device_property(RawAddress* remote_addr,
                                     bt_property_t* property);

/*******************************************************************************
 *
 * Function         btif_get_remote_service_record
 *
 * Description      Looks up the service matching uuid on the remote device
 *                  and fetches the SCN and service_name if the UUID is found
 *
 ******************************************************************************/
void btif_get_remote_service_record(const RawAddress remote_addr,
                                    const bluetooth::Uuid uuid);

/*******************************************************************************
 *  BTIF DM API
 ******************************************************************************/

/*******************************************************************************
 *
 * Function         btif_dm_start_discovery
 *
 * Description      Start device discovery/inquiry
 *
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_dm_start_discovery(void);

/*******************************************************************************
 *
 * Function         btif_dm_cancel_discovery
 *
 * Description      Cancels search
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_dm_cancel_discovery(void);

/*******************************************************************************
 *
 * Function         btif_dm_create_bond
 *
 * Description      Initiate bonding with the specified device
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_dm_create_bond(const RawAddress* bd_addr, int transport);

/*******************************************************************************
 *
 * Function         btif_dm_create_bond_out_of_band
 *
 * Description      Initiate bonding with the specified device using OOB data.
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_dm_create_bond_out_of_band(
    const RawAddress* bd_addr, int transport,
    const bt_out_of_band_data_t* oob_data);

/*******************************************************************************
 *
 * Function         btif_dm_cancel_bond
 *
 * Description      Initiate bonding with the specified device
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_dm_cancel_bond(const RawAddress* bd_addr);

/*******************************************************************************
 *
 * Function         btif_dm_remove_bond
 *
 * Description      Removes bonding with the specified device
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_dm_remove_bond(const RawAddress* bd_addr);

/*******************************************************************************
 *
 * Function         btif_dm_get_connection_state
 *
 * Description      Returns whether the remote device is currently connected
 *
 * Returns          0 if not connected
 *
 ******************************************************************************/
uint16_t btif_dm_get_connection_state(const RawAddress* bd_addr);

/*******************************************************************************
 *
 * Function         btif_dm_pin_reply
 *
 * Description      BT legacy pairing - PIN code reply
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_dm_pin_reply(const RawAddress* bd_addr, uint8_t accept,
                              uint8_t pin_len, bt_pin_code_t* pin_code);

/*******************************************************************************
 *
 * Function         btif_dm_passkey_reply
 *
 * Description      BT SSP passkey reply
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_dm_passkey_reply(const RawAddress* bd_addr, uint8_t accept,
                                  uint32_t passkey);

/*******************************************************************************
 *
 * Function         btif_dm_ssp_reply
 *
 * Description      BT SSP Reply - Just Works, Numeric Comparison & Passkey
 *                  Entry
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_dm_ssp_reply(const RawAddress* bd_addr,
                              bt_ssp_variant_t variant, uint8_t accept,
                              uint32_t passkey);

/*******************************************************************************
 *
 * Function         btif_dm_get_adapter_property
 *
 * Description      Queries the BTA for the adapter property
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_dm_get_adapter_property(bt_property_t* prop);

/*******************************************************************************
 *
 * Function         btif_dm_get_remote_services
 *
 * Description      Start SDP to get remote services
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_dm_get_remote_service_record(const RawAddress& remote_addr,
                                              const bluetooth::Uuid& uuid);

/*******************************************************************************
 *
 * Function         btif_dm_get_remote_services
 *
 * Description      Start SDP to get remote services
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
void btif_dm_get_remote_services(const RawAddress remote_addr);

/*******************************************************************************
 *
 * Function         btif_dm_get_remote_services_by_transport
 *
 * Description      Start SDP to get remote services by transport
 *
 * Returns          bt_status_t
 *
 ******************************************************************************/
bt_status_t btif_dm_get_remote_services_by_transport(RawAddress* remote_addr,
                                                     int transport);

/*******************************************************************************
 *
 * Function         btif_dut_mode_configure
 *
 * Description      Configure Test Mode - 'enable' to 1 puts the device in test
 *                  mode and 0 exits test mode
 *
 * Returns          BT_STATUS_SUCCESS on success
 *
 ******************************************************************************/
bt_status_t btif_dut_mode_configure(uint8_t enable);

/*******************************************************************************
 *
 * Function         btif_dut_mode_send
 *
 * Description     Sends a HCI Vendor specific command to the controller
 *
 * Returns          BT_STATUS_SUCCESS on success
 *
 ******************************************************************************/
bt_status_t btif_dut_mode_send(uint16_t opcode, uint8_t* buf, uint8_t len);

/*******************************************************************************
 *
 * Function         btif_le_test_mode
 *
 * Description     Sends a HCI BLE Test command to the Controller
 *
 * Returns          BT_STATUS_SUCCESS on success
 *
 ******************************************************************************/
bt_status_t btif_le_test_mode(uint16_t opcode, uint8_t* buf, uint8_t len);

/*******************************************************************************
 *
 * Function         btif_dm_read_energy_info
 *
 * Description     Reads the energy info from controller
 *
 * Returns          void
 *
 ******************************************************************************/
void btif_dm_read_energy_info();

/*******************************************************************************
 *
 * Function         btif_config_hci_snoop_log
 *
 * Description     enable or disable HCI snoop log
 *
 * Returns          BT_STATUS_SUCCESS on success
 *
 ******************************************************************************/
bt_status_t btif_config_hci_snoop_log(uint8_t enable);

/*******************************************************************************
 *
 * Function         btif_debug_bond_event_dump
 *
 * Description     Dump bond event information
 *
 * Returns          void
 *
 ******************************************************************************/
void btif_debug_bond_event_dump(int fd);

#endif /* BTIF_API_H */
