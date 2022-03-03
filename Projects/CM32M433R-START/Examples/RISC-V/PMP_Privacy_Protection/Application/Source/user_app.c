#include "privacy_api.h"
#include "privacy.h"
#include <stdio.h>

uint32_t user_app_direct()
{
  printf("enter user_app_direct \r\n");
  uint8_t tmp[16] = {0};
  uint8_t i = 0;
  uint32_t ret = 0;
  privacy_encrypt(tmp, 16 , tmp);

  // could not run to here
  for(i = 0; i < 16; i ++)
  {
    ret += tmp[i];
  }
  printf("user_app_direct success! \r\n");
  return ret;;
}


uint32_t user_app_api()
{
  printf("enter user_app_api! \r\n");
  uint8_t tmp[16] = {0};
  uint8_t i = 0;
  uint32_t ret = 0;
  privacy_encrypt_api(tmp, 16 , tmp);

  for(i = 0; i < 16; i ++)
  {
    ret += tmp[i];
  }
  printf("user_app_api success! \r\n");
  return ret;;
}

void user_app_main()
{
  printf("try call user api via system call first \r\n");
  user_app_api();
  printf("try call user api directly \r\n");
  user_app_direct();
}
