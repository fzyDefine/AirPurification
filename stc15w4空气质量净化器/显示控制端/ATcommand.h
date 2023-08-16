#ifndef __ATCOMMAND_H_
#define __ATCOMMAND_H_

#define u8 unsigned char
#define u16 unsigned int
#define u8 unsigned char
#define u16 unsigned int
#define true  1
#define flase 0
#define bool u8

void Set_MsgMode(u8 *phone_center);
void Send_Msg(u8 *target_phone,u8 *content);
bool Wait_CREG(void);

#endif // !__ATCOMMAND_H_