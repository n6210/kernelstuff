#ifndef _NRF24L01_SYSFS_H_
#define _NRF24L01_SYSFS_H_

#include <linux/device.h>

ssize_t nrf24l01_sysfs_show_channel(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_channel(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_address_pipe0(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe5(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_address_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_payload_width_pipe0(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe5(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_payload_width_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_enable_pipe0(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enable_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enable_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enable_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enable_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enable_pipe5(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_enable_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enable_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enable_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enable_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enable_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enable_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_dynpd_pipe0(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_dynpd_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_dynpd_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_dynpd_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_dynpd_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_dynpd_pipe5(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_dynpd_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_dynpd_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_dynpd_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_dynpd_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_dynpd_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_dynpd_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_enaa_pipe0(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enaa_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enaa_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enaa_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enaa_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enaa_pipe5(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_enaa_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enaa_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enaa_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enaa_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enaa_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enaa_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);

#endif
