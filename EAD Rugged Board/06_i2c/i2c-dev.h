/*
    i2c-dev.h - i2c-bus driver, char device interface
 
    Copyright (C) 1995-97 Simon G. Vogl
    Copyright (C) 1998-99 Frodo Looijaard <frodol@dds.nl>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
    MA 02110-1301 USA.
*/
 
#ifndef _LINUX_I2C_DEV_H
#define _LINUX_I2C_DEV_H
 
#include <linux/types.h>
#include <sys/ioctl.h>
#include <stddef.h>
 

/*
 * Data for SMBus Messages
 */
#define I2C_SMBUS_BLOCK_MAX    32    /* As specified in SMBus standard */
#define I2C_SMBUS_I2C_BLOCK_MAX    32    /* Not specified but we use same structure */
union i2c_smbus_data {
    __u8 byte;
    __u16 word;
    __u8 block[I2C_SMBUS_BLOCK_MAX + 2]; /* block[0] is used for length */
                                                /* and one more for PEC */
};
 
/* smbus_access read or write markers */
#define I2C_SMBUS_READ    1
#define I2C_SMBUS_WRITE    0
 
/* SMBus transaction types (size parameter in the above functions)
   Note: these no longer correspond to the (arbitrary) PIIX4 internal codes! */
#define I2C_SMBUS_BLOCK_DATA        5

 
 
#define I2C_SLAVE    0x0703    /* Use this slave address */
 
#define I2C_SMBUS    0x0720    /* SMBus transfer */
 
 
/* This is the structure as used in the I2C_SMBUS ioctl call */
struct i2c_smbus_ioctl_data {
    __u8 read_write;
    __u8 command;
    __u32 size;
    union i2c_smbus_data *data;
};
 
static inline __s32 i2c_smbus_access(int file, char read_write, __u8 command,
                                     int size, union i2c_smbus_data *data)
{
    struct i2c_smbus_ioctl_data args;
 
    args.read_write = read_write;
    args.command = command;
    args.size = size;
    args.data = data;
    return ioctl(file,I2C_SMBUS,&args);
}
  
 
static inline __s32 i2c_smbus_write_block_data(int file, __u8 command,
                                               __u8 length, const __u8 *values)
{
    union i2c_smbus_data data;
    int i;
    if (length > 32)
        length = 32;
    for (i = 1; i <= length; i++)
        data.block[i] = values[i-1];
    data.block[0] = length;
    return i2c_smbus_access(file,I2C_SMBUS_WRITE,command,
                            I2C_SMBUS_BLOCK_DATA, &data);
}

#endif /* _LINUX_I2C_DEV_H */
