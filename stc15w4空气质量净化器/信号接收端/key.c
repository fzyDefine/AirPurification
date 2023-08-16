#include "key.h"
u8 _4Keys_Scan();
u8 _16Keys_Scan();

u8 key_value = 0;

void Timer_Long_Press(u8 key_total, u8 *get_value)
{
    if (key_total == 4)
    {
        *get_value = _4Keys_Scan();
    }
    else
    {
        *get_value = _16Keys_Scan();
    }
}

// mode == 0Ϊ �̰�ģʽ, 1Ϊ����ģʽ
void Timer_Keys_Scan(u8 key_total) //��¼���һ�ΰ��µİ���ֵ
{
    static u8 now_state = 0, last_state = 0;

    last_state = now_state;

    if (key_total == 4)
        now_state = _4Keys_Scan();
    else
        now_state = _16Keys_Scan();

    //ȷ����һ��10ms��⵽�˰�������,������μ�������˼�Ϊһ����Ч��������
    if (last_state != 0 && now_state == 0)
    {
        key_value = last_state; //��������ֵ�洢��key_value
    }
}

u8 read_key_value() //�ڶ̰�ģʽ��,���ⲿ���ʴ˺���ʱ��,���ش���İ���ֵ��������,�Ұ���ֵkey_value��λΪ0
{
    u8 temp = 0;
    temp = key_value;
    key_value = 0;
    return temp;
}

u8 _4Keys_Scan()
{
    u8 key_num = 0;
    if (KEY_S4_PIN == 0)
        key_num = S4_PRESS;
    else if (KEY_S5_PIN == 0)
        key_num = S5_PRESS;
    // else if (KEY_S6_PIN == 0)
    //     key_num = S6_PRESS;
    // else if (KEY_S7_PIN == 0)
    //     key_num = S7_PRESS;

    return key_num;
}

u8 _16Keys_Scan()
{
    u8 key_num = 0;
    KEY_16_REG = 0x0f;
    P42 = 0;
    P44 = 0;
    if (KEY_16_REG != 0x0f)
    {
        KEY_16_REG = 0x0f;
        switch (KEY_16_REG)
        {
        case 0x07:
            key_num = 4;
            break;
        case 0x0b:
            key_num = 5;
            break;
        case 0x0d:
            key_num = 6;
            break;
        case 0x0e:
            key_num = 7;
            break;
        }
        KEY_16_REG = 0xf0;
        P42 = 1;
        P44 = 1;
        if (!P44)
            key_num = key_num;
        if (!P42)
            key_num = key_num + 4;
        if (!P35)
            key_num = key_num + 8;
        if (!P34)
            key_num = key_num + 12;
    }

    return key_num;
}
