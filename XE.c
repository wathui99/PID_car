#include "function.h"
#define time_get_sample 40.0
#define err_ratio_PID_servo 150.0

#define kp_m 23
#define ki_m 0.001
#define kd_m 0.46

#define time_servo 50

#define handle_case_21	3
#define handle_case_22	13
#define handle_case_23	15
#define handle_case_24	15
#define handle_case_25	18
#define handle_case_26	27
#define handle_case_27	45 //33
#define handle_case_28	64 //54
#define handle_case_29	106 //97
#define handle_case_210	130
#define handle_case_211	140

#define handle_case_31	-3
#define handle_case_32	-15
#define handle_case_33	-18
#define handle_case_34	-18
#define handle_case_35	-24
#define handle_case_36	-29
#define handle_case_37	-45 //-33
#define handle_case_38	-61 //51
#define handle_case_39	-103 //95
#define handle_case_310	-135
#define handle_case_311	-145


void case_40();	// cua vuong
void case_50(); // trai
void case_60(); // phai
void PID_ctrl_motor();
void PID_ctrl_servo();

uint8_t  pattern_dir;
uint8_t pattern_level;
volatile uint16_t pulse_v;
volatile int pre_err;
volatile uint32_t pulse_time_get_sample;
volatile uint16_t pulse_time_case_special;

int main(void)
{
	INIT();
	sel_mode();
	//float goc=0;
	//while(1) {
		//handle(goc);
		//led7_data.sensor_out=(sensor_cmp(0xff));
		//led7((goc<0?-(int)goc:(int)goc));
		//if(get_button(BTN0)) {
			//if(goc-3<-150) goc=150;
			//else goc-=3;
		//}
		//if(get_button(BTN1)) {
			//if(goc+3>150) goc=-150;
			//else goc+=3;
		//}
		//if(get_button(BTN2)) {
			//goc=0;
		//}
	//}
	//init elements pid
	pulse_time_get_sample=0;
	pulse_v=0;
	pre_err=0;
	//end init
	pattern_dir=10;
	uint8_t conti=true;
	int previous=0; //truong hop truoc do
	int pre_handle=0;
	pulse_time_case_special=0;
	while(1)
	{
		case40:
		if (sensor_cmp(0xFF)==0b11111111||sensor_cmp(0xFF)==0b11101111) { //truong hop case_40 (cua vuong phai)
			special_flag=true;
			crook_flag=false;
			straight_flag=false;
			special_ratio=1;
			speed(-225,-225,100);
			_delay_ms(200);
			special_ratio=0.4;
			speed(100,100, 100);
			case_40();
			special_flag=false;
		}
		if (sensor_cmp(0xFF)==0b11111000 || sensor_cmp(0xFF)==0b11111100 || sensor_cmp(0xFF)==0b11111110) { // case 50 (queo trai)
			special_flag=true;
			crook_flag=false;
			straight_flag=false;
			handle(-33);
			special_ratio=1;
			if(pulse_v>11) {
				speed(-255,-255,100);
				_delay_ms(100);
			}
			special_ratio=0.8;
			speed(50,80,80);
			pulse_time_case_special=0; //thoi gian chong nhieu~
			while (pulse_time_case_special<20) {
				if(sensor_cmp(0xFF)==0xFF) { goto case40;}
			}
			case_50();
			special_flag=false;
		}
		if (sensor_cmp(0xFF)==0b00011111 || sensor_cmp(0xFF)==0b00111111 || sensor_cmp(0xFF)==0b01111111 ){
			special_flag=true;
			crook_flag=false;
			straight_flag=false;
			handle(42);
			special_ratio=1;
			if(pulse_v>11) {
				speed(-255,-255,100);
				_delay_ms(100);
			}
			special_ratio=0.8;
			speed(80,50,80);
			pulse_time_case_special=0; //thoi gian chong nhieu~
			while (pulse_time_case_special<20) {
				if(sensor_cmp(0xFF)==0xFF) { goto case40;}
			}
			case_60();
			special_flag=false;
		}
		//nhap du lieu led 7
		led7_data.sensor_out=sensor_cmp(0xFF);
		print();
		
		//===========xet truong hop queo trai, phai, thang
		if (conti) {
			//led7(pattern_dir);
			switch(sensor_cmp(0xFF)) {
				case 0b00111100:
					pattern_dir=10; //di thang
					straight_flag=true;
					crook_flag=false;
					special_flag=false;
					break;
				case 0b00011100:
				case 0b00011110:
				case 0b00010110:
				case 0b00001110:
				case 0b00000110:
				case 0b00000111:
				case 0b00000011:
					pattern_dir=20; //queo phai
					break;
				case 0b00111000:
				case 0b01111000:
				case 0b01101000:
				case 0b01100000:
				case 0b11100000:
				case 0b11000000:
					pattern_dir=30; //queo trai
					break;
				default:
					speed(0,0,0);
					break;
			}
		}
		
		switch(pattern_dir) {
			case 10:
				if(previous!=10) {
					straight_flag=true;
					crook_flag=false;
					special_flag=false;
					speed(255,255,100);
					previous=10;
				}
				led7(10);
				break;
			case 20:
				pattern_level=sensor_cmp(0xFF);
				switch(pattern_level) {
					
					case 0b00011100: //21
						if (previous!=21) {
							uint16_t temp=pulse_v_des;
							pulse_v_des=(pulse_v_des/100)*90;
							straight_flag=true;
							crook_flag=false;
							special_flag=false;
							speed(255,204,100);
							pulse_v_des=temp;
						}
						handle(handle_case_21);
						pre_handle=handle_case_21;
						while(sensor_cmp(0xff)==0b00011100) {}
						led7(21);
						previous=21;
						conti=false;
						break;
						
					case 0b00011110: //22					
						if(previous!=22) {
							uint16_t temp=pulse_v_des;
							pulse_v_des=(pulse_v_des/100)*90;
							straight_flag=true;
							crook_flag=false;
							special_flag=false;
							speed(255,204,100);
							pulse_v_des=temp;
						}
						handle(handle_case_22);
						pre_handle=handle_case_22;
						while(sensor_cmp(0xff)==0b00011110);
						led7(22);
						previous=22;
						conti=false;
						break;
	
					case 0b00010110: //23
					case 0b00001110: //24
						if(previous!=30) {
							uint16_t temp=pulse_v_crook_des;
							pulse_v_crook_des=(pulse_v_crook_des/100)*80;
							straight_flag=false;
							crook_flag=true;
							special_flag=false;
							speed(255,179,100);
							pulse_v_crook_des=temp;
						}
						handle(handle_case_23);
						pre_handle=handle_case_23;
						while (sensor_cmp(0xff)==0b00010110||sensor_cmp(0xff)==0b00001110);
						led7(2324);
						previous=23;
						conti=false;
						break;
					
					case 0b00000100:
					case 0b00000110: //25
						if(previous!=25) {
							uint16_t temp=pulse_v_crook_des;
							pulse_v_crook_des=(pulse_v_crook_des/100)*80;
							straight_flag=false;
							crook_flag=true;
							special_flag=false;
							speed(255,128,60);
							pulse_v_crook_des=temp;
						}
						handle(handle_case_25);
						pre_handle=handle_case_25;
						while(sensor_cmp(0xff)==0b00000100||sensor_cmp(0xff)==0b00000110);
						led7(25);
						previous=25;
						conti=false;
						break;
						
					case 0b00000111: //26
						if(previous!=26) {
							uint16_t temp=pulse_v_crook_des;
							pulse_v_crook_des=(pulse_v_crook_des/100)*70;
							straight_flag=false;
							crook_flag=true;
							special_flag=false;
							speed(255,128,50);
							pulse_v_crook_des=temp;
						}
						handle(handle_case_26);
						pre_handle=handle_case_26;
						while(sensor_cmp(0xff)==0b00000111);
						led7(26);
						previous=26;
						conti=false;
						break;
						
					case 0b00000011: //27
						if(previous!=27) {
							special_flag=true;
							special_ratio=0.3;
							speed(255,-80,100);
						}
						special_flag=false;
						handle(handle_case_27);
						pre_handle=handle_case_27;
						while(sensor_cmp(0xff)==0b00000011);
						led7(27);
						previous=27;
						conti=false;
						break;
						
					case 0b00000001: //28
						if(previous!=28) {
							special_flag=true;
							special_ratio=0.4;
							speed(255,-90,100);
						}
						special_flag=false;
						handle(handle_case_28);
						pre_handle=handle_case_28;
						while(sensor_cmp(0xff)==0b00000001);
						led7(28);
						previous=28;
						conti=false;
						break;
						
					case 0b00000000: //29
						if(previous!=29){
							special_flag=true;
							special_ratio=0.5;
							speed(255,-90,100);
						}
						special_flag=false;
						handle(handle_case_29);
						pre_handle=handle_case_29;
						while(sensor_cmp(0xff)==0b00000000);
						led7(29);
						previous=29;
						conti=false;
						break;
						
					case 0b10000000: //210
						if(previous!=210) {
							special_flag=true;
							special_ratio=0.5;
							speed(255,-100,90);
						}
						special_flag=false;
						handle(handle_case_210);
						pre_handle=handle_case_210;
						led7(210);
						previous=210;
						conti=false;
						break;
					case 0b11000000: //211
						if(previous!=211) {
							special_flag=true;
							special_ratio=0.5;
							speed(255,-100,100);
						}
						special_flag=false;
						handle(handle_case_211);
						pre_handle=handle_case_211;
						led7(211);
						previous=211;
						conti=false;
						break;
					case 0b00111000:
						if(previous==210||previous==211) break;
						pattern_dir=30;
						conti=true;
						break;
					
					case 0b00111100:
						if(previous==210||previous==211) break;
						straight_flag=true;
						crook_flag=false;
						special_flag=false;
						speed(255,255,100);
						pattern_dir=10;
						conti=true;
						break;
				}
				break;
			case 30:
				pattern_level=sensor_cmp(0xFF);
				switch(pattern_level) {
					case 0b00111000: //31
						if(previous!=31) {
							uint16_t temp=pulse_v_des;
							pulse_v_des=(pulse_v_des/100)*90;
							straight_flag=true;
							crook_flag=false;
							special_flag=false;
							speed(204,255,90);
							pulse_v_des=temp;
						}
						handle(handle_case_31);
						while(sensor_cmp(0xff)==0b00111000);
						led7(31);
						previous=31;
						conti=false;
						break;
						
					case 0b01111000: //32
						if(previous!=32) {
							uint16_t temp=pulse_v_des;
							pulse_v_des=(pulse_v_des/100)*80;
							straight_flag=true;
							crook_flag=false;
							special_flag=false;
							speed(204,255,80);
							pulse_v_des=temp;
						}
						handle(handle_case_32);
						while(sensor_cmp(0xff)==0b01111000);
						led7(32);
						previous=32;
						conti=false;
						break;
					
					case 0b01101000: //33
						if(previous!=33) {
							uint16_t temp=pulse_v_crook_des;
							pulse_v_crook_des=(pulse_v_crook_des/100)*80;
							straight_flag=false;
							crook_flag=true;
							special_flag=false;
							speed(179,255,70);
							pulse_v_crook_des=temp;
						}
						handle(handle_case_33);
						while(sensor_cmp(0xff)==0b01101000);
						led7(33);
						previous=33;
						conti=false;
						break;
						
					case 0b01100000: //35
						if(previous!=35) {
							uint16_t temp=pulse_v_crook_des;
							pulse_v_crook_des=(pulse_v_crook_des/100)*70;
							straight_flag=false;
							crook_flag=true;
							special_flag=false;
							speed(128,255,60);
							pulse_v_crook_des=temp;
						}
						handle(handle_case_35);
						while(sensor_cmp(0xff)==0b01100000);
						
						previous=35;
						led7(35);
						conti=false;
						break;
					case 0b11100000: //36
						if(previous!=36) {
							uint16_t temp=pulse_v_crook_des;
							pulse_v_crook_des=(pulse_v_crook_des/100)*70;
							straight_flag=false;
							crook_flag=true;
							special_flag=false;
							speed(128,255,50);
							pulse_v_crook_des=temp;
						}
						handle(handle_case_36);
						while(sensor_cmp(0xff)==0b11100000);
						previous=36;
						led7(36);
						conti=false;
						break;
					case 0b11000000: //37
						if(previous!=37) {
							special_flag=1;
							special_ratio=0.3;
							speed(-80,255,100);
						}
						special_flag=false;
						handle(handle_case_37);
						while(sensor_cmp(0xff)==0b11000000);
						previous=37;
						led7(37);
						conti=false;
						break;
					case 0b10000000: //38
						if(previous!=38) {
							special_flag=1;
							special_ratio=0.4;
							speed(-90,255,100);
						}
					special_flag=false;
						handle(handle_case_38);
						while(sensor_cmp(0xff)==0b10000000);
						previous=38;
						led7(38);
						conti=false;
						break;
						
					case 0b00000000: //39
						if(previous!=39) {
							special_flag=1;
							special_ratio=0.5;
							speed(-90,255,100);
						}
						special_flag=false;
						handle(handle_case_39);
						while(sensor_cmp(0xff)==0b00000000);
						previous=39;
						led7(39);
						conti=false;
						break;
						
					case 0b00000001: //310
						if(previous!=310) {
							special_flag=true;
							special_ratio=0.5;
							speed(-100,255,90);
						}
						special_flag=false;
						handle(handle_case_310);
						pre_handle=handle_case_310;
						previous=310;
						led7(310);
						conti=false;
						break;
						
					case 0b00000011: //311
						if(previous!=311) {
							special_flag=true;
							special_ratio=0.5;
							speed(-100,255,100);
						}
						special_flag=false;
						handle(handle_case_311);
						pre_handle=handle_case_311;
						previous=311;
						//led7(311);
						conti=false;
						break;
					
					case 0b00011100:
						if(previous==310||previous==311) break;
						pattern_dir=20;
						conti=true;
						break;
						
					case 0b00111100:
						if(previous==310||previous==311) break;
						straight_flag=true;
						crook_flag=false;
						special_flag=false;
						pattern_dir=10;
						conti=true;
						break;
				}
				break;
		}		
	}
}

// special case
void case_40() {
	uint8_t conti=true;
	uint8_t pattern_dir=10;
	uint8_t pattern_level;
	int previous=10;
	while (1) {
		if (sensor_cmp(0xFF)==0b00011100||
		sensor_cmp(0xFF)==0b00011110||
		sensor_cmp(0xFF)==0b00010110||
		sensor_cmp(0xFF)==0b00001110||
		sensor_cmp(0xFF)==0b00000110||
		sensor_cmp(0xFF)==0b00000111||
		sensor_cmp(0xFF)==0b00000001||
		
		sensor_cmp(0xFF)==0b00111000||
		sensor_cmp(0xFF)==0b01111000||
		sensor_cmp(0xFF)==0b01100000||
		sensor_cmp(0xFF)==0b11100000||
		sensor_cmp(0xFF)==0b11000000||
		sensor_cmp(0xFF)==0b10000000) // delay den khi nao thoat khoi vach ngang bao hieu
		break;
	}
	while(1) { // bat dau while
		led7_data.sensor_out=sensor_cmp(0xFF);
		switch(sensor_cmp(0xFF)) {
			//tin hieu re phai (cua vuong)
			case 0b11010000:
			case 0b10010000:
			case 0b00011111:
			case 0b00001111:
			handle(110);
			special_ratio=0.5;
			speed(220,-50,100);
			uint8_t value=sensor_cmp(0xFF);
			while(1) {
				if(value==0b00111100||
				value==0b00011100||
				value==0b00011110||
				value==0b00010110||
				value==0b00001110||
				value==0b00000110||
				value==0b00111000||
				value==0b01111000||
				value==0b01101000||
				value==0b01100000)
				return;
				value=sensor_cmp(0xFF);
			}
			break;
			
			//tin hieu re trai cua vuong
			case 0b11111000:
			case 0b00010011:
			case 0b00010001:
			case 0b00010110:
			case 0b11101100:
				handle(-110);
				special_ratio=0.5;
				speed(-30,220,100);
				value=sensor_cmp(0xFF);
				while(1) {
					if(value==0b00111100||
					value==0b00011100||
					value==0b00011110||
					value==0b00010110||
					value==0b00001110||
					value==0b00000110||
					value==0b00111000||
					value==0b01111000||
					value==0b01101000||
					value==0b01100000)
					return;
					value=sensor_cmp(0xFF);
				}
			break;
		}
		if (conti) {
			led7(pattern_dir);
			switch(sensor_cmp(0xFF)) {
				case 0b00111100:
				pattern_dir=10; //di thang
				break;
				case 0b00011100:
				case 0b00011110:
				case 0b00010110:
				case 0b00001110:
				case 0b00000110:
				case 0b00000111:
				case 0b00000011:
				case 0b00000001:
				pattern_dir=20; //queo phai
				break;
				case 0b00111000:
				case 0b01111000:
				case 0b01101000:
				case 0b01100000:
				case 0b11100000:
				case 0b11000000:
				case 0b10000000:
				pattern_dir=30; //queo trai
				break;
				default:
				speed(0,0,0);
				break;
			}
		}
		
		switch(pattern_dir) { //di vao chi tiet
			//case di thang
			case 10:
			if(previous!=10) {
				speed(255,255,100);
				previous=10;
			}
			break;
			//case queo phai
			case 20:
			pattern_level=sensor_cmp(0xFF);
			switch(pattern_level) {
				
				case 0b00011100: //21
				if (previous!=21) {
					speed(255,204,100);
					handle(handle_case_21);
				}
				led7(21);
				print();
				previous=21;
				conti=false;
				break;
				
				case 0b00011110: //22
				if(previous!=22) {
					speed(255,204,90);
					handle(handle_case_22);
				}
				led7(22);
				print();
				previous=22;
				conti=false;
				break;
				
				case 0b00010110: //23
				case 0b00001110: //24
				if(previous!=23) {
					speed(255,179,80);
					handle(handle_case_23);
				}
				led7(2324);
				print();
				previous=23;
				conti=false;
				break;
				
				case 0b00000100:
				case 0b00000110: //25
				if(previous!=25) {
					speed(255,128,70);
					handle(handle_case_25);
				}
				led7(25);
				print();
				previous=25;
				conti=false;
				break;
				
				case 0b00000111: //26
				if(previous!=26) {
					speed(255,128,65);
					handle(handle_case_26);
				}
				led7(26);
				print();
				previous=26;
				conti=false;
				break;
				
				case 0b00000011: //27
				if(previous!=27) {
					speed(255,26,70);
					handle(handle_case_27);
				}
				led7(27);
				print();
				previous=27;
				conti=false;
				break;
				
				case 0b00000001: //28
				if(previous!=28) {
					speed(255,0,80);
					handle(handle_case_28);
				}
				led7(28);
				print();
				previous=28;
				conti=false;
				break;
				
				//case nhieu
				case 0b01111111:
				case 0b11111110:
				case 0b01111110:
				case 0b00111111:
				case 0b11111100:
					//tin hieu re trai trong case 20
					handle(-110);
					special_ratio=0.5;
					speed(-50,220,100);
					uint8_t value = sensor_cmp(0xFF);
					while(1) {
						if(value==0b00111100||
						value==0b00011100||
						value==0b00011110||
						value==0b00010110||
						value==0b00001110||
						value==0b00000110||
						value==0b00111000||
						value==0b01111000||
						value==0b01101000||
						value==0b01100000)
						return;
						value=sensor_cmp(0xFF);
					}
				break;
				
				case 0b00111000:// case lech phai, queo trai
				case 0b01111000:
				case 0b01101000:
				case 0b01110000:
				pattern_dir=30;
				conti=true;
				break;
				
				case 0b00111100:
				speed(255,255,100);
				pattern_dir=10;
				conti=true;
				break;
			}
			break;
			
			//case queo trai
			case 30:
			pattern_level=sensor_cmp(0xFF);
			switch(pattern_level) {
				case 0b00111000: //31
				if(previous!=31) {
					speed(204,255,100);
					handle(handle_case_31);
				}
				led7(31);
				print();
				previous=31;
				conti=false;
				break;
				
				case 0b01111000: //32
				if(previous!=32) {
					speed(204,255,90);
					handle(handle_case_32);
				}
				led7(32);
				print();
				previous=32;
				conti=false;
				break;
				
				case 0b01101000: //33
				if(previous!=33) {
					speed(179,255,80);
					handle(handle_case_33);
				}
				led7(33);
				print();
				previous=33;
				conti=false;
				break;
				
				case 0b01100000: //35
				if(previous!=35) {
					speed(128,255,70);
					handle(handle_case_35);
				}
				previous=35;
				led7(35);
				print();
				conti=false;
				break;
				case 0b11100000: //36
				if(previous!=36) {
					speed(128,255,65);
					handle(handle_case_36);
				}
				previous=36;
				led7(36);
				print();
				conti=false;
				break;
				case 0b11000000: //37
				if(previous!=37) {
					speed(26,255,70);
					handle(handle_case_37);
				}
				previous=37;
				led7(37);
				print();
				conti=false;
				break;
				case 0b10000000: //38
				if(previous!=38) {
					speed(-13,255,80);
					handle(handle_case_38);
				}
				previous=38;
				led7(38);
				print();
				conti=false;
				break;
				
				//case nhieu
				case 0b01111111:
				case 0b11111110:
				case 0b01111110:
				case 0b00111111:
				case 0b11111100:
				//tin hieu re phai trong case 30
					special_ratio=0.5;
					handle(110);
					speed(220,-50,100);
					uint8_t value=sensor_cmp(0xFF);
					while(1) {
						if(value==0b00111100||
						value==0b00011100||
						value==0b00011110||
						value==0b00010110||
						value==0b00001110||
						value==0b00000110||
						value==0b00111000||
						value==0b01111000||
						value==0b01101000||
						value==0b01100000)
						return;
						value=sensor_cmp(0xFF);
					}
				break;
				
				case 0b00011100: //case lech trai
				case 0b00011110:
				case 0b00010110:
				case 0b00001110:
				pattern_dir=20;
				conti=true;
				break;
				
				case 0b00111100:
				pattern_dir=10;
				conti=true;
				break;
			}
			break;	
		}
	} //ket thuc while
}
void case_50() {
	led7(5555);
	while(sensor_cmp(0xFF)!=0x00) {}
	uint8_t temp=sensor_cmp(0xFF);
	while(temp!=0b00111000 && temp!=0b01111000 && temp!=0b01101000 && temp!=0b00011100 && temp!=0b00011110 && temp!=0b00010110 && temp!=0b00111100) {
		temp=sensor_cmp(0xff);
	}
		
}
void case_60()
{
	led7(6666);
	while(sensor_cmp(0xFF)!=0x00) {}
	uint8_t temp=sensor_cmp(0xFF);
	while(temp!=0b00111000 && temp!=0b01111000 && temp!=0b01101000 && temp!=0b00011100 && temp!=0b00011110 && temp!=0b00010110 && temp!=0b00111100) {
		temp=sensor_cmp(0xff);
	}
}

//PID ctrl
void PID_ctrl_motor() {
	volatile int err;
	if(straight_flag && !crook_flag) {
		err=pulse_v_des-pulse_v;
	}
	if(!straight_flag && crook_flag) {
		err=pulse_v_crook_des-pulse_v;
	}
	volatile float pPart=0;
	volatile float iPart=0;
	volatile float dPart=0;
	pPart=(float)err*kp_m;
	dPart=kd_m*(float)(err-pre_err)*(float)time_get_sample;
	iPart+=ki_m*(float)err*(float)time_get_sample/1000; //don vi chuan la s
	PID_ratio=(pPart+dPart+iPart)/(float)err_ratio_PID_servo;
	pre_err=err;
}
ISR(TIMER0_COMP_vect)
{
	pulse_time_case_special=(pulse_time_case_special+1)%60000; //thoi gian trong 2s
	pulse_time_get_sample++;
	if(pulse_time_get_sample==time_get_sample) {
		PID_ctrl_motor();
		pulse_v=0; //reset
		pulse_time_get_sample=0;
	}
	print();
}
ISR(INT0_vect)
{
	pulse_v++;
}
