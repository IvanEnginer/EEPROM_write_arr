#include <avr/io.h>
void EEPROM_write_arr(int address, int lenght, int *data)
{
	while (lenght)
	{
		while (EECR & (1<<1));
		EEAR = address;
		address = address + 1;
		EEDR = *data;
		data = data + 1;
		EECR |= (1 << 2);
		EECR |= (1 << 1);
		lenght = lenght -1;	
	}
}
void EEPROM_read_arr(int address, int lenght, int *data)
{
	while (EECR & (1 << 1));
	while (lenght--)
	{
		EEAR = address++;
		EECR |= (1 << 0);
		*data = EEDR;
		data++;
	}
}
void Read_write(int address1, int address2, int *data1, int data2)
{
	while (EECR & (1 << 1));
	{
		EEAR = address1;
		EECR |= (1 << 0);
		*data1 = EEDR;
	}
	while ( EECR & (1 << 1));
	EEAR = address2;
	EEDR = *data2;
	EECR |= (1 << 2);
	EECR |= (1 << 1);
}


int main(void)
{
	static int arr_iz_ram_v_eeprom[5] ={1, 2, 3, 4, 10};
	EEPROM_write_arr(0x00, 5, &arr_iz_ram_v_eeprom[0]);
	static int arr_iz_eeprom_v_ram[5];
	EEPROM_read_arr(0x00, 5, &arr_iz_eeprom_v_ram[0]);
	static int data1[1];
	static int data2[1];
	Read_write(0x00, 0x08, data1[0], data2[0]);
}