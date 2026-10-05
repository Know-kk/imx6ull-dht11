#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h> 
#include <string.h>
#include "sensor.h"
//函数
void input_data(SensorData *data,unsigned char *buf)
{
    data->temperature=buf[2]+buf[3]/10.0;
    data->humidity=buf[0]+buf[1]/10.0;
}

void add_data(SensorData *data)
{
			unsigned char buf[4];
		   int fd = open("/dev/querydht11",O_RDONLY);
		   if(fd<0)
		   {
				perror("open /dev/querydht11");
				return;
		   }
		   ssize_t len = read(fd,buf,4);
           if(len != 4)
           {
		   		perror("read sensor");
				close(fd);
				return;
           }
		   close(fd);
           input_data(data,buf);
          int file_fd=open(DATA_FILE,O_RDWR | O_CREAT | O_APPEND,0644);
            if (file_fd < 0)
        {
            printf("can not open DATA_FILE\n");
            printf("errno = %d\n", errno);
            perror("open");
        }
            len = write(file_fd, data, sizeof(SensorData));
            close(file_fd);
}

void browse_data(SensorData *data)
{
		printf("temperature:%.2f\n",data->temperature) ;
		printf("humidity:%.2f\n",data->humidity) ;
}

void browse_previous_data(SensorData *temp)
{
			int fd;
			ssize_t leng;
			fd=open(DATA_FILE,O_RDONLY);
            if (fd < 0)
        {
            printf("can not open DATA_FILE\n");
            printf("errno = %d\n", errno);
            perror("open");
        }
			lseek(fd,0,SEEK_SET);
            while((leng=read(fd,temp,sizeof(SensorData)))==sizeof(SensorData))
            {
            printf("temperature:%.2f humdity:%.2f\n",temp->temperature,temp->humidity);
            }
			if(leng==-1)
			{
			perror("read");
			}
			close(fd);
}

void statistics(SensorData *temp)
{
		int fd;
		fd=open(DATA_FILE,O_RDWR);
		if (fd < 0)
        {
            printf("can not open DATA_FILE\n");
            printf("errno = %d\n", errno);
            perror("open");
        }
    	float max_t =0.0 , sum_t ;
    	float max_h =0.0, sum_h ;
		int count =0;
		while((read(fd,temp,sizeof(SensorData)))==sizeof(SensorData))
		{
			count++;
			sum_t += temp->temperature;
			sum_h += temp->humidity;
			if(max_t<temp->temperature)
				max_t=temp->temperature;
			if(max_h<temp->humidity)
				max_h=temp->humidity;
		}
		if(count==0)
		{
			printf("zero==count\n");
			close(fd);
		}
		printf("Temperature:\n");
    	printf("  Max: %.2f\n", max_t);
    	printf("  Avg: %.2f\n", sum_t / count);
    	printf("Humidity:\n");
    	printf("  Max: %.2f\n", max_h);
    	printf("  Avg: %.2f\n", sum_h / count);
}


void clear_data(SensorData *data)
{
		printf("确定要清空所有数据吗？(y/n): ");
   	 	char ch;
    	scanf(" %c", &ch);
   	 	while (getchar() != '\n'); // 清空多余输入

    	if (ch == 'y' || ch == 'Y') 
		{
        // Linux 系统调用 unlink 删除文件
        if (unlink(DATA_FILE) == 0) 
		{
            printf("数据已清空。\n");
            // 重置当前数据状态
            data->temperature = 0.0;
            data->humidity = 0.0;
        } 
		else 
		{
            perror("清空数据失败（可能文件本来就不存在）");
        }
    	}
		else 
		{
        	printf("已取消清空操作。\n");
    	}
}


