```javascript

	/* This code controls two stepper motors using a potentiometer to 
 	* control speed and a push button to set the turning direction of the 
 	* motor. 
	* By Simon Castillo spcastil@uc.cl
	* NOTE: you have to delete ```javascript (line 1) and ``` (line 128) before use this program
 	*/
 
 #include <AccelStepper.h>

//Define Arduino pins
int stepPin_ye= 3; //connected to step slot of Easydriver
int dirPin_ye = 2; //connected to direction slot of Easydriver
int switchPin_ye = 8; //connected to push button
int speedPin_ye = 10; // connected to th potentiometer
int stepPin_gr= 5; //connected to step slot of Easydriver
int dirPin_gr = 4; //connected to direction slot of Easydriver
int switchPin_gr = 9; //connected to push button
int speedPin_gr = 11; // connected to th potentiometer

//Define global variables
int estado_switchPin_ye = 0;
int estadoAnt_switchPin_ye = 0;
int out_ye = 0;
int customDelay_ye,customDelayMapped_ye;
int estado_switchPin_gr = 0;
int estadoAnt_switchPin_gr = 0;
int out_gr = 0;
int customDelay_gr,customDelayMapped_gr; 

//Initialize stepper called by AccelStepper.h library 
AccelStepper stepperY (1,stepPin_ye,dirPin_ye); // 1: Easy driver 
AccelStepper stepperG (1,stepPin_gr,dirPin_gr); //  1: Easy driver 


void setup() {
		//For yellow motor
		pinMode (switchPin_ye, INPUT);  
		pinMode(dirPin_ye, OUTPUT);
		pinMode(stepPin_ye, OUTPUT);
		digitalWrite(dirPin_ye, LOW);
		digitalWrite(stepPin_ye, LOW);
		stepperY.setMaxSpeed (4800.0);
		stepperY.setAcceleration (500.0);
		
		//For green motor
		pinMode (switchPin_gr, INPUT);  
		pinMode(dirPin_gr, OUTPUT);
		pinMode(stepPin_gr, OUTPUT);
		digitalWrite(dirPin_gr, LOW);
		digitalWrite(stepPin_gr, LOW);
		stepperG.setMaxSpeed (4800.0);
		stepperG.setAcceleration (50.0);
}

void loop() {
		estado_switchPin_ye = digitalRead (switchPin_ye);
		estado_switchPin_gr = digitalRead (switchPin_gr);

		if ((estado_switchPin_ye == HIGH) && (estadoAnt_switchPin_ye == LOW)) {
		out_ye = 1-out_ye;
		delay(30);
		}
		
		if ((estado_switchPin_gr == HIGH) && (estadoAnt_switchPin_gr == LOW)) {
		out_gr = 1-out_gr;
		delay(30);
		}
  
     

 //out_ye = out_gr = 1 implies clockwise turning; 0 is anti-clockwise
		if ((out_ye == 1) && (out_gr == 1)) {
		  digitalWrite (estado_switchPin_ye, HIGH);
		  digitalWrite (estado_switchPin_gr, HIGH);
		  stepperY.setSpeed(speedUp_ye());
		  stepperG.setSpeed(speedUp_gr());
		  stepperY.runSpeed();
		  stepperG.runSpeed();
		  }
		  
		if ((out_ye == 0) && (out_gr == 1)){
		  digitalWrite (estado_switchPin_ye, LOW);
		  digitalWrite (estado_switchPin_gr, HIGH);
		  stepperY.setSpeed(-speedUp_ye());
		  stepperG.setSpeed(speedUp_gr());
		  stepperY.runSpeed();
		  stepperG.runSpeed();
		  }  
	  
			  
		if ((out_gr == 0) && (out_ye == 1)) {
		  digitalWrite (estado_switchPin_gr, LOW);
		  digitalWrite (estado_switchPin_ye, HIGH);
		  stepperY.setSpeed(speedUp_ye());
		  stepperG.setSpeed(-speedUp_gr());
		  stepperY.runSpeed();
		  stepperG.runSpeed();
		  }
		
		if ((out_gr == 0) && (out_ye == 0)) {
		  digitalWrite (estado_switchPin_gr, LOW);
		  digitalWrite (estado_switchPin_ye, LOW);
		  stepperY.setSpeed(-speedUp_ye());
		  stepperG.setSpeed(-speedUp_gr());
		  stepperY.runSpeed();
		  stepperG.runSpeed();
		  }
		  
		estadoAnt_switchPin_ye = estado_switchPin_ye;
		estadoAnt_switchPin_gr = estado_switchPin_gr;
}
/*Functions that read the potentiometers and convert those values into 
speed values*/
int speedUp_ye() {
  int customDelay_ye = analogRead(speedPin_ye); 
  int newCustom_ye = map(customDelay_ye, 0, 1023, 0,2000); 
  return newCustom_ye;  
  }


int speedUp_gr() {
  int customDelay_gr = analogRead(speedPin_gr); 
  int newCustom_gr = map(customDelay_gr, 0, 1023, 0,2000); 
  return newCustom_gr;  
  }
```
