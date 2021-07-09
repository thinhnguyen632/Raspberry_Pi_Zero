#include <stdio.h>
#include <stdlib.h>
#include <mariadb/mysql.h>
#include <time.h>

signed int nhiet_do=0, do_am=0;

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
    // Storing start time
    clock_t start_time = clock();
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

int random_int(int min, int max)
{
   return min + rand() % (max+1 - min);
}

void random_tang_giam_nhiet_do_va_do_am()
{  
    nhiet_do = nhiet_do + (random_int(0,8)-4); // nhiet do thay doi trong khoang -4 -> +4
    do_am = do_am + (random_int(0,8)-4); // do am thay doi trong khoang -4 -> +4
    if (nhiet_do>100)   nhiet_do=100;
    if (nhiet_do<0)     nhiet_do=0;
    if (do_am>100)      do_am=100;
    if (do_am<0)        do_am=0;
    else{
        nhiet_do = nhiet_do;
        do_am = do_am;
    }
}

int main(void)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "raspi";
    char *password = "123456"; /* set me first */
    char *database = "farm";

    while(1){
        // ket noi database
        conn = mysql_init(NULL);
        mysql_real_connect(conn,server,user,password,database,0,NULL,0); 
        
        char sql[200];

        // doc nhiet do va do am tu database
        sprintf(sql, "select nhiet_do, do_am from sensor order by stt desc limit 1");
        mysql_query(conn,sql);
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
		//while(row != NULL) // kiem tra row khac NULL de tranh loi segmentation fault
		//{
			nhiet_do = atoi(row[0]);
			do_am = atoi(row[1]);
		//}
        // tao nhiet do va do am moi
        random_tang_giam_nhiet_do_va_do_am();

        // gui nhiet do va do am moi len database
        sprintf(sql, "insert into sensor (nhiet_do, do_am) values (%d,%d)",nhiet_do,do_am);
        mysql_query(conn,sql);

        // ngat ket noi database
        mysql_close(conn);

        // thoi gian cap nhat 2s/lan
        delay(2000);
    }


    return 0;
}
