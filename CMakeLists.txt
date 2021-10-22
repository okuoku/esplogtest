cmake_minimum_required(VERSION 3.14) # For RULE_LAUNCH_CUSTOM fix
project(esplogtest)

set(PORT /dev/ttyS6) # COM7
set(idf_path ${CMAKE_CURRENT_LIST_DIR}/esp-idf)
set(ENV{IDF_PATH} ${idf_path})

set(maint_check $ENV{IDF_MAINTAINER})
if(NOT maint_check)
    message(FATAL_ERROR "Set IDF_MAINTAINER to silence IDF error")
endif()

# Generate custom launcher
set(launcher_file ${CMAKE_CURRENT_BINARY_DIR}/runtool.sh)
set(launcher_src "#!/bin/sh\nexport ESPPORT=${PORT}\nexport IDF_PATH=${idf_path}\nexec \"$@\"\n")
file(WRITE ${launcher_file} ${launcher_src})
set_property(GLOBAL
    PROPERTY RULE_LAUNCH_CUSTOM
    ${launcher_file})

execute_process(COMMAND
    chmod +x ${launcher_file})


include($ENV{IDF_PATH}/tools/cmake/idf.cmake)

# BTstack
set(BTSTACK ${CMAKE_CURRENT_LIST_DIR}/btstack)
set(btstack_srcs0
    port/esp32/components/btstack/btstack_audio_esp32.c
    port/esp32/components/btstack/btstack_port_esp32.c
    port/esp32/components/btstack/btstack_stdin_esp32.c
    port/esp32/components/btstack/btstack_tlv_esp32.c

    3rd-party/bluedroid/decoder/include/oi_assert.h
    3rd-party/bluedroid/decoder/include/oi_bitstream.h
    3rd-party/bluedroid/decoder/include/oi_bt_spec.h
    3rd-party/bluedroid/decoder/include/oi_codec_sbc.h
    3rd-party/bluedroid/decoder/include/oi_codec_sbc_private.h
    3rd-party/bluedroid/decoder/include/oi_common.h
    3rd-party/bluedroid/decoder/include/oi_cpu_dep.h
    3rd-party/bluedroid/decoder/include/oi_modules.h
    3rd-party/bluedroid/decoder/include/oi_osinterface.h
    3rd-party/bluedroid/decoder/include/oi_status.h
    3rd-party/bluedroid/decoder/include/oi_stddefs.h
    3rd-party/bluedroid/decoder/include/oi_string.h
    3rd-party/bluedroid/decoder/include/oi_time.h
    3rd-party/bluedroid/decoder/include/oi_utils.h
    3rd-party/bluedroid/decoder/srce/alloc.c
    3rd-party/bluedroid/decoder/srce/bitalloc-sbc.c
    3rd-party/bluedroid/decoder/srce/bitalloc.c
    3rd-party/bluedroid/decoder/srce/bitstream-decode.c
    3rd-party/bluedroid/decoder/srce/decoder-oina.c
    3rd-party/bluedroid/decoder/srce/decoder-private.c
    3rd-party/bluedroid/decoder/srce/decoder-sbc.c
    3rd-party/bluedroid/decoder/srce/dequant.c
    3rd-party/bluedroid/decoder/srce/framing-sbc.c
    3rd-party/bluedroid/decoder/srce/framing.c
    3rd-party/bluedroid/decoder/srce/oi_codec_version.c
    3rd-party/bluedroid/decoder/srce/synthesis-8-generated.c
    3rd-party/bluedroid/decoder/srce/synthesis-dct8.c
    3rd-party/bluedroid/decoder/srce/synthesis-sbc.c
    3rd-party/bluedroid/encoder/include/sbc_dct.h
    3rd-party/bluedroid/encoder/include/sbc_encoder.h
    3rd-party/bluedroid/encoder/include/sbc_enc_func_declare.h
    3rd-party/bluedroid/encoder/include/sbc_types.h
    3rd-party/bluedroid/encoder/srce/sbc_analysis.c
    3rd-party/bluedroid/encoder/srce/sbc_dct.c
    3rd-party/bluedroid/encoder/srce/sbc_dct_coeffs.c
    3rd-party/bluedroid/encoder/srce/sbc_encoder.c
    3rd-party/bluedroid/encoder/srce/sbc_enc_bit_alloc_mono.c
    3rd-party/bluedroid/encoder/srce/sbc_enc_bit_alloc_ste.c
    3rd-party/bluedroid/encoder/srce/sbc_enc_coeffs.c
    3rd-party/bluedroid/encoder/srce/sbc_packing.c
    3rd-party/hxcmod-player/hxcmod.c
    3rd-party/hxcmod-player/hxcmod.h
    3rd-party/hxcmod-player/mods/mod.h
    3rd-party/hxcmod-player/mods/nao-deceased_by_disease.c
    3rd-party/lwip/dhcp-server/dhserver.c
    3rd-party/lwip/dhcp-server/dhserver.h
    3rd-party/md5/md5.c
    3rd-party/md5/md5.h
    3rd-party/micro-ecc/uECC.c
    3rd-party/micro-ecc/uECC.h
    3rd-party/yxml/yxml.c
    3rd-party/yxml/yxml.h
    src/ad_parser.c
    src/ad_parser.h
    src/ble/att_db.c
    src/ble/att_db.h
    src/ble/att_db_util.c
    src/ble/att_db_util.h
    src/ble/att_dispatch.c
    src/ble/att_dispatch.h
    src/ble/att_server.c
    src/ble/att_server.h
    src/ble/core.h
    src/ble/gatt-service/ancs_client.c
    src/ble/gatt-service/ancs_client.h
    src/ble/gatt-service/battery_service.gatt
    src/ble/gatt-service/battery_service_client.c
    src/ble/gatt-service/battery_service_client.h
    src/ble/gatt-service/battery_service_server.c
    src/ble/gatt-service/battery_service_server.h
    src/ble/gatt-service/cycling_power_service.gatt
    src/ble/gatt-service/cycling_power_service_server.c
    src/ble/gatt-service/cycling_power_service_server.h
    src/ble/gatt-service/cycling_speed_and_cadence_service.gatt
    src/ble/gatt-service/cycling_speed_and_cadence_service_server.c
    src/ble/gatt-service/cycling_speed_and_cadence_service_server.h
    src/ble/gatt-service/device_information_service.gatt
    src/ble/gatt-service/device_information_service_client.c
    src/ble/gatt-service/device_information_service_client.h
    src/ble/gatt-service/device_information_service_server.c
    src/ble/gatt-service/device_information_service_server.h
    src/ble/gatt-service/heart_rate_service.gatt
    src/ble/gatt-service/heart_rate_service_server.c
    src/ble/gatt-service/heart_rate_service_server.h
    src/ble/gatt-service/hids.gatt
    src/ble/gatt-service/hids_client.c
    src/ble/gatt-service/hids_client.h
    src/ble/gatt-service/hids_device.c
    src/ble/gatt-service/hids_device.h
    src/ble/gatt-service/Makefile.inc
    src/ble/gatt-service/mesh_provisioning_service.gatt
    src/ble/gatt-service/mesh_provisioning_service_server.c
    src/ble/gatt-service/mesh_provisioning_service_server.h
    src/ble/gatt-service/mesh_proxy_service.gatt
    src/ble/gatt-service/mesh_proxy_service_server.c
    src/ble/gatt-service/mesh_proxy_service_server.h
    src/ble/gatt-service/nordic_spp_service.gatt
    src/ble/gatt-service/nordic_spp_service_server.c
    src/ble/gatt-service/nordic_spp_service_server.h
    src/ble/gatt-service/scan_parameters_service.gatt
    src/ble/gatt-service/scan_parameters_service_client.c
    src/ble/gatt-service/scan_parameters_service_client.h
    src/ble/gatt-service/scan_parameters_service_server.c
    src/ble/gatt-service/scan_parameters_service_server.h
    src/ble/gatt-service/ublox_spp_service.gatt
    src/ble/gatt-service/ublox_spp_service_server.c
    src/ble/gatt-service/ublox_spp_service_server.h
    src/ble/gatt_client.c
    src/ble/gatt_client.h
    src/ble/le_device_db.h
    src/ble/le_device_db_memory.c
    src/ble/le_device_db_tlv.c
    src/ble/le_device_db_tlv.h
    src/ble/Makefile.inc
    src/ble/sm.c
    src/ble/sm.h
    src/bluetooth.h
    src/bluetooth_company_id.h
    src/bluetooth_data_types.h
    src/bluetooth_gatt.h
    src/bluetooth_psm.h
    src/bluetooth_sdp.h
    src/btstack.h
    src/btstack_audio.c
    src/btstack_audio.h
    src/btstack_base64_decoder.c
    src/btstack_base64_decoder.h
    src/btstack_bool.h
    src/btstack_chipset.h
    src/btstack_control.h
    src/btstack_crypto.c
    src/btstack_crypto.h
    src/btstack_debug.h
    src/btstack_defines.h
    src/btstack_em9304_spi.h
    src/btstack_event.h
    src/btstack_hid.c
    src/btstack_hid.h
    src/btstack_hid_parser.c
    src/btstack_hid_parser.h
    src/btstack_linked_list.c
    src/btstack_linked_list.h
    src/btstack_linked_queue.c
    src/btstack_linked_queue.h
    src/btstack_memory.c
    src/btstack_memory.h
    src/btstack_memory_pool.c
    src/btstack_memory_pool.h
    src/btstack_network.h
    src/btstack_resample.c
    src/btstack_resample.h
    src/btstack_ring_buffer.c
    src/btstack_ring_buffer.h
    src/btstack_run_loop.c
    src/btstack_run_loop.h
    src/btstack_run_loop_base.c
    src/btstack_run_loop_base.h
    src/btstack_sco_transport.h
    src/btstack_slip.c
    src/btstack_slip.h
    src/btstack_stdin.h
    src/btstack_tlv.c
    src/btstack_tlv.h
    src/btstack_tlv_none.c
    src/btstack_tlv_none.h
    src/btstack_uart.h
    src/btstack_uart_block.h
    src/btstack_uart_slip_wrapper.c
    src/btstack_uart_slip_wrapper.h
    src/btstack_util.c
    src/btstack_util.h
    src/classic/a2dp_sink.c
    src/classic/a2dp_sink.h
    src/classic/a2dp_source.c
    src/classic/a2dp_source.h
    src/classic/avdtp.c
    src/classic/avdtp.h
    src/classic/avdtp_acceptor.c
    src/classic/avdtp_acceptor.h
    src/classic/avdtp_initiator.c
    src/classic/avdtp_initiator.h
    src/classic/avdtp_sink.c
    src/classic/avdtp_sink.h
    src/classic/avdtp_source.c
    src/classic/avdtp_source.h
    src/classic/avdtp_util.c
    src/classic/avdtp_util.h
    src/classic/avrcp.c
    src/classic/avrcp.h
    src/classic/avrcp_browsing.c
    src/classic/avrcp_browsing.h
    src/classic/avrcp_browsing_controller.c
    src/classic/avrcp_browsing_controller.h
    src/classic/avrcp_browsing_target.c
    src/classic/avrcp_browsing_target.h
    src/classic/avrcp_controller.c
    src/classic/avrcp_controller.h
    src/classic/avrcp_media_item_iterator.c
    src/classic/avrcp_media_item_iterator.h
    src/classic/avrcp_target.c
    src/classic/avrcp_target.h
    src/classic/bnep.c
    src/classic/bnep.h
    src/classic/btstack_cvsd_plc.c
    src/classic/btstack_cvsd_plc.h
    src/classic/btstack_link_key_db.h
    src/classic/btstack_link_key_db_memory.c
    src/classic/btstack_link_key_db_memory.h
    src/classic/btstack_link_key_db_static.c
    src/classic/btstack_link_key_db_static.h
    src/classic/btstack_link_key_db_tlv.c
    src/classic/btstack_link_key_db_tlv.h
    src/classic/btstack_sbc.h
    src/classic/btstack_sbc_decoder_bluedroid.c
    src/classic/btstack_sbc_encoder_bluedroid.c
    src/classic/btstack_sbc_plc.c
    src/classic/btstack_sbc_plc.h
    src/classic/core.h
    src/classic/device_id_server.c
    src/classic/device_id_server.h
    src/classic/gatt_sdp.c
    src/classic/gatt_sdp.h
    src/classic/goep_client.c
    src/classic/goep_client.h
    src/classic/hfp.c
    src/classic/hfp.h
    src/classic/hfp_ag.c
    src/classic/hfp_ag.h
    src/classic/hfp_gsm_model.c
    src/classic/hfp_gsm_model.h
    src/classic/hfp_hf.c
    src/classic/hfp_hf.h
    src/classic/hfp_msbc.c
    src/classic/hfp_msbc.h
    src/classic/hid_device.c
    src/classic/hid_device.h
    src/classic/hid_host.c
    src/classic/hid_host.h
    src/classic/hsp_ag.c
    src/classic/hsp_ag.h
    src/classic/hsp_hs.c
    src/classic/hsp_hs.h
    src/classic/Makefile.inc
    src/classic/obex.h
    src/classic/obex_iterator.c
    src/classic/obex_iterator.h
    src/classic/obex_message_builder.c
    src/classic/obex_message_builder.h
    src/classic/pan.c
    src/classic/pan.h
    src/classic/pbap_client.c
    src/classic/pbap_client.h
    src/classic/rfcomm.c
    src/classic/rfcomm.h
    src/classic/sdp_client.c
    src/classic/sdp_client.h
    src/classic/sdp_client_rfcomm.c
    src/classic/sdp_client_rfcomm.h
    src/classic/sdp_server.c
    src/classic/sdp_server.h
    src/classic/sdp_util.c
    src/classic/sdp_util.h
    src/classic/spp_server.c
    src/classic/spp_server.h
    src/gap.h
    src/hci.c
    src/hci.h
    src/hci_cmd.c
    src/hci_cmd.h
    src/hci_dump.c
    src/hci_dump.h
    src/hci_transport.h
    src/hci_transport_em9304_spi.c
    src/hci_transport_em9304_spi.h
    src/hci_transport_h4.c
    src/hci_transport_h4.h
    src/hci_transport_h5.c
    src/hci_transport_h5.h
    src/hci_transport_usb.h
    src/l2cap.c
    src/l2cap.h
    src/l2cap_signaling.c
    src/l2cap_signaling.h
    src/Makefile.inc
    src/mesh/adv_bearer.c
    src/mesh/adv_bearer.h
    src/mesh/beacon.c
    src/mesh/beacon.h
    src/mesh/gatt_bearer.c
    src/mesh/gatt_bearer.h
    src/mesh/mesh.c
    src/mesh/mesh.h
    src/mesh/mesh_access.c
    src/mesh/mesh_access.h
    src/mesh/mesh_configuration_client.c
    src/mesh/mesh_configuration_client.h
    src/mesh/mesh_configuration_server.c
    src/mesh/mesh_configuration_server.h
    src/mesh/mesh_crypto.c
    src/mesh/mesh_crypto.h
    src/mesh/mesh_foundation.c
    src/mesh/mesh_foundation.h
    src/mesh/mesh_generic_default_transition_time_client.c
    src/mesh/mesh_generic_default_transition_time_client.h
    src/mesh/mesh_generic_default_transition_time_server.c
    src/mesh/mesh_generic_default_transition_time_server.h
    src/mesh/mesh_generic_level_client.c
    src/mesh/mesh_generic_level_client.h
    src/mesh/mesh_generic_level_server.c
    src/mesh/mesh_generic_level_server.h
    src/mesh/mesh_generic_model.h
    src/mesh/mesh_generic_on_off_client.c
    src/mesh/mesh_generic_on_off_client.h
    src/mesh/mesh_generic_on_off_server.c
    src/mesh/mesh_generic_on_off_server.h
    src/mesh/mesh_health_server.c
    src/mesh/mesh_health_server.h
    src/mesh/mesh_iv_index_seq_number.c
    src/mesh/mesh_iv_index_seq_number.h
    src/mesh/mesh_keys.c
    src/mesh/mesh_keys.h
    src/mesh/mesh_lower_transport.c
    src/mesh/mesh_lower_transport.h
    src/mesh/mesh_network.c
    src/mesh/mesh_network.h
    src/mesh/mesh_node.c
    src/mesh/mesh_node.h
    src/mesh/mesh_peer.c
    src/mesh/mesh_peer.h
    src/mesh/mesh_proxy.c
    src/mesh/mesh_proxy.h
    src/mesh/mesh_upper_transport.c
    src/mesh/mesh_upper_transport.h
    src/mesh/mesh_virtual_addresses.c
    src/mesh/mesh_virtual_addresses.h
    src/mesh/pb_adv.c
    src/mesh/pb_adv.h
    src/mesh/pb_gatt.c
    src/mesh/pb_gatt.h
    src/mesh/provisioning.c
    src/mesh/provisioning.h
    src/mesh/provisioning_device.c
    src/mesh/provisioning_device.h
    src/mesh/provisioning_provisioner.c
    src/mesh/provisioning_provisioner.h

    platform/freertos/btstack_run_loop_freertos.c
    platform/freertos/btstack_run_loop_freertos.h
    platform/freertos/btstack_uart_block_freertos.c

    platform/embedded/btstack_audio_embedded.c
    #platform/embedded/btstack_em9304_spi_embedded.c
    platform/embedded/btstack_run_loop_embedded.c
    platform/embedded/btstack_run_loop_embedded.h
    #platform/embedded/btstack_stdin_embedded.c
    platform/embedded/btstack_tlv_flash_bank.c
    platform/embedded/btstack_tlv_flash_bank.h
    platform/embedded/btstack_uart_block_embedded.c
    platform/embedded/hal_audio.h
    platform/embedded/hal_cpu.h
    platform/embedded/hal_em9304_spi.h
    platform/embedded/hal_flash_bank.h
    platform/embedded/hal_flash_bank_memory.c
    platform/embedded/hal_flash_bank_memory.h
    platform/embedded/hal_led.h
    platform/embedded/hal_stdin.h
    platform/embedded/hal_tick.h
    platform/embedded/hal_time_ms.h
    platform/embedded/hal_uart_dma.h
    platform/embedded/hci_dump_embedded_stdout.c
    platform/embedded/hci_dump_embedded_stdout.h
    #platform/embedded/hci_dump_segger_rtt_binary.c
    #platform/embedded/hci_dump_segger_rtt_binary.h
    #platform/embedded/hci_dump_segger_rtt_stdout.c
    #platform/embedded/hci_dump_segger_rtt_stdout.h

    platform/lwip/bnep_lwip.c
    platform/lwip/bnep_lwip.h
    platform/lwip/port/arch/cc.h
    platform/lwip/port/lwipopts.h
    #platform/lwip/port/sys_arch.c

    )

set(btstack_srcs)
foreach(e ${btstack_srcs0})
    list(APPEND btstack_srcs
        ${BTSTACK}/${e})
endforeach()
include_directories(
    # FIXME: IDF components
    ${idf_path}/components/spi_flash/include # nvs_flash dep.
    ${idf_path}/components/bt/include/esp32/include
    ${idf_path}/components/nvs_flash/include
    # BTstack
    ${BTSTACK}/port/esp32/components/btstack/include
    ${BTSTACK}/3rd-party/bluedroid/decoder/include
    ${BTSTACK}/3rd-party/bluedroid/encoder/include
    ${BTSTACK}/3rd-party/hxcmod-player
    ${BTSTACK}/3rd-party/hxcmod-player/mods
    #../lwip/lwip/src/include
    ${BTSTACK}/3rd-party/lwip/dhcp-server
    ${BTSTACK}/3rd-party/md5
    ${BTSTACK}/3rd-party/yxml
    ${BTSTACK}/3rd-party/micro-ecc # Missing?
    ${BTSTACK}/src/classic
    ${BTSTACK}/src/ble/gatt-service
    ${BTSTACK}/src/ble
    ${BTSTACK}/src/classic
    ${BTSTACK}/src
    ${BTSTACK}/platform/embedded
    ${BTSTACK}/platform/freertos
    ${BTSTACK}/platform/lwip
    )

# ESP-IDF targets
# https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html#using-esp-idf-in-custom-cmake-projects
idf_build_process(esp32
    # Initialize ESP-IDF (local build)
    SDKCONFIG ${CMAKE_CURRENT_LIST_DIR}/sdkconfig
    COMPONENTS esp32 freertos esptool_py
    # BTstack
    bt nvs_flash
    # my app
    esp_http_server # Need to be in COMPONENTS to see it in `menuconfig`
    )
add_executable(check 
    ${btstack_srcs}
    main.c)
target_link_libraries(check
    idf::bt
    idf::nvs_flash
    idf::esp_http_server
    idf::newlib)
idf_build_executable(check)


# Custom targets for tools

add_custom_target(run
    COMMAND
    ${PYTHON} ${idf_path}/components/esptool_py/esptool/esptool.py
    --chip esp32
    --baud 115200
    --after hard_reset
    --port ${PORT}
    write_flash
    # From flash_app_args
    --flash_mode dio --flash_freq 40m --flash_size 4MB
    0x10000 check.bin
    COMMAND
    ${PYTHON} ${idf_path}/tools/idf_monitor.py
    --port ${PORT}
    --baud 115200
    --decode-coredumps info
    --decode-panic backtrace
    ${CMAKE_CURRENT_BINARY_DIR}/check
    USES_TERMINAL)

add_custom_target(mon
    COMMAND
    ${PYTHON} ${idf_path}/tools/idf_monitor.py
    --port ${PORT}
    --baud 115200
    check.elf
    USES_TERMINAL)


