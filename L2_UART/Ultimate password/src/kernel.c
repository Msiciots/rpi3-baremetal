#include "mini_uart.h"
#define ans 43

void send_quession(int a,int b){
	char s[34] = "Guess a number between 100 ~ 100\r\n";
	int s_count=23;
	int rev_count=0,i;
	char rev[10];
	if(a==0){
		s[s_count++]='0';
	}
	else{
	while(a > 0){
		char atoc = a%10 +'0';
		rev[rev_count++]= atoc;
		a = a/10;
	}
	rev[rev_count]='\0';
	// uart_send_string(rev);
	for(i = rev_count-1;i>=0;i--){
		s[s_count++]=rev[i];
	}
	}
	s[s_count++]=' ';
	s[s_count++]='~';
	s[s_count++]=' ';
	rev_count=0;
	while(b > 0){
		char btoc = b%10 +'0';
		rev[rev_count++]= btoc;
		b = b/10;
	}
	for(i = rev_count-1;i>=0;i--){
		s[s_count++]=rev[i];
	}
	s[s_count++]='\r';
	s[s_count++]='\n';
	s[s_count++]='\0';
	uart_send_string(s);
	
}
void kernel_main(void)
{
	uart_init();
	uart_send_string("Guess a number between 0 ~ 100\r\n");
    int a=0,b=100;
	while (1) {
		int d=0;
		char c=uart_recv();
		uart_send(c);
		while(c!=13){
			
			d = d*10;
			d = d + c - '0';
			c = uart_recv();
			if(c==13)
				uart_send_string("\r\n");
			else
				uart_send(c);
		}
		if (d == ans){
			uart_send_string("You win !!\r\n");
			
		}
		else if((d>a)&&(d<b)){
			if(d>ans)
				b = d;
			else 
				a = d;
			send_quession(a,b);
		}
		else
		    uart_send_string("wrong input!!\r\n");
	}
}
