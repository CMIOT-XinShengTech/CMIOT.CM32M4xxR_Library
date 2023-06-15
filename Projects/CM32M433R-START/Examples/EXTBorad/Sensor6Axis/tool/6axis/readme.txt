6轴传感器演示的程序需要在板端的main.c代码中新增{angle}字段（修改后需要先clean再编译）

main函数如下：


int main(void)
{
	int ms_count = 0;
	unsigned int timestamp;
	float temperature;
	float acc[3],gyro[3];
	float angle_x = 0;
	float angle_y = 0;
	float angle_z = 0;
	log_init();
	qmi8658_init();
	delay_ms(100);

    while (1)
    {
    	delay_ms(10);
    	ms_count = ms_count + 1;
    	qmi8658_read_sensor_data(acc,gyro);
    	if(gyro[0]>0)
    	{
    		angle_x = angle_x + (int)((gyro[0]+0.05)*10+0.5);
    	}
    	else
    	{
    		angle_x = angle_x + (int)((gyro[0]+0.05)*10-0.5);
    	}

    	if(gyro[0]>0)
		{
    		angle_y = angle_y + (int)((gyro[1]+0.06)*10+0.5);
		}
		else
		{
			angle_y = angle_y + (int)((gyro[1]+0.06)*10-0.5);
		}

    	if(gyro[0]>0)
		{
    		angle_z = angle_z + (int)(gyro[2]*10+0.5);
		}
		else
		{
			angle_z = angle_z + (int)(gyro[2]*10-0.5);
		}

    	if(ms_count < 11)
    	{
    		continue;
    	}

    	qmi8658_read_timestamp(&timestamp);
    	temperature = qmi8658_readTemp();
    	printf("<%d>{ACC}%f m/s2, %f m/s2 ,%f m/s2\n",timestamp,acc[0],acc[1],acc[2]);
    	printf("<%d>{GYRO}%f rad/s, %f rad/s,%f rad/s\n",timestamp,gyro[0],gyro[1],gyro[2]);
    	printf("<%d>{angle}%f rad, %f rad,%f rad\n",timestamp,angle_x/900,angle_y/900,angle_z/800);
    	printf("<%d>{TEMP}%f\n",timestamp,temperature);
    	ms_count = 0;
    }
}