#include <linux/kernel.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/device.h>

#include "nrf24l01_core.h"
#include "nrf24l01_functions.h"
#include "nrf24l01_sysfs.h"

static char* nrf24l01_sanitize_string(const char* data, size_t len)
{
	char* str = vzalloc(len + 1);
	if(!str)
		return str;
	memcpy(str, data, len);
	return str;
}

ssize_t nrf24l01_sysfs_show_channel(struct device* dev, struct device_attribute* attr, char* buf)
{
	unsigned int channel;
	int err;
	if((err = nrf24l01_get_channel(((nrf24l01_chrdev*)dev_get_drvdata(dev))->nrf, &channel)))
		return err;
	printk(KERN_INFO "Got channel %d\n", channel);
	return sprintf(buf, "%d\n", channel);
}

ssize_t nrf24l01_sysfs_store_channel(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	unsigned int channel;
	ssize_t err;
	char* buff = nrf24l01_sanitize_string(buf, count);
	if(!buff)
		return -ENOMEM;
	if((err = kstrtouint(buff, 10, &channel)))
		goto exit_buffalloc;
	err = nrf24l01_set_channel(((nrf24l01_chrdev*)dev_get_drvdata(dev))->nrf, channel);	
	if(err)
		goto exit_buffalloc;
	return count;
exit_buffalloc:
	vfree(buff);
	return err;
}

static ssize_t nrf24l01_sysfs_show_address(struct device* dev, char* buf, unsigned int pipe)
{
	int err;
	unsigned int addr_width;
	u64 addr = 0;
	nrf24l01_t* nrf = ((nrf24l01_chrdev*)dev_get_drvdata(dev))->nrf;
	if((err = nrf24l01_get_address_u64(nrf, &addr, pipe)))
		return err;
	if(pipe <= 1)
	{
		if((err = nrf24l01_get_address_width(nrf, &addr_width)))
			return err;
		char fmt[10];
		sprintf(fmt, "%%0%ullX\n", addr_width);
		return sprintf(buf, fmt, addr);
	}
	else
		return sprintf(buf, "%02llX\n", addr);
}

ssize_t nrf24l01_sysfs_show_address_pipe0(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_address(dev, buf, 0);
}

ssize_t nrf24l01_sysfs_show_address_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_address(dev, buf, 1);
}

ssize_t nrf24l01_sysfs_show_address_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_address(dev, buf, 2);
}

ssize_t nrf24l01_sysfs_show_address_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_address(dev, buf, 3);
}

ssize_t nrf24l01_sysfs_show_address_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_address(dev, buf, 4);
}

ssize_t nrf24l01_sysfs_show_address_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_address(dev, buf, 5);
}

static ssize_t nrf24l01_sysfs_store_address(struct device* dev, const char* buf, size_t count, unsigned int pipe)
{
	ssize_t err;
	u64 addr;
	nrf24l01_t* nrf = ((nrf24l01_chrdev*)dev_get_drvdata(dev))->nrf;
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtou64(str, 16, &addr)))
		goto exit_stralloc;
	if((err = nrf24l01_set_address_u64(nrf, addr, pipe)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_address_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_address(dev, buf, count, 0);
}

ssize_t nrf24l01_sysfs_store_address_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_address(dev, buf, count, 1);
}

ssize_t nrf24l01_sysfs_store_address_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_address(dev, buf, count, 2);
}

ssize_t nrf24l01_sysfs_store_address_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_address(dev, buf, count, 3);
}

ssize_t nrf24l01_sysfs_store_address_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_address(dev, buf, count, 4);
}

ssize_t nrf24l01_sysfs_store_address_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_address(dev, buf, count, 5);
}

static ssize_t nrf24l01_sysfs_show_payload_width(struct device* dev, char* buf, unsigned int pipe)
{
	ssize_t err;
	unsigned int width;
	nrf24l01_t* nrf = ((nrf24l01_chrdev*)dev_get_drvdata(dev))->nrf;
	if((err = nrf24l01_get_pld_width(nrf, pipe, &width)))
		goto exit_err;
	return sprintf(buf, "%u\n", width);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe0(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_payload_width(dev, buf, 0);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_payload_width(dev, buf, 1);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_payload_width(dev, buf, 2);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_payload_width(dev, buf, 3);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_payload_width(dev, buf, 4);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_payload_width(dev, buf, 5);
}

static ssize_t nrf24l01_sysfs_store_payload_width(struct device* dev, const char* buf, size_t count, unsigned int pipe)
{
	ssize_t err;
	unsigned int width;
	nrf24l01_t* nrf = ((nrf24l01_chrdev*)dev_get_drvdata(dev))->nrf;
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &width)))
		goto exit_stralloc;
	if((err = nrf24l01_set_pld_width(nrf, pipe, width)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_payload_width(dev, buf, count, 0);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_payload_width(dev, buf, count, 1);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_payload_width(dev, buf, count, 2);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_payload_width(dev, buf, count, 3);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_payload_width(dev, buf, count, 4);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_payload_width(dev, buf, count, 5);
}

static ssize_t nrf24l01_sysfs_show_enable(struct device* dev, char* buf, unsigned int pipe)
{
	ssize_t err;
	unsigned int state;
	nrf24l01_t* nrf = ((nrf24l01_chrdev*)dev_get_drvdata(dev))->nrf;
	if((err = nrf24l01_get_en_rxaddr(nrf, pipe, &state)))
		goto exit_err;
	return sprintf(buf, "%u\n", state);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_enable_pipe0(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enable(dev, buf, 0);
}

ssize_t nrf24l01_sysfs_show_enable_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enable(dev, buf, 1);
}

ssize_t nrf24l01_sysfs_show_enable_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enable(dev, buf, 2);
}

ssize_t nrf24l01_sysfs_show_enable_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enable(dev, buf, 3);
}

ssize_t nrf24l01_sysfs_show_enable_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enable(dev, buf, 4);
}

ssize_t nrf24l01_sysfs_show_enable_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enable(dev, buf, 5);
}

static ssize_t nrf24l01_sysfs_store_enable(struct device* dev, const char* buf, size_t count, unsigned int pipe)
{
	ssize_t err;
	unsigned int state;
	nrf24l01_t* nrf = ((nrf24l01_chrdev*)dev_get_drvdata(dev))->nrf;
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &state)))
		goto exit_stralloc;
	if((err = nrf24l01_set_en_rxaddr(nrf, pipe, state)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_enable_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enable(dev, buf, count, 0);
}

ssize_t nrf24l01_sysfs_store_enable_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enable(dev, buf, count, 1);
}

ssize_t nrf24l01_sysfs_store_enable_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enable(dev, buf, count, 2);
}

ssize_t nrf24l01_sysfs_store_enable_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enable(dev, buf, count, 3);
}

ssize_t nrf24l01_sysfs_store_enable_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enable(dev, buf, count, 4);
}

ssize_t nrf24l01_sysfs_store_enable_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enable(dev, buf, count, 5);
}

static ssize_t nrf24l01_sysfs_show_dynpd(struct device* dev, char* buf, unsigned int pipe)
{
	ssize_t err;
	unsigned int state;
	nrf24l01_t* nrf = ((nrf24l01_chrdev*)dev_get_drvdata(dev))->nrf;
	if((err = nrf24l01_get_dynpd(nrf, pipe, &state)))
		goto exit_err;
	return sprintf(buf, "%u\n", state);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_dynpd_pipe0(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_dynpd(dev, buf, 0);
}

ssize_t nrf24l01_sysfs_show_dynpd_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_dynpd(dev, buf, 1);
}

ssize_t nrf24l01_sysfs_show_dynpd_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_dynpd(dev, buf, 2);
}

ssize_t nrf24l01_sysfs_show_dynpd_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_dynpd(dev, buf, 3);
}

ssize_t nrf24l01_sysfs_show_dynpd_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_dynpd(dev, buf, 4);
}

ssize_t nrf24l01_sysfs_show_dynpd_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_dynpd(dev, buf, 5);
}

static ssize_t nrf24l01_sysfs_store_dynpd(struct device* dev, const char* buf, size_t count, unsigned int pipe)
{
	ssize_t err;
	unsigned int state;
	nrf24l01_t* nrf = ((nrf24l01_chrdev*)dev_get_drvdata(dev))->nrf;
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &state)))
		goto exit_stralloc;
	if((err = nrf24l01_set_dynpd(nrf, pipe, state)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_dynpd_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_dynpd(dev, buf, count, 0);
}

ssize_t nrf24l01_sysfs_store_dynpd_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_dynpd(dev, buf, count, 1);
}

ssize_t nrf24l01_sysfs_store_dynpd_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_dynpd(dev, buf, count, 2);
}

ssize_t nrf24l01_sysfs_store_dynpd_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_dynpd(dev, buf, count, 3);
}

ssize_t nrf24l01_sysfs_store_dynpd_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_dynpd(dev, buf, count, 4);
}

ssize_t nrf24l01_sysfs_store_dynpd_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_dynpd(dev, buf, count, 5);
}

static ssize_t nrf24l01_sysfs_show_enaa(struct device* dev, char* buf, unsigned int pipe)
{
	ssize_t err;
	unsigned int state;
	nrf24l01_t* nrf = ((nrf24l01_chrdev*)dev_get_drvdata(dev))->nrf;
	if((err = nrf24l01_get_enaa(nrf, pipe, &state)))
		goto exit_err;
	return sprintf(buf, "%u\n", state);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_enaa_pipe0(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enaa(dev, buf, 0);
}

ssize_t nrf24l01_sysfs_show_enaa_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enaa(dev, buf, 1);
}

ssize_t nrf24l01_sysfs_show_enaa_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enaa(dev, buf, 2);
}

ssize_t nrf24l01_sysfs_show_enaa_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enaa(dev, buf, 3);
}

ssize_t nrf24l01_sysfs_show_enaa_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enaa(dev, buf, 4);
}

ssize_t nrf24l01_sysfs_show_enaa_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enaa(dev, buf, 5);
}

static ssize_t nrf24l01_sysfs_store_enaa(struct device* dev, const char* buf, size_t count, unsigned int pipe)
{
	ssize_t err;
	unsigned int state;
	nrf24l01_t* nrf = ((nrf24l01_chrdev*)dev_get_drvdata(dev))->nrf;
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &state)))
		goto exit_stralloc;
	if((err = nrf24l01_set_enaa(nrf, pipe, state)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_enaa_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enaa(dev, buf, count, 0);
}

ssize_t nrf24l01_sysfs_store_enaa_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enaa(dev, buf, count, 1);
}

ssize_t nrf24l01_sysfs_store_enaa_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enaa(dev, buf, count, 2);
}

ssize_t nrf24l01_sysfs_store_enaa_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enaa(dev, buf, count, 3);
}

ssize_t nrf24l01_sysfs_store_enaa_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enaa(dev, buf, count, 4);
}

ssize_t nrf24l01_sysfs_store_enaa_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enaa(dev, buf, count, 5);
}
